import cv2
import numpy as np
import matplotlib.pyplot as plt


def ava_custom(img, kernel_size):
    len_half = kernel_size // 2
    M, N = img.shape
    a = np.ones((kernel_size, kernel_size))  # a即n×n模板，元素全是1

    # 对原始图像进行边界复制
    img_pad = cv2.copyMakeBorder(img, len_half, len_half, len_half, len_half, cv2.BORDER_REFLECT)

    new_img = np.zeros_like(img)

    for i in range(len_half, M + len_half):
        for j in range(len_half, N + len_half):
            # 取出以(i, j)为中心的n×n区域与模板相乘
            c = img_pad[i - len_half:i + len_half + 1, j - len_half:j + len_half + 1] * a
            s = np.sum(c)  # 求c矩阵中各元素之和
            new_img[i - len_half, j - len_half] = s / (kernel_size * kernel_size)  # 将与模板运算后的各元素的均值赋给模板中心位置

    return new_img


def ava(n):
    # 读入BMP图像
    imNew = cv2.imread('noise.bmp', cv2.IMREAD_GRAYSCALE)
    imNew = imNew.astype(float) / 255.0  # 归一化到 [0, 1] 范围

    # 均值滤波
    avg_filtered = ava_custom(imNew, n)

    # 显示原图像和均值滤波后的图像
    plt.figure(figsize=(8, 4))

    plt.subplot(1, 2, 1)
    plt.imshow(imNew, cmap='gray')
    plt.title('原始图像')

    plt.subplot(1, 2, 2)
    plt.imshow(avg_filtered, cmap='gray')
    plt.title(f'均值滤波处理 {n}x{n} 图像')

    plt.show()


# 调用函数
ava(3)  # 将参数设置为你需要的模板大小
