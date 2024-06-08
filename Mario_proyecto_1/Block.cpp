#include "Block.h"

Block::Block(int _v)
{

	// En el constructor, se inicializan los objetos que se representan el bloque
	int _xPos = 0;
	int _yPos = 0;
	_getHit = false;// Inicializa la variable de estado _getHit como false

	_boxTex = new Texture;
	_boxSp = new Sprite;
	_boxTex->loadFromFile("Asset/Images/bloque_pared.png");// Carga la textura del bloque
	_boxSp->setTexture(*_boxTex);// Asigna la textura al sprite
	_boxSp->setScale(1.3f, 1.3f);// Ajusta la escala del sprite
	_boxSp->setPosition(_xPos, _yPos);// Establece la posición inicial del sprite
	_boxSp->setOrigin(_boxSp->getGlobalBounds().width / 2, _boxSp->getGlobalBounds().height / 2);// Establece el origen del sprite

	_font = new Font;
	_textInBox = new Text;
	_font->loadFromFile("Asset/Font/junegull.ttf");// Carga la fuente del texto
	_textInBox->setFont(*_font);// Asigna la fuente al texto
	_textInBox->setCharacterSize(20);// Establece el tamaño del texto
	_textInBox->setFillColor(Color::Yellow);// Establece el color del texto
	_textInBox->setString(to_string(_v));// Establece el texto del bloque pasando como parametro un valor
	_textInBox->setPosition(_xPos, _yPos);// Establece la posición inicial del texto
	_textInBox->setOrigin(_textInBox->getGlobalBounds().width, _textInBox->getGlobalBounds().height + 10);// Establece el origen del texto
}


Block::~Block()
{

	// En el destructor, se eliminan los objetos utilizados
	delete _font;
	delete _textInBox;
	delete _boxSp;
}

Sprite Block::GetSprite()
{

	// Devuelve el sprite del bloque
	return *_boxSp;
}

Text Block::GetText()
{

	//Devuelve el texto dentro del bloque
	return *_textInBox;
}

void Block::SetTextString(const string& text)
{

	// Establece el texto dentro del bloque
	_textInBox->setString(text);
}

String Block::GetTextString()
{

	// Devuelve el texto dentro del bloque
	String txt = _textInBox->getString();

	return txt;
}

void Block::SetPosition(int _xPos, int _yPos)
{

	// Establece la posición del bloque
	_boxSp->setPosition(_xPos, _yPos);
	_textInBox->setPosition(_xPos, _yPos);
}

FloatRect Block::Getposition()
{

	// Devuelve la posición del bloque
	FloatRect _spritePos = _boxSp->getGlobalBounds();

	return _spritePos;
}

void Block::SetHit()
{

	// Establece que el bloque ha sido golpeado
	_getHit = true;
}

bool Block::GetHit()
{

	// Devuelve true si el bloque ha sido golpeado
	return _getHit;
}

void Block::SetColorGreen()
{

	// Establece el color del texto del bloque a verde
	_textInBox->setFillColor(Color::Green);
}

void Block::SetColorWhite()
{
	_textInBox->setFillColor(Color::White); // Establecer el color del texto a blanco
}

void Block::Draw(RenderWindow& _wnd)
{

// Dibuja el bloque en la ventana
// Esta función está vacía, ya que el dibujo se realiza en otra parte del código
}
