/*============================================================================
 * Autor: Grupo 4
 * Fecha: 2017-14-04 
 *===========================================================================*/

/*==================[inlcusiones]============================================*/

#include "programa.h"   // <= su propio archivo de cabecera
#include "sapi.h"       // <= Biblioteca sAPI
//#include "driverDisplays7Segmentos.h"
#include "driverTecladoMatricial.h"
//#include "mefAscensor.h"
//#include "mefIngresoPiso.h"
//#include "mefModoConfiguracion.h"
//#include "mefPuertas.h"
/*==================[definiciones y macros]==================================*/

typedef enum{
    EN_ESPERA_DE_DIGITO_1,
    EN_ESPERA_DE_DIGITO_2_O_LETRA,
    EN_ESPERA_DE_LETRA,
    GUARDAR_PISO
    }ingresoMEF_t;
    

/*==================[definiciones de datos internos]=========================*/

/*==================[definiciones de datos externos]=========================*/

/*==================[definiciones de datos globales]=========================*/

ingresoMEF_t estadoIngreso;
uint16_t valorPiso[2];  //Aca va a estar guardado el valor del piso

/*==================[declaraciones de funciones internas]====================*/

/*==================[declaraciones de funciones externas]====================*/

/*==================[definiciones de funciones internas]=====================*/

/*==================[definiciones de funciones externas]=====================*/

void romperMEFIngresoPiso( void ){
   if( !gpioRead(TEC4) ){
      estadoIngreso=EN_ESPERA_DE_DIGITO_1;  //Si se presiona la tec4 vuelve al comienzo del MEF
   }
}

void InicializarMEFIngresoPiso( void ){
    configurarTecladoMatricial();   //Inicializo el driver del teclado
    
    }

void ActualizarMEFIngresoPiso( void ){
    switch(estadoIngreso){

        case EN_ESPERA_DE_DIGITO_1:
            valorPiso[0]='0';
            valorPiso[1]='0';   //inicializa en 0
            if (leerTecladoMatricial()){
                estadoIngreso=EN_ESPERA_DE_DIGITO_2_O_LETRA;
                delay(100); //efecto anti-rebote
                }
        break;
        
        case EN_ESPERA_DE_DIGITO_2_O_LETRA:
            valorPiso[0]=devolverTeclaApretada();
            //FALTA PONER:  Iniciar temporizador1
            //FALTA PONER: si temporizador1=time-out --> estadoIngreso=EN_ESPERA_DE_DIGITO_1
            if(leerTecladoMatricial()){
                if(devolverTeclaApretada()==(0x0b)){
                    estadoIngreso=EN_ESPERA_DE_DIGITO_1;
                    }
                if(devolverTeclaApretada()==(0x0a)){
                    estadoIngreso=GUARDAR_PISO;
                    }
                if((devolverTeclaApretada()!=(0x0c))&&(devolverTeclaApretada()!=(0x0d))&& //Esto es para asegurarse
                    (devolverTeclaApretada()!=(0x0e))&&(devolverTeclaApretada()!=(0x0f))){ //Que ingreso un numero y no otra letra
                        estadoIngreso=EN_ESPERA_DE_LETRA;
                        }
                } 
                delay(100); //efecto anti-rebote
        break;
        
        case EN_ESPERA_DE_LETRA:
            if(leerTecladoMatricial()){
                valorPiso[1]=devolverTeclaApretada();
                //FALTA PONER: Iniciar temporizador2
                if(devolverTeclaApretada()==(0x0b)){
                        estadoIngreso=EN_ESPERA_DE_DIGITO_1;
                    }
                if(devolverTeclaApretada()==(0x0a)){
                        estadoIngreso=GUARDAR_PISO;
                    }
                }
                //FALTA PONER:  Si el temporizador2=time-out
                //estadoIngreso=EN_ESPERA_DE_DIGITO_1;
            delay(100); //efecto anti-rebote
        break;
        
        case GUARDAR_PISO:
            //El piso ya esta guardado antes
            estadoIngreso=EN_ESPERA_DE_DIGITO_1;
            //Despues ver que hacer con "valorPiso[]"
            //Osea como le paso ese valor a mefAscensor
        break;
                
        }
    
    }



void ingresarPiso(){

    
    }
/*==================[fin del archivo]========================================*/