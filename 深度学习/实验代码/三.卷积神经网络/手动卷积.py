import torch
import numpy as np
import random
from matplotlib import pyplot as plt
import torch.utils.data as Data
from PIL import Image
import os
from torch import nn
import torch.optim as optim
from torch.nn import init
import torch.nn.functional as F
import time
import torchvision
from torch.optim import optimizer
from torchvision import transforms, datasets
from shutil import copy, rmtree
import json


# 自定义单通道卷积
def corr2d(X, K):
    """
    X:输入，shape (batch_size,H,W)
    K:卷积核，shape (k_h,k_w)
    """
    batch_size, H, W = X.shape
    k_h, k_w = K.shape
    # 初始化结果矩阵
    Y = torch.zeros((batch_size, H - k_h + 1, W - k_w + 1)).to(device)
    for i in range(Y.shape[1]):
        for j in range(Y.shape[2]):
            Y[:, i, j] = (X[:, i:i + k_h, j:j + k_w] * K).sum()
    return Y


# 自定义多通道卷积
def corr2d_multi_in(X, K):
    """
    输入X:维度(batch_size,C_in,H, W)
    卷积核K:维度(C_in,k_h,k_w)
    输出:维度(batch_size,H_out,W_out)
    """
    # 先计算第一通道
    res = corr2d(X[:, 0, :, :], K[0, :, :])
    for i in range(1, X.shape[1]):
        # 按通道相加
        res += corr2d(X[:, i, :, :], K[i, :, :])
    return res


# 自定义多个多通道卷积
def corr2d_multi_in_out(X, K):
    # X: shape (batch_size,C_in,H,W)
    # K: shape (C_out,C_in,h,w)
    # Y: shape(batch_size,C_out,H_out,W_out)
    return torch.stack([corr2d_multi_in(X, k) for k in K], dim=1)


# 自定义池化
def pool2d(X, pool_size, mode='max'):
    X = X.float()
    p_h, p_w = pool_size
    Y = torch.zeros(X.shape[0] - p_h + 1, X.shape[1] - p_w + 1)
    for i in range(Y.shape[0]):
        for j in range(Y.shape[1]):
            if mode == "max":
                Y[i, j] = X[i:i + p_h, j:j + p_w].max()
            elif mode == "avg":
                Y[i, j] = X[i:i + p_h, j:j + p_w].mean()
    return Y


class MyConv2D(nn.Module):
    def __init__(self, in_channels, out_channels, kernel_size):
        super(MyConv2D, self).__init__()
        # 初始化卷积层的2个参数:卷积核、偏差
        # isinstance判断类型
        if isinstance(kernel_size, int):
            kernel_size = (kernel_size, kernel_size)
            self.weight = nn.Parameter(torch.randn((out_channels, in_channels) + kernel_size)).to(device)
            self.bias = nn.Parameter(torch.randn(out_channels, 1, 1)).to(device)

    def forward(self, x):  # x:输入图片，维度(batch_size,C_in,H,W)
        return corr2d_multi_in_out(x, self.weight) + self.bias


# 添加自定义卷积层到模块中
class MyConvModule(nn.Module):
    def __init__(self):
        super(MyConvModule, self).__init__()
        # 定义一层卷积层
        self.conv = nn.Sequential(
            MyConv2D(in_channels=3, out_channels=32, kernel_size=3),
            nn.BatchNorm2d(32),
            # inplace-选择是否进行覆盖运算
            nn.ReLU(inplace=True))
        # 输出层,将通道数变为分类数量
        self.fc = nn.Linear(32, num_classes)

    def forward(self, x):
        # 图片经过一层卷积，输出维度变为(batch_size,C_out,H,W)
        out = self.conv(x)
        # 使用平均池化层将图片的大小变为1x1,第二个参数为最后输出的长和宽（这里默认相等了）64-3/1 + 1 =62
        out = F.avg_pool2d(out, 30)
        # 将张量out从shape batchx32x1x1 变为 batch x32
        out = out.squeeze()
        # 输入到全连接层将输出的维度变为3
        out = self.fc(out)
        return out


def train_epoch(net, data_loader, device):
    net.train()  # 指定当前为训练模式
    train_batch_num = len(data_loader)  # 记录共有多少个batch
    total_1oss = 0  # 记录Loss
    correct = 0  # 记录共有多少个样本被正确分类
    sample_num = 0  # 记录样本总数

    # 遍历每个batch进行训练
    for batch_idx, (data, target) in enumerate(data_loader):
        t1 = time.time()
        # 将图片放入指定的device中
        data = data.to(device).float()
        # 将图片标签放入指定的device中
        target = target.to(device).long()
        # 将当前梯度清零
        optimizer.zero_grad()
        # 使用模型计算出结果
        output = net(data)
        # 计算损失
        loss = criterion(output, target.squeeze())
        # 进行反向传播
        loss.backward()
        optimizer.step()
        # 累加loss
        total_1oss += loss.item()
        # 找出每个样本值最大的idx,即代表预测此图片属于哪个类别
        prediction = torch.argmax(output, 1)
        # 统计预测正确的类别数量
        correct += (prediction == target).sum().item()
        # 累加当前的样本总数
        sample_num += len(prediction)
        # if batch_idx//5 ==0:
        t2 = time.time()
        print("processing:{}/{},消耗时间{}s".
              format(batch_idx + 1, len(data_loader), t2 - t1))

    # 计算平均oss与准确率
    loss = total_1oss / train_batch_num
    acc = correct / sample_num
    return loss, acc


def test_epoch(net, data_loader, device):
    net.eval()  # 指定当前模式为测试模式
    test_batch_num = len(data_loader)
    total_loss = 0
    correct = 0
    sample_num = 0
    # 指定不进行梯度变化
    with torch.no_grad():
        for batch_idx, (data, target) in enumerate(data_loader):
            data = data.to(device).float()
            target = target.to(device).long()
            output = net(data)
            loss = criterion(output, target)
            total_loss += loss.item()
            prediction = torch.argmax(output, 1)
            correct += (prediction == target).sum().item()
            sample_num += len(prediction)
    loss = total_loss / test_batch_num
    acc = correct / sample_num
    return loss, acc


data_dir = './data'
transform = transforms.Compose(
    [transforms.ToTensor(),
     transforms.Normalize((0.5, 0.5, 0.5), (0.5, 0.5, 0.5))]
)
cifar_train = torchvision.datasets.CIFAR10(root=data_dir, train=True, download=True, transform=transform)
cifar_test = torchvision.datasets.CIFAR10(root=data_dir, train=False, download=True, transform=transform)
classes = ('plane', 'car', 'bird', 'cat', 'deer', 'dog', 'frog', 'horse', 'ship', 'truck')
num_classes = 10
epochs = 5
lr = 0.001
batch_size = 512
device = torch.device("cuda:0" if torch.cuda.is_available() else "cpu")
cifar_trainloader = torch.utils.data.DataLoader(
    cifar_train, batch_size=batch_size, shuffle=True, num_workers=0
)
cifar_testloader = torch.utils.data.DataLoader(
    cifar_test, batch_size=batch_size, shuffle=True, num_workers=0
)
net = MyConvModule().to(device)

criterion = nn.CrossEntropyLoss()
optimizer = optim.Adam(net.parameters(), lr=lr)

#### 存储每一个epoch的loss与acc的变化，便于后面可视化
train_loss_list = []
train_acc_list = []
test_loss_list = []
test_acc_list = []
time_list = []
timestart = time.time()
# 进行训练
for epoch in range(epochs):
    # 每一个epoch的开始时间
    epochstart = time.time()

    # 在训练集上训练
    train_loss, train_acc = train_epoch(net, data_loader=cifar_trainloader, device=device)
    # 在测试集上验证
    test_loss, test_acc = test_epoch(net, data_loader=cifar_testloader, device=device)

    # 每一个epoch的结束时间
    elapsed = (time.time() - epochstart)
    # 保存各个指际
    train_loss_list.append(train_loss)
    train_acc_list.append(train_acc)
    test_loss_list.append(test_loss)
    test_acc_list.append(test_acc)
    time_list.append(elapsed)
    print('epoch %d, train_loss %.6f,test_loss %.6f,train_acc %.6f,test_acc %.6f,Time used %.6fs' % (
        epoch + 1, train_loss, test_loss, train_acc, test_acc, elapsed))
# 计算总时间
timesum = (time.time() - timestart)
print('The total time is %fs', timesum)


def Draw_Curve(*args, xlabel="epoch", ylabel="loss"):  #
    for i in args:
        x = np.linspace(0, len(i[0]), len(i[0]))
        plt.plot(x, i[0], label=i[1], linewidth=1.5)
    plt.xlabel(xlabel)
    plt.ylabel(ylabel)
    plt.legend()
    plt.show()


Draw_Curve([train_acc_list, "train_acc"], [test_acc_list, "test_acc"], ylabel="acc")
Draw_Curve([train_loss_list, "train_loss"], [test_loss_list, "test_loss"])
