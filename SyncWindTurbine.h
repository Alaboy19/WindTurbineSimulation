#ifndef SyncWindTurbine_h
#define SyncWindTurbine_h
#pragma once
#include "WindTurbine.h"

class SyncWindTurbine : public WindTurbine
{
public:
	SyncWindTurbine()
	{
		this->machineType = "Synchronous";
		this->transP = 0.95;
	}
	double getTransP()
	{
		//TODO:: other things
		return transP;
	}
};
#endif