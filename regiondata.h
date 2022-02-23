//CONTAGION - CSCE2110.201 - Group 10
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "agent.h"

#ifndef REGIONDATA_H
#define REGIONDATA_H

using namespace std;

class regionData{	//stores id, population data as well as vector of agents (of population size)
public:
	regionData();
	regionData(int id, int pop, int vax);
	
	void setID(int id);
	int getID();
	
	void setPop(int pop);
	int getPop();

	void giveVax();
	int getVax();
	
	void addAdjacent(int adjArea);	//reads in data for adjacencies
	void printAdjacent();	//prints adjacency list
	int getAdjacentSize();
	int getAdjacents(int i);
	
	void createAgents();	//creates an object for each person in an area
	int countAgents();	//counts total number of agents in an area
	int countType(char type);//counts total number of a specified type of agents in an area
	
	void changeState(int num, char type1, char type2); //changes health state of num of agents from type1 to type2
	
	void resetAgents();	//resets all agents to S after each simulation
	int countNewInf();	//counts newly infected agents for total infected (analysis)
	
	int countRecoveries(int time);	//counts number of infected that have been infected for infPeriod
	void updateTime();	//adds a day to infected for infPeriod
private:
	int areaID;
	int areaPop;
	int vaxRec; //number of vaccines recieved from distribution.
	vector<agent*> agents;
	vector<int> adjacent;
};

#endif