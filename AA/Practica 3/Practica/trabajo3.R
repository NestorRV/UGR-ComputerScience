## ----setup, include=FALSE------------------------------------------------
knitr::opts_chunk$set(echo = TRUE)

## ------------------------------------------------------------------------
trainTest = as.vector(read.table("./datos/spam.traintest"))
cantidadUnos = sum(trainTest)
cat("Numero de unos:", cantidadUnos, "\n")

## ------------------------------------------------------------------------
datos = datos = read.csv("./datos/spam.data", header = F, sep = " ")
indicesTrain = which(trainTest == 0)
train = (as.matrix(datos))[indicesTrain,]
test = (as.matrix(datos))[-indicesTrain,]
cat("Tamaño train:", dim(train), "\n")
cat("Tamaño test:", dim(test), "\n")

## ------------------------------------------------------------------------
# Guardamos las clases de los conjuntos
clasesTrain = train[, dim(train)[2]]
clasesTest = test[, dim(test)[2]]
# Eliminamos las clases de los conjuntos
train = train[, -dim(train)[2]]
test = test[, -dim(test)[2]]

library("caret")

# Se usa el método YeoJohnson en vez de BoxCox ya que el segundo no es adecuado
# cuando las características pueden tomar valores negativos o valores iguales
# a cero, y esto ocurre en nuestro dataset.
ObjetoTrans = preProcess(train, method = c("YeoJohnson", "center", "scale", "pca"), 
                         thresh=0.95)
ObjetoTrans_sinPCA = preProcess(train, method = c("YeoJohnson", "center", "scale"), 
                                thresh=0.95)

trainPCA = predict(ObjetoTrans, train)
cat("Nuevo tamaño de train (con PCA):", dim(trainPCA), "\n")
testPCA = predict(ObjetoTrans, test)
cat("Nuevo tamaño de test (con PCA):", dim(testPCA), "\n")

trainSinPCA = predict(ObjetoTrans_sinPCA, train)
cat("Nuevo tamaño de train (sin PCA):", dim(trainSinPCA), "\n")
testSinPCA = predict(ObjetoTrans_sinPCA, test)
cat("Nuevo tamaño de test (sin PCA):", dim(testSinPCA), "\n")

## ------------------------------------------------------------------------
library("leaps")

trainPCA = as.data.frame(cbind(clasesTrain, trainPCA))
testPCA = as.data.frame(cbind(clasesTest, testPCA))
trainSinPCA = as.data.frame(cbind(clasesTrain, trainSinPCA))
testSinPCA = as.data.frame(cbind(clasesTest, testSinPCA))

subsetPCA = regsubsets(trainPCA$clasesTrain ~ . , data = trainPCA, 
                       nvmax = dim(trainPCA)[2], method = "forward")
summaryPCA = summary(subsetPCA)

subsetSinPCA = regsubsets(trainSinPCA$clasesTrain ~ . , data = trainSinPCA, 
                          nvmax = dim(testSinPCA)[2], method = "forward")
summarySinPCA = summary(subsetSinPCA)

## ------------------------------------------------------------------------
head(summaryPCA$outmat)
head(summarySinPCA$outmat)

## ------------------------------------------------------------------------
par(mfrow=c(1,2))
plot(summaryPCA$cp, xlab = "Número de variables (con PCA).", ylab = "CP", type = "l")
plot(summaryPCA$bic, xlab = "Número de variables (con PCA).", ylab = "BIC", type = "l")
plot(summarySinPCA$cp, xlab = "Número de variables (sin PCA).", ylab = "CP", type = "l")
plot(summarySinPCA$bic, xlab = "Número de variables (sin PCA).", ylab = "BIC", type = "l")

cat("Mejor número de características - CP (con PCA):", which.min(summaryPCA$cp), "\n")
cat("Mejor número de características - BIC (con PCA):", which.min(summaryPCA$bic), "\n")
cat("Mejor número de características - CP (sin PCA):", which.min(summarySinPCA$cp), "\n")
cat("Mejor número de características - BIC (sin PCA):", which.min(summarySinPCA$bic), "\n")

## ------------------------------------------------------------------------
as.vector(which(summaryPCA$outmat[29,] == "*"))
as.vector(which(summaryPCA$outmat[36,] == "*"))

as.vector(which(summarySinPCA$outmat[29,] == "*"))
as.vector(which(summarySinPCA$outmat[36,] == "*"))

## ------------------------------------------------------------------------
as.vector(which(summaryPCA$outmat[1,] == "*"))
as.vector(which(summaryPCA$outmat[1,] == "*"))

as.vector(which(summarySinPCA$outmat[1,] == "*"))
as.vector(which(summarySinPCA$outmat[1,] == "*"))

## ------------------------------------------------------------------------
datosTrainModeloPCA_1 = trainPCA[, c(1, as.vector(which(summaryPCA$outmat[1,] 
                                                        == "*")) + 1)]
datosTrainModeloSinPCA_1 = trainSinPCA[, c(1, as.vector(which(summarySinPCA$outmat[1,] 
                                                              == "*")) + 1)]

datosTrainModeloPCA_29 = trainPCA[, c(1, as.vector(which(summaryPCA$outmat[29,] 
                                                         == "*")) + 1)]
datosTrainModeloSinPCA_29 = trainSinPCA[, c(1, as.vector(which(summarySinPCA$outmat[29,] 
                                                               == "*")) + 1)]

datosTrainModeloPCA_36 = trainPCA[, c(1, as.vector(which(summaryPCA$outmat[36,] 
                                                         == "*")) + 1)]
datosTrainModeloSinPCA_36 = trainSinPCA[, c(1, as.vector(which(summarySinPCA$outmat[36,] 
                                                               == "*")) + 1)]

datosTrainModeloPCA_57 = trainPCA
datosTrainModeloSinPCA_57 = trainSinPCA

# En el caso de los conjuntos de test, no vamos a guardar la clase en el dataset
datosTestModeloPCA_1 = as.data.frame(testPCA[, as.vector(
  which(summaryPCA$outmat[1,] == "*")) + 1])
datosTestModeloSinPCA_1 = as.data.frame(testSinPCA[, as.vector(
  which(summarySinPCA$outmat[1,] == "*")) + 1])

# Al crear un data.frame con una única columna se pierde el nombre de la columna
names1 = names(datosTrainModeloPCA_1)[-1]
names2 = names(datosTrainModeloSinPCA_1)[-1]
names(datosTestModeloPCA_1) = names1
names(datosTestModeloSinPCA_1) = names2

datosTestModeloPCA_29 = as.data.frame(testPCA[, as.vector(
  which(summaryPCA$outmat[29,] == "*")) + 1])
datosTestModeloSinPCA_29 = as.data.frame(testSinPCA[, as.vector(
  which(summarySinPCA$outmat[29,] == "*")) + 1])

datosTestModeloPCA_36 = as.data.frame(testPCA[, as.vector(
  which(summaryPCA$outmat[36,] == "*")) + 1])
datosTestModeloSinPCA_36 = as.data.frame(testSinPCA[, as.vector(
  which(summarySinPCA$outmat[36,] == "*")) + 1])

datosTestModeloPCA_57 = testPCA[,-1]
datosTestModeloSinPCA_57 = testSinPCA[,-1]

# Si en family no pones nada es lineal
# Si pones family = binomial(logit) es regresion logistica

#Una vez tenemos los conjuntos de datos, aprendemos los modelos
glmPCA_1 = glm(datosTrainModeloPCA_1$clasesTrain ~ ., 
                 data = datosTrainModeloPCA_1, family = binomial(logit))
glmSinPCA_1 = glm(datosTrainModeloSinPCA_1$clasesTrain ~ ., 
                    data = datosTrainModeloSinPCA_1, family = binomial(logit))

glmPCA_29 = glm(datosTrainModeloPCA_29$clasesTrain ~ ., 
                  data = datosTrainModeloPCA_29, family = binomial(logit))
glmSinPCA_29 = glm(datosTrainModeloSinPCA_29$clasesTrain ~ ., 
                     data = datosTrainModeloSinPCA_29, family = binomial(logit))

glmPCA_36 = glm(datosTrainModeloPCA_36$clasesTrain ~ ., 
                  data = datosTrainModeloPCA_36, family = binomial(logit))
glmSinPCA_36 = glm(datosTrainModeloSinPCA_36$clasesTrain ~ ., 
                     data = datosTrainModeloSinPCA_36, family = binomial(logit))

glmPCA_57 = glm(datosTrainModeloPCA_57$clasesTrain ~ ., 
                  data = datosTrainModeloPCA_57, family = binomial(logit))
glmSinPCA_57 = glm(datosTrainModeloSinPCA_57$clasesTrain ~ ., 
                     data = datosTrainModeloSinPCA_57, family = binomial(logit))

## ------------------------------------------------------------------------
library("glmnet")
a = cv.glmnet(x = as.matrix(datosTrainModeloPCA_29[,-1]), 
              y = as.matrix(datosTrainModeloPCA_29[,1]), alpha = 0)
mejorLambda = a$lambda.min
# Sin regularización
glmnet(x = as.matrix(datosTrainModeloPCA_29[,-1]), 
       y = as.matrix(datosTrainModeloPCA_29[,1]), alpha = 0, 
       lambda = 0, standardize = FALSE)

# Con regularización
glmnet(x = as.matrix(datosTrainModeloPCA_29[,-1]), 
       y = as.matrix(datosTrainModeloPCA_29[,1]), alpha = 0, 
       lambda = mejorLambda, standardize = FALSE)

## ------------------------------------------------------------------------
a = cv.glmnet(x = as.matrix(datosTrainModeloPCA_29[,-1]), 
              y = as.matrix(datosTrainModeloPCA_29[,1]), alpha = 0)
mejorLambda = a$lambda.min
# Si usamos alpha = 0 hace WD
glmnetPCA_29 = glmnet(x = as.matrix(datosTrainModeloPCA_29[,-1]), 
                      y = as.matrix(datosTrainModeloPCA_29[,1]), alpha = 0, 
                      lambda = mejorLambda, standardize = FALSE)

a = cv.glmnet(x = as.matrix(datosTrainModeloSinPCA_29[,-1]), 
              y = as.matrix(datosTrainModeloSinPCA_29[,1]), alpha = 0)
mejorLambda = a$lambda.min
glmnetSinPCA_29 = glmnet(x = as.matrix(datosTrainModeloSinPCA_29[,-1]),
                         y = as.matrix(datosTrainModeloSinPCA_29[,1]), alpha = 0, 
                         lambda = mejorLambda, standardize = FALSE)

a = cv.glmnet(x = as.matrix(datosTrainModeloPCA_36[,-1]), 
              y = as.matrix(datosTrainModeloPCA_36[,1]), alpha = 0)
mejorLambda = a$lambda.min
glmnetPCA_36 = glmnet(x = as.matrix(datosTrainModeloPCA_36[,-1]), 
                      y = as.matrix(datosTrainModeloPCA_36[,1]), alpha = 0, 
                      lambda = mejorLambda, standardize = FALSE)

a = cv.glmnet(x = as.matrix(datosTrainModeloSinPCA_36[,-1]), 
              y = as.matrix(datosTrainModeloSinPCA_36[,1]), alpha = 0)
mejorLambda = a$lambda.min
glmnetSinPCA_36 = glmnet(x = as.matrix(datosTrainModeloSinPCA_36[,-1]), 
                         y = as.matrix(datosTrainModeloSinPCA_36[,1]), alpha = 0, 
                         lambda = mejorLambda, standardize = FALSE)

a = cv.glmnet(x = as.matrix(datosTrainModeloPCA_57[,-1]), 
              y = as.matrix(datosTrainModeloPCA_57[,1]), alpha = 0)
mejorLambda = a$lambda.min
glmnetPCA_57 = glmnet(x = as.matrix(datosTrainModeloPCA_57[,-1]), 
                      y = as.matrix(datosTrainModeloPCA_57[,1]), alpha = 0, 
                      lambda = mejorLambda, standardize = FALSE)

a = cv.glmnet(x = as.matrix(datosTrainModeloSinPCA_57[,-1]), 
              y = as.matrix(datosTrainModeloSinPCA_57[,1]), alpha = 0)
mejorLambda = a$lambda.min
glmnetSinPCA_57 = glmnet(x = as.matrix(datosTrainModeloSinPCA_57[,-1]), 
                         y = as.matrix(datosTrainModeloSinPCA_57[,1]), alpha = 0, 
                         lambda = mejorLambda, standardize = FALSE)

## ------------------------------------------------------------------------
datos = as.data.frame(datosTrainModeloPCA_29[,-1])
# Recuperamos los nombres del data.frame
names = names(datosTrainModeloPCA_29)[-1]
names(datos) = names

#Intentamos aplicar una transformación polinomial
#poly(as.matrix(datos), 2)

## ------------------------------------------------------------------------
dfAux = as.data.frame(datosTrainModeloPCA_1[,-1])
dfAux2 = as.data.frame(datosTrainModeloSinPCA_1[,-1])
names1 = names(datosTrainModeloPCA_1)[-1]
names2 = names(datosTrainModeloSinPCA_1)[-1]
names(dfAux) = names1
names(dfAux2) = names2

probTrainModeloPCA_1 = predict(glmPCA_1, dfAux, type="response")
predTrainModeloPCA_1 = rep(0, length(probTrainModeloPCA_1))
predTrainModeloPCA_1[probTrainModeloPCA_1 >=0.5] = 1
errorTrainModeloPCA_1 = mean(predTrainModeloPCA_1 != clasesTrain)
cat("Error dentro de la muestra (E_Train) usando el modelo glmPCA_1:", 
    errorTrainModeloPCA_1, "\n")

probTrainModeloSinPCA_1 = predict(glmSinPCA_1, dfAux2, type="response")
predTrainModeloSinPCA_1 = rep(0, length(probTrainModeloSinPCA_1))
predTrainModeloSinPCA_1[probTrainModeloSinPCA_1 >=0.5] = 1
errorTrainModeloSinPCA_1 = mean(predTrainModeloSinPCA_1 != clasesTrain)
cat("Error dentro de la muestra (E_Train) usando el modelo glmSinPCA_1:", 
    errorTrainModeloSinPCA_1, "\n")

probTrainModeloPCA_29 = predict(glmPCA_29, as.data.frame(datosTrainModeloPCA_29[,-1]), 
                                type="response")
predTrainModeloPCA_29 = rep(0, length(probTrainModeloPCA_29))
predTrainModeloPCA_29[probTrainModeloPCA_29 >=0.5] = 1
errorTrainModeloPCA_29 = mean(predTrainModeloPCA_29 != clasesTrain)
cat("Error dentro de la muestra (E_Train) usando el modelo glmPCA_29:", 
    errorTrainModeloPCA_29, "\n")

probTrainModeloSinPCA_29 = predict(glmSinPCA_29, as.data.frame(datosTrainModeloSinPCA_29[,-1]), 
                                   type="response")
predTrainModeloSinPCA_29 = rep(0, length(probTrainModeloSinPCA_29))
predTrainModeloSinPCA_29[probTrainModeloSinPCA_29 >=0.5] = 1
errorTrainModeloSinPCA_29 = mean(predTrainModeloSinPCA_29 != clasesTrain)
cat("Error dentro de la muestra (E_Train) usando el modelo glmSinPCA_29:", 
    errorTrainModeloSinPCA_29, "\n")

probTrainModeloPCA_36 = predict(glmPCA_36, as.data.frame(datosTrainModeloPCA_36[,-1]), 
                                type="response")
predTrainModeloPCA_36 = rep(0, length(probTrainModeloPCA_36))
predTrainModeloPCA_36[probTrainModeloPCA_36 >=0.5] = 1
errorTrainModeloPCA_36 = mean(predTrainModeloPCA_36 != clasesTrain)
cat("Error dentro de la muestra (E_Train) usando el modelo glmPCA_36:", 
    errorTrainModeloPCA_36, "\n")

probTrainModeloSinPCA_36 = predict(glmSinPCA_36, as.data.frame(datosTrainModeloSinPCA_36[,-1]), 
                                   type="response")
predTrainModeloSinPCA_36 = rep(0, length(probTrainModeloSinPCA_36))
predTrainModeloSinPCA_36[probTrainModeloSinPCA_36 >=0.5] = 1
errorTrainModeloSinPCA_36 = mean(predTrainModeloSinPCA_36 != clasesTrain)
cat("Error dentro de la muestra (E_Train) usando el modelo glmSinPCA_36:", 
    errorTrainModeloSinPCA_36, "\n")

probTrainModeloPCA_57 = predict(glmPCA_57, as.data.frame(datosTrainModeloPCA_57[,-1]), 
                                type="response")
predTrainModeloPCA_57 = rep(0, length(probTrainModeloPCA_57))
predTrainModeloPCA_57[probTrainModeloPCA_57 >=0.5] = 1
errorTrainModeloPCA_57 = mean(predTrainModeloPCA_57 != clasesTrain)
cat("Error dentro de la muestra (E_Train) usando el modelo glmPCA_57:", 
    errorTrainModeloPCA_57, "\n")

probTrainModeloSinPCA_57 = predict(glmSinPCA_57, as.data.frame(datosTrainModeloSinPCA_57[,-1]), 
                                   type="response")
predTrainModeloSinPCA_57 = rep(0, length(probTrainModeloSinPCA_57))
predTrainModeloSinPCA_57[probTrainModeloSinPCA_57 >=0.5] = 1
errorTrainModeloSinPCA_57 = mean(predTrainModeloSinPCA_57 != clasesTrain)
cat("Error dentro de la muestra (E_Train) usando el modelo glmSinPCA_57:", 
    errorTrainModeloSinPCA_57, "\n")

## ------------------------------------------------------------------------
probTestModeloPCA_1 = predict(glmPCA_1, datosTestModeloPCA_1, type="response")
predTestModeloPCA_1 = rep(0, length(probTestModeloPCA_1))
predTestModeloPCA_1[probTestModeloPCA_1 >=0.5] = 1
errorModeloPCA_1 = mean(predTestModeloPCA_1 != clasesTest)
cat("Error fuera de la muestra (E_test) usando el modelo glmPCA_1:", 
    errorModeloPCA_1, "\n")

probTestModeloSinPCA_1 = predict(glmSinPCA_1, datosTestModeloSinPCA_1, type="response")
predTestModeloSinPCA_1 = rep(0, length(probTestModeloSinPCA_1))
predTestModeloSinPCA_1[probTestModeloSinPCA_1 >=0.5] = 1
errorModeloSinPCA_1 = mean(predTestModeloSinPCA_1 != clasesTest)
cat("Error fuera de la muestra (E_test) usando el modelo glmSinPCA_1:", 
    errorModeloSinPCA_1, "\n")

probTestModeloPCA_29 = predict(glmPCA_29, datosTestModeloPCA_29, type="response")
predTestModeloPCA_29 = rep(0, length(probTestModeloPCA_29))
predTestModeloPCA_29[probTestModeloPCA_29 >=0.5] = 1
errorModeloPCA_29 = mean(predTestModeloPCA_29 != clasesTest)
cat("Error fuera de la muestra (E_test) usando el modelo glmPCA_29:", 
    errorModeloPCA_29, "\n")

probTestModeloSinPCA_29 = predict(glmSinPCA_29, datosTestModeloSinPCA_29, type="response")
predTestModeloSinPCA_29 = rep(0, length(probTestModeloSinPCA_29))
predTestModeloSinPCA_29[probTestModeloSinPCA_29 >=0.5] = 1
errorModeloSinPCA_29 = mean(predTestModeloSinPCA_29 != clasesTest)
cat("Error fuera de la muestra (E_test) usando el modelo glmSinPCA_29:", 
    errorModeloSinPCA_29, "\n")

probTestModeloPCA_36 = predict(glmPCA_36, datosTestModeloPCA_36, type="response")
predTestModeloPCA_36 = rep(0, length(probTestModeloPCA_36))
predTestModeloPCA_36[probTestModeloPCA_36 >=0.5] = 1
errorModeloPCA_36 = mean(predTestModeloPCA_36 != clasesTest)
cat("Error fuera de la muestra (E_test) usando el modelo glmPCA_36:", 
    errorModeloPCA_36, "\n")

probTestModeloSinPCA_36 = predict(glmSinPCA_36, datosTestModeloSinPCA_36, type="response")
predTestModeloSinPCA_36 = rep(0, length(probTestModeloSinPCA_36))
predTestModeloSinPCA_36[probTestModeloSinPCA_36 >=0.5] = 1
errorModeloSinPCA_36 = mean(predTestModeloSinPCA_36 != clasesTest)
cat("Error fuera de la muestra (E_test) usando el modelo glmSinPCA_36:", 
    errorModeloSinPCA_36, "\n")

probTestModeloPCA_57 = predict(glmPCA_57, datosTestModeloPCA_57, type="response")
predTestModeloPCA_57 = rep(0, length(probTestModeloPCA_57))
predTestModeloPCA_57[probTestModeloPCA_57 >=0.5] = 1
errorModeloPCA_57 = mean(predTestModeloPCA_57 != clasesTest)
cat("Error fuera de la muestra (E_test) usando el modelo glmPCA_57:", 
    errorModeloPCA_57, "\n")

probTestModeloSinPCA_57 = predict(glmSinPCA_57, datosTestModeloSinPCA_57, type="response")
predTestModeloSinPCA_57 = rep(0, length(probTestModeloSinPCA_57))
predTestModeloSinPCA_57[probTestModeloSinPCA_57 >=0.5] = 1
errorModeloSinPCA_57 = mean(predTestModeloSinPCA_57 != clasesTest)
cat("Error fuera de la muestra (E_test) usando el modelo glmSinPCA_57:", 
    errorModeloSinPCA_57, "\n")

## ------------------------------------------------------------------------
probRegTestModeloPCA_29 = predict(glmnetPCA_29, s = mejorLambda, 
                                  newx = as.matrix(datosTestModeloPCA_29))
predRegTestModeloPCA_29 = rep(0, length(probRegTestModeloPCA_29))
predRegTestModeloPCA_29[probRegTestModeloPCA_29 >=0.5] = 1
errorRegTestModeloPCA_29 = mean(predRegTestModeloPCA_29 != clasesTest)
cat("Error fuera de la muestra (E_test) usando el modelo glmnetPCA_29:",
    errorRegTestModeloPCA_29, "\n")

probRegTestModeloSinPCA_29 = predict(glmnetSinPCA_29, s = mejorLambda, 
                                     newx = as.matrix(datosTestModeloSinPCA_29))
predRegTestModeloSinPCA_29 = rep(0, length(probRegTestModeloSinPCA_29))
predRegTestModeloSinPCA_29[probRegTestModeloSinPCA_29 >=0.5] = 1
errorRegTestModeloSinPCA_29 = mean(predRegTestModeloSinPCA_29 != clasesTest)
cat("Error fuera de la muestra (E_test) usando el modelo glmnetSinPCA_29:",
    errorRegTestModeloSinPCA_29, "\n")

probRegTestModeloPCA_36 = predict(glmnetPCA_36, s = mejorLambda, 
                                  newx = as.matrix(datosTestModeloPCA_36))
predRegTestModeloPCA_36 = rep(0, length(probRegTestModeloPCA_36))
predRegTestModeloPCA_36[probRegTestModeloPCA_36 >=0.5] = 1
errorRegTestModeloPCA_36 = mean(predRegTestModeloPCA_36 != clasesTest)
cat("Error fuera de la muestra (E_test) usando el modelo glmnetPCA_36:",
    errorRegTestModeloPCA_36, "\n")

probRegTestModeloSinPCA_36 = predict(glmnetSinPCA_36, s = mejorLambda, 
                                     newx = as.matrix(datosTestModeloSinPCA_36))
predRegTestModeloSinPCA_36 = rep(0, length(probRegTestModeloSinPCA_36))
predRegTestModeloSinPCA_36[probRegTestModeloSinPCA_36 >=0.5] = 1
errorRegTestModeloSinPCA_36 = mean(predRegTestModeloSinPCA_36 != clasesTest)
cat("Error fuera de la muestra (E_test) usando el modelo glmnetSinPCA_36:",
    errorRegTestModeloSinPCA_36, "\n")

probRegTestModeloPCA_57 = predict(glmnetPCA_57, s = mejorLambda, 
                                  newx = as.matrix(datosTestModeloPCA_57))
predRegTestModeloPCA_57 = rep(0, length(probRegTestModeloPCA_57))
predRegTestModeloPCA_57[probRegTestModeloPCA_57 >=0.5] = 1
errorRegTestModeloPCA_57 = mean(predRegTestModeloPCA_57 != clasesTest)
cat("Error fuera de la muestra (E_test) usando el modelo glmnetPCA_57:",
    errorRegTestModeloPCA_57, "\n")

probRegTestModeloSinPCA_57 = predict(glmnetSinPCA_57, s = mejorLambda, 
                                     newx = as.matrix(datosTestModeloSinPCA_57))
predRegTestModeloSinPCA_57 = rep(0, length(probRegTestModeloSinPCA_57))
predRegTestModeloSinPCA_57[probRegTestModeloSinPCA_57 >=0.5] = 1
errorRegTestModeloSinPCA_57 = mean(predRegTestModeloSinPCA_57 != clasesTest)
cat("Error fuera de la muestra (E_test) usando el modelo glmnetSinPCA_57:",
    errorRegTestModeloSinPCA_57, "\n")

## ------------------------------------------------------------------------
table(predTestModeloPCA_1, clasesTest)
table(predTestModeloSinPCA_1, clasesTest)
table(predTestModeloPCA_29, clasesTest)
table(predTestModeloSinPCA_29, clasesTest)
table(predTestModeloPCA_36, clasesTest)
table(predTestModeloSinPCA_36, clasesTest)
table(predTestModeloPCA_57, clasesTest)
table(predTestModeloSinPCA_57, clasesTest)

## ------------------------------------------------------------------------
library("ROCR")
prediccionTestModeloPCA_1 = prediction(probTestModeloPCA_1, clasesTest)
rendTestModeloPCA_1 = performance(prediccionTestModeloPCA_1,"tpr","fpr")

prediccionTestModeloSinPCA_1 = prediction(probTestModeloSinPCA_1, clasesTest)
rendTestModeloSinPCA_1 = performance(prediccionTestModeloSinPCA_1,"tpr","fpr")

prediccionTestModeloPCA_29 = prediction(probTestModeloPCA_29, clasesTest)
rendTestModeloPCA_29 = performance(prediccionTestModeloPCA_29,"tpr","fpr")

prediccionTestModeloSinPCA_29 = prediction(probTestModeloSinPCA_29, clasesTest)
rendTestModeloSinPCA_29 = performance(prediccionTestModeloSinPCA_29,"tpr","fpr")

prediccionTestModeloPCA_36 = prediction(probTestModeloPCA_36, clasesTest)
rendTestModeloPCA_36 = performance(prediccionTestModeloPCA_36,"tpr","fpr")

prediccionTestModeloSinPCA_36 = prediction(probTestModeloSinPCA_36, clasesTest)
rendTestModeloSinPCA_36 = performance(prediccionTestModeloSinPCA_36,"tpr","fpr")

prediccionTestModeloPCA_57 = prediction(probTestModeloPCA_57, clasesTest)
rendTestModeloPCA_57 = performance(prediccionTestModeloPCA_57,"tpr","fpr")

prediccionTestModeloSinPCA_57 = prediction(probTestModeloSinPCA_57, clasesTest)
rendTestModeloSinPCA_57 = performance(prediccionTestModeloSinPCA_57,"tpr","fpr")


plot(rendTestModeloPCA_1, col = 1)
plot(rendTestModeloSinPCA_1, add = T, col = 2)
plot(rendTestModeloPCA_29, add = T, col = 3)
plot(rendTestModeloSinPCA_29, add = T, col = 4)
plot(rendTestModeloPCA_36, add = T, col = 5)
plot(rendTestModeloSinPCA_36, add = T, col = 6)
plot(rendTestModeloPCA_57, add = T, col = 7)
plot(rendTestModeloSinPCA_57, add = T, col = 8)

## ------------------------------------------------------------------------
library("pracma")

cat("Area debajo de la curva rendTestModeloPCA_1:", 
    trapz(unlist(rendTestModeloPCA_1@x.values), unlist(rendTestModeloPCA_1@y.values)),
    "\n")
cat("Area debajo de la curva rendTestModeloSinPCA_1:", 
    trapz(unlist(rendTestModeloSinPCA_1@x.values), unlist(rendTestModeloSinPCA_1@y.values)),
    "\n")

cat("Area debajo de la curva rendTestModeloPCA_29:", 
    trapz(unlist(rendTestModeloPCA_29@x.values), unlist(rendTestModeloPCA_29@y.values)),
    "\n")
cat("Area debajo de la curva rendTestModeloSinPCA_29:", 
    trapz(unlist(rendTestModeloSinPCA_29@x.values), unlist(rendTestModeloSinPCA_29@y.values)),
    "\n")

cat("Area debajo de la curva rendTestModeloPCA_36:", 
    trapz(unlist(rendTestModeloPCA_36@x.values), unlist(rendTestModeloPCA_36@y.values)),
    "\n")
cat("Area debajo de la curva rendTestModeloSinPCA_36:", 
    trapz(unlist(rendTestModeloSinPCA_36@x.values), unlist(rendTestModeloSinPCA_36@y.values)),
    "\n")

cat("Area debajo de la curva rendTestModeloPCA_58:", 
    trapz(unlist(rendTestModeloPCA_57@x.values), unlist(rendTestModeloPCA_57@y.values)),
    "\n")
cat("Area debajo de la curva rendTestModeloSinPCA_58:", 
    trapz(unlist(rendTestModeloSinPCA_57@x.values), unlist(rendTestModeloSinPCA_57@y.values)),
    "\n")

## ------------------------------------------------------------------------
prostate = read.table("./datos/prostate.data", sep=" ", head=T)
# Quitamos el identificador
prostate = prostate[,-1]
# y el indicar de si va a train o no
trainTest = prostate[,dim(prostate)[2]]
prostate = prostate[,-dim(prostate)[2]]
# Vemos como debemos particionar los conjuntos
indexTrain = which(trainTest == T)
indexTest = which(trainTest == F)
train = prostate[indexTrain,]
test = prostate[indexTest,]

## ------------------------------------------------------------------------
library("caret")

ObjetoTrans = preProcess(train, method = c("YeoJohnson", "center", "scale"), thresh=1)
train = predict(ObjetoTrans, train)
test = predict(ObjetoTrans, test)

## ------------------------------------------------------------------------
library("leaps")

subset = regsubsets(train$lpsa ~ . , data = train, nvmax = dim(train)[2], method = "forward")
summary = summary(subset)

## ------------------------------------------------------------------------
summary$outmat

## ------------------------------------------------------------------------
par(mfrow=c(1,2))
plot(summary$cp, xlab = "Número de variables.", ylab = "CP", type = "l")
plot(summary$bic, xlab = "Número de variables.", ylab = "BIC", type = "l")

cat("Mejor número de características - CP:", which.min(summary$cp), "\n")
cat("Mejor número de características - BIC:", which.min(summary$bic), "\n")

## ------------------------------------------------------------------------
as.vector(which(summary$outmat[7,] == "*"))
as.vector(which(summary$outmat[3,] == "*"))

## ------------------------------------------------------------------------
as.vector(which(summary$outmat[1,] == "*"))

## ------------------------------------------------------------------------
datosTrainModelo_1 = as.data.frame(train[, c(as.vector(which(summary$outmat[1,] == "*")),
                                             dim(train)[2])])
datosTrainModelo_3 = as.data.frame(train[, c(as.vector(which(summary$outmat[3,] == "*")),
                                             dim(train)[2])])
datosTrainModelo_7 = as.data.frame(train[, c(as.vector(which(summary$outmat[7,] == "*")),
                                             dim(train)[2])])
datosTrainModelo_8 = as.data.frame(train)

datosTestModelo_1 = as.data.frame(test[, c(as.vector(which(summary$outmat[1,] == "*")),
                                           dim(train)[2])])

datosTestModelo_3 = as.data.frame(test[, c(as.vector(which(summary$outmat[3,] == "*")),
                                           dim(train)[2])])
datosTestModelo_7 = as.data.frame(test[, c(as.vector(which(summary$outmat[7,] == "*")),
                                           dim(train)[2])])
datosTestModelo_8 = as.data.frame(test)

# Una vez tenemos los conjuntos de datos, aprendemos los modelos
# Usamos regresión lineal
glm_1 = glm(datosTrainModelo_1$lpsa ~ ., data = datosTrainModelo_1)
glm_3 = glm(datosTrainModelo_3$lpsa ~ ., data = datosTrainModelo_3)
glm_7 = glm(datosTrainModelo_7$lpsa ~ ., data = datosTrainModelo_7)
glm_8 = glm(datosTrainModelo_8$lpsa ~ ., data = datosTrainModelo_8)

## ------------------------------------------------------------------------
library("glmnet")
a = cv.glmnet(x = as.matrix(datosTrainModelo_3[,-dim(datosTrainModelo_3)[2]]), 
              y = as.matrix(datosTrainModelo_3$lpsa), alpha = 0)
mejorLambda_3 = a$lambda.min
# Sin regularización
glmnet(x = as.matrix(datosTrainModelo_3[,-dim(datosTrainModelo_3)[2]]), 
       y = as.matrix(datosTrainModelo_3$lpsa), alpha = 0, 
       lambda = 0, standardize = FALSE)

# Con regularización
glmnet(x = as.matrix(datosTrainModelo_3[,-dim(datosTrainModelo_3)[2]]), 
       y = as.matrix(datosTrainModelo_3$lpsa), alpha = 0, 
       lambda = mejorLambda_3, standardize = FALSE)

## ------------------------------------------------------------------------
a = cv.glmnet(x = as.matrix(datosTrainModelo_3[,-dim(datosTrainModelo_3)[2]]), 
              y = as.matrix(datosTrainModelo_3$lpsa), alpha = 0)
mejorLambda_3 = a$lambda.min
# Si usamos alpha = 0 hace WD
glmnet_3 = glmnet(x = as.matrix(datosTrainModelo_3[,-dim(datosTrainModelo_3)[2]]), 
                  y = as.matrix(datosTrainModelo_3$lpsa), alpha = 0, 
                  lambda = mejorLambda_3, standardize = FALSE)

a = cv.glmnet(x = as.matrix(datosTrainModelo_7[,-dim(datosTrainModelo_7)[2]]), 
              y = as.matrix(datosTrainModelo_7$lpsa), alpha = 0)
mejorLambda_7 = a$lambda.min
glmnet_7 = glmnet(x = as.matrix(datosTrainModelo_7[,-dim(datosTrainModelo_7)[2]]), 
                  y = as.matrix(datosTrainModelo_7$lpsa), alpha = 0, 
                  lambda = mejorLambda_7, standardize = FALSE)

a = cv.glmnet(x = as.matrix(datosTrainModelo_8[,-dim(datosTrainModelo_8)[2]]), 
              y = as.matrix(datosTrainModelo_8$lpsa), alpha = 0)
mejorLambda_8 = a$lambda.min
glmnet_8 = glmnet(x = as.matrix(datosTrainModelo_8[,-dim(datosTrainModelo_8)[2]]), 
                  y = as.matrix(datosTrainModelo_8$lpsa), alpha = 0, 
                  lambda = mejorLambda_8, standardize = FALSE)

## ------------------------------------------------------------------------
datosTransformadosTrainModelo_1 = cbind(as.data.frame(polym(datosTrainModelo_1$lcavol, 
                                                            degree = 2, raw = T)), 
                                        datosTrainModelo_1$lpsa)

datosTransformadosTrainModelo_3 = cbind(as.data.frame(polym(datosTrainModelo_3$lcavol, 
                                                            datosTrainModelo_3$lweight, 
                                                            datosTrainModelo_3$pgg45, 
                                                            degree = 2, raw = T)), 
                                        datosTrainModelo_3$lpsa)

datosTransformadosTrainModelo_7 = cbind(as.data.frame(polym(datosTrainModelo_7$lcavol, 
                                                            datosTrainModelo_7$lweight, 
                                                            datosTrainModelo_7$age, 
                                                            datosTrainModelo_7$lbph, 
                                                            datosTrainModelo_7$svi, 
                                                            datosTrainModelo_7$lcp, 
                                                            datosTrainModelo_7$pgg45, 
                                                            degree = 2, raw = T)), 
                                        datosTrainModelo_7$lpsa)

datosTransformadosTrainModelo_8 = cbind(as.data.frame(polym(datosTrainModelo_8$lcavol, 
                                                            datosTrainModelo_8$lweight, 
                                                            datosTrainModelo_8$age, 
                                                            datosTrainModelo_8$lbph, 
                                                            datosTrainModelo_8$svi, 
                                                            datosTrainModelo_8$lcp, 
                                                            datosTrainModelo_8$gleason, 
                                                            datosTrainModelo_8$pgg45, 
                                                            degree = 2, raw = T)), 
                                        datosTrainModelo_8$lpsa)

names = names(datosTransformadosTrainModelo_1)
names(datosTransformadosTrainModelo_1) = c(names[-length(names)], "lpsa")
names = names(datosTransformadosTrainModelo_3)
names(datosTransformadosTrainModelo_3) = c(names[-length(names)], "lpsa")
names = names(datosTransformadosTrainModelo_7)
names(datosTransformadosTrainModelo_7) = c(names[-length(names)], "lpsa")
names = names(datosTransformadosTrainModelo_8)
names(datosTransformadosTrainModelo_8) = c(names[-length(names)], "lpsa")


datosTransformadosTestModelo_1 = cbind(as.data.frame(polym(datosTestModelo_1$lcavol, 
                                                           degree = 2, raw = T)), 
                                       datosTestModelo_1$lpsa)

datosTransformadosTestModelo_3 = cbind(as.data.frame(polym(datosTestModelo_3$lcavol, 
                                                          datosTestModelo_3$lweight, 
                                                           datosTestModelo_3$pgg45, 
                                                           degree = 2, raw = T)), 
                                       datosTestModelo_3$lpsa)

datosTransformadosTestModelo_7 = cbind(as.data.frame(polym(datosTestModelo_7$lcavol, 
                                                           datosTestModelo_7$lweight, 
                                                           datosTestModelo_7$age, 
                                                           datosTestModelo_7$lbph, 
                                                           datosTestModelo_7$svi, 
                                                           datosTestModelo_7$lcp, 
                                                           datosTestModelo_7$pgg45, 
                                                           degree = 2, raw = T)), 
                                       datosTestModelo_7$lpsa)

datosTransformadosTestModelo_8 = cbind(as.data.frame(polym(datosTestModelo_8$lcavol, 
                                                           datosTestModelo_8$lweight, 
                                                           datosTestModelo_8$age, 
                                                           datosTestModelo_8$lbph, 
                                                           datosTestModelo_8$svi, 
                                                           datosTestModelo_8$lcp, 
                                                           datosTestModelo_8$gleason, 
                                                           datosTestModelo_8$pgg45, 
                                                           degree = 2, raw = T)), 
                                       datosTestModelo_8$lpsa)

names = names(datosTransformadosTestModelo_1)
names(datosTransformadosTestModelo_1) = c(names[-length(names)], "lpsa")
names = names(datosTransformadosTestModelo_3)
names(datosTransformadosTestModelo_3) = c(names[-length(names)], "lpsa")
names = names(datosTransformadosTestModelo_7)
names(datosTransformadosTestModelo_7) = c(names[-length(names)], "lpsa")
names = names(datosTransformadosTestModelo_8)
names(datosTransformadosTestModelo_8) = c(names[-length(names)], "lpsa")

## ------------------------------------------------------------------------
glmTransformados_1 = glm(datosTransformadosTrainModelo_1$lpsa ~ ., 
                         data = datosTransformadosTrainModelo_1)
glmTransformados_3 = glm(datosTransformadosTrainModelo_3$lpsa ~ ., 
                         data = datosTransformadosTrainModelo_3)
glmTransformados_7 = glm(datosTransformadosTrainModelo_7$lpsa ~ ., 
                         data = datosTransformadosTrainModelo_7)
glmTransformados_8 = glm(datosTransformadosTrainModelo_8$lpsa ~ ., 
                         data = datosTransformadosTrainModelo_8)

## ------------------------------------------------------------------------
probTrainModelo1 = predict(glm_1, as.data.frame(datosTrainModelo_1), 
                           type="response", exact = T)
cat("Error dentro de la muestra (E_Train) usando el modelo glm_1:", 
    mean((probTrainModelo1 - datosTrainModelo_1$lpsa)^2), "\n")

probTrainModelo3 = predict(glm_3, as.data.frame(datosTrainModelo_3), 
                           type="response", exact = T)
cat("Error dentro de la muestra (E_Train) usando el modelo glm_3:", 
    mean((probTrainModelo3 - datosTrainModelo_3$lpsa)^2), "\n")

probTrainModelo7 = predict(glm_7, as.data.frame(datosTrainModelo_7), 
                           type="response", exact = T)
cat("Error dentro de la muestra (E_Train) usando el modelo glm_7:", 
    mean((probTrainModelo7 - datosTrainModelo_7$lpsa)^2), "\n")

probTrainModelo8 = predict(glm_8, as.data.frame(datosTrainModelo_8), 
                           type="response", exact = T)
cat("Error dentro de la muestra (E_Train) usando el modelo glm_8:", 
    mean((probTrainModelo8 - datosTrainModelo_8$lpsa)^2), "\n")

probTestModelo1 = predict(glm_1, as.data.frame(datosTestModelo_1), 
                           type="response", exact = T)
cat("Error fuera de la muestra (E_Test) usando el modelo glm_1:", 
    mean((probTestModelo1 - datosTestModelo_1$lpsa)^2), "\n")

probTestModelo3 = predict(glm_3, as.data.frame(datosTestModelo_3), 
                           type="response", exact = T)
cat("Error fuera de la muestra (E_Test) usando el modelo glm_3:", 
    mean((probTestModelo3 - datosTestModelo_3$lpsa)^2), "\n")

probTestModelo7 = predict(glm_7, as.data.frame(datosTestModelo_7), 
                           type="response", exact = T)
cat("Error fuera de la muestra (E_Test) usando el modelo glm_7:", 
    mean((probTestModelo7 - datosTestModelo_7$lpsa)^2), "\n")

probTestModelo8 = predict(glm_8, as.data.frame(datosTestModelo_8), 
                           type="response", exact = T)
cat("Error fuera de la muestra (E_Test) usando el modelo glm_8:", 
    mean((probTestModelo8 - datosTestModelo_8$lpsa)^2), "\n")

## ------------------------------------------------------------------------
probTrainModeloReg3 = predict(glmnet_3, s = mejorLambda_3, 
                             newx = as.matrix(datosTrainModelo_3[,-dim(datosTrainModelo_3)[2]]))
cat("Error dentro de la muestra (E_Train) usando el modelo glmnet_3:", 
    mean((probTrainModeloReg3 - datosTrainModelo_3$lpsa)^2), "\n")

probTrainModeloReg7 = predict(glmnet_7, s = mejorLambda_7, 
                             newx = as.matrix(datosTrainModelo_7[,-dim(datosTrainModelo_7)[2]]))
cat("Error dentro de la muestra (E_Train) usando el modelo glmnet_7:", 
    mean((probTrainModeloReg7 - datosTrainModelo_7$lpsa)^2), "\n")

probTrainModeloReg8 = predict(glmnet_8, s = mejorLambda_8, 
                             newx = as.matrix(datosTrainModelo_8[,-dim(datosTrainModelo_8)[2]]))
cat("Error dentro de la muestra (E_Train) usando el modelo glmnet_8:", 
    mean((probTrainModeloReg8 - datosTrainModelo_8$lpsa)^2), "\n")


probTestModeloReg3 = predict(glmnet_3, s = mejorLambda_3, 
                             newx = as.matrix(datosTestModelo_3[,-dim(datosTestModelo_3)[2]]))
cat("Error fuera de la muestra (E_Test) usando el modelo glmnet_3:", 
    mean((probTestModeloReg3 - datosTestModelo_3$lpsa)^2), "\n")

probTestModeloReg7 = predict(glmnet_7, s = mejorLambda_7, 
                             newx = as.matrix(datosTestModelo_7[,-dim(datosTestModelo_7)[2]]))
cat("Error fuera de la muestra (E_Test) usando el modelo glmnet_7:", 
    mean((probTestModeloReg7 - datosTestModelo_7$lpsa)^2), "\n")

probTestModeloReg8 = predict(glmnet_8, s = mejorLambda_8, 
                             newx = as.matrix(datosTestModelo_8[,-dim(datosTestModelo_8)[2]]))
cat("Error fuera de la muestra (E_Test) usando el modelo glmnet_8:", 
    mean((probTestModeloReg8 - datosTestModelo_8$lpsa)^2), "\n")

## ------------------------------------------------------------------------
probTestTransformadosModelo1 = predict(glmTransformados_1, 
                                       as.data.frame(datosTransformadosTestModelo_1[, 
                                       -dim(datosTransformadosTestModelo_1)[2]]), 
                                       type="response", exact = T)
cat("Error fuera de la muestra (E_Test) usando el modelo glmTransformados_1:", 
    mean((probTestTransformadosModelo1 - datosTransformadosTestModelo_1$lpsa)^2), "\n")

probTestTransformadosModelo3 = predict(glmTransformados_3, 
                                       as.data.frame(datosTransformadosTestModelo_3[, 
                                       -dim(datosTransformadosTestModelo_3)[2]]), 
                                       type="response", exact = T)
cat("Error fuera de la muestra (E_Test) usando el modelo glmTransformados_3:", 
    mean((probTestTransformadosModelo3 - datosTransformadosTestModelo_3$lpsa)^2), "\n")

probTestTransformadosModelo7 = predict(glmTransformados_7, 
                                       as.data.frame(datosTransformadosTestModelo_7[, 
                                       -dim(datosTransformadosTestModelo_7)[2]]), 
                                       type="response", exact = T)
cat("Error fuera de la muestra (E_Test) usando el modelo glmTransformados_7:", 
    mean((probTestTransformadosModelo7 - datosTransformadosTestModelo_7$lpsa)^2), "\n")

probTestTransformadosModelo8 = predict(glmTransformados_8, 
                                       as.data.frame(datosTransformadosTestModelo_8[, 
                                       -dim(datosTransformadosTestModelo_8)[2]]), 
                                       type="response", exact = T)
cat("Error fuera de la muestra (E_Test) usando el modelo glmTransformados_8:", 
    mean((probTestTransformadosModelo8 - datosTransformadosTestModelo_8$lpsa)^2), "\n")

