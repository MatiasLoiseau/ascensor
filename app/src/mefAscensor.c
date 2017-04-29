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
#include "mefPuertas.h"
/*==================[definiciones y macros]==================================*/



/*==================[definiciones de datos externos]=========================*/

/*==================[definiciones de datos globales]=========================*/

// Variable de estado (global)
ascensorMEF_t ascensor_state;
config_t configuracion;
state_t estado;   //SI NO CREAN ESTAS VARIABLES NO VA A COMPILAR ! ! ! ! !

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
    uint8_t upcount;
    uint8_t downcount;
    switch(ascensor_state) 
    {
       case EN_PLANTA_BAJA:
            aperturaPuertas();
            upcount = 0;
            downcount = 0;
            for(k= 0;k<MAX_QUEUE;k++)
            {
                if(estado.nivel_deseado[k]>=configuracion.cantidadSubsuelos)
                {
                    remains = true;
                    if (estado.nivel_deseado[k]>=configuracion.cantidadSubsuelos>0)
                        upcount++;
                    else
                        downcount++;
                    }
            }
            if(remains  && (puertas == PUERTA_CERRADA))
            {
                if(upcount >= downcount)
                    ascensor_state = SUBIENDO;
                else
                    ascensor_state = BAJANDO;
            }
             if(configuracion.configState == PENDIENTE)
                 ascensor_state = MODO_CONFIGURACION;
           break;
       case MODO_CONFIGURACION:
           secuenciaConfiguracion();
            if(configuracion.configState == SALIR)
                ascensor_state = EN_PLANTA_BAJA;
           break;
       case BAJANDO:
           if(delayRead(&configuracion.tiempoBajando))
            {
                estado.nivel_actual--;
                for (k = 0;k<MAX_QUEUE;k++)
                {
                    if (estado.nivel_actual == estado.nivel_deseado[k])
                    {
                        estado.prev_state = BAJANDO;
                        ascensor_state = PARADO;
                        aperturaPuertas();
                        estado.nivel_deseado[k] = -MAX_S_LEVELS;
                    }
                    if(estado.nivel_deseado[k] >= MAX_L_LEVELS)
                        remains = true;
                }                
                if ( (estado.nivel_actual > -MAX_L_LEVELS) && remains )
                {
                    estado.prev_state = BAJANDO;
                    ascensor_state = BAJANDO;
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
                estado.nivel_actual++;
                for (k = 0;k<MAX_QUEUE;k++)
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
           if(delayRead(&configuracion.tiempoBajando))
            {
                estado.nivel_actual--;
                for (k = 0;k<MAX_QUEUE;k++)
                {
                    if (estado.nivel_actual == 0)
                    {
                        estado.prev_state = BAJANDO;
                        ascensor_state = PARADO;
                        aperturaPuertas();
                        if (estado.nivel_deseado[k] == 0)
                            estado.nivel_deseado[k] = -MAX_S_LEVELS;
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
      default:
         InicializarMEFAscensor();
        break;
         
   }      
}


/*==================[fin del archivo]========================================*/