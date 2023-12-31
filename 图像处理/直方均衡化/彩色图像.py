import cv2
import numpy as np
import matplotlib.pyplot as plt

# 读入BMP图像
pic = cv2.imread('color.bmp', cv2.IMREAD_UNCHANGED)

# 显示原始图像
plt.imshow(cv2.cvtColor(pic, cv2.COLOR_BGR2RGB))
plt.title('原始图像')
plt.show()

# 提取各通道分量
r = pic[:, :, 2]
g = pic[:, :, 1]
b = pic[:, :, 0]

# 转换为双精度浮点型
pic_double = pic.astype(float)

# 执行颜色空间转换
angle = np.arccos(0.5 * ((r - g) + (r - b)) / np.sqrt((r - g)**2 + (r - b) * (g - b)))
H = np.where(b >= g, 2 * np.pi - angle, angle) / (2 * np.pi)
S = 1 - 3 * np.minimum.reduce([r, g, b]) / (r + g + b)
H[S == 0] = 0
I = (r + g + b) / 3

# 原始图像的直方图
hist, bins = np.histogram(I.flatten(), 256, [0, 256])
prob = hist / (I.shape[0] * I.shape[1])
plt.bar(np.arange(256), prob, color='b')
plt.title('原始图像直方图')
plt.xlabel('亮度值')
plt.ylabel('出现概率')
plt.show()

# 直方图均衡化
S2 = np.cumsum(prob) * 255 + 0.5
S2 = S2.astype(np.uint8)
Inew = S2[I]

# 均衡化后图像的直方图
hist_eq, _ = np.histogram(Inew.flatten(), 256, [0, 256])
prob_eq = hist_eq / (Inew.shape[0] * Inew.shape[1])
plt.bar(np.arange(256), prob_eq, color='b')
plt.title('均衡化后的直方图')
plt.xlabel('亮度值')
plt.ylabel('出现概率')
plt.show()

# 亮度级变换曲线
plt.plot(np.arange(256), S2, 'r')
plt.xlabel('均值化前')
plt.ylabel('均值化后')
plt.grid(True)
plt.legend(['亮度级变换曲线'])
plt.show()

# 转换为RGB格式
H = H * 2 * np.pi
I = I.astype(np.double)
S = S.astype(np.double)
H = H.astype(np.double)

# 颜色转换
R, G, B = np.zeros_like(H), np.zeros_like(H), np.zeros_like(H)
for i in range(H.shape[0]):
    for j in range(H.shape[1]):
        if 0 <= H[i, j] < 2 * np.pi / 3:
            B[i, j] = I[i, j] * (1 - S[i, j])
            R[i, j] = I[i, j] * (1 + S[i, j] * np.cos(H[i, j]) / np.cos(np.pi / 3 - H[i, j]))
            G[i, j] = 3 * I[i, j] - (R[i, j] + B[i, j])
        elif 2 * np.pi / 3 <= H[i, j] < 4 * np.pi / 3:
            H[i, j] = H[i, j] - 2 * np.pi / 3
            R[i, j] = I[i, j] * (1 - S[i, j])
            G[i, j] = I[i, j] * (1 + S[i, j] * np.cos(H[i, j] - 2 * np.pi / 3) / np.cos(np.pi - H[i, j]))
            B[i, j] = 3 * I[i, j] - (R[i, j] + G[i, j])
        elif 4 * np.pi / 3 <= H[i, j] < 2 * np.pi:
            H[i, j] = H[i, j] - 4 * np.pi / 3
            G[i, j] = I[i, j] * (1 - S[i, j])
            B[i, j] = I[i, j] * (1 + S[i, j] * np.cos(H[i, j] - 4 * np.pi / 3) / np.cos(5 * np.pi / 3 - H[i, j]))
            R[i, j] = 3 * I[i, j] - (G[i, j] + B[i, j])

output3 = np.stack((B, G, R), axis=-1)
output3 = output3.astype(np.uint8)

# 显示处理后的图像
plt.imshow(output3)
plt.show()
