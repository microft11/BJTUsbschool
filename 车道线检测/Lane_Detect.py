import cv2
import numpy as np


# 高斯滤波+canny边缘检测
def get_edge_img(color_img, gaussian_ksize=5, gaussian_sigmax=3,
                 canny_threshold1=50, canny_threshold2=200):
    # param intoduction
    # color_img 输入图片    gaussian_ksize 高斯核大小
    # gaussian_sigmax X方向上的高斯核标准偏差
    gaussian = cv2.GaussianBlur(color_img, (gaussian_ksize, gaussian_ksize),
                                gaussian_sigmax)
    gray_img = cv2.cvtColor(gaussian, cv2.IMREAD_GRAYSCALE)
    edge_img = cv2.Canny(gray_img, canny_threshold1, canny_threshold2);
    return edge_img


def roi_mask(gray_img):
    # poly_pts = np.array([[[0, 332], [242, 255], [305, 255], [402, 332]]])
    poly_pts = np.array([[[44, 245], [221, 117], [303, 119], [461, 233]]])
    mask = np.zeros_like(gray_img)
    cv2.fillPoly(mask, pts=poly_pts, color=255)
    img_mask = cv2.bitwise_and(gray_img, mask)
    return img_mask


def get_lines(edge_img):
    # 斜率计算
    def calculate_slope(line):
        x_1, y_1, x_2, y_2 = line[0]
        slope = (y_2 - y_1) / (x_2 - x_1)
        return slope

    # 离群值过滤
    def reject_abnormal_lines(lines, threshold):
        slopes = [calculate_slope(line) for line in lines]
        while len(lines) > 0:
            mean = np.mean(slopes)
            diff = [abs(s - mean) for s in slopes]
            idx = np.argmax(diff)
            if diff[idx] > threshold:
                slopes.pop(idx)
                lines.pop(idx)
            else:
                break
        return lines

    # 最小二乘拟合
    def least_squares_fit(lines):

        x_coords = np.ravel([[line[0][0], line[0][2]] for line in lines])
        y_coords = np.ravel([[line[0][1], line[0][3]] for line in lines])
        # 2. 进行直线拟合.得到多项式系数
        if len(x_coords) == 0:
            return None
        poly = np.polyfit(x_coords, y_coords, deg=1)
        # 3. 根据多项式系数,计算两个直线上的点,用于唯一确定这条直线
        point_min = (np.min(x_coords), np.polyval(poly, np.min(x_coords)))
        point_max = (np.max(x_coords), np.polyval(poly, np.max(x_coords)))
        return np.array([point_min, point_max], dtype=np.int64)

    lines = cv2.HoughLinesP(edge_img, 1, np.pi / 180, 15, minLineLength=20, maxLineGap=40)

    left_lines = [line for line in lines if calculate_slope(line) < 0]
    right_lines = [line for line in lines if calculate_slope(line) > 0]

    left_lines = reject_abnormal_lines(left_lines, threshold=0.2)
    right_lines = reject_abnormal_lines(right_lines, threshold=0.2)

    return least_squares_fit(left_lines), least_squares_fit(right_lines)


def draw_line(img, lines):
    left_line, right_line = lines

    # 检查左车道线是否存在
    if left_line is not None:
        cv2.line(img, tuple(left_line[0]), tuple(left_line[1]), color=(100, 205, 255), thickness=2)

    # 检查右车道线是否存在
    if right_line is not None:
        cv2.line(img, tuple(right_line[0]), tuple(right_line[1]), color=(100, 205, 255), thickness=2)


def show_lane(color_img):
    edge_img = get_edge_img(color_img)
    mask_gray_img = roi_mask(edge_img)
    lines = get_lines(mask_gray_img)
    draw_line(color_img, lines)
    return color_img


if __name__ == '__main__':
    capture = cv2.VideoCapture('video2cut.mp4')
    fourcc = cv2.VideoWriter_fourcc('X', 'V', 'I', 'D')
    outfile = cv2.VideoWriter('output.avi', fourcc, 25, (1280, 368))

    while True:
        ret, frame = capture.read()
        origin = np.copy(frame)
        frame = show_lane(frame)
        output = np.concatenate((origin, frame), axis=1)
        outfile.write(output)
        cv2.imshow('video', output)
        cv2.waitKey(10)
