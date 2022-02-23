//CONTAGION - CSCE2110.201 - Group 10
#include "agent.h"

agent::agent(){
	agentType = 'X';
	agentTime = -1;
}

agent::agent(char type, int time){
	agentType = type;
	agentTime = time;
}

void agent::setType(char type){
	agentType = type;
}

char agent::getType(){
	return agentType;
}

void agent::setTime(int time){
	agentTime = time;
}

int agent::getTime(){
	return agentTime;
}