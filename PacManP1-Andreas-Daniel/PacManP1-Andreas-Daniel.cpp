// PacManP1-Andreas-Daniel.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//
//using namespace std; con esto no hace falta escribir std::

#include <iostream>
#include <conio.h>

#define MAP_VERTICAL 29
#define MAP_HORIZONTAL 120
#define PERSONAJE 'O'
#define SALTOLINEA std::cout << std::endl; //Las macro pueden ejecutar lo que sea
enum TILES { EMPTY = ' ', WALL = '#', POINT = '*' };


TILES map[MAP_VERTICAL][MAP_HORIZONTAL];//Creamos Array
bool run = true;

enum INPUT { QUIT, UP, DOWN, LEFT, RIGHT, UNKNOW };
INPUT currentInput = INPUT::UNKNOW;



/// <summary>
/// Definimos los ejes del personaje
/// </summary>
int personaje_x;
int personaje_y;
int puntuacion_actual = 0;
int puntuacion_total;


/// <summary>
/// Configuracion del mapa en consola
/// </summary>
void Setup() {
	//Posicion inicial del personaje
	personaje_x = MAP_HORIZONTAL / 2;
	personaje_y = MAP_VERTICAL / 2;

	//Inicializamos todos los valores del Array
	for (size_t i = 0; i < MAP_VERTICAL; i++)
	{
		for (size_t j = 0; j < MAP_HORIZONTAL; j++)
		{
			if (i == 0 || j == 0 || i == MAP_VERTICAL - 1 || j == MAP_HORIZONTAL - 1)
			{
				map[i][j] = TILES::WALL;
			}
			else
			{
				map[i][j] = TILES::EMPTY;
			}
		}
	}

	/// <summary>
	/// Posicion de objectos en el mapa
	/// </summary>
	map[12][10] = TILES::POINT;
	map[12][11] = TILES::POINT;
	map[12][12] = TILES::POINT;
	map[12][13] = TILES::POINT;
	
	map[12][13] = TILES::POINT;

	// - Dibujado de paredes en Horizonatal
	map[10][0] = TILES::EMPTY;
	map[11][0] = TILES::EMPTY;
	map[12][0] = TILES::EMPTY;
	map[13][0] = TILES::EMPTY;
	map[14][0] = TILES::EMPTY;

	map[10][MAP_HORIZONTAL - 1] = TILES::EMPTY;
	map[11][MAP_HORIZONTAL - 1] = TILES::EMPTY;
	map[12][MAP_HORIZONTAL - 1] = TILES::EMPTY;
	map[13][MAP_HORIZONTAL - 1] = TILES::EMPTY;
	map[14][MAP_HORIZONTAL - 1] = TILES::EMPTY;

	// - Dibujado de paredes en Vertical
	map[0][55] = TILES::EMPTY;
	map[0][56] = TILES::EMPTY;
	map[0][57] = TILES::EMPTY;
	map[0][58] = TILES::EMPTY;
	map[0][59] = TILES::EMPTY;
	map[0][60] = TILES::EMPTY;
	map[0][61] = TILES::EMPTY;
	map[0][62] = TILES::EMPTY;
	map[0][63] = TILES::EMPTY;
	map[0][64] = TILES::EMPTY;
	map[0][65] = TILES::EMPTY;
	
	map[MAP_VERTICAL - 1][55] = TILES::EMPTY;
	map[MAP_VERTICAL - 1][56] = TILES::EMPTY;
	map[MAP_VERTICAL - 1][57] = TILES::EMPTY;
	map[MAP_VERTICAL - 1][58] = TILES::EMPTY;
	map[MAP_VERTICAL - 1][59] = TILES::EMPTY;
	map[MAP_VERTICAL - 1][60] = TILES::EMPTY;
	map[MAP_VERTICAL - 1][61] = TILES::EMPTY;
	map[MAP_VERTICAL - 1][62] = TILES::EMPTY;
	map[MAP_VERTICAL - 1][63] = TILES::EMPTY;
	map[MAP_VERTICAL - 1][64] = TILES::EMPTY;
	map[MAP_VERTICAL - 1][65] = TILES::EMPTY;

	// - Dibujado de pared central up
	map[9][52] = TILES::WALL;
	map[9][53] = TILES::WALL;
	map[9][54] = TILES::WALL;
	map[9][55] = TILES::WALL;
	map[9][56] = TILES::WALL;
	map[9][57] = TILES::WALL;
	map[9][58] = TILES::WALL;
	map[9][59] = TILES::WALL;
	map[9][60] = TILES::WALL;
	map[9][61] = TILES::WALL;
	map[9][62] = TILES::WALL;
	map[9][63] = TILES::WALL;
	map[9][64] = TILES::WALL;
	map[9][65] = TILES::WALL;
	map[9][66] = TILES::WALL;
	map[9][67] = TILES::WALL;
	map[9][68] = TILES::WALL;

	// - Dibujado de pared down
	map[22][55] = TILES::WALL;
	map[22][56] = TILES::WALL;
	map[22][57] = TILES::WALL;
	map[22][58] = TILES::WALL;
	map[22][59] = TILES::WALL;
	map[22][60] = TILES::WALL;
	map[22][61] = TILES::WALL;
	map[22][62] = TILES::WALL;
	map[22][63] = TILES::WALL;
	map[22][64] = TILES::WALL;
	map[22][65] = TILES::WALL;

	// - Dibujado de pareds lateral
	map[22][55] = TILES::WALL;
	map[23][55] = TILES::WALL;
	map[24][55] = TILES::WALL;
	map[25][55] = TILES::WALL;
	map[26][55] = TILES::WALL;
	map[27][55] = TILES::WALL;
	map[28][55] = TILES::WALL;

	map[22][65] = TILES::WALL;
	map[23][65] = TILES::WALL;
	map[24][65] = TILES::WALL;
	map[25][65] = TILES::WALL;
	map[26][65] = TILES::WALL;
	map[27][65] = TILES::WALL;
	map[28][65] = TILES::WALL;






	//Comprobacion de puntos totales
	for (size_t i = 0; i < MAP_VERTICAL; i++)
	{
		for (size_t j = 0; j < MAP_HORIZONTAL; j++)
		{
			if (map[i][j] == TILES::POINT)
			{
				puntuacion_total++;
			}
		}
	}
}


/// <summary>
/// Configuracion de los inputs para mover el personaje
/// </summary>
void Input() {
	//con _getch() capturamos la tecla pulsada como char y la pasamos a input
	char input = _getch();
	switch (input) {
	case 'w':
	case 'W':
		currentInput = INPUT::UP;
		break;
	case 's':
	case 'S':
		currentInput = INPUT::DOWN;
		break;
	case 'a':
	case 'A':
		currentInput = INPUT::LEFT;
		break;
	case 'd':
	case 'D':
		currentInput = INPUT::RIGHT;
		break;
	case 'q':
	case 'Q':
		currentInput = INPUT::QUIT;
		break;
	default:
		currentInput = INPUT::UNKNOW;
		break;
	}
}



/// <summary>
/// Parte logica para mover el personaje por el mapa
/// </summary>
void Logic() {
	int personaje_y_new = personaje_y;
	int personaje_x_new = personaje_x;
	switch (currentInput)
	{
	case QUIT:
		run = false;
		break;
	case UP:
		personaje_y_new--;
		break;
	case DOWN:
		personaje_y_new++;
		break;
	case LEFT:
		personaje_x_new--;
		break;
	case RIGHT:
		personaje_x_new++;
		break;
	}

	//Comprobamos la coordenada por si teletransportamos al personaje
	if (personaje_x_new < 0) {
		personaje_x_new = MAP_HORIZONTAL - 1;
	}
	personaje_x_new = personaje_x_new % MAP_HORIZONTAL;

	if (personaje_y_new < 0) {
		personaje_y_new = MAP_VERTICAL - 1;
	}
	personaje_y_new = personaje_y_new % MAP_VERTICAL;

	//Comprobamos si dentro del array hay dibujado WALL, si no lo hay puedo moverme, si lo hay no puedo y no hace nada
	switch (map[personaje_y_new][personaje_x_new])
	{
	case TILES::WALL:
		break;
	case TILES::POINT:
		puntuacion_actual++;
		map[personaje_y_new][personaje_x_new] = TILES::EMPTY;
	default:
		personaje_y = personaje_y_new;
		personaje_x = personaje_x_new;
		break;
	}
}


/// <summary>
/// Dibujado en consola
/// </summary>
void Draw() {

	//Limpiar la pantalla
	system("CLS");
	//Imprimimos el Array por pantalla
	for (size_t i = 0; i < MAP_VERTICAL; i++)
	{
		for (size_t j = 0; j < MAP_HORIZONTAL; j++)
		{
			//Si el persoinaje esta en estos ejes le pintanmos
			if (i == personaje_y && j == personaje_x) {
				std::cout << PERSONAJE;
			}
			else {
				std::cout << (char)map[i][j];
			}
		}
		SALTOLINEA
	}
	std::cout << puntuacion_actual << "/" << puntuacion_total;
}


/// <summary>
/// Ejecuta las diferentes partes en el orden definido
/// </summary>
/// <returns></returns>
int main()
{

		Setup();
		Draw();
	while (run) {

		Input();
		Logic();
		Draw();
		
		//Si la puntuación es la máxima, cerramos el juego
		if (puntuacion_total == puntuacion_actual) {
			std::cout << "                                          ---HAS GANADO---";
			run = false;
		}
	}

}