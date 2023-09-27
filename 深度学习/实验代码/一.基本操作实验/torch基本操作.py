import torch
"""
使用 𝐓𝐞𝐧𝐬𝐨𝐫 初始化一个 𝟏×𝟑 的矩阵 𝑴 和一个 𝟐×𝟏 的矩阵 𝑵，
对两矩阵进行减法操作（要求实现三种不同的形式），
给出结果并分析三种方式的不同（如果出现报错，分析报错的原因），
同时需要指出在计算过程中发生了什么
"""

M = torch.Tensor([[1, 2, 3]])
N = torch.Tensor([[4],
                  [5]])

# 使用了广播机制
result1 = M - N
print(result1)

# 转置为同一维度
result2 = M - N.T
print(result2)

# 调整张量N的形状以匹配张量M
N_adjusted = N.expand_as(M)
# 执行逐元素减法
result3 = M - N_adjusted
# 结果张量
print(result3)


"""
① 利用 𝐓𝐞𝐧𝐬𝐨𝐫 创建两个大小分别 𝟑×𝟐 和 𝟒×𝟐 的随机数矩阵 𝑷 和 𝑸 ，
   要求服从均值为0，标准差0.01为的正态分布；
② 对第二步得到的矩阵 𝑸 进行形状变换得到 𝑸 的转置 𝑸^𝑻 ；
③ 对上述得到的矩阵 𝑷 和矩阵 𝑸^𝑻 求矩阵相乘

"""
# 1: 创建随机数矩阵 P 和 Q
mean = 0
std_dev = 0.01
P = torch.normal(mean, std_dev, size=(3, 2))
Q = torch.normal(mean, std_dev, size=(4, 2))

# 2: 对矩阵 Q 进行形状变换得到 Q^T
Qt = Q.t()  # 或者可以使用 Qt = Q.transpose(0, 1)

# 3: 计算矩阵相乘
result = torch.mm(P, Qt)

print("矩阵 P:")
print(P)

print("\n矩阵 Q^T:")
print(Qt)

print("\n矩阵相乘结果:")
print(result)

"""
给定公式 𝑦_3=𝑦_1+𝑦_2=𝑥^2+𝑥^3，且 𝑥=1。
利用学习所得到的Tensor的相关知识，求𝑦_3对𝑥的梯度，即(𝑑𝑦_3)/𝑑𝑥
要求在计算过程中，在计算〖 𝑥〗^3 时中断梯度的追踪，
观察结果并进行原因分析提示, 可使用 with torch.no_grad()， 
"""

# 定义x作为一个需要计算梯度的张量
x = torch.tensor(1.0, requires_grad=True)
# 计算y1 = x^2，这里会追踪梯度
y1 = x**2
# 使用torch.no_grad()中断对x^3的梯度追踪
with torch.no_grad():
    y2 = x**3

# 计算y3 = y1 + y2，这里会追踪梯度
y3 = y1 + y2
# 计算y3对x的梯度，这里只有y1的梯度会被计算，因为y2的梯度追踪被中断了
y3.backward()
print("dy3/dx (梯度):", x.grad)
