import cv2
from matplotlib import pyplot as plt
import numpy as np
import copy
import math
import itertools


def plot_images(images, names, n_rows, n_cols, name_windows):
    fig = plt.figure(0)
    fig.canvas.set_window_title(name_windows)

    for i in range(n_rows * n_cols):
        if i < len(images):
            plt.subplot(n_rows, n_cols, i + 1)

            if len(np.shape(images[i])) == 3:
                img = cv2.cvtColor(np.array(images[i], dtype=np.uint8), cv2.COLOR_BGR2RGB)
                plt.imshow(img)
            else:
                plt.imshow(images[i], cmap="gray")

            plt.title(names[i])

    plt.savefig("./PDF/" + name_windows, dpi=700)
    plt.show()
    plt.clf()


def convolution(img, sigma, kernel=None, size=3, border=0, normalize=False):
    if kernel is None:
        kernel = cv2.getGaussianKernel(ksize=size * 2 * sigma + 1, sigma=sigma)

    kernel = kernel.flatten()

    if len(np.shape(img)) == 3:
        channel_1, channel_2, channel_3 = cv2.split(img)

        aux_1 = np.zeros(shape=np.shape(channel_1), dtype=np.float64)
        aux_2 = np.zeros(shape=np.shape(channel_2), dtype=np.float64)
        aux_3 = np.zeros(shape=np.shape(channel_3), dtype=np.float64)

        for row_1, row_2, row_3, i in zip(channel_1, channel_2, channel_3, range(np.shape(img)[0])):
            aux_1[i] = cv2.filter2D(src=row_1, ddepth=-1, kernel=kernel, borderType=border).flatten()
            aux_2[i] = cv2.filter2D(src=row_2, ddepth=-1, kernel=kernel, borderType=border).flatten()
            aux_3[i] = cv2.filter2D(src=row_3, ddepth=-1, kernel=kernel, borderType=border).flatten()

        aux_1 = np.array(aux_1).transpose()
        aux_2 = np.array(aux_2).transpose()
        aux_3 = np.array(aux_3).transpose()

        result_1 = np.zeros(shape=np.shape(aux_1), dtype=np.float64)
        result_2 = np.zeros(shape=np.shape(aux_2), dtype=np.float64)
        result_3 = np.zeros(shape=np.shape(aux_3), dtype=np.float64)

        for row_1, row_2, row_3, i in zip(aux_1, aux_2, aux_3, range(np.shape(aux_1)[0])):
            result_1[i] = cv2.filter2D(src=row_1, ddepth=-1, kernel=kernel, borderType=border).flatten()
            result_2[i] = cv2.filter2D(src=row_2, ddepth=-1, kernel=kernel, borderType=border).flatten()
            result_3[i] = cv2.filter2D(src=row_3, ddepth=-1, kernel=kernel, borderType=border).flatten()

        result_1 = np.array(result_1).transpose()
        result_2 = np.array(result_2).transpose()
        result_3 = np.array(result_3).transpose()

        if normalize:
            result_1 = (result_1 - np.amin(result_1)) / (np.amax(result_1) - np.amin(result_1))
            result_2 = (result_2 - np.amin(result_2)) / (np.amax(result_2) - np.amin(result_2))
            result_3 = (result_3 - np.amin(result_3)) / (np.amax(result_3) - np.amin(result_3))

        return cv2.merge([result_1, result_2, result_3])
    else:
        aux = np.zeros(shape=np.shape(img), dtype=np.float64)

        for row, i in zip(img, range(np.shape(img)[0])):
            aux[i] = cv2.filter2D(src=row, ddepth=-1, kernel=kernel, borderType=border).flatten()

        aux = np.array(aux).transpose()

        result = np.zeros(shape=np.shape(aux), dtype=np.float64)

        for row, i in zip(aux, range(np.shape(aux)[0])):
            result[i] = cv2.filter2D(src=row, ddepth=-1, kernel=kernel, borderType=border).flatten()

        result = np.array(result).transpose()

        if normalize:
            result = (result - np.amin(result)) / (np.amax(result) - np.amin(result))

        return result


def derived_convolution(img, sigma, dx=1, dy=1, size=3, border=0, normalize=False):
    kernel_dx_x, kernel_dx_y = cv2.getDerivKernels(dx=dx, dy=0, ksize=7, normalize=True)
    kernel_dy_x, kernel_dy_y = cv2.getDerivKernels(dx=0, dy=dy, ksize=7, normalize=True)

    kernel_dx_x = kernel_dx_x.flatten()
    kernel_dx_y = kernel_dx_y.flatten()

    kernel_dy_x = kernel_dy_x.flatten()
    kernel_dy_y = kernel_dy_y.flatten()
    kernel_dx_x = kernel_dx_x[::-1]
    kernel_dx_y = kernel_dx_y[::-1]

    kernel_dy_x = kernel_dy_x[::-1]
    kernel_dy_y = kernel_dy_y[::-1]

    if len(np.shape(img)) == 3:
        channel_1, channel_2, channel_3 = cv2.split(img)
        aux_x_1 = np.zeros(shape=np.shape(channel_1), dtype=np.float64)
        aux_x_2 = np.zeros(shape=np.shape(channel_2), dtype=np.float64)
        aux_x_3 = np.zeros(shape=np.shape(channel_3), dtype=np.float64)

        result_x_1 = np.zeros(shape=np.shape(channel_1), dtype=np.float64)
        result_x_2 = np.zeros(shape=np.shape(channel_2), dtype=np.float64)
        result_x_3 = np.zeros(shape=np.shape(channel_3), dtype=np.float64)

        for row_1, row_2, row_3, i in zip(channel_1, channel_2, channel_3, range(np.shape(result_x_1)[0])):
            aux_x_1[i] = cv2.filter2D(src=row_1, ddepth=cv2.CV_16S, kernel=kernel_dx_x, borderType=border).flatten()
            aux_x_2[i] = cv2.filter2D(src=row_2, ddepth=cv2.CV_16S, kernel=kernel_dx_x, borderType=border).flatten()
            aux_x_3[i] = cv2.filter2D(src=row_3, ddepth=cv2.CV_16S, kernel=kernel_dx_x, borderType=border).flatten()

        for row_1, row_2, row_3, i in zip(aux_x_1, aux_x_2, aux_x_3, range(np.shape(result_x_1)[0])):
            result_x_1[i] = cv2.filter2D(src=row_1, ddepth=-1, kernel=kernel_dx_y, borderType=border).flatten()
            result_x_2[i] = cv2.filter2D(src=row_2, ddepth=-1, kernel=kernel_dx_y, borderType=border).flatten()
            result_x_3[i] = cv2.filter2D(src=row_3, ddepth=-1, kernel=kernel_dx_y, borderType=border).flatten()

        channel_1_transpose = channel_1.transpose()
        channel_2_transpose = channel_2.transpose()
        channel_3_transpose = channel_3.transpose()

        aux_y_1 = np.zeros(shape=np.shape(channel_1_transpose), dtype=np.float64)
        aux_y_2 = np.zeros(shape=np.shape(channel_2_transpose), dtype=np.float64)
        aux_y_3 = np.zeros(shape=np.shape(channel_3_transpose), dtype=np.float64)

        result_y_1 = np.zeros(shape=np.shape(channel_1_transpose), dtype=np.float64)
        result_y_2 = np.zeros(shape=np.shape(channel_2_transpose), dtype=np.float64)
        result_y_3 = np.zeros(shape=np.shape(channel_3_transpose), dtype=np.float64)

        for row_1, row_2, row_3, i in zip(channel_1_transpose, channel_2_transpose, channel_3_transpose,
                                          range(np.shape(aux_y_1)[0])):
            aux_y_1[i] = cv2.filter2D(src=row_1, ddepth=cv2.CV_16S, kernel=kernel_dy_x, borderType=border).flatten()
            aux_y_2[i] = cv2.filter2D(src=row_2, ddepth=cv2.CV_16S, kernel=kernel_dy_x, borderType=border).flatten()
            aux_y_3[i] = cv2.filter2D(src=row_3, ddepth=cv2.CV_16S, kernel=kernel_dy_x, borderType=border).flatten()

        for row_1, row_2, row_3, i in zip(aux_y_1, aux_y_2, aux_y_3, range(np.shape(result_y_1)[0])):
            result_y_1[i] = cv2.filter2D(src=row_1, ddepth=-1, kernel=kernel_dy_y, borderType=border).flatten()
            result_y_2[i] = cv2.filter2D(src=row_2, ddepth=-1, kernel=kernel_dy_y, borderType=border).flatten()
            result_y_3[i] = cv2.filter2D(src=row_3, ddepth=-1, kernel=kernel_dy_y, borderType=border).flatten()

        if normalize:
            result_x_1 = (result_x_1 - np.amin(result_x_1)) / (np.amax(result_x_1) - np.amin(result_x_1))
            result_x_2 = (result_x_2 - np.amin(result_x_2)) / (np.amax(result_x_2) - np.amin(result_x_2))
            result_x_3 = (result_x_3 - np.amin(result_x_3)) / (np.amax(result_x_3) - np.amin(result_x_3))
            result_y_1 = (result_y_1 - np.amin(result_y_1)) / (np.amax(result_y_1) - np.amin(result_y_1))
            result_y_2 = (result_y_2 - np.amin(result_y_2)) / (np.amax(result_y_2) - np.amin(result_y_2))
            result_y_3 = (result_y_3 - np.amin(result_y_3)) / (np.amax(result_y_3) - np.amin(result_y_3))

        result_x = cv2.merge([result_x_1, result_x_2, result_x_3])
        result_y = cv2.merge([result_y_1.transpose(), result_y_2.transpose(), result_y_3.transpose()])

        if sigma == 1:
            return result_x, result_y
        else:
            x = convolution(img=result_x, sigma=sigma - 1, kernel=None, size=size, border=border)
            y = convolution(img=result_y, sigma=sigma - 1, kernel=None, size=size, border=border)

            if normalize:
                x = (x - np.amin(x)) / (np.amax(x) - np.amin(x))
                y = (y - np.amin(y)) / (np.amax(y) - np.amin(y))

            return x, y
    else:
        aux_x = np.zeros(shape=np.shape(img), dtype=np.float64)
        result_x = np.zeros(shape=np.shape(img), dtype=np.float64)

        for row, i in zip(img, range(np.shape(aux_x)[0])):
            aux_x[i] = cv2.filter2D(src=row, ddepth=cv2.CV_16S, kernel=kernel_dx_x, borderType=border).flatten()

        for row, i in zip(aux_x, range(np.shape(result_x)[0])):
            result_x[i] = cv2.filter2D(src=row, ddepth=-1, kernel=kernel_dx_y, borderType=border).flatten()

        img_transpose = img.transpose()

        aux_y = np.zeros(shape=np.shape(img_transpose), dtype=np.float64)
        result_y = np.zeros(shape=np.shape(img_transpose), dtype=np.float64)

        for row, i in zip(img_transpose, range(np.shape(aux_y)[0])):
            aux_y[i] = cv2.filter2D(src=row, ddepth=cv2.CV_16S, kernel=kernel_dy_x, borderType=border).flatten()

        for row, i in zip(aux_y, range(np.shape(result_y)[0])):
            result_y[i] = cv2.filter2D(src=row, ddepth=-1, kernel=kernel_dy_y, borderType=border).flatten()

        result_y = result_y.transpose()

        if normalize:
            result_x = (result_x - np.amin(result_x)) / (np.amax(result_x) - np.amin(result_x))
            result_y = (result_y - np.amin(result_y)) / (np.amax(result_y) - np.amin(result_y))

        if sigma == 1:
            return result_x, result_y
        else:
            x = convolution(img=result_x, sigma=sigma - 1, kernel=None, size=size, border=border)
            y = convolution(img=result_y, sigma=sigma - 1, kernel=None, size=size, border=border)

            if normalize:
                x = (x - np.amin(x)) / (np.amax(x) - np.amin(x))
                y = (y - np.amin(y)) / (np.amax(y) - np.amin(y))

            return x, y


def gaussian_pyramid(img, n_images=4, border=0, collage=False):
    aux = copy.deepcopy(img)
    result = [img]

    for i in range(n_images):
        aux = cv2.pyrDown(src=aux, borderType=border)
        result.append(aux)

    if collage:
        cols = 0
        for e in result:
            cols += np.shape(e)[1]

        final_matrix = np.full((np.shape(img)[0], cols, 3), 255, dtype=np.float64)
        accumulator = 0
        for e in result:
            for i in range(np.shape(e)[0]):
                for j in range(np.shape(e)[1]):
                    final_matrix[i][j + accumulator] = e[i][j]

            accumulator += np.shape(e)[1]

        return final_matrix
    else:
        return result


def harris_matrix_binary(src, block_size, ksize, k=0.04, border=0):
    eigenvals = cv2.cornerEigenValsAndVecs(src=src, blockSize=block_size, ksize=ksize, borderType=border)
    harris_matrix = np.zeros(shape=np.shape(src))

    first = eigenvals[:, :, 0]
    second = eigenvals[:, :, 1]

    for i in range(np.shape(src)[0]):
        for j in range(np.shape(src)[1]):
            harris_matrix[i][j] = (first[i][j] * second[i][j]) - k * ((first[i][j] + second[i][j]) ** 2)

    # Return the harris matrix and a binary one (0 or 255)
    return harris_matrix, np.ones(shape=np.shape(src)) * 255


def suppress_non_max(binary, harris_matrix, window_size=7):
    def is_center_max(windows):
        return np.max(windows) == windows[np.shape(windows)[0] // 2][np.shape(windows)[1] // 2]

    def make_zeros(img, size, i, j):
        # The center is i, j
        img[i - size:i + size + 1, j - size:j + size + 1] = 0

    # Add the border to not have problems with the window_size
    # window_size is the full width
    size = window_size // 2
    harris_matrix_augmented = cv2.copyMakeBorder(src=harris_matrix, top=size, bottom=size, right=size, left=size,
                                                 borderType=cv2.BORDER_CONSTANT)

    for i in range(np.shape(binary)[0]):
        for j in range(np.shape(binary)[1]):
            if binary[i][j] != 0:
                if is_center_max(harris_matrix_augmented[i:i + size + size + 1, j:j + size + size + 1]):
                    make_zeros(binary, size, i, j)
                    binary[i, j] = 255
                else:
                    binary[i, j] = 0


def get_n_best(src, n, points):
    for img, set in zip(src, points):
        index = [(int(np.round(p.pt[0])), int(np.round(p.pt[1]))) for p in set]
        index_j = [t[0] for t in index]
        index_i = [t[1] for t in index]
        values = img[index_i, index_j]

        for p, v in zip(set, values):
            p.response = v

    points_flatten = [p for set in points for p in set]
    sorted_points = sorted(points_flatten, key=lambda x: x.response, reverse=True)

    if len(sorted_points) > n:
        return sorted_points[0:n]
    else:
        return sorted_points


def harris_points(src, block_size=7, ksize=7, windos_size=7, n_best=500, border=cv2.BORDER_CONSTANT):
    points = []
    harris = []

    sigmas = np.arange(0, len(src))
    for img, scale in zip(src, sigmas):
        set = []
        harris_matrix, binary = harris_matrix_binary(src=img, block_size=block_size, ksize=ksize, border=border)
        suppress_non_max(binary=binary, harris_matrix=harris_matrix, window_size=windos_size)
        harris.append(harris_matrix)

        index_i, index_j = np.where(binary == 255)
        for i, j in zip(index_i, index_j):
            p = cv2.KeyPoint(x=j, y=i, _size=block_size, _octave=scale)
            set.append(p)

        points.append(set)

    return get_n_best(src=harris, n=n_best, points=points), harris


def refine_best_points(src, points, harris_matrix):
    sets_points = [[] for _ in range(len(src))]

    octaves = np.unique(np.array([p.octave for p in points]))
    d = {}
    for octave, i in zip(octaves, range(len(octaves))):
        d[octave] = i

    for p in points:
        sets_points[d[p.octave]].append(p)

    for img, set, i in zip(src, sets_points, range(len(src))):
        only_points = [(p.pt[0], p.pt[1]) for p in set]
        float_points = np.array(only_points, dtype=np.float32)
        cv2.cornerSubPix(image=img, corners=float_points, winSize=(5, 5), zeroZone=(-1, -1),
                         criteria=(cv2.TERM_CRITERIA_EPS + cv2.TERM_CRITERIA_MAX_ITER, 40, 0.01))

        for p, kp in zip(float_points, set):
            kp.pt = (p[0], p[1])

    # Delete outside points
    return [[p for p in set if p.pt[1] < np.shape(src[d[p.octave]])[0] and p.pt[0] < np.shape(src[d[p.octave]])[1]] for
            set in sets_points]


def orientation(src, points):
    for img, set_points in zip(src, points):
        int_points = [(p.pt[0], p.pt[1]) for p in set_points]
        i, j = [], []
        for p in int_points:
            i.append(int(np.round(p[1])))
            j.append(int(np.round(p[0])))

        dx, dy = derived_convolution(img=img, sigma=5, dx=1, dy=1, size=3, border=0, normalize=False)
        dx_g = cv2.GaussianBlur(src=dx, ksize=(6 * 5 + 1, 6 * 5 + 1), sigmaX=4.5, borderType=cv2.BORDER_REFLECT)
        dy_g = cv2.GaussianBlur(src=dy, ksize=(6 * 5 + 1, 6 * 5 + 1), sigmaX=4.5, borderType=cv2.BORDER_REFLECT)

        set_angles = ((np.arctan2(dy_g[i, j], dx_g[i, j])) * 180) / np.pi

        for p, a in zip(set_points, set_angles):
            p.angle = a


def add_circles_lines(src, best_points, color=(0, 0, 0), thickness=1):
    processed_image = copy.deepcopy(src)

    for set_points in best_points:
        for p in set_points:
            cv2.circle(img=processed_image,
                       center=(int(np.round(p.pt[0] * 2 ** p.octave)), int(np.round(p.pt[1] * 2 ** p.octave))),
                       radius=int(np.round(10 / int(p.octave + 1))), color=color, thickness=thickness)

            cv2.arrowedLine(img=processed_image,
                            pt1=(int(np.round(p.pt[0] * 2 ** p.octave)), int(np.round(p.pt[1] * 2 ** p.octave))),
                            pt2=(int(np.round(p.pt[0] * 2 ** p.octave)) + math.floor(
                                np.sin(p.angle) * np.round(10 / int(p.octave + 1))),
                                 int(np.round(p.pt[1] * 2 ** p.octave)) + math.floor(
                                     np.cos(p.angle) * np.round(10 / int(p.octave + 1)))),
                            color=color, thickness=thickness)

    return processed_image


def harris(img, block_size=7, ksize=7, windos_size=7, n_best=500, circle_color=(0, 0, 0), thickness=1):
    pyramid = gaussian_pyramid(img=img, n_images=2, border=cv2.BORDER_REFLECT, collage=False)
    # Best points, no matter the level
    points, harris_matrix = harris_points(src=pyramid, block_size=block_size, ksize=ksize, windos_size=windos_size,
                                          n_best=n_best,
                                          border=cv2.BORDER_CONSTANT)

    refined_points = refine_best_points(src=pyramid, points=points, harris_matrix=harris_matrix)
    orientation(src=pyramid, points=refined_points)

    return refined_points, add_circles_lines(src=img, best_points=refined_points, color=circle_color,
                                             thickness=thickness)


def extract_descriptors(img, keypoints):
    extractor = cv2.xfeatures2d.SIFT_create()
    kp = [kp for set in keypoints for kp in set]
    kp_news = [cv2.KeyPoint(x=k.pt[0] * 2 ** k.octave, y=k.pt[1] * 2 ** k.octave, _octave=k.octave,
                            _size=k.size, _angle=k.angle, _response=k.response) for k in kp]
    return extractor.compute(image=img, keypoints=kp_news)


def sift_descriptor(img1, img2, norm_type=cv2.NORM_L2, n_matches=50, bruteForce=True, threshold=0.7, keypoints=None):
    if keypoints is None:
        descriptor = cv2.xfeatures2d.SIFT_create()
        kp1, desc1 = descriptor.detectAndCompute(image=img1, mask=None)
        kp2, desc2 = descriptor.detectAndCompute(image=img2, mask=None)
    else:
        kp1, desc1 = extract_descriptors(img=img1, keypoints=keypoints[0])
        kp2, desc2 = extract_descriptors(img=img2, keypoints=keypoints[1])

    if bruteForce:
        bf_matcher = cv2.BFMatcher(normType=norm_type, crossCheck=True)
        matches = bf_matcher.match(desc1, desc2)
    else:
        bf_matcher = cv2.BFMatcher(normType=norm_type, crossCheck=False)
        all_matches = bf_matcher.knnMatch(desc1, desc2, 2)
        matches = [m[0] for m in all_matches if m[0].distance < m[1].distance * threshold]

    matches = np.array(sorted(matches, key=lambda x: x.distance, reverse=False))
    output = np.zeros(shape=(1, 1)).astype(np.float64)
    full = cv2.drawMatches(img1=img1, keypoints1=kp1, img2=img2, keypoints2=kp2, matches1to2=matches, outImg=output)

    if n_matches < len(matches):
        partial_matches = matches[0:n_matches]
        partial = cv2.drawMatches(img1=img1, keypoints1=kp1, img2=img2, keypoints2=kp2, matches1to2=partial_matches,
                                  outImg=output)

        return full, partial, partial_matches
    else:
        return full, full, matches


def get_homography(img1, img2, norm_type=cv2.NORM_L2, threshold=0.7):
    sift = cv2.xfeatures2d.SIFT_create()

    kp1, desc1 = sift.detectAndCompute(img1, None)
    kp2, desc2 = sift.detectAndCompute(img2, None)

    bf_matcher = cv2.BFMatcher(normType=norm_type, crossCheck=True)
    matches = bf_matcher.match(desc1, desc2)

    sorted_matches = sorted(matches, key=lambda x: x.distance, reverse=False)

    src_points = np.float32([kp1[p.queryIdx].pt for p in sorted_matches])
    dst_points = np.float32([kp2[p.trainIdx].pt for p in sorted_matches])

    return cv2.findHomography(src_points, dst_points, cv2.RANSAC, 1)


def mosaic(src):
    if len(src) % 2 == 0:
        src.append(src[-1])

    height = int(np.sum([np.shape(img)[0] for img in src]))
    width = int(np.sum([np.shape(img)[1] for img in src]))
    result = np.ones(shape=(height, width)) * 255
    center = len(src) // 2
    shape_center = np.shape(src[center])
    shape_mosaic = np.shape(result)

    homographies = [get_homography(src[i], src[i + 1])[0] for i in range(len(src) - 1)]

    for i in range(center, len(homographies)):
        homographies[i] = np.linalg.inv(homographies[i])

    h_0 = [[1, 0, int(np.round(shape_mosaic[1] / 2)) - int(np.round(shape_center[1] / 2))],
           [0, 1, int(np.round(shape_mosaic[0] / 2)) - int(np.round(shape_center[0] / 2))],
           [0, 0, 1]]

    left, right = np.split(np.array(homographies), 2)
    left = list(reversed(left))
    left = list(itertools.chain(np.array([h_0]), left))
    right = list(itertools.chain(np.array([h_0]), right))

    for i in range(1, len(left)):
        left[i] = np.dot(left[i - 1], left[i])
        right[i] = np.dot(right[i - 1], right[i])

    left = list(reversed(left))
    del left[-1]

    final_homographies = list(itertools.chain(left, right))

    for i in range(len(src)):
        result = cv2.warpPerspective(src=src[i], M=np.array(final_homographies[i], dtype=np.float32), dst=result,
                                     dsize=(np.shape(result)[1], np.shape(result)[0]),
                                     borderMode=cv2.BORDER_TRANSPARENT)

    r, g, b = cv2.split(result)
    r = np.transpose(r)
    g = np.transpose(g)
    b = np.transpose(b)
    transposed = cv2.merge([r, g, b])

    rows = [i for i, row in zip(range(np.shape(result)[0]), result) if not np.all(row == [0, 0, 0])]
    cols = [i for i, col in zip(range(np.shape(result)[1]), transposed) if not np.all(col == [0, 0, 0])]
    return result[rows][:, cols]


def main():
    yosemite1 = cv2.imread('./data/yosemite/Yosemite1.jpg', cv2.IMREAD_GRAYSCALE)
    yosemite2 = cv2.imread('./data/yosemite/Yosemite2.jpg', cv2.IMREAD_GRAYSCALE)

    # block_size = 3 * int(sigma) + 1 + 3 * int(sigma) -> 7
    # ksize = 6 * sigma + 1 -> 7
    y1 = harris(yosemite1, block_size=7, ksize=7, windos_size=7, n_best=500, circle_color=(0, 0, 0), thickness=1)
    y2 = harris(yosemite2, block_size=7, ksize=7, windos_size=7, n_best=500, circle_color=(0, 0, 0), thickness=1)

    plot_images(images=[y1[1]], names=["Yosemite 1"], n_rows=1, n_cols=1, name_windows="1_HP_Yosemite1")
    plot_images(images=[y2[1]], names=["Yosemite 2"], n_rows=1, n_cols=1, name_windows="1_HP_Yosemite2")

    f_bf, p_bf, m_bf = sift_descriptor(img1=yosemite1, img2=yosemite2, norm_type=cv2.NORM_L2, n_matches=50,
                                       bruteForce=True, keypoints=None)
    f_knn, p_knn, m_knn = sift_descriptor(img1=yosemite1, img2=yosemite2, norm_type=cv2.NORM_L2, n_matches=50,
                                          bruteForce=False, threshold=0.7, keypoints=None)

    own_f_bf, own_p_bf, own_m_bf = sift_descriptor(img1=yosemite1, img2=yosemite2, norm_type=cv2.NORM_L2,
                                                   n_matches=50,
                                                   bruteForce=True, keypoints=(y1[0], y2[0]))
    own_f_knn, own_p_knn, own_m_knn = sift_descriptor(img1=yosemite1, img2=yosemite2, norm_type=cv2.NORM_L2,
                                                      n_matches=50, bruteForce=False, threshold=0.7,
                                                      keypoints=(y1[0], y2[0]))

    plot_images(images=[f_bf], names=["BF+CC. All matches: cv2"], n_rows=1, n_cols=1, name_windows="2_Full_BF+CC")
    plot_images(images=[p_bf], names=["BF+CC. Partial matches: cv2"], n_rows=1, n_cols=1,
                name_windows="2_Partial_BF+CC")

    plot_images(images=[own_f_bf], names=["BF+CC. All matches"], n_rows=1, n_cols=1, name_windows="2_Own_Full_BF+CC")
    plot_images(images=[own_p_bf], names=["BF+CC. Partial matches"], n_rows=1, n_cols=1,
                name_windows="2_Own_Partial_BF+CC")

    plot_images(images=[f_knn], names=["kNN. All matches: cv2"], n_rows=1, n_cols=1, name_windows="2_Full_kNN")
    plot_images(images=[p_knn], names=["kNN. Partial matches: cv2"], n_rows=1, n_cols=1, name_windows="2_Partial_kNN")

    plot_images(images=[own_f_knn], names=["kNN. All matches"], n_rows=1, n_cols=1, name_windows="2_Own_Full_kNN")
    plot_images(images=[own_p_knn], names=["kNN. Partial matches"], n_rows=1, n_cols=1,
                name_windows="2_Own_Partial_kNN")

    img1 = cv2.imread('./data/mosaico-1/mosaico002.jpg')
    img2 = cv2.imread('./data/mosaico-1/mosaico003.jpg')
    img3 = cv2.imread('./data/mosaico-1/mosaico004.jpg')
    img4 = cv2.imread('./data/mosaico-1/mosaico006.jpg')
    img5 = cv2.imread('./data/mosaico-1/mosaico005.jpg')
    img6 = cv2.imread('./data/mosaico-1/mosaico007.jpg')
    img7 = cv2.imread('./data/mosaico-1/mosaico008.jpg')
    img8 = cv2.imread('./data/mosaico-1/mosaico009.jpg')
    img9 = cv2.imread('./data/mosaico-1/mosaico010.jpg')
    img10 = cv2.imread('./data/mosaico-1/mosaico011.jpg')

    images = [img1, img2, img3]
    m = mosaic(src=images)
    plot_images(images=[m], names=["Mosaic. N = 3"], n_rows=1, n_cols=1, name_windows="3_Mosaic")

    images = [img1, img2, img3, img4, img5]
    m = mosaic(src=images)
    plot_images(images=[m], names=["Mosaic. N = 5"], n_rows=1, n_cols=1, name_windows="4_Mosaic_5")

    images = [img1, img2, img3, img4, img5, img6, img7, img8, img9, img10]
    m = mosaic(src=images)
    plot_images(images=[m], names=["Mosaic. N = 10"], n_rows=1, n_cols=1, name_windows="4_Mosaic_10")

    img1 = cv2.imread('./data/street/1.jpg')
    img2 = cv2.imread('./data/street/2.jpg')
    img3 = cv2.imread('./data/street/3.jpg')
    img4 = cv2.imread('./data/street/4.jpg')
    img5 = cv2.imread('./data/street/6.jpg')
    img6 = cv2.imread('./data/street/5.jpg')
    img7 = cv2.imread('./data/street/7.jpg')

    images = [img1, img2, img3, img4, img5, img6, img7]
    m = mosaic(src=images)
    plot_images(images=[m], names=["Street. N = 7"], n_rows=1, n_cols=1, name_windows="4_Street_7")


if __name__ == "__main__":
    main()
