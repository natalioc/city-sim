//SIMCITY - CSCE2110.201 - Group 10
#include "simulation.h"

//stores/controls the timesteps for the simulation
simulation::simulation(){
	timeStep = 0;
}

void simulation::setTimeStep(){
	timeStep = 1;
}

int simulation::getTimeStep(){
	return timeStep;
}
void simulation::updateTimeStep(){
	timeStep = timeStep + 1;
}
