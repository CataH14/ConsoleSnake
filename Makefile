construct : app.o ui.o tabla.o bloc.o
	g++ -Wall -o snake app.o ui.o tabla.o bloc.o -lncurses -pthread -O3

app.o : app.cpp tabla.h ui.h 
	g++ -c app.cpp

ui.o : ui.cpp tabla.h bloc.h ui.h
	g++ -c ui.cpp

tabla.o : tabla.cpp tabla.h bloc.h
	g++ -c tabla.cpp

bloc.o : bloc.cpp bloc.h
	g++ -c bloc.cpp

clean : 
	rm app.o ui.o tabla.o bloc.o