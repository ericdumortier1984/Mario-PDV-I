#include "Counter.h"

Counter::Counter()
{

	// En el constructor, se inicializan los objetos necesarios para el contador de tiempo
	_clock = new Clock();// Objeto Clock para medir el tiempo
	_time = new Time();// Objeto Time para almacenar el tiempo transcurrido

	_font = new Font();// Objeto Font para la fuente del texto del contador
	_textCounter = new Text();// Objeto Text para mostrar el contador de tiempo

	_counterTime = 60;// Tiempo total del contador en segundos
	_initTime = _counterTime;// Tiempo inicial del contador en segundos
	_timeUp = false;// Indica si el tiempo se ha agotado
	// Inicializar las variables de reduccion de tiempo en false
	_timeReduction = false; 
	_timeReduction2 = false;
	_timeReduction3 = false;
}

Counter::~Counter()
{

    // En el destructor, se eliminan los objetos utilizados
	delete _font;
	delete _textCounter;
	delete _clock;
	delete _time;
}

void Counter::InitCounter()
{

	// Inicializa el contador de tiempo
	*_time = seconds(_counterTime);
	UpdateTextCounter();
}


void Counter::UpdateCounter()
{

	// Actualiza el tiempo restante del contador
	*_time -= _clock->restart();
	UpdateTextCounter();

	if (*_time <= seconds(0))
	{
		_timeUp = true;
	}
}

void Counter::UpdateTextCounter()
{

	// Actualiza el texto que muestra el contador de tiempo
	int _s = _time->asSeconds();
	if (_s >= 0)
	{
		_font->loadFromFile("Asset/Font/junegull.ttf");
		_textCounter->setFont(*_font);
		_textCounter->setCharacterSize(60);
		_textCounter->setFillColor(Color::Black);
		_textCounter->setPosition(10.f, 10.f);
		_textCounter->setString("TIME: " + to_string(_s));
	}
}

void Counter::WrongBlock()
{

	// Reduce el tiempo del contador cuando se golpea un bloque incorrecto
	if (!_timeReduction && (*_time < seconds(60) && *_time > seconds(40)))
	{
		*_time -= seconds(10);
		_timeReduction = true; // Marcar que se ha aplicado la reduccion de tiempo
	}
	else if (!_timeReduction2 && (*_time < seconds(40) && *_time > seconds(20)))
	{
		*_time -= seconds(10);
		_timeReduction2 = true; // Marcar que se ha aplicado la reduccion de tiempo
	}
	else if (!_timeReduction3 && (*_time < seconds(20) && *_time > seconds(5)))
	{
		*_time -= seconds(10);
		_timeReduction3 = true; // Marcar que se ha aplicado la reduccion de tiempo
	}
}

void Counter::StopCounter()
{
	// Detiene el contador de tiempo
	*_time = seconds(0);
}

bool Counter::TimeUp()
{

	// Devuelve true si el tiempo se ha agotado
	if (*_time <= seconds(0) )
	{
		return _timeUp = true;
	}
}

void Counter::Draw(RenderWindow& _wnd)
{

	// Dibuja el contador de tiempo en la ventana
	_wnd.draw(*_textCounter);
}
