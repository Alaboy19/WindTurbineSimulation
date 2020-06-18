#ifndef WindTurbine_h
#define WindTrubine_h
#pragma once
#include <string>
using namespace std;
class WindTurbine
{

public:
	string machineType;
	double transP;
	double b; 
	double v_cutin;
	double v_optimum;
	double area; 

	WindTurbine()
	{
		transP = 0;
	}
	virtual double getTransP()
	{
		return transP;
	}
};
#endif