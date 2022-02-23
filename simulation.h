//SIMCITY - CSCE2110.201 - Group 10

#include <iostream>
#include <vector>
#include <string>
#include "celldata.h"
#include "initialize.h"

#ifndef SIMULATION_H
#define SIMULATION_H

//stores/controls the timesteps for the simulation
class simulation{
public:
	simulation();
	void setTimeStep();
	int getTimeStep();
	void updateTimeStep();
	
protected:
	int timeStep;

};

#endif