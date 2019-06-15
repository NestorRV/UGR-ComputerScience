# El siguiente paquete es necesario para la lectura de fichero ARFF
# si no está instalado y da error, descomentar la línea 5 y la última
# para desinstalar el paquete después de usarlo

# devtools::install_github("mlr-org/farff")
library(farff)
# Leo los datos
sonar = readARFF("./Inputs/sonar.arff")
spambase = readARFF("./Inputs/spambase-460.arff")
wdbc1 = readARFF("./Inputs/wdbc.arff")
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

# Vamos a realizar las particiones de sonar
sonar_size = floor(0.5*nrow(sonar))
set.seed(75573052)
sonar_indices1 = sample(seq_len(nrow(sonar)), size = sonar_size)
sonar_train_1 = sonar[sonar_indices1,]
sonar_test_1 = sonar[-sonar_indices1,]

set.seed(55730527)
sonar_indices2 = sample(seq_len(nrow(sonar)), size = sonar_size)
sonar_train_2 = sonar[sonar_indices2,]
sonar_test_2 = sonar[-sonar_indices2,]

set.seed(57305275)
sonar_indices3 = sample(seq_len(nrow(sonar)), size = sonar_size)
sonar_train_3 = sonar[sonar_indices3,]
sonar_test_3 = sonar[-sonar_indices3,]

set.seed(73052755)
sonar_indices4 = sample(seq_len(nrow(sonar)), size = sonar_size)
sonar_train_4 = sonar[sonar_indices4,]
sonar_test_4 = sonar[-sonar_indices4,]

set.seed(30527557)
sonar_indices5 = sample(seq_len(nrow(sonar)), size = sonar_size)
sonar_train_5 = sonar[sonar_indices5,]
sonar_test_5 = sonar[-sonar_indices5,]

# Vamos a realizar las particiones de spambase
spambase_size = floor(0.5*nrow(spambase))
set.seed(75573052)
spambase_indices1 = sample(seq_len(nrow(spambase)), size = spambase_size)
spambase_train_1 = spambase[spambase_indices1,]
spambase_test_1 = spambase[-spambase_indices1,]

set.seed(55730527)
spambase_indices2 = sample(seq_len(nrow(spambase)), size = spambase_size)
spambase_train_2 = spambase[spambase_indices2,]
spambase_test_2 = spambase[-spambase_indices2,]

set.seed(57305275)
spambase_indices3 = sample(seq_len(nrow(spambase)), size = spambase_size)
spambase_train_3 = spambase[spambase_indices3,]
spambase_test_3 = spambase[-spambase_indices3,]

set.seed(73052755)
spambase_indices4 = sample(seq_len(nrow(spambase)), size = spambase_size)
spambase_train_4 = spambase[spambase_indices4,]
spambase_test_4 = spambase[-spambase_indices4,]

set.seed(30527557)
spambase_indices5 = sample(seq_len(nrow(spambase)), size = spambase_size)
spambase_train_5 = spambase[spambase_indices5,]
spambase_test_5 = spambase[-spambase_indices5,]

# Vamos a realizar las particiones de wdbc
wdbc_size = floor(0.5*nrow(wdbc))
set.seed(75573052)
wdbc_indices1 = sample(seq_len(nrow(wdbc)), size = wdbc_size)
wdbc_train_1 = wdbc[wdbc_indices1,]
wdbc_test_1 = wdbc[-wdbc_indices1,]

set.seed(55730527)
wdbc_indices2 = sample(seq_len(nrow(wdbc)), size = wdbc_size)
wdbc_train_2 = wdbc[wdbc_indices2,]
wdbc_test_2 = wdbc[-wdbc_indices2,]

set.seed(57305275)
wdbc_indices3 = sample(seq_len(nrow(wdbc)), size = wdbc_size)
wdbc_train_3 = wdbc[wdbc_indices3,]
wdbc_test_3 = wdbc[-wdbc_indices3,]

set.seed(73052755)
wdbc_indices4 = sample(seq_len(nrow(wdbc)), size = wdbc_size)
wdbc_train_4 = wdbc[wdbc_indices4,]
wdbc_test_4 = wdbc[-wdbc_indices4,]

set.seed(30527557)
wdbc_indices5 = sample(seq_len(nrow(wdbc)), size = wdbc_size)
wdbc_train_5 = wdbc[wdbc_indices5,]
wdbc_test_5 = wdbc[-wdbc_indices5,]

# Limpiamos lo que ya no es necesario
rm(sonar_indices1); rm(sonar_indices2); rm(sonar_indices3); rm(sonar_indices4); rm(sonar_indices5);
rm(spambase_indices1); rm(spambase_indices2); rm(spambase_indices3); rm(spambase_indices4); rm(spambase_indices5);
rm(wdbc_indices1); rm(wdbc_indices2); rm(wdbc_indices3); rm(wdbc_indices4); rm(wdbc_indices5);
rm(sonar_size); rm(spambase_size); rm(wdbc_size)


dir.create("./Data/csv", recursive = FALSE, mode = "0777")
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
