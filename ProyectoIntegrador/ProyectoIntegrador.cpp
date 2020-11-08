// ProyectoIntegrador.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <mysql.h>
#include <iostream>

using namespace std;
int qstate;

int main(){
    
    MYSQL* conn;
    MYSQL_ROW row;
    MYSQL_RES *res;
    conn = mysql_init(0);

    conn = mysql_real_connect(conn, "localhost", "root", "12345", "semaforo_inteligente", 3306, NULL, 0);

    if (conn) {
        puts("Conexion a la base de datos exitosa");

        string query = "SELECT * FROM camara";
        const char* q = query.c_str();
        qstate = mysql_query(conn, q);
        if (!qstate) {
            res = mysql_store_result(conn);
            while (row = mysql_fetch_row(res)) {
                printf("id_Camara: %s, peatone: %s, id_Semaforo: %s, fecha: %s\n", row[0], row[1], row[2], row[0]);
            }
        } else {
            cout << "Fallo la consulta: " << mysql_error(conn) << endl;
        }
    } else {
        puts("Fallo la conexion a la base de datos");
    }
    return 0;
}

// Ejecutar programa: Ctrl + F5 o menú Depurar > Iniciar sin depurar
// Depurar programa: F5 o menú Depurar > Iniciar depuración

// Sugerencias para primeros pasos: 1. Use la ventana del Explorador de soluciones para agregar y administrar archivos
//   2. Use la ventana de Team Explorer para conectar con el control de código fuente
//   3. Use la ventana de salida para ver la salida de compilación y otros mensajes
//   4. Use la ventana Lista de errores para ver los errores
//   5. Vaya a Proyecto > Agregar nuevo elemento para crear nuevos archivos de código, o a Proyecto > Agregar elemento existente para agregar archivos de código existentes al proyecto
//   6. En el futuro, para volver a abrir este proyecto, vaya a Archivo > Abrir > Proyecto y seleccione el archivo .sln
