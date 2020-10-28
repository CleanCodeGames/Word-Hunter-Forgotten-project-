#pragma once
#include "System.h"
#include "oUnit.h"

class oTrigg : public System
{
protected:

	bool is_End;

public:

	oTrigg() : is_End(false) { }
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual bool IsEnd() const { return is_End; }
	virtual ~oTrigg() { }
};