import numpy as np
from sklearn.model_selection import train_test_split

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

# 划分数据集为训练集和测试集
X_train_A, X_test_A, y_train_A, y_test_A = train_test_split(X_A, y_A, test_size=0.3, random_state=42)
X_train_B, X_test_B, y_train_B, y_test_B = train_test_split(X_B, y_B, test_size=0.3, random_state=42)

# 打印数据集维度
print("数据集A训练集 X 维度:", X_train_A.shape)
print("数据集A测试集 X 维度:", X_test_A.shape)
print("数据集B训练集 X 维度:", X_train_B.shape)
print("数据集B测试集 X 维度:", X_test_B.shape)
