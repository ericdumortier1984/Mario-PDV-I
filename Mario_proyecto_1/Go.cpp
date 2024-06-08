#include "Game.h"
// To fix: reduccion de tiempo es provisoria hasta encontrar mejores soluciones

int main()
{
	srand(time(NULL));// Genera semilla para los numeros aleatorios
	Game* Go;// declara un puntero llamado Go que apunta a un objeto de la clase Game
	Go = new Game;// Crea una instancia de la clase Game y asigna su dirección de memoria al puntero Go
	Go->Loop();// LLamada al metodo Loop() del objeto Game al que apunta Go

	return EXIT_SUCCESS;// valor que indica al sistema operativo que el programa se cerró exitosamente
}
