//CONTAGION - CSCE2110.201 - Group 10
#ifndef ANALYSIS_H
#define ANALYSIS_H

using namespace std;

class analysis{
public:
	analysis();
	analysis(int maxInf, int maxDay, int totalInfected, int lastDay);
	
	void setPeakInf(int maxInf);
	int getPeakInf();
	
	void setPeakDay(int maxDay);
	int getPeakDay();
	
	void setTotalInf(int totalInfected);
	int getTotalInf();
	
	void setEndDay(int lastDay);
	int getEndDay();

private:
	int peakInf;
	int peakDay;
	int totalInf;
	int endDay;
};

#endif