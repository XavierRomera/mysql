//#include <my_global.h>
#include <mysql.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
int main(int argc, char **argv)
{
	MYSQL *conn;
	int err;
	// Estructura especial para almacenar resultados de consultas 
	MYSQL_RES *resultado;
	MYSQL_ROW row;
	char nombre[10]="Xavier";

	char consulta [180]="";
	char vector [20];
	char vector2 [20];
	//Creamos una conexion al servidor MYSQL 
	conn = mysql_init(NULL);
	if (conn==NULL) {
		printf ("Error al crear la conexi\uffc3\uffb3n: %u %s\n", 
				mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
	//inicializar la conexion
	conn = mysql_real_connect (conn, "localhost","root", "mysql", "BBDDv1",0, NULL, 0);
	if (conn==NULL) {
		printf ("Error al inicializar la conexi\uffc3\uffb3n: %u %s\n", 
				mysql_errno(conn), mysql_error(conn));
		exit (1);
	}

		// Ahora vamos a buscar el nombre de la persona cuyo DNI es uno
		// 
		strcpy(consulta,"SELECT participacion.idP FROM(jugador,partidas,participacion) WHERE jugador.nombre='");
		// construimos la consulta SQL
		strcat (consulta, nombre);
		strcat (consulta,"' AND jugador.id=participacion.idJ AND participacion.idP=partidas.id AND partidas.ganador='");
		strcat (consulta, nombre);
		strcat (consulta, "'");
		
		// hacemos la consulta 
		err=mysql_query (conn, consulta); 
		if (err!=0) {
			printf ("Error al consultar datos de la base %u %s\n",
					mysql_errno(conn), mysql_error(conn));
			exit (1);
		}
		//recogemos el resultado de la consulta 
		resultado = mysql_store_result (conn); 
		row = mysql_fetch_row (resultado);
		if (row == NULL)
			printf ("No se han obtenido datos en la consulta\n");
		else{

			while(row !=NULL){
				sprintf(vector,"%s%s/",vector,row[0]);
				row = mysql_fetch_row (resultado);

			}
			// El resultado debe ser una matriz con una sola fila
			// y una columna que contiene el nombre
		}
		
		strcpy(consulta,"SELECT partidas.id FROM (jugador,partidas,participacion) WHERE jugador.nombre = '");
		// construimos la consulta SQL
		strcat (consulta, nombre);
		strcat (consulta,"' AND jugador.id = participacion.idJ AND participacion.idP = partidas.id");
		
		// hacemos la consulta 
		err=mysql_query (conn, consulta); 
		if (err!=0) {
			printf ("Error al consultar datos de la base %u %s\n",
					mysql_errno(conn), mysql_error(conn));
			exit (1);
		}
		//recogemos el resultado de la consulta 
		resultado = mysql_store_result (conn); 
		row = mysql_fetch_row (resultado);
		
		if (row == NULL)
			printf ("No se han obtenido datos en la consulta\n");
		else{
			int x=0;
			int max =0;
			int i=0;
			
			while(row !=NULL){
				sprintf(vector2,"%s%s/",vector2,row[0]);
				row = mysql_fetch_row (resultado);
			}
		
			printf("%s",vector);
			printf("%s",vector2);
			
			char *p;
			char *l;
			p=strtok(vector,"/");
			int h=0;
			int g=0;
			
			while(p!=NULL){
				//if(i==0){
			
				l=strtok(vector2,"/");
				char z[10];
				strcpy(z,p);
				char y[10];
				strcpy(y,l);
				while(l!=NULL){
					if(h==0){
						if (strcmp(z,y)==0)
							x=x+1;
							h=1;
					}
					else{ 
						if (h!=0 && strcmp(z,y)==0){
							x=x+1;
							g=1;
						}
					}
					if (max<x)
						max=x;
					
					l=strtok(NULL,"/");
				}
				if (g==0){
					
					
					h=0;
					x=0;}
				p=strtok(NULL,"/");

		
				
			}
			// El resultado debe ser una matriz con una sola fila
			// y una columna que contiene el nombre
			printf("ha ganado estas partidas consecutivas: %d \n",max);
		}
		
		// cerrar la conexion con el servidor MYSQL 
		mysql_close (conn);
		exit(0);
}

