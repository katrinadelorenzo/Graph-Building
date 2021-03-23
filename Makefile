all: graphLabTest graphLab

graphLabTest: Graph.o Graph_driver.o
	g++ -o graphLabTest Graph.o Graph_driver.o

graphLab: Graph.o Graph_driver_file.o
	g++ -o graphLab Graph.o Graph_driver_file.o


wordCnt: unordered_map.cpp
	g++ -o wordCnt unordered_map.cpp

Graph.o: Graph.cpp Graph.h
	g++ -c Graph.cpp

Graph_driver.o: Graph_driver.cpp Graph.h
	g++ -c Graph_driver.cpp

Graph_driver_file.o: Graph_driver_file.cpp Graph.h
	g++ -c Graph_driver_file.cpp


clean: 
	rm *.o graphLab

