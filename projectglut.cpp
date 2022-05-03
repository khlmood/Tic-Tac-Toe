#include <GL/glut.h>
#include <iostream>
#include <string>
#include <math.h>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::to_string;

const float black[] = { 0.0, 0.0, 0.0 };
const float white[] = { 1.1, 1.1, 1.1 };
const float red[] = { 1.0, 0.0, 0.0 };
const float green[] = { 0.0, 1.0, 0.0 };
const float yellow[] = { 1.0, 1.0, 0.0 };
const float blue[] = { 0.0, 0.0, 1.0 };
const float magenta[] = { 1.0, 0.0, 1.0 };

struct player {
	char name[10];
	int score;
	bool win;
};

struct circle {
	float x;
	float y;
	float r;
	bool flag;
};

struct ex {
	float x;
	float y;
	float length;
	bool flag;
};

void cleargrid();
void reshape(int, int);
int grid[3][3];
player p1, p2;
circle c[5];
ex e[5];
circle* cptr;
ex* eptr;
int turn;


void plnames() {
	string n1, n2;
	do {
		cout << "Max character input is 10\n";
		cout << "Input the name of the first player :";
		do {
			if (n1.length() > 11) {
				cout << "Too much characters / try again : ";
			}
			cin >> n1;
		} while (n1.length() > 11);
		cout << "Input the name of the second player :";
		do {
			if (n2.length() > 11) {
				cout << "Too much characters / try again : ";
			}
			cin >> n2;
		} while (n2.length() > 11);
	} while (n1 == n2);
	for (int i = 0; i < 10 && n1[i] != '\0'; i++) {
		p1.name[i] = n1[i];
	}
	for (int i = 0; i < 10 && n2[i] != '\0'; i++) {
		p2.name[i] = n2[i];
	}

	p1.score = 0;
	p2.score = 0;
	turn = 0;
	cleargrid();
}

void displayText(float x, float y, const float color[3], char *string) {
	int j = strlen(string);
	glColor3fv(color);
	glRasterPos2f(x, y);
	for (int i = 0; i < j; i++) {
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, string[i]);
	}
}

string convintstring(int num) {
	string s = to_string(num);
	return s;
}

void drawX(float length, float x, float y) {
	float w, z;
	w = x + length;
	z = y + length;
	glBegin(GL_LINES);
	glVertex2f(x, y);
	glVertex2f(w, z);

	glVertex2f(x, z);
	glVertex2f(w, y);

	glEnd();
}
//the drawO func was copied from stackoverflow
void drawO(float cx, float cy, float r, int num_segments)
{
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < num_segments; i++)
	{
		float theta = 2.0f * 3.1415926f * float(i) / float(num_segments);//get the current angle
		float x = r * cosf(theta);//calculate the x component
		float y = r * sinf(theta);//calculate the y component
		glVertex2f(x + cx, y + cy);//output vertex
	}
	glEnd();
}

void setcirclevalues(circle* c, float x, float y, float r) {
	c->x = x;
	c->y = y;
	c->r = r;
	c->flag = false;
}

void setexvalues(ex* exe, float x, float y, float length) {
	exe->x = x;
	exe->y = y;
	exe->length = length;
	exe->flag = false;
}

void drawextoscreen(ex* exe) {
	drawX(exe->length, exe->x, exe->y);
}

void drawcircletoscreen(circle* c) {
	drawO(c->x, c->y, c->r, 100);
}

void disp2player() {
	//make grid
	glBegin(GL_LINES);

	glVertex2f(-25.0, 45.0);
	glVertex2f(-25.0, -45.0);

	glVertex2f(5.0, 45.0);
	glVertex2f(5.0, -45.0);

	glVertex2f(-55.0, 15.0);
	glVertex2f(35.0, 15.0);

	glVertex2f(-55.0, -15.0);
	glVertex2f(35.0, -15.0);

	glEnd();

	char play1[] = "Player 1:";
	char play2[] = "Player 2:";
	char sc[] = "Score";
	char playe1[] = "P1 :";
	char playe2[] = "P2 :";
	displayText(-70, 70, white, play1);
	displayText(20, 70, white, play2);
	displayText(-40, 70, white, p1.name);
	displayText(50, 70, white, p2.name);
	displayText(50, -10, white, sc);
	displayText(60, -20, white, playe1);
	displayText(60, -30, white, playe2);
	//I can't use the function that display to the screen, it is type int not char*
	//I will convert them and display each char individually
	string sco1 = convintstring(p1.score);
	string sco2 = convintstring(p2.score);
	int sco1x = 73, sco1y = -20;
	for (int i = 0; sco1[i] != '\0'; i++) {
		glColor3fv(white);
		glRasterPos2f(sco1x, sco1y);
		char c = sco1[i];
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, c);
		sco1x += 3;
	}
	int sco2x = 73, sco2y = -30;
	for (int i = 0; sco2[i] != '\0'; i++) {
		glColor3fv(white);
		glRasterPos2f(sco2x, sco2y);
		char c = sco2[i];
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, c);
		sco2x += 3;
	}

	/*if (turn % 2 == 0) {
		glBegin(GL_LINES);
		glVertex2f(-68,65);
		glVertex2f(-50,65);
		glEnd();
	}
	if(turn % 2 == 1) {
		glBegin(GL_LINES);
		glVertex2f(22,65);
		glVertex2f(40,65);
		glEnd();
	}*/

	drawcircletoscreen(&c[0]);
	drawcircletoscreen(&c[1]);
	drawcircletoscreen(&c[2]);
	drawcircletoscreen(&c[3]);
	drawcircletoscreen(&c[4]);

	drawextoscreen(&e[0]);
	drawextoscreen(&e[1]);
	drawextoscreen(&e[2]);
	drawextoscreen(&e[3]);
	drawextoscreen(&e[4]);

	if (e[0].flag == true) {
		if (e[0].y > -30) {
			e[0].y = e[0].y - 5;
			cout << e[0].y<<endl;
			e[0].length = e[0].length+1;
		}
	}

	glutSwapBuffers();
}

//void dispvictory(player p) {
//
//}

bool checkwin() {
	if (grid[0][0] == grid[0][1] && grid[0][0] == grid[0][2] && grid[0][0] != 2 && grid[0][1] != 2 && grid[0][2] != 2)
		return true;
	else if (grid[1][0] == grid[1][1] && grid[1][0] == grid[1][2] && grid[1][0] != 2 && grid[1][1] != 2 && grid[1][2] != 2)
		return true;
	else if (grid[2][0] == grid[2][1] && grid[2][0] == grid[2][2] && grid[2][0] != 2 && grid[2][1] != 2 && grid[2][2] != 2)
		return true;
	else if (grid[0][0] == grid[1][0] && grid[0][0] == grid[2][0] && grid[0][0] != 2 && grid[1][0] != 2 && grid[2][0] != 2)
		return true;
	else if (grid[0][1] == grid[1][1] && grid[0][1] == grid[2][1] && grid[0][1] != 2 && grid[1][1] != 2 && grid[2][1] != 2)
		return true;
	else if (grid[0][2] == grid[1][2] && grid[0][2] == grid[2][2] && grid[0][2] != 2 && grid[1][2] != 2 && grid[2][2] != 2)
		return true;
	else if (grid[0][0] == grid[1][1] && grid[0][0] == grid[2][2] && grid[0][0] != 2 && grid[1][1] != 2 && grid[2][2] != 2)
		return true;
	else if (grid[2][0] == grid[1][1] && grid[2][0] == grid[0][2] && grid[2][0] != 2 && grid[1][1] != 2 && grid[0][2] != 2)
		return true;
	else return false;
}

bool checkdraw() {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (grid[i][j] == 2)
				return false;
		}
	}
	return true;
}

void cleargrid() {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			grid[i][j] = 2;
		}
	}
}

void incrementptr(int num) {
	if (num == 1) {
		eptr->flag = true;
		if (turn != 8) {
			eptr++;
		}
	}
	else {
		cptr->flag = true;
		if (turn != 8) {
			cptr++;
		}
	}
}

void mousecoord(int button, int state, int x, int y) {

	if (button == GLUT_LEFT && state == GLUT_DOWN) {
		int num;
		if (turn % 2 == 0)
			num = 1;
		else
			num = 0;

		if (x >= 141 && x <= 219 && y >= 171 && y <= 245) {
			//square 1
			if (grid[0][0] == 2) {
				grid[0][0] = num;
				cout << grid[0][0] << endl;
				turn++;
				incrementptr(num);
			}
		}
		else if (x >= 229 && x <= 305 && y >= 168 && y <= 243) {
			//square 2
			if (grid[0][1] == 2) {
				grid[0][1] = num;
				cout << grid[0][1] << endl;
				turn++;
				incrementptr(num);
			}
		}
		else if (x >= 321 && x <= 389 && y >= 168 && y <= 243) {
			//square 3
			if (grid[0][2] == 2) {
				grid[0][2] = num;
				cout << grid[0][2] << endl;
				turn++;
				incrementptr(num);
			}
		}
		else if (x >= 139 && x <= 217 && y >= 261 && y <= 334) {
			//square 4
			if (grid[1][0] == 2) {
				grid[1][0] = num;
				cout << grid[1][0] << endl;
				turn++;
				incrementptr(num);
			}
		}
		else if (x >= 228 && x <= 307 && y >= 261 && y <= 334) {
			//square 5
			if (grid[1][1] == 2) {
				grid[1][1] = num;
				cout << grid[1][1] << endl;
				turn++;
				incrementptr(num);
			}
		}
		else if (x >= 321 && x <= 400 && y >= 261 && y <= 334) {
			//square 6
			if (grid[1][2] == 2) {
				grid[1][2] = num;
				cout << grid[1][2] << endl;
				turn++;
				incrementptr(num);
			}
		}
		else if (x >= 137 && x <= 219 && y >= 351 && y <= 430) {
			//square 7
			if (grid[2][0] == 2) {
				grid[2][0] = num;
				cout << grid[2][0] << endl;
				turn++;
				incrementptr(num);
			}
		}
		else if (x >= 229 && x <= 309 && y >= 351 && y <= 430) {
			//square 8
			if (grid[2][1] == 2) {
				grid[2][1] = num;
				cout << grid[2][1] << endl;
				turn++;
				incrementptr(num);
			}
		}
		else if (x >= 318 && x <= 402 && y >= 351 && y <= 430) {
			//square 9
			if (grid[2][2] == 2) {
				grid[2][2] = num;
				cout << grid[2][2] << endl;
				turn++;
				incrementptr(num);
			}
		}
		else;// cout << x << "     " << y << endl;

		if (checkwin() == true) {
			cout << "won";
			p1.win = true;
		}
		if (checkdraw() == true && checkwin() == false)
			cout << "draw";
	}
}

void timer1(int) {
	glutPostRedisplay();
	glutTimerFunc(1000 / 60, timer1, 0);
}

void g2player() {
	plnames();
	setcirclevalues(&c[0], 50.0, 76.0, 1.0);
	setcirclevalues(&c[1], 54.0, 76.0, 1.0);
	setcirclevalues(&c[2], 58.0, 76.0, 1.0);
	setcirclevalues(&c[3], 62.0, 76.0, 1.0);
	setcirclevalues(&c[4], 66.0, 76.0, 1.0);
	setexvalues(&e[0], -40.0, 76.0, 2.0);
	setexvalues(&e[1], -36.0, 76.0, 2.0);
	setexvalues(&e[2], -32.0, 76.0, 2.0);
	setexvalues(&e[3], -28.0, 76.0, 2.0);
	setexvalues(&e[4], -24.0, 76.0, 2.0);
	cptr = c;
	eptr = e;
	glutDisplayFunc(disp2player);
	glutReshapeFunc(reshape);
	glutTimerFunc(100000, timer1, 0);
	glutMouseFunc(mousecoord);
}

void reshape(int w, int h) {
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-100, 100, -100, 100);
	glMatrixMode(GL_MODELVIEW);
}

void init() {
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	glutSwapBuffers();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(300, 50);
	glutCreateWindow("Tic Tac Toe");
	init();
	glutDisplayFunc(g2player);
	glutReshapeFunc(reshape);
	glutMainLoop();
}
