/* 
** Fichero: MaquinasExpendedoras.c
** Autor: Antonio V. Márquez
** Fecha: 13-05-2010
** Descripcion: ALGORITMO INGRESOS MUYBUENOMAQUINAS(MBM)-DISTRIBUIDORA DE PRODUCTOS
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX_PRODUCTOS 40
#define MAX_CENTROS 20

#define FINAL_SECUENCIA -3
#define FINAL_CENTRO -2
#define FINAL_MAQUINA -1
#define FINAL_SEC_SALIDA 0


/* Definición de tipo */
typedef enum {FALSE, TRUE} bool;

typedef struct {
                   int codiProducto;
                   float ingresos;                  
                } tProducto;

typedef struct { 
                   tProducto producto[MAX_PRODUCTOS];       
                   int nProductos;
                } tProductosCentro;

typedef struct { 
                   int idCentro;
                   int codiProductoMasIngresos;
                   float ingresosProductoMasIngresos;
                } tResultadoCentro;

typedef struct {
                   int idCentroMasIngresos;
                   float ingresosCentroMasIngresos;
                   tResultadoCentro resultadoCentro[MAX_CENTROS];       
                   int nCentros;
                } tResultados;                
   
/* Predeclaraciones de funciones */
void procesarVenta(int codiProducto,float importe,tProductosCentro *productos );
int obtenerIndiceProductoMasIngresos(tProductosCentro productos);
void mostrarResultados(tResultados  resultats);


int main(void){

    tResultados resultados;
    tProductosCentro productosCentro;

    int idCentro,idMaquina,codiProducto;
    float totalIngresosCentro;
    float precio;
    int indice;

    resultados.idCentroMasIngresos = 0;
    resultados.ingresosCentroMasIngresos = 0.0;
    resultados.nCentros = 0;
    indice = 0;
    
    scanf("%d", &idCentro);
    while (idCentro != FINAL_SECUENCIA){
         totalIngresosCentro = 0.0;
         productosCentro.nProductos = 0;
         scanf("%d", &idMaquina);
         while (idMaquina != FINAL_CENTRO) {
                   scanf("%d", &codiProducto);
                   while (codiProducto != FINAL_MAQUINA) {
                             scanf("%f", &precio);
                             totalIngresosCentro = totalIngresosCentro + precio;
                             procesarVenta(codiProducto,precio,&productosCentro);
                             scanf("%d", &codiProducto);
                             }
                   scanf("%d", &idMaquina);
         }

         if (totalIngresosCentro > 0.0){
              if (totalIngresosCentro > resultados.ingresosCentroMasIngresos){                  
                   resultados.ingresosCentroMasIngresos = totalIngresosCentro;
                   resultados.idCentroMasIngresos = idCentro;
              }
          indice = obtenerIndiceProductoMasIngresos(productosCentro);

          resultados.nCentros++;
          resultados.resultadoCentro[resultados.nCentros-1].idCentro = idCentro;
          resultados.resultadoCentro[resultados.nCentros-1].codiProductoMasIngresos=productosCentro.producto[indice].codiProducto;
          resultados.resultadoCentro[resultados.nCentros-1].ingresosProductoMasIngresos=productosCentro.producto[indice].ingresos;                            
         }
         scanf("%d", &idCentro);
    }

    mostrarResultados(resultados);
/*  system ("PAUSE"); */
    return 0;
}
/******************************************************************************/
/*accion para procesar las ventas de cada Centro*/
void procesarVenta(int codiProducto, float importe,tProductosCentro *productos){

    int i;
    bool encontrado;

    i = 0;
    encontrado = FALSE;

    while (i <= productos->nProductos && !encontrado){
         if (productos->producto[i].codiProducto == codiProducto){
             encontrado = TRUE;}
         else{
             i++; }
    }
    if (encontrado){
        productos->producto[i].ingresos = productos->producto[i].ingresos + importe;}
    else { 
         productos->nProductos = i;
         productos->producto[i].ingresos = importe;
         productos->producto[i].codiProducto = codiProducto;
    }
}
/******************************************************************************/
/*función para obtener el indice del producto con mas ingresos*/
int obtenerIndiceProductoMasIngresos(tProductosCentro productos){

    int i;
    int indiceMaxingresos;
    float maxIngresos;
    
    maxIngresos = productos.producto[0].ingresos;
    indiceMaxingresos = 1;
    i = 1;
    while (i <= productos.nProductos) {
          if (productos.producto[i].ingresos > maxIngresos) {
             maxIngresos = productos.producto[i].ingresos;
             indiceMaxingresos = i;
             }
             i++;          
          }
    return indiceMaxingresos;
}
/******************************************************************************/
/*accion para mostrar los resultados finales*/
void mostrarResultados(tResultados resultados){

    int i;

    if (resultados.idCentroMasIngresos > 0){
         
         printf("%d ", resultados.idCentroMasIngresos);
         printf("%.2f ", resultados.ingresosCentroMasIngresos);
         for (i = 0; i < resultados.nCentros; i++){
              printf("%d ", resultados.resultadoCentro[i].idCentro);
              printf("%d ", resultados.resultadoCentro[i].codiProductoMasIngresos);
              printf("%.2f ", resultados.resultadoCentro[i].ingresosProductoMasIngresos);
         }
    }
    printf("%d ",FINAL_SEC_SALIDA);
}
