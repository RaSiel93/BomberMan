#include <time.h>
#include "SERVICE.h"
#include "PROCESS.h"
#include <setjmp.h>

static jmp_buf env;
PROCESS *game;
PLAYER *play;

void Draw(){
	glClear(GL_COLOR_BUFFER_BIT);
	game->GameProcess();
	glutSwapBuffers();
	game->GameOver();
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

	game = new PROCESS;

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