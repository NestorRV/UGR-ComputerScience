## ----setup, include=FALSE------------------------------------------------
knitr::opts_chunk$set(echo = TRUE)

## ----utilidades gráficas-------------------------------------------------
set.seed(3) # semilla para los aleatorios

# por defecto genera 2 puntos entre [0,1] de 2 dimensiones
simula_unif = function (N=2,dims=2, rango = c(0,1)){
  m = matrix(runif(N*dims, min=rango[1], max=rango[2]), nrow = N, ncol=dims, byrow=T)
  m
}

# función simula_gaus(N, dim, sigma) que genera un
# conjunto de longitud N de vectores de dimensión dim, conteniendo números
# aleatorios gaussianos de media 0 y varianzas dadas por el vector sigma.
# por defecto genera 2 puntos de 2 dimensiones
simula_gaus = function(N=2,dim=2,sigma){
  if (missing(sigma)) stop("Debe dar un vector de varianzas")
  sigma = sqrt(sigma)  # para la generación se usa sd, y no la varianza
  if(dim != length(sigma)) stop ("El numero de varianzas es distinto de la dimensión")
  simula_gauss1 = function() rnorm(dim, sd = sigma) # genera 1 muestra, con las
                                                    # desviaciones especificadas
  m = t(replicate(N,simula_gauss1())) # repite N veces, simula_gauss1 y se hace la
                                      # traspuesta
  m
}

#  simula_recta(intervalo) una funcion que calcula los parámetros
#  de una recta aleatoria, y = ax + b, que corte al cuadrado [-50,50]x[-50,50]
#  (Para calcular la recta se simulan las coordenadas de 2 ptos dentro del
#  cuadrado y se calcula la recta que pasa por ellos),
#  se pinta o no segun el valor de parametro visible
simula_recta = function (intervalo = c(-1,1), visible=F){
   ptos = simula_unif(2,2,intervalo) # se generan 2 puntos
   a = (ptos[1,2] - ptos[2,2]) / (ptos[1,1]-ptos[2,1]) # calculo de la pendiente
   b = ptos[1,2]-a*ptos[1,1]  # calculo del punto de corte

   if (visible) {  # pinta la recta y los 2 puntos
       if (dev.cur()==1) # no esta abierto el dispositivo lo abre con plot
           plot(1, type="n", xlim=intervalo, ylim=intervalo)
       points(ptos,col=3)  #pinta en verde los puntos
       abline(b,a,col=3)   # y la recta
   }
   c(a,b) # devuelve el par pendiente y punto de corte
}

## ----1.1-----------------------------------------------------------------
datosA = simula_unif(50, 2, c(-50,50))
datosB = simula_gaus(50, 2, c(5,7))
plot(datosA)
plot(datosB)

## ----1.2-----------------------------------------------------------------
# Función auxiliar para generar ruido en etiquetas
asignarRuido=function(etiquetas, porcentaje=10){
	positivas = which(etiquetas==1)
	negativas = which(etiquetas==-1)
	positivas = sample(positivas, length(positivas)*0.02*porcentaje, replace=FALSE)
	negativas = sample(negativas, length(negativas)*0.02*porcentaje, replace=FALSE)
	etiquetas[positivas]=-1
	etiquetas[negativas]=1
	etiquetas
}

# Generamos 100 datos de dimensión 2 en el rango -50,50
datos1 = simula_unif(100, 2, c(-50,50))
# Generamos la recta que va a determinar como clasificamos los datos
recta = simula_recta(c(-50,50))
# Vamos a ver los datos que hemos generado junto con la recta:
plot(datos1)
abline(recta[2], recta[1])
# Para realizar la clasificación voy a usar la siguiente idea:
# Para cada punto calculo el valor y de la recta en la coordenada x del punto y realizo
# la diferencia entre el valor y del punto y el valor y de la recta. Si la diferencia
# es positiva (valor del ver con la función sign()) el punto está por encima de la recta
# y si es negativa, el punto está por debajo de la recta.
# Función que calcula el valor de y para un punto x seguún la recta y = pendiente*x+valor
valor_y = function(x, pendiente, valor){
  y = pendiente*x+valor
  y
}
# Aplicamos la idea comentada anteriormente para generar las etiquetas
etiquetas = sign(valor_y(datos1[,1], recta[1], recta[2])-datos1[,2])
# Pintamos los datos junto con las etiquetas (Ojo, las etiquetas son -1 y 1 pero los
# colores no pueden ser negativos, por eso le sumamos 5)
plot(datos1, col=etiquetas+5)
# Pintamos la recta para comprobar que están bien clasificados
abline(recta[2], recta[1])
# Generamos unas nuevas etiquetas con ruido
etiquetas.R = asignarRuido(etiquetas, 10)
# Pintar dos gráficos
par(mfrow=c(1,2))
# Primero pintamos las que no tienen ruido
plot(datos1, col=etiquetas+5)
abline(recta[2], recta[1])
# Y a continuación las que tienen ruido, para comparar correctamente
plot(datos1, col=etiquetas.R+5)
abline(recta[2], recta[1])
# Pintar sólo un gráfico
par(mfrow=c(1,1))

## ----1.3-----------------------------------------------------------------
# funcion para pintar la frontera de la función a la que se pueden añadir puntos,
# y etiquetas
pintar_frontera = function(f,rango=c(-50,50)) {
   x=y=seq(rango[1],rango[2],length.out = 200)
   z = outer(x,y,FUN=f)
  if (dev.cur()==1) # no esta abierto el dispositivo lo abre con plot
           plot(1, type="n", xlim=rango, ylim=rango)
   contour(x,y,z, levels=0, drawlabels=FALSE,xlim=rango, ylim=rango, xlab="x", ylab="y")
}

# Ejemplo de llamada a una funcion f1_xy que hemos de definir
# pintar_frontera(f1_xy)

# Funciones dadas por el ejercicio
funcion1 = function(x, y) (x-10)^2 + (y-20)^2 - 400
funcion2 = function(x, y) (0.5*(x+10)^2 + (y-20)^2 - 400)
funcion3 = function(x, y) (0.5*(x-10)^2 - (y+20)^2 - 400)
funcion4 = function(x, y) (y-20*x^2 - 5*x+3)

e1 = sign(funcion1(datos1[,1], datos1[,2]))
e2 = sign(funcion2(datos1[,1], datos1[,2]))
e3 = sign(funcion3(datos1[,1], datos1[,2]))
e4 = sign(funcion4(datos1[,1], datos1[,2]))

# Pintamos con ruido
par(mfrow=c(1,2))

plot(datos1, col=etiquetas.R+5)
abline(recta[2], recta[1])
pintar_frontera(funcion1); points(x=datos1[,1], y=datos1[,2], col=e1+5)

plot(datos1, col=etiquetas.R+5)
abline(recta[2], recta[1])
pintar_frontera(funcion2); points(x=datos1[,1], y=datos1[,2], col=e2+5)

plot(datos1, col=etiquetas.R+5)
abline(recta[2], recta[1])
pintar_frontera(funcion3); points(x=datos1[,1], y=datos1[,2], col=e3+5)

plot(datos1, col=etiquetas.R+5)
abline(recta[2], recta[1])
pintar_frontera(funcion4); points(x=datos1[,1], y=datos1[,2], col=e4+5)

## ----2.1-----------------------------------------------------------------
ajusta_PLA = function(datos, label, max_iter, vini){
  seguirIterando = TRUE
  w = vini
  iter = 0
  # Debemos añadir una columna de unos para que no de problemas al realizar el producto
  # vectorial (con el debuger (browser) se puede ver el error, ya que datos[i,]
  # y w no tienen el mismo tamaño)
  datos = cbind(1,datos)
  # Recorremos todos los datos mientras se produzca algun cambio
  # en algun peso y no hayamos dado el número máximo de iteraciones
  while (seguirIterando && iter < max_iter){
    seguirIterando = FALSE
    for (i in sample(1:nrow(datos))){
      if (sign(crossprod(w, datos[i,])) != label[i]){
        # Si entramos aquí, se ha producido un cambio en algún peso, así que
        # debemos dar una iteración más
        seguirIterando = TRUE
        w = w + label[i] * datos[i,]
      }
    }
    iter = iter + 1
  }
  # Devolvemos el vector de pesos, el número de iteraciones y los coeficientes
  # del hiperplano
  resultado = list(w, iter, c(-w[1]/w[3], -w[2]/w[3]))
  resultado
}

## ----2.2-----------------------------------------------------------------
ejecutarPLA = function(i) {solucion = ajusta_PLA(datos1, etiquetas, 1000, c(0,0,0))
                          solucion[2]}
ejecutarPLA_aleatorio = function(i) {pesos = c(simula_unif(3, 1, c(0,1)))
                          solucion = ajusta_PLA(datos1, etiquetas, 1000, pesos)
                          solucion[2]}
resultados = mapply(ejecutarPLA, 1:10)
mean(unlist(resultados))
resultados = mapply(ejecutarPLA_aleatorio, 1:10)
mean(unlist(resultados))

## ----2.3-----------------------------------------------------------------
ajusta_PLA(datos1, etiquetas.R, 500, c(0,0,0))
ejecutarPLA = function(i) {pesos = c(simula_unif(3, 1, c(0,1)))
                          solucion = ajusta_PLA(datos1, etiquetas.R, 500, pesos)
                          solucion[2]}
resultados = mapply(ejecutarPLA, 1:10)
mean(unlist(resultados))


ajusta_PLA(datos1, etiquetas.R, 1500, c(0,0,0))
ejecutarPLA = function(i) {pesos = c(simula_unif(3, 1, c(0,1)))
                          solucion = ajusta_PLA(datos1, etiquetas.R, 1500, pesos)
                          solucion[2]}
resultados = mapply(ejecutarPLA, 1:10)
mean(unlist(resultados))

## ----3.1-----------------------------------------------------------------
# Leemos los datos
digit.train = read.table("./datos/zip.train", quote="\"", comment.char="", 
                         stringsAsFactors=FALSE)

digitos1_5.train = digit.train[digit.train$V1==1 | digit.train$V1==5,]
etiquetasTrain = digitos1_5.train[,1]
ndigitos = nrow(digitos1_5.train)

# se retira la clase y se monta una matriz 3D: 599*16*16
datos1_5Train = array(unlist(subset(digitos1_5.train,select=-V1)),c(ndigitos,16,16))
rm(digit.train)
rm(digitos1_5.train)

# Para visualizar los 4 primeros
## ------------------------------------------------------------------------

par(mfrow=c(2,2))
for(i in 1:4){
  imagen = datos1_5Train[i,,16:1] # se rota para verlo bien
  image(z=imagen)
}

## ----3.2-----------------------------------------------------------------
simetria <- function(A){
  A = abs(A-A[,ncol(A):1])
  -mean(A)
}

# Aplicamos la función para calcular la simetria y la intensidad a cada matriz
# de la lista de matrices
datos1_5Train.media = apply(datos1_5Train, 1, mean)
datos1_5Train.simetria = apply(datos1_5Train, 1, simetria)
plot(datos1_5Train.media, datos1_5Train.simetria,
     xlab="Intensidad", ylab="Simetria", col=etiquetasTrain)

## ----3.3-----------------------------------------------------------------
# Se necesita el paquete matrixcalc. En caso de no estar instalado, se instalará
Regress_Lin = function(datos, label) {
  # Nos aseguramos de que vamos a trabar con matrices
  datos = as.matrix(datos)
  label = as.matrix(label)

  x = t(datos) %*% datos
  matrices = svd(x)
  auxiliar = matrices$v%*%diag(1/matrices$d)%*%t(matrices$v)
  pseudo = auxiliar%*%t(datos)
  w = pseudo%*%label
  w
  unlist(w)
}

datosTrain = matrix(c(rep(1, length(datos1_5Train.simetria)), datos1_5Train.media, 
                    datos1_5Train.simetria), nrow = length(datos1_5Train.simetria))
modelo = Regress_Lin(datosTrain, etiquetasTrain)
plot(datos1_5Train.media, datos1_5Train.simetria, col=etiquetasTrain)
abline(-modelo[1]/modelo[3], -modelo[2]/modelo[3])

## ------------------------------------------------------------------------
etiquetasTrain

## ------------------------------------------------------------------------
etiquetasPositivasNegativas = replace(etiquetasTrain, etiquetasTrain==5, -1)
etiquetasPositivasNegativas

## ------------------------------------------------------------------------
modelo = Regress_Lin(datosTrain, etiquetasPositivasNegativas)
plot(datos1_5Train.media, datos1_5Train.simetria, 
     xlab="Intensidad", ylab="Simetria", col=etiquetasPositivasNegativas+5)
abline(-modelo[1]/modelo[3], -modelo[2]/modelo[3])

## ------------------------------------------------------------------------
calculadas = sign(t(modelo)%*%t(datosTrain))
diferencia = calculadas == etiquetasPositivasNegativas
Ein = length(diferencia[diferencia == FALSE]) / nrow(datosTrain)
Ein

## ------------------------------------------------------------------------
digit.test = read.table("./datos/zip.test", quote="\"", comment.char="", 
                        stringsAsFactors=FALSE)

digitos1_5.test = digit.test[digit.test$V1==1 | digit.test$V1==5,]
etiquetasTest = digitos1_5.test[,1]
ndigitos = nrow(digitos1_5.test)

# se retira la clase y se monta una matriz 3D: 599*16*16
datos1_5Test = array(unlist(subset(digitos1_5.test,select=-V1)),c(ndigitos,16,16))
rm(digit.test)
rm(digitos1_5.test)

datos1_5Test.media = apply(datos1_5Test, 1, mean)
datos1_5Test.simetria = apply(datos1_5Test, 1, simetria)
plot(datos1_5Test.media, datos1_5Test.simetria,
     xlab="Intensidad", ylab="Simetria", col=etiquetasTest)

# Debemos construir la misma matriz que en el ejercicio anterior
datosTest = matrix(c(rep(1, length(datos1_5Test.simetria)), datos1_5Test.media, 
                  datos1_5Test.simetria), nrow = length(datos1_5Test.simetria))
# Tener cuidado con las etiquetas
etiquetasPositivasNegativas = replace(etiquetasTest, etiquetasTest==5, -1)
# Y repetir el proceso, pero con los pesos ya calculados
plot(datos1_5Test.media, datos1_5Test.simetria, 
     xlab="Intensidad", ylab="Simetria", col=etiquetasPositivasNegativas+5)
abline(-modelo[1]/modelo[3], -modelo[2]/modelo[3])

## ------------------------------------------------------------------------
calculadas = sign(t(modelo)%*%t(datosTest))
diferencia = calculadas == etiquetasPositivasNegativas
Eout = length(diferencia[diferencia == FALSE]) / nrow(datosTest)
Eout

## ------------------------------------------------------------------------
entrenamiento = simula_unif(1000, 2, c(-1,1))
plot(entrenamiento)

## ------------------------------------------------------------------------
f = function(x1, x2) (x1+0.2)^2 + (x2)^2 - 0.6
e = sign(f(entrenamiento[,1], entrenamiento[,2]))
e.R = asignarRuido(e, 10)
plot(entrenamiento, col=e.R+5)

## ------------------------------------------------------------------------
datosExperimento = matrix(c(rep(1, length(entrenamiento[,2])), entrenamiento[,1], 
                            entrenamiento[,2]), nrow = length(entrenamiento[,2]))
modelo = Regress_Lin(datosExperimento, e.R)
plot(entrenamiento[,1], entrenamiento[,2], col=e.R+5)
abline(-modelo[1]/modelo[3], -modelo[2]/modelo[3])

calculadas = sign(t(modelo)%*%t(datosExperimento))
diferencia = calculadas == e.R
Ein = length(diferencia[diferencia == FALSE]) / nrow(datosExperimento)
Ein

## ------------------------------------------------------------------------
experimento1 = function(i) {
  f = function(x1, x2) (x1+0.2)^2 + (x2)^2 - 0.6
  entrenamiento = simula_unif(1000, 2, c(-1,1))
  eTrain = sign(f(entrenamiento[,1], entrenamiento[,2]))
  eTrain.R = asignarRuido(eTrain, 10)
  
  datosTrain = matrix(c(rep(1, length(entrenamiento[,2])), entrenamiento[,1], 
                            entrenamiento[,2]), nrow = length(entrenamiento[,2]))
  modelo = Regress_Lin(datosTrain, eTrain.R)

  calculadas = sign(t(modelo)%*%t(datosTrain))
  diferencia = calculadas == eTrain.R
  Ein = length(diferencia[diferencia == FALSE]) / nrow(datosTrain)
  
  test = simula_unif(1000, 2, c(-1,1))
  eTest = sign(f(test[,1], test[,2]))
  eTest.R = asignarRuido(eTest, 10)
  
  datosTest = matrix(c(rep(1, length(test[,2])), test[,1], 
                       test[,2]), nrow = length(test[,2]))
  
  calculadas = sign(t(modelo)%*%t(datosTest))
  diferencia = calculadas == eTest.R
  Eout = length(diferencia[diferencia == FALSE]) / nrow(datosTest)
  c(Ein, Eout)
}

resultadosExperimento1 = replicate(1000, experimento1())
Ein.medio = mean(resultadosExperimento1[1,])
Eout.medio = mean(resultadosExperimento1[2,])
Ein.medio
Eout.medio

## ------------------------------------------------------------------------
entrenamiento = simula_unif(1000, 2, c(-1,1))
eTrain = sign(f(entrenamiento[,1], entrenamiento[,2]))
eTrain.R = asignarRuido(eTrain, 10)

datosTrain = matrix(c(rep(1, length(entrenamiento[,2])), entrenamiento[,1], 
                    entrenamiento[,2], entrenamiento[,1]*entrenamiento[,2], 
                    entrenamiento[,1]^2, entrenamiento[,2]^2),
                    nrow = length(entrenamiento[,2]))

modelo = Regress_Lin(datosTrain, eTrain.R)
calculadas = sign(t(modelo)%*%t(datosTrain))
diferencia = calculadas == eTrain.R
Ein = length(diferencia[diferencia == FALSE]) / nrow(datosTrain)
Ein

## ------------------------------------------------------------------------
experimento2 = function(i) {
  f = function(x1, x2) (x1+0.2)^2 + (x2)^2 - 0.6
  entrenamiento = simula_unif(1000, 2, c(-1,1))
  eTrain = sign(f(entrenamiento[,1], entrenamiento[,2]))
  eTrain.R = asignarRuido(eTrain, 10)
  
  datosTrain = matrix(c(rep(1, length(entrenamiento[,2])), entrenamiento[,1], 
                    entrenamiento[,2], entrenamiento[,1]*entrenamiento[,2], 
                    entrenamiento[,1]^2, entrenamiento[,2]^2),
                    nrow = length(entrenamiento[,2]))
  modelo = Regress_Lin(datosTrain, eTrain.R)

  calculadas = sign(t(modelo)%*%t(datosTrain))
  diferencia = calculadas == eTrain.R
  Ein = length(diferencia[diferencia == FALSE]) / nrow(datosTrain)
  
  test = simula_unif(1000, 2, c(-1,1))
  eTest = sign(f(test[,1], test[,2]))
  eTest.R = asignarRuido(eTest, 10)
  
  datosTest = matrix(c(rep(1, length(test[,2])), test[,1], 
                    test[,2], test[,1]*test[,2], 
                    test[,1]^2, test[,2]^2),
                    nrow = length(test[,2]))
  
  calculadas = sign(t(modelo)%*%t(datosTest))
  diferencia = calculadas == eTest.R
  Eout = length(diferencia[diferencia == FALSE]) / nrow(datosTest)
  c(Ein, Eout)
}

resultadosExperimento2 = replicate(1000, experimento2())
Ein.medio = mean(resultadosExperimento2[1,])
Eout.medio = mean(resultadosExperimento2[2,])
Ein.medio
Eout.medio

## ------------------------------------------------------------------------
apartadoA = function(i) {
  bonus = simula_unif(100, 2, c(-10,10))
  recta = simula_recta(c(-10,10))
  bonus.e = lapply(1:nrow(bonus), function(i) {
      d = bonus[i,]
      sign(d[2] - recta[1]*d[1] - recta[2])
  })
  bonus.e = unlist(bonus.e)
  
  bonusTrain = matrix(c(rep(1, length(bonus[,2])), bonus[,1], 
                        bonus[,2]), nrow = length(bonus[,2]))
  
  g = Regress_Lin(bonusTrain, bonus.e)
  
  calculadas = sign(t(g)%*%t(bonusTrain))
  diferencia = calculadas == bonus.e
  Ein = length(diferencia[diferencia == FALSE]) / nrow(bonusTrain)
  Ein
}

EinApartadoA = replicate(1000, apartadoA())
Ein.medio = mean(EinApartadoA)
Ein.medio

## ------------------------------------------------------------------------
apartadoB = function(i) {
  bonus = simula_unif(100, 2, c(-10,10))
  recta = simula_recta(c(-10,10))
  bonus.e = lapply(1:nrow(bonus), function(i) {
      d = bonus[i,]
      sign(d[2] - recta[1]*d[1] - recta[2])
  })
  bonus.e = unlist(bonus.e)
  
  bonusTrain = matrix(c(rep(1, length(bonus[,2])), bonus[,1], 
                        bonus[,2]), nrow = length(bonus[,2]))
  
  g = Regress_Lin(bonusTrain, bonus.e)
  
  bonus = simula_unif(1000, 2, c(-10,10))
  bonusTest.e = lapply(1:nrow(bonus), function(i) {
      d = bonus[i,]
      sign(d[2] - recta[1]*d[1] - recta[2])
  })
  bonusTest.e = unlist(bonusTest.e)
  
  bonusTest = matrix(c(rep(1, length(bonus[,2])), bonus[,1], 
                       bonus[,2]), nrow = length(bonus[,2]))
  
  calculadas = sign(t(g)%*%t(bonusTest))
  diferencia = calculadas == bonusTest.e
  Eout = length(diferencia[diferencia == FALSE]) / nrow(bonusTest)
  Eout
}

EoutApartadoB = replicate(1000, apartadoB())
Eout.medio = mean(EoutApartadoB)
Eout.medio

## ------------------------------------------------------------------------
apartadoC = function(i) {
  bonus = simula_unif(10, 2, c(-10,10))
  recta = simula_recta(c(-10,10))
  bonus.e = lapply(1:nrow(bonus), function(i) {
      d = bonus[i,]
      sign(d[2] - recta[1]*d[1] - recta[2])
  })
  bonus.e = unlist(bonus.e)
  
  bonusTrain = matrix(c(rep(1, length(bonus[,2])), bonus[,1], 
                        bonus[,2]), nrow = length(bonus[,2]))
  
  g = Regress_Lin(bonusTrain, bonus.e)
  
  solucion = ajusta_PLA(bonus, bonus.e, 1000, c(g[1],g[2],g[3]))
  solucion[2]
}

iteraciones = replicate(1000, apartadoC())
iteraciones.media = mean(unlist(iteraciones))
iteraciones.media

