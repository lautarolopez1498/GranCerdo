#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED
#include <iostream>
#include <time.h>
#include <unistd.h>
#include <string>
using namespace std;

void jugar(bool *p_seJugo, string *p_nombreJugador, int *p_cantidadPDV);
bool determinarInicio(string nombreJ1, string nombreJ2);
void jugarRonda(int *p_puntajeJugador, int *p_puntajeOponente, int vec[], string nombreJugador, string nombreOponente, int ronda, bool *p_hundirseBarro, bool *p_tresDados, int hitosJugador[]);
int condicion_1(int vec[], int tamanio);
int condicion_2(int vec[], int tamanio);
int condicion_3(int vec[], int tamanio);
int condicion_4(int vec[], int tamanio);
int condicion_5(int vec[], int tamanio);
int dadoAleatorio();
void lanzarDados(int vec[], int tamanio);
void mostrarVector(int vec[], int tamanio);
void mostrarMenu();
int sumarVector(int vec[], int tamanio);
int contarAs(int vec[], int tamanio);
bool cederTurno();
void cargarVector(int vec[], int tamanio);
void mostrarInfoRonda(int numeroRonda, int puntosRonda, int cantLanzamientos, string nombre);
void datosFinRondas(string nombreJ1, int hitosJ1[], string nombreJ2, int hitosJ2[], string *p_nombreJugador, int *p_cantidadPDV);
void creditos();
bool salir();


#endif // FUNCIONES_H_INCLUDED
