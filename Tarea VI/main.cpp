//
// Created by geo71 on 28/03/2026.
//

#include "main.h"

#include <iostream>
using namespace std;

// ===== ESTRUCTURA DEL NODO =====
struct Nodo {
    string accion;
    Nodo* siguiente;
};

// ===== FUNCION PUSH =====
void push(Nodo*& pila, string accion) {
    Nodo* nuevo = new Nodo();
    nuevo->accion = accion;
    nuevo->siguiente = pila;
    pila = nuevo;
}

// ===== FUNCION POP =====
string pop(Nodo*& pila) {
    if (pila == NULL) {
        return "";
    }

    Nodo* temp = pila;
    string accion = temp->accion;
    pila = pila->siguiente;

    delete temp;
    return accion;
}

// ===== FUNCION MOSTRAR =====
void mostrar(Nodo* pila) {
    if (pila == NULL) {
        cout << "Pila vacia.\n";
        return;
    }

    Nodo* actual = pila;
    while (actual != NULL) {
        cout << "- " << actual->accion << endl;
        actual = actual->siguiente;
    }
}

// ===== FUNCION LIMPIAR =====
void limpiar(Nodo*& pila) {
    while (pila != NULL) {
        pop(pila);
    }
}

int main() {
    Nodo* pilaAcciones = NULL;
    Nodo* pilaRehacer = NULL;

    int opcion;
    string accion;

    do {
        cout << "\n------------- SIMULADOR UNDO / REDO --------------------\n";
        cout << "Nombre: Elder Geovani Samayoa Esquivel \n";
        cout << "1. Realizar accion\n";
        cout << "2. Deshacer (UNDO)\n";
        cout << "3. Rehacer (REDO)\n";
        cout << "4. Mostrar acciones actuales\n";
        cout << "5. Mostrar pila de rehacer\n";
        cout << "6. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        cin.ignore();

        switch(opcion) {

            case 1:
                cout << "Ingrese la accion: ";
                getline(cin, accion);

                push(pilaAcciones, accion);
                limpiar(pilaRehacer); // limpiar redo

                cout << "Accion realizada.\n";
                break;

            case 2:
                if (pilaAcciones == NULL) {
                    cout << "No hay acciones para deshacer.\n";
                } else {
                    accion = pop(pilaAcciones);
                    push(pilaRehacer, accion);

                    cout << "Accion deshecha: " << accion << endl;
                }
                break;

            case 3:
                if (pilaRehacer == NULL) {
                    cout << "No hay acciones para rehacer.\n";
                } else {
                    accion = pop(pilaRehacer);
                    push(pilaAcciones, accion);

                    cout << "Accion rehecha: " << accion << endl;
                }
                break;

            case 4:
                cout << "\n--- Acciones actuales ---\n";
                mostrar(pilaAcciones);
                break;

            case 5:
                cout << "\n--- Pila de rehacer ---\n";
                mostrar(pilaRehacer);
                break;

            case 6:
                cout << "Saliendo del programa...\n";
                break;

            default:
                cout << "Opcion invalida.\n";
        }

    } while(opcion != 6);

    // Liberar memoria
    limpiar(pilaAcciones);
    limpiar(pilaRehacer);

    return 0;
}