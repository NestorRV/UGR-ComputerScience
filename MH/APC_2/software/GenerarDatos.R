# El siguiente paquete es necesario para la lectura de fichero ARFF
# si no está instalado y da error, descomentar la línea 5 y la última
# para desinstalar el paquete después de usarlo

#devtools::install_github("mlr-org/farff")
library(farff)
# Leo los datos
sonar = readARFF("./Data_Original/sonar.arff")
spambase = readARFF("./Data_Original/spambase-460.arff")
wdbc1 = readARFF("./Data_Original/wdbc.arff")
# Cambio el orden de la clase para ponerla en la ultima columna
wdbc = wdbc1[c(2:31, 1)]
# Funciones para cambiar el valor del campo clase por 1 o -1
f1 <- function(x) ifelse(x=="Rock", 1, -1)
f2 <- function(x) ifelse(x==1, 1, -1)
f3 <- function(x) ifelse(x=="B", 1, -1)
# Clases ya cambiadas
clase1 = mapply(f1, sonar[,length(sonar)])
clase2 = mapply(f2, spambase[,length(spambase)])
clase3 = mapply(f3, wdbc[,length(wdbc)])
# Borramos la ultima columna (la clase) de los datos leídos
sonar = sonar[,-length(sonar)]
spambase = spambase[,-length(spambase)]
wdbc = wdbc[,-length(wdbc)]
# Añadimos la clase a nuestros datos
sonar = cbind(sonar, clase1)
spambase = cbind(spambase, clase2)
wdbc = cbind(wdbc, clase3)
# Función que vamos a usar para normalizar
normalizar = function(x) {(x-min(x))/(max(x)-min(x))}
# Normalizamos todas las columnas menos la de la clase
aux = apply(sonar[1:60], 2, normalizar)
# apply devuelve una matriz así que la transformamos en un data.frame
aux = as.data.frame(aux)
# Le añadimos la clase
sonar = cbind(aux, sonar[,length(sonar)])
# Cambiamos el nombre de la columna clase (más que nada por estética)
colnames(sonar)[length(sonar)] = "Class"
# Repetimos el proceso para el segundo conjunto
aux = apply(spambase[1:57], 2, normalizar)
aux = as.data.frame(aux)
spambase = cbind(aux, spambase[,length(spambase)])
colnames(spambase)[length(spambase)] = "Class"
# Repetimos el proceso para el tercer conjunto
aux = apply(wdbc[1:30], 2, normalizar)
aux = as.data.frame(aux)
wdbc = cbind(aux, wdbc[,length(wdbc)])
colnames(wdbc)[length(wdbc)] = "Class"
# Limpiamos lo que ya no es necesario
rm(wdbc1); rm(aux); rm(clase1); rm(clase2); rm(clase3); rm(f1); rm(f2); rm(f3); rm(normalizar)

#############################################################################
#            Funciones auxiliares para el proceso de partición
#############################################################################

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


#############################################################################
#            Empezamos el proceso de partición de sonar
#############################################################################
clases_pos = which(sonar[,61] == 1)
clases_neg = which(sonar[,61] == -1)

set.seed(75573052)
#Barajamos los indices de los datos
pos = sample(clases_pos)
neg = sample(clases_neg)
#Particionamos los indices
particiones_pos = split(pos, cut(seq_along(pos), 5, labels = F))
particiones_neg = split(neg, cut(seq_along(neg), 5, labels = F))

#Debemos comprobar que sean todos del mismo tamaño, así que cogemos el mínimo
pos.size = min(unlist(lapply(particiones_pos, length)))
neg.size = min(unlist(lapply(particiones_neg, length)))

resultado = sobrantes(particiones_pos, pos.size)
particiones_pos = resultado[[1]]
pos.extras = as.vector(resultado[[2]])
resultado = sobrantes(particiones_neg, neg.size)
particiones_neg = resultado[[1]]
neg.extras = as.vector(resultado[[2]])
extras = c(pos.extras, neg.extras)

#Cogemos los datos de los indices según las particiones de los indices
sonar.pos <- lapply(particiones_pos, function(part) sonar[part,])
sonar.neg <- lapply(particiones_neg, function(part) sonar[part,])

#Generamos los cinco conjuntos
conjunto_1 = rbind(sonar.pos[[1]], sonar.neg[[1]])
conjunto_2 = rbind(sonar.pos[[2]], sonar.neg[[2]])
conjunto_3 = rbind(sonar.pos[[3]], sonar.neg[[3]])
conjunto_4 = rbind(sonar.pos[[4]], sonar.neg[[4]])
conjunto_5 = rbind(sonar.pos[[5]], sonar.neg[[5]])

#Añadimos lo que ha sobrado
l = list(conjunto_1, conjunto_2, conjunto_3, conjunto_4, conjunto_5)
for(i in 1:length(extras)){
  l[[i]] = rbind(l[[i]], sonar[extras[i],])
}

conjunto_1 = l[[1]]
conjunto_2 = l[[2]]
conjunto_3 = l[[3]]
conjunto_4 = l[[4]]
conjunto_5 = l[[5]]

#Repartimos los conjuntos y los guardamos en ficheros
sonar_test_1 = conjunto_1
sonar_train_1 = rbind(conjunto_2, conjunto_3, conjunto_4, conjunto_5)
sonar_test_2 = conjunto_2
sonar_train_2 = rbind(conjunto_1, conjunto_3, conjunto_4, conjunto_5)
sonar_test_3 = conjunto_3
sonar_train_3 = rbind(conjunto_1, conjunto_2, conjunto_4, conjunto_5)
sonar_test_4 = conjunto_4
sonar_train_4 = rbind(conjunto_1, conjunto_2, conjunto_3, conjunto_5)
sonar_test_5 = conjunto_5
sonar_train_5 = rbind(conjunto_1, conjunto_2, conjunto_3, conjunto_4)

#############################################################################
#            Empezamos el proceso de partición de spambase
#############################################################################
clases_pos = which(spambase[,58] == 1)
clases_neg = which(spambase[,58] == -1)

set.seed(75573052)
#Barajamos los indices de los datos
pos = sample(clases_pos)
neg = sample(clases_neg)
#Particionamos los indices
particiones_pos = split(pos, cut(seq_along(pos), 5, labels = F))
particiones_neg = split(neg, cut(seq_along(neg), 5, labels = F))
#Cogemos los datos de los indices según las particiones de los indices
spambase.pos <- lapply(particiones_pos, function(part) spambase[part,])
spambase.neg <- lapply(particiones_neg, function(part) spambase[part,])

#Debemos comprobar que sean todos del mismo tamaño, así que cogemos el mínimo
pos.size = min(unlist(lapply(particiones_pos, length)))
neg.size = min(unlist(lapply(particiones_neg, length)))

resultado = sobrantes(particiones_pos, pos.size)
particiones_pos = resultado[[1]]
pos.extras = as.vector(resultado[[2]])
resultado = sobrantes(particiones_neg, neg.size)
particiones_neg = resultado[[1]]
neg.extras = as.vector(resultado[[2]])
extras = c(pos.extras, neg.extras)

#Cogemos los datos de los indices según las particiones de los indices
spambase.pos <- lapply(particiones_pos, function(part) spambase[part,])
spambase.neg <- lapply(particiones_neg, function(part) spambase[part,])

#Generamos los cinco conjuntos
conjunto_1 = rbind(spambase.pos[[1]], spambase.neg[[1]])
conjunto_2 = rbind(spambase.pos[[2]], spambase.neg[[2]])
conjunto_3 = rbind(spambase.pos[[3]], spambase.neg[[3]])
conjunto_4 = rbind(spambase.pos[[4]], spambase.neg[[4]])
conjunto_5 = rbind(spambase.pos[[5]], spambase.neg[[5]])

#Añadimos lo que ha sobrado
l = list(conjunto_1, conjunto_2, conjunto_3, conjunto_4, conjunto_5)
for(i in 1:length(extras)){
  l[[i]] = rbind(l[[i]], spambase[extras[i],])
}

conjunto_1 = l[[1]]
conjunto_2 = l[[2]]
conjunto_3 = l[[3]]
conjunto_4 = l[[4]]
conjunto_5 = l[[5]]

#Repartimos los conjuntos y los guardamos en ficheros
spambase_test_1 = conjunto_1
spambase_train_1 = rbind(conjunto_2, conjunto_3, conjunto_4, conjunto_5)
spambase_test_2 = conjunto_2
spambase_train_2 = rbind(conjunto_1, conjunto_3, conjunto_4, conjunto_5)
spambase_test_3 = conjunto_3
spambase_train_3 = rbind(conjunto_1, conjunto_2, conjunto_4, conjunto_5)
spambase_test_4 = conjunto_4
spambase_train_4 = rbind(conjunto_1, conjunto_2, conjunto_3, conjunto_5)
spambase_test_5 = conjunto_5
spambase_train_5 = rbind(conjunto_1, conjunto_2, conjunto_3, conjunto_4)


#############################################################################
#            Empezamos el proceso de partición de wdbc
#############################################################################
clases_pos = which(wdbc[,31] == 1)
clases_neg = which(wdbc[,31] == -1)

set.seed(75573052)
#Barajamos los indices de los datos
pos = sample(clases_pos)
neg = sample(clases_neg)
#Particionamos los indices
particiones_pos = split(pos, cut(seq_along(pos), 5, labels = F))
particiones_neg = split(neg, cut(seq_along(neg), 5, labels = F))
#Cogemos los datos de los indices según las particiones de los indices
wdbc.pos <- lapply(particiones_pos, function(part) wdbc[part,])
wdbc.neg <- lapply(particiones_neg, function(part) wdbc[part,])

#Debemos comprobar que sean todos del mismo tamaño, así que cogemos el mínimo
pos.size = min(unlist(lapply(particiones_pos, length)))
neg.size = min(unlist(lapply(particiones_neg, length)))

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

conjunto_1 = l[[1]]
conjunto_2 = l[[2]]
conjunto_3 = l[[3]]
conjunto_4 = l[[4]]
conjunto_5 = l[[5]]

#Repartimos los conjuntos y los guardamos en ficheros
wdbc_test_1 = conjunto_1
wdbc_train_1 = rbind(conjunto_2, conjunto_3, conjunto_4, conjunto_5)
wdbc_test_2 = conjunto_2
wdbc_train_2 = rbind(conjunto_1, conjunto_3, conjunto_4, conjunto_5)
wdbc_test_3 = conjunto_3
wdbc_train_3 = rbind(conjunto_1, conjunto_2, conjunto_4, conjunto_5)
wdbc_test_4 = conjunto_4
wdbc_train_4 = rbind(conjunto_1, conjunto_2, conjunto_3, conjunto_5)
wdbc_test_5 = conjunto_5
wdbc_train_5 = rbind(conjunto_1, conjunto_2, conjunto_3, conjunto_4)


dir.create("./Data/csv", recursive = FALSE, mode = "0777")
#############################################################################
#            Empezamos el proceso de escritura en ficheros
#############################################################################
write.csv(sonar_test_1, file = "./Data/csv/sonar_test_1.csv", row.names = F)
write.csv(sonar_train_1, file = "./Data/csv/sonar_train_1.csv", row.names = F)
write.csv(sonar_test_2, file = "./Data/csv/sonar_test_2.csv", row.names = F)
write.csv(sonar_train_2, file = "./Data/csv/sonar_train_2.csv", row.names = F)
write.csv(sonar_test_3, file = "./Data/csv/sonar_test_3.csv", row.names = F)
write.csv(sonar_train_3, file = "./Data/csv/sonar_train_3.csv", row.names = F)
write.csv(sonar_test_4, file = "./Data/csv/sonar_test_4.csv", row.names = F)
write.csv(sonar_train_4, file = "./Data/csv/sonar_train_4.csv", row.names = F)
write.csv(sonar_test_5, file = "./Data/csv/sonar_test_5.csv", row.names = F)
write.csv(sonar_train_5, file = "./Data/csv/sonar_train_5.csv", row.names = F)

write.csv(spambase_test_1, file = "./Data/csv/spambase_test_1.csv", row.names = F)
write.csv(spambase_train_1, file = "./Data/csv/spambase_train_1.csv", row.names = F)
write.csv(spambase_test_2, file = "./Data/csv/spambase_test_2.csv", row.names = F)
write.csv(spambase_train_2, file = "./Data/csv/spambase_train_2.csv", row.names = F)
write.csv(spambase_test_3, file = "./Data/csv/spambase_test_3.csv", row.names = F)
write.csv(spambase_train_3, file = "./Data/csv/spambase_train_3.csv", row.names = F)
write.csv(spambase_test_4, file = "./Data/csv/spambase_test_4.csv", row.names = F)
write.csv(spambase_train_4, file = "./Data/csv/spambase_train_4.csv", row.names = F)
write.csv(spambase_test_5, file = "./Data/csv/spambase_test_5.csv", row.names = F)
write.csv(spambase_train_5, file = "./Data/csv/spambase_train_5.csv", row.names = F)

write.csv(wdbc_test_1, file = "./Data/csv/wdbc_test_1.csv", row.names = F)
write.csv(wdbc_train_1, file = "./Data/csv/wdbc_train_1.csv", row.names = F)
write.csv(wdbc_test_2, file = "./Data/csv/wdbc_test_2.csv", row.names = F)
write.csv(wdbc_train_2, file = "./Data/csv/wdbc_train_2.csv", row.names = F)
write.csv(wdbc_test_3, file = "./Data/csv/wdbc_test_3.csv", row.names = F)
write.csv(wdbc_train_3, file = "./Data/csv/wdbc_train_3.csv", row.names = F)
write.csv(wdbc_test_4, file = "./Data/csv/wdbc_test_4.csv", row.names = F)
write.csv(wdbc_train_4, file = "./Data/csv/wdbc_train_4.csv", row.names = F)
write.csv(wdbc_test_5, file = "./Data/csv/wdbc_test_5.csv", row.names = F)
write.csv(wdbc_train_5, file = "./Data/csv/wdbc_train_5.csv", row.names = F)
# remove.packages("farff")