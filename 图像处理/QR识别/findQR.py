"""
找到二维码的地点
"""
import numpy as np
import argparse
import cv2
import cv2
import pyzbar.pyzbar as pyzbar


def decodeDisplay(image):
    barcodes = pyzbar.decode(image)
    for barcode in barcodes:
        # 提取二维码的边界框的位置
        # 画出图像中条形码的边界框
        (x, y, w, h) = barcode.rect
        cv2.rectangle(image, (x, y), (x + w, y + h), (255, 255, 225), 7)

        # 提取二维码数据为字节对象，所以如果我们想在输出图像上
        # 画出来，就需要先将它转换成字符串
        barcodeData = barcode.data.decode("utf-8")
        barcodeType = barcode.type

        # 绘出图像上条形码的数据和条形码类型
        text = "{} ({})".format(barcodeData, barcodeType)
        cv2.putText(image, text, (x, y - 10), cv2.FONT_HERSHEY_SIMPLEX,
                    .5, (0, 225, 225), 2)

        # 向终端打印条形码数据和条形码类型
        print("[INFO] Found {} barcode: {}".format(barcodeType, barcodeData))
    return image


def detect_static_image(image_path):
    # 读取图像
    frame = cv2.imread(image_path)
    # 转为灰度图像
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    im = decodeDisplay(gray)

    cv2.imshow("image", im)
    cv2.waitKey(0)
    cv2.destroyAllWindows()


if __name__ == '__main__':
    image_path = "myQR.png"
    detect_static_image(image_path)

"""
以下代码不可运行
# print("请输入解码图片完整名称：")
# code_name = input('>>:').strip()
# print("正在识别：")
# image = cv2.imread(code_name)

image = cv2.imread("myQR.png")

# 灰度
gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)

# 使用opencv自带的Sobel算子进行过滤
gradX = cv2.Sobel(gray, ddepth=5, dx=1, dy=0, ksize=-1)
gradY = cv2.Sobel(gray, ddepth=5, dx=0, dy=1, ksize=-1)

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
(_, cnts, _) = cv2.findContours(closed.copy(),
                                cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
# 计算出包围目标的最小矩形区域
c = sorted(cnts, key=cv2.contourArea, reverse=True)[0]
rect = cv2.minAreaRect(c)
box = np.int0(cv2.boxPoints(rect))

cv2.drawContours(image, [box], -1, (0, 255, 0), 3)
cv2.imshow("ScanQRcodeTest", image)
cv2.waitKey(0)
"""
