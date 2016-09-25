taxi.out: TaxiMain.o Dispatcher.o Taxi.o Graph.o
	g++ -o taxi.out TaxiMain.o Dispatcher.o Taxi.o Graph.o

TaxiMain.o: TaxiMain.cpp Dispatcher.h
	g++ -c TaxiMain.cpp

Dispatcher.o: Dispatcher.cpp Dispatcher.h Taxi.h
	g++ -c Dispatcher.cpp

Taxi.o: Taxi.cpp Taxi.h Graph.h
	g++ -c Taxi.cpp

Graph.o: Graph.cpp Graph.h
	g++ -c Graph.cpp

clean:
	rm *.o *.out *.exe *.stackdump
