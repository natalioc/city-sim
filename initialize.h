//SIMCITY - CSCE2110.201 - Group 10
//Initialization, reading in config/region layout written by Natalio Castaneda
//Residential written by Natalio Castaneda
//Industrial written by Mamerto Cruz
//Commercial written by Natalio Castaneda
//Pollution written by Natalio Castaneda
//Region analysis written by Mamerto Cruz
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdio>
#include <algorithm>
#include "celldata.h"

#ifndef INITIALIZE_H
#define INITIALIZE_H

using namespace std;

class initialize{
public:							
    string readConfig(string configName);
    void readLayout(string layoutName);
    void printRegion();
    void cleanData();
	
	int getTimeLimit();
	int getRefreshRate();
	
	//checks if adjacent cells exist
	bool checkAdjacent(int i, int j);
	
	//counts the total number of cells with a certain population that exist around a specified cell
	int countAdjacentPop(int i, int j, int pop);
	int totalAdjacentPop(int i, int j);
	int regionSizeX();
	int regionSizeY();
	
	//updates each zone every timestep
	void updateResidential();
	void updateIndustrial();
	void updateCommercial();
	
	//increases/decreses/sets/gets workers and goods
	void incWorkers();
	void decWorkers();
	void setWorkers(int numWorkers);
	int getWorkers();
	void incGoods();
	void decGoods();
	void setGoods(int numGoods);
	int getGoods();
	
	//prints available workers and goods
	void printAvailableWG();
	
	//analysis for user selected cells
	void printDesiredArea(int x1, int y1, int x2, int y2);
	
	//prints total population for each zone
	void printTotalPopulations();
	
	//check if cells were updated to stop simulation
	void setUpdated(bool resetUpdated);
	bool getUpdatedR();
	bool getUpdatedI();
	bool getUpdatedC();
	
	//pollution functions
	void updatePollution();	//updates at end of simulation
	void printPollution();
	int totalPollution();
	
protected:
    int timeLimit;
    int refreshRate;
	vector<vector<celldata*>> row;	//2d vector outer
	vector<celldata*> col;			//2d vector inner
	//total populations for each zone
	int residentialPopulation;
	int industrialPopulation;
	int commercialPopulation;
	int workers;
	int goods;
	int count1, count2, count3, count4, count5;
	vector<vector<celldata*>> temp;
	vector<vector<celldata*>> updateCheck;			//checks if updates occured in each zone each time step
	bool updatedR, updatedI, updatedC;
};

#endif
