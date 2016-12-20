/*-----------------------------------------------------------------------------
*  Fundamentos de Programación
*  Primavera 2010
*  Práctica "Información sobre las ventas de máquinas expendedoras en centros"
*----------------------------------------------------------------------------*/


#include <stdio.h>
#include <stdlib.h>

/*----------------------------------------------------------------------------
*      Definiciones de Constantes
*---------------------------------------------------------------------------*/

#define MAX_PRODUCTOS 40
#define MAX_CENTROS 20
#define FINAL_SECUENCIA -3
#define FINAL_CENTRO -2
#define FINAL_MAQUINA -1
#define FINAL_SEC_SALIDA 0 

/*----------------------------------------------------------------------------
*      Definiciones de Tipo
*---------------------------------------------------------------------------*/

typedef enum {FALSO=0, CIERTO=1} booleano;

typedef struct {
               int codiProducto;
               float ingresos;
        } tProducto;

typedef struct {
               tProducto producto[MAX_PRODUCTOS];
               int nProductos; /* número de productos en la tabla */
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
               int nCentros; /* número de centros en la tabla */
        } tResultados;

/*----------------------------------------------------------------------------
*  Declaración de acciones y funciones
*---------------------------------------------------------------------------*/

void procesarVenta(int codiProducto, float importe, tProductosCentro *productos);
int obtenerIndiceProductoMasIngresos(tProductosCentro *productos);
void mostrarResultados (tResultados *resultados);

/*---------------------------------------------------------------------------
* Algoritmo maquinasExpendedoras
*
* Pre: la entrada contiene los datos estructurados de la forma 
* <idCentro1 idMaquina11 codiProd11_1  precio11_1 codiProd11_2 precio11_2 ... -1                       
*	        idMaquina12 codiProd12_1 precio12_1  codiProd12_2 precio12_2 ... -1 
*                   ...  -1  -2
*  idCentro2 idMaquina21 codiProd21_1  precio21_1 codiProd21_2 precio1_2 ... -1                       
*	      idMaquina22 codiProd22_1 precio22_1  codiProd22_2 precio22_2 ... -1 
*	      ...  -1  -2
*                  ...  -2
*   -3>
* donde
* idCentroi: es un entero positivo, mayor que 0, que identifica un centro.
* idMaquinaij:es un entero pos. que identifica una máquina del centro idCentroi
* codiProdij_k: es un entero positivo que indica el código de un  producto  
*               expedido por la máquina de código idMaquinaij.
* Precioij_k: es el precio al que se ha vendido el producto de código 
*             codiProdij_k, expresado en euros y con dos decimales.
* Habrá como máximo 20 centros y 40 productos diferentes por centro.
*---------------------------------------------------------------------------*/
int main()
{
    tResultados resultados;
    tProductosCentro productosCentro;
    int idCentro;
    int idMaquina;
    int codiProducto;
    float precio;
    float totalIngresosCentro;
    int indice;

   resultados.idCentroMasIngresos=0;
   resultados.ingresosCentroMasIngresos=0.0;
   resultados.nCentros=0;
   scanf("%d", &idCentro); 
   /* Recorremos secuencia de entrada. En cada iteración se procesa un centro*/
   while (idCentro!=FINAL_SECUENCIA) {
      totalIngresosCentro=0.0;
      productosCentro.nProductos=0;
      scanf("%d", &idMaquina);     
     /* Recorremos subsecuencia de máquinas del centro que estamos procesando*/
      while (idMaquina!=FINAL_CENTRO) { 
         /*Recorremos la subsec. de productos del tique que estamos procesando*/
        scanf("%d", &codiProducto);
         while (codiProducto!=FINAL_MAQUINA) {
            scanf("%f", &precio);
            totalIngresosCentro=totalIngresosCentro + precio;
            procesarVenta(codiProducto,  precio, &productosCentro);
            /* Registra la venta del producto en productosCentro */
            scanf("%d", &codiProducto);
         }
         scanf("%d", &idMaquina);
      }
      if ( totalIngresosCentro > 0.0) { 
         if ( totalIngresosCentro > resultados.ingresosCentroMasIngresos) {
            resultados.ingresosCentroMasIngresos=totalIngresosCentro;
            resultados.idCentroMasIngresos=idCentro;
         }
         indice=obtenerIndiceProductoMasIngresos(&productosCentro);
         /* Busca producto que ha generado más ingresos del centro */
         resultados.resultadoCentro[resultados.nCentros].idCentro=idCentro;
         resultados.resultadoCentro[resultados.nCentros].codiProductoMasIngresos=
                     productosCentro.producto[indice].codiProducto;
         resultados.resultadoCentro[resultados.nCentros].ingresosProductoMasIngresos=
                     productosCentro.producto[indice].ingresos;
         resultados.nCentros++;
      }
      scanf("%d", &idCentro); 
   }
		 
   mostrarResultados(&resultados);	
   /*   system("PAUSE");*/
   return 0;
}
/* Pos: Se ha escrito una salida de la forma
 * <idCentroMax  ingreso idCentro1 codiProd1 Ingreso1 idCentro2 
 * codiProd2 Ingreso2 ... 0>
 * donde IdCentroMax es el identificador de un centro con mayores ingresos e 
 * Ingreso la cantidad de estos ingresos máximos.
 * Por cada centro con ingresos mayores que 0, habrá una terna 
 * [IdCentroi codiProdi Ingresoi] que indica, para el centro identificado 
 * por IdCentroi, que el producto con identificador codiProdi es uno de los 
 * que han generado mayores ingresos (no hay ningún otro producto que haya 
 * generado más ingresos en este centro). Estos ingresos son iguales a Ingresi. 
 * Finalmente, la secuencia termina con un 0, que es la marca de final. 
 */
		


void procesarVenta(int codiProducto, float importe, 
                                       tProductosCentro *productos) {

/* Pre: codiProducto se encuentra en la tabla o ésta tiene suficiente espacio 
 * Pos: si el producto ya estaba en la tabla, se han incrementado sus ingresos. 
 * Si no lo estaba, se ha añadido a la tabla. 
 */

   int i; 
   booleano encontrado;

   i = 0; 
   encontrado = FALSO; 
   while (i < (*productos).nProductos && !encontrado) {
      if ((*productos).producto[i].codiProducto == codiProducto) 
         encontrado = CIERTO;
      else
         i++;
   }
   if (encontrado) 
      (*productos).producto[i].ingresos = 
        (*productos).producto[i].ingresos + importe;
   else {
      (*productos).producto[i].ingresos = importe;
      (*productos).producto[i].codiProducto = codiProducto;
      (*productos).nProductos = i+1;
   }
}

int obtenerIndiceProductoMasIngresos(tProductosCentro *productos) {
/* Pre: hay algún producto en la tabla 
 * Pos: retorna el índice del producto con mayores ingresos 
 */

   int i;
   float maxIngresos;
   int indiceMaxIngresos;

   maxIngresos = (*productos).producto[0].ingresos;
   indiceMaxIngresos=0;
   i=1;
   while (i < (*productos).nProductos) { 
      if ((*productos).producto[i].ingresos > maxIngresos) { 
         maxIngresos= (*productos).producto[i].ingresos;
         indiceMaxIngresos=i;
      }
      i++;
   }
   return(indiceMaxIngresos);
}

void mostrarResultados( tResultados *resultados) {
/*  Pre: tResultados contiene la información obtenida de la entrada 
 * Pos: escribe la información siguiendo la poscondición del algoritmo */

   int i;

   if ((*resultados).idCentroMasIngresos) {
        printf("%d ", (*resultados).idCentroMasIngresos);
        printf("%.2f ", (*resultados).ingresosCentroMasIngresos);
        for( i=0; i < (*resultados).nCentros; i++) { 
             printf("%d ", (*resultados).resultadoCentro[i].idCentro);
             printf("%d ", (*resultados).resultadoCentro[i].codiProductoMasIngresos);
             printf("%.2f ", (*resultados).resultadoCentro[i].ingresosProductoMasIngresos);
        }
   }
   printf("%d ", FINAL_SEC_SALIDA);
}

