#include "Tabla.h"

class Schema
{
public:
    vector<Tabla> tablas;

    void leerArchivo(const string &nombre_archivo)
    {
        ifstream archivo(nombre_archivo);
        if (!archivo.is_open())
        {
            cerr << "Error al abrir el archivo: " << nombre_archivo << endl;
            return;
        }

        string linea;
        while (getline(archivo, linea))
        {
            procesarLinea(linea);
        }

        archivo.close();
    }

    void procesarLinea(const string &linea)
    {
        stringstream ss(linea);
        string parte;
        vector<string> partes;

        while (getline(ss, parte, '#'))
        {
            partes.push_back(parte);
        }

        if (partes.size() >= 3)
        {
            Tabla tabla(partes[0]); 

            for (size_t i = 1; i < partes.size(); i += 2)
            {
                string nombre_columna = partes[i];
                string tipo_dato_columna = (i + 1 < partes.size()) ? partes[i + 1] : "desconocido";
                tabla.agregarColumna(Columna(nombre_columna, tipo_dato_columna));
            }

            tablas.push_back(tabla);
        }
    }

    Tabla *buscarTabla(const string &nombre_tabla)
    {
        for (auto &tabla : tablas)
        {
            if (tabla.nombre_tabla == nombre_tabla)
            {
                return &tabla;
            }
        }
        return nullptr;
    }

    void mostrarEstructura() const
    {
        for (const auto &tabla : tablas)
        {
            tabla.mostrarEstructura();
            cout << endl;
        }
    }
};