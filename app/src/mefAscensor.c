/*============================================================================
 * Autor: Grupo 4
 * Fecha: 2017-14-04 
 
 Usuarios:
 ML: Matias Loiseau
 EO: Esteban Osella
 GDZ: Gastón Daniel Zapata
 
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
// EO: Solamente las cosas que se necesiten, chequear. 
//#include "programa.h"   // <= su propio archivo de cabecera
#include "sapi.h"       // <= Biblioteca sAPI
//#include "driverDisplays7Segmentos.h"
//#include "driverTecladoMatricial.h"
#include "mefAscensor.h"
#include "mefIngresoPiso.h"
#include "mefModoConfiguracion.h"
#include "mefPuertas.h"
/*==================[definiciones y macros]==================================*/

#define LED_MOTION  LEDB
#define LED_STOP    LED3
#define MAX_S_LEVELS  20
#define MAX_L_LEVELS  5
#define MAX_QUEE    128


    
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
    int8_t nivel_deseado[MAX_QUEE];
} state;

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
state estado;   //SI NO CREAN ESTAS VARIABLES NO VA A COMPILAR ! ! ! ! !

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
   unsigned int k = 0;
    bool remains = false;
    switch(ascensor_state) 
    {
       case EN_PLANTA_BAJA:
           aperturaPuertas();
           break;
       case MODO_CONFIGURACION:
           break;
       case BAJANDO:
           if(delayRead(&configuracion.tiempoBajando))
            {
                for (k = 0;k<MAX_QUEE;k++)
                {
                    if (estado.nivel_actual == estado.nivel_deseado[k])
                    {
                        estado.prev_state = BAJANDO;
                        ascensor_state = PARADO;
                        aperturaPuertas();
                        estado.nivel_deseado[k] = -MAX_S_LEVELS;
                        // --> la maquina de estados de las puertas dispara el tiempo de apertura
                        //puertas = ABRIENDO_PUERTA;
                    }
                    if(estado.nivel_deseado[k] >= MAX_L_LEVELS)
                        remains = true;
                }                
                if ( estado.nivel_actual > MAX_L_LEVELS && remains )
                {
                    estado.prev_state = BAJANDO;
                    ascensor_state = BAJANDO;
                    estado.nivel_actual --;
                    delayRead(&configuracion.tiempoBajando);
                }
                else
                {
                    // no quedan otros niveles por recorrer, no tiene sentido seguir en movimiento
                    estado.prev_state = PARADO;
                    ascensor_state = PARADO;
                }
            }
           break;
       case SUBIENDO:
           if(delayRead(&configuracion.tiempoSubiendo))
            {
                for (k = 0;k<MAX_QUEE;k++)
                {
                    if (estado.nivel_actual == estado.nivel_deseado[k])
                    {
                        estado.prev_state = SUBIENDO;
                        ascensor_state = PARADO;
                        estado.nivel_deseado[k] = -MAX_S_LEVELS;
                        aperturaPuertas();
                    }
                    if(estado.nivel_deseado[k] >= MAX_L_LEVELS)
                        remains = true;
                }
                if (estado.nivel_actual < MAX_S_LEVELS && remains)
                {
                    estado.nivel_actual ++;
                    delayRead(&configuracion.tiempoSubiendo);
                }
                else
                {
                    estado.prev_state = PARADO;
                    ascensor_state = PARADO;
                }
            }
           break;
       case PARADO:
           if(remains) //EO  chequear que las puertas hayan terminado de cerrarse
           {
               if (estado.prev_state = BAJANDO)
               {
                   estado.prev_state = PARADO;
                   ascensor_state = BAJANDO;
                }
                else if (estado.prev_state = SUBIENDO)
               {
                   estado.prev_state = PARADO;
                   ascensor_state = SUBIENDO;
                }
            }
           break;
       case YENDO_A_PLANTA_BAJA:
           break;
      default:
         InicializarMEFAscensor();
        break;
         
   }      
}


/*==================[fin del archivo]========================================*/