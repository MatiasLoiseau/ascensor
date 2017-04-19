/*============================================================================
 * Autor: Grupo 4
 * Fecha: 2017-14-04 
 ToDo: 
    --> establecer leyes de transicion de estados
    --> una vez que ande, y si estamos muy al pedo y se acabo el porron del 
        sabado por la noche, poner un array con la lista de pisos a recorrer y
        en el metodo de parada, verificar que el piso este en el array, y si 
        esta, parar, abrir las puertas y removerlo de la lista poniendole algun
        NaN o algo asi; Cuando llego al mas alto de los que habia en la cola, 
        recorrer la lista y si hay alguno no NaN bajar y hacer lo equivalente
        asd
 *===========================================================================*/

/*==================[inlcusiones]============================================*/
// Solamente las cosas que se necesiten, chequear. 
//#include "programa.h"   // <= su propio archivo de cabecera
#include "sapi.h"       // <= Biblioteca sAPI
//#include "driverDisplays7Segmentos.h"
#include "driverTecladoMatricial.h"
#include "mefAscensor.h"
#include "mefIngresoPiso.h"
#include "mefModoConfiguracion.h"
#include "mefPuertas.h"
/*==================[definiciones y macros]==================================*/

#define LED_MOTION  LEDB
#define LED_STOP    LED3
#define MAX_S_LEVELS  20
#define MAX_L_LEVELS  5


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
    ascensorMEF_t state;
    int8_t nivel_actual;
    int8_t nivel_deseado[128];
} estado;

typedef struct configuracionAscensor
{
    uint8_t cantidadPisos;      //Tienen que ser variables porque en el modo configuracion
    uint8_t cantidadSubsuelos;  //pueden cambiar la cantidad de pisos y subsuelos
    delay_t tiempoSubiendo;
    delay_t tiempoBajando;
    delay_t tiempoAbriendoPuerta;
    delay_t tiempoCerrandoPuerta;
    delay_t tiempoPuertaAbierta;
    delay_t tiempoAlarmaPuertaAbierta;
    } config;
/*==================[definiciones de datos externos]=========================*/

/*==================[definiciones de datos globales]=========================*/

// Variable de estado (global)
ascensorMEF_t ascensor_state;
config configuracion;


/*==================[declaraciones de funciones internas]====================*/

/*==================[declaraciones de funciones externas]====================*/

/*==================[definiciones de funciones internas]=====================*/

/*==================[definiciones de funciones externas]=====================*/
void romperMEFAscensor( void ){
   if( !gpioRead(TEC4) ){
      ascensor_state = 58;      
   }
}


// Función Inicializar MEF
void InicializarMEFAscensor( void ){
    ascensor_state = PARADO;
    configuracion.cantidadSubsuelos = 1;
    configuracion.cantidadPisos = 1;
    delayConfig( &configuracion.tiempoSubiendo, SEG_TO_MS(1) );
    delayConfig( &configuracion.tiempoBajando, SEG_TO_MS(1) );
    delayConfig( &configuracion.tiempoAbriendoPuerta, SEG_TO_MS(1) );
    delayConfig( &configuracion.tiempoCerrandoPuerta, SEG_TO_MS(1) );  
    delayConfig( &configuracion.tiempoPuertaAbierta, SEG_TO_MS(2) );
    delayConfig( &configuracion.tiempoAlarmaPuertaAbierta, SEG_TO_MS(3) ); 
    //for (unsigned int k= 0; k<MAX_QUEE;k++)           //error al compilar antes: for (unsigned int k= 0; k<MAX_QUEUE;k++)
        //estado.nivel_deseado(k)=-MAX_S_LEVELS;        //Me tira que max_queue no esta definida
}                                                       //Aparte de eso si ponemos MAX_S_LEVELS en donde dice MAX_QUEE 
                                                        //no va a funcionar y tira otro error que no conozco
// Función Actualizar MEF
void ActualizarMEFAscensor(void){
   
   switch(ascensor_state) 
    {
       case EN_PLANTA_BAJA:
           break;
       case MODO_CONFIGURACION:
           break;
       case BAJANDO:
           break;
       case SUBIENDO:
           break;
       case PARADO:
           break;
       case YENDO_A_PLANTA_BAJA:
           break;
      default:
         InicializarMEFAscensor();
        break;
         
   }      
}


/*==================[fin del archivo]========================================*/