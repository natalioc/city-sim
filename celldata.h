//SIMCITY - CSCE2110.201 - Group 10
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#ifndef CELLDATA_H
#define CELLDATA_H

using namespace std;

class celldata {
public:
    celldata();
	//used to create new object to hold data for each cell
    celldata(char cellType, int cellPopulation, int cellPollution, int xCoord, int yCoord);
    void setType(char cellType);
    void setPopulation(int cellPopulation);
    void setPollution(int cellPollution);
    char getType();
    int getPopulation();
    int getPollution();
	
	//increases population by one
	void incPopulation();
	
	//temporary population functions for updating cells
	void setTempPopulation(int tPop);
	int getTempPopulation();
	void incTempPopulation();
	
	//set/get total population of adjacent cells; for prioritization in zone updates
	void setTotalAdjPop(int tap);
	int getTotalAdjPop();
	
	void setX(int xCoord);
	void setY(int yCoord);
	int getX();
	int getY();

protected:
    char type;
	int tempPopulation;
	int totalAdjPop;
    int population;
    int pollution;
	int x;
	int y;
};

#endif
