#include <iostream>
#include <math.h>
#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>

// to use inputs.
using namespace std;

// circle(wheel) variables.
GLfloat twicePi = 2 * 3.141592; 
float radius = 2.0;
int i;
float center_x;
float center_y;
int lineAmount = 70;

// headlight variables.
bool isFront = false;
bool isRear = false;
int vehicleDirection = 0;

// wheels rotation relative to y axis(turning left or right).
float wheelsXRot = 0.0;
float rotSpeed = 2.0;
// wheels rotation relative to z axis(moving forward or back).
float forwardRot = 0.0;
float carSpeed = -7.5;

// mouse positions(using to rotate wire car).
float xRot = 0.0;
float yRot = 0.0;

// component colors.
char chasisColor = 'b';
char wheelsColor = 'g';
char steeringWheelColor = 'r';
char shaftsColor = 'p';

// declaring functions.
void display();
void timer(int t);
void createCar();
void mouse(int x, int y);
void keyboard(unsigned char, int, int);
void createMenu(int);
void draw_infos();
void print_bitmap_string(void* font, char* s);

void init(){
	// setting up 3D environment
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, 1, 0.1, 50);
	gluLookAt(10, 10, 10, 0, 0, 0, 0, 1, 0);
	glEnable(GL_DEPTH_TEST);
}

int main(int argc, char** argv) {
	
	// setting display mode.
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

	// initialization of window.
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Wire Car");
	
	// setting up menu.
	int menuChasis = glutCreateMenu(createMenu);
	glutAddMenuEntry("White", 1);
	glutAddMenuEntry("Blue", 2);
	glutAddMenuEntry("Green", 3);
	glutAddMenuEntry("Red", 4);
	glutAddMenuEntry("Purple", 5);
	glutCreateMenu(createMenu);
	
	int menuWheels = glutCreateMenu(createMenu);
	glutAddMenuEntry("White", 6);
	glutAddMenuEntry("Blue", 7);
	glutAddMenuEntry("Green", 8);
	glutAddMenuEntry("Red", 9);
	glutAddMenuEntry("Purple", 10);
	glutCreateMenu(createMenu);
	
	int menuSteeringWheel = glutCreateMenu(createMenu);
	glutAddMenuEntry("White", 11);
	glutAddMenuEntry("Blue", 12);
	glutAddMenuEntry("Green", 13);
	glutAddMenuEntry("Red", 14);
	glutAddMenuEntry("Purple", 15);
	glutCreateMenu(createMenu);
	
	int menuShafts = glutCreateMenu(createMenu);
	glutAddMenuEntry("White", 16);
	glutAddMenuEntry("Blue", 17);
	glutAddMenuEntry("Green", 18);
	glutAddMenuEntry("Red", 19);
	glutAddMenuEntry("Purple", 20);
	glutCreateMenu(createMenu);
		
	glutAddSubMenu("Chasis Color", menuChasis);
	glutAddSubMenu("Wheels Color", menuWheels);
	glutAddSubMenu("Steering Wheel Color", menuSteeringWheel);
	glutAddSubMenu("Shafts Color", menuShafts);

	glutAttachMenu(GLUT_RIGHT_BUTTON);
	
	// setting up input and other functions.
	glutIdleFunc(display);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutMotionFunc(mouse);
	glutTimerFunc(0, timer, 0);

	// init and main loop.
	init();
	glutMainLoop();
}

void createMenu(int value) {

	switch (value)
	{
	case 1:
		chasisColor = 'w';
		break;
	case 2:
		chasisColor = 'b';
		break;
	case 3:
		chasisColor = 'g';
		break;
	case 4:
		chasisColor = 'r';
		break;
	case 5:
		chasisColor = 'p';
		break;
		
	case 6:
		wheelsColor = 'w';
		break;
	case 7:
		wheelsColor = 'b';
		break;
	case 8:
		wheelsColor = 'g';
		break;
	case 9:
		wheelsColor = 'r';
		break;
	case 10:
		wheelsColor = 'p';
		break;
		
	case 11:
		steeringWheelColor = 'w';
		break;
	case 12:
		steeringWheelColor = 'b';
		break;
	case 13:
		steeringWheelColor = 'g';
		break;
	case 14:
		steeringWheelColor = 'r';
		break;
	case 15:
		steeringWheelColor = 'p';
		break;
		
	case 16:
		shaftsColor = 'w';
		break;
	case 17:
		shaftsColor = 'b';
		break;
	case 18:
		shaftsColor = 'g';
		break;
	case 19:
		shaftsColor = 'r';
		break;
	case 20:
		shaftsColor = 'p';
		break;
	}

	glutPostRedisplay();
}

void display(){
	// clearing old bits.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0, 0.0, 0.0, 0.0);
	
	// calling write instructions function.
	draw_infos();
	// calling our createCar function to draw a car.
	createCar();

	glutSwapBuffers();
}

void timer(int t){
	glutPostRedisplay();
	glutTimerFunc(1000/60, timer, 0);
}

void keyboard(unsigned char key, int x, int y){
	vehicleDirection = 0;
	
	if(key == 'w'){
		forwardRot += carSpeed;
		vehicleDirection = 1;
	}
	if(key == 's'){
		forwardRot -= carSpeed;
		vehicleDirection = -1;
	}
	if(key == 'a'){
		if(wheelsXRot < 45.0){
			wheelsXRot += rotSpeed;
		}		
	}
	if(key == 'd'){
		if(wheelsXRot > -45.0){
			wheelsXRot -= rotSpeed;
		}
	}
	if(key == 'f'){
		isFront = !isFront;
	}
	if(key == 'r'){
		isRear = !isRear;
	}
}

void mouse(int x, int y){
	// setting mouse positions.
    // setting rotations.
    yRot = x;
    xRot = y;
    
    // print mouse positions on console.
    cout << x;
    cout << " - ";
    cout << y;
    cout << "\n";
}

void print_bitmap_string(void* font, char* s) {
   if (s && strlen(s)) {
      while (*s) {
         glutBitmapCharacter(font, *s);
         s++;
      }
   }
}

void draw_infos(){
	
	// variables to use as counters.
	unsigned int i, j;
   	unsigned int count;
   	
   	// bitmap fonts we used --GLUT_BITMAP_HELVETICA_12--
	void* bitmap_fonts[7] = {
		GLUT_BITMAP_9_BY_15,
		GLUT_BITMAP_8_BY_13,
		GLUT_BITMAP_TIMES_ROMAN_10,
		GLUT_BITMAP_TIMES_ROMAN_24,
		GLUT_BITMAP_HELVETICA_10,
		GLUT_BITMAP_HELVETICA_12,
		GLUT_BITMAP_HELVETICA_18     
	};
	
	// to write rear headlights condition.
   	char* rearLight;
   	if(isRear){
   		rearLight = "Rear_Lights: On";
   	}else{
   		rearLight = "Rear_Lights: Off";
   	}
   	
   	// to write front headlights condition.
   	char* frontLight;
   	if(isFront){
   		frontLight = "Front_Lights: On";
   	}else{
   		frontLight = "Front_Lights: Off";
   	}
   	
   	// to write vehicle direction.
   	char* vehicleDir;
   	switch(vehicleDirection){
   		case -1:
   			vehicleDir = "Vehicle_Direction: Backward";
		   	break;	
		case 0:
			vehicleDir = "Vehicle_Direction: Stop";
		  	break;
		case 1:
			vehicleDir = "Vehicle_Direction: Forward";
		   	break;
	}
   
   	// text color and sizing.
	GLfloat x, y, ystep, yild, stroke_scale;
	glColor4f(0.0, 1.0, 0.0, 0.0);

	// drawing texts above.
	glPushMatrix();
	glTranslatef(-12.0, 4.0, 0.0);
	glRasterPos2f(0.0, 0.0);
	print_bitmap_string(bitmap_fonts[5], frontLight);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(-12.3, 3.4, 0.0);
	glRasterPos2f(0.0, 0.0);
	print_bitmap_string(bitmap_fonts[5], rearLight);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(-12.7, 2.8, 0.0);
	glRasterPos2f(0.0, 0.0);
	print_bitmap_string(bitmap_fonts[5], vehicleDir);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(-13.0, 2.0, 0.0);
	glRasterPos2f(0.0, 0.1);
	print_bitmap_string(bitmap_fonts[5], "-----INPUTS-----");
	glPopMatrix();
	
	// instructions.
	glPushMatrix();
	glTranslatef(-13.5, 1.5, 0.0);
	glRasterPos2f(0.0, 0.0);
	print_bitmap_string(bitmap_fonts[5], "(Left Click) Rotate Camera");
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(-13.8, 0.8, 0.0);
	glRasterPos2f(0.0, 0.0);
	print_bitmap_string(bitmap_fonts[5], "(Right Click) Customization Menu");
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(-14.25, 0.1, 0.0);
	glRasterPos2f(0.0, 0.0);
	print_bitmap_string(bitmap_fonts[5], "(W) Forward");
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(-14.5, -0.6, 0.0);
	glRasterPos2f(0.0, 0.0);
	print_bitmap_string(bitmap_fonts[5], "(S) Backward");
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(-15.0, -1.5, 0.0);
	glRasterPos2f(0.0, 0.0);
	print_bitmap_string(bitmap_fonts[5], "(A) Wheel Left Rotation");
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(-15.25, -2.3, 0.0);
	glRasterPos2f(0.0, 0.0);
	print_bitmap_string(bitmap_fonts[5], "(D) Wheel Right Rotation");
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(-15.75, -3.2, 0.0);
	glRasterPos2f(0.0, 0.0);
	print_bitmap_string(bitmap_fonts[5], "(F) Toggle Front Headlights");
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(-16.25, -4.3, 0.0);
	glRasterPos2f(0.0, 0.0);
	print_bitmap_string(bitmap_fonts[5], "(R) Toggle Rear Headlights");
	glPopMatrix();
	
}

void createCar(){
	
	glMatrixMode(GL_MODELVIEW);
	
	// CHASIS...
	// check CHASIS color.
	switch(chasisColor){
		case 'r':
			glColor3f(1.0, 0.0, 0.0);
			break;
		case 'g':
			glColor3f(0.0, 1.0, 0.0);
			break;
		case 'b':
			glColor3f(0.0, 0.0, 1.0);
			break;
		case 'w':
			glColor3f(1.0, 1.0, 1.0);
			break;
		case 'p':
			glColor3f(1.0, 0.0, 1.0);
			break;
		default:
			glColor3f(1.0, 1.0, 1.0);
	}
	glPushMatrix();
	glLoadIdentity();
	glRotatef(yRot, 0.0, 1.0, 0.0);	
	glRotatef(xRot, 1.0, 0.0, 0.0);	
	glTranslatef(0, 0, 0);
	glScalef(1, 0.25, 0.5);
	glutWireCube(5);

	glLoadIdentity();
	glRotatef(yRot, 0.0, 1.0, 0.0);	
	glRotatef(xRot, 1.0, 0.0, 0.0);	
	glTranslatef(0, 0.25 * 5, 0);
	glScalef(0.5, 0.25, 0.5);
	glutWireCube(5);
	
	// SteeringWheel.
	// check SteeringWheel color.
	switch(steeringWheelColor){
		case 'r':
			glColor3f(1.0, 0.0, 0.0);
			break;
		case 'g':
			glColor3f(0.0, 1.0, 0.0);
			break;
		case 'b':
			glColor3f(0.0, 0.0, 1.0);
			break;
		case 'w':
			glColor3f(1.0, 1.0, 1.0);
			break;
		case 'p':
			glColor3f(1.0, 0.0, 1.0);
			break;
		default:
			glColor3f(1.0, 1.0, 1.0);
	}
	glPushMatrix ();
	glTranslatef(2.0, -2.0, -1.5);
	glScalef(0.5, 0.5, 0.5);
	glRotatef(90.0, 1.0, 0.0, 0.0);
	glRotatef(180.0, 0.0, 1.0, 0.0);
	glRotatef(wheelsXRot, 0.0, 0.0, 1.0);	
	glBegin(GL_LINE_LOOP);
    for(i = 0; i <= lineAmount;i++) { 
        glVertex3f(
            center_x + (radius * cos(i * twicePi / lineAmount)), 
            center_y + (radius * sin(i * twicePi / lineAmount)),
            0.0
        );
    }
	glVertex3f(0.0,-2.0,0.0);
	glVertex3f(0.0,2.0,0.0);
	glEnd();
	glPopMatrix();
	
	glPushMatrix ();
	glTranslatef(2.0, -2.0, -1.5);
	glBegin(GL_LINES);
	glVertex3f(0.0, 0.0,0.0);
	glVertex3f(1.0,-6.0,0.0);
	glEnd();
	glPopMatrix();
	
	// WHEELS...
	// check WHEELS color.
	switch(wheelsColor){
		case 'r':
			glColor3f(1.0, 0.0, 0.0);
			break;
		case 'g':
			glColor3f(0.0, 1.0, 0.0);
			break;
		case 'b':
			glColor3f(0.0, 0.0, 1.0);
			break;
		case 'w':
			glColor3f(1.0, 1.0, 1.0);
			break;
		case 'p':
			glColor3f(1.0, 0.0, 1.0);
			break;
		default:
			glColor3f(1.0, 1.0, 1.0);
	}
	// Front Right Wheel.
	glPushMatrix ();
	glTranslatef(3.0, -8.0, 2.5);
	glScalef(0.5, 1.0, 0.5);
	glRotatef(wheelsXRot, 0.0, 1.0, 0.0);	
	glRotatef(forwardRot, 0.0, 0.0, 1.0);
	glBegin(GL_LINE_LOOP);
    for(i = 0; i <= lineAmount;i++) { 
        glVertex3f(
            center_x + (radius * cos(i * twicePi / lineAmount)), 
            center_y + (radius* sin(i * twicePi / lineAmount)),
            0.0
        );
    }
    
    glVertex3f(-2.0, 0.0, 0.0);
    glVertex3f(2.0, 0.0, 0.0);
    
    glVertex3f(2.0, 0.0, 0.0);
    glVertex3f(0.0, 2.0, 0.0);
    
    glVertex3f(0.0, 2.0, 0.0);
    glVertex3f(-2.0, 0.0, 0.0);
    
    glVertex3f(-2.0, 0.0, 0.0);
    glVertex3f(0.0, -2.0, 0.0);
    
    glVertex3f(0.0, -2.0, 0.0);
    glVertex3f(2.0, 0.0, 0.0);
    
    glEnd();
	glPopMatrix();
	
	// Front Left Wheel.
	glPushMatrix ();
	glTranslatef(3.0, -8.0, -2.5);
	glScalef(0.5, 1.0, 0.5);
	glRotatef(wheelsXRot, 0.0, 1.0, 0.0);	
	glRotatef(forwardRot, 0.0, 0.0, 1.0);
	glBegin(GL_LINE_LOOP);
    for(i = 0; i <= lineAmount;i++) { 
        glVertex3f(
            center_x + (radius * cos(i * twicePi / lineAmount)), 
            center_y + (radius* sin(i * twicePi / lineAmount)),
            0.0
        );
    }
    
    glVertex3f(-2.0, 0.0, 0.0);
    glVertex3f(2.0, 0.0, 0.0);
    
    glVertex3f(2.0, 0.0, 0.0);
    glVertex3f(0.0, 2.0, 0.0);
    
    glVertex3f(0.0, 2.0, 0.0);
    glVertex3f(-2.0, 0.0, 0.0);
    
    glVertex3f(-2.0, 0.0, 0.0);
    glVertex3f(0.0, -2.0, 0.0);
    
    glVertex3f(0.0, -2.0, 0.0);
    glVertex3f(2.0, 0.0, 0.0);
    
    glEnd();
	glPopMatrix();
	
	// Rear Right Wheel.
	glPushMatrix ();
	glTranslatef(-3.0, -8.0, 2.5);
	glScalef(0.5, 1.0, 0.5);
	glRotatef(forwardRot, 0.0, 0.0, 1.0);
	glBegin(GL_LINE_LOOP);
    for(i = 0; i <= lineAmount;i++) { 
        glVertex3f(
            center_x + (radius * cos(i * twicePi / lineAmount)), 
            center_y + (radius* sin(i * twicePi / lineAmount)),
            0.0
        );
    }
    
    glVertex3f(-2.0, 0.0, 0.0);
    glVertex3f(2.0, 0.0, 0.0);
    
    glVertex3f(2.0, 0.0, 0.0);
    glVertex3f(0.0, 2.0, 0.0);
    
    glVertex3f(0.0, 2.0, 0.0);
    glVertex3f(-2.0, 0.0, 0.0);
    
    glVertex3f(-2.0, 0.0, 0.0);
    glVertex3f(0.0, -2.0, 0.0);
    
    glVertex3f(0.0, -2.0, 0.0);
    glVertex3f(2.0, 0.0, 0.0);
    
    glEnd();
	glPopMatrix();
	
	
	// Rear Left Wheel.
	glPushMatrix ();
	glTranslatef(-3.0, -8.0, -2.5);
	glScalef(0.5, 1.0, 0.5);
	glRotatef(forwardRot, 0.0, 0.0, 1.0);
	glBegin(GL_LINE_LOOP);
    for(i = 0; i <= lineAmount;i++) { 
        glVertex3f(
            center_x + (radius * cos(i * twicePi / lineAmount)), 
            center_y + (radius* sin(i * twicePi / lineAmount)),
            0.0
        );
    }
    
    glVertex3f(-2.0, 0.0, 0.0);
    glVertex3f(2.0, 0.0, 0.0);
    
    glVertex3f(2.0, 0.0, 0.0);
    glVertex3f(0.0, 2.0, 0.0);
    
    glVertex3f(0.0, 2.0, 0.0);
    glVertex3f(-2.0, 0.0, 0.0);
    
    glVertex3f(-2.0, 0.0, 0.0);
    glVertex3f(0.0, -2.0, 0.0);
    
    glVertex3f(0.0, -2.0, 0.0);
    glVertex3f(2.0, 0.0, 0.0);
    
    glEnd();
	glPopMatrix();

	// SHAFTS...
	// check SHAFTS color.
	switch(shaftsColor){
		case 'r':
			glColor3f(1.0, 0.0, 0.0);
			break;
		case 'g':
			glColor3f(0.0, 1.0, 0.0);
			break;
		case 'b':
			glColor3f(0.0, 0.0, 1.0);
			break;
		case 'w':
			glColor3f(1.0, 1.0, 1.0);
			break;
		case 'p':
			glColor3f(1.0, 0.0, 1.0);
			break;
		default:
			glColor3f(1.0, 1.0, 1.0);
	}
	// Front.
	glPushMatrix ();
	glTranslatef(3.0, -8.0, 0.0);
	glRotatef(forwardRot, 0.0, 0.0, 1.0);	
	glBegin(GL_LINES);
	glVertex3f(0.0, 0.0, 2.5);
	glVertex3f(0.0, 0.0, -2.5);
	glEnd();
	glPopMatrix();
	// Rear.
	glPushMatrix ();
	glTranslatef(-3.0, -8.0, 0.0);
	glRotatef(forwardRot, 0.0, 0.0, 1.0);	
	glBegin(GL_LINES);
	glVertex3f(0.0, 0.0, 2.5);
	glVertex3f(0.0, 0.0, -2.5);
	glEnd();
	glPopMatrix();
	
	// Middle.
	glPushMatrix ();
	glTranslatef(0.0, -8.0, 0.0);
	glRotatef(forwardRot, 1.0, 0.0, 0.0);	
	glBegin(GL_LINES);
	glVertex3f(-3.0, 0.0, 0.0);
	glVertex3f(3.0, 0.0, 0.0);
	glEnd();
	glPopMatrix();
	
	// HEADLIGHTS...
	if(isFront){
		// Front Left Light.
		glColor3f(1.0, 1.0, 1.0);
		glPushMatrix();
		glTranslatef(5.0, -5.0, -2.0);
		glBegin(GL_POLYGON);
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(0.0, 0.0, 1.0);
		glVertex3f(0.0, 1.0, 0.0);
		glVertex3f(0.0, 1.0, 1.0);
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(0.0, 1.0, 0.0);
		glVertex3f(0.0, 0.0, 1.0);
		glVertex3f(0.0, 1.0, 1.0);
		glEnd();
		glPopMatrix();
		
		// Front Right Light
		glColor3f(1.0, 1.0, 1.0);
		glPushMatrix();
		glTranslatef(5.0, -5.0, 1.0);
		glBegin(GL_POLYGON);
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(0.0, 0.0, 1.0);
		glVertex3f(0.0, 1.0, 0.0);
		glVertex3f(0.0, 1.0, 1.0);
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(0.0, 1.0, 0.0);
		glVertex3f(0.0, 0.0, 1.0);
		glVertex3f(0.0, 1.0, 1.0);
		glEnd();
		glPopMatrix();
	}else{
		// Front Left Light.
		glColor3f(1.0, 1.0, 1.0);
		glPushMatrix();
		glTranslatef(5.0, -5.0, -2.0);
		glBegin(GL_LINES);
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(0.0, 0.0, 1.0);
		glVertex3f(0.0, 1.0, 0.0);
		glVertex3f(0.0, 1.0, 1.0);
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(0.0, 1.0, 0.0);
		glVertex3f(0.0, 0.0, 1.0);
		glVertex3f(0.0, 1.0, 1.0);
		glEnd();
		glPopMatrix();
		
		// Front Right Light
		glColor3f(1.0, 1.0, 1.0);
		glPushMatrix();
		glTranslatef(5.0, -5.0, 1.0);
		glBegin(GL_LINES);
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(0.0, 0.0, 1.0);
		glVertex3f(0.0, 1.0, 0.0);
		glVertex3f(0.0, 1.0, 1.0);
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(0.0, 1.0, 0.0);
		glVertex3f(0.0, 0.0, 1.0);
		glVertex3f(0.0, 1.0, 1.0);
		glEnd();
		glPopMatrix();
	}
	
	
	if(isRear){
		// Rear Left Light
		glColor3f(1.0, 0.0, 0.0);
		glPushMatrix();
		glTranslatef(-5.0, -5.0, -2.0);
		glBegin(GL_POLYGON);
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(0.0, 0.0, 1.0);
		glVertex3f(0.0, 1.0, 0.0);
		glVertex3f(0.0, 1.0, 1.0);
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(0.0, 1.0, 0.0);
		glVertex3f(0.0, 0.0, 1.0);
		glVertex3f(0.0, 1.0, 1.0);
		glEnd();
		glPopMatrix();
		
		// Rear Right Light
		glColor3f(1.0, 0.0, 0.0);
		glPushMatrix();
		glTranslatef(-5.0, -5.0, 1.0);
		glBegin(GL_POLYGON);
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(0.0, 0.0, 1.0);
		glVertex3f(0.0, 1.0, 0.0);
		glVertex3f(0.0, 1.0, 1.0);
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(0.0, 1.0, 0.0);
		glVertex3f(0.0, 0.0, 1.0);
		glVertex3f(0.0, 1.0, 1.0);
		glEnd();
		glPopMatrix();
	}else{
		// Rear Left Light
		glColor3f(1.0, 0.0, 0.0);
		glPushMatrix();
		glTranslatef(-5.0, -5.0, -2.0);
		glBegin(GL_LINES);
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(0.0, 0.0, 1.0);
		glVertex3f(0.0, 1.0, 0.0);
		glVertex3f(0.0, 1.0, 1.0);
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(0.0, 1.0, 0.0);
		glVertex3f(0.0, 0.0, 1.0);
		glVertex3f(0.0, 1.0, 1.0);
		glEnd();
		glPopMatrix();
		
		// Rear Right Light
		glColor3f(1.0, 0.0, 0.0);
		glPushMatrix();
		glTranslatef(-5.0, -5.0, 1.0);
		glBegin(GL_LINES);
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(0.0, 0.0, 1.0);
		glVertex3f(0.0, 1.0, 0.0);
		glVertex3f(0.0, 1.0, 1.0);
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(0.0, 1.0, 0.0);
		glVertex3f(0.0, 0.0, 1.0);
		glVertex3f(0.0, 1.0, 1.0);
		glEnd();
		glPopMatrix();
	}
	glPopMatrix();
	
}













