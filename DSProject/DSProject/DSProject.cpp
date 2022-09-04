#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
#include "Graph.h"
#include "Simulation.h"
#include"Queue.h"
#include"PriorityQueue.h"
using namespace std;


int main()
{
	cout << "\t\t\t\t===================================================" << endl;
	cout << "\t\t\t\t||	  WELCOME TO Flight scheduling APP	  ||" << endl;
	cout << "\t\t\t\t===================================================" << endl;

	auto simulation = new Simulation();
	simulation->StartSimulation("InititalData.txt");

//	Flight flight1;
//	Flight flight2;
//auto pq= new PriorityQueue<int>;
//pq->appendNode(4);
//pq->appendNode(2);
//cout << pq->head->value << endl;
	

	return 0;
}