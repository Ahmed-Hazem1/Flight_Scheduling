#pragma once

#include<fstream>
#include<sstream>
#include<iostream>
#include <string>

class Simulation;
using namespace std;

class InputManger
{
	ofstream OutPutFile;
public:
	void ReadDataFromFile(string FileName, Simulation* sim);
	bool CreateOutPutFile(string OutPutFileName);
	void ExcuteOutputFile(string OutputFileName);     
	void AnalysisOutputFile(string OutputFileName);
	 



};
