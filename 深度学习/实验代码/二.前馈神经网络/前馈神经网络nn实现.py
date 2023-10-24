import torch
import torch.nn as nn
import torch.optim as optim
import torchvision
from torchvision import transforms
from torch.utils.data import DataLoader
import matplotlib.pyplot as plt


def draw_loss(train_loss, test_loss):
    x = range(len(train_loss))
    plt.plot(x, train_loss, label="Train loss", linewidth=1.5)
    plt.plot(x, test_loss, label="Test loss", linewidth=1.5)
    plt.xlabel("Epoch")
    plt.ylabel("Loss")
    plt.legend()
    plt.show()


# Define the neural network using nn.Module
class Net(nn.Module):
    def __init__(self):
        super(Net, self).__init()
        num_input, num_output, num_hiddens = 784, 10, 256
        self.fc1 = nn.Linear(num_input, num_hiddens)
        self.relu = nn.ReLU()
        self.fc2 = nn.Linear(num_hiddens, num_output)

    def forward(self, x):
        x = x.view(x.size(0), -1)
        x = self.fc1(x)
        x = self.relu(x)
        x = self.fc2(x)
        return x


def train(net, train_loader, test_loader, loss_func, optimizer, num_epochs):
    train_loss_list = []
    test_loss_list = []

    for epoch in range(num_epochs):
        net.train()
        train_l_sum, train_acc_sum, n, c = 0.0, 0.0, 0, 0
        for X, y in train_loader:
            y_hat = net(X)
            l = loss_func(y_hat, y)
            optimizer.zero_grad()
            l.backward()
            optimizer.step()
            train_l_sum += l.item()
            train_acc_sum += (y_hat.argmax(dim=1) == y).sum().item()
            n += y.shape[0]
            c += 1
        test_loss, test_acc = evaluate_accuracy(net, test_loader, loss_func)
        train_loss_list.append(train_l_sum / c)
        test_loss_list.append(test_loss)
        print(
            f'Epoch {epoch + 1}, Train loss: {train_l_sum / c:.4f}, Test loss: {test_loss:.4f}, Train acc: {train_acc_sum / n:.3f}, Test acc: {test_acc:.3f}')

    return train_loss_list, test_loss_list


def evaluate_accuracy(model, data_loader, loss_func):
    model.eval()
    acc_sum, test_l_sum, n, c = 0.0, 0.0, 0, 0
    with torch.no_grad():
        for X, y in data_loader:
            y_hat = model(X)
            acc_sum += (y_hat.argmax(dim=1) == y).float().sum().item()
            test_l_sum += loss_func(y_hat, y).item()
            n += y.shape[0]
            c += 1
    return test_l_sum / c, acc_sum / n


# Hyperparameters
batch_size = 256
num_epochs = 20
lr = 0.01

# Load the Fashion-MNIST dataset
mnist_train = torchvision.datasets.FashionMNIST(root='./datasets/FashionMNIST', train=True,
                                                download=True, transform=transforms.ToTensor())
mnist_test = torchvision.datasets.FashionMNIST(root='./datasets/FashionMNIST', train=False,
                                               download=True, transform=transforms.ToTensor())

train_loader = DataLoader(mnist_train, batch_size=batch_size, shuffle=True)
test_loader = DataLoader(mnist_test, batch_size=batch_size, shuffle=False)

# Create the model
net = Net()

# Define the loss function and optimizer
loss_func = nn.CrossEntropyLoss()
optimizer = optim.SGD(net.parameters(), lr=lr)

# Train the model
train_loss, test_loss = train(net, train_loader, test_loader, loss_func, optimizer, num_epochs)

# Plot the loss curves
draw_loss(train_loss, test_loss)
