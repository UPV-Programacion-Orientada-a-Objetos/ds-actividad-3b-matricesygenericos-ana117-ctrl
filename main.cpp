#include "MatrizDinamica.h"

int main() {
    cout << "Sistema de Análisis de Transformaciones lineales" << endl;

    try {
        // matriz de enteros
        cout << ">> Prueba de Matriz ENTERA (Tipo INT) <<" << endl;
        cout << "Creando Matriz A (Tipo INT) de 2x3..." << endl;

        MatrizDinamica<int> A(2, 3);

        cout << "\nIngresar valores para A (2x3):" << endl;
        A.asignarValor(0, 0, 1);
        A.asignarValor(0, 1, 2);
        A.asignarValor(0, 2, 3);
        A.asignarValor(1, 0, 4);
        A.asignarValor(1, 1, 5);
        A.asignarValor(1, 2, 6);

        cout << "Matriz A original (2x3):" << endl;
        A.imprimir();

        // redimensionar matriz
        cout << "\n>> Redimensionando Matriz A <<" << endl;
        cout << "Redimensionando A a 3x3. Datos conservados:" << endl;
        A.redimensionar(3, 3);
        A.imprimir();

        // matriz flotante
        cout << "\n>> Prueba de Multiplicación (Tipo FLOAT) <<" << endl;
        cout << "Creando Matriz B (Tipo FLOAT) de 3x2..." << endl;

        MatrizDinamica<float> B(3, 2);

        cout << "\nIngresar valores para B (3x2):" << endl;
        B.asignarValor(0, 0, 1.5f);
        B.asignarValor(0, 1, 0.5f);
        B.asignarValor(1, 0, 2.0f);
        B.asignarValor(1, 1, 1.0f);
        B.asignarValor(2, 0, 1.0f);
        B.asignarValor(2, 1, 2.5f);

        cout << "Matriz B (3x2):" << endl;
        B.imprimir();

        // Multiplicación
        cout << "\n>> Multiplicación: C = A(3x3) x B(3x2) <<" << endl;
        
        // Convertir A (int) a A_float (float) para multiplicar
        MatrizDinamica<float> A_float(A.obtenerFilas(), A.obtenerColumnas());
        for (int i = 0; i < A.obtenerFilas(); i++) {
            for (int j = 0; j < A.obtenerColumnas(); j++) {
                A_float.asignarValor(i, j, (float)A.obtenerValor(i, j));
            }
        }
        
        MatrizDinamica<float> C = MatrizDinamica<float>::multiplicar(A_float, B);
        
        cout << "Matriz C (Resultado 3x2, Tipo FLOAT):" << endl;
        C.imprimir();

        // matriz adicional para demostrar generacidad 
        cout << "\n>> Prueba Adicional: Multiplicación INT <<" << endl;
        
        MatrizDinamica<int> D(2, 3);
        D.asignarValor(0, 0, 1);
        D.asignarValor(0, 1, 2);
        D.asignarValor(0, 2, 3);
        D.asignarValor(1, 0, 2);
        D.asignarValor(1, 1, 3);
        D.asignarValor(1, 2, 4);

        MatrizDinamica<int> E(3, 2);
        E.asignarValor(0, 0, 5);
        E.asignarValor(0, 1, 1);
        E.asignarValor(1, 0, 2);
        E.asignarValor(1, 1, 3);
        E.asignarValor(2, 0, 1);
        E.asignarValor(2, 1, 2);

        cout << "Matriz D (2x3):" << endl;
        D.imprimir();

        cout << "Matriz E (3x2):" << endl;
        E.imprimir();

        MatrizDinamica<int> F = MatrizDinamica<int>::multiplicar(D, E);

        cout << "Matriz F = D x E (Resultado 2x2, Tipo INT):" << endl;
        F.imprimir();

        cout << "\n>> Liberando memoria de todas las matrices... <<" << endl;

    }
    catch (invalid_argument& e) {
        cout << "Error de argumento: " << e.what() << endl;
        return 1;
    }
    catch (out_of_range& e) {
        cout << "Error: " << e.what() << endl;
        return 1;
    }
    catch (bad_alloc& e) {
        cout << "Error de memoria: " << e.what() << endl;
        return 1;
    }
    catch (exception& e) {
        cout << "Error inesperado: " << e.what() << endl;
        return 1;
    }

    cout << "Programa finalizado correctamente." << endl;
    return 0;
}