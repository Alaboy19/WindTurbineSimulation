#pragma once
#include<vector>
#include<string>
#include <fstream>
#include<iostream>
#include <sstream>
#ifndef FileReaderWriter_h
#define FileReaderWriter_h
#include <io.h>  /////?????????????????????????????????????????????????????????????????????????????????????????????????????????
#include "WindData.h"
#include "MissingData.h"
using namespace std;
//reading file 
class FileReaderWriter
{
public:
	//read file according to the begin time and end time, to read file and flag indicate whether to read all the data and meantimr process data and write to file and save to new file
	vector<WindData> readFromFile(string fileName, string beginTime, string endTime, int flag);

	//fixing the data
	void processData(string fileName, vector<WindData>& datas, vector<WindData>& precessRes, string beginTime, string endTime, int flag);

	
	//write the data to new file
	void writeToFile(string fileName, vector<WindData>& datas, string beginTime, string endTime, int flag);
	
	//list all the datfiles
	vector<string> listAllCsvFiles(string path, string fileType);
};
#endif
