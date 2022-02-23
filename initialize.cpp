//SIMCITY - CSCE2110.201 - Group 10
//Initialization, reading in config/region layout written by Natalio Castaneda
//Residential written by Natalio Castaneda
//Industrial written by Mamerto Cruz
//Commercial written by Natalio Castaneda
//Pollution written by Natalio Castaneda
//Region analysis written by Mamerto Cruz
#include "initialize.h"

string initialize::readConfig(string configName){														//FUNCTION: READ CONFIG FILE
    ifstream configFile;
    string layoutFileName;

    configFile.open(configName);		                												//open config
    while(!configFile.is_open()){			                											//check if open
        cout << configName << " is an invalid file name. Please enter a new name: " << endl;			//prompt user for new name and retry opening
        cin >> configName;
        configFile.open(configName);
    }

    configFile.ignore(15,':');             																//read contents of file
    configFile >> layoutFileName;																		//store layout filename for reading layout file
    configFile.ignore(15,':');
    configFile >> timeLimit;																			//store timeLimit and refreshRate in initialization class for simulation
    configFile.ignore(15,':');
    configFile >> refreshRate;
    configFile.close();

    return layoutFileName;																				//return layout filename to main to call readLayout function
}

void initialize::readLayout(string layoutName) {														//FUNCTION: READ LAYOUT FILE
    ifstream layoutFile;
    layoutFile.open(layoutName);		                												//open layout
    if(!layoutFile.is_open()){				                											//check if open
        cout << "Could not find layout file " << layoutName << ". Exiting program..."<< endl;
        exit (EXIT_FAILURE);																			//exit program if layout program not found
    }

    char data;																							//read in initial region layout data and store in 2D vector of class celldata
	int x = 0;
	int y = 0;
	while(!layoutFile.eof()){																			//stop reading at file end
        layoutFile.get(data);																			//read in character
        if(data != ',' && data != '\n'){																//only store cell data from CSV
            col.push_back(new celldata(data, 0, 0, x, y));													//allocate memory to vector elements
			x = x + 1;
		}
        if(data == '\n'){																				//add row of cells to vector when reaching end of line
            row.push_back(col);																			
            y = y + 1;
			x = 0;
			col.clear();																				//clear inidividual cell (column) vector (is not needed for storing data long term)
        }
    }
    layoutFile.close();																					//close layout file
	residentialPopulation = 0;
	industrialPopulation = 0;
	commercialPopulation = 0;
}

void initialize::printRegion(){																			//FUNCTION: PRINT REGION

    for(int k = 0; k < row.size(); k++){cout << "--";}													//print proper size top border
    cout << endl;
    for(int i = 0; i < row.size(); i++){																//traverse through first vector
        for(int j = 0; j < row[i].size(); j++){															//traverse through second vector
            if(j == 0){cout << "|";}																	//print left border
			if(row[i][j]->getPopulation() == 0){
				cout << row[i][j]->getType() << " ";													//print cell type if population is zero
			}else{
				cout << row[i][j]->getPopulation() << " ";												//print cell population if population is not zero
			}
            if(j == row[i].size() - 1){cout << "|";}													//print right border
        }
        if(i != row.size() - 1){cout << endl;}															//go to next row
    }
    for(int k = 0; k < row.size(); k++){cout << "--";}													//print proper size bottom border
    cout << endl;
}

void initialize::cleanData() {																			//FUNCTION: CLEAN MEMORY
    for(int i = 0; i < row.size(); i++){																//traverse vectors
        for(int j = 0; j < row[i].size(); j++){
            delete row[i][j];																			//delete allocated memory
        }
    }
}

int initialize::getTimeLimit(){
	return timeLimit;
}
int initialize::getRefreshRate(){
	return refreshRate;
}

void initialize::incWorkers(){
	workers = workers + 1;
}

void initialize::decWorkers(){
	workers = workers - 1;
}

void initialize::setWorkers(int numWorkers){
	workers = numWorkers;
}

int initialize::getWorkers(){
	return workers;
}

void initialize::incGoods(){
	goods = goods + 1;
}

void initialize::decGoods(){
	goods = goods - 1;
}

void initialize::setGoods(int numGoods){
	goods = numGoods;
}

int initialize::getGoods(){
	return goods;
}

int initialize::regionSizeY()	
{
	return row.size()-2;
}
int initialize::regionSizeX()	
{
	return row[0].size()-1;
}

void initialize::printAvailableWG(){	
	cout << "Available Workers " << workers << " Available Goods " << goods << endl;
}

bool initialize::checkAdjacent(int i, int j){	//checks if adjacent cell exists
	bool exists;
	if(i >= 0 && i < row[i].size() && j >= 0 && j < row.size()){
		exists = true;
	}else{
		exists = false;
	}
	return exists;
}

//counts the total number of cells with a certain population that surround a specified cell
int initialize::countAdjacentPop(int i, int j, int pop){

	int count = 0;
	if(checkAdjacent(i-1, j-1)){//makes sure adjacent cell exists
		if(row[i-1][j-1]->getPopulation() >= pop){ //if it exists and has atleast pop population
			count = count + 1;	//increases counter by one
		}
	}
	if(checkAdjacent(i-1,j)){
		if(row[i-1][j]->getPopulation() >= pop){
			count = count + 1;
		}
	}
	if(checkAdjacent(i-1,j+1)){
		if(row[i-1][j+1]->getPopulation() >= pop){
			count = count + 1;
		}
	}
	if(checkAdjacent(i,j-1)){
		if(row[i][j-1]->getPopulation() >= pop){
			count = count + 1;
		}
	}
	if(checkAdjacent(i,j+1)){
		if(row[i][j+1]->getPopulation() >= pop){
			count = count + 1;
		}
	}
	if(checkAdjacent(i+1,j-1)){
		if(row[i+1][j-1]->getPopulation() >= pop){
			count = count + 1;
		}
	}
	if(checkAdjacent(i+1,j)){
		if(row[i+1][j]->getPopulation() >= pop){
			count = count + 1;
		}
	}
	if(checkAdjacent(i+1,j+1)){
		if(row[i+1][j+1]->getPopulation() >= pop){
			count = count + 1;
		}			
	}
	return count;	//returns counter value
}

int initialize::totalAdjacentPop(int i, int j){//calculates the total population for surrounding cells
	int count = 0;
	if(checkAdjacent(i-1, j-1)){//checks if adjacent cell exists
		count = count + row[i-1][j-1]->getPopulation(); //adds population of adjacent cell to counter
	}
	if(checkAdjacent(i-1,j)){
		count = count + row[i-1][j]->getPopulation();
	}
	if(checkAdjacent(i-1,j+1)){
		count = count + row[i-1][j+1]->getPopulation();
	}
	if(checkAdjacent(i,j-1)){
		count = count + row[i][j-1]->getPopulation();
	}
	if(checkAdjacent(i,j+1)){
		count = count + row[i][j+1]->getPopulation();
	}
	if(checkAdjacent(i+1,j-1)){
		count = count + row[i+1][j-1]->getPopulation();
	}
	if(checkAdjacent(i+1,j)){
		count = count + row[i+1][j]->getPopulation();
	}
	if(checkAdjacent(i+1,j+1)){
		count = count + row[i+1][j+1]->getPopulation();		
	}
	return count;	//returns counter
}

void initialize::updateResidential(){
	//WRITTEN BY NATALIO CASTANEDA
	temp = row;//set temp vector to row vector
	updateCheck = row;
	updatedR = true;
	int tempPop = residentialPopulation;	//sets temp total population to current total population of zone
	for(int i = 0; i < row.size(); i++){
		for(int j = 0; j < row[i].size(); j++){
			if(row[i][j]->getType() == 'R'){	//searches 2d vector for residential cells
				temp[i][j]->setTempPopulation(row[i][j]->getPopulation());	//sets temp population to current cell population
				if(residentialPopulation == 0){	//if total residential population is 0
					if(row[i][j]->getPopulation() == 0 && checkAdjacent(i-1, j-1) && temp[i][j]->getTempPopulation() == 0){ //if cell population is 0, adjacent exists, and adjacent is powerline
						if(row[i-1][j-1]->getType() == 'T' || row[i-1][j-1]->getType() == '#'){
							temp[i][j]->incTempPopulation();	//increases cell population by 1
							workers = workers + 1;	//increase available workers by 1
							tempPop = tempPop + 1;	//increase total residential population by 1
						}
					}	//repeat for every adjacent cell
					if(row[i][j]->getPopulation() == 0 && checkAdjacent(i-1,j) && temp[i][j]->getTempPopulation() == 0){
						if(row[i-1][j]->getType() == 'T' || row[i-1][j]->getType() == '#'){
							temp[i][j]->incTempPopulation();
							workers = workers + 1;
							tempPop = tempPop + 1;
						}
					}
					if(row[i][j]->getPopulation() == 0 && checkAdjacent(i-1,j+1) && temp[i][j]->getTempPopulation() == 0){
						if(row[i-1][j+1]->getType() == 'T' || row[i-1][j+1]->getType() == '#'){
							temp[i][j]->incTempPopulation();
							workers = workers + 1;
							tempPop = tempPop + 1;
						}
					}
					if(row[i][j]->getPopulation() == 0 && checkAdjacent(i,j-1) && temp[i][j]->getTempPopulation() == 0){
						if(row[i][j-1]->getType() == 'T' || row[i][j-1]->getType() == '#'){
							temp[i][j]->incTempPopulation();
							workers = workers + 1;
							tempPop = tempPop + 1;
						}
					}
					if(row[i][j]->getPopulation() == 0 && checkAdjacent(i,j+1) && temp[i][j]->getTempPopulation() == 0){
						if(row[i][j+1]->getType() == 'T' || row[i][j+1]->getType() == '#'){
							temp[i][j]->incTempPopulation();
							workers = workers + 1;
							tempPop = tempPop + 1;
						}
					}
					if(row[i][j]->getPopulation() == 0 && checkAdjacent(i+1,j-1) && temp[i][j]->getTempPopulation() == 0){
						if(row[i+1][j-1]->getType() == 'T' || row[i+1][j-1]->getType() == '#'){
							temp[i][j]->incTempPopulation();
							workers = workers + 1;
							tempPop = tempPop + 1;
						}
					}
					if(row[i][j]->getPopulation() == 0 && checkAdjacent(i+1,j) && temp[i][j]->getTempPopulation() == 0){
						if(row[i+1][j]->getType() == 'T' || row[i+1][j]->getType() == '#'){
							temp[i][j]->incTempPopulation();
							workers = workers + 1;
							tempPop = tempPop + 1;
						}
					}
					if(row[i][j]->getPopulation() == 0 && checkAdjacent(i+1,j+1) && temp[i][j]->getTempPopulation() == 0){
						if(row[i+1][j+1]->getType() == 'T' || row[i+1][j+1]->getType() == '#'){
							temp[i][j]->incTempPopulation();
							workers = workers + 1;
							tempPop = tempPop + 1;
						}
					}
				}	
				if(residentialPopulation > 0){	//if total population is greater than one
					if(temp[i][j]->getPopulation() == 0 && countAdjacentPop(i, j, 1) >= 1){
						temp[i][j]->incTempPopulation();	//each if statement follows rules for residential cell updates
						workers = workers + 1;
						tempPop = tempPop + 1;
					}
					if(temp[i][j]->getPopulation() == 1 && countAdjacentPop(i, j, 1) >= 2){
						temp[i][j]->incTempPopulation();
						workers = workers + 1;
						tempPop = tempPop + 1;
					}
					if(temp[i][j]->getPopulation() == 2 && countAdjacentPop(i, j, 2) >= 4){
						temp[i][j]->incTempPopulation();
						workers = workers + 1;
						tempPop = tempPop + 1;
					}
					if(temp[i][j]->getPopulation() == 3 && countAdjacentPop(i, j, 3) >= 6){
						temp[i][j]->incTempPopulation();
						workers = workers + 1;
						tempPop = tempPop + 1;
					}
					if(temp[i][j]->getPopulation() == 4 && countAdjacentPop(i, j, 4) >= 8){
						temp[i][j]->incTempPopulation();
						workers = workers + 1;
						tempPop = tempPop + 1;
					}
				}
			}
		}
	}
	row = temp;	//set new temp values to row for output/next timestep
	for(int i = 0; i < row.size(); i++){
		for(int j = 0; j < row[i].size(); j++){
			if(row[i][j]->getType() == 'R'){
				row[i][j]->setPopulation(temp[i][j]->getTempPopulation());
			}
		}
	}
	residentialPopulation = tempPop;
	if(updateCheck == row){
		updatedR = false;
	}
}

void initialize::updateIndustrial(){
	//WRITTEN BY MAMERTO CRUZ
	temp = row;
	updateCheck = row;
	int tempPop = industrialPopulation;
	int k = 0;
	int tempI = -1;
	int tempJ = -1;
	vector<celldata*> industrialPriority;
	updatedI = true;
	for(int i = 0; i < row.size(); i++){													//loop that iterates through the region
		for(int j = 0; j < row[i].size(); j++){
			if(row[i][j]->getType() == 'I'){
				industrialPriority.push_back(new celldata('I', 0, 0, i, j));
				industrialPriority[k]->setTotalAdjPop(totalAdjacentPop(i, j));
				k++;
			}
		}
	}
	
	k = 0;
	int keep = 0;
	while(k < industrialPriority.size()){
		int greatest = 0;
		for(int m = 0; m < industrialPriority.size(); m++){
			 int currVal = industrialPriority[m]->getTotalAdjPop();
			 if(currVal > greatest){
				 greatest = currVal;
				 keep = m;
			 }else if(currVal <= greatest){
				if(industrialPriority[m]->getY() < industrialPriority[k]->getY()){
					keep = m;
				}else if(industrialPriority[m]->getY() >= industrialPriority[k]->getY()){
					if(industrialPriority[m]->getX() < industrialPriority[k]->getX()){
					keep = m;
					}
				}
			}
		}
		tempI = industrialPriority[k]->getX();
		tempJ = industrialPriority[k]->getY();
		industrialPriority[k]->setX(industrialPriority[keep]->getX());
		industrialPriority[k]->setY(industrialPriority[keep]->getY());
		industrialPriority[keep]->setX(tempI);
		industrialPriority[keep]->setY(tempJ);
		k++;
	}
	
	for(int k = 0; k < industrialPriority.size(); k++){
		int i = industrialPriority[k]->getX();
		int j = industrialPriority[k]->getY();
		temp[i][j]->setTempPopulation(row[i][j]->getPopulation());
		if(industrialPopulation == 0 && workers >= 2){																						//checks for 0 population in cell and at least 2 workers
			if(row[i][j]->getPopulation() == 0 && checkAdjacent(i-1, j-1) && temp[i][j]->getTempPopulation() == 0 && workers >= 2){			//checking the adjacent cells
				if(row[i-1][j-1]->getType() == 'T' || row[i-1][j-1]->getType() == '#'){
					temp[i][j]->incTempPopulation();
					workers = workers - 2;
					tempPop = tempPop + 1;
					goods = goods + 1;
				}
			}
			if(row[i][j]->getPopulation() == 0 && checkAdjacent(i-1,j) && temp[i][j]->getTempPopulation() == 0 && workers >= 2){
				if(row[i-1][j]->getType() == 'T' || row[i-1][j]->getType() == '#'){
					temp[i][j]->incTempPopulation();
					workers = workers - 2;
					tempPop = tempPop + 1;
					goods = goods + 1;
				}
			}
			if(row[i][j]->getPopulation() == 0 && checkAdjacent(i-1,j+1) && temp[i][j]->getTempPopulation() == 0 && workers >= 2){
				if(row[i-1][j+1]->getType() == 'T' || row[i-1][j+1]->getType() == '#'){
					temp[i][j]->incTempPopulation();
					workers = workers - 2;
					tempPop = tempPop + 1;
					goods = goods + 1;
				}
			}
			if(row[i][j]->getPopulation() == 0 && checkAdjacent(i,j-1) && temp[i][j]->getTempPopulation() == 0 && workers >= 2){
				if(row[i][j-1]->getType() == 'T' || row[i][j-1]->getType() == '#'){
					temp[i][j]->incTempPopulation();
					workers = workers - 2;
					tempPop = tempPop + 1;
					goods = goods + 1;
				}
			}
			if(row[i][j]->getPopulation() == 0 && checkAdjacent(i,j+1) && temp[i][j]->getTempPopulation() == 0 && workers >= 2){
				if(row[i][j+1]->getType() == 'T' || row[i][j+1]->getType() == '#'){
					temp[i][j]->incTempPopulation();
					workers = workers - 2;
					tempPop = tempPop + 1;
					goods = goods + 1;
				}
			}
			if(row[i][j]->getPopulation() == 0 && checkAdjacent(i+1,j-1) && temp[i][j]->getTempPopulation() == 0 && workers >= 2){
				if(row[i+1][j-1]->getType() == 'T' || row[i+1][j-1]->getType() == '#'){
					temp[i][j]->incTempPopulation();
					workers = workers - 2;
					tempPop = tempPop + 1;
					goods = goods + 1;
				}
			}
			if(row[i][j]->getPopulation() == 0 && checkAdjacent(i+1,j) && temp[i][j]->getTempPopulation() == 0 && workers >= 2){
				if(row[i+1][j]->getType() == 'T' || row[i+1][j]->getType() == '#'){
					temp[i][j]->incTempPopulation();
					workers = workers - 2;
					tempPop = tempPop + 1;
					goods = goods + 1;
				}
			}
			if(row[i][j]->getPopulation() == 0 && checkAdjacent(i+1,j+1) && temp[i][j]->getTempPopulation() == 0 && workers >= 2){
				if(row[i+1][j+1]->getType() == 'T' || row[i+1][j+1]->getType() == '#'){
					temp[i][j]->incTempPopulation();
					workers = workers - 2;
					tempPop = tempPop + 1;
					goods = goods + 1;
				}
			}
		}	
		if(industrialPopulation > 0){																											//checks for population greater than 0
			if(temp[i][j]->getPopulation() == 2 && countAdjacentPop(i, j, 2) >= 4 && workers >= 2){												//checks for population size of 2 and 4 adjacent cells with population 2
				temp[i][j]->incTempPopulation();
				workers = workers - 2;
				tempPop = tempPop + 1;
				goods = goods + 1;
			}		
			if(temp[i][j]->getPopulation() == 1 && countAdjacentPop(i, j, 1) >= 2 && workers >= 2){												//checks for population size of 1 and 2 adjacent cells with population 1
				temp[i][j]->incTempPopulation();
				workers = workers - 2;
				tempPop = tempPop + 1;
				goods = goods + 1;
			}			
			if(temp[i][j]->getPopulation() == 0 && countAdjacentPop(i, j, 1) >= 1 && workers >= 2){												//checks for population size of 0 and adjacent cell with population 1
				temp[i][j]->incTempPopulation();
				workers = workers - 2;
				tempPop = tempPop + 1;
				goods = goods + 1;
			}
			

		}
	}
	row = temp;
	for(int i = 0; i < row.size(); i++){
		for(int j = 0; j < row[i].size(); j++){
			if(row[i][j]->getType() == 'I'){
				row[i][j]->setPopulation(temp[i][j]->getTempPopulation());
				row[i][j]->setPollution(temp[i][j]->getTempPopulation());
			}
		}
	}
	industrialPopulation = tempPop;
	if(updateCheck == row){
		updatedI = false;
	}
}
	
void initialize::updateCommercial(){
	//WRITTEN BY NATALIO CASTANEDA
	temp = row;
	updateCheck = row;
	int tempPop = commercialPopulation;
	int k = 0;
	int tempI = -1;
	int tempJ = -1;
	vector<celldata*> commercialPriority;
	updatedC = true;
	for(int i = 0; i < row.size(); i++){
		for(int j = 0; j < row[i].size(); j++){
			if(row[i][j]->getType() == 'C'){
				commercialPriority.push_back(new celldata('C', 0, 0, i, j));
				commercialPriority[k]->setTotalAdjPop(totalAdjacentPop(i, j));
				k++;
			}
		}
	}
	
	k = 0;
	int keep = 0;
	int currVal = 0;
	int greatest = 0;
	while(k < commercialPriority.size()){
		currVal = commercialPriority[k]->getTotalAdjPop();
		for(int m = 0; m < commercialPriority.size(); m++){
			currVal = commercialPriority[m]->getTotalAdjPop();
			if(currVal > greatest){
				greatest = currVal;
				keep = m;
			}else if(currVal <= greatest){
				if(commercialPriority[m]->getY() < commercialPriority[k]->getY()){
					keep = m;
				}else if(commercialPriority[m]->getY() >= commercialPriority[k]->getY()){
					if(commercialPriority[m]->getX() < commercialPriority[k]->getX()){
					keep = m;
					}
				}
			}
		}
		tempI = commercialPriority[k]->getX();
		tempJ = commercialPriority[k]->getY();
		commercialPriority[k]->setX(commercialPriority[keep]->getX());
		commercialPriority[k]->setY(commercialPriority[keep]->getY());
		commercialPriority[keep]->setX(tempI);
		commercialPriority[keep]->setY(tempJ);
		k++;
	}
	
	for(int k = 0; k < commercialPriority.size(); k++){
		int i = commercialPriority[k]->getX();
		int j = commercialPriority[k]->getY();
		temp[i][j]->setTempPopulation(row[i][j]->getPopulation());
		if(temp[i][j]->getTempPopulation() == 0 && workers >= 1 && goods >= 1){
			if(row[i][j]->getPopulation() == 0 && checkAdjacent(i-1, j-1) && temp[i][j]->getTempPopulation() == 0 && workers >= 1 && goods >= 1){
				if(row[i-1][j-1]->getType() == 'T' || row[i-1][j-1]->getType() == '#'){
					temp[i][j]->incTempPopulation();
					workers = workers - 1;
					tempPop = tempPop + 1;
					goods = goods - 1;
				}
			}
			if(row[i][j]->getPopulation() == 0 && checkAdjacent(i-1,j) && temp[i][j]->getTempPopulation() == 0 && workers >= 1 && goods >= 1){
				if(row[i-1][j]->getType() == 'T' || row[i-1][j]->getType() == '#'){
					temp[i][j]->incTempPopulation();
					workers = workers - 1;
					tempPop = tempPop + 1;
					goods = goods - 1;
				}
			}
			if(row[i][j]->getPopulation() == 0 && checkAdjacent(i-1,j+1) && temp[i][j]->getTempPopulation() == 0 && workers >= 1 && goods >= 1){
				if(row[i-1][j+1]->getType() == 'T' || row[i-1][j+1]->getType() == '#'){
					temp[i][j]->incTempPopulation();
					workers = workers - 1;
					tempPop = tempPop + 1;
					goods = goods - 1;
				}
			}
			if(row[i][j]->getPopulation() == 0 && checkAdjacent(i,j-1) && temp[i][j]->getTempPopulation() == 0 && workers >= 1 && goods >= 1){
				if(row[i][j-1]->getType() == 'T' || row[i][j-1]->getType() == '#'){
					temp[i][j]->incTempPopulation();
					workers = workers - 1;
					tempPop = tempPop + 1;
					goods = goods - 1;
				}
			}
			if(row[i][j]->getPopulation() == 0 && checkAdjacent(i,j+1) && temp[i][j]->getTempPopulation() == 0 && workers >= 1 && goods >= 1){
				if(row[i][j+1]->getType() == 'T' || row[i][j+1]->getType() == '#'){
					temp[i][j]->incTempPopulation();
					workers = workers - 1;
					tempPop = tempPop + 1;
					goods = goods - 1;
				}
			}
			if(row[i][j]->getPopulation() == 0 && checkAdjacent(i+1,j-1) && temp[i][j]->getTempPopulation() == 0 && workers >= 1 && goods >= 1){
				if(row[i+1][j-1]->getType() == 'T' || row[i+1][j-1]->getType() == '#'){
					temp[i][j]->incTempPopulation();
					workers = workers - 1;
					tempPop = tempPop + 1;
					goods = goods - 1;
				}
			}
			if(row[i][j]->getPopulation() == 0 && checkAdjacent(i+1,j) && temp[i][j]->getTempPopulation() == 0 && workers >= 1 && goods >= 1){
				if(row[i+1][j]->getType() == 'T' || row[i+1][j]->getType() == '#'){
					temp[i][j]->incTempPopulation();
					workers = workers - 1;
					tempPop = tempPop + 1;
					goods = goods - 1;
				}
			}
			if(row[i][j]->getPopulation() == 0 && checkAdjacent(i+1,j+1) && temp[i][j]->getTempPopulation() == 0 && workers >= 1 && goods >= 1){
				if(row[i+1][j+1]->getType() == 'T' || row[i+1][j+1]->getType() == '#'){
					temp[i][j]->incTempPopulation();
					workers = workers - 1;
					tempPop = tempPop + 1;
					goods = goods - 1;
				}
			}
		}	
		if(commercialPopulation > 0){
						if(temp[i][j]->getPopulation() == 1 && countAdjacentPop(i, j, 1) >= 2 && workers >= 1 && goods >= 1){
				temp[i][j]->incTempPopulation();
				workers = workers - 1;
				tempPop = tempPop + 1;
				goods = goods - 1;
			}
			if(temp[i][j]->getPopulation() == 0 && countAdjacentPop(i, j, 1) >= 1 && workers >= 1 && goods >= 1){
				temp[i][j]->incTempPopulation();
				workers = workers - 1;
				tempPop = tempPop + 1;
				goods = goods - 1;
			}

		}
	}
	row = temp;
	for(int i = 0; i < row.size(); i++){
		for(int j = 0; j < row[i].size(); j++){
			if(row[i][j]->getType() == 'C'){
				row[i][j]->setPopulation(temp[i][j]->getTempPopulation());
			}
		}
	}
	commercialPopulation = tempPop;
	if(updateCheck == row){
		updatedC = false;
	}
}

void initialize::printDesiredArea(int x1, int y1, int x2, int y2)
{
	int rPop = 0, iPop = 0, cPop = 0, areaPollution = 0;

	for(int i = x1; i < (x2+1); i++)											//for loop to iterate through desired region
	{
		for(int j = y1; j < (y2+1); j++)
		{
			if(row[i][j]->getType() == 'R')										//check for residential
			{
				rPop += row[i][j]->getPopulation();
			}
			if(row[i][j]->getType() == 'I')										//check for industrial
			{
				iPop += row[i][j]->getPopulation();
			}
			if(row[i][j]->getType() == 'C')										//check for commercial
			{
				cPop += row[i][j]->getPopulation();
			}
			areaPollution = areaPollution + row[i][j]->getPollution();
		}
	}
	//print out total results in the desired area
	cout << "The total populations for the requested area are:" << endl << "Residential: " << rPop << endl << "Industrial: " << iPop << endl << "Commercial: " << cPop << endl;
	cout << "The total amount of pollution for the requested area is " << areaPollution << " units" << endl;
}

void initialize::printTotalPopulations(){
	cout << "The total populations for the region are:" << endl;
	cout << "Residential: " << residentialPopulation << endl;
	cout << "Industrial: " << industrialPopulation << endl;
	cout << "Commercial: " << commercialPopulation << endl;
}

void initialize::setUpdated(bool resetUpdated){
	updatedR = resetUpdated;
	updatedI = resetUpdated;
	updatedC = resetUpdated;
}

bool initialize::getUpdatedR(){
	return updatedR;
}

bool initialize::getUpdatedI(){
	return updatedI;
}

bool initialize::getUpdatedC(){
	return updatedC;
}

void initialize::updatePollution(){
	for(int i = 0; i < row.size(); i++){
		for(int j = 0; j < row[i].size(); j++){
			if(row[i][j]->getType() == 'I'){	//updates all cells adjacent to industrial cells
				if(row[i][j]->getPollution() > 1){
					if(checkAdjacent(i-1, j-1) && row[i-1][j-1]->getPollution() < row[i][j]->getPollution()){
						row[i-1][j-1]->setPollution(row[i][j]->getPollution() - 1);
					}
					if(checkAdjacent(i-1, j) && row[i-1][j]->getPollution() < row[i][j]->getPollution()){
						row[i-1][j]->setPollution(row[i][j]->getPollution() - 1);
					}
					if(checkAdjacent(i-1, j+1) && row[i-1][j+1]->getPollution() < row[i][j]->getPollution()){
						row[i-1][j+1]->setPollution(row[i][j]->getPollution() - 1);
					}
					if(checkAdjacent(i, j-1) && row[i][j-1]->getPollution() < row[i][j]->getPollution()){
						row[i][j-1]->setPollution(row[i][j]->getPollution() - 1);
					}
					if(checkAdjacent(i, j+1) && row[i][j+1]->getPollution() < row[i][j]->getPollution()){
						row[i][j+1]->setPollution(row[i][j]->getPollution() - 1);
					}
					if(checkAdjacent(i+1, j-1) && row[i+1][j-1]->getPollution() < row[i][j]->getPollution()){
						row[i+1][j-1]->setPollution(row[i][j]->getPollution() - 1);
					}
					if(checkAdjacent(i+1, j) && row[i+1][j]->getPollution() < row[i][j]->getPollution()){
						row[i+1][j]->setPollution(row[i][j]->getPollution() - 1);
					}
					if(checkAdjacent(i+1, j+1) && row[i+1][j+1]->getPollution() < row[i][j]->getPollution()){
						row[i+1][j+1]->setPollution(row[i][j]->getPollution() - 1);
					}
				}
			}
		}
	}
}

void initialize::printPollution(){	//prints layout the of pollution values												
	cout << "Pollution" << endl;
    for(int k = 0; k < row.size(); k++){cout << "--";}													
    cout << endl;
    for(int i = 0; i < row.size(); i++){																
        for(int j = 0; j < row[i].size(); j++){															
            if(j == 0){cout << "|";}																	
			cout << row[i][j]->getPollution() << " ";
			if(j == row[i].size() - 1){cout << "|";}
        }
        if(i != row.size() - 1){cout << endl;}															
    }
    for(int k = 0; k < row.size(); k++){cout << "--";}													
    cout << endl;
}

int initialize::totalPollution(){	//calculates pollution for all cells
	int totalPollution = 0;
	for(int i = 0; i < row.size(); i++){
		for(int j = 0; j < row[i].size(); j++){
			totalPollution = totalPollution + row[i][j]->getPollution();
		}
	}
	return totalPollution;
}









































