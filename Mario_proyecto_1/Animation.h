#ifndef ANIMATION_H
#define ANIMATION_H

#include "Includes&usings.h"

class Animation
{
	friend class Afichmation;
private:

	string name;
	vector<int> frames;
	vector<int>::iterator it;
	bool loop;
	int fps;
	int frame;
	int indexFrame;
	bool finish;

public:

	Animation(string name, initializer_list<int> frames, int fps, bool loop)
	{
		this->name = name;
		this->loop = loop;
		this->fps = fps;
		this->frame = 0;
		finish = false;
		initializer_list<int>::iterator iter = frames.begin();
		while (iter != frames.end()) {
			this->frames.push_back(*iter);
			iter++;
		}
		this->indexFrame = *this->frames.begin();
	}

	void NextFrame()
	{
		if (frame >= frames.size())
		{
			frame = 0;
			if (!loop) {
				finish = true;
			}
		}
		it = frames.begin() + frame;
		indexFrame = *it;
		frame++;
	}
};
#endif
