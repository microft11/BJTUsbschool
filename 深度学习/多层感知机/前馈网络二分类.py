# 二分类
import numpy as np
from sklearn.model_selection import train_test_split
import matplotlib.pyplot as plt

# 设置随机种子以确保可重复性
np.random.seed(0)

# 创建数据集A
n_samples_A = 10000
n_features = 200
mean_A = np.random.rand(n_features)  # 特征均值为随机值
mean_B = -mean_A  # 特征均值为相反数
std_dev = 1.0  # 方差相同

# 生成特征矩阵X_A和X_B，分别服从正态分布
X_A = np.random.normal(mean_A, std_dev, size=(n_samples_A, n_features))
X_B = np.random.normal(mean_B, std_dev, size=(n_samples_A, n_features))

# 为数据集A和B生成相应的标签
y_A = np.zeros(n_samples_A, dtype=int)  # 数据集A的标签为0
y_B = np.ones(n_samples_A, dtype=int)  # 数据集B的标签为1

# 合并数据集并划分为训练集和测试集
X = np.vstack((X_A, X_B))
y = np.hstack((y_A, y_B))
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.3, random_state=42)

print("合并后的训练集 X 维度:", X_train.shape)
print("合并后的测试集 X 维度:", X_test.shape)


# 创建神经网络模型
class NeuralNetwork:
    def __init__(self, input_size, hidden_size, output_size, learning_rate):
        self.input_size = input_size
        self.hidden_size = hidden_size
        self.output_size = output_size
        self.learning_rate = learning_rate

        self.W1 = np.random.randn(self.input_size, self.hidden_size)
        self.b1 = np.zeros((1, self.hidden_size))
        self.W2 = np.random.randn(self.hidden_size, self.output_size)
        self.b2 = np.zeros((1, self.output_size))

        self.loss_list = []  # 用于保存每次训练后的损失

    def sigmoid(self, x):
        return 1 / (1 + np.exp(-x))

    def sigmoid_derivative(self, x):
        return x * (1 - x)

    def forward(self, x):
        self.z1 = np.dot(x, self.W1) + self.b1
        self.a1 = self.sigmoid(self.z1)
        self.z2 = np.dot(self.a1, self.W2) + self.b2
        self.a2 = self.sigmoid(self.z2)
        return self.a2

    def backward(self, x, y, output):
        self.error = y - output
        self.d_output = self.error * self.sigmoid_derivative(output)
        self.error_hidden = self.d_output.dot(self.W2.T)
        self.d_hidden = self.error_hidden * self.sigmoid_derivative(self.a1)
        self.W1 += x.reshape(-1, 1).dot(self.d_hidden) * self.learning_rate
        self.b1 += np.sum(self.d_hidden, axis=0, keepdims=True) * self.learning_rate
        self.W2 += self.a1.T.dot(self.d_output) * self.learning_rate
        self.b2 += np.sum(self.d_output, axis=0, keepdims=True) * self.learning_rate

    def train(self, x, y):
        output = self.forward(x)
        self.backward(x, y, output)
        loss = np.mean(np.square(y - output))  # 均方误差损失
        self.loss_list.append(loss)

    def predict(self, x):
        output = self.forward(x)
        return np.round(output)

# 设置超参数
input_size = 200
hidden_size = 256
output_size = 1
learning_rate = 0.01

# 初始化神经网络
model = NeuralNetwork(input_size, hidden_size, output_size, learning_rate)

# 训练模型
num_epochs = 10
for epoch in range(num_epochs):
    for i in range(len(X_train)):
        x = X_train[i]
        y = y_train[i]
        model.train(x, y)
    print(f'Epoch {epoch + 1}, Loss: {model.loss_list[-1]}')

# 测试模型
correct = 0
total = len(X_test)
for i in range(total):
    x = X_test[i]
    y = y_test[i]
    prediction = model.predict(x)
    if prediction == y:
        correct += 1

accuracy = correct / total
print("Accuracy:", accuracy)

# 绘制损失曲线
plt.plot(model.loss_list)
plt.xlabel('Epoch')
plt.ylabel('Loss')
plt.title('Training Loss')
plt.show()