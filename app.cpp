#include "ui.h"
#include "tabla.h"

#include <vector>
#include <string>
#include <iostream>

#define ROWS 30
#define COLS 30
#define SPEED 2	

int main(int argc, char* argv[]){
	int rows = ROWS;
	int cols = COLS;
	float speed = SPEED;
	string numef;
	
	//pun argumentele intr-un vector de stringuri pentru manipulare mai usoara
	std::vector<std::string> args(argv + 1, argv + argc);
	for(auto i = args.begin(); i != args.end(); i++){
		//for simplu pentru a putea accesa parametrii direct si pentru a putea sari
		if(*i == "-r" || *i == "--rows"){
			i++;
			if(i != args.end())
				rows = atoi(i->c_str());

			if(rows < 9)
				rows = ROWS;
		}
		else if(*i == "-c" || *i == "--columns"){
			i++;
			if(i != args.end())
				cols = atoi(i->c_str());

			if(cols < 9)
				cols = COLS;
		}
		else if(*i == "-s" || *i == "--speed"){
			i++;
			if(i != args.end())
				speed = atof(i->c_str());

			if(speed < 1 || speed > 1000)
				speed = SPEED;
		}
		else if(*i == "-m" || *i == "--map"){
			i++;
			if(i != args.end())
				numef = *i;
		}
		else if(*i == "--help" || *i == "-h"){
			std::cout << "Help:\n";
			std::cout << "-h   --help                show this menu\n";
			std::cout << "-r   --rows                specify the number of rows. Greater than 1\n";
			std::cout << "-c   --columns             specify the number of columns. Greater than 1\n";
			std::cout << "-s   --speed               specify the game speed(spaces/second)\n";
			std::cout << "-m   --map                 specify the ASCII text file for the maze\n";
			std::cout << "\n\n move using WASD\n";
			std::cout << "q - quit\n";
			std::cout << "r - restart\n";
			std::cout << "p - pause\n";
			return 0;
		}
		else{
			std::cout << "Unknown argument: "<< *i << "\n";
			return 0;
		}
	}
	
	
	Tabla t{rows, cols, numef};
	UI ui{t, speed};
	
	ui.run();
	
	return 0;
}