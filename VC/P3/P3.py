import cv2
from matplotlib import pyplot as plt
import numpy as np
import os
import re
import collections
from collections import Counter
import auxFunc


def plot_images(images, names, n_rows, n_cols, name_windows):
    fig = plt.figure(0)
    fig.canvas.set_window_title(name_windows)

    for i in range(n_rows * n_cols):
        if i < len(images):
            plt.subplot(n_rows, n_cols, i + 1)

            if len(np.shape(images[i])) == 3:
                img = cv2.cvtColor(np.array(images[i], dtype=np.uint8), cv2.COLOR_BGR2RGB)
                plt.imshow(img)
                plt.axis('off')
            else:
                plt.imshow(images[i], cmap="gray")
                plt.axis('off')

            title_obj = plt.title(names[i])
            plt.setp(title_obj, color='r')

    plt.savefig("./PDF/Imagenes/" + name_windows, dpi=700)
    # plt.show()
    plt.clf()


def sift_descriptor(img1, img2, points, k=0.7):
    descriptor = cv2.xfeatures2d.SIFT_create()

    mask = np.zeros(shape=(np.shape(img1)[0], np.shape(img1)[1]))
    cv2.fillConvexPoly(mask, np.array(points, dtype=np.int32), color=1)

    kp1, desc1 = descriptor.detectAndCompute(image=img1, mask=np.array(mask, dtype=np.uint8))
    kp2, desc2 = descriptor.detectAndCompute(image=img2, mask=None)

    bf_matcher = cv2.BFMatcher(normType=cv2.NORM_L2, crossCheck=False)
    all_matches = bf_matcher.knnMatch(desc1, desc2, 2)
    matches = [m[0] for m in all_matches if m[0].distance < m[1].distance * k]

    full = cv2.drawMatches(img1=img1, keypoints1=kp1, img2=img2, keypoints2=kp2, matches1to2=matches, outImg=None,
                           flags=2)

    return full


def compute_descriptors():
    descriptor = cv2.xfeatures2d.SIFT_create(nOctaveLayers=4, contrastThreshold=0.000000001)

    descriptors = []

    def atoi(text):
        return int(text) if text.isdigit() else text

    for dirName, subdirList, fileList in os.walk("./data"):
        for fname in sorted(fileList, key=lambda x: [atoi(c) for c in re.split('(\d+)', x)]):
            if fname != ".DS_Store":
                img = cv2.imread('./data/' + fname)
                kp, desc = descriptor.detectAndCompute(image=img, mask=None)
                descriptors.append(desc)

    return descriptors


def inverted_file(dictionary):
    descriptors = compute_descriptors()
    file = collections.defaultdict(list)
    histograms = []

    for d, img in zip(descriptors, range(len(descriptors))):
        similarity = np.dot(d, np.matrix.transpose(dictionary))
        norm = np.apply_along_axis(np.linalg.norm, 1, dictionary)
        h = Counter(np.argmax(similarity / norm, axis=1))
        histograms.append(h)
        [file[k].append(img) for k in h]

    return dict(file), histograms


def query(dictionary, file, histograms, img):
    descriptor = cv2.xfeatures2d.SIFT_create(nOctaveLayers=4, contrastThreshold=0.0000001)
    kp, desc = descriptor.detectAndCompute(image=img, mask=None)

    similarity = np.dot(desc, np.matrix.transpose(dictionary))
    norm = np.apply_along_axis(np.linalg.norm, 1, dictionary)
    h = Counter(np.argmax(similarity / norm, axis=1))

    images = []
    h_dict = dict(h)

    for k in h_dict:
        try:
            images.append(file[k])
        except KeyError:
            pass

    flatten_images = [p for row in images for p in row]
    h_img = Counter(flatten_images)

    h_img_sorted = sorted(dict(h_img).items(), key=lambda x: x[1], reverse=True)
    n = 100 if len(h_img_sorted) > 100 else len(h_img_sorted)
    selected_imgs = [e[0] for e in h_img_sorted[0:n]]

    zeros_h = np.zeros(len(dictionary))

    for k in h:
        zeros_h[k] = h[k]

    similarities = []
    zeros_query = np.zeros(len(dictionary))

    for img in selected_imgs:
        for k in histograms[img]:
            zeros_query[k] = histograms[img][k]

        similarities.append((img, sum(zeros_query * zeros_h) / (np.linalg.norm(zeros_query) * np.linalg.norm(zeros_h))))

    sorted_similarities = sorted(similarities, key=lambda x: x[1], reverse=True)
    n = len(sorted_similarities) if 5 > len(sorted_similarities) else 5
    return [e[0] for e in sorted_similarities[0:n]]


def plot_clusters(index):
    descriptors, patches = auxFunc.loadAux("./descriptorsAndpatches.pkl", True)
    accuracy, labels, dictionary = auxFunc.loadDictionary("./kmeanscenters" + str(index) + ".pkl")

    labels_enumerated = list(enumerate(labels.flatten()))
    dict_clusters = collections.defaultdict(list)
    for i, c in labels_enumerated:
        dict_clusters[c].append(i)

    selected_descriptors = []
    vars = []
    for i in range(len(dictionary)):
        distance = np.sqrt(np.sum((descriptors[dict_clusters[i]] - dictionary[i]) ** 2, axis=1))
        my_index = np.argsort(distance)
        twenty_selected = my_index[0:20] if len(my_index) >= 20 else my_index
        my_descriptors = np.array(dict_clusters[i])[twenty_selected]
        selected_descriptors.append(my_descriptors)
        var = np.mean(np.var(descriptors[my_descriptors], axis=0))
        vars.append(var)

    vars_sorted = np.argsort(vars)
    selected_clusters = vars_sorted[0:5]
    final_descriptors = [selected_descriptors[e] for e in selected_clusters]

    print(index, selected_clusters)

    images = [np.array(patches)[d] for d in final_descriptors]
    names = [[str(e) for e in d] for d in final_descriptors]
    [plot_images(img, n, 4, 5, "2_" + str(index) + "_Cluster_" + str(c)) for img, n, c in
     zip(images, names, selected_clusters)]


def main():

    img128 = cv2.imread('./data/128.png')
    img130 = cv2.imread('./data/130.png')

    img143 = cv2.imread('./data/143.png')
    img145 = cv2.imread('./data/145.png')

    img216 = cv2.imread('./data/216.png')

    img229 = cv2.imread('./data2/229.png')
    img232 = cv2.imread('./data2/232.png')

    pts_128 = [(425, 253), (505, 274), (580, 256), (480, 245)]
    pts_143 = [(348, 42), (348, 129), (452, 129), (452, 42)]
    pts_229 = [(393, 111), (393, 147), (408, 147), (408, 112)]

    result = sift_descriptor(img128, img130, pts_128)
    plot_images(images=[result], names=["Images: 128 - 130."], n_rows=1, n_cols=1, name_windows="1_128_130_07")

    result = sift_descriptor(img143, img145, pts_143)
    plot_images(images=[result], names=["Images: 143 - 145."], n_rows=1, n_cols=1, name_windows="1_143_145_07")

    result = sift_descriptor(img229, img232, pts_229)
    plot_images(images=[result], names=["Images: 229 - 232."], n_rows=1, n_cols=1, name_windows="1_229_232_07")

    result = sift_descriptor(img128, img130, pts_128, 0.9)
    plot_images(images=[result], names=["Images: 128 - 130."], n_rows=1, n_cols=1, name_windows="1_128_130_09")

    result = sift_descriptor(img143, img145, pts_143, 0.9)
    plot_images(images=[result], names=["Images: 143 - 145."], n_rows=1, n_cols=1, name_windows="1_143_145_09")

    result = sift_descriptor(img229, img232, pts_229, 0.9)
    plot_images(images=[result], names=["Images: 229 - 232."], n_rows=1, n_cols=1, name_windows="1_229_232_09")

    result = sift_descriptor(img128, img216, pts_128, 0.7)
    plot_images(images=[result], names=["Images: 128 - 216."], n_rows=1, n_cols=1, name_windows="1_128_216_07")

    plot_clusters(500)
    plot_clusters(1000)
    plot_clusters(5000)

    accuracy, labels, dictionary = auxFunc.loadDictionary("./kmeanscenters5000.pkl")
    file, histograms = inverted_file(dictionary)

    result = query(dictionary, file, histograms, cv2.imread('./data/13.png'))
    imgs = [cv2.imread('./data/13.png')]
    [imgs.append(cv2.imread('./data/' + str(img) + '.png')) for img in result]
    names = ["Query: img 13"]
    [names.append("Image: " + str(img)) for img in result]
    plot_images(images=imgs, names=names, n_rows=2, n_cols=3, name_windows="3_Query_13_5000")

    result = query(dictionary, file, histograms, cv2.imread('./data/95.png'))
    imgs = [cv2.imread('./data/95.png')]
    [imgs.append(cv2.imread('./data/' + str(img) + '.png')) for img in result]
    names = ["Query: img 95"]
    [names.append("Image: " + str(img)) for img in result]
    plot_images(images=imgs, names=names, n_rows=2, n_cols=3, name_windows="3_Query_95_5000")

    result = query(dictionary, file, histograms, cv2.imread('./data/128.png'))
    imgs = [cv2.imread('./data/128.png')]
    [imgs.append(cv2.imread('./data/' + str(img) + '.png')) for img in result]
    names = ["Query: img 128"]
    [names.append("Image: " + str(img)) for img in result]
    plot_images(images=imgs, names=names, n_rows=2, n_cols=3, name_windows="3_Query_128_5000")

    accuracy, labels, dictionary = auxFunc.loadDictionary("./kmeanscenters1000.pkl")
    file, histograms = inverted_file(dictionary)

    result = query(dictionary, file, histograms, cv2.imread('./data/13.png'))
    imgs = [cv2.imread('./data/13.png')]
    [imgs.append(cv2.imread('./data/' + str(img) + '.png')) for img in result]
    names = ["Query: img 13"]
    [names.append("Image: " + str(img)) for img in result]
    plot_images(images=imgs, names=names, n_rows=2, n_cols=3, name_windows="3_Query_13_1000")

    result = query(dictionary, file, histograms, cv2.imread('./data/95.png'))
    imgs = [cv2.imread('./data/95.png')]
    [imgs.append(cv2.imread('./data/' + str(img) + '.png')) for img in result]
    names = ["Query: img 95"]
    [names.append("Image: " + str(img)) for img in result]
    plot_images(images=imgs, names=names, n_rows=2, n_cols=3, name_windows="3_Query_95_1000")

    result = query(dictionary, file, histograms, cv2.imread('./data/128.png'))
    imgs = [cv2.imread('./data/128.png')]
    [imgs.append(cv2.imread('./data/' + str(img) + '.png')) for img in result]
    names = ["Query: img 128"]
    [names.append("Image: " + str(img)) for img in result]
    plot_images(images=imgs, names=names, n_rows=2, n_cols=3, name_windows="3_Query_128_1000")

    accuracy, labels, dictionary = auxFunc.loadDictionary("./kmeanscenters500.pkl")
    file, histograms = inverted_file(dictionary)

    result = query(dictionary, file, histograms, cv2.imread('./data/13.png'))
    imgs = [cv2.imread('./data/13.png')]
    [imgs.append(cv2.imread('./data/' + str(img) + '.png')) for img in result]
    names = ["Query: img 13"]
    [names.append("Image: " + str(img)) for img in result]
    plot_images(images=imgs, names=names, n_rows=2, n_cols=3, name_windows="3_Query_13_500")

    result = query(dictionary, file, histograms, cv2.imread('./data/95.png'))
    imgs = [cv2.imread('./data/95.png')]
    [imgs.append(cv2.imread('./data/' + str(img) + '.png')) for img in result]
    names = ["Query: img 95"]
    [names.append("Image: " + str(img)) for img in result]
    plot_images(images=imgs, names=names, n_rows=2, n_cols=3, name_windows="3_Query_95_500")

    result = query(dictionary, file, histograms, cv2.imread('./data/128.png'))
    imgs = [cv2.imread('./data/128.png')]
    [imgs.append(cv2.imread('./data/' + str(img) + '.png')) for img in result]
    names = ["Query: img 128"]
    [names.append("Image: " + str(img)) for img in result]
    plot_images(images=imgs, names=names, n_rows=2, n_cols=3, name_windows="3_Query_128_500")



if __name__ == "__main__":
    main()
