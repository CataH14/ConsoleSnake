#ifndef UI_H
#define UI_H

#include <ncurses.h>
#include <unistd.h>
#include <vector>
#include <string>

#include <thread>
#include <mutex>
#include <chrono>

#include "tabla.h"
#include "bloc.h"

using std::vector;
using std::string;
using std::chrono::time_point;
using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::microseconds;


class UI;
void input(UI* ui);

class UI{
	friend void input(UI*);
	
	private:
		WINDOW * wnd;
		WINDOW * wscore;
		
		time_point<high_resolution_clock> start, stop;
		
		std::mutex mtx_pause;
		
		vector<Block> to_modif;
		
		int rows, cols;
	
		bool quit, over, pause, restart;
		
		int spb;
	
		Tabla& tabla;
		void logic();
		
		void show();
		
		void modify();
		
		void change(Block& b);
		
		void game_over();
		
		void show_score();
		
		void restart_all();
		
		void sync();
		
	public:
		UI(Tabla& t, float speed);
		
		~UI();
		
		void run();
};

#endif