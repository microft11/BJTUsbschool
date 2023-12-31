import cv2
import numpy as np
import matplotlib.pyplot as plt


def medfilt2_custom(img, kernel_size):
    len_half = kernel_size // 2
    M, N = img.shape
    new_img = np.zeros_like(img)

    for i in range(len_half, M - len_half):
        for j in range(len_half, N - len_half):
            # 取出以(i, j)为中心的n×n区域，将其展开为一维数组并进行中值滤波
            region = img[i - len_half:i + len_half + 1, j - len_half:j + len_half + 1]
            new_img[i, j] = np.median(region)

    return new_img


def med(n):
    # 读入BMP图像
    imNew = cv2.imread('noise.bmp', cv2.IMREAD_GRAYSCALE)
    imNew = imNew.astype(float) / 255.0  # 归一化到 [0, 1] 范围

    # 中值滤波
    med_filtered = medfilt2_custom(imNew, n)

    # 显示原图像和中值滤波后的图像
    plt.figure(figsize=(8, 4))

    plt.subplot(1, 2, 1)
    plt.imshow(imNew, cmap='gray')
    plt.title('原始图像')

    plt.subplot(1, 2, 2)
    plt.imshow(med_filtered, cmap='gray')
    plt.title(f'中值滤波处理 {n}x{n} 图像')

    plt.show()


# 调用函数
med(3)  # 将参数设置为你需要的模板大小
