#ifndef InductionWindTurbine_h
#define InductionWindTurbine_h
#pragma once
#include "WindTurbine.h"

class IndutionWindTurbine : public WindTurbine
{
public:
	IndutionWindTurbine()
	{
		this->machineType = "Electrical";
		this->transP = 0.9;
	}
	double getTransP()
	{
		//TODO:: other things
		return transP;
	}
};
#endif