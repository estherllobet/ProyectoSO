#include <mysql.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv)
{
    // Conector para acceder al servidor de bases de datos
    MYSQL *conn;
    int err;
    
    // Creamos una conexión al servidor MySQL
    conn = mysql_init(NULL);
    if (conn == NULL)
    {
        printf("Error al crear la conexión: %u %s\n", mysql_errno(conn), mysql_error(conn));
        exit(1);
    }

    // Inicializar la conexión, indicando nuestras claves de acceso al servidor de bases de datos
    conn = mysql_real_connect(conn, "localhost", "root", "mysql", NULL, 0, NULL, 0);
    if (conn == NULL)
    {
        printf("Error al inicializar la conexión: %u %s\n", mysql_errno(conn), mysql_error(conn));
        exit(1);
    }

    // Borramos la base de datos si ya existe
    mysql_query(conn, "DROP DATABASE IF EXISTS battleship_database;");
    
    // Creamos la base de datos
    err = mysql_query(conn, "CREATE DATABASE battleship_database;");
    if (err != 0)
    {
        printf("Error al crear la base de datos: %u %s\n", mysql_errno(conn), mysql_error(conn));
        exit(1);
    }

    // Seleccionamos la base de datos para trabajar
    err = mysql_query(conn, "USE battleship_database;");
    if (err != 0)
    {
        printf("Error al seleccionar la base de datos: %u %s\n", mysql_errno(conn), mysql_error(conn));
        exit(1);
    }

    // Creamos la tabla que define la entidad 'users'
    err = mysql_query(conn,
                      "CREATE TABLE users ("
                      "id_user INTEGER not null primary key AUTO_INCREMENT, "
                      "username VARCHAR(100) NOT NULL UNIQUE, "
                      "password VARCHAR(100) NOT NULL, " 
                      "email VARCHAR(100) NOT NULL UNIQUE, "
                      "total_points INTEGER)");
    
    if (err != 0)
    {
        printf("Error al definir la tabla 'users': %u %s\n", mysql_errno(conn), mysql_error(conn));
        exit(1);
    }

    // Creamos la tabla que define la entidad 'games'
    err = mysql_query(conn,
                      "CREATE TABLE games ("
                      "id_game INTEGER not null primary key AUTO_INCREMENT, "
                      "id_player_1 INTEGER NOT NULL,"
                      "id_player_2 INTEGER NOT NULL,"
                      "points_player_1 INTEGER NOT NULL, "
                      "points_player_2 INTEGER NOT NULL, "
                      "start_time DATETIME, "
                      "end_time DATETIME, "
                      "FOREIGN KEY (id_player_1) REFERENCES users(id_user), "
                      "FOREIGN KEY (id_player_2) REFERENCES users(id_user), "
                      "CHECK (id_player_1 != id_player_2))");
    
    if (err != 0)
    {
        printf("Error al definir la tabla 'games': %u %s\n", mysql_errno(conn), mysql_error(conn));
        exit(1);
    }

    // Cerramos la conexión con el servidor MySQL
    mysql_close(conn);
    exit(0);
}
