#include "tabla.h"

void Tabla::init(){
	for(int i = 0; i < rows; i++){
		field.push_back(vector<Block>{});
		for(int j = 0; j < cols; j++){
			field[i].push_back(Block(i, j, ' '));
		}
	}
}

void Tabla::f_init(){
	std::ifstream fin(numef);
	fin >> rows >> cols;
	string buf;
	fin >> buf;
	getline(fin, buf);
	
	for(int i = 0; i < rows; i++){
		field.push_back(vector<Block>{});
		getline(fin, buf);
		for(int j = 0; j < cols; j++){
			field[i].push_back(Block(i, j, buf.at(j + 1)));
		}
	}
	
	fin.close();
}

void Tabla::restart(){
	pity_turn = true;
	field.clear();
	direction.clear();
	snake = queue<Block*>{};
	
	if(numef.size() == 0)
		init();
	else
		f_init();
	
	snake.push(&field[rows/2][cols/2 - 2]);
	snake.push(&field[rows/2][cols/2 - 1]);
	
	head.y = rows/2;
	head.x = cols/2 - 1;
	
	move_fruit();
	
	score = 0;
	
	curent_dir = 1;
}

Tabla::Tabla(int rows, int cols, const string& numef) : rows(rows), cols(cols), numef(numef){
	srand(time(NULL));
	restart();
}

vector<string> Tabla::get_all() const{
	vector<string> res;
	
	for(int i = 0; i < rows; i++){
		res.push_back(string{});
		for(int j = 0; j < cols; j++){
			res[i].push_back(field[i][j].get_type());
			res[i].push_back(' ');
		}
	}
	
	return res;
}

int Tabla::get_rows() const{
	return rows;
}

int Tabla::get_cols() const{
	return cols;
}

int Tabla::get_direction() const{
	return direction.front();
}

void Tabla::set_direction(int d){
	mtx_dir.lock();

	if(direction.size() == 0){
		if(d != curent_dir && (d + 2) % 4 != curent_dir)
			direction.emplace_back(d);
	}
	else if(direction.size() < MAX_INPUT && d != direction.back() && (d + 2) % 4 != direction.back())
		direction.emplace_back(d);

	mtx_dir.unlock();
}

int Tabla::get_score() const{
	return score;
}

bool Tabla::move(){
	bool cont;
	
	mtx_dir.lock();
	if(direction.size() >= 1){
		curent_dir = direction.front();
		direction.erase(direction.begin());
	}
	mtx_dir.unlock();
	
	switch(curent_dir){
		case 0:
			next.y = (head.y - 1 + rows) % rows;
			next.x = head.x;
			
			cont = move_snake();
			break;
			
		case 1:
			next.x = (head.x + 1 + cols) % cols;
			next.y = head.y;
			
			cont = move_snake();
			break;
			
		case 2:
			next.y = (head.y + 1 + rows) % rows;
			next.x = head.x;
			
			cont = move_snake();
			break;
			
		case 3:
			next.x = (head.x - 1 + cols) % cols;
			next.y = head.y;
			
			cont = move_snake();
			break;
			
		default:
			break;
	}
	
	return cont;
}

bool Tabla::move_snake(){
	modified.clear();
	Block* removed;
	
	char tip_next = field[next.y][next.x].get_type();
	
	switch(tip_next){
		case ' ':
			head = next;
			field[head.y][head.x].set_type('x');
			snake.push(&field[head.y][head.x]);
			modified.push_back(field[head.y][head.x]);
			
			removed = snake.front();
			snake.pop();
			removed->set_type(' ');
			modified.push_back(*removed);
			
			pity_turn = true;
			return true;
			
		case 'o':
			head = next;
			field[head.y][head.x].set_type('O');
			snake.push(&field[head.y][head.x]);
			modified.push_back(field[head.y][head.x]);
			
			removed = move_fruit();
			modified.push_back(*removed);
			
			pity_turn = true;
			score++;
			return true;
			
		default:
			if(pity_turn){
				pity_turn = false;
				return true;
			}
			return false;
	}
	return false;
}

const vector<Block>& Tabla::get_modified() const {
	return modified;
}

Block* Tabla::move_fruit(){
	bool ok = false;
	int y;
	int x;
	
	while(!ok){
		y = rand()%rows;
		x = rand()%cols;
		
		if(field[y][x].get_type() == ' ')
			ok = true;
	}
	
	field[y][x].set_type('o');
	return &field[y][x];
}








