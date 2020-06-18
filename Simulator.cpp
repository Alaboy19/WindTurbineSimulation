#include "FileReaderWriter.h"
#include "DoublyFedWindTurbine.h"
#include "IndutionWindTurbine.h"
#include "SyncWindTurbine.h"
#include "MissingData.h"
#include <time.h>
#define A 1.225
string report = "summary_report.txt";


void generateReport(ReportInfo& totalSummary, vector<double> powers, string fileName, string startTime, string endTime)
{
	ofstream outFile;
	outFile.open(report, ios::app);
	double totalPower = 0;
	for(int i = 0; i < powers.size(); i++)
	{
		totalPower += powers[i] / 1000; 
	}
	outFile<<"Report for file "<<fileName<<"("<<startTime<<"-"<<endTime<<")"<<endl;
	outFile<<"Total power:"<<totalPower<<endl;
	cout<<"Input the income for this farm:"<<endl;
	double income;
	cin>>income;
	income = totalPower * income;
	outFile<<"Total income:"<<income<<endl;
	int ratedPower;
	cout<<"Input the Rated Power(KW):"<<endl;
	cin>>ratedPower;
	int capacity = totalPower / (ratedPower * powers.size()) * 100;
	if(powers.size() == 0)
		capacity = 0;
	outFile<<"Capacity factor:"<<capacity<<endl;
	cout<<"Calaulate the farm report done."<<endl;
	totalSummary.totalIncome += income;
	totalSummary.totalPower += totalPower;
	totalSummary.capacity += capacity;
	outFile.close();
}

//the equtions of calculating the power
void calculatePower(vector<WindData>& datas, vector<double>& powers, int rotorArea, string startTime, string endTime, string fileName, WindTurbine * windTurbine)
{
	cout<<"Begin generate power series and insufficient series for file "<<fileName<<endl;
	vector<WindData> windDatas; 
	string outputFile = fileName.substr(0, fileName.length() - 4);
	outputFile = outputFile + "_" + transDateFormat(startTime) + "_" + transDateFormat(endTime) + "_power.csv";
	string insufficientFile = fileName.substr(0, fileName.length() - 4);
	insufficientFile += "_" + transDateFormat(startTime) + "_" + transDateFormat(endTime) + "_insufficient.csv";
	for(int i = 0; i < datas.size(); i++)
	{
		double power = 0;
		if(datas[i].windSpeed < 10 || datas[i].windSpeed > 30){
			power = 0;
			windDatas.push_back(datas[i]);
		}
		else 
			power = rotorArea * A * pow(datas[i].windSpeed, 3) / 2 * windTurbine->getTransP();
		powers.push_back(power);
	}
	ofstream outFile;
	outFile.open(outputFile, ios::out);
	for(int i = 0; i < datas.size(); i++)
	{
		outFile<<datas[i].dateTime<<","<<powers[i]<<endl;
	}
	outFile.close();

	outFile.open(insufficientFile, ios::out);
	for(int i = 0; i < windDatas.size(); i++)
	{
		outFile<<windDatas[i].dateTime<<","<<windDatas[i].windSpeed<<endl;
	}
	outFile.close();
	cout<<"done..."<<endl;
}

//according to different types of generator
vector<double> analysis(vector<WindData>& datas, string startTime, string endTime, string fileName)
{
	WindTurbine * windTurbine;
	
	cout<<"Please select the wind turbine type:"<<endl<<"1.Sync type.\n2.Indution type\n3.Doubly Fed type\n";
	int input;
	cin>>input;
	if(input == 1)
	{
		windTurbine = &SyncWindTurbine();
	}
	else if(input == 2)
	{
		windTurbine = &IndutionWindTurbine();
	}else if(input == 3)
	{
		windTurbine = &DoublyFedWindTurbine();
	}
	int rotorArea = 0;
	cout<<"Input the rotor area:"<<endl;
	cin>>rotorArea;
	vector<double> powerList;
	calculatePower(datas, powerList, rotorArea, startTime, endTime, fileName, windTurbine);	
	windTurbine = NULL; 
	return powerList;
}

//calculate all the cvs files of current folder
void genPowerDetails(vector<string>& csvFiles, string startTime, string endTime, FileReaderWriter& fileReaderWriter, int range)
{
	ReportInfo totalSummary;
	for(int i = 0; i < csvFiles.size(); i++){
		cout<<"Process file of "<<csvFiles[i]<<endl;
		vector<WindData> datas = fileReaderWriter.readFromFile(csvFiles[i], startTime, endTime, 1);
		//add the variance
		for(int i = 0; i < datas.size(); i++)
		{
			double rangeNum = getRandNum(datas[i].windSpeed, range);
			datas[i].windSpeed = rangeNum;
		}
		//save to a new file
		fileReaderWriter.writeToFile(csvFiles[i], datas, startTime, endTime, 1);
		cout<<"done..."<<endl;
		vector<double> powerList = analysis(datas, startTime, endTime, csvFiles[i]); 
		generateReport(totalSummary, powerList, csvFiles[i], startTime, endTime);
		cout<<endl<<endl;
	}
	ofstream outFile;
	outFile.open(report, ios::app);
	outFile<<endl<<endl;
	outFile<<"Report for all farms "<<"("<<startTime<<"-"<<endTime<<")"<<endl;
	outFile<<"Total power:"<<totalSummary.totalPower<<endl;
	outFile<<"Total income:"<<totalSummary.totalIncome<<endl;
	outFile<<"Capacity factor:"<<totalSummary.capacity / 4<<"%"<<endl;
	outFile.close();
}

//Simulator main
void windSimulator(FileReaderWriter& fileReaderWriter)
{
	string filePath;
	string currFileName;
	cout<<"Please input the data file path:"<<endl;
	cin>>filePath;
	report  = filePath + "\\" + report;
	fstream file(report, ios::out);
	vector<string> csvFiles = fileReaderWriter.listAllCsvFiles(filePath, ".csv");
	if(csvFiles.size() == 0)
	{
		cout<<"No csv files in the target path, Please check again!"<<endl;
		exit(0);
	}
	string startTime, endTime;
	cout<<"Input the start Time(eg.2018/01/01):"<<endl;
	cin>>startTime;
	cout<<"Input the end Time(eg.2019/01/01):"<<endl;
	cin>>endTime;
	cout<<"Add variance range(0-10)%:"<<endl;
	int range = 0;
	cin>>range;
	cout<<"Begin analysis..."<<endl;
	genPowerDetails(csvFiles, startTime, endTime, fileReaderWriter, range);
		
}

int main()
{
	srand((int)time(NULL));
	FileReaderWriter fileReaderWriter;
	windSimulator(fileReaderWriter);
	return 0;
}