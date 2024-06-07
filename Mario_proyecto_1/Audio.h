#pragma once
#include "Includes&usings.h"

class Audio
{
private:

    // Punteros a los objetos Sound que representan los diferentes sonidos
	Sound* _wrong;
	Sound* _yes;
	Sound* _jump;
	Sound* _clock;
	// Punteros a los objetos SoundBuffer que contienen los datos de los archivos de sonido
	SoundBuffer* _musicBuffer;
	SoundBuffer* _wrongBuffer;
	SoundBuffer* _yesBuffer;
	SoundBuffer* _jumpBuffer;
	SoundBuffer* _clockBuffer;

public:

    // Constructor y destructor de la clase Audio
	Audio();
	~Audio();

	// Métodos para reproducir los diferentes sonidos
	void PlayWrongBlock();// Reproduce el sonido de un bloque incorrecto
	void PlayRightBlock();// Reproduce el sonido de un bloque correcto
	void PlayJump();// Reproduce el sonido de un salto
	void PlayClock();// Reproduce el sonido de un reloj
	void StopClock();// Detiene la reproducción del sonido del reloj
};
