#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

void limpiarArchivo()
{
    ofstream archivo("resultado.txt", ios::trunc);
    if (!archivo.is_open())
    {
        cerr << "Error: No se pudo abrir el archivo resultado.txt para limpiar." << endl;
    }
    archivo.close();
}

class Columna
{
public:
    void guardarEnArchivo(const string &texto, bool newline = true) const
    {
        ofstream archivo("resultado.txt", ios::app);
        if (archivo.is_open())
        {
            archivo << texto;
            if (newline)
                archivo << endl;
        }
        else
        {
            cerr << "Error: No se pudo abrir el archivo resultado.txt." << endl;
        }

        cout << texto;
        if (newline)
            cout << endl;
    }

    string nombre;
    string tipo_dato;

    Columna(const string &nombre_columna, const string &tipo_dato_columna)
        : nombre(nombre_columna), tipo_dato(tipo_dato_columna) {}
};

class Tabla
{
public:
    void guardarEnArchivo(const string &texto, bool newline = true) const
    {
        ofstream archivo("resultado.txt", ios::app);
        if (archivo.is_open())
        {
            archivo << texto;
            if (newline)
                archivo << endl;
        }
        else
        {
            cerr << "Error: No se pudo abrir el archivo resultado.txt." << endl;
        }

        cout << texto;
        if (newline)
            cout << endl;
    }

    string nombre_tabla;
    vector<Columna> columnas;

    Tabla(const string &nombre) : nombre_tabla(nombre) {}

    void agregarColumna(const Columna &columna)
    {
        columnas.push_back(columna);
    }

    void mostrarEstructura() const
    {
        guardarEnArchivo("Tabla: " + nombre_tabla);
        for (const auto &columna : columnas)
        {
            guardarEnArchivo("  Columna: " + columna.nombre + ", Tipo de dato: " + columna.tipo_dato);
        }
    }

    void mostrarRegistro(const string &registro) const
    {
        stringstream ss(registro);
        string valor;
        size_t i = 0;

        while (getline(ss, valor, '#'))
        {
            if (i < columnas.size())
            {
                guardarEnArchivo(valor + "\t", false);
            }
            i++;
        }
        guardarEnArchivo("");
    }

    void mostrarRegistroSeleccionado(const string &registro, const vector<int> &indices_columnas) const
    {
        stringstream ss(registro);
        string valor;
        vector<string> valores_registro;

        while (getline(ss, valor, '#'))
        {
            valores_registro.push_back(valor);
        }

        for (int indice : indices_columnas)
        {
            if (indice < valores_registro.size())
            {
                guardarEnArchivo(valores_registro[indice] + "\t", false);
            }
        }
        guardarEnArchivo("");
    }

    bool mostrarRegistroSiCoincide(const string &registro, int indice_columna, const string &valor_busqueda) const
    {
        stringstream ss(registro);
        string valor;
        vector<string> valores_registro;

        while (getline(ss, valor, '#'))
        {
            valores_registro.push_back(valor);
        }

        if (indice_columna < valores_registro.size() && valores_registro[indice_columna] == valor_busqueda)
        {
            mostrarRegistro(registro);
            return true;
        }
        return false;
    }
};
