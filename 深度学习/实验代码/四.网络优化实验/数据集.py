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
