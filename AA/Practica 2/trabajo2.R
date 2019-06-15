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
simula_gaus = function(N=2,dim=2,sigma, media){
  if (missing(sigma)) stop("Debe dar un vector de varianzas")
  sigma = sqrt(sigma)  # para la generación se usa sd, y no la varianza
  if(dim != length(sigma)) stop ("El numero de varianzas es distinto de la dimensión")
  simula_gauss1 = function() rnorm(mean = media, dim, sd = sigma) # genera 1 muestra, con las
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

## ------------------------------------------------------------------------
f1 = function(u, v) ((u^2*exp(v) - 2*v^2*exp(-u))^2)
du1 = function(u,v) (2*((2*u*exp(v) + 2*v^2*exp(-u))*(u^2*exp(v) - 2*v^2*exp(-u))))
dv1 = function(u,v) (2*((u^2*exp(v) - 2*(2*v)*exp(-u))*(u^2*exp(v) - 2*v^2*exp(-u))))

GD = function(u = 1, v = 1, eta = 0.1, umbral = 10^(-4), max_iter = 1000, f, du, dv){
  noLlanura = T
  u_0 = 0.0
  v_0 = 0.0
  u_1 = u
  v_1 = v
  iter = 0            
  # Como condición de parada tenemos el número de iteraciones
  # y que no estemos en una zona plana, es decir, que haya una diferencia
  # entre el valor de la función en el punto nuevo con respecto al anterior.
  while(iter < max_iter & noLlanura == T) {
    u_0 = u_1
    v_0 = v_1
    u_1 = u_0 - eta * du(u_0, v_0)
    v_1 = v_0 - eta * dv(u_0, v_0)
    iter = iter + 1
    if(abs(f(u_1, v_1) - f(u_0, v_0)) < umbral)
      noLlanura = F
  }
  c(iter, f(u_1, v_1), u_1, v_1, abs(f(u_1, v_1) - f(u_0, v_0)))
}

GD(f = f1, du = du1, dv = dv1)

## ------------------------------------------------------------------------
f2 = function(x, y) ((x-2)^2 + 2*(y-2)^2 + 2*sin(2*pi*x)*sin(2*pi*y))
dx2 = function(x, y) (2*(x-2) + 2*(cos(2*pi*x)*(2*pi))*sin(2*pi*y))
dy2 = function(x, y) (2*(2*(y-2)) + 2*sin(2*pi*x)*(cos(2*pi*y)*(2*pi)))

GD_graf = function(u = 1, v = 1, eta = 0.1, umbral = 10^(-4), max_iter = 1000, f, du, dv){
  noLlanura = T
  valores=list()
  iteraciones=list()
  u_0 = 0.0
  v_0 = 0.0
  u_1 = u
  v_1 = v
  iter = 0            
  # Como condición de parada tenemos el número de iteraciones
  # y que no estemos en una zona plana, es decir, que haya una diferencia
  # entre el valor de la función en el punto nuevo con respecto al anterior.
  while(iter < max_iter & noLlanura == T) {
    u_0 = u_1
    v_0 = v_1
    u_1 = u_0 - eta * du(u_0, v_0)
    v_1 = v_0 - eta * dv(u_0, v_0)
    valores = c(valores, f(u_1, v_1))
    iteraciones = c(iteraciones, iter)
    iter = iter + 1
    if(abs(f(u_1, v_1) - f(u_0, v_0)) < umbral)
      noLlanura = F
  }
  valores=unlist(valores)
  iteraciones=unlist(iteraciones)
  valores = matrix(valores, nrow=length(valores), ncol=1)
  iteraciones = matrix(iteraciones, nrow=length(iteraciones), ncol=1)
  salida = cbind(iteraciones, valores)
  plot(salida, xlab="Iteraciones.", ylab="Valor de la función.")
  c(iter, f(u_1, v_1), u_1, v_1, abs(f(u_1, v_1) - f(u_0, v_0)))
}

par(mfrow=c(1,2))
GD_graf(eta = 0.01, f = f2, du = dx2, dv = dy2, max_iter = 50)
GD_graf(eta = 0.1, f = f2, du = dx2, dv = dy2, max_iter = 50)
par(mfrow=c(1,1))

## ------------------------------------------------------------------------
GD(u = 2.1, v = 2.1, eta = 0.1, f = f2, du = dx2, dv = dy2, max_iter = 50)
GD(u = 3, v = 3, eta = 0.1, f = f2, du = dx2, dv = dy2, max_iter = 50)
GD(u = 1.5, v = 1.5, eta = 0.1, f = f2, du = dx2, dv = dy2, max_iter = 50)
GD(u = 1, v = 1, eta = 0.1, f = f2, du = dx2, dv = dy2, max_iter = 50)

## ------------------------------------------------------------------------
datosEj2 = simula_unif(N = 100, dims = 2, rango = c(0,2))
rectaEj2 = simula_recta(intervalo = c(0,2))
valor_y = function(x, pendiente, valor){ pendiente*x+valor }
etiquetasEj2 = sign(valor_y(datosEj2[,1], rectaEj2[1], rectaEj2[2]) - datosEj2[,2])

norma = function(v){
  sqrt(sum(v^2))
}

RLSGD = function(datos, etiquetas, eta = 0.01, umbral = 0.01, max_iter = 550){
  indices = c(1:nrow(datos))
  datos = cbind(1,datos)
  w_1 = c(0, 0, 0)
  seguirEjecucion = T
  iter = 0
  
  while(iter < max_iter & seguirEjecucion){
    w_0 = w_1
    indices = sample(indices)
    for(i in indices){
      w_1 = w_1 - eta*(-etiquetas[i]*datos[i,])/as.vector((1+exp(etiquetas[i]*(w_1%*%datos[i,]))))
    }
    if(norma(w_0 - w_1) < umbral)
      seguirEjecucion = F
    iter = iter + 1
  }
  
  w_1
}

par(mfrow=c(1,2))
sol = RLSGD(datos = datosEj2, etiquetas = etiquetasEj2)
plot(datosEj2, col=etiquetasEj2+5, main="Resultado con RLSGD")
abline(-sol[1]/sol[3], -sol[2]/sol[3])
plot(datosEj2, col=etiquetasEj2+5, main="Resultado original")
abline(rectaEj2[2], rectaEj2[1])
par(mfrow=c(1,1))

#Calculamos el error usando el error de regresión logistica
#que aparece en la página 95 del libro "Learning from Data"
sum(log(1+exp(-etiquetasEj2*(t(sol)%*%t(cbind(1, datosEj2))))))/nrow(datosEj2)

## ------------------------------------------------------------------------
datos_test = simula_unif(N = 1000, dims = 2, rango = c(0,2))

recta_test = rectaEj2
etiquetas_test = sign(valor_y(datos_test[,1], recta_test[1], recta_test[2]) - datos_test[,2])

#Calculamos el error usando el error de regresión logistica
#que aparece en la página 95 del libro "Learning from Data"
sum(log(1+exp(-etiquetas_test*(t(sol)%*%t(cbind(1, datos_test))))))/nrow(datos_test)

## ------------------------------------------------------------------------
# Leemos los datos
digit.train = read.table("./datos/zip.train", quote="\"", comment.char="", 
                         stringsAsFactors=FALSE)

digitos.train = digit.train[digit.train$V1==4 | digit.train$V1==8,]
etiquetasTrain = digitos.train[,1]
ndigitosTrain = nrow(digitos.train)

# se retira la clase y se monta una matriz 3D: 599*16*16
datosTrain = array(unlist(subset(digitos.train,select=-V1)),c(ndigitosTrain,16,16))
rm(digit.train)
rm(digitos.train)

simetria <- function(A){
  A = abs(A-A[,ncol(A):1])
  -mean(A)
}

# Aplicamos la función para calcular la simetria y la intensidad a cada matriz
# de la lista de matrices
datosTrain.media = apply(datosTrain, 1, mean)
datosTrain.simetria = apply(datosTrain, 1, simetria)

datosTrain = matrix(c(datosTrain.media, datosTrain.simetria), 
                    nrow = length(datosTrain.simetria))

# Leemos los datos de test
digit.test = read.table("./datos/zip.test", quote="\"", comment.char="", 
                         stringsAsFactors=FALSE)

digitos.test = digit.test[digit.test$V1==4 | digit.test$V1==8,]
etiquetasTest = digitos.test[,1]
ndigitosTest = nrow(digitos.test)

# se retira la clase y se monta una matriz 3D: 599*16*16
datosTest = array(unlist(subset(digitos.test,select=-V1)),c(ndigitosTest,16,16))
rm(digit.test)
rm(digitos.test)

# Aplicamos la función para calcular la simetria y la intensidad a cada matriz
# de la lista de matrices
datosTest.media = apply(datosTest, 1, mean)
datosTest.simetria = apply(datosTest, 1, simetria)

datosTest = matrix(c(datosTest.media, datosTest.simetria), 
                    nrow = length(datosTest.simetria))

plot(datosTrain, xlab="Intensidad", ylab="Simetria", col=etiquetasTrain, main="Train")
plot(datosTest, xlab="Intensidad", ylab="Simetria", col=etiquetasTest, main="Test")

## ------------------------------------------------------------------------
Regress_Lin = function(datos, label) {
  # Nos aseguramos de que vamos a trabar con matrices
  datos = as.matrix(datos)
  label = as.matrix(label)
  datos = cbind(1, datos)

  x = t(datos) %*% datos
  matrices = svd(x)
  auxiliar = matrices$v%*%diag(1/matrices$d)%*%t(matrices$v)
  pseudo = auxiliar%*%t(datos)
  w = pseudo%*%label
  unlist(w)
}

PLA_Pocket = function(datos, etiquetas, max_iter = 1000, vini = c(0,0,0)){
  seguirIterando = TRUE
  w = vini
  mejor_w = w
  iter = 0
  datos = cbind(1, datos)
  #Guardamos el error que nos da el vector de pesos inicial
  error = sum(sign(t(w)%*%t(datos)) != etiquetas) / length(etiquetas)
  #El algoritmos es igual que el PLA original
  while (seguirIterando && iter < max_iter){
    seguirIterando = FALSE
    indices = sample(1:nrow(datos))
    contador = 1
    while(contador <= length(indices) & !seguirIterando){
      i = indices[contador]
      if (sign(crossprod(w, datos[i,])) != etiquetas[i]){
        seguirIterando = TRUE
        w = w + etiquetas[i] * datos[i,]
      }
      contador = contador + 1
    }
    iter = iter + 1
    #Pero cada vez que se actualizan los pesos, calculamos el error que nos dan
    #estos pesos nuevos
    error_actual = sum(sign(t(w)%*%t(datos)) != etiquetas) / length(etiquetas)
    #Y si es menor que lo mejor que teníamos, lo guardamos
    #En este punto es donde se introduce memoria al PLA
    if(error_actual < error){
      mejor_w = w
      error = error_actual
    }
  }
  mejor_w
}

## ------------------------------------------------------------------------
etiquetasTrain_2 = replace(etiquetasTrain, etiquetasTrain==4, -1)
etiquetasTrain_2 = replace(etiquetasTrain_2, etiquetasTrain_2==8, 1)

etiquetasTest_2 = replace(etiquetasTest, etiquetasTest==4, -1)
etiquetasTest_2 = replace(etiquetasTest_2, etiquetasTest_2==8, 1)

## ------------------------------------------------------------------------
RLTrain = Regress_Lin(datosTrain, etiquetasTrain_2)
plot(datosTrain, xlab="Intensidad", ylab="Simetria",
     col=etiquetasTrain_2+5, main="RL para train")
abline(-RLTrain[1]/RLTrain[3], -RLTrain[2]/RLTrain[3])

RLTest = Regress_Lin(datosTest, etiquetasTest_2)
plot(datosTest, xlab="Intensidad", ylab="Simetria",
     col=etiquetasTest_2+5, main="RL para test")
abline(-RLTest[1]/RLTest[3], -RLTest[2]/RLTest[3])

PLA_PocketTrain = PLA_Pocket(datos = datosTrain, etiquetas = etiquetasTrain_2)
plot(datosTrain, xlab="Intensidad", ylab="Simetria",
     col=etiquetasTrain_2+5, main="PLA_Pocket para train")
abline(-PLA_PocketTrain[1]/PLA_PocketTrain[3], -PLA_PocketTrain[2]/PLA_PocketTrain[3])

PLA_PocketTest = PLA_Pocket(datos = datosTest, etiquetas = etiquetasTest_2)
plot(datosTest, xlab="Intensidad", ylab="Simetria",
     col=etiquetasTest_2+5, main="PLA_Pocket para test")
abline(-PLA_PocketTest[1]/PLA_PocketTest[3], -PLA_PocketTest[2]/PLA_PocketTest[3])

## ------------------------------------------------------------------------
RLEinTrain = sum(sign(t(RLTrain)%*%t(cbind(1, datosTrain))) 
                 != etiquetasTrain_2) / nrow(datosTrain)

RLEinTest = sum(sign(t(RLTest)%*%t(cbind(1, datosTest))) 
                != etiquetasTest_2) / nrow(datosTest)

PLA_PocketEinTrain = sum(sign(t(RLTrain)%*%t(cbind(1, datosTrain))) 
                         != etiquetasTrain_2) / nrow(datosTrain)

PLA_PocketEinTest = sum(sign(t(RLTest)%*%t(cbind(1, datosTest))) 
                        != etiquetasTest_2) / nrow(datosTest)
RLEinTrain
RLEinTest
PLA_PocketEinTrain
PLA_PocketEinTest

## ------------------------------------------------------------------------
as.vector(RLTrain)
as.vector(RLTest)
PLA_PocketTrain
PLA_PocketTest

## ------------------------------------------------------------------------
PLA_PocketTrain = PLA_Pocket(datos = datosTrain, etiquetas = etiquetasTrain_2, 
                             vini = RLTrain)

PLA_PocketTest = PLA_Pocket(datos = datosTest, etiquetas = etiquetasTest_2, vini = RLTest)

PLA_PocketEinTrain2 = sum(sign(t(PLA_PocketTrain)%*%t(cbind(1, datosTrain))) 
                         != etiquetasTrain_2) / nrow(datosTrain)

PLA_PocketEinTest2 = sum(sign(t(PLA_PocketTest)%*%t(cbind(1, datosTest))) 
                        != etiquetasTest_2) / nrow(datosTest)
RLEinTrain
RLEinTest
PLA_PocketEinTrain
PLA_PocketEinTest
PLA_PocketEinTrain2
PLA_PocketEinTest2

## ------------------------------------------------------------------------
EoutTrain = RLEinTrain + sqrt((8/ndigitosTrain)*log((4*((2*ndigitosTrain)^3 + 1))/0.05))
EoutTest = RLEinTrain + sqrt((8/ndigitosTest)*log((4*((2*ndigitosTest)^3 + 1))/0.05))
EoutTrain
EoutTest

## ------------------------------------------------------------------------
RL_WD = function(datos, label, lamda) {
  # Nos aseguramos de que vamos a trabajar con matrices
  datos = as.matrix(datos)
  label = as.matrix(label)

  # El segundo termino de la sumatoria es lo que nos proporcionar el 
  # wight decay
  x = t(datos) %*% datos + diag(lamda, ncol(datos), ncol(datos))
  matrices = svd(x)
  auxiliar = matrices$v%*%diag(1/matrices$d)%*%t(matrices$v)
  pseudo = auxiliar%*%t(datos)
  w = pseudo%*%label
  w
  unlist(w)
}

experimento = function(){
  datos = matrix(replicate(130, simula_gaus(N = 3, dim = 1, sigma = 1, media = 1)), 
               nrow = 130, ncol = 3, byrow = T)
  datos = cbind(1,datos)
  w_f = simula_gaus(N = 4, dim = 1, sigma = 1, media = 0)
  #Se lo sumo al primero en vez de al último ya que mi termino indepentdiente en los 
  #datos es el primero, no el último
  w_f[1] = w_f[1] + 1
  ruido = simula_gaus(N = nrow(datos), dim = 1, sigma = 0.5, media = 0)
  
  etiquetas = as.vector(datos %*% as.vector(w_f)) + 0.5*ruido
  
  
  ini = 1
  fin = 13
  errores = list()
  for(i in 1:10){
    test = datos[ini:fin,]
    etiquetas.test = etiquetas[ini:fin]
    train = datos[-c(ini:fin),]
    etiquetas.train = etiquetas[-c(ini:fin)]
    w = RL_WD(train, etiquetas.train, lamda = 0.05/nrow(train))
    etiquetas.calculadas = as.vector(t(w)%*%t(test))
    #Calculamos el error usando minimos cuadrados
    error = sum((etiquetas.calculadas - etiquetas.test)^2) / (length(etiquetas.test))
    errores = c(errores, error)
    
    #Ojo, las particiones son de trece elementos
    ini = 1+i*13
    fin = 13+i*13
  }
  unlist(errores)
}

mil_experimentos = function(){
  salida = matrix(ncol = 10)
  for(i in 1:1000){
    errores = experimento()
    salida = rbind(salida, errores)
  }
  #Al crear la matriz se mete una fila de NA, así que la quitamos
  salida = salida[-1,]
  salida
}

resultados = mil_experimentos()

#Calculamos los errores e1, ..., eN para todos los experimentos (media de las columnas)
e_partes_medios = apply(resultados, c(2), mean)
#Calculamos la varianza en cada particion
e_partes_var = apply(resultados, c(2), var)
#Calculamos el error medio de validacion cruzada
e_vc_med = mean(e_partes_medios)
e_vc_var = mean(e_partes_var)

e_partes_medios[1] #e1
e_partes_medios[2] #e2
e_vc_med  #Evc
e_partes_var[1] #varianza 1
e_partes_var[2] #varianza 2
e_vc_var  #varianza media de los experimentos

## ------------------------------------------------------------------------
RL = function(datos, label, lamda) {
  # Nos aseguramos de que vamos a trabajar con matrices
  datos = as.matrix(datos)
  label = as.matrix(label)

  # El segundo termino de la sumatoria es lo que nos proporcionar el 
  # wight decay
  x = t(datos) %*% datos
  matrices = svd(x)
  auxiliar = matrices$v%*%diag(1/matrices$d)%*%t(matrices$v)
  pseudo = auxiliar%*%t(datos)
  w = pseudo%*%label
  w
  unlist(w)
}

experimento = function(){
  datos = matrix(replicate(130, simula_gaus(N = 3, dim = 1, sigma = 1, media = 1)), 
               nrow = 130, ncol = 3, byrow = T)
  datos = cbind(1,datos)
  w_f = simula_gaus(N = 4, dim = 1, sigma = 1, media = 0)
  #Se lo sumo al primero en vez de al último ya que mi termino indepentdiente en los 
  #datos es el primero, no el último
  w_f[1] = w_f[1] + 1
  ruido = simula_gaus(N = nrow(datos), dim = 1, sigma = 0.5, media = 0)
  
  etiquetas = as.vector(datos %*% as.vector(w_f)) + 0.5*ruido
  
  
  ini = 1
  fin = 13
  errores = list()
  for(i in 1:10){
    test = datos[ini:fin,]
    etiquetas.test = etiquetas[ini:fin]
    train = datos[-c(ini:fin),]
    etiquetas.train = etiquetas[-c(ini:fin)]
    w = RL(train, etiquetas.train, lamda = 0.05/nrow(train))
    etiquetas.calculadas = as.vector(t(w)%*%t(test))
    #Calculamos el error usando minimos cuadrados
    error = sum((etiquetas.calculadas - etiquetas.test)^2) / (length(etiquetas.test))
    errores = c(errores, error)
    
    #Ojo, las particiones son de trece elementos
    ini = 1+i*13
    fin = 13+i*13
  }
  unlist(errores)
}

mil_experimentos = function(){
  salida = matrix(ncol = 10)
  for(i in 1:1000){
    errores = experimento()
    salida = rbind(salida, errores)
  }
  #Al crear la matriz se mete una fila de NA, así que la quitamos
  salida = salida[-1,]
  salida
}

resultados = mil_experimentos()

#Calculamos los errores e1, ..., eN para todos los experimentos (media de las columnas)
e_partes_medios = apply(resultados, c(2), mean)
#Calculamos la varianza en cada particion
e_partes_var = apply(resultados, c(2), var)
#Calculamos el error medio de validacion cruzada
e_vc_med = mean(e_partes_medios)
e_vc_var = mean(e_partes_var)

e_partes_medios[1] #e1
e_partes_medios[2] #e2
e_vc_med  #Evc
e_partes_var[1] #varianza 1
e_partes_var[2] #varianza 2
e_vc_var  #varianza media de los experimentos

## ------------------------------------------------------------------------
f1 = function(u, v) ((u^2*exp(v) - 2*v^2*exp(-u))^2)
du1 = function(u,v) (2*((2*u*exp(v) + 2*v^2*exp(-u))*(u^2*exp(v) - 2*v^2*exp(-u))))
dv1 = function(u,v) (2*((u^2*exp(v) - 2*(2*v)*exp(-u))*(u^2*exp(v) - 2*v^2*exp(-u))))

CD = function(u = 1, v = 1, eta = 0.1, umbral = 10^(-4), max_iter = 1000, f, du, dv){
  noLlanura = T
  u_0 = 0.0
  v_0 = 0.0
  u_1 = u
  v_1 = v
  iter = 0            
  # Como condición de parada tenemos el número de iteraciones
  # y que no estemos en una zona plana, es decir, que haya una diferencia
  # entre el valor de la función en el punto nuevo con respecto al anterior.
  while(iter < max_iter & noLlanura == T) {
    u_0 = u_1
    v_0 = v_1
    #Paso 1
    u_1 = u_0 - eta * du(u_0, v_0)
    #Paso 2
    v_1 = v_0 - eta * dv(u_1, v_0)
    iter = iter + 1
    if(abs(f(u_1, v_1) - f(u_0, v_0)) < umbral)
      noLlanura = F
  }
  c(iter, f(u_1, v_1), u_1, v_1, abs(f(u_1, v_1) - f(u_0, v_0)))
}

CD(f = f1, du = du1, dv = dv1, max_iter = 15)
GD(f = f1, du = du1, dv = dv1, max_iter = 15)

## ------------------------------------------------------------------------
fun = function(x, y) ((x-2)^2 + 2*(y-2)^2 + 2*sin(2*pi*x)*sin(2*pi*y))
dx = function(x, y) (2*(2*pi*cos(2*pi*x)*sin(2*pi*y)+x-2))
dxy = function(x, y) (8*pi^2*cos(2*pi*x)*cos(2*pi*y))
d2x = function(x, y) (2-8*pi^2*sin(2*pi*x)*sin(2*pi*y))
dy = function(x, y) (4*(pi*sin(2*pi*x)*cos(2*pi*y)+y-2))
d2y = function(x, y) (4-8*pi^2*sin(2*pi*x)*sin(2*pi*y))
dyx = function(x, y) (8*pi^2*cos(2*pi*x)*cos(2*pi*y))

MatrizNewton = function(x, y, d2x, dxy, dyx, d2y){
  matrix(c(d2x(x,y), dxy(x,y), dyx(x,y), d2y(x,y)), ncol = 2, nrow = 2, byrow = T)
}

Metodo_Newton_Graf = function(x0 = 1, y0 = 1, f, dx, dy, d2x, d2y, dxy, dyx, eta = 0.1, 
                              umbral = 10^(-4), max_iter = 200) {
  w0 = c(0,0)
  w1 = c(x0,y0)
  
  iter = 0
  seguir = T
  
  valores=list()
  iteraciones=list()

  while(iter < max_iter & seguir){
    w0 = w1
    m = MatrizNewton(w0[1], w0[2], d2x, dxy, dyx, d2y)
    gradiente = c(dx(w0[1], w0[2]), dy(w0[1], w0[2]))
    w1 = w0 - eta*(solve(m)%*%gradiente)
    
    valores = c(valores, f(w1[1], w1[2]))
    iteraciones = c(iteraciones, iter)
    
    iter = iter + 1
    if(abs(f(w1[1], w1[2]) - f(w0[1], w0[2])) < umbral){
      seguir = F
    }
  }
  
  valores=unlist(valores)
  iteraciones=unlist(iteraciones)
  valores = matrix(valores, nrow=length(valores), ncol=1)
  iteraciones = matrix(iteraciones, nrow=length(iteraciones), ncol=1)
  salida = cbind(iteraciones, valores)
  plot(salida, xlab="Iteraciones.", ylab="Valor de la función.")
}


par(mfrow=c(1,2))
Metodo_Newton_Graf(x0 = 1, y0 = 1, f = fun, dx = dx, dy = dy, d2x = d2x, d2y = d2y, dxy = 
                     dxy, dyx = dyx, eta = 0.01, umbral = 10^(-4), max_iter = 200)

GD_graf(eta = 0.01, f = f2, du = dx, dv = dy, max_iter = 200)
par(mfrow=c(1,1))

## ------------------------------------------------------------------------
par(mfrow=c(1,2))
Metodo_Newton_Graf(x0 = 1, y0 = 1, f = fun, dx = dx, dy = dy, d2x = d2x, d2y = d2y, dxy = 
                     dxy, dyx = dyx, eta = 1, umbral = 10^(-4), max_iter = 200)

GD_graf(eta = 0.01, f = f2, du = dx, dv = dy, max_iter = 200)
par(mfrow=c(1,1))

## ------------------------------------------------------------------------
#Version modificada para devolver las iteraciones tambien
RLSGD_aux = function(datos, etiquetas, eta = 0.01, umbral = 0.01, max_iter = 550){
  indices = c(1:nrow(datos))
  datos = cbind(1,datos)
  w_1 = c(0, 0, 0)
  seguirEjecucion = T
  iter = 0
  while(iter < max_iter & seguirEjecucion){
    w_0 = w_1
    indices = sample(indices)
    for(i in indices){
      w_1 = w_1 - eta*(-etiquetas[i]*datos[i,])/as.vector((1+exp(etiquetas[i]*
                                                                   (w_1%*%datos[i,]))))
    }
    if(norma(w_0 - w_1) < umbral)
      seguirEjecucion = F
    
    iter = iter + 1
  }
  c(w_1, iter)
}

datos = simula_unif(N = 100, dims = 2, rango = c(0,2))
resultados_Ej3 = list()
iteraciones_Ej3 = list()
for(i in 1:100){
  recta = simula_recta(c(0,2))
  etiquetasEj2 = sign(valor_y(datosEj2[,1], rectaEj2[1], rectaEj2[2]) - datosEj2[,2])
  
  sol = RLSGD_aux(datos = datosEj2, etiquetas = etiquetasEj2)
  iteraciones = sol[4]
  sol = sol[-4]
  
  datos_test = simula_unif(N = 100, dims = 2, rango = c(0,2))
  recta_test = simula_recta(intervalo = c(0,2))
  etiquetas_test = sign(valor_y(datos_test[,1], recta_test[1], recta_test[2]) - 
                          datos_test[,2])
  
  error = sum(sign(t(sol)%*%t(cbind(1, datos_test))) 
      != etiquetas_test) / nrow(datos_test) 
  iteraciones_Ej3 = c(iteraciones_Ej3, iteraciones)
  resultados_Ej3 = c(resultados_Ej3, error)
}
mean(unlist(resultados_Ej3))
mean(unlist(iteraciones_Ej3))

## ------------------------------------------------------------------------
# Leemos los datos
digit.train = read.table("./datos/zip.train", quote="\"", comment.char="", 
                         stringsAsFactors=FALSE)

digitos.train = digit.train[digit.train$V1==4 | digit.train$V1==8,]
etiquetasTrain = digitos.train[,1]
ndigitosTrain = nrow(digitos.train)

# se retira la clase y se monta una matriz 3D: 599*16*16
datosTrain = array(unlist(subset(digitos.train,select=-V1)),c(ndigitosTrain,16,16))
rm(digit.train)
rm(digitos.train)

simetria <- function(A){
  A = abs(A-A[,ncol(A):1])
  -mean(A)
}

# Aplicamos la función para calcular la simetria y la intensidad a cada matriz
# de la lista de matrices
datosTrain.media = apply(datosTrain, 1, mean)
datosTrain.simetria = apply(datosTrain, 1, simetria)

datosTrain = matrix(c(datosTrain.media, datosTrain.simetria), 
                    nrow = length(datosTrain.simetria))

# Leemos los datos de test
digit.test = read.table("./datos/zip.test", quote="\"", comment.char="", 
                         stringsAsFactors=FALSE)

digitos.test = digit.test[digit.test$V1==4 | digit.test$V1==8,]
etiquetasTest = digitos.test[,1]
ndigitosTest = nrow(digitos.test)

# se retira la clase y se monta una matriz 3D: 599*16*16
datosTest = array(unlist(subset(digitos.test,select=-V1)),c(ndigitosTest,16,16))
rm(digit.test)
rm(digitos.test)

# Aplicamos la función para calcular la simetria y la intensidad a cada matriz
# de la lista de matrices
datosTest.media = apply(datosTest, 1, mean)
datosTest.simetria = apply(datosTest, 1, simetria)

datosTest = matrix(c(datosTest.media, datosTest.simetria), 
                    nrow = length(datosTest.simetria))

etiquetasTrain_2 = replace(etiquetasTrain, etiquetasTrain==4, -1)
etiquetasTrain_2 = replace(etiquetasTrain_2, etiquetasTrain_2==8, 1)

etiquetasTest_2 = replace(etiquetasTest, etiquetasTest==4, -1)
etiquetasTest_2 = replace(etiquetasTest_2, etiquetasTest_2==8, 1)

## ------------------------------------------------------------------------
datosTrain = matrix(c(datosTrain[,1], datosTrain[,2], datosTrain[,1]*datosTrain[,2], 
                    datosTrain[,1]^2, datosTrain[,2]^2, datosTrain[,1]^3,
                    datosTrain[,1]^2*datosTrain[,2], 
                    datosTrain[,2]^2*datosTrain[,1], datosTrain[,2]^3),
                    nrow = length(datosTrain[,1]))

datosTest = matrix(c(datosTest[,1], datosTest[,2], datosTest[,1]*datosTest[,2], 
                    datosTest[,1]^2, datosTest[,2]^2, datosTest[,1]^3,
                    datosTest[,1]^2*datosTest[,2],
                    datosTest[,2]^2*datosTest[,1], datosTest[,2]^3),
                    nrow = length(datosTest[,1]))

RLTrain = Regress_Lin(datosTrain, etiquetasTrain_2)
RLTest = Regress_Lin(datosTest, etiquetasTest_2)
PLA_PocketTrain = PLA_Pocket(datos = datosTrain, etiquetas = etiquetasTrain_2, 
                             vini = c(rep(0, dim(datosTrain)[2] + 1)))
PLA_PocketTest = PLA_Pocket(datos = datosTest, etiquetas = etiquetasTest_2, 
                            vini = c(rep(0, dim(datosTest)[2] + 1)))

RLEinTrain = sum(sign(t(RLTrain)%*%t(cbind(1, datosTrain))) 
                 != etiquetasTrain_2) / nrow(datosTrain)

RLEinTest = sum(sign(t(RLTest)%*%t(cbind(1, datosTest))) 
                != etiquetasTest_2) / nrow(datosTest)

PLA_PocketEinTrain = sum(sign(t(RLTrain)%*%t(cbind(1, datosTrain))) 
                         != etiquetasTrain_2) / nrow(datosTrain)

PLA_PocketEinTest = sum(sign(t(RLTest)%*%t(cbind(1, datosTest))) 
                        != etiquetasTest_2) / nrow(datosTest)
RLEinTrain
RLEinTest
PLA_PocketEinTrain
PLA_PocketEinTest

