#include "Schema.h"

class Consultas
{
private:
    Schema schema;

public:
    Consultas(const string &archivo_schema)
    {
        schema.leerArchivo(archivo_schema);
    }

    void INNER_JOIN(const string &columna_1, const string &tabla_1, const string &columna_2, const string &tabla_2)
    {
        Tabla *t1 = schema.buscarTabla(tabla_1);
        Tabla *t2 = schema.buscarTabla(tabla_2);

        if (!t1 || !t2)
        {
            cerr << "Error: Una de las tablas no existe." << endl;
            return;
        }

        int index_col1 = -1, index_col2 = -1;

        for (size_t i = 0; i < t1->columnas.size(); i++)
        {
            if (t1->columnas[i].nombre == columna_1)
            {
                index_col1 = i;
                break;
            }
        }
        for (size_t i = 0; i < t2->columnas.size(); i++)
        {
            if (t2->columnas[i].nombre == columna_2)
            {
                index_col2 = i;
                break;
            }
        }

        if (index_col1 == -1 || index_col2 == -1)
        {
            cerr << "Error: Una de las columnas no existe." << endl;
            return;
        }

        ifstream archivo_t1(tabla_1 + ".txt");
        ifstream archivo_t2(tabla_2 + ".txt");

        if (!archivo_t1.is_open() || !archivo_t2.is_open())
        {
            cerr << "Error al abrir uno de los archivos de las tablas." << endl;
            return;
        }

        string registro_t1, registro_t2;
        vector<vector<string>> resultados;

        vector<vector<string>> datos_t2;
        while (getline(archivo_t2, registro_t2))
        {
            stringstream ss(registro_t2);
            vector<string> valores_t2;
            string valor;
            while (getline(ss, valor, '#'))
            {
                valores_t2.push_back(valor);
            }
            datos_t2.push_back(valores_t2);
        }

        while (getline(archivo_t1, registro_t1))
        {
            stringstream ss1(registro_t1);
            vector<string> valores_t1;
            string valor1;
            while (getline(ss1, valor1, '#'))
            {
                valores_t1.push_back(valor1);
            }

            for (const auto &registro_2 : datos_t2)
            {
                if (valores_t1[index_col1] == registro_2[index_col2])
                {
                    vector<string> join_result = valores_t1;
                    join_result.insert(join_result.end(), registro_2.begin(), registro_2.end());
                    resultados.push_back(join_result);
                }
            }
        }

        for (const auto &resultado : resultados)
        {
            for (const auto &campo : resultado)
            {
                cout << campo << " ";
            }
            cout << endl;
        }
    }

    void LEFT_JOIN(const string &columna_1, const string &tabla_1, const string &columna_2, const string &tabla_2)
    {
        Tabla *t1 = schema.buscarTabla(tabla_1);
        Tabla *t2 = schema.buscarTabla(tabla_2);

        if (!t1 || !t2)
        {
            cerr << "Error: Una de las tablas no existe." << endl;
            return;
        }

        int index_col1 = -1, index_col2 = -1;

        for (size_t i = 0; i < t1->columnas.size(); i++)
        {
            if (t1->columnas[i].nombre == columna_1)
            {
                index_col1 = i;
                break;
            }
        }
        for (size_t i = 0; i < t2->columnas.size(); i++)
        {
            if (t2->columnas[i].nombre == columna_2)
            {
                index_col2 = i;
                break;
            }
        }

        if (index_col1 == -1 || index_col2 == -1)
        {
            cerr << "Error: Una de las columnas no existe." << endl;
            return;
        }

        ifstream archivo_t1(tabla_1 + ".txt");
        ifstream archivo_t2(tabla_2 + ".txt");

        if (!archivo_t1.is_open() || !archivo_t2.is_open())
        {
            cerr << "Error al abrir uno de los archivos de las tablas." << endl;
            return;
        }

        string registro_t1, registro_t2;
        vector<vector<string>> datos_t2;

        while (getline(archivo_t2, registro_t2))
        {
            stringstream ss(registro_t2);
            vector<string> valores_t2;
            string valor;
            while (getline(ss, valor, '#'))
            {
                valores_t2.push_back(valor);
            }
            datos_t2.push_back(valores_t2);
        }

        while (getline(archivo_t1, registro_t1))
        {
            stringstream ss1(registro_t1);
            vector<string> valores_t1;
            string valor1;
            while (getline(ss1, valor1, '#'))
            {
                valores_t1.push_back(valor1);
            }

            bool coincidencia = false;

            for (const auto &registro_2 : datos_t2)
            {
                if (valores_t1[index_col1] == registro_2[index_col2])
                {
                    vector<string> join_result = valores_t1;
                    join_result.insert(join_result.end(), registro_2.begin(), registro_2.end());
                    for (const auto &campo : join_result)
                    {
                        cout << campo << " ";
                    }
                    cout << endl;
                    coincidencia = true;
                }
            }

            if (!coincidencia)
            {
                for (const auto &campo : valores_t1)
                {
                    cout << campo << " ";
                }
                for (size_t i = 0; i < t2->columnas.size(); i++)
                {
                    cout << "NULL ";
                }
                cout << endl;
            }
        }

        archivo_t1.close();
        archivo_t2.close();
    }

    void RIGHT_JOIN(const string &columna_1, const string &tabla_1, const string &columna_2, const string &tabla_2)
    {
        Tabla *t1 = schema.buscarTabla(tabla_1);
        Tabla *t2 = schema.buscarTabla(tabla_2);

        if (!t1 || !t2)
        {
            cerr << "Error: Una de las tablas no existe." << endl;
            return;
        }

        int index_col1 = -1, index_col2 = -1;

        for (size_t i = 0; i < t1->columnas.size(); i++)
        {
            if (t1->columnas[i].nombre == columna_1)
            {
                index_col1 = i;
                break;
            }
        }
        for (size_t i = 0; i < t2->columnas.size(); i++)
        {
            if (t2->columnas[i].nombre == columna_2)
            {
                index_col2 = i;
                break;
            }
        }

        if (index_col1 == -1 || index_col2 == -1)
        {
            cerr << "Error: Una de las columnas no existe." << endl;
            return;
        }

        ifstream archivo_t1(tabla_1 + ".txt");
        ifstream archivo_t2(tabla_2 + ".txt");

        if (!archivo_t1.is_open() || !archivo_t2.is_open())
        {
            cerr << "Error al abrir uno de los archivos de las tablas." << endl;
            return;
        }

        string registro_t1, registro_t2;
        vector<vector<string>> datos_t1;

        while (getline(archivo_t1, registro_t1))
        {
            stringstream ss(registro_t1);
            vector<string> valores_t1;
            string valor;
            while (getline(ss, valor, '#'))
            {
                valores_t1.push_back(valor);
            }
            datos_t1.push_back(valores_t1);
        }

        while (getline(archivo_t2, registro_t2))
        {
            stringstream ss2(registro_t2);
            vector<string> valores_t2;
            string valor2;
            while (getline(ss2, valor2, '#'))
            {
                valores_t2.push_back(valor2);
            }

            bool coincidencia = false;

            for (const auto &registro_1 : datos_t1)
            {
                if (valores_t2[index_col2] == registro_1[index_col1])
                {
                    vector<string> join_result = valores_t2;
                    join_result.insert(join_result.end(), registro_1.begin(), registro_1.end());
                    for (const auto &campo : join_result)
                    {
                        cout << campo << " ";
                    }
                    cout << endl;
                    coincidencia = true;
                }
            }

            if (!coincidencia)
            {
                for (const auto &campo : valores_t2)
                {
                    cout << campo << " ";
                }
                for (size_t i = 0; i < t1->columnas.size(); i++)
                {
                    cout << "NULL ";
                }
                cout << endl;
            }
        }

        archivo_t1.close();
        archivo_t2.close();
    }

    void SELECT_ALL_FROM(const string &nombre_tabla, const string &nombre_columna = "", const string &valor_where_equal = "", const string &join_type = "", const string &columna_1 = "", const string &tabla_2 = "", const string &columna_2 = "")
    {
        Tabla *tabla = schema.buscarTabla(nombre_tabla);
        if (!tabla)
        {
            cerr << "Error: No se encontró la tabla " << nombre_tabla << endl;
            return;
        }

        if (!join_type.empty())
        {
            if (join_type == "inner")
            {
                INNER_JOIN(columna_1, nombre_tabla, columna_2, tabla_2);
            }
            else if (join_type == "left")
            {
                LEFT_JOIN(columna_1, nombre_tabla, columna_2, tabla_2);
            }
            else if (join_type == "right")
            {
                RIGHT_JOIN(columna_1, nombre_tabla, columna_2, tabla_2);
            }
            return;
        }

        string archivo_tabla = nombre_tabla + ".txt";
        ifstream archivo(archivo_tabla);
        if (!archivo.is_open())
        {
            cerr << "Error al abrir el archivo de la tabla: " << archivo_tabla << endl;
            return;
        }

        string registro;
        int indice_columna = -1;
        if (!nombre_columna.empty() && !valor_where_equal.empty())
        {
            for (size_t i = 0; i < tabla->columnas.size(); i++)
            {
                if (tabla->columnas[i].nombre == nombre_columna)
                {
                    indice_columna = i;
                    break;
                }
            }
            if (indice_columna == -1)
            {
                cerr << "Error: No se encontró la columna " << nombre_columna << endl;
                return;
            }
        }

        while (getline(archivo, registro))
        {
            if (!valor_where_equal.empty())
            {
                if (tabla->mostrarRegistroSiCoincide(registro, indice_columna, valor_where_equal))
                {
                    continue;
                }
            }
            else
            {
                tabla->mostrarRegistro(registro);
            }
        }

        archivo.close();
    }

    void SELECT_FROM(const vector<string> &columnas, const string &nombre_tabla, const string &nombre_columna = "", const string &valor_where_equal = "", const string &join_type = "", const string &columna_1 = "", const string &tabla_2 = "", const string &columna_2 = "")
    {
        Tabla *tabla = schema.buscarTabla(nombre_tabla);
        if (!tabla)
        {
            cerr << "Error: No se encontró la tabla " << nombre_tabla << endl;
            return;
        }

        if (!join_type.empty())
        {
            if (join_type == "inner")
            {
                INNER_JOIN(columna_1, nombre_tabla, columna_2, tabla_2);
            }
            else if (join_type == "left")
            {
                LEFT_JOIN(columna_1, nombre_tabla, columna_2, tabla_2);
            }
            else if (join_type == "right")
            {
                RIGHT_JOIN(columna_1, nombre_tabla, columna_2, tabla_2);
            }
            return;
        }

        vector<int> indices_columnas;
        for (const auto &columna : columnas)
        {
            for (size_t i = 0; i < tabla->columnas.size(); i++)
            {
                if (tabla->columnas[i].nombre == columna)
                {
                    indices_columnas.push_back(i);
                    break;
                }
            }
        }

        string archivo_tabla = nombre_tabla + ".txt";
        ifstream archivo(archivo_tabla);
        if (!archivo.is_open())
        {
            cerr << "Error al abrir el archivo de la tabla: " << archivo_tabla << endl;
            return;
        }

        string registro;
        int indice_columna = -1;
        if (!nombre_columna.empty() && !valor_where_equal.empty())
        {
            for (size_t i = 0; i < tabla->columnas.size(); i++)
            {
                if (tabla->columnas[i].nombre == nombre_columna)
                {
                    indice_columna = i;
                    break;
                }
            }
            if (indice_columna == -1)
            {
                cerr << "Error: No se encontró la columna " << nombre_columna << endl;
                return;
            }
        }

        while (getline(archivo, registro))
        {
            if (!valor_where_equal.empty())
            {
                if (tabla->mostrarRegistroSiCoincide(registro, indice_columna, valor_where_equal))
                {
                    tabla->mostrarRegistroSeleccionado(registro, indices_columnas);
                }
            }
            else
            {
                tabla->mostrarRegistroSeleccionado(registro, indices_columnas);
            }
        }

        archivo.close();
    }

    void UPDATE(const string& columna, const string& tabla, const string& valor_columna_referencia, const string& valor_where_equal, const string& valor_nuevo) {
    Tabla* t = schema.buscarTabla(tabla);
    if (!t) {
        cerr << "Error: No se encontró la tabla " << tabla << endl;
        return;
    }

    int index_columna = -1, index_columna_referencia = -1;

    for (size_t i = 0; i < t->columnas.size(); i++) {
        if (t->columnas[i].nombre == columna) {
            index_columna = i;
        }
        if (t->columnas[i].nombre == valor_columna_referencia) {
            index_columna_referencia = i;
        }
    }

    if (index_columna == -1 || index_columna_referencia == -1) {
        cerr << "Error: No se encontró una de las columnas" << endl;
        return;
    }

    string archivo_tabla = tabla + ".txt";
    ifstream archivo(archivo_tabla);
    if (!archivo.is_open()) {
        cerr << "Error al abrir el archivo de la tabla: " << archivo_tabla << endl;
        return;
    }

    vector<vector<string>> registros;
    string registro;

    while (getline(archivo, registro)) {
        stringstream ss(registro);
        vector<string> valores_registro;
        string valor;
        while (getline(ss, valor, '#')) {
            valores_registro.push_back(valor);
        }
        registros.push_back(valores_registro);
    }
    archivo.close();

    ofstream archivo_salida(archivo_tabla);
    if (!archivo_salida.is_open()) {
        cerr << "Error al abrir el archivo de la tabla para escritura: " << archivo_tabla << endl;
        return;
    }

    for (auto& valores : registros) {
        if (valores[index_columna_referencia] == valor_where_equal) {
            valores[index_columna] = valor_nuevo;
        }
        for (size_t i = 0; i < valores.size(); ++i) {
            archivo_salida << valores[i];
            if (i < valores.size() - 1) {
                archivo_salida << "#";
            }
        }
        archivo_salida << endl;
    }

    archivo_salida.close();
    cout << "Registro(s) actualizado(s) correctamente en la tabla " << tabla << "." << endl;
}

};
