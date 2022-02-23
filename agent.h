//CONTAGION - CSCE2110.201 - Group 10
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#ifndef AGENT_H
#define AGENT_H

using namespace std;

class agent{	//stores data for each person in an area - wether the person is susceptable, infectious, etc
public:
	agent();
	agent(char type, int time);
	
	void setType(char type);
	char getType();
	
	void setTime(int time);
	int getTime();
	
private:
	char agentType; //SIRV - S is the initial type
	int agentTime;
};

#endif