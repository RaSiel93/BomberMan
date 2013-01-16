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
void BLOCK::Draw(){/*
	cursor_to_global( position.first * m_height, position.second * m_width );
	setColor( 8, 0 );
	for( int i = 0; i < m_height; i++ ){
		for( int j = 0; j < m_width; j++ )
			cout << rand()%10;
		cursor_to( 1, -m_width );
	}*/
}

BRICK::BRICK( int y, int x ){
	setPos( y, x );
}
void BRICK::Draw(){}

PLAYER::PLAYER( int y, int x ){
	setPos( y, x );
}
void PLAYER::Draw(){}

BOMB::BOMB( int x, int y ){
	timer = 30;
	setPos( x, y );
}
int BOMB::getTimer(){
	return timer;
}
void BOMB::setTimer(){
	timer--;
}
void BOMB::Draw(){	/*	
	setColor( 15, 0 );
	cursor_to_global( position.first * m_height, position.second * m_width );
	cout<<"         ";cursor_to( 1, -m_width );
	cout<<"         ";cursor_to( 1, -m_width );
	cout<<"    OOOO ";cursor_to( 1, -m_width );
	cout<<"   OOOOOO";cursor_to( 1, -m_width );
	cout<<"   OOOOOO";cursor_to( 1, -m_width );
	cout<<"   OOOOOO";cursor_to( 1, -m_width );
	cout<<"    OOOO ";
	setColor( 6, 0 );
	cursor_to( -5, -m_width + 1 );
	cout<<"~~";
	cursor_to( 1, 0 );
	cout<<"~";
	setColor( 12, 0 );
	cursor_to( 0, -4 );
	cout<<"~";
	/*for( int i = 0; i < m_height; i++ ){
		for( int j = 0; j < m_width; j++ )
			cout << rand()%10;
		cursor_to( 1, -m_width );
	}*/
}

FIRE::FIRE( int x, int y ){
	setPos( x, y );
}
void FIRE::Draw(){		
	//setColor( 12, 0 );
	//cursor_to_global( position.first * m_height, position.second * m_width );
	for( int i = 0; i < object_h; i++ ){
		for( int j = 0; j < object_w; j++ )
			cout << rand()%10;
		//cursor_to( 1, -m_width );
	}
}

MONSTER_1::MONSTER_1( int y, int x ){
	setPos( y, x );
}
void MONSTER_1::Draw(){
	//setColor( 4, 0 );
	//cursor_to_global( position.first * m_height, position.second * m_width );
	for( int i = 0; i < object_h; i++ ){
		for( int j = 0; j < object_w; j++ )
			cout << rand()%10;
		//cursor_to( 1, -m_width );
	}
}