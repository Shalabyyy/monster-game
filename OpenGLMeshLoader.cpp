#include "Model_3DS.h"
#include "GLTexture.h"
#include <glut.h>
//PATHS
char oof[] = "D:/My stuff/GUC/Year 4/Semester 7/Computer Graphics/monster-game/sfx/robloxoof.wav";
char whoosh[] = "D:/My stuff/GUC/Year 4/Semester 7/Computer Graphics/monster-game/sfx/whoosh.wav";
char failed[] = "D:/My stuff/GUC/Year 4/Semester 7/Computer Graphics/monster-game/sfx/failed.wav";
//DIMENSIONS
int WIDTH = 1280;
int HEIGHT = 720;
//GAME VARIABLES
int score = 0;
int frames = 0;
int time = 30;
int gameSpeed = 200;
//RED BOI VARIABLES
double posX, posZ=0.0;
float angleX = 0.0f;

//BLUE ENEMY VARIABLES
double bluX = 5.0; 
double bluZ = 5.0;
float bluAngle = 0.0f;
double minBluX = bluX - 1;
double maxBluX = bluX + 1;
double minBluZ = bluZ - 1;
double maxBluZ = bluZ + 1;
bool bluAlive = true;
bool deathAnim = false;

//GREEN ENEMY VARIABLES
double grnX = 11.0;
double grnZ = 11.0;
float grnAngle = 0.0f;
double minGrnX = grnX - 1;
double maxGrnX = grnX + 1;
double minGrnZ = grnZ - 1;
double maxGrnZ = grnZ+ 1;
bool grnAlive = true;

//YELLOW ENEMY VARIABLES
double ylwX = 7.0;
double ylwZ = 15.0;
float ylwAngle = 0.0f;
double minYlwX = ylwX - 1;
double maxYlwX = ylwX + 1;
double minYlwZ = ylwZ - 1;
double maxYlwZ = ylwZ + 1;
bool ylwAlive = true;

//ORANGE ENEMY VARIABLES
double orgX = -10.0;
double orgZ = -20.0;
float orgAngle = 0.0f;
double minOrgX = orgX - 1;
double maxOrgX = orgX + 1;
double minOrgZ = orgZ - 1;
double maxOrgZ = orgZ + 1;
bool orgAlive = true;





char title[] = "3D Model Loader Sample";

// 3D Projection Options
GLdouble fovy = 45.0;
GLdouble aspectRatio = (GLdouble)WIDTH / (GLdouble)HEIGHT;
GLdouble zNear = 0.1;
GLdouble zFar = 100;

class Vector
{
public:
	GLdouble x, y, z;
	Vector() {}
	Vector(GLdouble _x, GLdouble _y, GLdouble _z) : x(_x), y(_y), z(_z) {}
	//================================================================================================//
	// Operator Overloading; In C++ you can override the behavior of operators for you class objects. //
	// Here we are overloading the += operator to add a given value to all vector coordinates.        //
	//================================================================================================//
	void operator +=(float value)
	{
		x += value;
		y += value;
		z += value;
	}
};

Vector Eye(20, 5, 20);
Vector At(0, 0, 0);
Vector Up(0, 1, 0);

int cameraZoom = 0;

// Model Variables
Model_3DS model_house;
Model_3DS model_tree;
Model_3DS spiderman;
Model_3DS alien;
Model_3DS box;
Model_3DS gun;
Model_3DS stickman;
Model_3DS sample;

// Textures
GLTexture tex_ground;
GLTexture cobblestone_ground;


//=======================================================================
// Lighting Configuration Function
//=======================================================================
void InitLightSource()
{
	// Enable Lighting for this OpenGL Program
	glEnable(GL_LIGHTING);

	// Enable Light Source number 0
	// OpengL has 8 light sources
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHT0);

	// Define Light source 0 ambient light
	GLfloat ambient[] = { 0.1f, 0.1f, 0.1, 1.0f };
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);

	// Define Light source 0 diffuse light
	GLfloat diffuse[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);

	// Define Light source 0 Specular light
	GLfloat specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glLightfv(GL_LIGHT1, GL_SPECULAR, specular);

	// Finally, define light source 0 position in World Space
	GLfloat light_position[] = { 0.0f, 10.0f, 0.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
}

//=======================================================================
// Material Configuration Function
//======================================================================
void InitMaterial()
{
	// Enable Material Tracking
	glEnable(GL_COLOR_MATERIAL);

	// Sich will be assigneet Material Properties whd by glColor
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	// Set Material's Specular Color
	// Will be applied to all objects
	GLfloat specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);

	// Set Material's Shine value (0->128)
	GLfloat shininess[] = { 96.0f };
	glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
}

//=======================================================================
// OpengGL Configuration Function
//=======================================================================
void myInit(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();

	gluPerspective(fovy, aspectRatio, zNear, zFar);
	//*******************************************************************************************//
	// fovy:			Angle between the bottom and top of the projectors, in degrees.			 //
	// aspectRatio:		Ratio of width to height of the clipping plane.							 //
	// zNear and zFar:	Specify the front and back clipping planes distances from camera.		 //
	//*******************************************************************************************//

	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();

	gluLookAt(Eye.x, Eye.y, Eye.z, At.x, At.y, At.z, Up.x, Up.y, Up.z);
	//*******************************************************************************************//
	// EYE (ex, ey, ez): defines the location of the camera.									 //
	// AT (ax, ay, az):	 denotes the direction where the camera is aiming at.					 //
	// UP (ux, uy, uz):  denotes the upward orientation of the camera.							 //
	//*******************************************************************************************//

	InitLightSource();

	InitMaterial();

	glEnable(GL_DEPTH_TEST);

	glEnable(GL_NORMALIZE);
}

//=======================================================================
// Render Ground Function
//=======================================================================
void RenderGround()
{
	glDisable(GL_LIGHTING);	// Disable lighting 
	glColor3f(0.6, 0.6, 0.6);	// Dim the ground texture a bit
	glEnable(GL_TEXTURE_2D);	// Enable 2D texturing
	glBindTexture(GL_TEXTURE_2D, tex_ground.texture[0]);	// Bind the ground texture
	glPushMatrix();
	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);	// Set quad normal direction.
	glTexCoord2f(0, 0);		// Set tex coordinates ( Using (0,0) -> (5,5) with texture wrapping set to GL_REPEAT to simulate the ground repeated grass texture).
	glVertex3f(-20, 0, -20);
	glTexCoord2f(5, 0);
	glVertex3f(20, 0, -20);
	glTexCoord2f(5, 5);
	glVertex3f(20, 0, 20);
	glTexCoord2f(0, 5);
	glVertex3f(-20, 0, 20);
	glEnd();
	glPopMatrix();

	glEnable(GL_LIGHTING);	// Enable lighting again for other entites coming throung the pipeline.

	glColor3f(1, 1, 1);	// Set material back to white instead of grey used for the ground texture.
}

//=======================================================================
// Display Function
//=======================================================================
void myDisplay(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Draw Ground
	RenderGround();

	// Draw Tree Model
	glPushMatrix();
	glTranslatef(10, 0, 0);
	glScalef(0.7, 0.7, 0.7);
	model_tree.Draw();
	glPopMatrix();

	// Draw House Model
	glPushMatrix();
	glRotatef(90.f, 1, 0, 0);
	glScaled(1.5, 1.5, 1.5);
	model_house.Draw();
	glPopMatrix();

	//Draw Red Hero
	glPushMatrix();
	glTranslatef(0 + posX, 0, 0 + posZ);
	glRotatef(angleX,0 , 1,0);
	glScalef(0.04, 0.04, 0.04);
	glColor3f(1.0f, 0.0f, 0.0f);
	stickman.Draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0 + 12, 0, 0 + 12);
	glRotatef(bluAngle, 0, 0, 1);
	glScalef(0.5, 0.5, 0.5);
	sample.Draw();
	glPopMatrix();

	//Draw Blu Boi 1
	if (bluAlive){
		glPushMatrix();
		glTranslatef(0 + bluX, 0, 0 + bluZ);
		glRotatef(bluAngle, 0, 0, 1);
		glScalef(0.04, 0.04, 0.04);
		glColor3f(0.0f, 0.0f, 1.0f);
		stickman.Draw();
		glPopMatrix();
	}
	//Draw Grn Boi 1
	if (grnAlive){
		glPushMatrix();
		glTranslatef(0 + grnX, 0, 0 + grnZ);
		glRotatef(grnAngle, 0, 1, 0);
		glScalef(0.04, 0.04, 0.04);
		glColor3f(0.0f, 1.0f, 0.0f);
		stickman.Draw();
		glPopMatrix();
	}
	if (ylwAlive){
		glPushMatrix();
		glTranslatef(0 + ylwX, 0, 0 + ylwZ);
		glRotatef(ylwAngle, 0, 1, 0);
		glScalef(0.04, 0.04, 0.04);
		glColor3f(1.0f, 1.0f, 0.0f);
		stickman.Draw();
		glPopMatrix();
	}
	if (orgAlive){
		glPushMatrix();
		glTranslatef(0 + orgX, 0, 0 + orgZ);
		glRotatef(orgAngle, 0, 1, 0);
		glScalef(0.04, 0.04, 0.04);
		glColor3f(1.0f, 0.27f, 0.0f);
		stickman.Draw();
		glPopMatrix();
	}

	glutSwapBuffers();
}

void attackAnimation(){
	float temp = angleX;
	for (int i = 0; i < 360; i++){
		printf("HARHAR \n");
		angleX = temp - i;
		glutPostRedisplay();
	}
	angleX = temp;
	glutPostRedisplay();

}
 void attack(){

	 printf("I am at (%f,%f) \n", posX, posZ);
	 bool punched_ = PlaySound(TEXT(whoosh), NULL, SND_ASYNC | SND_FILENAME);
	 //attackAnimation();

	 //BLUE BOI
	 bool condBx = posX >= minBluX && posX <= maxBluX;
	 bool condBz = posZ >= minBluZ && posZ <= maxBluZ;
	 printf("BLUE BOI FROM X:%f -> %f AND Z: %f -> %f \n",minBluX,maxBluX,minBluZ,maxBluZ );
	 if (condBx && condBz && bluAlive){
		 score = score + 100;
		 bool played = PlaySound(TEXT(oof), NULL, SND_ASYNC | SND_FILENAME);
		 bluAlive = false;

	 }
	 //GREEN BOI
	 
	 bool condGx = posX >= minGrnX && posX <= maxGrnX;
	 bool condGz = posZ >= minGrnZ && posZ <= maxGrnZ;
	 printf("GREEN BOI FROM X:%f -> %f AND Z: %f -> %f \n", minGrnX, maxGrnX, minGrnZ, maxGrnZ);
	 if (condGx && condGz && grnAlive){
		 grnAlive = false;
		 score = score + 100;
		 bool played = PlaySound(TEXT(oof), NULL, SND_ASYNC | SND_FILENAME);
	 }

	 //YELLOW BOI
	 bool condYx = posX >= minYlwX && posX <= maxYlwX;
	 bool condYz = posZ >= minYlwZ && posZ <= maxYlwZ;
	 printf("YELLOW BOI FROM X:%f -> %f AND Z: %f -> %f \n", minYlwX, maxYlwX, minYlwZ, maxYlwZ);
	 if (condYx && condYz && ylwAlive){
		 ylwAlive = false;
		 score = score + 100;
		 bool played = PlaySound(TEXT(oof), NULL, SND_ASYNC | SND_FILENAME);

	 }
	 //ORANGE BOI
	 bool condOGx = posX >= minOrgX && posX <= maxOrgX;
	 bool condOGz = posZ >= minOrgZ && posZ <= maxOrgZ;
	 printf("ORANGE BOI FROM X:%f -> %f AND Z: %f -> %f \n", minOrgX, maxOrgX, minOrgZ, maxOrgZ);
	 if (condOGx && condOGz && orgAlive){
		 orgAlive = false;
		 score = score + 100;
		 bool played = PlaySound(TEXT(oof), NULL, SND_ASYNC | SND_FILENAME);
	 }

	 printf("---------------------------------------------------------------------------------\n");
	 glutPostRedisplay();
}
//=======================================================================
// Keyboard Function
//=======================================================================
 void move(unsigned char key){
	 //use the first if as a reference 
	 if (angleX >= 0 && angleX < 90){
		 printf("First Quadrant \n");
		 if (key == 'w'){
			 //N7ot Function el a EL ADEEM
			 posZ = posZ + 0.5;
		 }
		 else if (key == 's'){
			 //N7ot function el d EL ADEEMA
			 posZ = posZ - 0.5;
		 }
		 else if (key == 'a'){
			 //N7ot Function el w EL ADEEMA
			 posX = posX + 0.5;

		 }
		 else if (key == 'd'){
			 //n7ot function el s EL ADEEMA
			 posX = posX - 0.5;

		 }
	 }
	 else if (angleX >= 90 && angleX < 180){
		 printf("Second Quadrant \n");
		 if (key == 'w'){
			 posX = posX + 0.5;

		 }
		 else if (key == 's'){
			 posX = posX - 0.5;

		 }
		 else if (key == 'a'){
			 posZ = posZ - 0.5;
		 }
		 else if (key == 'd'){
			 posZ = posZ + 0.5;

		 }
	 }
	 else if (angleX >= 180 && angleX < 270){
		 printf("Third Quadrant \n");
		 if (key == 'w'){
			 posZ = posZ - 0.5;
		 }
		 else if (key == 's'){
			 posZ = posZ + 0.5;
		 }
		 else if (key == 'a'){
			 posX = posX - 0.5;
		 }
		 else if (key == 'd'){
			 posX = posX + 0.5;
		 }

	 }
	 else if (angleX >= 270 && angleX < 360){
		 printf("Fourth Quadrant \n");

		 if (key == 'w'){
			 posX = posX - 0.5;

		 }
		 else if (key == 's'){
			 posX = posX + 0.5;

		 }
		 else if (key == 'a'){
			 posZ = posZ + 0.5;
		 }
		 else if (key == 'd'){
			 posZ = posZ - 0.5;

		 }
	 }


 }

void myKeyboard(unsigned char button, int x, int y)
{
	switch (button)
	{
	case'p': 
		Eye.y=Eye.y + 1;
		break;
	case 't':
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		break;
	case 'r':
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		break;
	case 'w':
		//posX = posX + 0.5;
		move(button);
		break;
	case 's':
		//posX = posX - 0.5;
		move(button);
			break;
	case 'a':
		//posZ = posZ + 0.5;
		move(button);
		break;
	case 'd':
		//posZ = posZ - 0.5;
		move(button);
		break;
	case 'z':
		angleX = angleX - 22.5;
		printf("NEGATIVE BOOM %f \n", angleX);
		if (angleX == -360){
			angleX = 0.0f;
			printf("BOOM %f \n",angleX);
		}
		break;
	case 'c':
		angleX = angleX + 22.5;
		printf("POSOTIVE BOOM %f \n", angleX);
		if (angleX == 360){
			angleX = 0.0f;
			printf("BOOM %f \n", angleX);

		}
		break;
	case 27:
		exit(0);
		break;
	case'q':
		attack();
		break;
	default:
		break;	
	}

	glutPostRedisplay();
}

//=======================================================================
// Motion Function
//=======================================================================

void myMotion(int x, int y)
{
	y = HEIGHT - y;

	if (cameraZoom - y > 0)
	{
		Eye.x += -0.1;
		Eye.z += -0.1;
	}
	else
	{
		Eye.x += 0.1;
		Eye.z += 0.1;
	}

	cameraZoom = y;

	glLoadIdentity();	//Clear Model_View Matrix

	gluLookAt(Eye.x, Eye.y, Eye.z, At.x, At.y, At.z, Up.x, Up.y, Up.z);	//Setup Camera with modified paramters

	GLfloat light_position[] = { 0.0f, 10.0f, 0.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	glutPostRedisplay();	//Re-draw scene 
}
//=======================================================================
// Mouse Function
//=======================================================================
void myMouse(int button, int state, int x, int y)
{
	y = HEIGHT - y;

	if (state == GLUT_DOWN)
	{
		cameraZoom = y;
	}
}
//=======================================================================
// Timer Function
//=======================================================================
void timer(int val){
	frames++; 
	if (frames % 5 == 0){
		time--;
	}
	if (time < 0){
		bool sound = PlaySound(TEXT(failed), NULL, SND_ASYNC | SND_FILENAME);
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	else{
		printf("TIME REMAING: %d \n", time);
		printf("FRAMES REMAING: %d \n", frames);
		printf("------------------------------------------\n");
	}

	glutPostRedisplay();
	glutTimerFunc(gameSpeed, timer, 0);

}
//=======================================================================
// Reshape Function
//=======================================================================
void myReshape(int w, int h)
{
	if (h == 0) {
		h = 1;
	}

	WIDTH = w;
	HEIGHT = h;

	// set the drawable region of the window
	glViewport(0, 0, w, h);

	// set up the projection matrix 
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(fovy, (GLdouble)WIDTH / (GLdouble)HEIGHT, zNear, zFar);

	// go back to modelview matrix so we can move the objects about
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(Eye.x, Eye.y, Eye.z, At.x, At.y, At.z, Up.x, Up.y, Up.z);
}

//=======================================================================
// Assets Loading Function
//=======================================================================
void LoadAssets()
{
	// Loading Model files
	model_house.Load("Models/house/house.3ds");
	model_tree.Load("Models/tree/tree1.3ds");
	stickman.Load("Models/stickman/StickFigurea.3ds");
	sample.Load("Models/bear/BEAR_KDK.3ds");
	// Loading texture files
	tex_ground.Load("Textures/ground.bmp");
}

//=======================================================================
// Main Function
//=======================================================================
void main(int argc, char** argv)
{
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	glutInitWindowSize(WIDTH, HEIGHT);


	glutInitWindowPosition(100, 150);

	glutCreateWindow(title);

	glutDisplayFunc(myDisplay);

	glutKeyboardFunc(myKeyboard);

	glutMotionFunc(myMotion);

	glutMouseFunc(myMouse);

	glutTimerFunc(0, timer, 0);

	glutReshapeFunc(myReshape);

	myInit();


	LoadAssets();

	glutMainLoop();
}