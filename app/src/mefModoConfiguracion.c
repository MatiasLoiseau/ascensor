/*============================================================================
 * Autor: Grupo 4
 * Fecha: 2017-14-04 
 
 Usuarios:
 ML: Matias Loiseau
 EO: Esteban Osella
 GDZ: Gastón Daniel Zapata
 
 ToDo: 
    --> 
        
        
 *===========================================================================*/

/*==================[inlcusiones]============================================*/

//#include "programa.h"   // <= su propio archivo de cabecera
#include "sapi.h"       // <= Biblioteca sAPI
//#include "driverDisplays7Segmentos.h"
//#include "driverTecladoMatricial.h"
#include "mefAscensor.h"
//#include "mefIngresoPiso.h"
#include "mefModoConfiguracion.h"
//#include "mefPuertas.h"
/*==================[definiciones y macros]==================================*/

/* --> fue al .h

typedef enum{
    ESPERA_MENU, // entra a la configuracion
    ESPERA_CONFIRMACION,
    CONFIGURANDO,
    GUARDANDO,
    SALIR,
    PENDIENTE
    }configuracionMEF_t;
*/
/*==================[definiciones de datos internos]=========================*/

/*==================[definiciones de datos externos]=========================*/
// ver de estas cuales son las que son necesarias conservar
extern config_t configuracion;
extern ascensorMEF_t ascensor_state;
extern state_t estado;   
/*==================[definiciones de datos globales]=========================*/

/*==================[declaraciones de funciones internas]====================*/

/*==================[declaraciones de funciones externas]====================*/

void secuenciaConfiguracion(){}
/*==================[definiciones de funciones internas]=====================*/

/*==================[definiciones de funciones externas]=====================*/

/*==================[fin del archivo]========================================*/