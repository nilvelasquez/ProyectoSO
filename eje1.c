//#include <my_global.h>
#include <string.h>
//#include <stdlib.h>
#include <mysql.h>
//#include <stdio.h>
void main(){
	MYSQL *conn;
	int err;
	char con[80];
	MYSQL_RES *resultado;
	MYSQL_ROW row;
	conn=mysql_init(NULL);
	if(conn==NULL)
	{
		printf ("Error al crear la conexion: %u %s\n",
				mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
	conn = mysql_real_connect (conn, "localhost","root", "mysql", "BaseDatos",0, NULL, 0);
	if (conn==NULL)
	{
		printf ("Error al inicializar la conexion: %u %s\n",
				mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
	char data[10];
	char nombre[20];
	printf("Escribe la fecha en la que quieras buscar con el formato YYYY-MM-DD: \n");
	scanf("%s", data);
	printf("Escribe el nombre de la persona que quieras: \n");
	scanf("%s", nombre);
	int idJ;
	sprintf(con, "SELECT ID FROM Jugador WHERE Nombre = '%s';", nombre);
	err= mysql_query(conn,con);
	if (err!=0)
	{
		printf ("Error al consultar datos de la base. \n");
		exit (1);
	}
	resultado = mysql_store_result(conn);
	row = mysql_fetch_row (resultado);
	if(row == NULL)
	{
		printf("No hay ID para %s.\n", nom);
	}
	else
	{
		idJ=row[0];
	}
	int idP;	
	sprintf(con,"SELECT ID FROM Partida WHERE Fecha='%s';", data);
	err= mysql_query(conn,con);
	if (err!=0)
	{
		printf ("Error al consultar datos de la base. \n");
		exit (1);
	}
	resultado = mysql_store_result(conn);
	row = mysql_fetch_row (resultado);
	if(row == NULL)
	{
		printf("No hay datos para esa fecha.\n");
	}
	else
	{
		idP=row[0];
	}
	int puntos;
	sprintf(con,"SELECT Puntuacion FROM Partidas WHERE ID_P='%s' AND ID_J='%s';",idP,idJ);
	err= mysql_query(conn,con);
	if (err!=0)
	{
		printf ("Error al consultar datos de la base.\n");
		exit (1);
	}
	resultado = mysql_store_result(conn);
	row = mysql_fetch_row (resultado);
	if (row == NULL)
		printf ("No se han obtenido datos en la consulta.\n");
	else
		puntos = row[0];
	printf("%s ha hecho %s puntos el dia %s. \n", nombre, puntos, data);
	
	mysql_close (conn);
}
