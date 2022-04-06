#include "bloc.h"

char Block::get_type() const{
	return type;
}

Poz Block::get_poz() const {
	return Poz{y, x};
}

void Block::set_type(char new_type){
	type = new_type;
}