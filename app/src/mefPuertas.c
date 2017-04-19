/*============================================================================
 * Autor: Grupo 4
 * Fecha: 2017-14-04 
 *===========================================================================*/

/*==================[inlcusiones]============================================*/

//#include "programa.h"   // <= su propio archivo de cabecera
#include "sapi.h"       // <= Biblioteca sAPI
//#include "driverDisplays7Segmentos.h"
//#include "driverTecladoMatricial.h"
//#include "mefAscensor.h"
//#include "mefIngresoPiso.h"
//#include "mefModoConfiguracion.h"
#include "mefPuertas.h"
/*==================[definiciones y macros]==================================*/

/*==================[definiciones de datos internos]=========================*/

/*==================[definiciones de datos externos]=========================*/
#define LED_ALARMA      LEDR
#define TEC_GENTE       TEC1S
#define LED_ABIERTAS    LEDG
#define LED_ABRIENDOSE  LED1
#define LED_CERRANDOSE  LED2


typedef enum{
    PUERTA_CERRADA,
    ABRIENDO_PUERTA,
    PUERTA_ABIERTA,
    CERRANDO_PUERTA,
    ALARMA_PUERTA_ABIERTA
    }puertasMEF_t;
    
puertasMEF_t puertas;
/*==================[definiciones de datos globales]=========================*/

/*==================[declaraciones de funciones internas]====================*/

/*==================[declaraciones de funciones externas]====================*/

/*==================[definiciones de funciones internas]=====================*/

/*==================[definiciones de funciones externas]=====================*/

/*==================[fin del archivo]========================================*/