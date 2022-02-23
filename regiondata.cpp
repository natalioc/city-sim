//CONTAGION - CSCE2110.201 - Group 10
#include "regiondata.h"

regionData::regionData(){
	areaID = -1;
	areaPop = -1;
	vaxRec = 0;
}

regionData::regionData(int id, int pop, int vax){
	areaID = id;
	areaPop = pop;
	vaxRec = vax;
}

void regionData::setID(int id){
	areaID = id;
}

int regionData::getID(){
	return areaID;
}

void regionData::setPop(int pop){
	areaID = pop;
}

int regionData::getPop(){
	return areaPop;
}

void regionData::giveVax(){
	vaxRec++;
}

int regionData::getVax(){
	return vaxRec;
}

void regionData::addAdjacent(int adjArea){
	adjacent.push_back(adjArea);
}

void regionData::printAdjacent(){
	for(int i = 0; i < adjacent.size(); i++){
		cout << adjacent[i] << " ";
	}
	cout << endl;
}

int regionData::getAdjacentSize(){
	return adjacent.size();
}

int regionData::getAdjacents(int i){
	return adjacent[i] - 1;
}	

void regionData::createAgents(){
	for(int i = 0; i < areaPop; i++){
		agents.push_back(new agent('S', 0));
	}
}

int regionData::countAgents(){
	return agents.size();
}

int regionData::countType(char type){
	int num = 0;
	
	for(int i = 0; i < areaPop; i++){
		if(agents[i]->getType() == type){
			num = num + 1;
		}
	}
	
	return num;
}

void regionData::changeState(int num, char type1, char type2){
	for(int i = agents.size() - 1; i >= 0; i--){	//changes type from the back end of the vector
		if(agents[i]->getType() == type1 && num != 0){	//if type1 is found & remaining changes is not 0
			agents[i]->setType(type2);	//change to type 2
			num = num - 1;	//reduced number of remaining changes by 1
		}
	}
}

void regionData::resetAgents(){
	for(int i = 0; i < agents.size(); i++){
		agents[i]->setType('S');
		agents[i]->setTime(0);
	}
}

int regionData::countNewInf(){
	int count = 0;
	
	for(int i = 0; i < agents.size(); i++){
		if(agents[i]->getType() == 'I' && agents[i]->getTime() == 0){
			count = count + 1;
		}
	}
	
	return count;
}

int regionData::countRecoveries(int time){
	int count = 0;
	for(int i = 0; i < agents.size(); i++){
		if(agents[i]->getTime() == time && agents[i]->getType() == 'I'){
			count = count + 1;
		}
	}
	
	return count;
}

void regionData::updateTime(){
	int newTime = 0;
	for(int i = 0; i < agents.size(); i++){
		newTime = 0;
		newTime = agents[i]->getTime() + 1;
		if(agents[i]->getType() == 'I'){
			agents[i]->setTime(newTime);
		}
	}
}