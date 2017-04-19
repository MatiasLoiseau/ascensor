/*============================================================================
 * Autor: Grupo 4
 * Fecha: 2017-14-04 
 *===========================================================================*/

/*==================[inlcusiones]============================================*/

#include "programa.h"   // <= su propio archivo de cabecera
#include "sapi.h"       // <= Biblioteca sAPI
#include "driverDisplays7Segmentos.h"
#include "driverTecladoMatricial.h"
#include "mefAscensor.h"
#include "mefIngresoPiso.h"
#include "mefModoConfiguracion.h"
#include "mefPuertas.h"
/*==================[definiciones y macros]==================================*/

typedef enum{
    EN_ESPERA_DE_DIGITO_1,
    EN_ESPERA_DE_DIGITO_2_O_LETRA,
    EN_ESPERA_DE_LETRA,
    GUARDAR_PISO
    }ingresoMEF_t;
    
ingresoMEF_t ingreso;

/*==================[definiciones de datos internos]=========================*/

/*==================[definiciones de datos externos]=========================*/

/*==================[definiciones de datos globales]=========================*/

/*==================[declaraciones de funciones internas]====================*/

/*==================[declaraciones de funciones externas]====================*/

/*==================[definiciones de funciones internas]=====================*/

/*==================[definiciones de funciones externas]=====================*/
void ingresarPiso(){
    //Leer datos del teclado --> driverDisplays7Segmentos.h
    
    }
/*==================[fin del archivo]========================================*/