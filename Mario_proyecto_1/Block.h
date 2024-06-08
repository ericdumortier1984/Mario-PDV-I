#pragma once
#include "Includes&usings.h"

class Block
{

private:

	// Punteros a los objetos que representan el bloque
	Texture* _boxTex;// Textura del bloque
	Sprite* _boxSp;// Sprite del bloque
	Text* _textInBox;// Texto dentro del bloque
	Font* _font;// Fuente del texto
	// Variables de estado del bloque
	bool _getHit;// Indica si el bloque ha sido golpeado
	int _xPos;// Posición horizontal del bloque
	int _yPos;// Posición vertical del bloque
public:

	// Constructor y destructor de la clase Block
	Block(int _v);
	~Block();

	// Métodos de la clase Block
	Sprite GetSprite();// Devuelve el sprite del bloque
	Text GetText();// Devuelve el texto dentro del bloque
	void SetTextString(const string& text);// Establece el texto dentro del bloque
	String GetTextString();// Devuelve el texto dentro del bloque
	void SetColorGreen();// Establece el color del texto del bloque a verde
	void SetColorWhite();
	void SetHit();// Establece que el bloque ha sido golpeado
	bool GetHit();// Devuelve true si el bloque ha sido golpeado
	void SetPosition(int _xPos, int _yPos);// Establece la posición del bloque
	FloatRect Getposition();// Devuelve la posición del bloque
	void Draw(RenderWindow& _wnd);// Dibuja el objeto en la ventana
};
