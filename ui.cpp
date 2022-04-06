#include "ui.h"

void UI::run(){
	std::thread input_thr(input, this);
	
	//main game loop
	while(!quit){
		logic();
		modify();
		sync();
	}
	
	input_thr.join();
}

UI::UI(Tabla& t, float speed) : tabla(t), spb(1000000/speed){
	quit = false;
	over = false;
	pause = false;
	restart = false;
	
	initscr();
	
	rows = tabla.get_rows() + 2;
	cols = tabla.get_cols() * 2 + 2;
	
	int xMax, yMax;
	getmaxyx(stdscr, yMax, xMax);
	
	wnd = newwin(rows, cols , 0, (xMax - cols) / 2);
	wscore = newwin(1, 20, rows + 1, (xMax - cols) / 2);
	refresh();
	
	noecho();
	cbreak();
	
	nodelay(wnd, true);
	
	show();
	start = high_resolution_clock::now();
}

UI::~UI(){
	endwin();
}

void UI::logic(){
	if(restart)
		restart_all();
	
	else if(!over){
		over = !tabla.move();
		to_modif = tabla.get_modified();
		if(over)
			game_over();
	}
}

void UI::game_over(){
	wmove(wnd, rows / 2, cols / 2 - 4);
	wprintw(wnd, "GAME OVER");
	wmove(wnd, 0, 0);
}

void UI::modify(){
	for(auto& b : to_modif)
		change(b);
	
	show_score();
	
	wmove(wnd, 0, 0);
	wrefresh(wnd);
}

void UI::change(Block& b){
	mvwprintw(wnd, b.get_poz().y + 1, b.get_poz().x * 2 + 1, "%c", b.get_type());
}

void UI::show(){
	wclear(wnd);
	vector<string> v = tabla.get_all();
	for(int i = 0; i < v.size(); i++){
		mvwprintw(wnd, i + 1, 1, "%s", v[i].c_str());
	}
	box(wnd, 0, 0);
	wrefresh(wnd);
	
	show_score();
	
	wmove(wnd, 0, 0);
}

void UI::show_score(){
	mvwprintw(wscore, 0, 0, "Score: %10d", tabla.get_score());
	wrefresh(wscore);
}

void UI::restart_all(){
	quit = false;
	over = false;
	pause = false;
	restart = false;
	
	tabla.restart();
	to_modif.clear();
	
	show();
}

//adauga o intarziere in afisare in funtie de
//diferenta de timp dintre durata unui cadru si durata de procesare a cadrului curent
//pentru a mentine viteza jocului constanta
//start trebuie sa fie initializat !!!
void UI::sync(){
	stop = high_resolution_clock::now();
	auto elapsed = duration_cast<microseconds>(stop - start);
	
	if(spb - elapsed.count() > 0)
		usleep(spb - elapsed.count());
	
	mtx_pause.lock();
	mtx_pause.unlock();
	
	start = high_resolution_clock::now();
}

void input(UI* ui){
	while(!ui->quit){
		int cmd = getch();

		switch(cmd){
			case 'w':
			    if(!ui->pause)
					ui->tabla.set_direction(UP);
				break;
				
			case 'd':
				if(!ui->pause)
					ui->tabla.set_direction(RIGHT);
				break;
				
			case 's':
				if(!ui->pause)
					ui->tabla.set_direction(DOWN);
				break;
				
			case 'a':
				if(!ui->pause)
					ui->tabla.set_direction(LEFT);
				break;
				
			case 'p':
				if(!ui->pause){
					ui->pause = true;
					ui->mtx_pause.lock();
				}
				else{
					ui->pause = false;
					ui->mtx_pause.unlock();
				}
				break;
			
			case 'r':
				ui->restart = true;
				if(ui->pause){
					ui->pause = false;
					ui->mtx_pause.unlock();
				}
				break;
				
			case 'q':
				ui->quit = true;
				if(ui->pause){
					ui->mtx_pause.unlock();
					ui->pause = false;
				}
				break;
		}
	}
}



