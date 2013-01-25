#include <time.h>
#include "SERVICE.h"
#include "PROCESS.h"

static jmp_buf env;
PROCESS *game;
PLAYER *play;
bool flag_start = false;
int level = 1;

void Draw(){
	glClear(GL_COLOR_BUFFER_BIT);
	if( !flag_start ) {
		game = new PROCESS;
		flag_start = game->LevelGenerate( level );
	}
	game->Print();
	game->BombTime();
	game->MoveMoobs();
	game->DestroyFire();
	glutSwapBuffers();	
	if( game->GameOver() ) {
		game->Restart();
	}
	if( game->WinLevel() ) {
		glClearColor(0.1, 0.4, 0.1, 1.0);
		glutPostRedisplay();
		glLoadIdentity();
		glClear(GL_COLOR_BUFFER_BIT);
		Sleep(1000);
		flag_start = false;
		level++;
		delete game;
	}
 }

void Timer(int value){
	glutPostRedisplay();
	glutTimerFunc(50, Timer, 0);
}

void Keyboard(unsigned char  key, int x, int y){
	switch(key){
	case 32: game->PushBomb( 0 );
		break;
	}
}
void SKeyboard(int key, int x, int y){
	switch(key){
	case GLUT_KEY_LEFT: game->MovePlayer( "LEFT" ); break;
	case GLUT_KEY_RIGHT: game->MovePlayer( "RIGHT" ); break;
	case GLUT_KEY_UP: game->MovePlayer( "UP" ); break;
	case GLUT_KEY_DOWN: game->MovePlayer( "DOWN" ); break;
	}
}
void Initialize(){
	glClearColor(0.1, 0.4, 0.1, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho( -ob_size*area_w/2, ob_size*area_w/2,-ob_size*area_h/2, ob_size*area_h/2, -200.0, 200.0);
	glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv){
	srand( time(0) );
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); 
	glutInitWindowSize( ob_size * area_w, ob_size * area_h );
	glutInitWindowPosition( 50.0, 50.0 );
	glutCreateWindow("Bomberman with OpenGl");

	while( 1 ){
		setjmp(env);
		
		glutDisplayFunc(Draw);	
		glutTimerFunc(500, Timer, 0);
		glutKeyboardFunc(Keyboard);
		glutSpecialFunc(SKeyboard);
		Initialize();
		
		glutMainLoop();
		
		game->~PROCESS();
	}
	return 0;
}