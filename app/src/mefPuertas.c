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


/*==================[definiciones de datos globales]=========================*/

/*==================[declaraciones de funciones internas]====================*/

/*==================[declaraciones de funciones externas]====================*/
void aperturaPuertas()
{
    /* eo: en realidad, acualiza el mef ... asi es una chanchada
    if(puertas == PUERTA_CERRADA)
    {
        puertas = ABRIENDO_PUERTA;
        delayRead(&configuracion.tiempoAbriendoPuerta); // dispara el delay de apertura de puertas
    }
    else if(puertas == PABRIENDO_PUERTA)
    {
        if(delayRead(&configuracion.tiempoAbriendoPuerta))
        {
            puertas =PUERTA_ABIERTA;
            delayRead(&configuracion.tiempoPuertaAbierta); 
        }
    }
    else if(puertas == PUERTA_ABIERTA)
    {
        if(delayRead(&configuracion.tiempoPuertaAbierta))
        {
            puertas = ALARMA_PUERTA_ABIERTA;
            delayRead(&configuracion.tiempoAlarmaPuertaAbierta); 
        }
    }*/
}


/*==================[definiciones de funciones internas]=====================*/

/*==================[definiciones de funciones externas]=====================*/

/*==================[fin del archivo]========================================*/