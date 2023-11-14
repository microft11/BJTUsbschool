import torch
from torch import nn
import torchvision
import matplotlib.pyplot as plt
from IPython import display
from torch.utils import data
from torchvision import transforms


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


net = nn.Sequential(
    nn.Conv2d(1, 6, kernel_size=5, padding=2), nn.Sigmoid(),
    nn.AvgPool2d(kernel_size=2, stride=2),
    nn.Conv2d(6, 16, kernel_size=5), nn.Sigmoid(),
    nn.AvgPool1d(kernel_size=2, stride=2),
    nn.Flatten(),
    nn.Linear(16 * 5 * 5, 120), nn.Sigmoid(),
    nn.Linear(120, 84), nn.Sigmoid(),
    nn.Linear(84, 10)
)
batch_size = 256
train_iter, test_iter = load_data_fashion_mnist(batch_size)


def evaluate_accuracy_gpu(net, data_iter, device=None):
    """使用GPU计算模型在数据集上的精度"""
    if isinstance(net, nn.Module):
        net.eval()  # 设置为评估模式
        if not device:
            device = next(iter(net.parameters())).device
    # 正确预测的数量，总预测的数量
    num_correct = 0
    num_samples = 0

    with torch.no_grad():
        for X, y in data_iter:
            if isinstance(X, list):
                # BERT微调所需的（之后将介绍）
                X = [x.to(device) for x in X]
            else:
                X = X.to(device)
            y = y.to(device)

            outputs = net(X)
            _, predictions = torch.max(outputs, 1)
            num_correct += (predictions == y).sum().item()
            num_samples += y.numel()

    return num_correct / num_samples


def train_ch6(net, train_iter, test_iter, num_epochs, lr, device):
    """用GPU训练模型(在第六章定义)"""

    def init_weights(m):
        if type(m) == nn.Linear or type(m) == nn.Conv2d:
            nn.init.xavier_uniform_(m.weight)

    net.apply(init_weights)
    print('training on', device)
    net.to(device)
    optimizer = torch.optim.SGD(net.parameters(), lr=lr)
    loss = nn.CrossEntropyLoss()

    print(f'training on {device}')
    for epoch in range(num_epochs):
        # 训练损失之和，训练准确率之和，样本数
        total_loss, total_correct, total_samples = 0.0, 0.0, 0

        net.train()
        for X, y in train_iter:
            optimizer.zero_grad()
            X, y = X.to(device), y.to(device)
            y_hat = net(X)
            l = loss(y_hat, y)
            l.backward()
            optimizer.step()

            total_loss += l.item() * X.shape[0]
            total_correct += (y_hat.argmax(dim=1) == y).sum().item()
            total_samples += y.numel()

        train_loss = total_loss / total_samples
        train_acc = total_correct / total_samples

        test_acc = evaluate_accuracy_gpu(net, test_iter)

        print(f'Epoch [{epoch + 1}/{num_epochs}], '
              f'Loss: {train_loss:.4f}, '
              f'Train Acc: {train_acc:.4f}, '
              f'Test Acc: {test_acc:.4f}')


lr, num_epochs = 0.9, 10
train_ch6(net, train_iter, test_iter, num_epochs, lr, 'cpu')
