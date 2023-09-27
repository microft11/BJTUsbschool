import cv2
import numpy as np


# 高斯滤波+canny边缘检测
def get_edge_img(color_img, gaussian_ksize=5, gaussian_sigmax=3, canny_threshold1=50, canny_threshold2=200):
    gaussian = cv2.GaussianBlur(color_img, (gaussian_ksize, gaussian_ksize), gaussian_sigmax)
    gray_img = cv2.cvtColor(gaussian, cv2.COLOR_BGR2GRAY)
    edge_img = cv2.Canny(gray_img, canny_threshold1, canny_threshold2)
    return edge_img


def roi_mask(gray_img):
    # region = np.array([[[120, 332], [527, 342], [482, 284], [213, 271]]], dtype=np.int32)  # video1
    region = np.array([[[44, 245], [221, 117], [303, 119], [461, 233]]], dtype=np.int32) # video2
    mask = np.zeros_like(gray_img)
    cv2.fillPoly(mask, region, 255)
    img_mask = cv2.bitwise_and(gray_img, mask)
    return img_mask


def get_lines(edge_img):
    # 斜率计算
    def calculate_slope(line):
        x1, y1, x2, y2 = line[0]
        slope = (y2 - y1) / (x2 - x1)
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
        if len(x_coords) == 0:
            return None
        poly = np.polyfit(x_coords, y_coords, deg=1)
        point_min = (np.min(x_coords), np.polyval(poly, np.min(x_coords)))
        point_max = (np.max(x_coords), np.polyval(poly, np.max(x_coords)))
        return np.array([point_min, point_max], dtype=np.int32)

    lines = cv2.HoughLinesP(edge_img, 1, np.pi / 180, 15, minLineLength=20, maxLineGap=40)

    ref_point = (edge_img.shape[1] // 2, edge_img.shape[0] - 1)  # 选取参照点为图像中心靠底部的位置

    distances = []
    for line in lines:
        for x1, y1, x2, y2 in line:
            center_x = (x1 + x2) // 2
            center_y = (y1 + y2) // 2
            dist = np.sqrt((center_x - ref_point[0]) ** 2 + (center_y - ref_point[1]) ** 2)
            distances.append(dist)

    min_dist_idx = np.argmin(distances)  # 距离参照点最近的轮廓索引
    closest_line = lines[min_dist_idx]

    left_lines, right_lines = [], []
    for line in lines:
        for x1, y1, x2, y2 in line:
            k = (y2 - y1) / (x2 - x1)
            if k < 0:
                left_lines.append(line)
            else:
                right_lines.append(line)

    closest_line_found = False
    for line in left_lines:
        if np.array_equal(line, closest_line):
            closest_line_found = True
            break
    if not closest_line_found:
        left_lines = []
        right_lines = []

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


def show_lane(color_img, prev_img):
    edge_img = get_edge_img(color_img)
    mask_gray_img = roi_mask(edge_img)
    lines = get_lines(mask_gray_img)

    if lines[0] is None or lines[1] is None:
        # Use the lines from the previous frame if either or both are not present
        edge_img = get_edge_img(prev_img)
        mask_gray_img = roi_mask(edge_img)
        lines_pre = get_lines(mask_gray_img)
        draw_line(color_img, lines_pre)
    else:
        draw_line(color_img, lines)

    return color_img


if __name__ == '__main__':

    capture = cv2.VideoCapture('video2.mp4')
    fourcc = cv2.VideoWriter_fourcc('X', 'V', 'I', 'D')
    outfile = cv2.VideoWriter('output.avi', fourcc, 25, (1280, 368))

    prev_frame = None

    while True:
        ret, frame = capture.read()
        if not ret:
            break

        if prev_frame is None:
            prev_frame = frame.copy()

        origin = np.copy(frame)
        frame = show_lane(frame, prev_frame)
        output = np.concatenate((origin, frame), axis=1)
        outfile.write(output)
        cv2.imshow('video', output)

        # Update the previous frame
        prev_frame = frame.copy()

        if cv2.waitKey(30) & 0xFF == ord('q'):
            break

    capture.release()
    outfile.release()
    cv2.destroyAllWindows()
