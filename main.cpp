//SIMCITY - CSCE2110.201 - Group 10
//Initialization, reading in config/region layout written by Natalio Castaneda
//Residential written by Natalio Castaneda
//Industrial written by Mamerto Cruz
//Commercial written by Natalio Castaneda
//Pollution written by Natalio Castaneda
//Region analysis written by Mamerto Cruz
#include <iostream>
#include <string>
#include "initialize.h"
#include "celldata.h"
#include "simulation.h"

using namespace std;

int main() {
	cout << "Initialization and Commercial were assigned to Natalia Martinez, but were completed by Natalio Castaneda" << endl;
    initialize initial;													//declare initialize class
	simulation sim;														//declare simulation class
	
    string configFileName, layoutFileName;								//declare filename strings
	int x1, y1, x2, y2;													//declare desired area coordinates

    cout << "Beginning simulation" << endl;
    cout << "Please enter the name of the configuration file:";
    cin >> configFileName;												//user input configuration file name

    layoutFileName = initial.readConfig(configFileName);				//read configuration file; timeLimit and refreshRate stored in class initialize
    initial.readLayout(layoutFileName);									//read layout file; name given in configuration file

    cout << "Initial Region State" << endl;
	initial.printRegion();												//print initial region layout

	sim.setTimeStep();													//initialize timeStep as 1!
	initial.setWorkers(0);												//initialize workers as 0!
	initial.setGoods(0);												//initialize goods as 0!
	initial.setUpdated(true);
	
																		//BEGIN TIME LOOP
																		//simulation time loop: stops by timeLimit, output rate is refreshRate
	while((sim.getTimeStep() <= initial.getTimeLimit())/* FIX: && (initial.getUpdatedR() == 1 || initial.getUpdatedI() == 1|| initial.getUpdatedC() == 1)*/){
		initial.updateResidential();									//update residential cells
		
		cout << "Time Step: " << sim.getTimeStep() << endl;			
		initial.printAvailableWG();										//print	avalable workers and goods
		
		if((sim.getTimeStep() - 1)%initial.getRefreshRate() == 0){		//prints layout for timeSteps in refreshRate
			initial.printRegion();									
		}
		
		while(initial.getGoods() >= 1 && initial.getWorkers() >= 1){	//update commercial cells if workers and goods available
			initial.updateCommercial();
		}
		while(initial.getWorkers() >= 2){								//update residential cells if workers available
			initial.updateIndustrial();	
		}
		
		sim.updateTimeStep();											//go to next timeStep
	}
																		//END OF TIME LOOP
	cout << "Final Region State" << endl;
	initial.printRegion();												//output final region state
	initial.updatePollution();											//update pollution for final region state
	initial.printPollution();											//print pollution layout
	initial.printTotalPopulations();									//print total population of each zone and total region pollution
	cout << "The total amount of pollution in the region is " << initial.totalPollution() << " units" << endl;
	
																		//prompt for requested area coordinates
	cout << "Please enter the diagonal corners of the area you wish to have more information about. (MinX = 0, MinY = 0, MaxX = " <<  initial.regionSizeX() << ", MaxY = " << initial.regionSizeY() << ")" << endl;
	cout << "Enter value for X1: ";
	cin >> x1;
	cout << "Enter value for Y1: ";
	cin >> y1;
	cout << "Enter value for X2: ";
	cin >> x2;
	cout << "Enter value for Y2: ";
	cin >> y2;

	initial.printDesiredArea(x1, y1, x2, y2);							//print desired region showing area

    initial.cleanData();												//cleans memory
	cout << "Simulation complete" << endl;
	return 0;
}
