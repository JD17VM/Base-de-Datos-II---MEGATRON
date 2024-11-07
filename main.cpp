#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

#include "Consultas.h"
#include "Parser.h"

using namespace std;

int main()
{
    Consultas consultas("schema.txt");
    Parser parser;
    string query_string;

    cout << "Bienvenido al sistema de consultas SQL simplificado." << endl;
    cout << "Puede ingresar consultas en formato SQL (ej. SELECT, UPDATE, JOIN)." << endl;
    cout << "Escriba 'salir' para terminar." << endl;

    while (true)
    {
        cout << "\nSQL> ";
        getline(cin, query_string);

        if (query_string == "salir")
        {
            cout << "Saliendo del sistema." << endl;
            break;
        }

        // Parsear la consulta SQL ingresada por el usuario
        Parser::Query query = parser.parse(query_string);

        // Mapear el comando a la función correcta en Consultas
        if (query.command == "SELECT")
        {
            if (query.columns[0] == "*")
            {
                // SELECT ALL
                cout << "\nMostrando todos los registros de la tabla '" << query.table << "':\n";
                consultas.SELECT_ALL_FROM(query.table);
            }
            else if (!query.condition_column.empty())
            {
                // SELECT WHERE
                cout << "\nMostrando registros de la tabla '" << query.table << "' donde '"
                     << query.condition_column << "' = '" << query.condition_value << "':\n";
                consultas.SELECT_ALL_FROM(query.table, query.condition_column, query.condition_value);
            }
            else
            {
                // SELECT columnas específicas
                cout << "\nMostrando las columnas seleccionadas de la tabla '" << query.table << "':\n";
                consultas.SELECT_FROM(query.columns, query.table);
            }
        }
        else if (query.command == "UPDATE")
        {
            // Actualizar un registro específico
            cout << "\nActualizando la columna '" << query.update_column << "' en la tabla '"
                 << query.table << "' donde '" << query.condition_column << "' = '"
                 << query.condition_value << "' con el nuevo valor '" << query.new_value << "'.\n";
            consultas.UPDATE(query.update_column, query.table, query.condition_column, query.condition_value, query.new_value);
            cout << "\nRegistro actualizado correctamente.\n";
        }
        else if (query.command == "JOIN")
        {
            // Ejecutar un JOIN especificado
            if (query.join_type == "inner")
            {
                cout << "\nRealizando INNER JOIN entre '" << query.table1 << "' y '"
                     << query.table2 << "'...\n";
                consultas.SELECT_ALL_FROM(query.table1, "", "", "inner", query.column1, query.table2, query.column2);
            }
            else if (query.join_type == "left")
            {
                cout << "\nRealizando LEFT JOIN entre '" << query.table1 << "' y '"
                     << query.table2 << "'...\n";
                consultas.SELECT_ALL_FROM(query.table1, "", "", "left", query.column1, query.table2, query.column2);
            }
            else if (query.join_type == "right")
            {
                cout << "\nRealizando RIGHT JOIN entre '" << query.table1 << "' y '"
                     << query.table2 << "'...\n";
                consultas.SELECT_ALL_FROM(query.table1, "", "", "right", query.column1, query.table2, query.column2);
            }
            else
            {
                cout << "Tipo de JOIN no válido. Intente nuevamente." << endl;
            }
        }
        else
        {
            cout << "Comando no soportado. Intente una consulta SQL válida (SELECT, UPDATE, JOIN)." << endl;
        }
    }

    return 0;
}