import cv2
from matplotlib import pyplot as plt
import numpy as np
import copy
import math


def plot_images(imagenes, nombres, num_filas, num_columnas, name_windows):
    fig = plt.figure(0)
    fig.canvas.set_window_title(name_windows)

    for i in range(num_filas * num_columnas):
        if i < len(imagenes):
            plt.subplot(num_filas, num_columnas, i + 1)

            if len(np.shape(imagenes[i])) == 3:
                # Si la imagen tiene tres canales, pintamos en color
                # Cuidado con que OpenCV no usar RGB
                img = cv2.cvtColor(np.array(imagenes[i], dtype=np.uint8), cv2.COLOR_BGR2RGB)
                plt.imshow(img)
            else:
                # Si tiene un canal, pintamos en gris
                plt.imshow(imagenes[i], cmap="gray")

            plt.title(nombres[i])

    plt.show()


def convolucion(img, sigma, tamanio=3, borde=0):
    gaussian_blur = cv2.GaussianBlur(src=img, ksize=(tamanio * 2 * sigma + 1, tamanio * 2 * sigma + 1), sigmaX=sigma,
                                     borderType=borde)

    return gaussian_blur


def convolucion_separable(img, sigma, kernel=None, tamanio=3, borde=0, normalize=False):
    if kernel is None:
        # Si no nos dan el kernel, lo calculamos
        kernel = cv2.getGaussianKernel(ksize=tamanio * 2 * sigma + 1, sigma=sigma)

    kernel = kernel.flatten()

    if len(np.shape(img)) == 3:
        # Tratamiento de los tres canales
        canal_1, canal_2, canal_3 = cv2.split(img)

        auxiliar_1 = np.zeros(shape=np.shape(canal_1), dtype=np.float64)
        auxiliar_2 = np.zeros(shape=np.shape(canal_2), dtype=np.float64)
        auxiliar_3 = np.zeros(shape=np.shape(canal_3), dtype=np.float64)

        # Paseamos la máscara por filas
        for fila_1, fila_2, fila_3, i in zip(canal_1, canal_2, canal_3, range(np.shape(img)[0])):
            auxiliar_1[i] = cv2.filter2D(src=fila_1, ddepth=-1, kernel=kernel, borderType=borde).flatten()
            auxiliar_2[i] = cv2.filter2D(src=fila_2, ddepth=-1, kernel=kernel, borderType=borde).flatten()
            auxiliar_3[i] = cv2.filter2D(src=fila_3, ddepth=-1, kernel=kernel, borderType=borde).flatten()

        # Trasponemos para acceder más fácilmente a las columnas
        auxiliar_1 = np.array(auxiliar_1).transpose()
        auxiliar_2 = np.array(auxiliar_2).transpose()
        auxiliar_3 = np.array(auxiliar_3).transpose()

        salida_1 = np.zeros(shape=np.shape(auxiliar_1), dtype=np.float64)
        salida_2 = np.zeros(shape=np.shape(auxiliar_2), dtype=np.float64)
        salida_3 = np.zeros(shape=np.shape(auxiliar_3), dtype=np.float64)

        # Paseamos la máscara por columnas
        for fila_1, fila_2, fila_3, i in zip(auxiliar_1, auxiliar_2, auxiliar_3, range(np.shape(auxiliar_1)[0])):
            salida_1[i] = cv2.filter2D(src=fila_1, ddepth=-1, kernel=kernel, borderType=borde).flatten()
            salida_2[i] = cv2.filter2D(src=fila_2, ddepth=-1, kernel=kernel, borderType=borde).flatten()
            salida_3[i] = cv2.filter2D(src=fila_3, ddepth=-1, kernel=kernel, borderType=borde).flatten()

        salida_1 = np.array(salida_1).transpose()
        salida_2 = np.array(salida_2).transpose()
        salida_3 = np.array(salida_3).transpose()

        if normalize:
            salida_1 = (salida_1 - np.amin(salida_1)) / (np.amax(salida_1) - np.amin(salida_1))
            salida_2 = (salida_2 - np.amin(salida_2)) / (np.amax(salida_2) - np.amin(salida_2))
            salida_3 = (salida_3 - np.amin(salida_3)) / (np.amax(salida_3) - np.amin(salida_3))

        return cv2.merge([salida_1, salida_2, salida_3])
    else:
        auxiliar = np.zeros(shape=np.shape(img), dtype=np.float64)

        for fila, i in zip(img, range(np.shape(img)[0])):
            auxiliar[i] = cv2.filter2D(src=fila, ddepth=-1, kernel=kernel, borderType=borde).flatten()

        auxiliar = np.array(auxiliar).transpose()

        salida = np.zeros(shape=np.shape(auxiliar), dtype=np.float64)

        for fila, i in zip(auxiliar, range(np.shape(auxiliar)[0])):
            salida[i] = cv2.filter2D(src=fila, ddepth=-1, kernel=kernel, borderType=borde).flatten()

        salida = np.array(salida).transpose()

        if normalize:
            salida = (salida - np.amin(salida)) / (np.amax(salida) - np.amin(salida))

        return salida


def convolucion_derivada(img, sigma, derivada_x=1, derivada_y=1, tamanio=3, borde=0, normalize=False):
    kernel_derivx_x, kernel_derivx_y = cv2.getDerivKernels(dx=derivada_x, dy=0, ksize=7, normalize=True)
    kernel_derivy_x, kernel_derivy_y = cv2.getDerivKernels(dx=0, dy=derivada_y, ksize=7, normalize=True)

    kernel_derivx_x = kernel_derivx_x.flatten()
    kernel_derivx_y = kernel_derivx_y.flatten()

    kernel_derivy_x = kernel_derivy_x.flatten()
    kernel_derivy_y = kernel_derivy_y.flatten()

    # Invertimos los kernels para hacer convolución
    kernel_derivx_x = kernel_derivx_x[::-1]
    kernel_derivx_y = kernel_derivx_y[::-1]

    kernel_derivy_x = kernel_derivy_x[::-1]
    kernel_derivy_y = kernel_derivy_y[::-1]

    if len(np.shape(img)) == 3:
        canal_1, canal_2, canal_3 = cv2.split(img)
        # Paseamos la máscara de la derivada en x por filas
        auxiliar_x_1 = np.zeros(shape=np.shape(canal_1), dtype=np.float64)
        auxiliar_x_2 = np.zeros(shape=np.shape(canal_2), dtype=np.float64)
        auxiliar_x_3 = np.zeros(shape=np.shape(canal_3), dtype=np.float64)

        salida_x_1 = np.zeros(shape=np.shape(canal_1), dtype=np.float64)
        salida_x_2 = np.zeros(shape=np.shape(canal_2), dtype=np.float64)
        salida_x_3 = np.zeros(shape=np.shape(canal_3), dtype=np.float64)

        for fila_1, fila_2, fila_3, i in zip(canal_1, canal_2, canal_3, range(np.shape(salida_x_1)[0])):
            auxiliar_x_1[i] = cv2.filter2D(src=fila_1, ddepth=cv2.CV_16S, kernel=kernel_derivx_x,
                                           borderType=borde).flatten()
            auxiliar_x_2[i] = cv2.filter2D(src=fila_2, ddepth=cv2.CV_16S, kernel=kernel_derivx_x,
                                           borderType=borde).flatten()
            auxiliar_x_3[i] = cv2.filter2D(src=fila_3, ddepth=cv2.CV_16S, kernel=kernel_derivx_x,
                                           borderType=borde).flatten()

        for fila_1, fila_2, fila_3, i in zip(auxiliar_x_1, auxiliar_x_2, auxiliar_x_3, range(np.shape(salida_x_1)[0])):
            salida_x_1[i] = cv2.filter2D(src=fila_1, ddepth=-1, kernel=kernel_derivx_y, borderType=borde).flatten()
            salida_x_2[i] = cv2.filter2D(src=fila_2, ddepth=-1, kernel=kernel_derivx_y, borderType=borde).flatten()
            salida_x_3[i] = cv2.filter2D(src=fila_3, ddepth=-1, kernel=kernel_derivx_y, borderType=borde).flatten()

        canal_1_transpose = canal_1.transpose()
        canal_2_transpose = canal_2.transpose()
        canal_3_transpose = canal_3.transpose()

        auxiliar_y_1 = np.zeros(shape=np.shape(canal_1_transpose), dtype=np.float64)
        auxiliar_y_2 = np.zeros(shape=np.shape(canal_2_transpose), dtype=np.float64)
        auxiliar_y_3 = np.zeros(shape=np.shape(canal_3_transpose), dtype=np.float64)

        salida_y_1 = np.zeros(shape=np.shape(canal_1_transpose), dtype=np.float64)
        salida_y_2 = np.zeros(shape=np.shape(canal_2_transpose), dtype=np.float64)
        salida_y_3 = np.zeros(shape=np.shape(canal_3_transpose), dtype=np.float64)

        # Paseamos la máscara de la derivada en y por columnas
        for fila_1, fila_2, fila_3, i in zip(canal_1_transpose, canal_2_transpose, canal_3_transpose,
                                             range(np.shape(auxiliar_y_1)[0])):
            auxiliar_y_1[i] = cv2.filter2D(src=fila_1, ddepth=cv2.CV_16S, kernel=kernel_derivy_x,
                                           borderType=borde).flatten()
            auxiliar_y_2[i] = cv2.filter2D(src=fila_2, ddepth=cv2.CV_16S, kernel=kernel_derivy_x,
                                           borderType=borde).flatten()
            auxiliar_y_3[i] = cv2.filter2D(src=fila_3, ddepth=cv2.CV_16S, kernel=kernel_derivy_x,
                                           borderType=borde).flatten()

        for fila_1, fila_2, fila_3, i in zip(auxiliar_y_1, auxiliar_y_2, auxiliar_y_3, range(np.shape(salida_y_1)[0])):
            salida_y_1[i] = cv2.filter2D(src=fila_1, ddepth=-1, kernel=kernel_derivy_y, borderType=borde).flatten()
            salida_y_2[i] = cv2.filter2D(src=fila_2, ddepth=-1, kernel=kernel_derivy_y, borderType=borde).flatten()
            salida_y_3[i] = cv2.filter2D(src=fila_3, ddepth=-1, kernel=kernel_derivy_y, borderType=borde).flatten()

        if normalize:
            salida_x_1 = (salida_x_1 - np.amin(salida_x_1)) / (np.amax(salida_x_1) - np.amin(salida_x_1))
            salida_x_2 = (salida_x_2 - np.amin(salida_x_2)) / (np.amax(salida_x_2) - np.amin(salida_x_2))
            salida_x_3 = (salida_x_3 - np.amin(salida_x_3)) / (np.amax(salida_x_3) - np.amin(salida_x_3))
            salida_y_1 = (salida_y_1 - np.amin(salida_y_1)) / (np.amax(salida_y_1) - np.amin(salida_y_1))
            salida_y_2 = (salida_y_2 - np.amin(salida_y_2)) / (np.amax(salida_y_2) - np.amin(salida_y_2))
            salida_y_3 = (salida_y_3 - np.amin(salida_y_3)) / (np.amax(salida_y_3) - np.amin(salida_y_3))

        salida_x = cv2.merge([salida_x_1, salida_x_2, salida_x_3])
        salida_y = cv2.merge([salida_y_1.transpose(), salida_y_2.transpose(), salida_y_3.transpose()])

        if sigma == 1:
            return salida_x, salida_y
        else:
            x = convolucion_separable(img=salida_x, sigma=sigma - 1, kernel=None, tamanio=tamanio, borde=borde)
            y = convolucion_separable(img=salida_y, sigma=sigma - 1, kernel=None, tamanio=tamanio, borde=borde)

            if normalize:
                x = (x - np.amin(x)) / (np.amax(x) - np.amin(x))
                y = (y - np.amin(y)) / (np.amax(y) - np.amin(y))

            return x, y
    else:
        auxiliar_x = np.zeros(shape=np.shape(img), dtype=np.float64)
        salida_x = np.zeros(shape=np.shape(img), dtype=np.float64)

        for fila, i in zip(img, range(np.shape(auxiliar_x)[0])):
            auxiliar_x[i] = cv2.filter2D(src=fila, ddepth=cv2.CV_16S, kernel=kernel_derivx_x,
                                         borderType=borde).flatten()

        for fila, i in zip(auxiliar_x, range(np.shape(salida_x)[0])):
            salida_x[i] = cv2.filter2D(src=fila, ddepth=-1, kernel=kernel_derivx_y, borderType=borde).flatten()

        img_transpose = img.transpose()

        auxiliar_y = np.zeros(shape=np.shape(img_transpose), dtype=np.float64)
        salida_y = np.zeros(shape=np.shape(img_transpose), dtype=np.float64)

        for fila, i in zip(img_transpose, range(np.shape(auxiliar_y)[0])):
            auxiliar_y[i] = cv2.filter2D(src=fila, ddepth=cv2.CV_16S, kernel=kernel_derivy_x,
                                         borderType=borde).flatten()

        for fila, i in zip(auxiliar_y, range(np.shape(salida_y)[0])):
            salida_y[i] = cv2.filter2D(src=fila, ddepth=-1, kernel=kernel_derivy_y, borderType=borde).flatten()

        salida_y = salida_y.transpose()

        if normalize:
            salida_x = (salida_x - np.amin(salida_x)) / (np.amax(salida_x) - np.amin(salida_x))
            salida_y = (salida_y - np.amin(salida_y)) / (np.amax(salida_y) - np.amin(salida_y))

        if sigma == 1:
            return salida_x, salida_y
        else:
            x = convolucion_separable(img=salida_x, sigma=sigma - 1, kernel=None, tamanio=tamanio, borde=borde)
            y = convolucion_separable(img=salida_y, sigma=sigma - 1, kernel=None, tamanio=tamanio, borde=borde)

            if normalize:
                x = (x - np.amin(x)) / (np.amax(x) - np.amin(x))
                y = (y - np.amin(y)) / (np.amax(y) - np.amin(y))

            return x, y


def laplaciana_gaussiana(img, sigma, tamanio=3, borde=0, normalize=False):
    # La laplaciana es la suma de las segundas derivadas
    salida_x, salida_y = convolucion_derivada(img=img, sigma=sigma, derivada_x=2, derivada_y=2, tamanio=tamanio,
                                              borde=borde, normalize=normalize)

    # Multiplicamos por sigma para normalizar
    salida = sigma * (salida_x + salida_y)
    if normalize:
        salida = (salida - np.amin(salida)) / (np.amax(salida) - np.amin(salida))

    return salida


def piramide_gausiana(img, n_imagenes=4, borde=0):
    aux = copy.deepcopy(img)
    salida = [img]

    # Obtenemos las n_imagenes imagenes que necesitamos y las guardamos en el vector 
    # salida para luego montar el collage
    for i in range(n_imagenes):
        if borde == 0:
            aux = cv2.pyrDown(src=aux)
        else:
            aux = cv2.pyrDown(src=aux, borderType=borde)

        salida.append(aux)

    columnas = 0
    for elemento in salida:
        columnas += np.shape(elemento)[1]

    # Creamos el collage de forma manual
    matriz_final = np.full((np.shape(img)[0], columnas, 3), 255, dtype=np.float64)
    acumulador = 0
    for elemento in salida:
        for i in range(np.shape(elemento)[0]):
            for j in range(np.shape(elemento)[1]):
                matriz_final[i][j + acumulador] = elemento[i][j]

        acumulador += np.shape(elemento)[1]

    return matriz_final


def piramide_laplaciana(img, n_imagenes=4, borde=0):
    if len(np.shape(img)) == 3:
        filas, columnas, _ = np.shape(img)
    else:
        filas, columnas = np.shape(img)

    # Calculamos cuantas filas faltan hasta alcanzar la potencia de 2 más cercana
    contador = 0
    exponente = 0
    while exponente < filas:
        exponente = np.power(2, contador)
        contador += 1

    filas_restanes = exponente - filas

    # Calculamos cuantas columnas faltan hasta alcanzar la potencia de 2 más cercana
    contador = 0
    exponente = 0
    while exponente < columnas:
        exponente = np.power(2, contador)
        contador += 1

    columnas_restanes = exponente - columnas

    # Añadimos las columnas y filas restantes para no tener problemas con los escalados
    img_nueva = np.zeros(shape=(filas + filas_restanes, columnas + columnas_restanes, 3), dtype=np.array(img).dtype)
    for i in range(filas):
        for j in range(columnas):
            img_nueva[i][j] = img[i][j]

    salida = []

    # Calculamos la piramide Laplaciana
    for i in range(n_imagenes):
        if borde == 0:
            down = cv2.pyrDown(img_nueva)
            up = cv2.pyrUp(down, dstsize=(np.shape(img_nueva)[0], np.shape(img_nueva)[1]))
            salida.append(img_nueva - up)
            img_nueva = down
        else:
            down = cv2.pyrDown(img_nueva, borderType=borde)
            up = cv2.pyrUp(down, borderType=borde, dstsize=(np.shape(img_nueva)[0], np.shape(img_nueva)[1]))
            salida.append(img_nueva - up)
            img_nueva = down

    # Debemos borrar los zeros extras, para obtener un mejor resultado visual
    salida_procesada = []
    contador = 1
    for elemento in salida:
        salida_procesada.append(elemento[0:np.shape(elemento)[0] - (filas_restanes // contador),
                                0:np.shape(elemento)[1] - (columnas_restanes // contador)])
        contador += 1

    columnas = 0
    for elemento in salida_procesada:
        columnas += np.shape(elemento)[1]

    # Creamos el collage
    matriz_final = np.full((np.shape(salida_procesada[0])[0], columnas, 3), 255, dtype=np.float64)
    acumulador = 0
    for elemento in salida_procesada:
        for i in range(np.shape(elemento)[0]):
            for j in range(np.shape(elemento)[1]):
                matriz_final[i][j + acumulador] = elemento[i][j]

        acumulador += np.shape(elemento)[1]

    return matriz_final


def imagen_hibrida(img_1, img_2, sigma_1, sigma_2, tamanio=3, borde=0, todas=False):
    # Frecuencias altas = imagen - frecuencias bajas
    frecuencias_altas = img_1 - convolucion_separable(img=img_1, sigma=sigma_1, tamanio=tamanio, borde=borde,
                                                      normalize=False)
    frecuencias_bajas = convolucion_separable(img=img_2, sigma=sigma_2, tamanio=tamanio, borde=borde, normalize=False)

    if todas:
        matriz_final = np.full((np.shape(img_1)[0], np.shape(img_1)[1] * 3, 3), 255, dtype=np.float64)

        imagenes = [frecuencias_altas, np.array(frecuencias_altas + frecuencias_bajas, dtype=np.uint8),
                    frecuencias_bajas]
        acumulador = 0
        for elemento in imagenes:
            for i in range(np.shape(elemento)[0]):
                for j in range(np.shape(elemento)[1]):
                    matriz_final[i][j + acumulador] = elemento[i][j]

            acumulador += np.shape(elemento)[1]

        return matriz_final
    else:
        return np.array(frecuencias_altas + frecuencias_bajas, dtype=np.uint8)


# Bonus
def mascara_gausiana(sigma, tamanio=3):
    def fx(x, sigma):
        return math.exp(-0.5 * (x ** 2 / sigma ** 2))

    kernel = list(range(-tamanio * sigma, tamanio * sigma + 1))
    kernel = np.array([fx(m, sigma) for m in kernel])
    # Lo devolvemos normalizado
    return np.divide(kernel, np.sum(kernel))


def aniadir_borde_reflejado(src, espacio):
    # Cogemos el trozo izquierdo a reflejar
    izquierda = src[0:espacio]
    # Cogemos el trozo derecho a reflejar
    derecha = (src[-espacio:])[::-1]

    # Concatenamos los 3 trozos y los devolvemos
    return np.append(np.append(izquierda, src, axis=0), derecha, axis=0)


def convolucion_1d(signal, kernel):
    signal_bordes = aniadir_borde_reflejado(src=signal, espacio=len(kernel) // 2)

    signal_bordes = signal_bordes.flatten()
    salida = np.zeros(shape=len(signal_bordes))

    # Paseamos la máscar por el vector señal pero sin contar sus bordes
    for i in range(len(kernel) // 2, len(salida) - len(kernel) // 2):
        salida[i] = np.sum(
            np.multiply(kernel, signal_bordes[i - len(kernel) // 2:i + len(kernel) // 2 + 1]))

    return salida[len(kernel) // 2:-len(kernel) // 2 + 1]


def convolucion_separable_manual(img, sigma, kernel=None, tamanio=3, normalize=False):
    if kernel is None:
        kernel = mascara_gausiana(sigma=sigma, tamanio=tamanio)

        kernel = kernel.flatten()

    if len(np.shape(img)) == 3:
        canal_1, canal_2, canal_3 = cv2.split(img)

        auxiliar_1 = np.zeros(shape=np.shape(canal_1), dtype=np.float64)
        auxiliar_2 = np.zeros(shape=np.shape(canal_2), dtype=np.float64)
        auxiliar_3 = np.zeros(shape=np.shape(canal_3), dtype=np.float64)

        filas = np.shape(auxiliar_1)[0]

        for i in range(0, filas):
            auxiliar_1[i] = convolucion_1d(signal=canal_1[i], kernel=kernel)
            auxiliar_2[i] = convolucion_1d(signal=canal_2[i], kernel=kernel)
            auxiliar_3[i] = convolucion_1d(signal=canal_3[i], kernel=kernel)

        auxiliar_1 = np.array(auxiliar_1).transpose()
        auxiliar_2 = np.array(auxiliar_2).transpose()
        auxiliar_3 = np.array(auxiliar_3).transpose()

        salida_1 = np.zeros(shape=np.shape(auxiliar_1), dtype=np.float64)
        salida_2 = np.zeros(shape=np.shape(auxiliar_2), dtype=np.float64)
        salida_3 = np.zeros(shape=np.shape(auxiliar_3), dtype=np.float64)

        filas = np.shape(auxiliar_1)[0]

        for i in range(0, filas):
            salida_1[i] = convolucion_1d(signal=auxiliar_1[i], kernel=kernel)
            salida_2[i] = convolucion_1d(signal=auxiliar_2[i], kernel=kernel)
            salida_3[i] = convolucion_1d(signal=auxiliar_3[i], kernel=kernel)

        salida_1 = np.array(salida_1).transpose()
        salida_2 = np.array(salida_2).transpose()
        salida_3 = np.array(salida_3).transpose()

        if normalize:
            salida_1 = (salida_1 - np.amin(salida_1)) / (np.amax(salida_1) - np.amin(salida_1))
            salida_2 = (salida_2 - np.amin(salida_2)) / (np.amax(salida_2) - np.amin(salida_2))
            salida_3 = (salida_3 - np.amin(salida_3)) / (np.amax(salida_3) - np.amin(salida_3))

        salida = cv2.merge([salida_1, salida_2, salida_3])

        return salida
    else:
        auxiliar_1 = np.zeros(shape=np.shape(img), dtype=np.float64)

        filas = np.shape(auxiliar_1)[0]

        for i in range(0, filas):
            auxiliar_1[i] = convolucion_1d(signal=img[i], kernel=kernel)

        auxiliar_1 = np.array(auxiliar_1).transpose()

        salida_1 = np.zeros(shape=np.shape(auxiliar_1), dtype=np.float64)

        filas = np.shape(auxiliar_1)[0]

        for i in range(0, filas):
            salida_1[i] = convolucion_1d(signal=auxiliar_1[i], kernel=kernel)

        salida = salida_1.transpose()
        if normalize:
            salida = (salida - np.amin(salida)) / (np.amax(salida) - np.amin(salida))

        return salida


def pyrdown_manual(src):
    src_filtro = convolucion_separable_manual(img=src, sigma=2, kernel=None, tamanio=3, normalize=False)
    # Devolvemos sólo las columnas impares
    return src_filtro[1::2, 1::2]


def piramide_gausiana_manual(img, n_imagenes=5):
    aux = copy.deepcopy(img)
    salida = [img]

    for i in range(n_imagenes):
        aux = pyrdown_manual(src=aux)
        salida.append(aux)

    columnas = 0
    for elemento in salida:
        columnas += np.shape(elemento)[1]

    matriz_final = np.full((np.shape(img)[0], columnas, 3), 255, dtype=np.float64)
    acumulador = 0
    for elemento in salida:
        for i in range(np.shape(elemento)[0]):
            for j in range(np.shape(elemento)[1]):
                matriz_final[i][j + acumulador] = elemento[i][j]

        acumulador += np.shape(elemento)[1]

    return matriz_final


def imagen_hibrida_manual(img_1, img_2, sigma_1, sigma_2, tamanio=3, todas=False):
    # Frecuencias altas = imagen - frecuencias bajas
    frecuencias_altas = img_1 - convolucion_separable_manual(img=img_1, sigma=sigma_1, tamanio=tamanio,
                                                             normalize=False)
    frecuencias_bajas = convolucion_separable_manual(img=img_2, sigma=sigma_2, tamanio=tamanio, normalize=False)

    if todas:
        matriz_final = np.full((np.shape(img_1)[0], np.shape(img_1)[1] * 3, 3), 255, dtype=np.float64)

        imagenes = [frecuencias_altas, np.array(frecuencias_altas + frecuencias_bajas, dtype=np.uint8),
                    frecuencias_bajas]
        acumulador = 0
        for elemento in imagenes:
            for i in range(np.shape(elemento)[0]):
                for j in range(np.shape(elemento)[1]):
                    matriz_final[i][j + acumulador] = elemento[i][j]

            acumulador += np.shape(elemento)[1]

        return matriz_final
    else:
        return np.array(frecuencias_altas + frecuencias_bajas, dtype=np.uint8)


def main():
    img = cv2.imread('./data/bicycle.bmp', cv2.IMREAD_GRAYSCALE)
    
    # Ejercicio 1
    # Apartado a.
    plot_images(imagenes=[img, img, img, img], nombres=["img1", "img2", "img3", "img4"], num_filas=2,
                num_columnas=2, name_windows="Apartado a. Imágenes:")

    # Apartado b.
    imagenes = [convolucion(img=img, sigma=1, tamanio=3, borde=cv2.BORDER_CONSTANT),
                convolucion(img=img, sigma=1, tamanio=3, borde=cv2.BORDER_REPLICATE),
                convolucion(img=img, sigma=3, tamanio=3, borde=cv2.BORDER_CONSTANT),
                convolucion(img=img, sigma=3, tamanio=3, borde=cv2.BORDER_REPLICATE)]

    nombres = ["BORDER_CONSTANT. σ = " + str(1), "BORDER_REPLICATE. σ = " + str(1), "BORDER_CONSTANT. σ = " + str(3),
               "BORDER_REPLICATE. σ = " + str(3)]

    plot_images(imagenes=imagenes, nombres=nombres, num_columnas=2, num_filas=2,
                name_windows="Apartado b.")

    # Apartado c.
    imagenes = [
        convolucion_separable(img=img, sigma=1, kernel=None, tamanio=3, borde=cv2.BORDER_CONSTANT, normalize=True),
        convolucion_separable(img=img, sigma=1, kernel=None, tamanio=3, borde=cv2.BORDER_REPLICATE, normalize=True),
        convolucion_separable(img=img, sigma=3, kernel=None, tamanio=3, borde=cv2.BORDER_CONSTANT, normalize=True),
        convolucion_separable(img=img, sigma=3, kernel=None, tamanio=3, borde=cv2.BORDER_REPLICATE, normalize=True)]

    nombres = ["BORDER_CONSTANT. σ = " + str(1), "BORDER_REPLICATE. σ = " + str(1),
               "BORDER_CONSTANT. σ = " + str(3), "BORDER_REPLICATE. σ = " + str(3)]

    plot_images(imagenes=imagenes, nombres=nombres, num_columnas=2, num_filas=2,
                name_windows="Apartado c.")
    
    # Apartado d.
    res = convolucion_derivada(img=img, sigma=1, derivada_x=1, derivada_y=1, tamanio=3, borde=cv2.BORDER_CONSTANT)
    res_2 = convolucion_derivada(img=img, sigma=3, derivada_x=1, derivada_y=1, tamanio=3, borde=cv2.BORDER_CONSTANT)
    imagenes = [res[0], res[1], res_2[0], res_2[1]]
    nombres = ["σ = 1 : dx", "σ = 1 : dy", "σ = 3 : dx", "σ = 3 : dy"]
    plot_images(imagenes=imagenes, nombres=nombres, num_columnas=2, num_filas=2,
                name_windows="Apartado d: BORDER_CONSTANT.")

    res = convolucion_derivada(img=img, sigma=1, derivada_x=1, derivada_y=1, tamanio=3, borde=cv2.BORDER_REFLECT)
    res_2 = convolucion_derivada(img=img, sigma=3, derivada_x=1, derivada_y=1, tamanio=3, borde=cv2.BORDER_REFLECT)
    imagenes = [res[0], res[1], res_2[0], res_2[1]]
    nombres = ["σ = 1 : dx", "σ = 1 : dy", "σ = 3 : dx", "σ = 3 : dy"]
    plot_images(imagenes=imagenes, nombres=nombres, num_columnas=2, num_filas=2,
                name_windows="Apartado d: BORDER_REFLECT.")

    # Apartado e.
    res = convolucion_derivada(img=img, sigma=1, derivada_x=2, derivada_y=2, tamanio=3, borde=cv2.BORDER_CONSTANT)
    res_2 = convolucion_derivada(img=img, sigma=3, derivada_x=2, derivada_y=2, tamanio=3, borde=cv2.BORDER_CONSTANT)
    imagenes = [res[0], res[1], res_2[0], res_2[1]]
    nombres = ["σ = 1 : dx", "σ = 1 : dy", "σ = 3 : dx", "σ = 3 : dy"]
    plot_images(imagenes=imagenes, nombres=nombres, num_columnas=2, num_filas=2,
                name_windows="Apartado e: BORDER_CONSTANT.")

    res = convolucion_derivada(img=img, sigma=1, derivada_x=2, derivada_y=2, tamanio=3, borde=cv2.BORDER_REFLECT)
    res_2 = convolucion_derivada(img=img, sigma=3, derivada_x=2, derivada_y=2, tamanio=3, borde=cv2.BORDER_REFLECT)
    imagenes = [res[0], res[1], res_2[0], res_2[1]]
    nombres = ["σ = 1 : dx", "σ = 1 : dy", "σ = 3 : dx", "σ = 3 : dy"]
    plot_images(imagenes=imagenes, nombres=nombres, num_columnas=2, num_filas=2,
                name_windows="Apartado e: BORDER_REFLECT.")

    # Apartado f.
    imagenes = [laplaciana_gaussiana(img=img, sigma=1, tamanio=3, borde=cv2.BORDER_CONSTANT, normalize=True),
                laplaciana_gaussiana(img=img, sigma=1, tamanio=3, borde=cv2.BORDER_REFLECT, normalize=True),
                laplaciana_gaussiana(img=img, sigma=3, tamanio=3, borde=cv2.BORDER_CONSTANT, normalize=True),
                laplaciana_gaussiana(img=img, sigma=3, tamanio=3, borde=cv2.BORDER_REFLECT, normalize=True)]

    nombres = ["BORDER_CONSTANT. σ = " + str(1), "BORDER_REFLECT. σ = " + str(1),
               "BORDER_CONSTANT. σ = " + str(3), "BORDER_REFLECT. σ = " + str(3)]

    plot_images(imagenes=imagenes, nombres=nombres, num_columnas=2, num_filas=2, name_windows="Apartado f.")

    # Apartado g.
    piramide = piramide_gausiana(img=img, n_imagenes=4, borde=cv2.BORDER_CONSTANT)
    plot_images(imagenes=[piramide], nombres=["Original y 4 muestreos"], num_columnas=1, num_filas=1,
                name_windows="Apartado g: Piramide Gausiana.")

    # Apartado h.
    piramide = piramide_laplaciana(img=img, n_imagenes=4, borde=cv2.BORDER_CONSTANT)
    plot_images(imagenes=[piramide], nombres=["4 muestreos"], num_columnas=1, num_filas=1,
                name_windows="Apartado h: Piramide Laplaciana.")

    # Ejercicio 2: Imagenes hibridas
    cat = cv2.imread('./data/cat.bmp', cv2.IMREAD_GRAYSCALE)
    dog = cv2.imread('./data/dog.bmp', cv2.IMREAD_GRAYSCALE)

    einstein = cv2.imread('./data/einstein.bmp', cv2.IMREAD_GRAYSCALE)
    marilyn = cv2.imread('./data/marilyn.bmp', cv2.IMREAD_GRAYSCALE)

    fish = cv2.imread('./data/fish.bmp', cv2.IMREAD_GRAYSCALE)
    submarine = cv2.imread('./data/submarine.bmp', cv2.IMREAD_GRAYSCALE)

    plane = cv2.imread('./data/plane.bmp', cv2.IMREAD_GRAYSCALE)
    bird = cv2.imread('./data/bird.bmp', cv2.IMREAD_GRAYSCALE)

    bicycle = cv2.imread('./data/bicycle.bmp', cv2.IMREAD_GRAYSCALE)
    motorcycle = cv2.imread('./data/motorcycle.bmp', cv2.IMREAD_GRAYSCALE)

    einstein_marilyn = imagen_hibrida(img_1=einstein, img_2=marilyn, sigma_1=3, sigma_2=3, tamanio=3,
                                      borde=cv2.BORDER_REFLECT, todas=True)
    plot_images(imagenes=[einstein_marilyn], nombres=["einstein σ = 3 - marilyn σ = 3"], num_columnas=1, num_filas=1,
                name_windows="Imagenes hibridas.")

    cat_dog = imagen_hibrida(img_1=cat, img_2=dog, sigma_1=7, sigma_2=4, tamanio=3, borde=cv2.BORDER_REFLECT,
                             todas=True)
    plot_images(imagenes=[cat_dog], nombres=["dog σ = 7 - cat σ = 4"], num_columnas=1, num_filas=1,
                name_windows="Imagenes hibridas.")

    fish_submarine = imagen_hibrida(img_1=fish, img_2=submarine, sigma_1=2, sigma_2=4, tamanio=3,
                                    borde=cv2.BORDER_REFLECT, todas=True)
    plot_images(imagenes=[fish_submarine], nombres=["fish σ = 2 - submarine σ = 4"], num_columnas=1, num_filas=1,
                name_windows="Imagenes hibridas.")

    plane_bird = imagen_hibrida(img_1=plane, img_2=bird, sigma_1=4, sigma_2=2, tamanio=3, borde=cv2.BORDER_REFLECT,
                                todas=True)
    plot_images(imagenes=[plane_bird], nombres=["plane σ = 4 - bird σ = 2"], num_columnas=1, num_filas=1,
                name_windows="Imagenes hibridas.")

    bicycle_motorcycle = imagen_hibrida(img_1=bicycle, img_2=motorcycle, sigma_1=2, sigma_2=2, tamanio=3,
                                        borde=cv2.BORDER_REFLECT, todas=True)
    plot_images(imagenes=[bicycle_motorcycle], nombres=["bycicle σ = 2 - motorcycle σ = 2"], num_columnas=1,
                num_filas=1,
                name_windows="Imagenes hibridas.")
    
    # Bonus
    # 1, 2 y 3.
    imagenes = [convolucion_separable_manual(img=img, sigma=1, kernel=None, tamanio=3, normalize=True),
                convolucion_separable_manual(img=img, sigma=1, kernel=None, tamanio=3, normalize=True),
                convolucion_separable_manual(img=img, sigma=3, kernel=None, tamanio=3, normalize=True),
                convolucion_separable_manual(img=img, sigma=3, kernel=None, tamanio=3, normalize=True)]

    nombres = ["BORDER_CONSTANT. σ = " + str(1), "BORDER_REFLECT. σ = " + str(1),
               "BORDER_CONSTANT. σ = " + str(3), "BORDER_REFLECT. σ = " + str(3)]

    plot_images(imagenes=imagenes, nombres=nombres, num_columnas=2, num_filas=2,
                name_windows="Ej. 1, 2 y 3 del bonus.")

    # Ejercicio 4.
    einstein_marilyn = imagen_hibrida(img_1=einstein, img_2=marilyn, sigma_1=3, sigma_2=3, tamanio=3,
                                      borde=cv2.BORDER_REFLECT,
                                      todas=False)
    cat_dog = imagen_hibrida(img_1=cat, img_2=dog, sigma_1=7, sigma_2=4, tamanio=3, borde=cv2.BORDER_REFLECT,
                             todas=False)
    fish_submarine = imagen_hibrida(img_1=fish, img_2=submarine, sigma_1=2, sigma_2=4, tamanio=3,
                                    borde=cv2.BORDER_REFLECT, todas=False)
    plane_bird = imagen_hibrida(img_1=plane, img_2=bird, sigma_1=4, sigma_2=2, tamanio=3, borde=cv2.BORDER_REFLECT,
                                todas=False)
    bicycle_motorcycle = imagen_hibrida(img_1=bicycle, img_2=motorcycle, sigma_1=2, sigma_2=2, tamanio=3,
                                        borde=cv2.BORDER_REFLECT, todas=False)

    piramide = piramide_gausiana_manual(img=cat_dog, n_imagenes=5)
    plot_images(imagenes=[piramide], nombres=["cat - dog"], num_columnas=1, num_filas=1, name_windows="Ejercicio 4.")

    piramide = piramide_gausiana_manual(img=einstein_marilyn, n_imagenes=5)
    plot_images(imagenes=[piramide], nombres=["einstein - marilyn"], num_columnas=1, num_filas=1,
                name_windows="Ejercicio 4.")

    piramide = piramide_gausiana_manual(img=fish_submarine, n_imagenes=5)
    plot_images(imagenes=[piramide], nombres=["fish - submarine"], num_columnas=1, num_filas=1,
                name_windows="Ejercicio 4.")

    piramide = piramide_gausiana_manual(img=plane_bird, n_imagenes=5)
    plot_images(imagenes=[piramide], nombres=["plane - bird"], num_columnas=1, num_filas=1, name_windows="Ejercicio 4.")

    piramide = piramide_gausiana_manual(img=bicycle_motorcycle, n_imagenes=5)
    plot_images(imagenes=[piramide], nombres=["bicycle - motorcycle"], num_columnas=1, num_filas=1,
                name_windows="Ejercicio 4.")

    # Ejercicio 5
    cat = cv2.imread('./data/cat.bmp', cv2.IMREAD_COLOR)
    dog = cv2.imread('./data/dog.bmp', cv2.IMREAD_COLOR)

    einstein = cv2.imread('./data/einstein.bmp', cv2.IMREAD_COLOR)
    marilyn = cv2.imread('./data/marilyn.bmp', cv2.IMREAD_COLOR)

    fish = cv2.imread('./data/fish.bmp', cv2.IMREAD_COLOR)
    submarine = cv2.imread('./data/submarine.bmp', cv2.IMREAD_COLOR)

    plane = cv2.imread('./data/plane.bmp', cv2.IMREAD_COLOR)
    bird = cv2.imread('./data/bird.bmp', cv2.IMREAD_COLOR)

    bicycle = cv2.imread('./data/bicycle.bmp', cv2.IMREAD_COLOR)
    motorcycle = cv2.imread('./data/motorcycle.bmp', cv2.IMREAD_COLOR)

    imagenes = imagen_hibrida_manual(img_1=einstein, img_2=marilyn, sigma_1=3, sigma_2=3, tamanio=3)
    plot_images(imagenes=[imagenes], nombres=["einstein σ = 3 - marilyn σ = 3"], num_columnas=1,
                num_filas=1, name_windows="Bonus: Ejercicio 5")

    imagenes = imagen_hibrida_manual(img_1=cat, img_2=dog, sigma_1=7, sigma_2=4, tamanio=3)
    plot_images(imagenes=[imagenes], nombres=["dog σ = 7 - cat σ = 4"], num_columnas=1,
                num_filas=1, name_windows="Bonus: Ejercicio 5")

    imagenes = imagen_hibrida_manual(img_1=fish, img_2=submarine, sigma_1=2, sigma_2=4, tamanio=3)
    plot_images(imagenes=[imagenes], nombres=["fish σ = 2 - submarine σ = 4"], num_columnas=1,
                num_filas=1, name_windows="Bonus: Ejercicio 5")

    imagenes = imagen_hibrida_manual(img_1=plane, img_2=bird, sigma_1=4, sigma_2=2, tamanio=3)
    plot_images(imagenes=[imagenes], nombres=["plane σ = 4 - bird σ = 2"], num_columnas=1,
                num_filas=1, name_windows="Bonus: Ejercicio 5")

    imagenes = imagen_hibrida_manual(img_1=bicycle, img_2=motorcycle, sigma_1=2, sigma_2=2, tamanio=3)
    plot_images(imagenes=[imagenes], nombres=["bycicle σ = 2 - motorcycle σ = 2"], num_columnas=1,
                num_filas=1, name_windows="Bonus: Ejercicio 5")


if __name__ == "__main__":
    main()
