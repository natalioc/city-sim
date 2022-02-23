//SIMCITY - CSCE2110.201 - Group 10
#include "celldata.h"

celldata::celldata() {
    type = 'x';
    population = 0;
    pollution = 0;
	x = -1;
	y = -1;
}

celldata::celldata(char cellType, int cellPopulation, int cellPollution, int xCoord, int yCoord){
    type = cellType;
    population = cellPopulation;
    pollution = cellPollution;
	x = xCoord;
	y = yCoord;
}

void celldata::setType(char cellType) {
    type = cellType;
}

void celldata::setPopulation(int cellPopulation) {
    population = cellPopulation;
}

void celldata::setPollution(int cellPollution) {
    pollution = cellPollution;
}

char celldata::getType() {
    return type;
}

int celldata::getPopulation() {
    return population;
}

int celldata::getPollution() {
    return pollution;
}

void celldata::incPopulation(){
	population = population + 1;
}

void celldata::setTempPopulation(int tPop){
	tempPopulation = tPop;
}

int celldata::getTempPopulation(){
	return tempPopulation;
}

void celldata::incTempPopulation(){
	tempPopulation = tempPopulation + 1;
}

void celldata::setTotalAdjPop(int tap){
	totalAdjPop = tap;
}

int celldata::getTotalAdjPop(){
	return totalAdjPop;
}

void celldata::setX(int xCoord){
	x = xCoord;
}

void celldata::setY(int yCoord){
	y = yCoord;
}

int celldata::getX(){
	return x;
}

int celldata::getY(){
	return y;
}

