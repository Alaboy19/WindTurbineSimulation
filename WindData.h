#ifndef WindData_h
#define WindData_h
#pragma once
#include<string>
using namespace std;
class WindData
{
public:
	string dateTime;
	double windSpeed;
	string initWindSpeedInfo;
	string initDateTime;

	WindData(string initDateTime, string initWindSpeedInfo)
	{
		this->initWindSpeedInfo = initWindSpeedInfo;
		this->initDateTime = initDateTime;
	}
	WindData(){}
};

class ReportInfo
{
public:
	double totalPower;
	double totalIncome;
	double capacity;
	ReportInfo()
	{
		totalPower = 0;
		totalIncome = 0;
		capacity = 0;
	}
};
#endif