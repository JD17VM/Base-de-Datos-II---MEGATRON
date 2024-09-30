#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

#include "Consultas.h"

void mostrarMenu() {
    cout << "\nMENU:" << endl;
    cout << "1. SELECT ALL FROM tabla" << endl;
    cout << "2. SELECT columnas especificas FROM tabla" << endl;
    cout << "3. SELECT WHERE valor especifico" << endl;
    cout << "4. UPDATE un registro" << endl;
    cout << "5. Realizar JOIN" << endl; 
    cout << "6. Salir" << endl;
}

int main() {
    Consultas consultas("schema.txt");

    int opcion;
    string tabla, columna, valor_where, nuevo_valor, columnas_input, valor_columna_referencia, tabla_1, tabla_2, columna_1, columna_2, join_type;
    vector<string> columnas;
    size_t pos;  
    
    do {
        mostrarMenu();
        cout << "Selecciona una opcion: ";
        cin >> opcion;
        cin.ignore(); 
        
        switch (opcion) {
            case 1: // SELECT ALL
                cout << "Ingrese el nombre de la tabla (ej. estudiantes): ";
                getline(cin, tabla);
                cout << "\nMostrando todos los registros de la tabla '" << tabla << "':\n";
                consultas.SELECT_ALL_FROM(tabla);
                break;

            case 2: // SELECT columnas especificas
                cout << "Ingrese el nombre de la tabla (ej. estudiantes): ";
                getline(cin, tabla);
                cout << "Ingrese las columnas separadas por coma (ej. nombres,apellidos): ";
                getline(cin, columnas_input);
                
                // Separar columnas
                columnas.clear();
                pos = 0;  // Reutilizamos `pos` declarado fuera del `switch`
                while ((pos = columnas_input.find(',')) != string::npos) {
                    columnas.push_back(columnas_input.substr(0, pos));
                    columnas_input.erase(0, pos + 1);
                }
                columnas.push_back(columnas_input);  

                cout << "\nMostrando las columnas seleccionadas de la tabla '" << tabla << "':\n";
                consultas.SELECT_FROM(columnas, tabla);
                break;

            case 3: // SELECT WHERE
                cout << "Ingrese el nombre de la tabla (ej. estudiantes): ";
                getline(cin, tabla);
                cout << "Ingrese el nombre de la columna por la que desea filtrar (ej. apellidos): ";
                getline(cin, columna);
                cout << "Ingrese el valor que desea buscar en la columna '" << columna << "' (ej. Perez Gomez): ";
                getline(cin, valor_where);
                
                cout << "\nMostrando registros de la tabla '" << tabla << "' donde '" << columna << "' = '" << valor_where << "':\n";
                consultas.SELECT_ALL_FROM(tabla, columna, valor_where);
                break;

            case 4: // UPDATE
                cout << "Ingrese el nombre de la tabla (ej. estudiantes): ";
                getline(cin, tabla);
                cout << "Ingrese la columna que desea actualizar (ej. apellidos): ";
                getline(cin, columna);
                cout << "Ingrese el nombre de la columna de referencia para buscar (ej. id): ";
                getline(cin, valor_columna_referencia);
                cout << "Ingrese el valor en la columna de referencia (ej. 3): ";
                getline(cin, valor_where);
                cout << "Ingrese el nuevo valor para la columna '" << columna << "' (ej. Martinez Torres): ";
                getline(cin, nuevo_valor);
                
                consultas.UPDATE(columna, tabla, valor_columna_referencia, valor_where, nuevo_valor);
                cout << "\nRegistro actualizado correctamente.\n";
                break;

            case 5: // JOIN
                cout << "Seleccione el tipo de JOIN (inner, left, right): ";
                getline(cin, join_type);
                cout << "Ingrese el nombre de la primera tabla (ej. estudiantes): ";
                getline(cin, tabla_1);
                cout << "Ingrese el nombre de la segunda tabla (ej. docentes): ";
                getline(cin, tabla_2);
                cout << "Ingrese el nombre de la columna de la primera tabla para unir (ej. apellidos): ";
                getline(cin, columna_1);
                cout << "Ingrese el nombre de la columna de la segunda tabla para unir (ej. apellidos): ";
                getline(cin, columna_2);
                
                if (join_type == "inner") {
                    cout << "\nRealizando INNER JOIN entre '" << tabla_1 << "' y '" << tabla_2 << "'...\n";
                    consultas.SELECT_ALL_FROM(tabla_1, "", "", "inner", columna_1, tabla_2, columna_2);
                } else if (join_type == "left") {
                    cout << "\nRealizando LEFT JOIN entre '" << tabla_1 << "' y '" << tabla_2 << "'...\n";
                    consultas.SELECT_ALL_FROM(tabla_1, "", "", "left", columna_1, tabla_2, columna_2);
                } else if (join_type == "right") {
                    cout << "\nRealizando RIGHT JOIN entre '" << tabla_1 << "' y '" << tabla_2 << "'...\n";
                    consultas.SELECT_ALL_FROM(tabla_1, "", "", "right", columna_1, tabla_2, columna_2);
                } else {
                    cout << "Tipo de JOIN no válido. Intente nuevamente." << endl;
                }
                break;

            case 6:
                cout << "Saliendo..." << endl;
                break;

            default:
                cout << "Opcion no válida. Intente de nuevo." << endl;
                break;
        }
    } while (opcion != 6);

    return 0;
}