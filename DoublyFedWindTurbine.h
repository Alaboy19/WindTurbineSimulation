#pragma once
#ifndef DoublyFedWindTurbine_h
#define DoublyFedWindTurbine_h
#include "WindTurbine.h"

class DoublyFedWindTurbine : public WindTurbine
{

public:
	DoublyFedWindTurbine()
	{
		this->machineType = "DoublyFed";
		this->transP = 1;


	}
	double getTransP()
	{
		//TODO:: other things
		return transP;
	}
};
#endif