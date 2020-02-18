#pragma once
#include "Animal.h"

class Sealion : public Animal
{
public:
	Sealion();
	~Sealion();
	Sealion *next;

private:
	float bonus_payout;		// used for special event

};

