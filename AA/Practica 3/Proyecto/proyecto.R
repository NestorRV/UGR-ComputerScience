# David López Pretel y Néstor Rodríguez Vico

## ----setup, include=FALSE------------------------------------------------
knitr::opts_chunk$set(echo = TRUE)

## ----Preparacion---------------------------------------------------------
set.seed(3)
suppressWarnings(suppressMessages(library("caret"))) # preProcess
suppressWarnings(suppressMessages(library("ROCR"))) # prediction
suppressWarnings(suppressMessages(library("pracma"))) # trapz

wdbc = read.csv("./Datos/wdbc.data", header = F, sep = ",", stringsAsFactors=FALSE)
# Eliminamos el identificador
wdbc = wdbc[, -1]
# Cambiamos el nombre de las columnas (por comodidad)
names(wdbc) = c("clase", 1:(dim(wdbc)[2]-1))
# Cambiamos la clase, Maligno por 1 y benigno por 0
clase = mapply(function(x) ifelse(x=="M", 1, 0), wdbc[,1], USE.NAMES = F)
wdbc = cbind(clase, wdbc[,-1])

# Comprobamos si hay valores NA
apply(wdbc, 2, function(x) sum(is.na(x)))

## ------------------------------------------------------------------------
reducir = function(lista, size, indice){
  if(length(unlist(lista)) > size){
    aux = unlist(lista, use.names = F)
    guardar = aux[length(aux)]
    aux = aux[-length(aux)]
    list(aux, guardar, indice)
  }
}

sobrantes = function(lista, size){
  sobrantes = c()
  for(i in 1:5){
    resultado = reducir(lista[i], size, i)
    if(!is.null(resultado)){
      lista[[resultado[[3]]]] = resultado[[1]]
      sobrantes = c(sobrantes, resultado[[2]])
    }
  }
  list(lista, sobrantes)
}

# Creamos los conjuntos de datos de manera balanceada
# y haciendo k-fold con k = 5 (80% train y 20% test)
pos = sample(which(wdbc[,1] == 1))
neg = sample(which(wdbc[,1] == 0))

# Separamos las tiquetas positivas y negativas
# para tener unos conjuntos balanceados
particiones_pos = split(pos, cut(seq_along(pos), 5, labels = F))
particiones_neg = split(neg, cut(seq_along(neg), 5, labels = F))
#Cogemos los datos de los indices según las particiones de los indices
wdbc.pos <- lapply(particiones_pos, function(part) wdbc[part,])
wdbc.neg <- lapply(particiones_neg, function(part) wdbc[part,])

#Debemos comprobar que sean todos del mismo tamaño, así que cogemos el mínimo
pos.size = min(unlist(lapply(particiones_pos, length)))
neg.size = min(unlist(lapply(particiones_neg, length)))

# Guardamos las asignaciones sobrantes
resultado = sobrantes(particiones_pos, pos.size)
particiones_pos = resultado[[1]]
pos.extras = as.vector(resultado[[2]])
resultado = sobrantes(particiones_neg, neg.size)
particiones_neg = resultado[[1]]
neg.extras = as.vector(resultado[[2]])
extras = c(pos.extras, neg.extras)

#Cogemos los datos de los indices según las particiones de los indices
wdbc.pos <- lapply(particiones_pos, function(part) wdbc[part,])
wdbc.neg <- lapply(particiones_neg, function(part) wdbc[part,])

#Generamos los cinco conjuntos
conjunto_1 = rbind(wdbc.pos[[1]], wdbc.neg[[1]])
conjunto_2 = rbind(wdbc.pos[[2]], wdbc.neg[[2]])
conjunto_3 = rbind(wdbc.pos[[3]], wdbc.neg[[3]])
conjunto_4 = rbind(wdbc.pos[[4]], wdbc.neg[[4]])
conjunto_5 = rbind(wdbc.pos[[5]], wdbc.neg[[5]])

#Añadimos lo que ha sobrado
l = list(conjunto_1, conjunto_2, conjunto_3, conjunto_4, conjunto_5)
for(i in 1:length(extras)){
  l[[i]] = rbind(l[[i]], wdbc[extras[i],])
}

# Ya tenemos los conjuntos creados (cada uno tiene el 20% de los datos)
conjunto_1 = l[[1]]
conjunto_2 = l[[2]]
conjunto_3 = l[[3]]
conjunto_4 = l[[4]]
conjunto_5 = l[[5]]

#Repartimos los conjuntos
test_1 = conjunto_1
train_1 = rbind(conjunto_2, conjunto_3, conjunto_4, conjunto_5)
test_2 = conjunto_2
train_2 = rbind(conjunto_1, conjunto_3, conjunto_4, conjunto_5)
test_3 = conjunto_3
train_3 = rbind(conjunto_1, conjunto_2, conjunto_4, conjunto_5)
test_4 = conjunto_4
train_4 = rbind(conjunto_1, conjunto_2, conjunto_3, conjunto_5)
test_5 = conjunto_5
train_5 = rbind(conjunto_1, conjunto_2, conjunto_3, conjunto_4)

## ----MLRLineal-----------------------------------------------------------
RegresionLineal = function(plot = F) {
  set.seed(3)
  par(mfrow=c(2,3))
  areas = NULL

  for(i in 1:5){
    # Preprocesamos los datos
    train = eval(as.name(paste0("train_", i)))
    test = eval(as.name(paste0("test_", i)))
    clase = train[,1]
    train = train[,-1]
    # No hacemos YeoJohnson porque da un warning por problemas de convergencia
    # "Convergence failure: return code = 52"
    obj = preProcess(train, method = c("center", "scale", "pca"), thresh=0.95)
    train = predict(obj, train)
    train = as.data.frame(cbind(clase, train))
    clase = test[,1]
    test = test[,-1]
    test = predict(obj, test)
    test = as.data.frame(cbind(clase, test))
    
    # Estimamos el modelo
    rlModel = glm(train$clase ~ ., data = train)
    
    # Obtenemos la curca ROC
    predict = predict(rlModel, as.data.frame(test[,-1]), type="response")
    prediction = prediction(predict, test$clase)
    rend = performance(prediction,"tpr","fpr")
    # Y el area debajo de la curva ROC
    area = trapz(unlist(rend@x.values), unlist(rend@y.values))
    # Guardamos el area
    areas[i] = area
    
    if(plot == T){
      plot(rend, col = i, main = "R. Lineal.") 
    }
  }
  areas
}

areaRLineal = RegresionLineal(plot = T)
cat("Area media bajo la curva ROC para un modelo lineal (regresión lineal):", 
    mean(areaRLineal), "\n")

## ----MLRLogistica--------------------------------------------------------
RegresionLogistica = function(plot = F) {
  set.seed(3)
  par(mfrow=c(2,3))
  areas = NULL

  for(i in 1:5){
    # Preprocesamos los datos
    train = eval(as.name(paste0("train_", i)))
    test = eval(as.name(paste0("test_", i)))
    clase = train[,1]
    train = train[,-1]
    # No hacemos YeoJohnson porque da un warning por problemas de convergencia
    # "Convergence failure: return code = 52"
    obj = preProcess(train, method = c("center", "scale", "pca"), thresh=0.95)
    train = predict(obj, train)
    train = as.data.frame(cbind(clase, train))
    clase = test[,1]
    test = test[,-1]
    test = predict(obj, test)
    test = as.data.frame(cbind(clase, test))
    
    # Estimamos el modelo
    rlModel = glm(train$clase ~ ., data = train, family = binomial(logit))
    
    # Obtenemos la curca ROC
    predict = predict(rlModel, as.data.frame(test[,-1]), type="response")
    prediction = prediction(predict, test$clase)
    rend = performance(prediction,"tpr","fpr")
    # Y el area debajo de la curva ROC
    area = trapz(unlist(rend@x.values), unlist(rend@y.values))
    
    # Guardamos el area
    areas[i] = area
    
    if(plot == T){
      plot(rend, col = i, main = "R. Logística.")
    }
  }
  areas
}

areaRlogistica = RegresionLogistica(plot = T)
cat("\nArea media bajo la curva ROC para un modelo lineal (regresión logística):", 
    mean(areaRlogistica), "\n")

## ----RN------------------------------------------------------------------
RedNeuronal = function(capas_ocultas = c(1), plot = F) {
  set.seed(3)
  par(mfrow=c(2,3))
  suppressWarnings(suppressMessages(library("neuralnet")))
  areas = NULL

  for(i in 1:5){
    # Preprocesamos los datos
    train = eval(as.name(paste0("train_", i)))
    test = eval(as.name(paste0("test_", i)))
    clase = train[,1]
    train = train[,-1]
    # No hacemos YeoJohnson porque da un warning por problemas de convergencia
    # "Convergence failure: return code = 52"
    obj = preProcess(train, method = c("center", "scale", "pca"), thresh=0.95)
    train = predict(obj, train)
    train = as.data.frame(cbind(clase, train))
    clase = test[,1]
    test = test[,-1]
    test = predict(obj, test)
    test = as.data.frame(cbind(clase, test))
    
    # Usamos una fórmula hecha a mano ya que la función neuralnet no admite
    # la sintaxis usada hasta ahora (y ~ x)
    f = as.formula(paste("clase ~", paste(names(train)[!names(train) %in% "clase"], 
                                          collapse = " + ")))
    
    # Estimamos el modelo
    # El argumento linear.output = F indica que queremos que se use la 
    # función de activación y que no queremos hacer regresión sino clasificación.
    nnModel = neuralnet(f, data=train, hidden=capas_ocultas, linear.output=F)
    
    # Obtenemos la curca ROC
    predict = compute(nnModel, test[,-1])
    # La función prediction está en ROCR y en neuralnet
    # así que da error tener los dos paquetes cargados a
    # la vez, así que tenemos que desactivar los dos y cargar
    # ROCR de nuevo
    detach("package:neuralnet", unload=TRUE)
    
    suppressWarnings(suppressMessages(library("ROCR")))
    prediction = prediction(predict$net.result, test$clase)
    rend = performance(prediction,"tpr","fpr")
    detach("package:ROCR", unload=TRUE)
    suppressWarnings(suppressMessages(library("neuralnet")))
    
    # Y el area debajo de la curva ROC
    area = trapz(unlist(rend@x.values), unlist(rend@y.values))
    # Guardamos el area
    areas[i] = area
    
    if(plot == T){
      plot(unlist(rend@x.values), unlist(rend@y.values), type = "l", 
           xlab = "False positive rate", ylab = "True positive rate", col = i, 
           main = paste("Capas:", paste(capas_ocultas, collapse = ",")))
    }
  }
  
  areas
}

area_1_1 = RedNeuronal(capas_ocultas = c(1), plot = T)
area_2_1 = RedNeuronal(capas_ocultas = c(1, 1), plot = T)
area_3_1 = RedNeuronal(capas_ocultas = c(1, 1, 1), plot = T)
area_1_10 = RedNeuronal(capas_ocultas = c(10), plot = T)
area_2_10 = RedNeuronal(capas_ocultas = c(10, 10), plot = T)
area_3_10 = RedNeuronal(capas_ocultas = c(10, 10, 10), plot = T)
area_1_25 = RedNeuronal(capas_ocultas = c(25), plot = T)
area_2_25 = RedNeuronal(capas_ocultas = c(25, 25), plot = T)
area_3_25 = RedNeuronal(capas_ocultas = c(25, 25, 25), plot = T)
area_1_50 = RedNeuronal(capas_ocultas = c(50), plot = T)
area_2_50 = RedNeuronal(capas_ocultas = c(50, 50), plot = T)
area_3_50 = RedNeuronal(capas_ocultas = c(50, 50, 50), plot = T)

area_3_1_5_10 = RedNeuronal(capas_ocultas = c(1, 5, 10), plot = T)
area_3_5_10_25 = RedNeuronal(capas_ocultas = c(5, 10, 25), plot = T)
area_3_10_25_50 = RedNeuronal(capas_ocultas = c(10, 25, 50), plot = T)

detach("package:neuralnet", unload=TRUE)
suppressWarnings(suppressMessages(library("ROCR")))

## ----SVM-----------------------------------------------------------------
SVM = function(plot = F) {
  set.seed(3)
  par(mfrow=c(2,3))
  suppressWarnings(suppressMessages(library("caret")))
  suppressWarnings(suppressMessages(library("kernlab")))
  areas = NULL

  for(i in 1:5){
    # Preprocesamos los datos
    train = eval(as.name(paste0("train_", i)))
    test = eval(as.name(paste0("test_", i)))
    clase = as.factor(train[,1])
    train = train[,-1]
    # No hacemos YeoJohnson porque da un warning por problemas de convergencia
    # "Convergence failure: return code = 52"
    obj = preProcess(train, method = c("center", "scale", "pca"), thresh=0.95)
    train = predict(obj, train)
    train = as.data.frame(cbind(clase, train))
    clase = as.factor(test[,1])
    test = test[,-1]
    test = predict(obj, test)
    test = as.data.frame(cbind(clase, test))
    
    # Estimamos los parámetros usando validación cruzada
    ctrl = trainControl(method="cv", summaryFunction=twoClassSummary, classProbs=T)
    tune = train(x=train[,-1], y = make.names(as.factor(train$clase)), 
                 method = "gaussprRadial", metric="ROC", trControl=ctrl)
    bestSigma = round(tune$bestTune[1,1], 2)
    
    # Estimamos el modelo
    # rbfdot: núcleo RBF-Gaussiano
    svmModelo = ksvm(train$clase ~ ., data=train, kernel="rbfdot", 
                     kpar=list(sigma=bestSigma))
    
    # Obtenemos la curca ROC
    predict = predict(svmModelo, as.data.frame(test[,-1]), type="response")
    prediction = prediction(as.numeric(predict), as.numeric(test$clase))
    rend = performance(prediction,"tpr","fpr")
    
    # Y el area debajo de la curva ROC
    area = trapz(unlist(rend@x.values), unlist(rend@y.values))
    # Guardamos el area
    areas[i] = area
    
    if(plot == T){
      plot(unlist(rend@x.values), unlist(rend@y.values), type = "l", 
           xlab = "False positive rate", ylab = "True positive rate", 
           col = i, main = paste0("sigma=", bestSigma))
    }
  }
  
  areas
}

areaSVM = SVM(plot = T)
cat("Area media bajo la curva ROC usando SVM:", mean(areaSVM), "\n")

## ----Boosting------------------------------------------------------------
Boosting = function(plot = F) {
  set.seed(3)
  par(mfrow=c(2,3))
  suppressWarnings(suppressMessages(library("ada")))
  areas = NULL

  for(i in 1:5){
    # Preprocesamos los datos
    train = eval(as.name(paste0("train_", i)))
    test = eval(as.name(paste0("test_", i)))
    clase = as.factor(train[,1])
    train = train[,-1]
    # No hacemos YeoJohnson porque da un warning por problemas de convergencia
    # "Convergence failure: return code = 52"
    obj = preProcess(train, method = c("center", "scale", "pca"), thresh=0.95)
    train = predict(obj, train)
    train = as.data.frame(cbind(clase, train))
    clase = as.factor(test[,1])
    test = test[,-1]
    test = predict(obj, test)
    test = as.data.frame(cbind(clase, test))
    
    # Estimamos los parámetros usando validación cruzada
    ctrl = trainControl(method="cv", summaryFunction=twoClassSummary, classProbs=T)
    tune = train(x=train[,-1], y = make.names(as.factor(train$clase)), method = "ada", 
                 metric="ROC", trControl=ctrl)
    
    # Estimamos el modelo
    boostingModelo = ada(train$clase ~ ., data=train, iter=tune$bestTune$iter, 
                         nu=tune$bestTune$nu, type="discrete",
                         control = rpart.control(maxdepth=1, cp=-1, 
                                                 minsplit = 0, xval = 0))
    
    # Obtenemos la curca ROC
    predict = predict(boostingModelo, as.data.frame(test[,-1]))
    prediction = prediction(as.numeric(predict), as.numeric(test$clase))
    rend = performance(prediction,"tpr","fpr")
    
    # Y el area debajo de la curva ROC
    area = trapz(unlist(rend@x.values), unlist(rend@y.values))
    # Guardamos el area
    areas[i] = area
    
    if(plot == T){
      plot(unlist(rend@x.values), unlist(rend@y.values), type = "l", 
           xlab = "False positive rate", ylab = "True positive rate", 
           col = i, main = paste0("nu=", tune$bestTune$nu, 
                                  ". iter=", tune$bestTune$iter))
    }
  }
  
  areas
}

areaBoosting = Boosting(plot = T)
cat("Area media bajo la curva ROC usando Boosting:", mean(areaBoosting), "\n")

## ----RF------------------------------------------------------------------
RandomForest = function(n_trees = 500, plot = F) {
  set.seed(3)
  par(mfrow=c(2,3))
  suppressWarnings(suppressMessages(library("randomForest")))
  areas = NULL

  for(i in 1:5){
    # Preprocesamos los datos
    train = eval(as.name(paste0("train_", i)))
    test = eval(as.name(paste0("test_", i)))
    clase = as.factor(train[,1])
    train = train[,-1]
    # No hacemos YeoJohnson porque da un warning por problemas de convergencia
    # "Convergence failure: return code = 52"
    obj = preProcess(train, method = c("center", "scale", "pca"), thresh=0.95)
    train = predict(obj, train)
    train = as.data.frame(cbind(clase, train))
    clase = as.factor(test[,1])
    test = test[,-1]
    test = predict(obj, test)
    test = as.data.frame(cbind(clase, test))
    
    # Estimamos el modelo
    rfModel = randomForest(train$clase ~ ., data = train, mtry = 
                             round(sqrt(dim(train)[2]-1)), ntree = n_trees)
    
    # Obtenemos la curca ROC
    predict = predict(rfModel, as.data.frame(test[,-1]), type="response")
    prediction = prediction(as.numeric(predict), as.numeric(test$clase))
    rend = performance(prediction,"tpr","fpr")
    
    # Y el area debajo de la curva ROC
    area = trapz(unlist(rend@x.values), unlist(rend@y.values))
    # Guardamos el area
    areas[i] = area
    
    if(plot == T){
      plot(unlist(rend@x.values), unlist(rend@y.values), type = "l", 
           xlab = "False positive rate", ylab = "True positive rate", 
           col = i, main = paste0("RF con ntree=", n_trees))
    }
  }
  
  areas
}

## ----ExperimentoArboles--------------------------------------------------
resultados = matrix(NA, ncol = 2)
for(i in seq(100, 5000, 100)){
  area = RandomForest(n_trees = i, plot = F)
  resultados = rbind(resultados, c(i, mean(area)))
}
resultados = resultados[-1,]

par(mfrow=c(1,1))
plot(x = resultados[,1], y = resultados[,2], type = "l", 
     xlab = "Número de árboles", ylab = "Area media bajo la curva ROC")

mejor = resultados[which(resultados[,2]==max(resultados[,2])),]

