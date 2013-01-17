#include "OBJECT.h"

OBJECT::OBJECT( int y, int x ){
	setPos( y, x );
}
void OBJECT::setPos( int y, int x ){
	position.first = y;
	position.second = x;
}

pair< int, int > OBJECT::getPos(){
	return position;
}

BLOCK::BLOCK( int y, int x ){
	setPos( y, x );
}
void BLOCK::Draw(){
	glColor3f(0.7, 0.7, 0.7);
	glBegin(GL_QUADS);	
		glVertex2f(-area_w*ob_size/2 + position.second*ob_size, area_h*ob_size/2 - position.first*ob_size);
		glVertex2f(-area_w*ob_size/2 + position.second*ob_size, area_h*ob_size/2 - position.first*ob_size - ob_size);
		glVertex2f(-area_w*ob_size/2 + position.second*ob_size + ob_size, area_h*ob_size/2 - position.first*ob_size - ob_size);
		glVertex2f(-area_w*ob_size/2 + position.second*ob_size + ob_size, area_h*ob_size/2 - position.first*ob_size);
	glEnd();
}

BRICK::BRICK( int y, int x ){
	setPos( y, x );
}
void BRICK::Draw(){
	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_LINES);	
		glVertex2f(-area_w*ob_size/2 + position.second*ob_size, area_h*ob_size/2 - position.first*ob_size);
		glVertex2f(-area_w*ob_size/2 + position.second*ob_size + ob_size, area_h*ob_size/2 - position.first*ob_size - ob_size);
		glVertex2f(-area_w*ob_size/2 + position.second*ob_size, area_h*ob_size/2 - position.first*ob_size - ob_size);
		glVertex2f(-area_w*ob_size/2 + position.second*ob_size + ob_size , area_h*ob_size/2 - position.first*ob_size);
	glEnd();
}

PLAYER::PLAYER( int y, int x ){
	setPos( y, x );
}
void PLAYER::Draw(){
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_LINES);	
		glVertex2f(-area_w*ob_size/2 + position.second*ob_size, area_h*ob_size/2 - position.first*ob_size);
		glVertex2f(-area_w*ob_size/2 + position.second*ob_size + ob_size/2, area_h*ob_size/2 - position.first*ob_size - ob_size);
		glVertex2f(-area_w*ob_size/2 + position.second*ob_size + ob_size/2, area_h*ob_size/2 - position.first*ob_size - ob_size);
		glVertex2f(-area_w*ob_size/2 + position.second*ob_size + ob_size, area_h*ob_size/2 - position.first*ob_size);
	glEnd();
}
BOMB::BOMB( int x, int y ){
	timer = 50;
	setPos( x, y );
}
int BOMB::getTimer(){
	return timer;
}
void BOMB::setTimer(){
	timer--;
}
void BOMB::Draw(){	
	glColor3f(0.0, 1.0, 1.0);
	glBegin(GL_QUADS);	
		glVertex2f(-area_w*ob_size/2 + position.second*ob_size, area_h*ob_size/2 - position.first*ob_size);
		glVertex2f(-area_w*ob_size/2 + position.second*ob_size, area_h*ob_size/2 - position.first*ob_size - ob_size);
		glVertex2f(-area_w*ob_size/2 + position.second*ob_size + ob_size, area_h*ob_size/2 - position.first*ob_size - ob_size);
		glVertex2f(-area_w*ob_size/2 + position.second*ob_size + ob_size, area_h*ob_size/2 - position.first*ob_size);
	glEnd();
}

FIRE::FIRE( int x, int y ){
	setPos( x, y );
}
void FIRE::Draw(){		
	glColor3f(1.0, 1.0, 0.0);
	glBegin(GL_QUADS);	
		glVertex2f(-area_w*ob_size/2 + position.second*ob_size, area_h*ob_size/2 - position.first*ob_size);
		glVertex2f(-area_w*ob_size/2 + position.second*ob_size, area_h*ob_size/2 - position.first*ob_size - ob_size);
		glVertex2f(-area_w*ob_size/2 + position.second*ob_size + ob_size, area_h*ob_size/2 - position.first*ob_size - ob_size);
		glVertex2f(-area_w*ob_size/2 + position.second*ob_size + ob_size, area_h*ob_size/2 - position.first*ob_size);
	glEnd();
}

MONSTER_1::MONSTER_1( int y, int x ){
	setPos( y, x );
}
void MONSTER_1::Draw(){
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_QUADS);	
		glVertex2f(-area_w*ob_size/2 + position.second*ob_size, area_h*ob_size/2 - position.first*ob_size);
		glVertex2f(-area_w*ob_size/2 + position.second*ob_size, area_h*ob_size/2 - position.first*ob_size - ob_size);
		glVertex2f(-area_w*ob_size/2 + position.second*ob_size + ob_size, area_h*ob_size/2 - position.first*ob_size - ob_size);
		glVertex2f(-area_w*ob_size/2 + position.second*ob_size + ob_size, area_h*ob_size/2 - position.first*ob_size);
	glEnd();
}