import torch
import torch.nn as nn
import torch.nn.functional as F


# 这是一个快，一个多层感知机
class MLP(nn.Module):
    def __init__(self):
        super(MLP, self).__init__()  # 修改这一行，使用super().__init__()

        self.hidden = nn.Linear(20, 256)
        self.output = nn.Linear(256, 10)

    def forward(self, X):
        return self.output(F.relu(self.hidden(X)))


# 创建MLP实例
net = MLP()
X = torch.rand(1, 20)
output = net(X)
print(output)


# 顺序快
class MySequential(nn.Module):
    def __init__(self, *args):
        super().__init__()
        for idx, model in enumerate(args):
            self._modules[str(idx)] = model

    def forward(self, X):
        for block in self._modules.values():
            X = block(X)
        return X


net = MySequential(nn.Linear(20, 256), nn.ReLU(), nn.Linear(256, 10))
output = net(X)
print(output)


# print(net[2].state_dict())

def block1():
    return nn.Sequential(nn.Linear(4, 8), nn.ReLU(),
                         nn.Linear(8, 1), nn.ReLU())  # 修改这一行


def block2():
    net = nn.Sequential()
    for i in range(4):
        net.add_module(f'block {i}', block1())
    return net


X = torch.rand(1, 4)
rgnet = nn.Sequential(block2(), nn.Linear(4, 1))
output = rgnet(X)
print(output)
