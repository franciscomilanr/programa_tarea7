/* 
Autor: Franciscomilan
Realizado: 07/04/22 - 08/05/2022
Materia: Programacion Estructurada
Profesor: Armando Cruz
Ciclo: 01/2022
Descripcion: Programa 4 del parcial 3 en C que conforma la tarea 7, el programa el arreglo de la estrcutura 
de Alumno y almacena los datos de 10 alumnos del arreglo en un archivo de texto, con las siguientes funcionalidades
0 para Salir
1 para Agregar alumnos
2 para Imprimir
3 para Alumnos aprobados
4 para Alumnos reprobados
5 para Pormedio del grupo
6 para Porcentaje de alumnos aprobados 
7 para Guardar datos
8 para Cargar datos
9 para Ordenar nombre
10 para Tarea-Ordenar por promedio
e implementa archivos, con mediciones para la materia programacion estructurada
*/

//Librerias
#include<stdio.h>
#include<stdlib.h>
#include"miLibreria.h"

//Variables globales
#define MAX 10	
struct alumno {
	char nombre[30];
	float promedio;
	int faltas;
};	
int n=0;  

//Prototipos
int menu();
void agregar(struct alumno x[]);
void imprimir(struct alumno x[], int tipo); 
void promedioGrupo (struct alumno x[]);
void porcentajeAprobados (struct alumno x[]);
void guardar (struct alumno x[]);
void cargar (struct alumno x[]);
void ordenarNombre(struct alumno x[]);
void ordenarPromedio(struct alumno x[]);

//Funciones
int main () {
	int op;
	struct alumno grupo[MAX];	
	do {
		op=menu();
		switch(op) {
			case 0: printf(" - Adios - \n");
				break;
			case 1: agregar(grupo);
				break;
			case 2: imprimir(grupo,0);
				break;
			case 3: imprimir(grupo,1);
				break;
			case 4: imprimir(grupo,2);
				break;
			case 5: promedioGrupo(grupo);
				break;
			case 6: porcentajeAprobados(grupo);
				break;
			case 7: guardar(grupo);
				break;
			case 8: cargar(grupo);
				break;
      			case 9: ordenarNombre(grupo);
       				 break;
     			case 10: ordenarPromedio(grupo);
       			 break;
		}
	}while(op!=0);
	return 0;
}

//Funcion menu
int menu() {
	//Variable local
	int opcion;
	printf(" --------------- MENU -------------\n ");
	printf(" 0. Salir \n");
	printf(" 1. Agregar alumnos \n");
	printf(" 2. Imprimir \n");
	printf(" 3. Alumnos aprobados\n");
	printf(" 4. Alumnos reprobados \n");
	printf(" 5. Promedio del grupo \n");
	printf(" 6. Porcentaje de alumno aprobados \n");
	printf(" 7. Guardar datos \n");
	printf(" 8. Cargar datos \n");
 	 printf(" 9. Ordenar por nombre \n");
 	 printf(" 10. Ordenar por promedio \n");
	opcion=leerd(" Seleccionar una opcion: ", 0, 10);
	return opcion;
}

//Funcion agregar
void agregar (struct alumno x[]) {
	int pregunta;
	while (n<MAX) {
		leers("Nombre: ", x[n].nombre,30);
    //x[n].nombre=leers("Nombre: ",0, 30);
		x[n].promedio=leerf("Promedio: ",0,10);
		x[n].faltas=leerd(" Faltas: ", 0, 32);
		pregunta=leerd(" Agregar otro alumno? (1-Si, 0-No): ",0,1);
		n++;
		if (pregunta==0) {
			break;
		}	
	}
	if (n==MAX) {
		printf(" Arreglo lleno ! \n");
		system("PAUSE");
	}
}

		
//Funcion imprimir aprobados y reprobados
void imprimir(struct alumno x[], int tipo) {
	//Variable local	
	char mensaje[20];
	switch(tipo) {
		case 0: strcpy(mensaje,"Totales");
			break;
		case 1: strcpy(mensaje, "Aprobados");
			break;
		case 2: strcpy(mensaje,"Reprobados");
			break;
	}
	//Salida
	printf("--------------Alumnos %s---------------------\n", mensaje);
	printf(" --------- DATOS DEL GRUPO ---------------\n");
	printf(" No.Alumno\t\t  Nombre\t   Promedio\t\t   Faltas\n");
	printf("--------------------------------------------------\n");
	//Proceso
	for (int i=0;i<n;i++) {
		int aprobados;
		switch(tipo) {
			case 0: printf("\t%2d \t\t\t\t %s30s \t\t %2d \t\t %4.1f \n",i+1,x[i].nombre, x[i].faltas,x[i].promedio);
				break;
			case 1: if (x[i].promedio>=7) {
					printf("\t%2d \t\t\t\t %s30s \t\t %2d \t\t %4.1f \n",i+1,x[i].nombre, x[i].faltas,x[i].promedio);
					aprobados++;
				}
				break;
			case 2: if (x[i].promedio<=7) {
					printf("\t%2d \t\t\t\t %s30s \t\t %2d \t\t %4.1f \n",i+1,x[i].nombre, x[i].faltas,x[i].promedio);
				}
				break;
			}
		}
	printf("----------------------------------------------------\n");
	system("PAUSE");
}


//Funcion promedio del grupo
void promedioGrupo (struct alumno x[]) {
	float suma=0, promedioA=0;
	int i=0;
	for (int i=0; i<n; i++) {
		suma=suma+x[i].promedio;
	}
	promedioA=suma/n;
	printf(" El promedio del grupo es: %4.1f \n", promedioA);
}

//Funcion para calcular el porcentaje
void porcentajeAprobados (struct alumno x[]) {
	float porcentajeApro=0;
	int aprobados=0;
	for (int i=0;i<n;i++) {
		if(x[i].promedio>=7 && x[i].faltas <=6) {
		aprobados++;	
		}
	}
	porcentajeApro=(aprobados*100/n);
	printf(" El porcentaje de alumnos aprobados es: %.1f\n",porcentajeApro);
}

//Funcion guardar en archivo de texto
void guardar (struct alumno x[]) {
	FILE *f;
	f=fopen("alumnos.txt","w");
	if (f==NULL) {
		printf(" Error al intentar guardar los datos !!! \n");
	} else {
		for (int i=0; i<n; i++) {
			fprintf(f,"%s \t%f \t%d\n", x[i].nombre, x[i].promedio, x[i].faltas);
		}
		fclose(f);
		printf("\n--> Se guardaron %d registro \n\n", n);
		system("PAUSE");
	}
}

//Funcion cargar archvio de texto
void cargar (struct alumno x[]){
 	 FILE *f;
 	 struct alumno a;
	  f=fopen("alumnos.txt","r");
	  n=0;
	  if (f==NULL){
	    printf("\nError al intentar cargar el archivo !! \n ");
 	 } else {
 	   printf("\n leyendo ....\n\n ");
 	   while (fscanf(f,"%30[^\n]\t %f\t %d\n",a.nombre, &a.promedio, &a.faltas)!=EOF){
   	   x[n]=a;
    	  n++;
 	    printf("%3d\t %-30s\t %4.1f\t %2d\n", n, a.nombre, a.promedio,  a.faltas);
 	   }
  	  fclose(f);
  	  printf("\n--> %d de registros leidos\n\n\n",n);
  	  system("PAUSE");
 	 }
}


//9 - Funcion ordenar por nombre
void ordenarNombre(struct alumno x[]) {
	//Ordenamiento del arreglo por el metodo de la burbuja
	for (int z=1; z<n; ++z) {
		struct alumno aux;
		for (int v=0; v<(n-z); v++) {
			//edades[v] > edades[v+1]
			if (strcmp(x[v].nombre, x[v+1].nombre)>0) {
				aux = x[v];
				x[v] = x[v+1];
				x[v+1] = aux;
			}
		}
	}
	imprimir(x,0);
}



//Funcion 10 - TAREA ordenar por promedio
/*void ordenarPromedio (struct alumno x[]) {
  
  for (int z=1; z<n; ++z) {
    struct alumno aux;
    for (int v=0; v<(n-z); v++){
      if (x[v].promedio <x[v+1].promedio){
        aux=x[v];
        x[v] = x[v+1];
        x[v+1] =aux;
      }
    }
  }
  imprimir(x,0);
}*/

