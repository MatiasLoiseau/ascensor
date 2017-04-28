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
#ifndef _MEFPUERTAS_H_
#define _MEFPUERTAS_H_

/*==================[inclusiones]============================================*/

/*==================[c++]====================================================*/

#ifdef __cplusplus
extern "C" {
#endif

/*==================[macros]=================================================*/

/*==================[tipos de datos declarados por el usuario]===============*/
typedef enum{
    PUERTA_CERRADA,
    ABRIENDO_PUERTA,
    PUERTA_ABIERTA,
    CERRANDO_PUERTA,
    ALARMA_PUERTA_ABIERTA
    }puertasMEF_t;
puertasMEF_t puertas;

/*==================[declaraciones de datos externos]========================*/

/*==================[declaraciones de funciones externas]====================*/

/*==================[c++]====================================================*/
#ifdef __cplusplus
}
#endif

/*==================[end of file]============================================*/
#endif /* _MEFPUERTAS_H_ */
