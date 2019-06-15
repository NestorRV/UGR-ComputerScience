; Plantilla para representar las licencias que va a conocer nuestro sistema experto
(deftemplate Licencia
    (multifield Nombre)
    (field Enlazar)
    (field Distribucion)
    (field Modificacion)
    (field Patentes)
    (field UsoPrivado)
    (field Sublicencia)
    (field Marca)
    (field GPL3)
)

; Plantilla para almacenar el texto que tiene un fichero
(deftemplate Fichero
    (field Nombre)
    (multifield Texto)
)

(deftemplate FicheroProcesado
    (field Nombre)
    (multifield Texto)
)

(deftemplate RespuestaDatos
    (field Identificador)
    (field DatoRecogido)
    (multifield Respuesta)
)

(deffacts Hechos
    ; Hecho para saber en que módulo estamos
    (Modulo 0)

    ; Guardamos las licencias
    (Licencia 
        (Nombre Apache)
        (Enlazar Permisivo)
        (Distribucion Permisivo)
        (Modificacion Permisivo)
        (Patentes Si)
        (UsoPrivado Si)
        (Sublicencia Permisivo)
        (Marca No)
        (GPL3 Si)
    )

    (Licencia 
        (Nombre BSD)
        (Enlazar Permisivo)
        (Distribucion Permisivo)
        (Modificacion Permisivo)
        (Patentes Manual)
        (UsoPrivado Si)
        (Sublicencia Permisivo)
        (Marca Manual)
        (GPL3 No)
    )

    (Licencia 
        (Nombre Creative Commons Zero)
        (Enlazar DominioPublico)
        (Distribucion DominioPublico)
        (Modificacion DominioPublico)
        (Patentes No)
        (UsoPrivado DominioPublico)
        (Sublicencia DominioPublico)
        (Marca No)
        (GPL3 Si)
    )

    (Licencia 
        (Nombre Eclipse)
        (Enlazar Limitado)
        (Distribucion Limitado)
        (Modificacion Limitado)
        (Patentes Si)
        (UsoPrivado Si)
        (Sublicencia Limitado)
        (Marca Manual)
        (GPL3 No)
    )

    (Licencia 
        (Nombre GNU-GPL)
        (Enlazar CompatibleConGPLv3)
        (Distribucion Copyleft)
        (Modificacion Copyleft)
        (Patentes Si)
        (UsoPrivado Si)
        (Sublicencia Copyleft)
        (Marca Si)
        (GPL3 Si)
    )

    (Licencia 
        (Nombre MIT-X11)
        (Enlazar Permisivo)
        (Distribucion Permisivo)
        (Modificacion Permisivo)
        (Patentes Manual)
        (UsoPrivado Si)
        (Sublicencia Permisivo)
        (Marca Manual)
        (GPL3 Si)
    )

    (Licencia 
        (Nombre Mozilla)
        (Enlazar Permisivo)
        (Distribucion Copyleft)
        (Modificacion Copyleft)
        (Patentes Si)
        (UsoPrivado Si)
        (Sublicencia Copyleft)
        (Marca No)
        (GPL3 Si)
    )

    ; Estos hechos es para convertir la respuesta del usuario desde teclado
    ; en el valor real de dicha respuesta. Se han generado a  traves de la 
    ; escala empleada en la rejilla de repertorio
    (CambiarEnlazar 1 Permisivo)
    (CambiarEnlazar 2 DominioPublico)
    (CambiarEnlazar 3 Limitado)
    (CambiarEnlazar 4 CompatibleConGPLv3)
    (CambiarDistribucion 1 Permisivo)
    (CambiarDistribucion 2 DominioPublico)
    (CambiarDistribucion 3 Limitado)
    (CambiarDistribucion 4 Copyleft)
    (CambiarModificacion 1 Permisivo)
    (CambiarModificacion 2 DominioPublico)
    (CambiarModificacion 3 Limitado)
    (CambiarModificacion 4 Copyleft)
    (CambiarPatentes 1 Si)
    (CambiarPatentes 2 Manual)
    (CambiarPatentes 3 No)
    (CambiarUsoPrivado 1 Si)
    (CambiarUsoPrivado 2 DominioPublico)
    (CambiarSublicencia 1 Permisivo)
    (CambiarSublicencia 2 DominioPublico)
    (CambiarSublicencia 3 Limitado)
    (CambiarSublicencia 4 Copyleft)
    (CambiarMarca 1 Si)
    (CambiarMarca 2 Manual)
    (CambiarMarca 3 No)
    (CambiarGPL3 1 Si)
    (CambiarGPL3 2 No)

    ; Estos hechos son para cambiar el indice de la licencia por su nombre
    (CambiarNombreLicencia 1 Apache)
    (CambiarNombreLicencia 2 BSD)
    (CambiarNombreLicencia 3 Creative Commons Zero)
    (CambiarNombreLicencia 4 Eclipse)
    (CambiarNombreLicencia 5 GNU-GPL)
    (CambiarNombreLicencia 6 MIT-X11)
    (CambiarNombreLicencia 7 Mozilla)

    (CambiarEnlazarModulo2 1 Permisivo)
    (CambiarEnlazarModulo2 3 DominioPublico)
    (CambiarEnlazarModulo2 5 Limitado)
    (CambiarEnlazarModulo2 7 CompatibleConGPLv3)
    (CambiarDistribucionModulo2 1 Permisivo)
    (CambiarDistribucionModulo2 3 DominioPublico)
    (CambiarDistribucionModulo2 5 Limitado)
    (CambiarDistribucionModulo2 7 Copyleft)
    (CambiarModificacionModulo2 1 Permisivo)
    (CambiarModificacionModulo2 3 DominioPublico)
    (CambiarModificacionModulo2 5 Limitado)
    (CambiarModificacionModulo2 7 Copyleft)
    (CambiarPatentesModulo2 1 Si)
    (CambiarPatentesModulo2 4 Manual)
    (CambiarPatentesModulo2 7 No)
    (CambiarUsoPrivadoModulo2 1 Si)
    (CambiarUsoPrivadoModulo2 7 DominioPublico)
    (CambiarSublicenciaModulo2 1 Permisivo)
    (CambiarSublicenciaModulo2 3 DominioPublico)
    (CambiarSublicenciaModulo2 5 Limitado)
    (CambiarSublicenciaModulo2 6 Copyleft)
    (CambiarMarcaModulo2 1 Si)
    (CambiarMarcaModulo2 4 Manual)
    (CambiarMarcaModulo2 7 No)
    (CambiarGPL3Modulo2 1 Si)
    (CambiarGPL3Modulo2 7 No)

    ; Modulo 3
    ; DatosEspecialmenteProtegidos
    (DEP Ideologia)
    (DEP AfiliacionSindical)
    (DEP Religion)
    (DEP Creencias)
    (DEP OrigenRacialEtnico)
    (DEP SaludVidaSexual)

    ; DatosCaracterIdentificativo
    (DCI DNI)
    (DCI Direccion)
    (DCI Imagen)
    (DCI Voz)
    (DCI NSeguridadSocial)
    (DCI Telefono)
    (DCI MarcasFisicas)
    (DCI NombreApellidos)
    (DCI FirmaHuella)
    (DCI FirmaElectronica)
    (DCI TarjetaSanitaria)

    ; DatosCaracteristicasPersonales
    (DCP DatosEstadoCivil)
    (DCP DatosFamilia)
    (DCP FechaNacimiento)
    (DCP LugarNacimiento)
    (DCP Edad)
    (DCP Sexo)
    (DCP Nacionalidad)
    (DCP LenguaMaterna)
    (DCP CaracteristicasFisicasAntropometricas)

    ; DatosCircunstanciasSociales
    (DCS CaracteristicasAlojamiento)
    (DCS Vivienda)
    (DCS SituacionFamiliar)
    (DCS Propiedades)
    (DCS Posesiones)
    (DCS AficionesEstilosVida)
    (DCS PertenenciaAlubesAsociaciones)
    (DCS Licencias)
    (DCS PermisosAutorizaciones)

    ; DatosAcademicosProfesionales
    (DAC Formacion)
    (DAC Titulaciones)
    (DAC HistorialEstudiante)
    (DAC ExperienciaProfesional)
    (DAC PertenenciaColegiosAsociacionesProfesionales)

    ; DetallesEmpleo
    (DE Profesion)
    (DE PuestosTrabajo)
    (DE DatosNoEconomicosNomina)
    (DE HistorialTrabajador)

    ; DatosInformacionComercial
    (DIC ActividadesNegocios)
    (DIC LicenciasComerciales)
    (DIC SubscripcionesPublicacionesMediosComunicacion)
    (DIC CreacionesArtisticas)
    (DIC Literarias)
    (DIC CientificasTecnicas)

    ; DatosEconomicosFinancierosSeguros
    (DEFS Ingresos)
    (DEFS Rentas)
    (DEFS Inversiones)
    (DEFS BienesPatrimoniales)
    (DEFS Creditos)
    (DEFS Prestamos)
    (DEFS Avales)
    (DEFS DatosBancarios)
    (DEFS PlanesPensiones)
    (DEFS Jubilacion)
    (DEFS DatosEconomicosNomina)
    (DEFS DatosDeduccionesImpositivasImpuestos)
    (DEFS Seguros)
    (DEFS Hipotecas)
    (DEFS Subsidios)
    (DEFS Beneficios)
    (DEFS HistorialCreditos)
    (DEFS TarjetasCredito)

    ; DatosTransaccionesBienesServicios
    (DTBS BienesServiciosSuministrados)
    (DTBS BienesServiciosRecibidos)
    (DTBS TransaccionesFinancieras)
    (DTBS CompensacionesIndemnizaciones)

    (Cambiar DEP 1 Ideologia)
    (Cambiar DEP 2 AfiliacionSindical)
    (Cambiar DEP 3 Religion)
    (Cambiar DEP 4 Creencias)
    (Cambiar DEP 5 OrigenRacialEtnico)
    (Cambiar DEP 6 SaludVidaSexual)

    (Cambiar DCI 1 DNI)
    (Cambiar DCI 2 Direccion)
    (Cambiar DCI 3 Imagen)
    (Cambiar DCI 4 Voz)
    (Cambiar DCI 5 NSeguridadSocial)
    (Cambiar DCI 6 Telefono)
    (Cambiar DCI 7 MarcasFisicas)
    (Cambiar DCI 8 NombreApellidos)
    (Cambiar DCI 9 FirmaHuella)
    (Cambiar DCI 10 FirmaElectronica)
    (Cambiar DCI 11 TarjetaSanitaria)

    (Cambiar DCP 1 DatosEstadoCivil)
    (Cambiar DCP 2 DatosFamilia)
    (Cambiar DCP 3 FechaNacimiento)
    (Cambiar DCP 4 LugarNacimiento)
    (Cambiar DCP 5 Edad)
    (Cambiar DCP 6 Sexo)
    (Cambiar DCP 7 Nacionalidad)
    (Cambiar DCP 8 LenguaMaterna)
    (Cambiar DCP 9 CaracteristicasFisicasAntropometricas)

    (Cambiar DCS 1 CaracteristicasAlojamiento)
    (Cambiar DCS 2 Vivienda)
    (Cambiar DCS 3 SituacionFamiliar)
    (Cambiar DCS 4 Propiedades)
    (Cambiar DCS 5 Posesiones)
    (Cambiar DCS 6 AficionesEstilosVida)
    (Cambiar DCS 7 PertenenciaAlubesAsociaciones)
    (Cambiar DCS 8 Licencias)
    (Cambiar DCS 9 PermisosAutorizaciones)

    (Cambiar DAC 1 Formacion)
    (Cambiar DAC 2 Titulaciones)
    (Cambiar DAC 3 HistorialEstudiante)
    (Cambiar DAC 4 ExperienciaProfesional)
    (Cambiar DAC 5 PertenenciaColegiosAsociacionesProfesionales)

    (Cambiar DE 1 Profesion)
    (Cambiar DE 2 PuestosTrabajo)
    (Cambiar DE 3 DatosNoEconomicosNomina)
    (Cambiar DE 4 HistorialTrabajador)

    (Cambiar DIC 1 ActividadesNegocios)
    (Cambiar DIC 2 LicenciasComerciales)
    (Cambiar DIC 3 SubscripcionesPublicacionesMediosComunicacion)
    (Cambiar DIC 4 CreacionesArtisticas)
    (Cambiar DIC 5 Literarias)
    (Cambiar DIC 6 CientificasTecnicas)

    (Cambiar DEFS 1 Ingresos)
    (Cambiar DEFS 2 Rentas)
    (Cambiar DEFS 3 Inversiones)
    (Cambiar DEFS 4 BienesPatrimoniales)
    (Cambiar DEFS 5 Creditos)
    (Cambiar DEFS 6 Prestamos)
    (Cambiar DEFS 7 Avales)
    (Cambiar DEFS 8 DatosBancarios)
    (Cambiar DEFS 9 PlanesPensiones)
    (Cambiar DEFS 10 Jubilacion)
    (Cambiar DEFS 11 DatosEconomicosNomina)
    (Cambiar DEFS 12 DatosDeduccionesImpositivasImpuestos)
    (Cambiar DEFS 13 Seguros)
    (Cambiar DEFS 14 Hipotecas)
    (Cambiar DEFS 15 Subsidios)
    (Cambiar DEFS 16 Beneficios)
    (Cambiar DEFS 17 HistorialCreditos)
    (Cambiar DEFS 18 TarjetasCredito)

    (Cambiar DTBS 1 BienesServiciosSuministrados)
    (Cambiar DTBS 2 BienesServiciosRecibidos)
    (Cambiar DTBS 3 TransaccionesFinancieras)
    (Cambiar DTBS 4 CompensacionesIndemnizaciones)

    (CambiarTipoOrganizacion 1 usuarioDomestico)
    (CambiarTipoOrganizacion 2 empresaPrivada)
    (CambiarTipoOrganizacion 3 organizacionesPublicas)

    (CambiarUsoDatos 1 UtilizacionGeneral)
    (CambiarUsoDatos 2 Investigacion)

    (Cambiar Siglas DEP DatosEspecialmenteProtegidos)
    (Cambiar Siglas DCI DatosCaracterIdentificativo)
    (Cambiar Siglas DCP DatosCaracteristicasPersonales)
    (Cambiar Siglas DCS DatosCircunstanciasSociales)
    (Cambiar Siglas DAC DatosAcademicosProfesionales)
    (Cambiar Siglas DE DetallesEmpleo)
    (Cambiar Siglas DIC DatosInformacionComercial)
    (Cambiar Siglas DEFS DatosEconomicosFinancierosSeguros)
    (Cambiar Siglas DTBS DatosTransaccionesBienesServicios)
)

(defrule Inicio
    ?f <- (Modulo 0)
    =>
    (printout t "Hola! Que deseas hacer? Pulsa 1 para elegir una licencia, pulsa 2 para comprobar la compatibilidad de una licencia, pulsa 3 para obtener informacion sobre la proteccion de datos o pulsa 4 para salir: ")
    (assert (Modulo (read)))
    (retract ?f)
)

(defrule Modulo1
    (Modulo 1)
    =>
    (printout t "Si va a modificar el codigo, como le interesa que sea la sublicencia de dicho codigo? Pulse 1 para Permisivo, pulse 2 para Dominio Publico, pulse 3 para Limitado o pulse 4 para Copyleft: ")
    (assert (Sublicencia (read)))
)

(defrule Modulo2
    (Modulo 2)
    =>
    (printout t "Vamos a comprobar la compatibilidad de dos licencias! Elige la licencia que quieres usar en tu codigo: " crlf "Pulsa: 1 para Apache, 2 para BSD, 3 para Creative Commons Zero, 4 para Eclipse, 5 para GNU-GPL, 6 para MIT-X11 y 7 para Mozilla: ")
    (assert (LicenciaMiCodigo (read)))
)

(defrule Modulo3
    (Modulo 3)
    =>
    (printout t "Vamos a ver que condiciones debes cumplir para no tener problemas con la ley de proteccion de datos! Ve pulsando el numero de los datos que quieres obtener informacion seguido de un enter y pulsa 0 para pasar al siguiente conjunto de datos!" crlf)
    ; Los hechos a continuación son para activar las reglas que piden los datos
    (assert (DEP *))
    (assert (Usuario DEP *))
    (assert (Usuario DCI *))
    (assert (Usuario DCP *))
    (assert (Usuario DCS *))
    (assert (Usuario DAC *))
    (assert (Usuario DE *))
    (assert (Usuario DIC *))
    (assert (Usuario DEFS *))
    (assert (Usuario DTBS *))
)

; ##############################################################
;                            Modulo 1
; ##############################################################
; En este modulo se permite al usuario elegir una licencia que se adecue a sus necesidades
; Las reglas a continuación implementan el árbol obtenido mediante la técnica de la rejilla
; de repertorio aplicada. En cada paso se justifica porque se ha tomado dicho paso.

; La idea de cada regla es saber en que parte del árbol está (mirando si el usuario ha introducido
; la informacion de los niveles superiores) y en función de eso realizar la pregunta correcta

(defrule LicenciaUno
    ?m <- (Modulo 1)
    (Sublicencia 2)
    (CambiarSublicencia 2 ?tipo)

    (Licencia (Nombre $?nombre) (Sublicencia ?tipo))
    =>
    (printout t "Como quieres que tu licencia tenga una sublicencia " ?tipo " tu licencia correcta seria " $?nombre crlf)
    (retract ?m)
)

(defrule LicenciaDos
    (Modulo 1)
    (Sublicencia ?sub)
    (test (neq ?sub 2))
    (CambiarSublicencia ?sub ?tipo)
    =>
    (printout t "Quieres que tu licencia tenga una sublicencia " ?tipo ". Si va a enlazar el codigo, como le interesa? Pulse 1 para Permisivo, pusle 2 para Dominio Publico pulse 3 para Limitado o pulse 4 para solo enlazarlo con GNU-CPL v3: ")
    (assert (Enlazar (read)))
)

(defrule EnlazarUno
    ?m <- (Modulo 1)
    (Sublicencia ?sub)
    (test (neq ?sub 2))
    (CambiarSublicencia ?sub ?sublicencia)
    (Enlazar 3)
    (CambiarEnlazar 3 ?enlazar)

    (Licencia (Nombre $?nombre) (Enlazar ?enlazar) (Sublicencia ?sublicencia))
    =>
    (printout t "Como quieres que tu licencia tenga una sublicencia " ?sublicencia " y un enlazado " ?enlazar " tu licencia correcta seria " $?nombre crlf)
    (retract ?m)
)

(defrule EnlazarDos
    (Modulo 1)
    (Sublicencia ?sub)
    (test (neq ?sub 2))
    (Enlazar ?enl)
    (test (neq ?enl 3))
    (CambiarSublicencia ?sub ?sublicencia)
    (CambiarEnlazar ?enl ?enlazar)
    =>
    (printout t "Quieres que tu licencia tenga una sublicencia " ?sublicencia " y un enlazado " ?enlazar ". Si va a distribuir el codigo, como le interesa? Pulse 1 para Permisivo o pulse 4 para Copyleft: ")
    (assert (Distribucion (read)))
)

(defrule DistribucionUno
    (Modulo 1)
    (Sublicencia ?sub)
    (test (neq ?sub 2))
    (Enlazar ?enl)
    (test (neq ?enl 3))
    (Distribucion 4)

    (CambiarSublicencia ?sub ?sublicencia)
    (CambiarEnlazar ?enl ?enlazar)
    (CambiarDistribucion 4 ?distribucion)
    =>
    (printout t "Quieres que tu licencia tenga una sublicencia " ?sublicencia ", un enlazado " ?enlazar " y una distribucion " ?distribucion ". Le interesa la concesion de marca para su codigo? Pulse 1 para Si o pulse 3 para No: ")
    (assert (Marca (read)))
)

(defrule DistribucionDos
    (Modulo 1)
    (Sublicencia ?sub)
    (test (neq ?sub 2))
    (Enlazar ?enl)
    (test (neq ?enl 3))
    (Distribucion ?dis)
    (test (neq ?dis 4))

    (CambiarSublicencia ?sub ?sublicencia)
    (CambiarEnlazar ?enl ?enlazar)
    (CambiarDistribucion ?dis ?distribucion)
    =>
    (printout t "Quieres que tu licencia tenga una sublicencia " ?sublicencia ", un enlazado " ?enlazar " y una distribucion " ?distribucion ". Le interesa la concesion de patentes para su codigo? Pulse 1 para Si o pulse 2 para Manual: ")
    (assert (Patentes (read)))
)

(defrule MarcaUno
    ?m <- (Modulo 1)
    (Sublicencia ?sub)
    (test (neq ?sub 2))
    (CambiarSublicencia ?sub ?sublicencia)
    (Enlazar ?enl)
    (test (neq ?enl 3))
    (CambiarEnlazar ?enl ?enlazar)
    (Distribucion 4)
    (CambiarDistribucion 4 ?distribucion)
    (Marca 1)
    (CambiarMarca 1 ?concesion)

    (Licencia (Nombre $?nombre) (Enlazar ?enlazar) (Distribucion ?distribucion) (Sublicencia ?sublicencia) (Marca ?concesion))
    =>
    (printout t "Como quieres que tu licencia tenga una sublicencia " ?sublicencia ", un enlazado " ?enlazar ", una distribucion " ?distribucion " y que la concesion de marca sea " ?concesion " tu licencia correcta seria " $?nombre crlf)
    (retract ?m)
)

(defrule MarcaDos
    ?m <- (Modulo 1)
    (Sublicencia ?sub)
    (test (neq ?sub 2))
    (CambiarSublicencia ?sub ?sublicencia)
    (Enlazar ?enl)
    (test (neq ?enl 3))
    (CambiarEnlazar ?enl ?enlazar)
    (Distribucion 4)
    (CambiarDistribucion 4 ?distribucion)
    (Marca 3)
    (CambiarMarca 3 ?concesion)

    (Licencia (Nombre $?nombre) (Enlazar ?enlazar) (Distribucion ?distribucion) (Sublicencia ?sublicencia) (Marca ?concesion))
    =>
    (printout t "Como quieres que tu licencia tenga una sublicencia " ?sublicencia ", un enlazado " ?enlazar ", una distribucion " ?distribucion " y que la concesion de marca sea " ?concesion " tu licencia correcta seria " $?nombre crlf)
    (retract ?m)
)

(defrule PatentesUno
    ?m <- (Modulo 1)
    (Sublicencia ?sub)
    (test (neq ?sub 2))
    (CambiarSublicencia ?sub ?sublicencia)
    (Enlazar ?enl)
    (test (neq ?enl 3))
    (CambiarEnlazar ?enl ?enlazar)
    (Distribucion ?dis)
    (test (neq ?dis 4))
    (CambiarDistribucion ?dis ?distribucion)
    (Patentes 1)
    (CambiarPatentes 1 ?patentes)

    (Licencia (Nombre $?nombre) (Enlazar ?enlazar) (Distribucion ?distribucion) (Patentes ?patentes) (Sublicencia ?sublicencia))
    =>
    (printout t "Como quieres que tu licencia tenga una sublicencia " ?sublicencia ", un enlazado " ?enlazar ", una distribucion " ?distribucion " y que la concesion de patentes sea " ?patentes " tu licencia correcta seria " $?nombre crlf)
    (retract ?m)
)

(defrule PatentesDos
    (Modulo 1)
    (Sublicencia ?sub)
    (test (neq ?sub 2))
    (Enlazar ?enl)
    (test (neq ?enl 3))
    (Distribucion ?dis)
    (test (neq ?dis 4))
    (Patentes 2)

    (CambiarSublicencia ?sub ?sublicencia)
    (CambiarEnlazar ?enl ?enlazar)
    (CambiarDistribucion ?dis ?distribucion)
    (CambiarPatentes 2 ?patentes)
    =>
    (printout t "Quieres que tu licencia tenga una sublicencia " ?sublicencia ", un enlazado " ?enlazar ", una distribucion " ?distribucion " y que la concesion de patentes sea " ?patentes ". Le interesa la compatibilidad con GNU-GPL (v3)? Pulse 1 para Si o pulse 2 para No: ")
    (assert (GPL3 (read)))
)

(defrule GPL3Uno
    ?m <- (Modulo 1)
    (Sublicencia ?sub)
    (test (neq ?sub 2))
    (CambiarSublicencia ?sub ?sublicencia)
    (Enlazar ?enl)
    (test (neq ?enl 3))
    (CambiarEnlazar ?enl ?enlazar)
    (Distribucion ?dis)
    (test (neq ?dis 4))
    (CambiarDistribucion ?dis ?distribucion)
    (Patentes 2)
    (CambiarPatentes 2 ?patentes)
    (GPL3 1)
    (CambiarGPL3 1 ?compatibilidad)


    (Licencia (Nombre $?nombre) (Enlazar ?enlazar) (Distribucion ?distribucion) (Patentes ?patentes) (Sublicencia ?sublicencia) (GPL3 ?compatibilidad))
    =>
    (printout t "Como quieres que tu licencia tenga una sublicencia " ?sublicencia ", un enlazado " ?enlazar ", una distribucion " ?distribucion ", que la concesion de patentes sea " ?patentes " y que " ?compatibilidad " tenga compatibilidad con GPL v3 tu licencia correcta seria " $?nombre crlf)
    (retract ?m)
)

(defrule GPL3Dos
    ?m <- (Modulo 1)
    (Sublicencia ?sub)
    (test (neq ?sub 2))
    (CambiarSublicencia ?sub ?sublicencia)
    (Enlazar ?enl)
    (test (neq ?enl 3))
    (CambiarEnlazar ?enl ?enlazar)
    (Distribucion ?dis)
    (test (neq ?dis 4))
    (CambiarDistribucion ?dis ?distribucion)
    (Patentes 2)
    (CambiarPatentes 2 ?patentes)
    (GPL3 2)
    (CambiarGPL3 2 ?compatibilidad)

    (Licencia (Nombre $?nombre) (Enlazar ?enlazar) (Distribucion ?distribucion) (Patentes ?patentes) (Sublicencia ?sublicencia) (GPL3 ?compatibilidad))
    =>
    (printout t "Como quieres que tu licencia tenga una sublicencia " ?sublicencia ", un enlazado " ?enlazar ", una distribucion " ?distribucion ", que la concesion de patentes sea " ?patentes " y que " ?compatibilidad " tenga compatibilidad con GPL v3 tu licencia correcta seria " $?nombre crlf)
    (retract ?m)
)

; ¿Que pasa si el usuario introduce las características de una licencia que no tenemos?
(defrule ErrorModulo1
    (declare (salience -20))
    ?m <- (Modulo 1)
    =>
    (printout t "Lo siento pero no conozco ninguna licencia que cumpla con tus requisitos..." crlf)
    (retract ?m)
)


; ##############################################################
;                            Modulo 2
; ##############################################################
; Al igual que sucedía en el modulo 1, sucede en el módulo 2. La idea es ir 
; bajando por el árbol de decisión que nos permite determinar si las dos licencias
; introducidas por el usuario son compatibles. Este árbol se ha aprendido con varios
; ejemplso de compatibilidades. 

(defrule LicenciaCodigoUsado
    (Modulo 2)
    (LicenciaMiCodigo ?l)
    =>
    (printout t "Elige la licencia tiene el codigo que usas en tu codigo: " crlf "Pulsa: 1 para Apache, 2 para BSD, 3 para Creative Commons Zero, 4 para Eclipse, 5 para GNU-GPL, 6 para MIT-X11 y 7 para Mozilla: ")
    (assert (LicenciaCodigoUsado (read)))
)

(defrule ComprobarDistribucionUno
    ?m <- (Modulo 2)
    (LicenciaMiCodigo ?lMia)
    (LicenciaCodigoUsado ?lUsado)
    (CambiarNombreLicencia ?lMia $?miLicencia)
    (CambiarNombreLicencia ?lUsado $?usoLicencia)

    (Licencia (Nombre $?usoLicencia) (Distribucion ?d))

    (CambiarDistribucionModulo2 ?numeroDistribucion ?d)

    (test (eq ?numeroDistribucion 1))
    =>
    (printout t "Las licencias son compatibles porque " ?usoLicencia " tiene una distribucion " ?d "." crlf)
    (retract ?m)
)

(defrule ComprobarDistribucionDos
    (Modulo 2)
    (LicenciaMiCodigo ?lMia)
    (LicenciaCodigoUsado ?lUsado)
    (CambiarNombreLicencia ?lMia $?miLicencia)
    (CambiarNombreLicencia ?lUsado $?usoLicencia)

    (Licencia (Nombre $?usoLicencia) (Distribucion ?d))

    (CambiarDistribucionModulo2 ?numeroDistribucion ?d)

    (test (neq ?numeroDistribucion 1))
    =>
    (assert (SegundoNivelModulo2))
)

(defrule ComprobarEnlazarUno
    ?m <- (Modulo 2)
    ?n <- (SegundoNivelModulo2)
    (LicenciaMiCodigo ?lMia)
    (LicenciaCodigoUsado ?lUsado)
    (CambiarNombreLicencia ?lMia $?miLicencia)
    (CambiarNombreLicencia ?lUsado $?usoLicencia)
    (Licencia (Nombre $?usoLicencia) (Distribucion ?d))
    (CambiarDistribucionModulo2 ?numeroDistribucion ?d)
    (test (eq ?numeroDistribucion 3))

    (Licencia (Nombre $?miLicencia) (Enlazar ?e))
    (CambiarEnlazarModulo2 ?numeroEnlazar ?e)
    (test (eq ?numeroEnlazar 1))
    =>
    (printout t "Las licencias no son compatibles porque " ?usoLicencia " tiene una distribucion " ?d " y " ?miLicencia " tiene un enlazado " ?e "." crlf)
    (retract ?m)
    (retract ?n)
)

(defrule ComprobarEnlazarDos
    ?m <- (Modulo 2)
    ?n <- (SegundoNivelModulo2)
    (LicenciaMiCodigo ?lMia)
    (LicenciaCodigoUsado ?lUsado)
    (CambiarNombreLicencia ?lMia $?miLicencia)
    (CambiarNombreLicencia ?lUsado $?usoLicencia)
    (Licencia (Nombre $?usoLicencia) (Distribucion ?d))
    (CambiarDistribucionModulo2 ?numeroDistribucion ?d)
    (test (eq ?numeroDistribucion 3))

    (Licencia (Nombre $?miLicencia) (Enlazar ?e))
    (CambiarEnlazarModulo2 ?numeroEnlazar ?e)
    (test (eq ?numeroEnlazar 7))
    =>
    (printout t "Las licencias son compatibles porque " ?usoLicencia " tiene una distribucion " ?d " y " ?miLicencia " tiene un enlazado " ?e "." crlf)
    (retract ?m)
    (retract ?n)
)

(defrule ComprobarMarcaUno
    ?m <- (Modulo 2)
    ?n <- (SegundoNivelModulo2)
    (LicenciaMiCodigo ?lMia)
    (LicenciaCodigoUsado ?lUsado)
    (CambiarNombreLicencia ?lMia $?miLicencia)
    (CambiarNombreLicencia ?lUsado $?usoLicencia)
    (Licencia (Nombre $?usoLicencia) (Distribucion ?d))
    (CambiarDistribucionModulo2 ?numeroDistribucion ?d)
    (test (eq ?numeroDistribucion 5))

    (Licencia (Nombre $?miLicencia) (Marca ?e))
    (CambiarMarcaModulo2 ?numeroMarca ?e)
    (test (eq ?numeroMarca 1))
    =>
    (printout t "Las licencias no son compatibles porque " ?usoLicencia " tiene una distribucion " ?d " y " ?miLicencia " tiene una concesion de marcas " ?e "." crlf)
    (retract ?m)
    (retract ?n)
)

(defrule ComprobarMarcaDos
    ?m <- (Modulo 2)
    ?n <- (SegundoNivelModulo2)
    (LicenciaMiCodigo ?lMia)
    (LicenciaCodigoUsado ?lUsado)
    (CambiarNombreLicencia ?lMia $?miLicencia)
    (CambiarNombreLicencia ?lUsado $?usoLicencia)
    (Licencia (Nombre $?usoLicencia) (Distribucion ?d))
    (CambiarDistribucionModulo2 ?numeroDistribucion ?d)
    (test (eq ?numeroDistribucion 5))

    (Licencia (Nombre $?miLicencia) (Marca ?e))
    (CambiarMarcaModulo2 ?numeroMarca ?e)
    (test (eq ?numeroMarca 4))
    =>
    (printout t "Las licencias no son compatibles porque " ?usoLicencia " tiene una distribucion " ?d " y " ?miLicencia " tiene una concesion de marcas " ?e "." crlf)
    (retract ?m)
    (retract ?n)
)

(defrule ComprobarMarcaTres
    ?m <- (Modulo 2)
    ?n <- (SegundoNivelModulo2)
    (LicenciaMiCodigo ?lMia)
    (LicenciaCodigoUsado ?lUsado)
    (CambiarNombreLicencia ?lMia $?miLicencia)
    (CambiarNombreLicencia ?lUsado $?usoLicencia)
    (Licencia (Nombre $?usoLicencia) (Distribucion ?d))
    (CambiarDistribucionModulo2 ?numeroDistribucion ?d)
    (test (eq ?numeroDistribucion 5))

    (Licencia (Nombre $?miLicencia) (Marca ?e))
    (CambiarMarcaModulo2 ?numeroMarca ?e)
    (test (eq ?numeroMarca 7))
    =>
    (printout t "Las licencias son compatibles porque " ?usoLicencia " tiene una distribucion " ?d " y " ?miLicencia " tiene una concesion de marcas " ?e "." crlf)
    (retract ?m)
    (retract ?n)
)

(defrule ComprobarMarcaCuatro
    ?m <- (Modulo 2)
    ?n <- (SegundoNivelModulo2)
    (LicenciaMiCodigo ?lMia)
    (LicenciaCodigoUsado ?lUsado)
    (CambiarNombreLicencia ?lMia $?miLicencia)
    (CambiarNombreLicencia ?lUsado $?usoLicencia)
    (Licencia (Nombre $?usoLicencia) (Distribucion ?d))
    (CambiarDistribucionModulo2 ?numeroDistribucion ?d)
    (test (eq ?numeroDistribucion 7))

    (Licencia (Nombre $?miLicencia) (Marca ?e))
    (CambiarMarcaModulo2 ?numeroMarca ?e)
    (test (eq ?numeroMarca 1))
    =>
    (printout t "Las licencias no son compatibles porque " ?usoLicencia " tiene una distribucion " ?d " y " ?miLicencia " tiene una concesion de marcas " ?e "." crlf)
    (retract ?m)
    (retract ?n)
)

(defrule ComprobarMarcaCinco
    (Modulo 2)
    (SegundoNivelModulo2)
    (LicenciaMiCodigo ?lMia)
    (LicenciaCodigoUsado ?lUsado)
    (CambiarNombreLicencia ?lMia $?miLicencia)
    (CambiarNombreLicencia ?lUsado $?usoLicencia)
    (Licencia (Nombre $?usoLicencia) (Distribucion ?d))
    (CambiarDistribucionModulo2 ?numeroDistribucion ?d)
    (test (eq ?numeroDistribucion 7))

    (Licencia (Nombre $?miLicencia) (Marca ?e))
    (CambiarMarcaModulo2 ?numeroMarca ?e)
    (test (eq ?numeroMarca 4))
    =>
    (assert (TercerNivelModulo2))
)

(defrule ComprobarMarcaSeis
    ?m <- (Modulo 2)
    ?n <- (SegundoNivelModulo2)
    (LicenciaMiCodigo ?lMia)
    (LicenciaCodigoUsado ?lUsado)
    (CambiarNombreLicencia ?lMia $?miLicencia)
    (CambiarNombreLicencia ?lUsado $?usoLicencia)
    (Licencia (Nombre $?usoLicencia) (Distribucion ?d))
    (CambiarDistribucionModulo2 ?numeroDistribucion ?d)
    (test (eq ?numeroDistribucion 7))

    (Licencia (Nombre $?miLicencia) (Marca ?e))
    (CambiarMarcaModulo2 ?numeroMarca ?e)
    (test (eq ?numeroMarca 7))
    =>
    (printout t "Las licencias son compatibles porque " ?usoLicencia " tiene una distribucion " ?d " y " ?miLicencia " tiene una concesion de marcas " ?e "." crlf)
    (retract ?m)
    (retract ?n)
)

(defrule ComprobarGPLUno
    (Modulo 2)
    (SegundoNivelModulo2)
    (TercerNivelModulo2)
    (LicenciaMiCodigo ?lMia)
    (LicenciaCodigoUsado ?lUsado)
    (CambiarNombreLicencia ?lMia $?miLicencia)
    (CambiarNombreLicencia ?lUsado $?usoLicencia)
    (Licencia (Nombre $?usoLicencia) (Distribucion ?d))
    (CambiarDistribucionModulo2 ?numeroDistribucion ?d)
    (test (eq ?numeroDistribucion 7))

    (Licencia (Nombre $?miLicencia) (Marca ?e) (GPL3 ?g))
    (CambiarMarcaModulo2 ?numeroMarca ?e)
    (CambiarGPL3Modulo2 ?numeroGPL ?g)
    (test (eq ?numeroMarca 4))
    (test (eq ?numeroGPL 1))
    =>
    (assert (CuartoNivelModulo2))
)

(defrule ComprobarGPLDos
    ?m <- (Modulo 2)
    ?n <- (SegundoNivelModulo2)
    ?o <- (TercerNivelModulo2)
    (LicenciaMiCodigo ?lMia)
    (LicenciaCodigoUsado ?lUsado)
    (CambiarNombreLicencia ?lMia $?miLicencia)
    (CambiarNombreLicencia ?lUsado $?usoLicencia)
    (Licencia (Nombre $?usoLicencia) (Distribucion ?d))
    (CambiarDistribucionModulo2 ?numeroDistribucion ?d)
    (test (eq ?numeroDistribucion 7))

    (Licencia (Nombre $?miLicencia) (Marca ?e) (GPL3 ?g))
    (CambiarMarcaModulo2 ?numeroMarca ?e)
    (CambiarGPL3Modulo2 ?numeroGPL ?g)
    (test (eq ?numeroMarca 4))
    (test (eq ?numeroGPL 7))
    =>
    (printout t "Las licencias son compatibles porque " ?usoLicencia " tiene una distribucion " ?d ", " ?miLicencia " tiene una concesion de marcas " ?e " y " ?g " es compatible con GPLv3." crlf)
    (retract ?m)
    (retract ?n)
    (retract ?o)
)

(defrule ComprobarEnlazarBisUno
    ?m <- (Modulo 2)
    ?n <- (SegundoNivelModulo2)
    ?o <- (TercerNivelModulo2)
    ?p <- (CuartoNivelModulo2)
    (LicenciaMiCodigo ?lMia)
    (LicenciaCodigoUsado ?lUsado)
    (CambiarNombreLicencia ?lMia $?miLicencia)
    (CambiarNombreLicencia ?lUsado $?usoLicencia)
    (Licencia (Nombre $?usoLicencia) (Distribucion ?d) (Enlazar ?enl))
    (CambiarDistribucionModulo2 ?numeroDistribucion ?d)
    (CambiarEnlazarModulo2 ?numeroEnlazar ?enl)
    (test (eq ?numeroDistribucion 7))
    (test (eq ?numeroEnlazar 1))

    (Licencia (Nombre $?miLicencia) (Marca ?e) (GPL3 ?g))
    (CambiarMarcaModulo2 ?numeroMarca ?e)
    (CambiarGPL3Modulo2 ?numeroGPL ?g)
    (test (eq ?numeroMarca 4))
    (test (eq ?numeroGPL 1))
    =>
    (printout t "Las licencias son compatibles porque " ?usoLicencia " tiene una distribucion " ?d ", " ?miLicencia " tiene una concesion de marcas " ?e ", " ?miLicencia " " ?g " es compatible con GPLv3 y " ?usoLicencia " tiene un enlazado " ?enl crlf)
    (retract ?m)
    (retract ?n)
    (retract ?o)
    (retract ?p)
)

(defrule ComprobarEnlazarBisDos
    ?m <- (Modulo 2)
    ?n <- (SegundoNivelModulo2)
    ?o <- (TercerNivelModulo2)
    ?p <- (CuartoNivelModulo2)
    (LicenciaMiCodigo ?lMia)
    (LicenciaCodigoUsado ?lUsado)
    (CambiarNombreLicencia ?lMia $?miLicencia)
    (CambiarNombreLicencia ?lUsado $?usoLicencia)
    (Licencia (Nombre $?usoLicencia) (Distribucion ?d) (Enlazar ?enl))
    (CambiarDistribucionModulo2 ?numeroDistribucion ?d)
    (CambiarEnlazarModulo2 ?numeroEnlazar ?enl)
    (test (eq ?numeroDistribucion 7))
    (test (neq ?numeroEnlazar 1))

    (Licencia (Nombre $?miLicencia) (Marca ?e) (GPL3 ?g))
    (CambiarMarcaModulo2 ?numeroMarca ?e)
    (CambiarGPL3Modulo2 ?numeroGPL ?g)
    (test (eq ?numeroMarca 4))
    (test (eq ?numeroGPL 1))
    =>
    (printout t "Las licencias no son compatibles porque " ?usoLicencia " tiene una distribucion " ?d ", " ?miLicencia " tiene una concesion de marcas " ?e ", " ?miLicencia " " ?g " es compatible con GPLv3 y " ?usoLicencia " tiene un enlazado " ?enl crlf)
    (retract ?m)
    (retract ?n)
    (retract ?o)
    (retract ?p)
)

; Debemos tener cuidado por si el usuario se equivoca al pulsar las teclas de las licencias
; y por lo tanto no podríamos comprobar si las licencias son compatibles o no.
(defrule ErrorModulo2
    (declare (salience -20))
    ?m <- (Modulo 2)
    =>
    (printout t "Lo siento pero ha introducido mal las licencias asi que no puedo comprobar si son compatibles o no..." crlf)
    (retract ?m)
)

; ##############################################################
;                            Modulo 3
; ##############################################################
; Este módulo tiene varios pasos. El primero de ellos es permitir al usuario que introduzca 
; los datos que va a usar en sus sitema. Para ello tenemos una regla para cada tipo de dato
; a usar y que es llamada hasta que el usuario pulse un 0 para ese tipo de datos (el cero 
; representa que el usuario no quiere introducir más datos de ese tipo)

(defrule LeerDEP
    (declare (salience -1))
    (Modulo 3)
    (Usuario DEP ?elemento)
    (test (neq ?elemento 0))
    =>
    (printout t "DatosEspecialmenteProtegidos: 1 para ideologia, 2 para afiliacion sindical, 3 para religion, 4 para creencias, 5 para origen racial o etnico, 6 para salud y vida sexual: ")
    (assert (Usuario DEP (read)))
)

(defrule LeerDCI
    (declare (salience -2))
    (Modulo 3)
    (Usuario DCI ?elemento)
    (test (neq ?elemento 0))
    =>
    (printout t "DatosCaracterIdentificativo: 1 para DNI, 2 para direccion, 3 para imagen, 4 para voz, 5 para Nº Seguridad Social/mutualidad, 6 para telefono, 7 para marcas fisicas, 8 para nombre y apellidos, 9 para firma/huella, 10 para firma electronica, 11 para tarjeta sanitaria: ")
    (assert (Usuario DCI (read)))
)

(defrule LeerDCP
    (declare (salience -3))
    (Modulo 3)
    (Usuario DCP ?elemento)
    (test (neq ?elemento 0))
    =>
    (printout t "DatosCaracteristicasPersonales: 1 para datos de estado civil, 2 para datos de familia, 3 para fecha de nacimiento, 4 para lugar de nacimiento, 5 para edad, 6 para sexo, 7 para nacionalidad, 8 para lengua materna, 9 para caracteristicas fisicas o antropometricas: ")
    (assert (Usuario DCP (read)))
)

(defrule LeerDCS
    (declare (salience -4))
    (Modulo 3)
    (Usuario DCS ?elemento)
    (test (neq ?elemento 0))
    =>
    (printout t "DatosCircunstanciasSociales: 1 para caracteristicas de alojamiento, 2 para vivienda, 3 para situacion familiar, 4 para propiedades, 5 para posesiones, 6 para aficiones y estilos de vida, 7 para pertenencia a clubes y asociaciones, 8 para licencias, 9 para permisos y autorizaciones: ")
    (assert (Usuario DCS (read)))
)

(defrule LeerDAC
    (declare (salience -5))
    (Modulo 3)
    (Usuario DAC ?elemento)
    (test (neq ?elemento 0))
    =>
    (printout t "DatosAcademicosProfesionales: 1 para formacion, 2 para titulaciones, 3 para historial del estudiante, 4 para experiencia profesional, 5 para pertenencia a colegios o asociaciones profesionales: ")
    (assert (Usuario DAC (read)))
)

(defrule LeerDE
    (declare (salience -6))
    (Modulo 3)
    (Usuario DE ?elemento)
    (test (neq ?elemento 0))
    =>
    (printout t "DetallesEmpleo: 1 para profesion, 2 para puestos de trabajo, 3 para datos no economicos de nomina, 4 para historial del trabajador: ")
    (assert (Usuario DE (read)))
)

(defrule LeerDIC
    (declare (salience -7))
    (Modulo 3)
    (Usuario DIC ?elemento)
    (test (neq ?elemento 0))
    =>
    (printout t "DatosInformacionComercial: 1 para actividades y negocios, 2 para licencias comerciales, 3 para subscripciones a publicaciones o medios de comunicacion, 4 para creaciones artisticas, 5 para literarias, 6 para cientificas o tecnicas: ")
    (assert (Usuario DIC (read)))
)

(defrule LeerDEFS
    (declare (salience -8))
    (Modulo 3)
    (Usuario DEFS ?elemento)
    (test (neq ?elemento 0))
    =>
    (printout t "DatosEconomicosFinancierosSeguros: 1 para ingresos, 2 para rentas, 3 para inversiones, 4 para bienes patrimoniales, 5 para creditos, 6 para prestamos, 7 para avales, 8 para datos bancarios, 9 para planes de pensiones, 10 para jubilacion, 11 para datos economicos de nomina, 12 para datos deducciones impositivas/impuestos, 13 para seguros, 14 para hipotecas, 15 para subsidios, 16 para beneficios, 17 para historial de creditos, 18 para tarjetas de credito: ")
    (assert (Usuario DEFS (read)))
)

(defrule LeerDTBS
    (declare (salience -9))
    (Modulo 3)
    (Usuario DTBS ?elemento)
    (test (neq ?elemento 0))
    =>
    (printout t "DatosTransaccionesBienesServicios: 1 para bienes y servicios suministrados por el afectado, 2 para bienes y servicios recibidos por el afectado, 3 para transacciones financieras, 4 para compensaciones/indemnizaciones: ")
    (assert (Usuario DTBS (read)))
)

; Una vez tenemos los datos recogidos, se los mostramos al usuario. Sabremos que el usuario ha 
; terminado de introducir los datos porqué habra un hecho con el último tipo de datos preguntado 
; (DTBD en nuestro caso) y con un cero
(defrule ImprimirDatos
    (Modulo 3)
    (Usuario DTBS 0)
    =>
    (printout t "Los datos que vas a usar son los siguientes: " crlf)
)

(defrule ImprimirDatos2
    (declare (salience -1))
    (Modulo 3)
    (Usuario DTBS 0)
    (Usuario ?tipo ?dato)
    (Cambiar ?tipo ?dato ?datoCambiado)
    (Cambiar Siglas ?tipo ?tipoTexto)
    =>
    (printout t ?tipoTexto " " ?datoCambiado crlf)
)

; Una vez tenemos los datos, le preguntamos por el resto de informacion que necesitamos
(defrule TipoOrganizacion
    (declare (salience -2))
    (Modulo 3)
    (Usuario DTBS 0)
    =>
    (printout t "Que tipo de organizacion va a usar los datos? Pulsa 1 para usuario domestico, 2 para empresa privada o pulsa 3 para organizaciones dependientes de las administraciones publicas: ")
    (assert (TipoOrganizacion (read)))
)

(defrule UsoDatos
    (declare (salience -3))
    (Modulo 3)
    (Usuario DTBS 0)
    =>
    (printout t "Que tipo de uso se le van a dar a los datos? Pulsa 1 para una utilizacion general de bases de datos (que incluye sector privado y publico) o pulsa 2 para bases de datos para investigacion judicial y policial: ")
    (assert (UsoDatos (read)))
)

(defrule UbicacionDatos
    (declare (salience -4))
    (Modulo 3)
    (Usuario DTBS 0)
    =>
    (printout t "Donde van a estar almacenados los datos? Pulsa 1 para España, pulsa 2 para Europa y pulsa 3 para fuera de Europa: ")
    (assert (UbicacionDatos (read)))
)

; Pasamos a detectar los datos que identifican a una persona
(defrule IdentificacionSegura
    (Modulo 3)
    (UsoDatos ?n)
    (UbicacionDatos ?u)

    (Usuario ?tipoDato ?introducido)
    (test (neq ?introducido 0))
    (test (neq ?introducido *))
    (Cambiar ?tipoDato ?introducido ?datoCambiado)

    (test (or (eq ?datoCambiado DNI) (eq ?datoCambiado Direccion) (eq ?datoCambiado Imagen) (eq ?datoCambiado Voz) 
              (eq ?datoCambiado NSeguridadSocial) (eq ?datoCambiado Telefono) (eq ?datoCambiado NombreApellidos) 
              (eq ?datoCambiado FirmaHuella) (eq ?datoCambiado FirmaElectronica) (eq ?datoCambiado TarjetaSanitaria)

              (eq ?datoCambiado CreacionesArtisticas) (eq ?datoCambiado Literarias) (eq ?datoCambiado CientificasTecnicas)

              (eq ?datoCambiado DatosBancarios) (eq ?datoCambiado DatosEconomicosNomina) (eq ?datoCambiado TarjetasCredito)
          )
    )
    =>
    (printout t "El usuario puede ser identificado por usar el dato: " ?datoCambiado crlf)
    (assert (IdentificablePor ?tipoDato ?datoCambiado))
)

; Y con los datos que podrían identificar a una persona necesitamos que el usuario
; nos de un poco más de informacion
(defrule PosibleIdentificacion
    (declare (salience -1))
    (Modulo 3)
    (UsoDatos ?n)
    (UbicacionDatos ?u)

    (Usuario ?tipoDato ?introducido)
    (test (neq ?introducido 0))
    (test (neq ?introducido *))
    (Cambiar ?tipoDato ?introducido ?datoCambiado)

    (test (and (neq ?datoCambiado DNI) (neq ?datoCambiado Direccion) (neq ?datoCambiado Imagen) (neq ?datoCambiado Voz) 
               (neq ?datoCambiado NSeguridadSocial) (neq ?datoCambiado Telefono) (neq ?datoCambiado NombreApellidos) 
               (neq ?datoCambiado FirmaHuella) (neq ?datoCambiado FirmaElectronica) (neq ?datoCambiado TarjetaSanitaria)

               (neq ?datoCambiado CreacionesArtisticas) (neq ?datoCambiado Literarias) (neq ?datoCambiado CientificasTecnicas)

               (neq ?datoCambiado DatosBancarios) (neq ?datoCambiado DatosEconomicosNomina) (neq ?datoCambiado TarjetasCredito)
          )
    )
    =>
    (printout t "En la circunstancia en la que vas a usar los datos puede darse el caso de que una persona pueda ser identificada por " ?datoCambiado "? Pulsa 1 para si y 2 para no: ")
    (assert (PuedeSerIdentificablePor ?tipoDato ?datoCambiado (read)))
)

; Si hay datos que el usuario nos ha dicho que pueden identificar a una persona
; en la situación en la que se van a usar los datos, debemos marcar dichos datos
; como datos que permiten identificar a una persona
(defrule ProcesarPosiblesIdentificaciones
    (Modulo 3)
    (PuedeSerIdentificablePor ?tipoDato ?datoCambiado 1)
    =>
    (assert (IdentificablePor ?tipoDato ?datoCambiado))
)

; Si el usuario utiliza algun dato de caracter personal, debemos indicarle que debe hacer para no tener problemas
(defrule ResumenMedidas
    (declare (salience -10))
    (Modulo 3)
    (Usuario ?a ?b)
    =>
    (printout t "Para cumplir con el articulo 4 de la LOPD, el empresario debe recoger los datos usando medios que no sean fraudulentos, solo puede recoger unicamente aquellos datos personales que sean adecuados, solo utilizara los datos para finalidades compatibles con la finalidad que origino su recogida, debera mantener los datos exactos y actualizados, debera cancelar los datos cuando hayan dejado de ser necesarios y el empresario debe almacenar los datos personales de manera que el titular de los datos pueda ejercer su derecho de acceso cuando lo considere oportuno." crlf)
    (printout t "Para cumplir con el articulo 5 de la LOPD, el empresario tiene el deber de informar al titular de los datos correctamente del uso que se le va a dar a los datos. El empresario debe elaborar las clausulas informativas y diseñar los procedimientos que sean necesarios para informar debidamente al ciudadano y demostrar posteriormente que ha cumplido con su obligacion." crlf)
    (printout t "Para cumplir con el articulo 6 de la LOPD, el empresario solo podra tratar los datos de caracter personal si dispone del consentimiento del titular de los datos salvo que el tratamiento este fundamentado en una de las excepciones legalmente previstas. El empresario debe tener muy claro cuando necesita el consentimiento del afectado y cuando no lo necesita, y, en caso de necesitarlo debera obtenerlo legalmente teniendo en cuenta que, para que sea valido el consentimiento, debe tratarse de una manifestacion de voluntad libre, inequivoca, especifica e informada." crlf)
    (printout t "Para cumplir con el articulo 7 de la LOPD, el empresario no puede obligar al ciudadano a declarar sobre su ideologia, religion o creencias y en caso de pedirle el consentimiento para tratar este tipo de datos debe advertirle acerca de su derecho a no prestarlo. El empresario solo podra utilizar datos de caracter personal que revelen la ideologia, afiliacion sindical, religion y creencias si dispone del consentimiento expreso y por escrito del interesado. El empresario solo podra utilizar datos de caracter personal que hagan referencia al origen racial, a la salud y a la vida sexual si dispone del consentimiento expreso. Los ficheros en los que se encuentren almacenados los datos de caracter personal deben estar protegidos con las medidas de seguridad correspondientes al nivel alto." crlf)
    (printout t "Para cumplir con el articulo 9 de la LOPD, el empresario debe adoptar en su organizacion las medidas de indole tecnica y organizativas necesarias que garanticen la seguridad de los datos de caracter personal y eviten su alteracion, perdida, tratamiento o acceso no autorizado, habida cuenta del estado de la tecnologia, la naturaleza de los datos almacenados y los riesgos a que esten expuestos, ya provengan de la accion humana o del medio fisico o natural." crlf)
    (printout t "Para cumplir con el articulo 10 de la LOPD, el empresario esta obligado a guardar secreto profesional sobre los datos tratados y a mantener la confidencialidad de los mismos dentro de su organizacion, debiendo tener en cuenta que la ley extiende el deber de secreto a cualquier persona o entidad que intervenga en cualquiera de las fases del tratamiento aun despues de finalizar sus relaciones con el titular del fichero o, en su caso, con el responsable del mismo." crlf)
    (printout t "Para cumplir con el articulo 11 de la LOPD, el empresario solo cedera los datos para el cumplimiento de fines directamente relacionados con las funciones legitimas del cedente y del cesionario. Tambien debera informar al titular de los datos de una manera expresa, precisa e inequivoca de la identidad y el tipo de actividad que desarrolla el destinatario de los datos asi como de la finalidad a que destinaran los datos." crlf)
    (printout t "Para cumplir con el articulo 12 de la LOPD, cuando el empresario contrate a otra persona, empresa o entidad para que le preste algun tipo de servicio utilizando los datos de caracter personal almacenados en sus ficheros debe formalizar la prestacion del servicio en un contrato que debera constar por escrito. El encargado del tratamiento unicamente tratara los datos conforme a las instrucciones del responsable del tratamiento. En el contrato quedara reflejada la finalidad con la que se deben tratar los datos. El encargado del tratamiento no comunicara los datos, ni siquiera para su conservacion, a otras personas. En el contrato se estipularan, las medidas de seguridad que el encargado del tratamiento esta obligado a implementar. Una vez cumplida la prestacion contractual, los datos de caracter personal deberan ser destruidos" crlf)
    (printout t "El empresario debe facilitar a los ciudadanos el ejercicio de los denominados derechos Arco (acceso, rectificacion, cancelacion y oposicion). " crlf)
    (printout t "Si los datos van a salir fuera del Espacio Economico Europeo se debera notificar las transferencias a la Agencia Española de Proteccion de Datos para su inscripcion en el Registro General de Proteccion de Datos. Previamente, el Director de la Agencia Española de Proteccion de Datos debera haber aprobado la transmision de datos fuera del Espacio Economico Europeo. Cuando la transferencia internacional de datos se realice con el objeto de entregar los datos a un tercero para que este los trate por su cuenta sera necesario aplicar las garantias previstas legalmente para la “cesion o comunicacion de datos”. Cuando la transferencia internacional de datos se realice para que un tercero preste un servicio al responsable del fichero sera necesario aplicar lo legalmente previsto para el “acceso a los datos por cuenta de terceros”." crlf)
)

; Finalmente, leemos los documentos ARCO para poder rellenarlos
(defrule AbrirAcceso
    (Modulo 3)
    =>
    (open "Acceso" mi_fichero)
    (assert (SeguirLeyendoAcceso))
    (assert (Fichero (Nombre Acceso) (Texto *)))
)

(defrule LeerAcceso
    (Modulo 3)
    ?f <- (SeguirLeyendoAcceso)
    ?d <- (Fichero (Nombre Acceso) (Texto $?texto))
    =>
    (bind ?leido (readline mi_fichero))
    (retract ?f)
    (retract ?d)

    (if (neq ?leido EOF) then
        (assert (Fichero (Nombre Acceso) (Texto $?texto ?leido)))
        (assert (SeguirLeyendoAcceso))
    )

    (if (eq ?leido EOF) then
        (close mi_fichero)
        (assert (Fichero (Nombre Acceso) (Texto $?texto)))
        (assert (FicheroAcceso Listo))
    )
)

(defrule AbrirCancelacion
    (Modulo 3)
    =>
    (open "Cancelacion" mi_fichero)
    (assert (SeguirLeyendoCancelacion))
    (assert (Fichero (Nombre Cancelacion) (Texto *)))
)

(defrule LeerCancelacion
    (Modulo 3)
    ?f <- (SeguirLeyendoCancelacion)
    ?d <- (Fichero (Nombre Cancelacion) (Texto $?texto))
    =>
    (bind ?leido (readline mi_fichero))
    (retract ?f)
    (retract ?d)

    (if (neq ?leido EOF) then
        (assert (Fichero (Nombre Cancelacion) (Texto $?texto ?leido)))
        (assert (SeguirLeyendoCancelacion))
    )

    (if (eq ?leido EOF) then
        (close mi_fichero)
        (assert (Fichero (Nombre Cancelacion) (Texto $?texto)))
        (assert (FicheroCancelacion Listo))
    )
)

(defrule AbrirOposicion
    (Modulo 3)
    =>
    (open "Oposicion" mi_fichero)
    (assert (SeguirLeyendoOposicion))
    (assert (Fichero (Nombre Oposicion) (Texto *)))
)

(defrule LeerOposicion
    (Modulo 3)
    ?f <- (SeguirLeyendoOposicion)
    ?d <- (Fichero (Nombre Oposicion) (Texto $?texto))
    =>
    (bind ?leido (readline mi_fichero))
    (retract ?f)
    (retract ?d)

    (if (neq ?leido EOF) then
        (assert (Fichero (Nombre Oposicion) (Texto $?texto ?leido)))
        (assert (SeguirLeyendoOposicion))
    )

    (if (eq ?leido EOF) then
        (close mi_fichero)
        (assert (Fichero (Nombre Oposicion) (Texto $?texto)))
        (assert (FicheroOposicion Listo))
    )
)

(defrule AbrirRectificacion
    (Modulo 3)
    =>
    (open "Rectificacion" mi_fichero)
    (assert (SeguirLeyendoRectificacion))
    (assert (Fichero (Nombre Rectificacion) (Texto *)))
)

(defrule LeerRectificacion
    (Modulo 3)
    ?f <- (SeguirLeyendoRectificacion)
    ?d <- (Fichero (Nombre Rectificacion) (Texto $?texto))
    =>
    (bind ?leido (readline mi_fichero))
    (retract ?f)
    (retract ?d)

    (if (neq ?leido EOF) then
        (assert (Fichero (Nombre Rectificacion) (Texto $?texto ?leido)))
        (assert (SeguirLeyendoRectificacion))
    )

    (if (eq ?leido EOF) then
        (close mi_fichero)
        (assert (Fichero (Nombre Rectificacion) (Texto $?texto)))
        (assert (FicheroRectificacion Listo))
    )
)

; Debemos perdirle al usuario los datos con los que desea rellenar los documentos ARCO
(defrule PedirDatos
    (declare (salience -20))
    (Modulo 3)
    (UsoDatos ?n)
    (UbicacionDatos ?u)

    (FicheroAcceso Listo)
    (FicheroCancelacion Listo)
    (FicheroOposicion Listo)
    (FicheroRectificacion Listo)
    =>
    (printout t "Voy a preguntarte por algunos datos que necesito para rellenar los fomularios ARCO. Primero sobre el responsable del fichero. Cual es su nombre? ")
    (assert (RespuestaDatos (Identificador Responsable) (DatoRecogido Nombre) (Respuesta (readline))))
    (printout t "En que calle vive? ")
    (assert (RespuestaDatos (Identificador Responsable) (DatoRecogido Direccion) (Respuesta (readline))))
    (printout t "En que numero vive? ")
    (assert (RespuestaDatos (Identificador Responsable) (DatoRecogido Numero) (Respuesta (readline))))
    (printout t "Cual es su codigo postal? ")
    (assert (RespuestaDatos (Identificador Responsable) (DatoRecogido CP) (Respuesta (readline))))
    (printout t "En que localidad vive? ")
    (assert (RespuestaDatos (Identificador Responsable) (DatoRecogido Localidad) (Respuesta (readline))))
    (printout t "En que provincia vive? ")
    (assert (RespuestaDatos (Identificador Responsable) (DatoRecogido Provincia) (Respuesta (readline))))
    (printout t "En que comunidad autonoma vive? ")
    (assert (RespuestaDatos (Identificador Responsable) (DatoRecogido CAutonoma) (Respuesta (readline))))
    (printout t "Cual es su DNI? ")
    (assert (RespuestaDatos (Identificador Responsable) (DatoRecogido DNI) (Respuesta (readline))))

    (printout t "Ahora sobre el interesado o el representante legal. Cual es su nombre? ")
    (assert (RespuestaDatos (Identificador Interesado) (DatoRecogido Nombre) (Respuesta (readline))))
    (printout t "En que calle vive? ")
    (assert (RespuestaDatos (Identificador Interesado) (DatoRecogido Direccion) (Respuesta (readline))))
    (printout t "En que numero vive? ")
    (assert (RespuestaDatos (Identificador Interesado) (DatoRecogido Numero) (Respuesta (readline))))
    (printout t "En que localidad vive? ")
    (assert (RespuestaDatos (Identificador Interesado) (DatoRecogido Localidad) (Respuesta (readline))))
    (printout t "En que provincia vive? ")
    (assert (RespuestaDatos (Identificador Interesado) (DatoRecogido Provincia) (Respuesta (readline))))
    (printout t "En que comunidad autonoma vive? ")
    (assert (RespuestaDatos (Identificador Interesado) (DatoRecogido CAutonoma) (Respuesta (readline))))
    (printout t "Cual es su codigo postal? ")
    (assert (RespuestaDatos (Identificador Interesado) (DatoRecogido CP) (Respuesta (readline))))
    (printout t "Cual es su DNI? ")
    (assert (RespuestaDatos (Identificador Interesado) (DatoRecogido DNI) (Respuesta (readline))))

    (printout t "En que ciudad se va a firmar el presente documento? ")
    (assert (RespuestaDatos (Identificador General) (DatoRecogido Ciudad) (Respuesta (readline))))
    (printout t "Que dia (numero) se va a firmar el presente documento? ")
    (assert (RespuestaDatos (Identificador General) (DatoRecogido Dia) (Respuesta (readline))))
    (printout t "Que mes se va a firmar el presente documento? ")
    (assert (RespuestaDatos (Identificador General) (DatoRecogido Mes) (Respuesta (readline))))
    (printout t "Que año (solo las dos ultimas cifras) se va a firmar el presente documento? ")
    (assert (RespuestaDatos (Identificador General) (DatoRecogido Anio) (Respuesta (readline))))

    (assert (DatosPedidos))
)

; Rellenamos todos los ficheros. Para ello simplemente debemos procesar el texto del fichero buscando los puntos
; que representan los campos a rellenar. La estrategia es coger los trozos de texto que hay entre los grupos de puntos 
; y concatenarlos con los datos que nos ha introducido el usuario
(defrule ProcesarDatos
    (Fichero (Nombre ?nombreFichero) (Texto ?asterisco ?texto))
    (DatosPedidos)
    
    (RespuestaDatos (Identificador Responsable) (DatoRecogido Nombre) (Respuesta ?Nombre))
    (RespuestaDatos (Identificador Responsable) (DatoRecogido Direccion) (Respuesta ?Direccion))
    (RespuestaDatos (Identificador Responsable) (DatoRecogido Numero) (Respuesta ?Numero))
    (RespuestaDatos (Identificador Responsable) (DatoRecogido CP) (Respuesta ?CP))
    (RespuestaDatos (Identificador Responsable) (DatoRecogido Localidad) (Respuesta ?Localidad))
    (RespuestaDatos (Identificador Responsable) (DatoRecogido Provincia) (Respuesta ?Provincia))
    (RespuestaDatos (Identificador Responsable) (DatoRecogido CAutonoma) (Respuesta ?CAutonoma))
    (RespuestaDatos (Identificador Responsable) (DatoRecogido DNI) (Respuesta ?DNI))
    
    (RespuestaDatos (Identificador Interesado) (DatoRecogido Nombre) (Respuesta ?NombreDos))
    (RespuestaDatos (Identificador Interesado) (DatoRecogido Direccion) (Respuesta ?DireccionDos))
    (RespuestaDatos (Identificador Interesado) (DatoRecogido Numero) (Respuesta ?NumeroDos))
    (RespuestaDatos (Identificador Interesado) (DatoRecogido Localidad) (Respuesta ?LocalidadDos))
    (RespuestaDatos (Identificador Interesado) (DatoRecogido Provincia) (Respuesta ?ProvinciaDos))
    (RespuestaDatos (Identificador Interesado) (DatoRecogido CAutonoma) (Respuesta ?CAutonomaDos))
    (RespuestaDatos (Identificador Interesado) (DatoRecogido CP) (Respuesta ?CPDos))
    (RespuestaDatos (Identificador Interesado) (DatoRecogido DNI) (Respuesta ?DNIDos))

    (RespuestaDatos (Identificador General) (DatoRecogido Ciudad) (Respuesta ?Ciudad))
    (RespuestaDatos (Identificador General) (DatoRecogido Dia) (Respuesta ?Dia))
    (RespuestaDatos (Identificador General) (DatoRecogido Mes) (Respuesta ?Mes))
    (RespuestaDatos (Identificador General) (DatoRecogido Anio) (Respuesta ?Anio))
    =>
    (bind ?final (sym-cat (sub-string 0 (- (str-index "....." ?texto) 1) ?texto) ?Nombre))
    (bind ?final (sym-cat ?final (sub-string (+ (str-index "....." ?texto) 5) (- (str-index "......" ?texto) 1) ?texto) ?Direccion))
    (bind ?final (sym-cat ?final (sub-string (+ (str-index "......" ?texto) 6) (- (str-index "......." ?texto) 1) ?texto) ?Numero))
    (bind ?final (sym-cat ?final (sub-string (+ (str-index "......." ?texto) 7) (- (str-index "........" ?texto) 1) ?texto) ?CP))
    (bind ?final (sym-cat ?final (sub-string (+ (str-index "........" ?texto) 8) (- (str-index "........." ?texto) 1) ?texto) ?Localidad))
    (bind ?final (sym-cat ?final (sub-string (+ (str-index "........." ?texto) 9) (- (str-index ".........." ?texto) 1) ?texto) ?Provincia))
    (bind ?final (sym-cat ?final (sub-string (+ (str-index ".........." ?texto) 10) (- (str-index "..........." ?texto) 1) ?texto) ?CAutonoma))
    (bind ?final (sym-cat ?final (sub-string (+ (str-index "..........." ?texto) 11) (- (str-index "............" ?texto) 1) ?texto) ?DNI))

    (bind ?final (sym-cat ?final (sub-string (+ (str-index "............" ?texto) 12) (- (str-index "............." ?texto) 1) ?texto) ?NombreDos))
    (bind ?final (sym-cat ?final (sub-string (+ (str-index "............." ?texto) 13) (- (str-index ".............." ?texto) 1) ?texto) ?DireccionDos))
    (bind ?final (sym-cat ?final (sub-string (+ (str-index ".............." ?texto) 14) (- (str-index "..............." ?texto) 1) ?texto) ?NumeroDos))
    (bind ?final (sym-cat ?final (sub-string (+ (str-index "..............." ?texto) 15) (- (str-index "................" ?texto) 1) ?texto) ?LocalidadDos))
    (bind ?final (sym-cat ?final (sub-string (+ (str-index "................" ?texto) 16) (- (str-index "................." ?texto) 1) ?texto) ?ProvinciaDos))
    (bind ?final (sym-cat ?final (sub-string (+ (str-index "................." ?texto) 17) (- (str-index ".................." ?texto) 1) ?texto) ?CAutonomaDos))
    (bind ?final (sym-cat ?final (sub-string (+ (str-index ".................." ?texto) 18) (- (str-index "..................." ?texto) 1) ?texto) ?CPDos))
    (bind ?final (sym-cat ?final (sub-string (+ (str-index "..................." ?texto) 19) (- (str-index "...................." ?texto) 1) ?texto) ?DNIDos))

    (bind ?final (sym-cat ?final (sub-string (+ (str-index "...................." ?texto) 20) (- (str-index "....................." ?texto) 1) ?texto) ?Ciudad))
    (bind ?final (sym-cat ?final (sub-string (+ (str-index "....................." ?texto) 21) (- (str-index "......................" ?texto) 1) ?texto) ?Dia))
    (bind ?final (sym-cat ?final (sub-string (+ (str-index "......................" ?texto) 22) (- (str-index "......................." ?texto) 1) ?texto) ?Mes))
    (bind ?final (sym-cat ?final (sub-string (+ (str-index "......................." ?texto) 23) (- (str-index "........................" ?texto) 1) ?texto) ?Anio))

    (assert (FicheroProcesado (Nombre ?nombreFichero) (Texto ?final)))
)

; Una vez tenemos los datos listos, los guardamos en ficheros de texto 
; para que el usuario pueda usarlos como desee
(defrule GuardarFicheros
    (FicheroProcesado (Nombre ?n) (Texto ?texto))
    =>
    (bind ?nombre (str-cat ?n "Procesado"))
    (open ?nombre data "w")
    (printout data ?texto crlf)
    (printout t "Se ha generado un fichero llamado " ?nombre " en el cual esta el documento relleno." crlf)
    (close data)
)