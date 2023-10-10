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
