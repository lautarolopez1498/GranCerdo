#include "funciones.h"

void jugar(bool *p_seJugo, string *p_nombreJugador, int *p_cantidadPDV){
    srand(time(NULL));
    *p_seJugo = true;
    int puntosGeneralJugador1 = 0;
    int puntosGeneralJugador2 = 0;
    const int TAM = 3;
    int dados[TAM] = {};
    bool hundirseBarro = false;
    bool tresDados = false;

    int hitosJugador_1[3] = {}; // acumula los puntos de cada hito
    int hitosJugador_2[3] = {};

    string nombreJugador1;
    string nombreJugador2;

    cout << "Ingrese el nombre del Jugador 1: ";
    cin.ignore();
    getline(cin, nombreJugador1);
    cout << endl;
    cout << "Ingrese el nombre del Jugador 2: ";
    getline(cin, nombreJugador2);

    system("cls");

    // Inicio del juego
     bool inicioPartida = determinarInicio(nombreJugador1, nombreJugador2);
     system("pause");
     system("cls");
     if(inicioPartida == true) {
        // Rondas
        for(int i = 0; i < 5; i++){
            int numeroRonda = i + 1;
            // Turno jugador 1
            jugarRonda(&puntosGeneralJugador1, &puntosGeneralJugador2, dados, nombreJugador1, nombreJugador2, numeroRonda, &hundirseBarro, &tresDados, hitosJugador_1);

            // Turno jugador 2
            jugarRonda(&puntosGeneralJugador2, &puntosGeneralJugador1, dados, nombreJugador2, nombreJugador1, numeroRonda, &hundirseBarro, &tresDados, hitosJugador_2);
        }
    } else{
        // Rondas
        for(int i = 0; i < 5; i++){
            int numeroRonda = i + 1;
            // Turno jugador 2
            jugarRonda(&puntosGeneralJugador2, &puntosGeneralJugador1, dados, nombreJugador2, nombreJugador1, numeroRonda, &hundirseBarro, &tresDados, hitosJugador_2);

            // Turno jugador 1
            jugarRonda(&puntosGeneralJugador1, &puntosGeneralJugador2, dados, nombreJugador1, nombreJugador2, numeroRonda, &hundirseBarro, &tresDados, hitosJugador_1);
        }
    }


    hitosJugador_1[0] = puntosGeneralJugador1;
    hitosJugador_2[0] = puntosGeneralJugador2;

    datosFinRondas(nombreJugador1, hitosJugador_1, nombreJugador2, hitosJugador_2, p_nombreJugador, p_cantidadPDV);
}

bool determinarInicio(string nombreJ1, string nombreJ2) {

    bool inicioJugador1 = true;

    //Jugador 1
    int vectorDadosJ1[2] = {};
    lanzarDados(vectorDadosJ1, 2);

    int suma_jugador1 = sumarVector(vectorDadosJ1, 2);
    int dadoMayor_jugador1;

    // Guardo el dado de mayor valor
    if(vectorDadosJ1[0] > vectorDadosJ1[1]){
        dadoMayor_jugador1 = vectorDadosJ1[0];
    } else {
        dadoMayor_jugador1 = vectorDadosJ1[1];
    }

    cout << "LANZA " << nombreJ1 << endl;
    cout << "----------------------------------------------" << endl;
    mostrarVector(vectorDadosJ1, 2);
    cout << "SUMA DE LOS DADOS: " << suma_jugador1 << endl;
    cout << "DADO MAYOR VALOR: " << dadoMayor_jugador1 << endl;
    cout << "----------------------------------------------" << endl << endl << endl << endl;

    //Jugador 2
    int vectorDadosJ2[2] = {};
    lanzarDados(vectorDadosJ2, 2);

    int suma_jugador2 = sumarVector(vectorDadosJ2, 2);
    int dadoMayor_jugador2;

    // Guardo el dado de mayor valor
    if(vectorDadosJ2[0] > vectorDadosJ2[1]){
        dadoMayor_jugador2 = vectorDadosJ2[0];
    } else {
        dadoMayor_jugador2 = vectorDadosJ2[1];
    }

    cout << "LANZA " << nombreJ2 << endl;
    cout << "----------------------------------------------" << endl;
    mostrarVector(vectorDadosJ2, 2);
    cout << "SUMA DE LOS DADOS: " << suma_jugador2 << endl;
    cout << "DADO MAYOR VALOR: " << dadoMayor_jugador2 << endl;
    cout << "----------------------------------------------" << endl << endl;

    // Decision del turno
    if(suma_jugador1 > suma_jugador2) {
        cout << "Arranca el juego " << nombreJ1 << ", obtuvo la suma mas alta con " << suma_jugador1 << " puntos! " << endl << endl;
        inicioJugador1 = true;
    } else if(suma_jugador2 > suma_jugador1) {
        cout << "Arranca el juego " << nombreJ2 << ", obtuvo la suma mas alta con " << suma_jugador2 << " puntos!" << endl << endl;
        inicioJugador1 = false;
    } else {
        if(dadoMayor_jugador1 > dadoMayor_jugador2) {
            cout << "Arranca el juego " << nombreJ1 << ", obtuvo el dado de mayor valor: " << dadoMayor_jugador1 << endl << endl;
            inicioJugador1 = true;
        } else if (dadoMayor_jugador2 > dadoMayor_jugador1) {
            cout << "Arranca el juego " << nombreJ2 << ", obtuvo el dado de mayor valor: " << dadoMayor_jugador2 << endl << endl;
            inicioJugador1 = false;
        } else {
            cout << "LOS DADOS MAXIMOS DE AMBOS JUGADORES SON IGUALES, LANZAR NUEVAMENTE..." << endl;
            system("pause");
            system("cls");
            cout << "LANZANDO..." << endl;
            sleep(1);
            return determinarInicio(nombreJ1, nombreJ2);
        }
    }

    return inicioJugador1;
}

void jugarRonda(int *p_puntajeJugador, int *p_puntajeOponente, int vec[], string nombreJugador, string nombreOponente, int ronda, bool *p_hundirseBarro, bool *p_tresDados, int hitosJugador[]){

    bool seguirTirando = true;
    int puntajeRonda = 0;
    int puntajeTirada = 0;
    int contador = 0;
    int contadorLanzamientos = 0;
    int posicionFinal = 0;

    if(*p_tresDados == false) {
        posicionFinal = 2;
    } else {
        posicionFinal = 3;
    }

    while(seguirTirando) {

        cout << "GRAN CERDO" << endl << endl;
        cout << "---------------------------------------------------------------------------------------------------------" << endl;
        cout << nombreJugador << ": " << *p_puntajeJugador << " TRUFAS ACUMULADAS                            " << nombreOponente << ": " << *p_puntajeOponente << " TRUFAS ACUMULADAS" << endl <<endl;
        cout << "---------------------------------------------------------------------------------------------------------" << endl << endl << endl;
        mostrarInfoRonda(ronda, puntajeRonda,contadorLanzamientos, nombreJugador);
        contadorLanzamientos++;
        cout << endl <<"LANZAMIENTO #" << contadorLanzamientos << endl;
        lanzarDados(vec, posicionFinal);
        //cargarVector(vec, posicionFinal);
        mostrarVector(vec, posicionFinal);
        int cantidad_As = contarAs(vec, posicionFinal);

        if(cantidad_As == 0) {
            int resultado_1 = condicion_1(vec, posicionFinal);
            if(resultado_1 > 0) {
                puntajeTirada = resultado_1;
                puntajeRonda += puntajeTirada;
                bool consulta = cederTurno();

                if(consulta == true) {
                    seguirTirando = false;
                } else {
                    seguirTirando = true;
                }

            } else {
                int resultado_2 = condicion_2(vec, posicionFinal);

                if(resultado_2 > 0) {
                    puntajeTirada = resultado_2;
                    puntajeRonda += puntajeTirada;
                    hitosJugador[1] += 1;
                    seguirTirando = true;
                }
            }
        }

        if(cantidad_As == 1) {
            int resultado_3 =  condicion_3(vec, posicionFinal);
            puntajeRonda = resultado_3;
            seguirTirando = false;

        }

        if(cantidad_As == 2) {
            int resultado_4 = condicion_4(vec, posicionFinal);
            *p_hundirseBarro = true;
            puntajeRonda = 0;
            *p_puntajeJugador = 0;
            seguirTirando = false;
        }

        if(cantidad_As == 3){
            int resultado_5 = condicion_5(vec, posicionFinal);
            *p_hundirseBarro = true;
            *p_puntajeOponente += puntajeRonda;
            puntajeRonda = 0;
            *p_puntajeOponente += *p_puntajeJugador;
            *p_puntajeJugador = 0;
            seguirTirando = false;

        }

        if(((*p_puntajeJugador + puntajeRonda > 50 && *p_puntajeOponente > 50) || *p_hundirseBarro != false) && posicionFinal == 2) {
            system("pause");
            system("cls");
            cout << " *** APARTIR DE AHORA, SE JUGARA CON 3 DADOS *** " << endl << endl;
            *p_tresDados = true;
            posicionFinal = 3;
        }

        system("pause");
        system("cls");
    }
    *p_puntajeJugador += puntajeRonda;

    if(contadorLanzamientos > hitosJugador[2]){
        hitosJugador[2] = contadorLanzamientos;
    }
}

// Si las caras son distintas entre si y ninguna de ellas es un as:
int condicion_1(int vec[], int tamanio){
    int puntos = 0;

    if(tamanio == 2) {
        if(vec[0] != vec[1]) {
            int resultado = sumarVector(vec, tamanio);
            puntos = resultado;
            cout << "Sumaste " << puntos << " trufas!" << endl << endl;
        }
    }
    if(tamanio == 3){
        if(vec[0] != vec[1] && vec[0] != vec[2] && vec[1] != vec[2]){
            int resultado1 = sumarVector(vec, tamanio);
            puntos = resultado1;
            cout << "Sumaste " << puntos << " trufas!" << endl << endl;
        } else if((vec[0] == vec[1] && vec[0] != vec[2]) || (vec[0] == vec[2] && vec[0] != vec[1]) || (vec[1] == vec[2] && vec[1] != vec[0])) {
            int resultado2 = sumarVector(vec, tamanio);
            puntos = resultado2;
            cout << "Sumaste " << puntos << " trufas!" << endl << endl;
        }
    }
    return puntos;
}

// Si las caras son iguales entre si y no son ases:
int condicion_2(int vec[], int tamanio) {
    int puntos = 0;

    if(tamanio == 2) {
        if(vec[0] == vec[1]) {
            int resultado = sumarVector(vec, tamanio);
            puntos = resultado * 2;
            cout << "OINKKKKKK!!! Sumaste " << puntos << " trufas! Debes continuar lanzando..." << endl << endl;
        }
    }

    if(tamanio == 3) {
        if(vec[0] == vec[1] && vec[1] == vec[2]) {
            int resultado = sumarVector(vec, tamanio);
            puntos += resultado * 2;
            cout << "OINKKKKKK!!! Sumaste " << puntos << " trufas!" << endl << endl;
        }
    }
    return puntos;
}

// Si las caras son distintas entre si y hay un as entre ellas:
int condicion_3(int vec[], int tamanio) {
    int puntos = 0;

    if(tamanio == 2) {
        if(vec[0] != vec[1]){
            puntos = 0;
            cout << "Perdes todas las trufas de la ronda :( " << endl << endl;
        }
    }
    if(tamanio == 3) {
        if(vec[0] != vec[1] && vec[1] != vec[2]){
            puntos = 0;
            // LAS CARAS SON DISTINTAS (HAY 1 AS)
            cout << "Perdes todas las trufas de la ronda :( " << endl << endl;
        } else {
            // DOS CARAS IGUALES Y UN AS
            cout << "Perdes todas las trufas de la ronda :( " << endl;
        }
    }
    return puntos;
}

// Si dos de las caras son iguales entre si y son ases:
int condicion_4(int vec[], int tamanio){
    int puntos = 0;
    if(tamanio == 2) {
        if(vec[0] == vec[1]) {
            // LAS CARAS SON IGUALES (HAY 2 AS)
            cout << "EL CERDO SE HUNDE EN EL BARRO! Pierdes todas las trufas" << endl << endl;
        }
    }
    if(tamanio == 3) {
        if(vec[0] == vec[1] || vec[0] == vec[2] || vec[1] == vec[2]){
            puntos = 0;
            // DOS CARAS SON AS"
            cout << "EL CERDO SE HUNDE EN EL BARRO! Pierdes todas las trufas" << endl << endl;
        }
    }
    return puntos;
}

// Si se esta lanzando con tres dados y tres de las caras son iguales entre si y son ases:
int condicion_5(int vec[], int tamanio) {
    int puntos = 0;
    cout << "SE TIRO CON TRES DADOS Y SON AS" << endl;
    cout << "EL CERDO SE HUNDE EN EL BARRO! Pierdes todas las trufas y se las queda tu oponente" << endl << endl;

    return puntos;
}

int dadoAleatorio(){
    int dado = rand()%6+1;

    return dado;
}

void lanzarDados(int vec[], int tamanio){
    for(int i = 0; i < tamanio; i++) {
        vec[i] = dadoAleatorio();
    }
}

void mostrarVector(int vec[], int tamanio){
    cout << endl << "Dados -> ";
    for(int i = 0; i < tamanio; i++) {
        cout << "  |  " << vec[i] << " | ";
    }
    cout << endl << endl;
}

void mostrarMenu() {
    cout << "GRAN CERDO" << endl;
    cout << "----------------------------------------------" << endl;
    cout << "1 - JUGAR" << endl;
    cout << "2 - ESTADISTICAS" << endl;
    cout << "3 - CREDITOS" << endl;
    cout << "==============================================" << endl;
    cout << "0 - Salir" << endl;
    cout << "----------------------------------------------" << endl;
}

int sumarVector(int vec[], int tamanio) {
    int suma = 0;
    for(int i = 0; i < tamanio; i++) {
        suma += vec[i];
    }
    return suma;
}

int contarAs(int vec[], int tamanio) {
    int contador = 0;

    for(int i = 0; i < tamanio; i++){
        if(vec[i] == 1) {
            contador++;
        }
    }
    return contador;
}

bool cederTurno(){
    char respuesta;

    cout << endl << "Continuar lanzando? (S/N): ";
    cin >> respuesta;
    cout << endl;

    while(respuesta != 'N' && respuesta != 'S'){
        cout << "No ingreso una opcion valida, por favor vuelva a seleccionar." << endl;
        cout << endl << "Continuar lanzando? (S/N): ";
        cin >> respuesta;
        cout << endl;
    }

    if(respuesta == 'S'){
        return false;
    }
    return true;
}

void cargarVector(int vec[], int tamanio){
    int numero = 0;
    for(int i = 0; i < tamanio; i++){
        cout << "Ingrese el resultado del dado " << i + 1 << ": ";
        cin >> numero;
        vec[i] = numero;
    }
}

void mostrarInfoRonda(int numeroRonda, int puntosRonda, int cantLanzamientos, string nombre){
    cout << "TURNO DE " << nombre << endl;
    cout << "----------------------------------------------" << endl;
    cout << "RONDA #" << numeroRonda << endl;
    cout << "PUNTOS DE LA RONDA: " << puntosRonda << endl;
    cout << "LANZAMIENTOS: " << cantLanzamientos << endl;
    cout << "----------------------------------------------" << endl << endl;

}

void datosFinRondas(string nombreJ1, int hitosJ1[], string nombreJ2, int hitosJ2[], string *p_nombreJugador, int *p_cantidadPDV) {
    string nombreGanador;
    int cantidadPDVGanador = 0;

    int masTrufasJ1 = 0;
    int masTrufasJ2 = 0;

    if(hitosJ1[0] > hitosJ2[0]){
        masTrufasJ1 = 5;
    } else if (hitosJ2[0] > hitosJ1[0]){
        masTrufasJ2 = 5;
    } else {
        masTrufasJ1 = 5;
        masTrufasJ2 = 5;
    }

    int cada50TrufasJ1 = hitosJ1[0] / 50;
    int cada50TrufasJ2 = hitosJ2[0] / 50;

    int oinksJ1 = hitosJ1[1] * 2;
    int oinksJ2 = hitosJ2[1] * 2;

    int mayorLanzamientoJ1 = 0;
    int mayorLanzamientoJ2 = 0;

    if(hitosJ1[2] > hitosJ2[2]){
        mayorLanzamientoJ1 = 3;
    } else if (hitosJ2[2] > hitosJ1[2]){
        mayorLanzamientoJ2 = 3;
    } else {
        mayorLanzamientoJ1 = 3;
        mayorLanzamientoJ2 = 3;
    }

    int totalPDV_J1 = masTrufasJ1 + cada50TrufasJ1 + oinksJ1 + mayorLanzamientoJ1;
    int totalPDV_J2 = masTrufasJ2 + cada50TrufasJ2 + oinksJ2 + mayorLanzamientoJ2;

    system("cls");

    cout << "GRAN CERDO" << endl;
    cout << "----------------------------------------------" << endl;
    cout << nombreJ1 << endl;
    cout << "----------------------------------------------" << endl;
    cout << "MAS TRUFAS EN TOTAL: " << masTrufasJ1 << " PDV (" << hitosJ1[0] << " trufas)" << endl;
    cout << "CADA 50 TRUFAS:      " << cada50TrufasJ1 << " PDV (" << cada50TrufasJ1 * 50 << " trufas)" << endl;
    cout << "OINKS:               " << oinksJ1 << " PDV (" << hitosJ1[1] << " oinks)" << endl;
    cout << "CERDO CODICIOSO:     " << mayorLanzamientoJ1 << " PDV (" << hitosJ1[2] << " lanzamientos)" << endl;
    cout << "==============================================" << endl;
    cout << "TOTAL:               " << totalPDV_J1 << " PDV" << endl << endl << endl;

    cout << "----------------------------------------------" << endl;
    cout << nombreJ2 << endl;
    cout << "----------------------------------------------" << endl;
    cout << "MAS TRUFAS EN TOTAL: " << masTrufasJ2 << " PDV (" << hitosJ2[0] << " trufas)" << endl;
    cout << "CADA 50 TRUFAS:      " << cada50TrufasJ2 << " PDV (" << cada50TrufasJ2 * 50 << " trufas)" << endl;
    cout << "OINKS:               " << oinksJ2 << " PDV (" << hitosJ2[1] << " oinks)" << endl;
    cout << "CERDO CODICIOSO:     " << mayorLanzamientoJ2 << " PDV (" << hitosJ2[2] << " lanzamientos)" << endl;
    cout << "==============================================" << endl;
    cout << "TOTAL:               " << totalPDV_J2 << " PDV" << endl << endl << endl;



    if(totalPDV_J1 > totalPDV_J2){
        nombreGanador = nombreJ1;
        cantidadPDVGanador = totalPDV_J1;
        cout <<  "GANADOR: " << nombreJ1 << " CON " << totalPDV_J1 << " PUNTOS DE VICTORIA" << endl;
    } else if (totalPDV_J2 > totalPDV_J1) {
        nombreGanador = nombreJ2;
        cantidadPDVGanador = totalPDV_J2;
        cout <<  "GANADOR: " << nombreJ2 << " CON " << totalPDV_J2 << " PUNTOS DE VICTORIA" << endl;
    } else{
        cout << "EMPATE: " << nombreJ1 << " , " << nombreJ2 << "CON " << totalPDV_J1 << " PUNTOS DE VICTORIA" << endl;
    }

    if(cantidadPDVGanador > *p_cantidadPDV) {
        *p_nombreJugador = nombreGanador;
        *p_cantidadPDV = cantidadPDVGanador;
    }

    string respuesta;

    cout << "Ingrese Oink para continuar: ";
    cin >> respuesta;
    cout << endl;

    while(respuesta != "Oink"){
        cout << "Respuesta incorrecta!" << endl;
        cout << "Ingrese Oink para continuar:";
        cin >> respuesta;
        cout << endl;
    }
}

void creditos(){
    cout << "-----------------------------------------------------------------" << endl << endl;
    cout << " DESARROLLADO POR:    Lautaro Lopez" << endl;
    cout << " LINKEDIN:            https://www.linkedin.com/in/lopezlautaro/" << endl << endl;
    cout << "-----------------------------------------------------------------" << endl;


}

bool salir(){
    char respuesta;

    cout << "SALIR DEL JUEGO? (S/N): ";
    cin >> respuesta;
    cout << endl;

    while(respuesta != 'N' && respuesta != 'S'){
        cout << "No ingreso una opcion valida, por favor vuelva a seleccionar." << endl;
        cout << endl << "SALIR DEL JUEGO? (S/N): ";
        cin >> respuesta;
        cout << endl;
    }

    if(respuesta == 'S'){
        return true;
    } else {
        return false;
    }

}

