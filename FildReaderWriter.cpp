#include "FileReaderWriter.h"

vector<WindData> FileReaderWriter::readFromFile(string fileName, string beginTime, string endTime, int flag) //reads from filename
{
	ifstream infile; // creates input stream
	infile.open(fileName, ios::in); // opens it 
	vector<WindData> res; // creates vector of windata objects
	vector<WindData> processRes; // creastes another vector of windata objects
	string date;
	double value;
	int i = 0;
	WindData windData;
	//read the file in order
	while (1) {
		if (getline(infile, date))
		{
			stringstream ss(date);
			string str1;
			string str2;
			getline(ss, str1, ',');   // gets the time instance
			getline(ss, str2, ','); // gets the speed instance
			WindData windData(str1, str2); // winddata constructor 
			res.push_back(windData); // push it back to vector of WindData 
		}
		else
		{
			break;
		}
	}
	//fix data and save the results to processRes
	processData(fileName, res, processRes, beginTime, endTime, flag);
	infile.close();
	return processRes;
}
// processData takes filename and vector of WindData object depending on the begintime and endtime and outputs corrected version of processRes
void FileReaderWriter::processData(string fileName, vector<WindData>& datas, vector<WindData>& precessRes, string beginTime, string endTime, int flag)
{
	for (int i = 0; i < datas.size(); i++)  // iterates through the datas vector that we will get from readfile function
	{
		string str1 = datas[i].initDateTime; // gets the string of datetime and pass to str1

		string beforeDate;    // below gets and pass it to beforeDate
		if (i != 0)
		{
			beforeDate = datas[i - 1].dateTime; // gets the one time instance before date time 
		}
		string str2 = datas[i].initWindSpeedInfo; // gets the speed value and pass to str2
		//if the time is illegal, fix the date by previous time to calculate the current tiume 
		if (str1 == "-99999") // if -99999 is found 
		{
			datas[i].dateTime = fixDate(beforeDate); // fix the date using the method implemented in MissingData.cpp(takes arguement in datetime-> fixed datetime)
		}
		else
		{
			datas[i].dateTime = str1; // no change if it is not -99999
		}
		//if wind speed is found to be -99999 or -99999.9
		if (str2 == "-99999" || str2 == "-99999.0")
		{
			double value1 = datas[i - 1].windSpeed; // takes before speed value 
			int j = i + 1; // current poistion index
			for (; j < datas.size(); j++) // when first missing speed data found, we need to check whether there are more of them after words
			{//iterates until did not reach to that point where no -99999, and findz the size of j (kind of the total number of the missed data in this interval)
				if (datas[j].initWindSpeedInfo != "-99999" && datas[j].initWindSpeedInfo != "-99999.0") // from one normal value to next value(how many j missed datas? )
				{
					break; // breaks when it reaches finish of missing data series for that time interval
				}
			}
			double value2 = 0;
			if (j == datas.size()) // if tehre is no end and even last instance of the vector is missing data, then value2  = 10
				value2 = 10;
			else
				value2 = atof(datas[j].initWindSpeedInfo.c_str()); // if not get float
			datas[i].windSpeed = (value1 + value2) / 2; // the value for i is equal to the average of them 
		}
		else
		{
			datas[i].windSpeed = atof(datas[i].initWindSpeedInfo.c_str()); // if there is no -99999, prvoius value is new value  
		}
		//if flag is one, the data between start and end will be saved in process Res or all will be saved
		if (flag)
		{
			if (compareWithDate(datas[i].dateTime, beginTime, endTime))
			{
				precessRes.push_back(datas[i]);
			}
		}
		else
		{
			precessRes.push_back(datas[i]);
		}
	}

}
void FileReaderWriter::writeToFile(string fileName, vector<WindData>& datas, string beginTime, string endTime, int flag)
{
	ofstream outFile; // creates outfile 
	string prefix = fileName.substr(0, fileName.length() - 4); // the name of file until 
	string outFileName;
	if (flag)
		outFileName = prefix + "_" + transDateFormat(beginTime) + "_" + transDateFormat(endTime) + ".csv";
	else
		outFileName = prefix + "_total.csv";
	outFile.open(outFileName, ios::out);
	for (int i = 0; i < datas.size(); i++)
	{
		outFile << datas[i].dateTime << "," << datas[i].windSpeed << endl;
	}
	outFile.close();
}
vector<string> FileReaderWriter::listAllCsvFiles(string path, string fileType)
{
	// handle file
	long hFile = 0;
	// file properties, info
	struct _finddata_t fileinfo;
	vector<string> files;
	string p;

	if ((hFile = _findfirst(p.assign(path).append("\\*" + fileType).c_str(), &fileinfo)) != -1) {
		do {
			// the root of saving
			files.push_back(p.assign(path).append("\\").append(fileinfo.name));
		} while (_findnext(hFile, &fileinfo) == 0);  //寻找下一个，成功返回0，否则-1
		_findclose(hFile);
	}
	return files;
}
