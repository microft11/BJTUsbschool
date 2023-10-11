import torch
import torchvision
from torch.utils import data
from torchvision import transforms

batch_size = 256


def load_data_fashion_mnist(batch_size, resize=None):  # @save
    """下载Fashion-MNIST数据集，然后将其加载到内存中"""
    trans = [transforms.ToTensor()]
    if resize:
        trans.insert(0, transforms.Resize(resize))
    trans = transforms.Compose(trans)
    mnist_train = torchvision.datasets.FashionMNIST(
        root="../data", train=True, transform=trans, download=True)
    mnist_test = torchvision.datasets.FashionMNIST(
        root="../data", train=False, transform=trans, download=True)
    return (data.DataLoader(mnist_train, batch_size, shuffle=True,
                            num_workers=4),
            data.DataLoader(mnist_test, batch_size, shuffle=False,
                            num_workers=4))


train_iter, test_iter = load_data_fashion_mnist(batch_size)

# 每个样本都是28X28的图像。 展平每个图像，把它们看作长度为784的向量
#  因为我们的数据集有10个类别，所以网络输出维度为10
num_inputs = 784
num_output = 10

W = torch.normal(0, 0.01, size=(num_inputs, num_output), requires_grad=True)
b = torch.zeros(num_output, requires_grad=True)


# 定义softmax 函数
def softmax(X):
    X_exp = torch.exp(X)
    partition = X_exp.sum(1, keepdim=True)
    return X_exp / partition  # 这里应用了广播机制


# 定义模型
def net(X):
    return softmax(torch.matmul(X.reshape((-1, W.shape[0])), W) + b)


# 定义损失函数
"""
y 是一个张量，表示真实的类别标签。在这个示例中，y 包含两个元素，即 [0, 2]。
这表示有两个样本，分别属于类别0和类别2。

y_hat 是一个张量，表示模型的预测概率分布。它是一个2x3的张量，其中每行对应一个样本，每列对应不同的类别。
例如，y_hat[0, :] 表示模型对第一个样本的类别概率分布，而 y_hat[1, :] 表示模型对第二个样本的类别概率分布。

y_hat[[0, 1], y] 是一个索引操作，它用于根据真实标签 y 从 y_hat 中选择相应的概率值。
具体来说，它会选择 y_hat 中的两个概率值，分别是 y_hat[0, 0] 和 y_hat[1, 2]。这是用于计算交叉熵损失的一部分。

cross_entropy 函数定义了一个计算交叉熵损失的方法。
它采用两个参数：y_hat 表示模型的概率预测，y 表示真实标签。在函数内部，它执行以下操作：

range(len(y_hat)) 用于生成一个整数范围，以便在 y_hat 的每一行上进行操作，即 [0, 1]。

y_hat[range(len(y_hat)), y] 用于选择 y_hat 中与真实标签 y 对应的概率值。这是计算交叉熵的关键部分。

-torch.log(...) 对选定的概率值取自然对数（logarithm），然后取负值。
这是交叉熵损失的数学公式之一，用于测量模型的预测与真实标签之间的差距。
"""
y = torch.tensor([0, 2])
y_hat = torch.tensor([[0.1, 0.3, 0.6], [0.3, 0.2, 0.5]])
y_hat[[0, 1], y]


def cross_entropy(y_hat, y):
    return - torch.log(y_hat[range(len(y_hat)), y])


cross_entropy(y_hat, y)


def accuracy(y_hat, y):  # @save
    """计算预测正确的数量"""
    """
    分类精度即正确预测数量与总预测数量之比。 
    虽然直接优化精度可能很困难（因为精度的计算不可导）， 
    但精度通常是我们最关心的性能衡量标准，我们在训练分类器时几乎总会关注它。

    为了计算精度，我们执行以下操作。 
    首先，如果y_hat是矩阵，那么假定第二个维度存储每个类的预测分数。 
    我们使用argmax获得每行中最大元素的索引来获得预测类别。 
    然后我们将预测类别与真实y元素进行比较。 
    由于等式运算符“==”对数据类型很敏感， 因此我们将y_hat的数据类型转换为与y的数据类型一致。 
    结果是一个包含0（错）和1（对）的张量。 
    最后，我们求和会得到正确预测的数量
    """
    if len(y_hat.shape) > 1 and y_hat.shape[1] > 1:
        y_hat = y_hat.argmax(axis=1)
    cmp = y_hat.type(y.dtype) == y
    return float(cmp.type(y.dtype).sum())


class Accumulator:
    """在n个变量上累加"""

    def __init__(self):
        self.data = None

    def __int__(self, n):
        self.data = [0.0] * n

    def add(self, *args):
        self.data = [a + float(b) for a, b in zip(self.data, args)]

    def reset(self):
        self.data = [0.0] * len(self.data)

    def __getitem__(self, idx):
        return self.data[idx]


def evaluate_accuracy(net, data_iter):
    """计算在指定数据集上模型的精度"""
    if isinstance(net, torch.nn.Module):
        net.eval()
    metric = Accumulator()
    with torch.no_grad:
        for X, y in data_iter:
            metric.add(accuracy(net(X), y), y.numel())
    return metric[0] / metric[1]


# 训练
def train_epoch_ch3(net, train_iter, loss, updater):
    if isinstance(net, torch.nn.Module):
        net.train()
    metric = Accumulator(3)
    for X, y in train_iter:
        y_hat = net(X)
        l = loss(y_hat, y)
        if isinstance(updater, torch.optim.Optimizer):
            updater.zero_grad()
            l.mean().backward()
            updater.step()
        else:
            l.sum().backward()
            updater(X.shape[0])
        metric.add(float(l.sum()), accuracy(y_hat, y), y.numel())

    return metric[0] / metric[2], metric[1] / metric[2]

