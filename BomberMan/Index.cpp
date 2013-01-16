//#pragma comment (lib, "kernel32.lib")
#include <math.h>

//#include "OBJECT.h"
#include "PROCESS.h"

#include <vector>
#include <time.h>
using namespace std;
#include <conio.h>

#include <GL\glut.h>

float WinWid = 400.0;
float WinHei = 400.0;
float Angle=0.0, Scale = 1.0;

void Draw(){
	glClear(GL_COLOR_BUFFER_BIT);
	glPushMatrix();
	Scale = 1.0 - abs(sin(3.14*Angle/90.0)/sqrt(3.0)/2);
	glRotatef(Angle, 0.0, 0.0, 1.0);
	glScalef(Scale, Scale, 1);
	glBegin(GL_LINES);
		for(float i = -WinWid/2; i <= WinWid/2; i += 20.0){
			glVertex2f(i, -WinHei/2);
			glVertex2f(i, WinHei/2);
		}
		for(float i = -WinHei/2; i <= WinHei/2; i += 20.0){
			glVertex2f(-WinWid/2, i);
			glVertex2f(WinWid/2, i);
		}
	glEnd();
	glPopMatrix();
	glutSwapBuffers();
}

void Timer(int value){
	/*switch (value){
	case 0: glColor3f(1.0, 1.0, 1.0);
		break;
	case 1: glColor3f(1.0, 0.0, 0.0);
		break;
	}*/
	//Draw();
	glutPostRedisplay();
	glutTimerFunc(50, Timer, 0);
}

void Keyboard(unsigned char  key, int x, int y){
	switch(key){
	case 'a': Angle++;
		break;
	case 'd': Angle--;
		break;
	}
}
void SKeyboard(int key, int x, int y){
	switch(key){
	case GLUT_KEY_LEFT: Angle++;
		break;
	case GLUT_KEY_RIGHT: Angle--;
		break;
	}
}

void Initialize(){
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-WinWid/2, WinWid/2, -WinHei/2, WinHei/2, -200.0, 200.0 );
	glMatrixMode(GL_MODELVIEW);
}

/*void cursor_to_global( SHORT yPos, SHORT xPos ){
	COORD curPos;
	curPos.X = xPos;
	curPos.Y = yPos;
	SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), curPos );
}

void cursor_to( SHORT yPos, SHORT xPos ){
	CONSOLE_SCREEN_BUFFER_INFO sbi;
	GetConsoleScreenBufferInfo( GetStdHandle(STD_OUTPUT_HANDLE), &sbi );
	COORD curPos;
	curPos.X = sbi.dwCursorPosition.X + xPos;
	curPos.Y = sbi.dwCursorPosition.Y + yPos;
	SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), curPos );
}

void setColor(int textcolor, int backcolor) { 
	WORD wAttributes = ((unsigned int) backcolor << 4) | (unsigned int) textcolor; 
	SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), wAttributes); 
}
*/

//typedef BOOL (WINAPI * LPSetConsoleFont)(HANDLE,DWORD);

int main(int argc, char** argv){
	//srand( time(0) );
	
	/*LPSetConsoleFont SetConsoleFont = reinterpret_cast<LPSetConsoleFont>(GetProcAddress(GetModuleHandle("kernel32.dll"), "SetConsoleFont"));
    SetConsoleFont(GetStdHandle(STD_OUTPUT_HANDLE),0);
	SetWindowPos( GetForegroundWindow(), 0, 20, 20, 0, 0, SWP_SHOWWINDOW );
	system("mode con cols=320 lines=110");*/
    
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); 
	glutInitWindowSize( 800.0, 450.0 );
	glutInitWindowPosition( 100.0, 100.0 );
	glutCreateWindow("Lesson 4");
	glutDisplayFunc(Draw);
	
	glutTimerFunc(500, Timer, 0);
	glutKeyboardFunc(Keyboard);
	glutSpecialFunc(SKeyboard);
	Initialize();
	glutMainLoop();

	PROCESS *area = new PROCESS;
	area->GetObject( "PLAYER", 0, "" );
	area->GetObject( "BLOCK", 2, "NO_RANDOM" );
	area->GetObject( "BRICK", 100, "RANDOM" );
	area->GetObject( "MONSTER_1", 5, "RANDOM" );
	area->Print();

	/*int time = 0;
	vector< pair< int, int > > bomba;
	while( 1 ) {
		for( int i = 0; i < area->bomb.size(); i++ ){
			area->bomb[i]->setTimer();
			if( area->bomb[i]->getTimer() == 0 ){
				area->bangBomb( i );
			}
		}
		time++;
		if( time > 9999999 ) time = 0; 
		Sleep( 100 );
		if (_kbhit())
		{
			int key = getch();
			if ( key == 32 ) { area->push_bomb(); }
			if ( key == 27 ) { return 1; }

  			if( key == 224 ){
				key = getch();

                switch(key){
                case 72:{ area->player_move_to( -1, 0 ); break;}
                case 80:{ area->player_move_to( 1, 0 ); break;}
                case 75:{ area->player_move_to( 0, -1 ); break;}
                case 77:{ area->player_move_to( 0, 1 ); break;}
                default:{ break;}
                }
			}
		}
		if( time % 5 == 0 ) area->moobs_move_to();
	}*/
	return 0;
}