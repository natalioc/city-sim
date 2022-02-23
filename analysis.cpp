//CONTAGION - CSCE2110.201 - Group 10
#include "analysis.h"

analysis::analysis(){
	peakInf = 0;
	peakDay = 0;
	totalInf = 0;
	endDay = 0;
}

analysis::analysis(int maxInf, int maxDay, int totalInfected, int lastDay){
	peakInf = maxInf;
	peakDay = maxDay;
	totalInf = totalInfected;
	endDay = lastDay;
}

	
void analysis::setPeakInf(int maxInf){
	peakInf = maxInf;
}

int analysis::getPeakInf(){
	return peakInf;
}


void analysis::setPeakDay(int maxDay){
	peakDay = maxDay;
}

int analysis::getPeakDay(){
	return peakDay;
}


void analysis::setTotalInf(int totalInfected){
	totalInf = totalInfected;
}

int analysis::getTotalInf(){
	return totalInf;
}


void analysis::setEndDay(int lastDay){
	endDay = lastDay;
}

int analysis::getEndDay(){
	return endDay;
}