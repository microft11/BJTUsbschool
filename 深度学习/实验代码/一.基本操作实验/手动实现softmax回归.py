import torch
import numpy as np
import torchvision
import torchvision.transforms as transforms
import matplotlib.pyplot as plt

# 下载Fashion-MINIST 数据
mnist_train = torchvision.datasets.FashionMNIST(root='./Datasets/FashionMNIST', train=True,
                                                download=True, transform=transforms.ToTensor())
mnist_test = torchvision.datasets.FashionMNIST(root='./Datasets/FashionMNIST', train=False,
                                               download=True, transform=transforms.ToTensor())

# 读取数据
batch_size = 256
train_iter = torch.utils.data.DataLoader(mnist_train, batch_size=batch_size, shuffle=True,
                                         num_workers=0)
test_iter = torch.utils.data.DataLoader(mnist_test, batch_size=batch_size, shuffle=False,
                                        num_workers=0)

# 输入与输出
num_inputs = 784
num_outputs = 10

W = torch.tensor(np.random.normal(0, 0.01, (num_inputs, num_outputs)), dtype=torch.float)
b = torch.zeros(num_outputs, dtype=torch.float)

# 开启梯度track
W.requires_grad_(requires_grad=True)
b.requires_grad_(requires_grad=True)


# 定义softmax函数
def softmax(X):
    X_exp = X.exp()
    partition = X_exp.sum(dim=1, keepdim=True)
    return X_exp / partition


# 手动实现定义模型
def net(X):
    f_x = torch.mm(X.view((-1, num_inputs)), W) + b
    return softmax(f_x)


# 手动实现交叉熵损失函数
def cross_entropy(y_hat, y):
    return -torch.log(y_hat.gather(1, y.view(-1, 1)))


# 优化函数
def sgd(params, lr, batch_size):
    for param in params:
        param.data -= lr * param.grad / batch_size


def evaluate_accuracy(data_iter, net):
    acc_sum, n = 0.0, 0
    for X, y in data_iter:
        acc_sum += (net(X).argmax(dim=1) == y).float().sum().item()
        n += y.shape[0]
    return acc_sum / n


# 训练函数，包括绘制损失曲线
def train(net, train_iter, test_iter, loss, num_epochs, batch_size, params=None, lr=None, optimizer=None):
    train_losses = []
    test_losses = []

    for epoch in range(num_epochs):
        train_l_num, train_acc_num, n = 0.0, 0.0, 0
        for X, y in train_iter:
            y_hat = net(X)
            l = loss(y_hat, y).sum()
            l.backward()
            sgd(params, lr, batch_size)
            W.grad.data.zero_()
            b.grad.data.zero_()
            train_l_num += l.item()
            train_acc_num += (y_hat.argmax(dim=1) == y).sum().item()
            n += y.shape[0]

        test_acc = evaluate_accuracy(test_iter, net)
        test_loss = sum(loss(net(X), y).sum() for X, y in test_iter)
        test_losses.append(test_loss.item())
        train_losses.append(train_l_num / n)
        print('epoch %d, loss %.4f, train_acc %.3f, test_acc %.3f' % (
        epoch + 1, train_l_num / n, train_acc_num / n, test_acc))

    # Plot the loss curve
    plt.plot(range(1, num_epochs + 1), train_losses, label='Training Loss')
    plt.plot(range(1, num_epochs + 1), test_losses, label='Test Loss')
    plt.xlabel('Epochs')
    plt.ylabel('Loss')
    plt.legend()
    plt.show()


num_epochs, lr = 10, 0.1
train(net, train_iter, test_iter, cross_entropy, num_epochs, batch_size, [W, b], lr)
