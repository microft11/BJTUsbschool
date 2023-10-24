import numpy as np
from sklearn.model_selection import train_test_split

# 设置随机种子以确保可重复性
np.random.seed(0)

# 生成特征矩阵 X，大小为 (10000, 500)
n_samples = 10000
n_features = 500
X = np.random.rand(n_samples, n_features)

# 生成噪声项 E，假设服从均值为0、标准差为1的正态分布
E = np.random.normal(0, 1, n_samples)

# 计算目标值 y，根据给定线性函数 y = 0.028 + 0.056 * X_i + E
# 其中，X_i 为特征矩阵 X 的第 i 列特征
y = 0.028 + 0.056 * X[:, 0] + E

# 划分数据集为训练集和测试集
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.3, random_state=42)

# 打印数据集维度
print("训练集 X 维度:", X_train.shape)
print("测试集 X 维度:", X_test.shape)

