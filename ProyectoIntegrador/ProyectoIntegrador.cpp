#define _CRT_SECURE_NO_WARNINGS                                                                 //Este define es necesario para usar el sprintf, el cual sir ve para juntar la consulta a la base de datos.

#include <iostream>
#include <stdio.h>
#include <Windows.h>
#include <mysql.h>
#include <mysqld_error.h>
#include <cstring>
#include <cstdio>
#include <string>

using namespace std;

int qstate;
string query;
MYSQL *conn;
MYSQL_ROW row;
MYSQL_RES *res;
MYSQL_ROW_OFFSET pos;


bool conection(); //Declaramos la funcion que usaremos para conectarnos a la base de datos.
void consulta();
void insertar();

int main(){
    int opcion = 0;
    if (conection()) {
        puts("Conexion a la base datos exitosa");
        while (opcion >= 0 && opcion < 4) {
            cout << "------------------------------ \n";
            cout << "Que decea hacer: \n";
            cout << "Ingresar un dato.       1\n";
            cout << "Hacer una consulta.     2\n";
            cout << "Borrar un dato.         3\n";
            cout << "Salir.                  4\n";
            cin >> opcion;
            switch (opcion) {
                case 1:
                    insertar();
                    break;
                case 2:
                    consulta();
                    break;
                case 3:
                    break;
                case 4:
                    break;
                default:
                    break;
            }
        }

    } else {
        puts("Fallo la conexion a la base de datos");

    }
}

//Funcion para iniciar y verificar la conexion a la base de datos
bool conection() {
    bool bandera;                                                                                           //Esta variable nos servira para usar esta funcion en nuestra funcion main
    char password[50];                                                                                      //esto es para ingresar la contraseña

    conn = mysql_init(0);

    cout << "Ingrese la contraseña: ";
    cin.getline(password,50,'\n');                                                                          //Ingresamos la contraseña para que no este en el codigo.
    

    conn = mysql_real_connect(conn, "localhost", "root", password, "semaforo_inteligente", 3306, NULL, 0);  // Conector a la base de datos.
    if (conn) {                                                                                             // Este if es para verificar si la conexion a la base de datos es exitosa
        bandera = true;                                                                                     // Declaramos nuestra variable bandera como verdadero en caso de existir una conexion exitosa a la base de datos
    } else {
        bandera = false;                                                                                    //  Declaramos nuestra variable bandera como false en caso de no existir una conexion exitosa a la base de datos
    }
    return bandera;                                                                                         // Regresamos el valor que nos haya arrojado nuestro if.
}

//Funcion exlusiva para hacer consultas a la base de datos
void consulta() {
    string cadena;                                                                                  // Esta variable es para guardar el nombre de la tabla
    int opcion;

    cout << "   **CONSULTAS** \n";
    cout << "     Que decea ver: \n";
    cout << "     Camara.       1\n";
    cout << "     Vehiculo.     2\n";
    cout << "     Semaforo.     3\n";
    cin >> opcion;                                                                                  // Switch para setear los nombres de las tablas en la variable cadena
    switch (opcion) {
        case 1:
            cadena = "camara";
            break;
        case 2:
            cadena = "senso_veicular";
            break;
        case 3:
            cadena = "semaforo";
            break;
        default:
            break;
    }

    query = "SELECT * FROM "+ cadena;                                                        // Declaro la consulta y concateno el nombre de la tabla previamente guardada
    const char* q = query.c_str();                                                                  // Se hace un parse de String a Char
    qstate = mysql_query(conn, q);
    if (!qstate) {
        res = mysql_store_result(conn);
        int cout = mysql_num_rows(res);                                                             // Recupero el numero de filas que hay en la tabla.
        printf("# de rows = %d\n", cout);                                                           // Imprimo el numero de filas que hay en la tabla.

        while ((row = mysql_fetch_row(res)) != NULL) {                                              // Este while es para la impresion de las consultas. Las cuales se imprimiran Columna y fila. 
            for (int i = 0; i < mysql_num_fields(res); i++) {                                       // Este for es para recorrer las filas e imprimirlas
                printf("%s \t",row[i] != NULL ? row[i] : NULL );                                    // Impresion de las filas.
            }
            printf("\n");                                                                           // Imprimo un salto de lina.
        }
    }
    else {
        cout << "Fallo la consulta: " << mysql_error(conn) << endl;                                 // En caso de fallar la conexion se mustra el error.
    }


}

//Funcuion para insertar datos a la base de datos.
void insertar() {
    char *consulta;
    char id[4];
    char direccion[45];
    char colonia[45];
    char estado[45];
    char querry[] = "INSERT INTO semaforo (`id_Semaforo`, `Direcion`, `colonia`, `Estado`) VALUES (\'%s\', \'%s\', \'%s\', \'%s\');";

    /*declaramos todo lo que usaremos para hacer la consulta a la base de datos.*/


    cout << "=================\n";
    cout << "/////////////////\n";
    cout << "=================\n";
    cout << "   **INSERTAR**  \n";
    cout << "Ingrese id_Semaforo: (NOTA, VERIFIQUE QUE EL ID NO SE REPITA) ";
    cin.get();
    cin.getline(id,4,'\n');
    cout << "Ingrese la direccion del semaforo: ";
    cin.getline(direccion, 45, '\n');
    cout << "Ingrese la colonia del semaforo: ";
    cin.getline(colonia, 45, '\n');
    cout << "Ingrese el estado del semaforo: ";
    cin.getline(estado, 45, '\n');

    cout << "Esros fueron sus valores ingresados: ['" << id << "', '" <<direccion << "', '" << colonia << "', '" << estado <<"']" << endl ;
    
    /*Ingresamos los datos y le mostramos al usuario lo que ingreso.*/


    consulta = new char[strlen(querry)+strlen(id)+strlen(direccion)+strlen(colonia)+strlen(estado)];        // Hacemos la concatenacion del querry (la sentencia de la base de datos.)
    sprintf(consulta, querry, id, direccion, colonia, estado);
    /* 
     * SPRINTF: Esta función es equivalente a fprintf, excepto que el argumento cadena especifica un array en el 
     *          cual la salida generada es para ser escrita, en vez de un stream. Un carácter nulo es escrito al 
     *          final de los caracteres escritos; no es contado como parte de la suma retornada. 
     *          El comportamiento acerca de copiando entre objetos que se superponen no está definido.
     */
    mysql_query(conn, consulta);                                                                            // Enviamos la consulta a la base de datos
    cout << "Esta fue su consulta: " << consulta << endl;                                                   // Le mostramos al usuario la consulta que hizo.
    delete[] consulta;                                                                                      // Limpiamos la variable consulta, para fururas inserciones.
}