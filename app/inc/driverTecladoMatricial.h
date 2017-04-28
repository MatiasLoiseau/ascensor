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

#ifndef _DRIVERTECLADOMATRICIAL_H_
#define _DRIVERTECLADOMATRICIAL_H_

/*==================[inclusiones]============================================*/

/*==================[c++]====================================================*/

#ifdef __cplusplus
extern "C" {
#endif

/*==================[macros]=================================================*/

/*==================[tipos de datos declarados por el usuario]===============*/

/*==================[declaraciones de datos externos]========================*/

/*==================[declaraciones de funciones externas]====================*/

void configurarTecladoMatricial( void );
bool_t leerTecladoMatricial( void );    
uint16_t devolverTeclaApretada();

/*==================[c++]====================================================*/
#ifdef __cplusplus
}
#endif

/*==================[end of file]============================================*/
#endif /* _DRIVERTECLADOMATRICIAL_H_ */
