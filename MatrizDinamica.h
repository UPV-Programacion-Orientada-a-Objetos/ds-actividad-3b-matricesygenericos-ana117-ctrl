#ifndef MATRIZ_DINAMICA_H
#define MATRIZ_DINAMICA_H

#include <iostream>

using namespace std;

template <typename T>
class MatrizDinamica {
private:
    T **datos;        // Puntero doble para matriz 2D
    int filas;        // Número de filas
    int columnas;     // Número de columnas

public:
    //Constructor
    MatrizDinamica(int f, int c) : filas(f), columnas(c) {
        try {
            //Asignar memoria para las filas (vector de punteros)
            datos = new T*[filas];
            
            //Para cada fila, asignar memoria para las columnas
            for (int i = 0; i < filas; i++) {
                datos[i] = new T[columnas];
            }
            
            //Inicializar todos los valores a cero
            for (int i = 0; i < filas; i++) {
                for (int j = 0; j < columnas; j++) {
                    datos[i][j] = T(0);  // Conversión a tipo T
                }
            }
        }
        catch (...) {
            cout << "Error: No hay suficiente memoria disponible." << endl;
            throw;
        }
    }

    //Destructor
    ~MatrizDinamica() {
        //Liberar cada fila (cada vector de columnas)
        for (int i = 0; i < filas; i++) {
            delete[] datos[i]; 
        }
        
        //Liberar el vector de punteros (las filas)
        delete[] datos;
        
        //Establecer puntero a nullptr 
        datos = nullptr;
        
        cout << "Matriz de " << filas << "x" << columnas 
             << " liberada correctamente." << endl;
    }

    //Constructor de copia
    MatrizDinamica(const MatrizDinamica<T>& otra) : filas(otra.filas), columnas(otra.columnas) {
        try {
            //Asignar memoria para las filas
            datos = new T*[filas];
            
            //Para cada fila, asignar memoria para las columnas
            for (int i = 0; i < filas; i++) {
                datos[i] = new T[columnas];
            }
            
            //Copiar todos los datos de la otra matriz
            for (int i = 0; i < filas; i++) {
                for (int j = 0; j < columnas; j++) {
                    datos[i][j] = otra.datos[i][j];
                }
            }
        }
        catch (...) {
            cout << "Error: No hay suficiente memoria para copiar la matriz." << endl;
            throw;
        }
    }

    //Operador de asignación
    MatrizDinamica<T>& operator=(const MatrizDinamica<T>& otra) {
        // Evitar auto-asignación
        if (this == &otra) {
            return *this;
        }

        //Liberar la memoria actual
        for (int i = 0; i < filas; i++) {
            delete[] datos[i];
        }
        delete[] datos;

        //Copiar las dimensiones
        filas = otra.filas;
        columnas = otra.columnas;

        try {
            //Asignar nueva memoria
            datos = new T*[filas];
            
            for (int i = 0; i < filas; i++) {
                datos[i] = new T[columnas];
            }
            
            //Copiar todos los datos
            for (int i = 0; i < filas; i++) {
                for (int j = 0; j < columnas; j++) {
                    datos[i][j] = otra.datos[i][j];
                }
            }
        }
        catch (...) {
            cout << "Error: No hay suficiente memoria en la asignación." << endl;
            throw;
        }

        return *this;
    }
    
    // Obtener el valor en una posición específica
    T obtenerValor(int fila, int columna) const {
        if (fila < 0 || fila >= filas || columna < 0 || columna >= columnas) {
            cout << "Error: Índice fuera de rango" << endl;
            return T(0);
        }
        return datos[fila][columna];
    }

    // Asignar un valor en una posición específica
    void asignarValor(int fila, int columna, T valor) {
        if (fila < 0 || fila >= filas || columna < 0 || columna >= columnas) {
            cout << "Error: Índice fuera de rango" << endl;
            return;
        }
        datos[fila][columna] = valor;
    }

    // Obtener número de filas
    int obtenerFilas() const {
        return filas;
    }

    // Obtener número de columnas
    int obtenerColumnas() const {
        return columnas;
    }

    //Metodo para imprimir
    void imprimir() const {
        cout << "\nMatriz (" << filas << "x" << columnas << "):" << endl;
        for (int i = 0; i < filas; i++) {
            cout << "| ";
            for (int j = 0; j < columnas; j++) {
                cout << datos[i][j] << " | ";
            }
            cout << endl;
        }
        cout << endl;
    }

    //Meotodo para redimensionar
    void redimensionar(int nuevaF, int nuevaC) {
        if (nuevaF <= 0 || nuevaC <= 0) {
            cout << "Error: Las dimensiones deben ser positivas" << endl;
            return;
        }

        try {
            //Crear la nueva matriz temporal
            T **nuevaDatos = new T*[nuevaF];
            for (int i = 0; i < nuevaF; i++) {
                nuevaDatos[i] = new T[nuevaC];
            }

            // Inicializar todos los valores a cero
            for (int i = 0; i < nuevaF; i++) {
                for (int j = 0; j < nuevaC; j++) {
                    nuevaDatos[i][j] = T(0);
                }
            }

            // Copiar datos de la matriz antigua a la nueva
            int filasACopiar = (filas < nuevaF) ? filas : nuevaF;
            int columnasACopiar = (columnas < nuevaC) ? columnas : nuevaC;

            for (int i = 0; i < filasACopiar; i++) {
                for (int j = 0; j < columnasACopiar; j++) {
                    nuevaDatos[i][j] = datos[i][j];
                }
            }

            //Liberar la matriz antigua
            for (int i = 0; i < filas; i++) {
                delete[] datos[i];
            }
            delete[] datos;

            //Asignar la nueva matriz como la actual
            datos = nuevaDatos;
            filas = nuevaF;
            columnas = nuevaC;

            cout << "Matriz redimensionada a " << nuevaF << "x" << nuevaC 
                 << " correctamente." << endl;
        }
        catch (...) {
            cout << "Error: No hay suficiente memoria para redimensionar." << endl;
            throw;
        }
    }

    //Metodo de multiplicación
    static MatrizDinamica<T> multiplicar(const MatrizDinamica<T>& A, 
                                         const MatrizDinamica<T>& B) {
        //Validar que las dimensiones sean compatibles
        if (A.columnas != B.filas) {
            cout << "Error: El número de columnas de A debe ser igual "
                 << "al número de filas de B para multiplicar." << endl;
            return MatrizDinamica<T>(0, 0);
        }

        //Crear la matriz resultado C
        MatrizDinamica<T> C(A.filas, B.columnas);

        //Implementar la fórmula de multiplicación
        for (int i = 0; i < A.filas; i++) {
            for (int j = 0; j < B.columnas; j++) {
                T suma = T(0);  // Inicializar acumulador
                
                for (int k = 0; k < A.columnas; k++) {
                    suma += A.datos[i][k] * B.datos[k][j];
                }
                
                C.datos[i][j] = suma;
            }
        }

        //Devolver la matriz resultado
        return C;
    }
};

#endif