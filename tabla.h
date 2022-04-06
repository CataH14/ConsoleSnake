#ifndef TABLA_H
#define TABLA_H

#define UP        0
#define RIGHT     1
#define DOWN      2
#define LEFT      3
#define MAX_INPUT 3

#include "bloc.h"
#include <vector>
#include <string>
#include <queue>
#include <list>
#include <stdlib.h>
#include <time.h>
#include <fstream>

#include <mutex>

using std::vector;
using std::string;
using std::queue;
using std::list;

class Tabla{
	private:
		bool pity_turn;
		int rows, cols;
		vector<vector<Block>> field;
		vector<Block> modified;
		queue<Block*> snake;
		string numef;
		
		std::mutex mtx_dir;
		
		int score;
		
		list<int> direction;
		int curent_dir;
		
		//0 	up
		//1		right
		//2		down
		//3		left
		Poz head, next;
		
		void init();
		void f_init();
		bool move_snake();
		Block* move_fruit();
	
	public:
		Tabla(int rows, int cols, const string& numef);
		~Tabla(){}
		
		//returneaza true daca jocul continua false altfel
		bool move();
		
		vector<string> get_all() const; 
		
		void set_direction(int d);
		
		int get_direction() const;

		int get_rows() const;
		
		int get_cols() const;
		
		int get_score() const;
		
		const vector<Block>& get_modified() const;
		
		void restart();
		
};

#endif