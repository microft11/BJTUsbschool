import torch
import numpy as np
from matplotlib import pyplot as plt
import torch.utils.data as Data
from PIL import Image
import os
from torch import nn
import torch.optim as optim
import torch.nn.functional as F
import time
import torchvision
from torch.optim import optimizer
from torchvision import transforms


# pytorch封装卷积层
class DilatedConvModule(nn.Module):
    def __init__(self):
        super(DilatedConvModule, self).__init__()
        # 定义三层卷积层
        self.conv = nn.Sequential(
            # 第一层
            nn.Conv2d(in_channels=3, out_channels=32,
                      kernel_size=3, stride=1, padding=0, dilation=1),
            nn.BatchNorm2d(32),
            # inplace-选择是否进行覆盖运算
            nn.ReLU(inplace=True),
            # 第二层
            nn.Conv2d(in_channels=32, out_channels=64,
                      kernel_size=3, stride=1, padding=0, dilation=2),
            nn.BatchNorm2d(64),
            # inplace-选择是否进行覆盖运算
            nn.ReLU(inplace=True),
            # 第三层
            nn.Conv2d(in_channels=64, out_channels=128,
                      kernel_size=3, stride=1, padding=0, dilation=5),
            nn.BatchNorm2d(128),
            # inplace-选择是否进行覆盖运算
            nn.ReLU(inplace=True)
        )
        # 输出层,将通道数变为分类数量
        self.fc = nn.Linear(128, num_classes)

    def forward(self, x):
        # 图片经过三层卷积，输出维度变为(batch_size,C_out,H,W)
        out = self.conv(x)
        # 使用平均池化层将图片的大小变为1x1
        out = F.avg_pool2d(out, 16)
        # 将张量out从shape batchx128x1x1 变为 batch x128
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
net = DilatedConvModule().to(device)

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

