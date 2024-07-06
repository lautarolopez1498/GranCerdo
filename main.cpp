#include <iostream>
#include <time.h>
#include <unistd.h>
using namespace std;

#include "funciones.h";

int main()
{
    int opcion = 1;
    string jugadorMayorPDV;
    int mayorCantiadPDV = 0;

    bool seJugo = false;
    bool salirDelJuego = false;

    // Menu
    while(!salirDelJuego){
        system("cls");

        mostrarMenu();

        cout << "Ingrese una opcion: ";
        cin >> opcion;
        cout << endl;

        switch(opcion){
        case 1:
            system("cls");
            jugar(&seJugo, &jugadorMayorPDV, &mayorCantiadPDV);
            break;
        case 2:
            if(seJugo){
                system("cls");
                cout << "JUGADOR CON MAYOR PUNTAJE EN GRAN CERDO" << endl << endl;
                cout << jugadorMayorPDV << " CON " << mayorCantiadPDV << " PDV" << endl << endl;
            }
            else{
                system("cls");
                cout << "Estadisticas no disponible, seleccionar la opcion JUGAR" << endl << endl;
            }
            break;
        case 3:
            system("cls");
            creditos();
            break;
        case 0: {
            system("cls");
            bool respuesta = salir();

            if(respuesta == true) {
                salirDelJuego = true;
                system("cls");
            }
        }
            break;
        default:
            cout << "No ingreso una opcion valida" << endl;
            break;
        }

        system("pause");

    }
    cout << endl << "GRACIAS POR JUGAR!" << endl;
    cout << "Tech Games" << endl << endl;
    return 0;
}
