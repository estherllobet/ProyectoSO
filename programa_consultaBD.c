#include <mysql.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv)
{
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
    int err;
    char me[25];  // Mi nombre de usuario
    char opponent[25];  // Jugador contra el que deseo consultar
    char consulta[512];  // Consulta SQL

    // Creamos una conexión al servidor MySQL
    conn = mysql_init(NULL);
    if (conn == NULL)
    {
        printf("Error al crear la conexion: %u %s\n", mysql_errno(conn), mysql_error(conn));
        exit(1);
    }

    // Inicializar la conexión con la base de datos `battleship_database`
    conn = mysql_real_connect(conn, "localhost", "root", "mysql", "battleship_database", 0, NULL, 0);
    if (conn == NULL)
    {
        printf("Error al inicializar la conexion: %u %s\n", mysql_errno(conn), mysql_error(conn));
        exit(1);
    }

    // Solicitar el nombre del jugador (tú) y el oponente
    printf("Introduce tu nombre de usuario: ");
    scanf("%s", me);
    printf("Introduce el nombre del jugador contra el que deseas consultar: ");
    scanf("%s", opponent);

    // Construir la consulta SQL con JOIN entre 'games' y 'users' para obtener los nombres de los jugadores
    sprintf(consulta, 
            "SELECT g.id_game, u1.username AS player1, u2.username AS player2, "
            "g.points_player_1, g.points_player_2, g.start_time, g.end_time "
            "FROM games g "
            "JOIN users u1 ON g.id_player_1 = u1.id_user "
            "JOIN users u2 ON g.id_player_2 = u2.id_user "
            "WHERE (u1.username = '%s' AND u2.username = '%s') OR (u1.username = '%s' AND u2.username = '%s');", 
            me, opponent, opponent, me);

    // Ejecutar la consulta
    err = mysql_query(conn, consulta);
    if (err != 0)
    {
        printf("Error al realizar la consulta: %u %s\n", mysql_errno(conn), mysql_error(conn));
        exit(1);
    }

    // Obtener el resultado de la consulta
    res = mysql_store_result(conn);
    if (res == NULL)
    {
        printf("Error al obtener el resultado: %u %s\n", mysql_errno(conn), mysql_error(conn));
        exit(1);
    }

    // Mostrar las partidas encontradas
    int num_rows = mysql_num_rows(res);
    if (num_rows > 0) 
    {
        printf("Partidas entre %s y %s:\n", me, opponent);
        while ((row = mysql_fetch_row(res)) != NULL)
        {
            printf("ID Partida: %s | Jugador 1: %s | Jugador 2: %s | Puntos Jugador 1: %s | Puntos Jugador 2: %s | INICIO: %s | FINAL: %s\n",
                   row[0], row[1], row[2], row[3], row[4], row[5], row[6]);
        }
    } 
    else 
    {
        printf("No se encontraron partidas entre %s y %s.\n", me, opponent);
    }

    // Liberar el resultado y cerrar la conexión
    mysql_free_result(res);
    mysql_close(conn);

    exit(0);
}
