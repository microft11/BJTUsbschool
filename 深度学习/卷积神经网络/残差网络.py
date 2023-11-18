import torch
import torch.nn as nn
import torch.optim as optim
import torchvision
from torchvision import transforms, datasets
import time
import matplotlib.pyplot as plt
import numpy as np


# Define a basic residual block
class ResidualBlock(nn.Module):
    def __init__(self, in_channels, out_channels, stride=1):
        super(ResidualBlock, self).__init__()

        self.conv1 = nn.Conv2d(in_channels, out_channels, kernel_size=3, stride=stride, padding=1, bias=False)
        self.bn1 = nn.BatchNorm2d(out_channels)
        self.relu = nn.ReLU(inplace=True)
        self.conv2 = nn.Conv2d(out_channels, out_channels, kernel_size=3, stride=1, padding=1, bias=False)
        self.bn2 = nn.BatchNorm2d(out_channels)

        # If the number of input channels does not match the number of output channels,
        # use a 1x1 convolution to adjust the dimensions
        self.shortcut = nn.Sequential()
        if stride != 1 or in_channels != out_channels:
            self.shortcut = nn.Sequential(
                nn.Conv2d(in_channels, out_channels, kernel_size=1, stride=stride, bias=False),
                nn.BatchNorm2d(out_channels)
            )

    def forward(self, x):
        residual = x

        out = self.conv1(x)
        out = self.bn1(out)
        out = self.relu(out)

        out = self.conv2(out)
        out = self.bn2(out)

        out += self.shortcut(residual)  # Add the shortcut connection
        out = self.relu(out)

        return out


# Define the ResNet model
class ResNet(nn.Module):
    def __init__(self, num_classes=10):
        super(ResNet, self).__init__()

        self.conv1 = nn.Conv2d(3, 32, kernel_size=3, stride=1, padding=1, bias=False)
        self.bn1 = nn.BatchNorm2d(32)
        self.relu = nn.ReLU(inplace=True)

        # Stack of residual blocks
        self.layer1 = self.make_layer(32, 32, blocks=2, stride=1)
        self.layer2 = self.make_layer(32, 64, blocks=2, stride=2)
        self.layer3 = self.make_layer(64, 128, blocks=2, stride=2)

        self.avg_pool = nn.AdaptiveAvgPool2d((1, 1))
        self.fc = nn.Linear(128, num_classes)

    def make_layer(self, in_channels, out_channels, blocks, stride):
        layers = []
        layers.append(ResidualBlock(in_channels, out_channels, stride))
        for _ in range(1, blocks):
            layers.append(ResidualBlock(out_channels, out_channels, stride=1))
        return nn.Sequential(*layers)

    def forward(self, x):
        x = self.conv1(x)
        x = self.bn1(x)
        x = self.relu(x)

        x = self.layer1(x)
        x = self.layer2(x)
        x = self.layer3(x)

        x = self.avg_pool(x)
        x = x.view(x.size(0), -1)
        x = self.fc(x)

        return x


def train_epoch(net, data_loader, criterion, optimizer, device):
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


def test_epoch(net, data_loader, criterion, device):
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


# Hyperparameters
num_classes = 10
epochs = 5
lr = 0.001
batch_size = 512
device = torch.device("cuda:0" if torch.cuda.is_available() else "cpu")

# Load CIFAR-10 dataset
transform = transforms.Compose([
    transforms.ToTensor(),
    transforms.Normalize((0.5, 0.5, 0.5), (0.5, 0.5, 0.5))
])
cifar_train = datasets.CIFAR10(root='./data', train=True, download=True, transform=transform)
cifar_test = datasets.CIFAR10(root='./data', train=False, download=True, transform=transform)

# Create data loaders
train_loader = torch.utils.data.DataLoader(cifar_train, batch_size=batch_size, shuffle=True, num_workers=0)
test_loader = torch.utils.data.DataLoader(cifar_test, batch_size=batch_size, shuffle=False, num_workers=0)

# Initialize the ResNet model, criterion, and optimizer
resnet = ResNet(num_classes=num_classes).to(device)
criterion = nn.CrossEntropyLoss()
optimizer = optim.Adam(resnet.parameters(), lr=lr)

# Lists to store metrics for visualization
train_loss_list = []
train_acc_list = []
test_loss_list = []
test_acc_list = []
time_list = []

# Training and evaluation loop
for epoch in range(epochs):
    start_time = time.time()

    # Training
    train_loss, train_acc = train_epoch(resnet, train_loader, criterion, optimizer, device)
    train_loss_list.append(train_loss)
    train_acc_list.append(train_acc)

    # Testing
    test_loss, test_acc = test_epoch(resnet, test_loader, criterion, device)
    test_loss_list.append(test_loss)
    test_acc_list.append(test_acc)

    elapsed_time = time.time() - start_time
    time_list.append(elapsed_time)

    print(f'Epoch {epoch + 1}/{epochs}, Train Loss: {train_loss:.6f}, Test Loss: {test_loss:.6f}, '
          f'Train Acc: {train_acc:.6f}, Test Acc: {test_acc:.6f}, Time used: {elapsed_time:.2f}s')


# Plotting curves
def Draw_Curve(*args, xlabel="epoch", ylabel="loss"):
    for i in args:
        x = np.linspace(0, len(i[0]), len(i[0]))
        plt.plot(x, i[0], label=i[1], linewidth=1.5)
    plt.xlabel(xlabel)
    plt.ylabel(ylabel)
    plt.legend()
    plt.show()


Draw_Curve([train_acc_list, "train_acc"], [test_acc_list, "test_acc"], ylabel="acc")
Draw_Curve([train_loss_list, "train_loss"], [test_loss_list, "test_loss"])