#include "Audio.h"

Audio::Audio()
{
	// En el constructor, se asigna un objeto Sound y un objeto SoundBuffer a cada uno de los sonidos
	_wrong = new Sound;
	_wrongBuffer = new SoundBuffer;
	_wrongBuffer->loadFromFile("Asset/Sound/wrong!.ogg");// Carga el archivo de sonido en el SoundBuffer
	_wrong->setBuffer(*_wrongBuffer);// Asigna el SoundBuffer al objeto Sound

	_yes = new Sound;
	_yesBuffer = new SoundBuffer;
	_yesBuffer->loadFromFile("Asset/Sound/yes!.ogg");// Carga el archivo de sonido en el SoundBuffer
	_yes->setBuffer(*_yesBuffer);// Asigna el SoundBuffer al objeto Sound

	_jump = new Sound;
	_jumpBuffer = new SoundBuffer();
	_jumpBuffer->loadFromFile("Asset/Sound/jump!.ogg");// Carga el archivo de sonido en el SoundBuffer
	_jump->setBuffer(*_jumpBuffer);// Asigna el SoundBuffer al objeto Sound

	_clock = new Sound;
	_clockBuffer = new SoundBuffer();
	_clockBuffer->loadFromFile("Asset/Sound/tic-tac.ogg");// Carga el archivo de sonido en el SoundBuffer
	_clock->setBuffer(*_clockBuffer);// Asigna el SoundBuffer al objeto Sound
}

Audio::~Audio()
{
	// En el destructor, se eliminan los objetos Sound y SoundBuffer
	delete _clock;
	delete _jump;
	delete _yes;
	delete _wrong;
}

void Audio::PlayWrongBlock()
{
	// Reproduce el sonido de un bloque incorrecto
	_wrong->play();
}

void Audio::PlayRightBlock()
{
	// Reproduce el sonido de un bloque correcto
	_yes->play();
}

void Audio::PlayJump()
{
	// Reproduce el sonido de un salto
	_jump->play();
}

void Audio::PlayClock()
{
	// Reproduce el sonido del reloj y lo configura para que se reproduzca en bucle
	_clock->play();
	_clock->setLoop(true);
}

void Audio::StopClock()
{
	// Detiene la reproducción del sonido del reloj
	_clock->stop();
}
