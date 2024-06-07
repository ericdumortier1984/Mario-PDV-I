#include "Game.h"

Game::Game()
{

	// Inicialización de la ventana y parámetros de juego
	w = new RenderWindow(VideoMode(800, 600), "Mario Practico 1");
	w->setFramerateLimit(60);
    _gameOver = false;
	_youWin = false;

	// Inicialización de textos y fuente
	_font = new Font;
	_font->loadFromFile("Asset/Font/junegull.ttf");
	_gameOverText = new Text;
	_gameOverText->setFont(*_font);

	// Inicialización del audio
	_audio = new Audio;
	if (!_gameOver)
	{
		_audio->PlayClock();// Inicia el reloj si el juego no ha terminado
	}

	// Inicialización del temporizador
	_timer = new Counter();
	_timer->InitCounter();

	// Inicialización del fondo
	_backTx = new Texture;
	_backSp = new Sprite;
	_backTx->loadFromFile("Asset/Images/mundo_fondo.jpg");
	_backSp->setTexture(*_backTx);

	// Inicialización de los bloques y Mario
	InitArray();
	InitMario();
}

void Game::DoEvents()
{

    // Maneja los eventos del teclado (movimiento de Mario)
	Event e;// Crea un objeto Event para procesar los eventos
	while (w->pollEvent(e))// Recorre los eventos ocurridos en la ventana
	{

		if (e.type == Event::Closed)
			w->close();

		if (Keyboard::isKeyPressed(Keyboard::A))
		{
			_runningLeft = true;
			_runningRight = false;
			_mario->Play("run");
			_mario->FlipX(false);
			float _newPos = _mario->getPosition().x - 25;// Calcula la nueva posición de Mario en el eje X
			if (_newPos >= _wnd_x_min)// Si la nueva posición no sale de la pantalla por el lado izquierdo
			{
				_mario->move(-_velocity.x, 0);
			}
		}
		else if (Keyboard::isKeyPressed(Keyboard::D))
		{
			_runningRight = true;
			_runningLeft = false;
			_mario->Play("run");
			_mario->FlipX(true);
			float _newPos = _mario->getPosition().x + 25;// Calcula la nueva posición de Mario en el eje X

			if (_newPos <= _wnd_x_max)// Si la nueva posición no sale de la pantalla por el lado derecho
			{
				_mario->move(_velocity.x, 0);
			}
		}
		else {
			//descanso
			_runningLeft = false;
			_runningRight = false;
			_mario->Play("idle");
		}
	}
	if (Keyboard::isKeyPressed(Keyboard::Space) && !_isJumping)// Si se presiona la tecla 'Espacio' y Mario no está saltando
	{
		//salto
		_isJumping = true;
		_velocity.y = -10.f;
		_mario->Play("jump");
		_audio->PlayJump();
	}
	if (_isJumping)// Si Mario está saltando
	{
		_velocity.y += _gravity;
		_mario->move(0, _velocity.y);

		if (_mario->getPosition().y >= _floor)
		{
		//piso
		_mario->setPosition(Vector2f(_mario->getPosition().x, _floor));// Coloca a Mario sobre el piso
		_isJumping = false;// Establece que Mario ya no está saltando
		_velocity.y = -10.f;// Reinicia la velocidad vertical inicial para el salto
		}
	}
}

void Game::Loop()
{

    // Bucle principal del juego
	while (w->isOpen())
	{
		if (!_gameOver && !_youWin)
		{
			w->setMouseCursorVisible(false);// Oculta el cursor del mouse
			_timer->UpdateCounter();
			DoEvents();
			DrawGame();
			_mario->Update();
			ProcessCollision();
			CheckGameConditions();
		}
		else
		{
			GameOver();
		}
	}
}

void Game::InitMario()
{

	// Inicialización de Mario
	_marioTex = new Texture;// Crear un objeto Texture para las animaciones de Mario
	_marioTex->loadFromFile("Asset/Images/spriteSheetMario.png");// Cargar la hoja de sprites de Mario
	_mario = new Afichmation(*_marioTex, true, 208, 249);// Crear un objeto Afichmation para Mario
	_mario->Add("idle", { 0, 1, 2, 1, 0 }, 8, true);// Agregar la animación de descanso
	_mario->Add("run", { 3, 4, 5, 4 }, 8, true);// Agregar la animación de correr
	_mario->Add("jump", { 14 }, 8, true);// Agregar la animación de salto
	_mario->Play("idle");// Establecer la animación inicial en "idle"
	_mario->setScale(Vector2f(0.25f, 0.25f));// Escalar el sprite de Mario a un 25% de su tama
	_mario->setOrigin(_mario->getOrigin().x / 2, _mario->getGlobalBounds().height - 16);// Establece el origen en el centro del ancho
	_mario->setPosition(Vector2f(50.f, 470.f));// Posicion inicial en x e y
	_mario->FlipX(true);// Comienza el sprite mirando a la derecha
	_velocity = Vector2f(5.f, 0.f);// Setear la velocidad x en 5 (es constante)
	_isJumping = false;
	_runningLeft = false;
	_runningRight = false;
}

void Game::InitArray()
{

	// Inicialización de los bloques y el array de números
	_textBox = new Block(0); // Inicializamos _textBox con un bloque de valor 0
	_previus_number = 0;// Inicializamos _previus_number a 0
	_number = 0;// Inicializamos _number a 0

	// Arreglos
	for (int i = 0; i < 10; i++)// Inicializamos el array _green_block
	{
		_green_block[i] = 0;
	}

	// Generamos números aleatorios y los almacenamos en _array_number
	for (int h = 0; h < 10; h++)
	{
		int _num = 1 + rand() % (1000 - 1);// Generar un número aleatorio entre 1 y 1000
		_array_number[h] = _num;// Almacenar el número aleatorio en _array_number
		_previus_number = _num;// Actualizar _previus_number con el número generado
	}

	// Ordenar el array _arrayOK
	for (int k = 0; k < 10; k++)
	{
		_arrayOK[k] = _array_number[k];
	}
	int _min = 0;
	int _aux = 0;
	for (int i = 0; i < 10; i++)
	{
		_min = i;
		for (int j = i + 1; j < 10; j++)
		{
			if (_arrayOK[j] < _arrayOK[_min])// Encontrar el índice del valor mínimo
			{
				_min = j;
			}
		}
		// Intercambiar los valores en _arrayOK
		_aux = _arrayOK[i];
		_arrayOK[i] = _arrayOK[_min];
		_arrayOK[_min] = _aux;
	}

	// Crear los bloques con los números aleatorios y posicionarlos
	for (int i = 0; i < 10; i++)
	{
		_block[i] = new Block(_array_number[i]);// Crear un nuevo bloque con el número aleatorio
		_block[i]->SetPosition(105 + i * 70, 350);// Establecer la posición del bloque
	}
}

void Game::BubbleSort(int _arr[], int _size)
{

    // Ordenamiento de los números mediante el algoritmo burbuja
	for (int i = 0; i < _size - 1; i++)
	{
		for (int j = 0; j < _size - i - 1; j++)
		{
			if (_arr[j] > _arr[j + 1])
			{
				// Intercambiar los elementos si están en el orden incorrecto
				int _temp = _arr[j];
				_arr[j] = _arr[j + 1];
				_arr[j + 1] = _temp;
			}
		}
	}
}

void Game::ProcessCollision()
{

	// Manejo de las colisiones entre Mario y los bloques
	for (int i = 0; i < 10; i++)
	{
	    // Si el personaje Mario intersecta con el bloque//////////////////y el bloque no ha sido golpeado
		if (_mario->getGlobalBounds().intersects(_block[i]->Getposition()) && _block[i]->GetHit() == false)
		{
		    // Si el texto del bloque es igual al número esperado
			if ((_block[i]->GetTextString()) == (to_string)(_arrayOK[_number]))
			{
				_block[i]->SetHit();// Marcar el bloque como golpeado
				_audio->PlayRightBlock();// Reproducir sonido de bloque correcto
				_block[i]->SetColorGreen();// Cambiar el color del texto del bloque a verde
				_green_block[i] = 1;// Marcar el texto del bloque como verde en el array _green_block
				_number++;// Incrementar _number
			}
			// Si el bloque no corresponde al número esperado y no ha sido golpeado
			else if (_number != i && _block[i]->GetHit() == false)
			{
				_block[i]->SetHit();// Marcar el bloque como golpeado
				_audio->PlayWrongBlock();// Reproducir sonido de bloque incorrecto
				_timer->WrongBlock();// Activar el temporizador de penalización
			}
		}
	}
}

void Game::CheckGameConditions()
{

	// Verifica si el juego ha terminado (victoria o derrota)
	_greenBlockCount = 0;// Inicializar contador de bloques en verdes en 0

	  // Contar cuántos bloques verdes hay
	for (int i = 0; i < 10; i++)
	{
		if (_green_block[i] == 1)
		{
			_greenBlockCount++;
		}
	}

	 // Si se agotó el tiempo y no se ha ganado, es derrota
	if (_timer->TimeUp() && !_youWin)
	{
		_audio->StopClock();
		_gameOver = true;
	}
	// Si se han golpeado todos los bloques correctamente, es victoria
	else if (_greenBlockCount == 10)
	{
		_audio->StopClock();
		_timer->StopCounter();
		_youWin = true;
	}
}

void Game::GameOver()
{

	// Muestra la pantalla de "Game Over"
	if (_gameOver || _youWin)
	{
		BubbleSort(_arrayOK, 10);
		for (int i = 0; i < 10; i++)
		{
			_block[i]->SetTextString(to_string(_arrayOK[i]));
		}

		_gameOverText->setCharacterSize(100);
		_gameOverText->setFillColor(Color::White);
		_gameOverText->setPosition(200, 100);
		_gameOverText->setString("GAME OVER");
	}

	Event evt;
	while (w->waitEvent(evt))
	{
		if (evt.type == Event::Closed) {
			w->close();
		}

		w->clear(Color::Cyan);
		w->draw(*_gameOverText);
		for (int i = 0; i < 10; i++)
		{
			w->draw(_block[i]->GetSprite());
			w->draw(_block[i]->GetText());
		}
		w->setMouseCursorVisible(true);
		w->display();
	}
}

void Game::DrawGame()
{
    //Limpia la ventana, dibuja y muestra todos los elementos
	w->clear();
	w->draw(*_backSp);
	_timer->Draw(*w);
	w->draw(*_mario);
	for (int i = 0; i < 10; i++)
	{
		w->draw(_block[i]->GetSprite());
		w->draw(_block[i]->GetText());
	}
	_textBox->Draw(*w);
	w->display();
}

Game::~Game()
{

	// Liberación de recursos
	delete _audio;
	delete _backSp;
	delete _timer;
	delete _mario;
	delete[] _block;
	delete _textBox;
	delete _gameOverText;
}

