import cv2


def find_qr_code(image_path):
    # 读取图像
    image = cv2.imread(image_path)

    if image is None:
        print("错误：无法读取图像。")
        return

    # 将图像转换为灰度
    gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)

    # 使用OpenCV自带的Sobel算子进行过滤
    gradX = cv2.Sobel(gray, ddepth=cv2.CV_32F, dx=1, dy=0, ksize=-1)
    gradY = cv2.Sobel(gray, ddepth=cv2.CV_32F, dx=0, dy=1, ksize=-1)

    # 将过滤得到的X方向像素值减去Y方向的像素值
    gradient = cv2.subtract(gradX, gradY)
    # 先缩放元素再取绝对值，最后转换格式为8bit型
    gradient = cv2.convertScaleAbs(gradient)
    # 均值滤波取二值化
    blurred = cv2.blur(gradient, (9, 9))
    (_, thresh) = cv2.threshold(blurred, 225, 255, cv2.THRESH_BINARY)

    # 腐蚀和膨胀的函数
    kernel = cv2.getStructuringElement(cv2.MORPH_RECT, (21, 7))
    closed = cv2.morphologyEx(thresh, cv2.MORPH_CLOSE, kernel)
    closed = cv2.erode(closed, None, iterations=4)
    closed = cv2.dilate(closed, None, iterations=4)

    # 找到边界findContours函数
    (cnts, _) = cv2.findContours(closed.copy(), cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

    # 计算出包围目标的最小矩形区域
    for c in cnts:
        epsilon = 0.04 * cv2.arcLength(c, True)
        approx = cv2.approxPolyDP(c, epsilon, True)

        if len(approx) == 4:
            # 在QR码周围绘制边界框
            cv2.drawContours(image, [approx], -1, (0, 255, 0), 2)

    # 显示结果
    cv2.imshow("QR码检测", image)
    cv2.waitKey(0)
    cv2.destroyAllWindows()


# 调用函数以进行QR码检测
find_qr_code('image/myQR.png')

# import cv2
#
#
# def find_qr_code(image_path):
#     # 读取图像
#     image = cv2.imread(image_path)
#
#     if image is None:
#         print("错误：无法读取图像。")
#         return
#
#     # 将图像转换为灰度
#     gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
#
#     # 应用高斯模糊以减少噪声并提高轮廓检测
#     blurred = cv2.GaussianBlur(gray, (5, 5), 0)
#
#     # 使用Canny边缘检测器在图像中找到边缘
#     edges = cv2.Canny(blurred, 50, 150)
#
#     # 在边缘图像中找到轮廓
#     (cnts, _) = cv2.findContours(edges.copy(), cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
#
#     # 遍历轮廓
#     for c in cnts:
#         # 近似轮廓为多边形
#         epsilon = 0.04 * cv2.arcLength(c, True)
#         approx = cv2.approxPolyDP(c, epsilon, True)
#
#         # 如果轮廓有4个顶点，则可能是QR码
#         if len(approx) == 4:
#             # 在QR码周围绘制边界框
#             cv2.drawContours(image, [approx], -1, (0, 255, 0), 2)
#
#     # 显示结果
#     cv2.imshow("QR码检测", image)
#     cv2.waitKey(0)
#     cv2.destroyAllWindows()
#
#
# find_qr_code('image/myQR.png')
