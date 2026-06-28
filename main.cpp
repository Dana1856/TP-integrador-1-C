#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// --- Configuración y Constantes ---
const int MAX_INVITADOS = 100; // Capacidad máxima del array global
const string ARCHIVO_DATOS = "invitados_studio54.txt";

// --- Estructura del Invitado ---
struct Invitado {
    int nroTicket;
    string nombre;
    int edad;
    bool confirmado;
};

// --- Variables Globales ---
Invitado listaInvitados[MAX_INVITADOS];
int contadorInvitados = 0;

// --- Prototipos de Funciones ---
void clearConsole();
void pauseConsole();
void cargarDesdeArchivo();
void guardarEnArchivo();
void agregarInvitado();
void borrarInvitado();
void modificarInvitado();
void listarAsistentes();
void gestionarAsistencia();
int buscarPorTicket(int ticket);

// --- Función Principal ---
int main() {
    // Cargar datos persistidos al arrancar
    cargarDesdeArchivo();
    
    int opcion;
    do {
        clearConsole();
        cout << "=========================================\n";
        cout << "   STUDIO 54 - ANNIVERSARY PARTY SYSTEM  \n";
        cout << "=========================================\n";
        cout << "1. Agregar Invitado\n";
        cout << "2. Borrar Invitado\n";
        cout << "3. Modificar Datos Personales\n";
        cout << "4. Listar Asistentes por Pantalla\n";
        cout << "5. Confirmar / Cancelar Asistencia\n";
        cout << "6. Salir del Sistema\n";
        cout << "=========================================\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        // Validar entrada del menú
        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000,'\n');
            opcion = 0;
        }

        clearConsole();
        switch (opcion) {
            case 1: agregarInvitado();
                break;
            case 2: borrarInvitado();
             break;
            case 3: modificarInvitado();
                break;
            case 4: listarAsistentes();
                break;
            case 5: gestionarAsistencia();
                break;
            case 6: 
                guardarEnArchivo();
                cout << "Datos guardados. Saliendo del sistema de Studio 54...\n"; 
                break;
            default: 
                cout << "Opcion no valida. Intente nuevamente.\n"; 
                pauseConsole();
                break;
        }
    } while (opcion != 6);
    
    return 0;
}

// --- Implementación de Funciones de Consola ---
void clearConsole() {
    #ifdef __unix__
        system("clear");
    #elif __APPLE__
        system("clear");
    #elif defined(_WIN32) || defined(WIN32) || defined(WIN64)
        system("cls");
    #endif
}

void pauseConsole() {
    #ifdef __unix__
        system("pause");
    #elif __APPLE__
        system("pause");
    #elif defined(_WIN32) || defined(WIN32) || defined(WIN64)
        system("pause");
    #else
        cout << "\nPresione Enter para continuar...";
        cin.ignore(10000, '\n');
        cin.get();
    #endif
}

// --- Funciones de Búsqueda y Auxiliares ---
int buscarPorTicket(int ticket) {
    for (int i = 0; i < contadorInvitados; i++) {
        if (listaInvitados[i].nroTicket == ticket) {
            return i; // Retorna el índice si lo encuentra
        }
    }
    return -1; // Retorna -1 si no existe
}

void eliminarPorIndice(int indice) {
    for (int i = indice; i < contadorInvitados - 1; i++) {
        listaInvitados[i] = listaInvitados[i + 1];
    }
    contadorInvitados--;
}

// --- Operaciones CRUD (Gestión de Invitados) ---
void agregarInvitado() {
    if (contadorInvitados >= MAX_INVITADOS) {
        cout << "Error: Lista de invitados llena. Capacidad maxima alcanzada.\n";
        pauseConsole();
        return;
    }

    int ticket;
    cout << "--- AGREGAR INVITADO ---\n";
    cout << "Ingrese Nro de Ticket: ";
    cin >> ticket;

    if (buscarPorTicket(ticket) != -1) {
        cout << "Error: El numero de ticket ya esta registrado.\n";
        pauseConsole();
        return;
    }

    listaInvitados[contadorInvitados].nroTicket = ticket;
    cin.ignore(); // Limpiar el buffer del salto de línea anterior

    cout << "Nombre Completo: ";
    getline(cin, listaInvitados[contadorInvitados].nombre);

    cout << "Edad: ";
    cin >> listaInvitados[contadorInvitados].edad;
    
    listaInvitados[contadorInvitados].confirmado = false; // Por defecto no confirmado

    contadorInvitados++;
    cout << "\nInvitado agregado exitosamente a la lista.\n";
    pauseConsole();
}

void borrarInvitado() {
    cout << "--- BORRAR INVITADO ---\n";
    int ticket;
    cout << "Ingrese el Nro de Ticket a eliminar: ";
    cin >> ticket;

    int indice = buscarPorTicket(ticket);
    if (indice == -1) {
        cout << "Invitado no encontrado.\n";
        pauseConsole();
        return;
    }

    // Desplazar los elementos hacia la izquierda para cubrir la vacante
    for (int i = indice; i < contadorInvitados - 1; i++) {
        listaInvitados[i] = listaInvitados[i + 1];
    }
    contadorInvitados--;

    cout << "Invitado eliminado correctamente.\n";
    pauseConsole();
}

void modificarInvitado() {
    cout << "--- MODIFICAR DATOS PERSONALES ---\n";
    int ticket;
    cout << "Ingrese el Nro de Ticket a modificar: ";
    cin >> ticket;

    int indice = buscarPorTicket(ticket);
    if (indice == -1) {
        cout << "Invitado no encontrado.\n";
        pauseConsole();
        return;
    }

    cin.ignore();
    cout << "Nuevo Nombre (Actual: " << listaInvitados[indice].nombre << "): ";
    getline(cin, listaInvitados[indice].nombre);

    cout << "Nueva Edad (Actual: " << listaInvitados[indice].edad << "): ";
    cin >> listaInvitados[indice].edad;

    cout << "Datos actualizados correctamente.\n";
    pauseConsole();
}

// --- Consultas y Confirmaciones ---
void listarAsistentes() {
    cout << "===================================================================\n";
    cout << "                      LISTA DE ASISTENTES                          \n";
    cout << "===================================================================\n";
    cout << "Ticket\t\tNombre\t\t\tEdad\tEstado\n";
    cout << "-------------------------------------------------------------------\n";

    if (contadorInvitados == 0) {
        cout << "\t\tLa lista esta vacia.\n";
    } else {
        for (int i = 0; i < contadorInvitados; i++) {
            cout << listaInvitados[i].nroTicket << "\t\t"
                 << listaInvitados[i].nombre << "\t\t"
                 << listaInvitados[i].edad << "\t"
                 << (listaInvitados[i].confirmado ? "CONFIRMADO" : "PENDIENTE") << "\n";
        }
    }
    cout << "===================================================================\n";
    pauseConsole();
}

void gestionarAsistencia() {
    cout << "--- CONFIRMAR / CANCELAR ASISTENCIA ---\n";
    int ticket;
    cout << "Ingrese el Nro de Ticket: ";
    cin >> ticket;

    int indice = buscarPorTicket(ticket);
    if (indice == -1) {
        cout << "Invitado no encontrado.\n";
        pauseConsole();
        return;
    }

    cout << "Invitado: " << listaInvitados[indice].nombre << "\n";
    cout << "Estado actual: " << (listaInvitados[indice].confirmado ? "CONFIRMADO" : "PENDIENTE") << "\n\n";
    
    cout << "1. Confirmar Asistencia\n";
    cout << "2. Cancelar Invitacion (Eliminara al invitado de la lista)\n";
    cout << "Seleccione una opcion: ";
    int op;
    cin >> op;

    if (op == 1) {
        listaInvitados[indice].confirmado = true;
        cout << "Asistencia Confirmada exitosamente.\n";
    } else if (op == 2) {
        // Al seleccionar cancelar, se remueve inmediatamente del array global
        eliminarPorIndice(indice);
        cout << "Invitacion cancelada. El invitado ha sido eliminado del sistema.\n";
    } else {
        cout << "Opcion invalida. No se realizaron cambios.\n";
    }
    pauseConsole();
}

// --- Persistencia en Archivos TXT ---
void guardarEnArchivo() {
    ofstream archivo(ARCHIVO_DATOS, ios::out);
    if (!archivo) {
        cout << "Error al abrir el archivo para guardar datos.\n";
        return;
    }

    for (int i = 0; i < contadorInvitados; i++) {
        archivo << listaInvitados[i].nroTicket << "\n"
                << listaInvitados[i].nombre << "\n"
                << listaInvitados[i].edad << "\n"
                << listaInvitados[i].confirmado << "\n";
    }
    archivo.close();
}

void cargarDesdeArchivo() {
    ifstream archivo(ARCHIVO_DATOS, ios::in);
    if (!archivo) {
        // Si el archivo no existe, no hace nada (primera ejecución)
        return;
    }

    contadorInvitados = 0;
    while (archivo >> listaInvitados[contadorInvitados].nroTicket && contadorInvitados < MAX_INVITADOS) {
        archivo.ignore(); // Limpiar el salto de línea tras el número de ticket
        getline(archivo, listaInvitados[contadorInvitados].nombre);
        archivo >> listaInvitados[contadorInvitados].edad;
        archivo >> listaInvitados[contadorInvitados].confirmado;
        contadorInvitados++;
    }
    archivo.close();
}