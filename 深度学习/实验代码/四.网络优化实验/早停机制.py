import time
import matplotlib.pyplot as plt
import numpy as np
import torch
import torch.nn as nn
import torchvision
from torch.nn.functional import cross_entropy, binary_cross_entropy
from torch.nn import CrossEntropyLoss
from torchvision import transforms
from sklearn import metrics

device = torch.device("cuda" if torch.cuda.is_available() else "cpu")  # 如果有gpu则在gpu上计算 加快计算速度
print(f'当前使用的device为{device}')
# 数据集定义
# 定义多分类数据集 - train_dataloader - test_dataloader
batch_size = 128
# Build the training and testing dataset
traindataset = torchvision.datasets.FashionMNIST(root='E:\\DataSet\\FashionMNIST\\Train',
                                                 train=True,
                                                 download=True,
                                                 transform=transforms.ToTensor())
testdataset = torchvision.datasets.FashionMNIST(root='E:\\DataSet\\FashionMNIST\\Test',
                                                train=False,
                                                download=True,
                                                transform=transforms.ToTensor())
traindataloader = torch.utils.data.DataLoader(traindataset, batch_size=batch_size, shuffle=True)
testdataloader = torch.utils.data.DataLoader(testdataset, batch_size=batch_size, shuffle=False)


# 绘制图像的代码
def picture(name, trainl, testl, xlabel='Epoch', ylabel='Loss'):
    plt.rcParams["font.sans-serif"] = ["SimHei"]  # 设置字体
    plt.rcParams["axes.unicode_minus"] = False  # 该语句解决图像中的“-”负号的乱码问题
    plt.figure(figsize=(8, 3))
    plt.title(name[-1])  # 命名
    color = ['g', 'r', 'b', 'c']
    if trainl is not None:
        plt.subplot(121)
        for i in range(len(name) - 1):
            plt.plot(trainl[i], c=color[i], label=name[i])
            plt.xlabel(xlabel)
            plt.ylabel(ylabel)
            plt.legend()
    if testl is not None:
        plt.subplot(122)
        for i in range(len(name) - 1):
            plt.plot(testl[i], c=color[i], label=name[i])
            plt.xlabel(xlabel)
            plt.ylabel(ylabel)
            plt.legend()


print(
    f'多分类数据集 样本总数量{len(traindataset) + len(testdataset)},训练样本数量{len(traindataset)},测试样本数量{len(testdataset)}')

# 手动实现
# 定义自己的前馈神经网络
from torch.nn import CrossEntropyLoss
from torch.optim import SGD


# dropout = 0.2
class MyNet():
    def __init__(self, dropout=0.0):
        # 设置隐藏层和输出层的节点数
        # global dropout
        self.dropout = dropout
        print('dropout: ', self.dropout)
        self.is_train = None
        num_inputs, num_hiddens, num_outputs = 28 * 28, 256, 10  # 十分类问题
        w_1 = torch.tensor(np.random.normal(0, 0.01, (num_hiddens, num_inputs)), dtype=torch.float32,
                           requires_grad=True)
        b_1 = torch.zeros(num_hiddens, dtype=torch.float32, requires_grad=True)
        w_2 = torch.tensor(np.random.normal(0, 0.01, (num_outputs, num_hiddens)), dtype=torch.float32,
                           requires_grad=True)
        b_2 = torch.zeros(num_outputs, dtype=torch.float32, requires_grad=True)
        self.params = [w_1, b_1, w_2, b_2]
        self.w = [w_1, w_2]
        # 定义模型结构
        self.input_layer = lambda x: x.view(x.shape[0], -1)
        self.hidden_layer = lambda x: self.my_relu(torch.matmul(x, w_1.t()) + b_1)
        self.output_layer = lambda x: torch.matmul(x, w_2.t()) + b_2

    def my_relu(self, x):
        return torch.max(input=x, other=torch.tensor(0.0))

    # 以下两个函数分别在训练和测试前调用，选择是否需要dropout
    def train(self):
        self.is_train = True

    def test(self):
        self.is_train = False

    """
    定义dropout层
    x: 输入数据
    dropout: 随机丢弃的概率
    """

    def dropout_layer(self, x):
        dropout = self.dropout
        assert 0 <= dropout <= 1  # dropout值必须在0-1之间
        # dropout==1，所有元素都被丢弃。
        if dropout == 1:
            return torch.zeros_like(x)
            # 在本情况中，所有元素都被保留。
        if dropout == 0:
            return x
        mask = (torch.rand(x.shape) < 1.0 - dropout).float()  # rand()返回一个张量，包含了从区间[0, 1)的均匀分布中抽取的一组随机数
        return mask * x / (1.0 - dropout)
        # 定义前向传播

    def forward(self, x):
        x = self.input_layer(x)
        if self.is_train:  # 如果是训练过程，则需要开启dropout 否则 需要关闭 dropout
            x = dropout_layer(x, dropout=self.dropout)
        x = self.my_relu(self.hidden_layer(x))
        if self.is_train:
            x = dropout_layer(x, dropout=self.dropout)
        x = self.output_layer(x)
        return x


# 默认的优化函数为手写的mySGD
def mySGD(params, lr, batchsize):
    for param in params:
        param.data -= lr * param.grad


# 定义L2范数惩罚项 参数 w 为模型的 w 在本次实验中为[w_1, w_2] batch_size=128
def l2_penalty(w):
    cost = 0
    for i in range(len(w)):
        cost += (w[i] ** 2).sum()
    return cost / batch_size / 2


"""
定义训练函数
model:定义的模型 默认为MyNet(0) 即无dropout的初始网络
epochs:训练总轮数 默认为30
criterion:定义的损失函数，默认为cross_entropy
lr :学习率 默认为0.1
optimizer:定义的优化函数，默认为自己定义的mySGD函数
"""


def train_and_test(model=MyNet(), init_states=None, optimizer=mySGD, epochs=20, lr=0.01, L2=False, lambd=0):
    train_all_loss = []  # 记录训练集上得loss变化
    test_all_loss = []  # 记录测试集上的loss变化
    train_ACC, test_ACC = [], []  # 记录正确的个数
    begintime = time.time()
    # 激活函数为自己定义的mySGD函数
    # criterion = cross_entropy # 损失函数为交叉熵函数
    criterion = CrossEntropyLoss()  # 损失函数
    model.train()  # 表明当前处于训练状态，允许使用dropout
    for epoch in range(epochs):
        train_l, train_acc_num = 0, 0
        for data, labels in traindataloader:
            pred = model.forward(data)
            train_each_loss = criterion(pred, labels)  # 计算每次的损失值
            # 若L2为True则表示需要添加L2范数惩罚项
            if L2 == True:
                train_each_loss += lambd * l2_penalty(model.w)
            train_l += train_each_loss.item()
            train_each_loss.backward()  # 反向传播
            # 若当前states为 None表示 使用的是 默认的优化函数mySGD
            if init_states == None:
                optimizer(model.params, lr, 128)  # 使用小批量随机梯度下降迭代模型参数
            # 否则的话使用的是自己定义的优化器，通过传入的参数，来实现优化效果
            else:
                states = init_states(model.params)
                optimizer(model.params, states, lr=lr)
            # 梯度清零
            train_acc_num += (pred.argmax(dim=1) == labels).sum().item()
            for param in model.params:
                param.grad.data.zero_()
            # print(train_each_loss)
        train_all_loss.append(train_l)  # 添加损失值到列表中
        train_ACC.append(train_acc_num / len(traindataset))  # 添加准确率到列表中
        model.test()  # 表明当前处于测试状态，无需使用dropout
        with torch.no_grad():
            is_train = False  # 表明当前为测试阶段，不需要dropout参与
            test_l, test_acc_num = 0, 0
            for data, labels in testdataloader:
                pred = model.forward(data)
                test_each_loss = criterion(pred, labels)
                test_l += test_each_loss.item()
                test_acc_num += (pred.argmax(dim=1) == labels).sum().item()
            test_all_loss.append(test_l)
            test_ACC.append(test_acc_num / len(testdataset))  # # 添加准确率到列表中
        if epoch == 0 or (epoch + 1) % 2 == 0:
            print('epoch: %d | train loss:%.5f | test loss:%.5f | train acc: %.2f | test acc: %.2f'
                  % (epoch + 1, train_l, test_l, train_ACC[-1], test_ACC[-1]))
    endtime = time.time()
    print("手动实现dropout = %d, %d轮 总用时: %.3f" % (model.dropout, epochs, endtime - begintime))
    return train_all_loss, test_all_loss, train_ACC, test_ACC


# torch.nn实现
# 利用torch.nn实现前馈神经网络-多分类任务
from collections import OrderedDict
from torch.nn import CrossEntropyLoss
from torch.optim import SGD


# 定义自己的前馈神经网络
class MyNet_NN(nn.Module):
    def __init__(self, dropout=0.0):
        super(MyNet_NN, self).__init__()
        # 设置隐藏层和输出层的节点数
        self.num_inputs, self.num_hiddens, self.num_outputs = 28 * 28, 256, 10  # 十分类问题
        # 定义模型结构
        self.input_layer = nn.Flatten()
        self.hidden_layer = nn.Linear(28 * 28, 256)
        # 根据设置的dropout设置丢失率
        self.drop = nn.Dropout(dropout)
        self.output_layer = nn.Linear(256, 10)
        # 使用relu激活函数
        self.relu = nn.ReLU()

    # 定义前向传播
    def forward(self, x):
        x = self.drop(self.input_layer(x))
        x = self.drop(self.hidden_layer(x))
        x = self.relu(x)
        x = self.output_layer(x)
        return x


# 训练
# 使用默认的参数即： num_inputs=28*28,num_hiddens=256,num_outs=10,act='relu'
model = MyNet_NN()
model = model.to(device)


# 将训练过程定义为一个函数，方便调用
def train_and_test_NN(model=model, epochs=30, lr=0.01, weight_decay=0.0, optimizer=None):
    MyModel = model
    print(MyModel)
    # 优化函数, 默认情况下weight_decay为0 通过更改weight_decay的值可以实现L2正则化。
    # 默认的优化函数为SGD 可以根据参数来修改优化函数
    if optimizer == None:
        optimizer = SGD(MyModel.parameters(), lr=lr, weight_decay=weight_decay)
    criterion = CrossEntropyLoss()  # 损失函数
    criterion = criterion.to(device)
    train_all_loss = []  # 记录训练集上得loss变化
    test_all_loss = []  # 记录测试集上的loss变化
    train_ACC, test_ACC = [], []
    begintime = time.time()
    for epoch in range(epochs):
        train_l, train_epoch_count, test_epoch_count = 0, 0, 0
        for data, labels in traindataloader:
            data, labels = data.to(device), labels.to(device)
            pred = MyModel(data)
            train_each_loss = criterion(pred, labels.view(-1))  # 计算每次的损失值
            optimizer.zero_grad()  # 梯度清零
            train_each_loss.backward()  # 反向传播
            optimizer.step()  # 梯度更新
            train_l += train_each_loss.item()
            train_epoch_count += (pred.argmax(dim=1) == labels).sum()
        train_ACC.append(train_epoch_count / len(traindataset))
        train_all_loss.append(train_l)  # 添加损失值到列表中
        with torch.no_grad():
            test_loss, test_epoch_count = 0, 0
            for data, labels in testdataloader:
                data, labels = data.to(device), labels.to(device)
                pred = MyModel(data)
                test_each_loss = criterion(pred, labels)
                test_loss += test_each_loss.item()
                test_epoch_count += (pred.argmax(dim=1) == labels).sum()
            test_all_loss.append(test_loss)
            test_ACC.append(test_epoch_count.cpu() / len(testdataset))
        if epoch == 0 or (epoch + 1) % 2 == 0:
            print('epoch: %d | train loss:%.5f | test loss:%.5f | train acc:%5f test acc:%.5f:' % (
                epoch + 1, train_all_loss[-1], test_all_loss[-1],
                train_ACC[-1], test_ACC[-1]))
    endtime = time.time()
    print("torch.nn实现前馈网络-多分类任务 %d轮 总用时: %.3fs" % (epochs, endtime - begintime))
    # 返回训练集和测试集上的 损失值 与 准确率
    return train_all_loss, test_all_loss, train_ACC, test_ACC

import random

# 得到0-60000的下标
index = list(range(len(traindataset)))
# 利用shuffle随机打乱下标
random.shuffle(index)
# 按照 训练集和验证集 8：2 的比例分配各自下标
train_index, val_index = index[: 48000], index[48000:]
# 由分配的下标得到对应的训练和验证及的数据以及他们对应的标签
train_dataset, train_labels = traindataset.data[train_index], traindataset.targets[train_index]
val_dataset, val_labels = traindataset.data[val_index], traindataset.targets[val_index]
print('训练集:', train_dataset.shape, train_labels.shape)
print('验证集:', val_dataset.shape, val_labels.shape)
# 构建相应的dataset以及dataloader
T_dataset = torch.utils.data.TensorDataset(train_dataset, train_labels)
V_dataset = torch.utils.data.TensorDataset(val_dataset, val_labels)
T_dataloader = torch.utils.data.DataLoader(dataset=T_dataset, batch_size=128, shuffle=True)
V_dataloader = torch.utils.data.DataLoader(dataset=V_dataset, batch_size=128, shuffle=True)
print('T_dataset', len(T_dataset), 'T_dataloader batch_size: 128')
print('V_dataset', len(V_dataset), 'V_dataloader batch_size: 128')


def train_and_test_4(model=model, epochs=30, lr=0.01, weight_decay=0.0):
    print(model)
    # 优化函数, 默认情况下weight_decay为0 通过更改weight_decay的值可以实现L2正则化。
    optimizer = torch.optim.Adam(model.parameters(), lr=0.01, betas=(0.9, 0.999), eps=1e-6)
    criterion = CrossEntropyLoss()  # 损失函数
    train_all_loss = []  # 记录训练集上得loss变化
    val_all_loss = []  # 记录测试集上的loss变化
    train_ACC, val_ACC = [], []
    begintime = time.time()
    flag_stop = 0
    for epoch in range(1000):
        train_l, train_epoch_count, val_epoch_count = 0, 0, 0
        for data, labels in traindataloader:
            data, labels = data.to(torch.float32).to(device), labels.to(device)
            pred = model(data)
            train_each_loss = criterion(pred, labels.view(-1))  # 计算每次的损失值
            optimizer.zero_grad()  # 梯度清零
            train_each_loss.backward()  # 反向传播
            optimizer.step()  # 梯度更新
            train_l += train_each_loss.item()
            train_epoch_count += (pred.argmax(dim=1) == labels).sum()
        train_ACC.append(train_epoch_count / len(traindataset))
        train_all_loss.append(train_l)  # 添加损失值到列表中
        with torch.no_grad():
            val_loss, val_epoch_count = 0, 0
            for data, labels in testdataloader:
                data, labels = data.to(torch.float32).to(device), labels.to(device)
                pred = model(data)
                val_each_loss = criterion(pred, labels)
                val_loss += val_each_loss.item()
                val_epoch_count += (pred.argmax(dim=1) == labels).sum()
            val_all_loss.append(val_loss)
            val_ACC.append(val_epoch_count / len(testdataset))
            # 实现早停机制
            # 若连续五次验证集的损失值连续增大，则停止运行，否则继续运行，
            if epoch > 5 and val_all_loss[-1] > val_all_loss[-2]:
                flag_stop += 1
                if flag_stop == 5 or epoch > 35:
                    print('停止运行，防止过拟合')
                    break
            else:
                flag_stop = 0
        if epoch == 0 or (epoch + 1) % 4 == 0:
            print('epoch: %d | train loss:%.5f | val loss:%.5f | train acc:%5f val acc:%.5f:' % (
            epoch + 1, train_all_loss[-1], val_all_loss[-1],
            train_ACC[-1], val_ACC[-1]))
    endtime = time.time()
    print("torch.nn实现前馈网络-多分类任务 %d轮 总用时: %.3fs" % (epochs, endtime - begintime))
    # 返回训练集和测试集上的 损失值 与 准确率
    return train_all_loss, val_all_loss, train_ACC, val_ACC


model_41 = MyNet_NN(dropout=0.5)
model_41 = model_41.to(device)
train_all_loss41, test_all_loss41, \
train_ACC41, test_ACC41 \
    = train_and_test_4(model=model_41, epochs=10000, lr=0.1)

#完成loss的显示
drop_name_6= ['','早停机制']
drop_train_6 = [train_all_loss41]
drop_test_6= [test_all_loss41]
picture(drop_name_6, drop_train_6,drop_test_6)
