#ifndef BLOC_H
#define BLOC_H

class Poz{
	public:
		int y;		//vertical
		int x;		//horizontal
		
		Poz(int y, int x) : x(x), y(y){}
		Poz(const Poz& ot) : x(ot.x), y(ot.y){}
		Poz(){}
};

class Block{
	private:
		int x, y;
		char type;
		//# wall
		//O food
		//Q snake
		//x snake
		//  empty
		
	public:
		Block(int y, int x, char type) : x(x), y(y), type(type){}
		
		char get_type() const;
		
		Poz get_poz() const;
		
		void set_type(char new_type);
		
		~Block(){}
};

#endif