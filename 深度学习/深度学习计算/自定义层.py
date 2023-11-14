import torch
import torch.nn as nn
from torch.nn import functional as F


# 不带参数的层
class CenteredLayer(nn.Module):
    def __init__(self):
        super().__init__()

    def forward(self, X):
        return X - X.mean()


# 我们可以将层作为组件合并到更复杂的模型中。
net = nn.Sequential(nn.Linear(8, 128), CenteredLayer())
Y = net(torch.rand(4, 8))
print(Y.mean())


# 定义具有参数的层， 这些参数可以通过训练进行调整。
# 我们可以使用内置函数来创建参数，这些函数提供一些基本的管理功能。 比如管理访问、初始化、共享、保存和加载模型参数
class MyLinear(nn.Module):
    def __init__(self, in_units, units):
        super().__init__()
        self.weight = nn.Parameter(torch.randn(in_units, units))  # nn.Parameter 是 torch.Tensor 的子类，表示一个可训练的参数
        self.bias = nn.Parameter(torch.randn(units, ))  # randn 用于生成具有标准正态分布（均值为 0，标准差为 1）的随机数的张量

    def forward(self, X):
        linear = torch.matmul(X, self.weight.data) + self.bias.data
        return F.relu(linear)
