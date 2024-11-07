#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

#include "Consultas.h"
#include "Parser.h"

void imprimirQuery(const Parser::Query &query)
{
    cout << "\n[DEBUG] Contenido de Query:" << endl;
    cout << "  Command: " << query.command << endl;
    cout << "  Table: " << query.table << endl;

    cout << "  Columns: ";
    for (const auto &col : query.columns)
        cout << col << " ";
    cout << endl;

    cout << "  Condition Column: " << query.condition_column << endl;
    cout << "  Condition Value: " << query.condition_value << endl;

    cout << "  Update Column: " << query.update_column << endl;
    cout << "  New Value: " << query.new_value << endl;

    cout << "  Join Type: " << query.join_type << endl;
    cout << "  Table1: " << query.table1 << endl;
    cout << "  Column1: " << query.column1 << endl;
    cout << "  Table2: " << query.table2 << endl;
    cout << "  Column2: " << query.column2 << endl;
}

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

        // Imprimir el contenido del query para depuración
        imprimirQuery(query);

        // Mapear el comando a la función correcta en Consultas
        if (query.command == "SELECT")
        {
            if (query.columns[0] == "*")
            {
                // SELECT * con o sin condición WHERE
                if (!query.condition_column.empty())
                {
                    cout << "\n[DEBUG] Llamando a SELECT_ALL_FROM con tabla: " << query.table
                         << ", columna condición: " << query.condition_column
                         << ", valor condición: " << query.condition_value << endl;
                    consultas.SELECT_ALL_FROM(query.table, query.condition_column, query.condition_value);
                }
                else
                {
                    cout << "\n[DEBUG] Llamando a SELECT_ALL_FROM con tabla: " << query.table << endl;
                    consultas.SELECT_ALL_FROM(query.table);
                }
            }
            else if (!query.condition_column.empty())
            {
                // SELECT columnas específicas con condición WHERE
                cout << "\n[DEBUG] Llamando a SELECT_FROM con columnas: ";
                for (const auto &col : query.columns)
                    cout << col << " ";
                cout << "y tabla: " << query.table << ", columna condición: " << query.condition_column
                     << ", valor condición: " << query.condition_value << endl;
                consultas.SELECT_FROM(query.columns, query.table, query.condition_column, query.condition_value);
            }
            else
            {
                // SELECT columnas específicas sin condición WHERE
                cout << "\n[DEBUG] Llamando a SELECT_FROM con columnas: ";
                for (const auto &col : query.columns)
                    cout << col << " ";
                cout << "y tabla: " << query.table << endl;
                consultas.SELECT_FROM(query.columns, query.table);
            }
        }
        else if (query.command == "UPDATE")
        {
            // Actualizar un registro específico
            cout << "\n[DEBUG] Llamando a UPDATE con tabla: " << query.table
                 << ", columna a actualizar: " << query.update_column
                 << ", valor nuevo: " << query.new_value
                 << ", columna condición: " << query.condition_column
                 << ", valor condición: " << query.condition_value << endl;

            consultas.UPDATE(query.update_column, query.table, query.condition_column, query.condition_value, query.new_value);
            cout << "\nRegistro actualizado correctamente.\n";
        }
        else if (query.command == "JOIN")
        {
            // Ejecutar un JOIN especificado
            cout << "\n[DEBUG] Llamando a JOIN con tipo: " << query.join_type
                 << ", tabla1: " << query.table1
                 << ", columna1: " << query.column1
                 << ", tabla2: " << query.table2
                 << ", columna2: " << query.column2 << endl;

            if (query.join_type == "inner")
            {
                consultas.SELECT_ALL_FROM(query.table1, "", "", "inner", query.column1, query.table2, query.column2);
            }
            else if (query.join_type == "left")
            {
                consultas.SELECT_ALL_FROM(query.table1, "", "", "left", query.column1, query.table2, query.column2);
            }
            else if (query.join_type == "right")
            {
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
