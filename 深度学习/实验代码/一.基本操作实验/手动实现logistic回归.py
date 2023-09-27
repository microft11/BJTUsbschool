import random
import torch
import numpy as np
import matplotlib.pyplot as plt


def synthetic_data(w, b, num_examples):
    X = torch.normal(0, 1, (num_examples, len(w)))
    y = torch.matmul(X, w) + b
    y += torch.normal(0, 0.01, y.shape)
    return X, y.reshape((-1, 1))


# 线性模型参数 [2, -3.4],b = 4.2
true_w = torch.tensor([2, -3.4])
true_b = 4.2

features, labels = synthetic_data(true_w, true_b, 1000)


def draw_img(features, labels):
    print('features:', features[0], '\nlabel:', labels[0])

    # Assuming you have 'features' and 'labels' as NumPy arrays
    plt.figure(figsize=(8, 6))  # Set the figure size

    # Create a scatter plot
    plt.scatter(features[:, 1], labels, s=1)  # 's' sets the marker size

    plt.xlabel('Feature 1')  # Set the x-axis label
    plt.ylabel('Labels')  # Set the y-axis label

    # Save the plot to a file (e.g., in PNG format)
    plt.savefig('save_img.png')

    # Display the plot (optional)
    plt.show()


#         生成大小为batch_size的小批量
def data_iter(batch_size, features, labels):
    num_examples = len(features)
    indices = list(range(num_examples))
    random.shuffle(indices)
    for i in range(0, num_examples - 1, batch_size):
        batch_indices = torch.tensor(
            indices[i: min(i + batch_size, num_examples)]
        )
        yield features[batch_indices], labels[batch_indices]


#         因为 PyTorch 允许你使用张量进行索引操作，它会返回包含相应索引的子集张量。
#         使用return会直接结束函数

# for X, y in data_iter(batch_size=10, features=features, labels=labels):
#     print(X, '\n', y)
#     break

w = torch.normal(0, 0.01, size=(2, 1), requires_grad=True)
b = torch.zeros(1, requires_grad=True)


def linreg(X, w, b):
    """
    线性回归模型
    """
    return torch.matmul(X, w) + b


def squared_loss(y_hat, y):
    """loss function"""
    return (y_hat - y.reshape(y.shape)) ** 2 / 2


def sgd(params, lr, batch_size):
    """小批量随机梯度"""
    with torch.no_grad():
        for param in params:
            param -= lr * param.grad / batch_size
            param.grad.zero_()


lr = 0.03
num_epochs = 3
net = linreg
loss = squared_loss

for epochs in range(num_epochs):
    for X, y in data_iter(batch_size=10, features=features, labels=labels):
        l = loss(net(X, w, b), y)
        l.sum().backward()
        sgd([w, b], lr, batch_size=10)
    with torch.no_grad():
        train_l = loss(net(features, w, b), labels)
        print(f'epoch{epochs + 1}, loss{float(train_l.mean())}')

predict = linreg
predicted_labels = predict(features, w, b)


def draw_img_with_line(features, labels, predicted_labels, w, b):
    # 转换模型参数为 NumPy 数组
    w_numpy = w.detach().numpy()
    b_numpy = b.detach().numpy()

    # 绘制数据点的散点图和模型的决策边界
    plt.figure(figsize=(8, 6))  # 设置图形大小
    plt.scatter(features[:, 1].detach().numpy(), predicted_labels.detach().numpy(), label='Model prediction',
                color='red', s=1)  # 绘制模型的预测点

    # # 计算并绘制模型的决策边界
    # x_values = np.linspace(features[:, 1].min().item(), features[:, 1].max().item(), 100)
    # y_values = (w_numpy[0] * x_values + b_numpy[0]).flatten()
    # plt.plot(x_values, y_values, label='Model decision boundary', color='green')
    # Create a scatter plot

    plt.xlabel('Feature 1')  # 设置 x 轴标签
    plt.ylabel('Predicted Labels')  # 设置 y 轴标签

    plt.legend()  # 显示图例
    plt.savefig("predict_img.png")
    plt.show()


draw_img_with_line(features, labels, predicted_labels, w, b)
draw_img(features, labels)