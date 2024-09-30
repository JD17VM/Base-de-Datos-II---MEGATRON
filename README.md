# Implementación de MEGATRON


## Índice

1. [Ejecución del proyecto](#ejecución-del-proyecto)
2. [Actividades del grupo](#actividades-del-grupo)
3. [Laboratorio 3](#laboratorio-3)
   - [1. Seleccionar tablas por *](#1-seleccionar-tablas-por-)
   - [2. Seleccionar tablas por columnas](#2-seleccionar-tablas-por-columnas)
   - [3. Seleccionar con WHERE](#3-seleccionar-con-where)
   - [4. JOIN de las tablas](#4-join-de-las-tablas)
   - [5. Selección de Unión de tablas](#5-selección-de-unión-de-tablas)
   - [6. Actualización de valores](#6-actualización-de-valores)

## Ejecución del proyecto

Para compilar el archivo `main.cpp`, utilizamos el compilador `g++`. Este comando generará un archivo ejecutable a partir del código fuente en C++:

```bash
g++ main.cpp
```
## Actividades del grupo
En esta sección se presenta el repositorio de GitHub con el historial de commits realizados por los desarrolladores del proyecto. Aquí podrás observar las contribuciones de cada miembro del equipo, incluyendo nuevas funcionalidades, correcciones y mejoras en el código. 

<p align="center">
    <img src="/Evidencias/Activities.jpeg" alt="Historial de commits en GitHub" width="600">
</p>

## Laboratorio 3

### 1. Seleccionar tablas por *

- Seleccionamos la tabla actor y mostramos todos los registros con *
<p align="center">
    <img src="/Evidencias/select_all_actor.jpg">
</p>

- Seleccionamos la tabla customer y mostramos todos los registros con *
<p align="center">
    <img src="/Evidencias/select_all_customer.jpg">
</p>

### 2. Seleccionar tablas por columnas

- Seleccionamos la tabla actor y mostramos las columnas "actor_id" y "first_name"
<p align="center">
    <img src="/Evidencias/select_columnas_actor.jpg">
</p>

- Seleccionamos la tabla film y mostramos las columnas "title" y "description"
<p align="center">
    <img src="/Evidencias/select_columnas_film.jpg">
</p>

### 3. Seleccionar con WHERE

- Seleccionamos la tabla address y mostramos el registro que tenga el valor "900 Santiago de Compostela Parkway"
<p align="center">
    <img src="/Evidencias/select_valor_address.jpg">
</p>

- Seleccionamos la tabla film_actor y mostramos los registros que tengan el valor "111"
<p align="center">
    <img src="/Evidencias/select_valor_film_actor.jpg">
</p>

### 4. JOIN de las tablas

- Hacemos uso de la función **inner join** para unir las tablas **actor** y **customer**
<p align="center">
    <img src="/Evidencias/join.png">
</p>

### 5. Selección de Unión de tablas

- Seleccionamos la tabla film_actor y mostramos todos los valores de esta tabla.
<p align="center">
    <img src="/Evidencias/joins_tables.png">
</p>

### 6. Actualización de valores

- Seleccionamos la opción de **UPDATE** en la tabla **actor** y actualizamos la columna **first_name**. El nombre de referencia es **Penelope** y lo actualizamos con el valor de **Luis**.
<p align="center">
    <img src="/Evidencias/update_values.png">
</p>
