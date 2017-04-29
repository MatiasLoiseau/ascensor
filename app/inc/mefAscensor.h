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

#ifndef _MEFASCENSOR_H_
#define _MEFASCENSOR_H_

/*==================[inclusiones]============================================*/
#include "mefModoConfiguracion.h"

/*==================[c++]====================================================*/

#ifdef __cplusplus
extern "C" {
#endif

/*==================[macros]=================================================*/


#define LED_MOTION  LEDB
#define LED_STOP    LED3
#define MAX_S_LEVELS  20
#define MAX_L_LEVELS  5
#define MAX_QUEUE    128

/*==================[tipos de datos declarados por el usuario]===============*/

    
typedef enum{
    EN_PLANTA_BAJA,          // 0
    MODO_CONFIGURACION,
    BAJANDO,
    SUBIENDO, 
    PARADO,
    YENDO_A_PLANTA_BAJA,
} ascensorMEF_t;



/*==================[definiciones de datos internos]=========================*/
typedef struct estadoActual {
    //ascensorMEF_t state;
    ascensorMEF_t prev_state;
    int8_t nivel_actual;
    int8_t nivel_deseado[MAX_QUEUE];
} state_t;

typedef struct configuracionAscensor
{
    configuracionMEF_t configState;
    uint8_t cantidadPisos;      //Tienen que ser variables porque en el modo configuracion
    uint8_t cantidadSubsuelos;  //pueden cambiar la cantidad de pisos y subsuelos
    delay_t tiempoSubiendo;
    delay_t tiempoBajando;
    delay_t tiempoAbriendoPuerta;
    delay_t tiempoCerrandoPuerta;
    delay_t tiempoPuertaAbierta;
    delay_t tiempoAlarmaPuertaAbierta;
    } config_t;
/*==================[declaraciones de datos externos]========================*/

/*==================[declaraciones de funciones externas]====================*/
// Prototipos de funciones
void InicializarMEFAscensor( void );
void ActualizarMEFAscensor( void );


void romperMEFAscensor( void );


/*==================[c++]====================================================*/
#ifdef __cplusplus
}
#endif

/*==================[end of file]============================================*/
#endif /* _MEFASCENSOR_H_ */
