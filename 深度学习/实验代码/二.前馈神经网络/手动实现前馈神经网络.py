import torch
import torch.nn as nn
import numpy as np
import torchvision
from torchvision import transforms
import matplotlib.pyplot as plt


def draw_loss(train_loss, test_loss):
    x = np.linspace(0, len(train_loss), len(train_loss))
    plt.plot(x, train_loss, label="Train loss", linewidth=1.5)
    plt.plot(x, test_loss, label="test loss", linewidth=1.5)
    plt.xlabel("Epoch")
    plt.ylabel("Loss")
    plt.legend()
    plt.show()


def evaluate_accuracy(data_iter, model, loss_func):
    acc_sum, test_l_sum, n, c = 0.0, 0.0, 0.0, 0.0
    for X, y in data_iter:
        result = model.forward(X)
        acc_sum += (result.argmax(dim=1) == y).float().sum().item()
        test_l_sum += loss_func(result, y).item()
        n += y.shape[0]
        c += 1
    return acc_sum / n, test_l_sum / c


batch_size = 256
# 下载Fashion-MINIST 数据
mnist_train = torchvision.datasets.FashionMNIST(root='../Datasets/FashionMNIST', train=True,
                                                download=True, transform=transforms.ToTensor())
mnist_test = torchvision.datasets.FashionMNIST(root='../Datasets/FashionMNIST', train=False,
                                               download=True, transform=transforms.ToTensor())
# 读取数据
train_iter = torch.utils.data.DataLoader(mnist_train, batch_size=batch_size, shuffle=True,
                                         num_workers=0)
test_iter = torch.utils.data.DataLoader(mnist_test, batch_size=batch_size, shuffle=False,
                                        num_workers=0)


class Net:
    def __init__(self):
        num_input, num_output, num_hiddens = 784, 10, 256
        W1 = torch.tensor(np.random.normal(0, 0.01, (num_hiddens, num_input)), dtype=torch.float)
        b1 = torch.zeros(num_hiddens, dtype=torch.float)
        W2 = torch.tensor(np.random.normal(0, 0.01, (num_output, num_hiddens)), dtype=torch.float)
        b2 = torch.zeros(num_output, dtype=torch.float)
        self.params = [W1, b1, W2, b2]
        for param in self.params:
            param.requires_grad = True

        self.input_layer = lambda x: x.view(x.shape[0], -1)
        self.hiddens_layer = lambda x: self.my_ReLU(torch.matmul(x, W1.t()) + b1)
        self.output_layer = lambda x: torch.matmul(x, W2.t()) + b2

    @staticmethod
    def my_ReLU(x):
        return torch.max(input=x, other=torch.tensor(0.0))

    def forward(self, x):
        flatten_input = self.input_layer(x)
        hidden_output = self.hiddens_layer(flatten_input)
        final_output = self.output_layer(hidden_output)
        return final_output


def my_cross_entropy_loss(y_hat, labels):
    def log_softmax(y_hat):
        max_v, _ = torch.max(y_hat, dim=1)
        return y_hat - max_v.view(-1, 1) - torch.log(torch.sum(torch.exp(y_hat - max_v.view(-1, 1)), dim=1)).view(-1, 1)

    log_probs = log_softmax(y_hat)
    index = torch.arange(0, len(y_hat))

    return -log_probs[index, labels].mean()


def SGD(params, lr):
    for param in params:
        param.data -= lr * param.grad


def train(net, train_iter, loss_func, num_epochs, lr=None, optimizer=None):
    train_loss_list = []
    test_loss_list = []
    for epoch in range(num_epochs):
        train_l_sum, train_acc_sum, n, c = 0.0, 0.0, 0, 0
        for X, y in train_iter:
            y_hat = net.forward(X)
            l = loss_func(y_hat, y)
            l.backward()
            optimizer(net.params, lr)
            for param in net.params:
                param.grad.data.zero_()
            train_l_sum += l.item()
            train_acc_sum += (y_hat.argmax(dim=1) == y).sum().item()
            n += y.shape[0]
            c += 1
        test_acc, test_loss = evaluate_accuracy(test_iter, net, loss_func)
        train_loss_list.append(train_l_sum / c)
        test_loss_list.append(test_loss)
        print('epoch %d train loss %.4f, test loss %.4f, train acc %.3f, test acc %.3f'
              % (epoch + 1, train_l_sum / c, test_loss, train_acc_sum / n, test_acc))
    return train_loss_list, test_loss_list


net = Net()
num_epoch = 20
lr = 0.01
optimizer = SGD

loss = my_cross_entropy_loss

train_loss, test_loss = train(net, train_iter, loss, num_epoch, lr, optimizer)

draw_loss(train_loss, test_loss)