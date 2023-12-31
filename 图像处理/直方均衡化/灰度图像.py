import numpy as np
import cv2
import matplotlib.pyplot as plt

# 读入BMP图像并转换为灰度图像
pic = cv2.imread('grey.bmp', cv2.IMREAD_GRAYSCALE)

# 显示原始灰度图像
plt.imshow(pic, cmap='gray')
plt.title('原始灰度图像')
plt.show()

# 绘制直方图
hist, bins = np.histogram(pic.flatten(), 256, [0, 256])
prob = hist / (pic.shape[0] * pic.shape[1])

plt.bar(np.arange(256), prob, color='b')
plt.title('原始图像直方图')
plt.xlabel('像素强度')
plt.ylabel('概率')
plt.show()

# 直方图均衡化
cumulative_distribution = np.cumsum(prob) * 255
equalized_image = cumulative_distribution[pic]

# 绘制均衡化后的直方图
hist_eq, _ = np.histogram(equalized_image.flatten(), 256, [0, 256])
prob_eq = hist_eq / (pic.shape[0] * pic.shape[1])

plt.bar(np.arange(256), prob_eq, color='b')
plt.title('均衡化后的直方图')
plt.xlabel('像素强度')
plt.ylabel('概率')
plt.show()

# 显示均衡化后的图像
plt.imshow(equalized_image, cmap='gray')
plt.title('均衡化后的图像')
plt.show()

# 绘制灰度级变换曲线
plt.plot(np.arange(256), cumulative_distribution, 'r')
plt.xlabel('原始强度')
plt.ylabel('变换后强度')
plt.grid(True)
plt.legend(['强度变换曲线'])
plt.show()

