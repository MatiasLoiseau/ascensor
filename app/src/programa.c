/*============================================================================
 * Autor: Grupo 4
 * Fecha: 2017-14-04
 
Entregable 10: Ascensor
   Estados:
      - 1-EN_ESPERA
      - 2-SUBIENDO
      - 3-BAJANDO
      - 4-ABRIENDO_PUERTA
	  - 5-PUERTA_ABIERTA
	  - 6-CERRANDO_PUERTA
	  - 7-PUERTA_CERRADA
	  - 8-MODO_CONFIGURACION
	  - 9-LEER_PISO
	  - 10-ALARMA_PUERTA_ABIERTA
	  
   Cambio de estados por tiempo:
      
	  -SUBIENDO: 1seg  //tiempo que tarda en subir un piso
	  -BAJANDO: 1seg   //tiempo que tarda en bajar un piso
	  -ABRIENDO_PUERTA: 1seg
	  -CERRANDO_PUERTA: 1seg
	  -PUERTA_ABIERTA: 2 seg
	  -ALARMA_PUERTA_ABIERTA: 3seg // si pasan 3 seg con puerta abierta activa la alarma
      
 
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

// Nuevo tipo de datos enumerado llamado estadoMEF
typedef enum{
   EN_ESPERA,          		// 0
   SUBIENDO,           		// 1
   BAJANDO,            		// 2
   ABRIENDO_PUERTA,    		// 3
   PUERTA_ABIERTA,     		// 4
   CERRANDO_PUERTA,    		// 5
   PUERTA_CERRADA,     		// 6
   MODO_CONFIGURACION,  	// 7
   LEER_PISO,           	// 8
   ALARMA_PUERTA_ABIERTA,   //10
    
} estadoMEF_t;

#define SEG_TO_MS(val) ((val)*1000)

/*==================[definiciones de datos internos]=========================*/

/*==================[definiciones de datos externos]=========================*/

/*==================[definiciones de datos globales]=========================*/

// Variable de estado (global)
estadoMEF_t estadoActual;

int cantidadPisos;      //Tienen que ser variables porque en el modo configuracion
int cantidadSubsuelos;  //pueden cambiar la cantidad de pisos y subsuelos

/*==================[declaraciones de funciones internas]====================*/

/*==================[declaraciones de funciones externas]====================*/

// Prototipos de funciones
void InicializarMEF( void );
void ActualizarMEF( void );


void romperMEF( void );

/*==================[funcion principal]======================================*/

// FUNCION PRINCIPAL, PUNTO DE ENTRADA AL PROGRAMA LUEGO DE ENCENDIDO O RESET.
int main( void ){

   // ---------- CONFIGURACIONES ------------------------------
   // Inicializar y configurar la plataforma
    boardConfig();
    uartConfig( UART_USB, 115200 ); // Configurar UART a 115200 
    configurarTecladoMatricial(); // Configurar teclado matricial
    InicializarMEF();

    //configuracion del driver D
   // ---------- REPETIR POR SIEMPRE --------------------------
   while( TRUE )
   {  
    
    ActualizarMEF();
      
    romperMEF();
   } 

   // NO DEBE LLEGAR NUNCA AQUI, debido a que a este programa se ejecuta 
   // directamenteno sobre un microcontroladore y no es llamado/ por ningun
   // Sistema Operativo, como en el caso de un programa para PC.
   return 0;
}

/*==================[definiciones de funciones internas]=====================*/

/*==================[definiciones de funciones externas]=====================*/

void romperMEF( void ){
   if( !gpioRead(TEC4) ){
      estadoActual = 58;      
   }
}


delay_t tiempoSubiendo;
delay_t tiempoBajando;
delay_t tiempoAbriendoPuerta;
delay_t tiempoCerrandoPuerta;
delay_t tiempoPuertaAbierta;
delay_t tiempoAlarmaPuertaAbierta;


// Función Inicializar MEF
void InicializarMEF( void ){
    estadoActual = EN_ESPERA;
   
    delayConfig( &tiempoSubiendo, SEG_TO_MS(1) );
    delayConfig( &tiempoBajando, SEG_TO_MS(1) );
    delayConfig( &tiempoAbriendoPuerta, SEG_TO_MS(1) );
    delayConfig( &tiempoCerrandoPuerta, SEG_TO_MS(1) );  
    delayConfig( &tiempoPuertaAbierta, SEG_TO_MS(2) );
    delayConfig( &tiempoAlarmaPuertaAbierta, SEG_TO_MS(3) );   
}

// Función Actualizar MEF
void ActualizarMEF(void){
   
   switch(estadoActual) {
      
      case EN_ESPERA:
               
      break;
      
      case SUBIENDO:
                
      break;
      
      case BAJANDO:
         
      break;
      
      case ABRIENDO_PUERTA:
           
      break;
	  
	  case CERRANDO_PUERTA:
         
	  break;
		 
	  case PUERTA_CERRADA:
         
	  break; 
	  
	  case MODO_CONFIGURACION:
        
	  break;
		 
	  case LEER_PISO:
         
	  break;
		 
	  case ALARMA_PUERTA_ABIERTA:
         
      break;
      
      default:
         //Si algo modificó la variable estadoActual
         // a un estado no válido llevo la MEF a un
         // lugar seguro, por ejemplo, la reinicio:
         InicializarMEF();
      break;
         
   }      
}


/*==================[fin del archivo]========================================*/