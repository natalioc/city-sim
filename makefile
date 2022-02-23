SimCity: main.o initialize.o celldata.o simulation.o
	g++ main.o initialize.o celldata.o simulation.o -o SimCity
	
main.o: main.cpp
	g++ -c main.cpp
	
initialize.o: initialize.cpp
	g++ -c initialize.cpp
	
celldata.o: celldata.cpp
	g++ -c celldata.cpp
	
simulation.o: simulation.cpp
	g++ -c simulation.cpp

clean:
	rm *.o SimCity
