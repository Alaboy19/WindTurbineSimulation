#ifndef MissingData_h
#define MissingData_h
#pragma once
#include<string>
#include<random>
using namespace std;
// function of getting next month if needed
string getNextMonth(string currMonth, int& v);
// function of getting next weekday
string getNextWeekDay(string currWeekDay);
// function of geting month index
int getMonthNum(string month);
//function of fixing data
string fixDate(string beforeData);
//function of comparing time period that chops the period that need to be considered
int compareWithDate(string initTime, string startTime, string endTime);
// random number generator that takes two arguments
double getRandNum(double initNum, int range);
// converts back to dateformat after fixing it 
string transDateFormat(string date);
#endif