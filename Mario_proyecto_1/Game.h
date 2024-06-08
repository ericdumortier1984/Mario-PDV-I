#pragma once
#include "Includes&usings.h"
#include "Afichmation.h"
#include "Block.h"
#include "Counter.h"
#include "Audio.h"

class Game
{
private:

	// Propiedades relacionadas con el mundo del juego
	const int _wnd_x_min = 0;// Límite izquierdo de la pantalla
	const int _wnd_x_max = 800;// Límite derecho de la pantalla
	const int _floor = 470;// Posicion del piso
	const float _gravity = 0.5f;// Aceleración de la gravedad

	// Ventana del juego
	RenderWindow* w;

	// Textos y fuente
	Font* _font;
	Text* _gameOverText;

	// Audio
	Audio* _audio;

	// Temporizador
	Counter* _timer;

    // Escenario de fondo
	Texture* _backTx;
	Sprite* _backSp;

	// Bloques
	Block* _block[10];
	Block* _textBox;
	int _array_number[10];// Array de números aleatorios
	int _arrayOK[10];// Array de números ordenados
	int _previus_number;
	int _green_block[10];
	int _greenBlockCount;
	int _number;

	// Mario
	Texture* _marioTex;
	Afichmation* _mario;
	Vector2f _velocity;
	bool _isJumping;
	bool _runningLeft;
	bool _runningRight;

	// Métodos privados
	void DoEvents();// Maneja los eventos
	void ProcessCollision();// Procesa las colisiones entre Mario y los bloques
	void DrawGame();// Dibuja todos los elementos en la ventana
	void InitArray();// Inicializa el array de bloques
	void InitMario();// Inicializa a Mario
	void BubbleSort(int _arr[], int _size);// Ordena el array de números usando el algoritmo de burbuja
	void CheckGameConditions();// Verifica las condiciones de victoria o derrota
	void GameOver();// Muestra la pantalla de "Game Over"

	// Variables de estado del juego
	bool _gameOver;
	bool _youWin;
	
public:

	// Constructor y destructor
	Game();
	~Game();

	// Método público
	void Loop();// Bucle principal del juego
};
