#pragma once
#include "System.h"

class oEffect_BG : public System
{
protected:

	Shape shape;

public:

	oEffect_BG(){}

	virtual void Update(){}

	virtual void Draw()
	{
		wnd->draw(shape);
	}

	virtual bool isEnd() const = 0;

	virtual ~oEffect_BG(){}
};