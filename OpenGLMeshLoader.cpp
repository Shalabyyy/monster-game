#include "Model_3DS.h"
#include "GLTexture.h"
#include <glut.h>
#include <stdio.h>
#include <math.h>
#include <random>
#include <iostream>
#include <Windows.h>
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
bool incTime = true;
bool level1 = true ;
float sysAngle = 0.0f;
bool third_person = true;
bool first_person = false;
bool finished_game = false;
char skr[6];
bool times_up = false;
bool ability = false;
int ability_counter = 10;
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
double orgZ = -10.0;
float orgAngle = 0.0f;
double minOrgX = orgX - 1;
double maxOrgX = orgX + 1;
double minOrgZ = orgZ - 1;
double maxOrgZ = orgZ + 1;
bool orgAlive = true;

//  5 Dragons
//RED DRAGON VARIABLES
double redDragonX = 6;
double redDragonZ = -10;
float redDragonAngle = 0.0f;
double minRedDragonX = redDragonX - 1;
double maxRedDragonX = redDragonX + 1;
double minRedDragonZ =redDragonZ - 1 ;
double maxRedDraginZ = redDragonZ + 1;
bool redDragonAlive = true;

//BLUE DRAGON VARIABLES
double blueDragonX = -11.0;
double blueDragonZ = 14.0;
float blueDragonAngle = 0.0f;
double minBlueDragonX = blueDragonX - 1;
double maxBlueDragonX = blueDragonX + 1;
double minBlueDragonZ = blueDragonZ - 1;
double maxBlueDraginZ = blueDragonZ + 1;
bool blueDragonAlive = true;

//GREEN DRAGON VARIABLES
double greenDragonX = 11.0;
double greenDragonZ = 11.0;
float greenDragonAngle = 0.0f;
double minGreenDragonX = greenDragonX - 1;
double maxGreenDragonX = greenDragonX + 1;
double minGreenDragonZ = greenDragonZ - 1;
double maxGreenDraginZ = greenDragonZ + 1;
bool greenDragonAlive = true;

//YELLOW DRAGON VARIABLES
double yellowDragonX = -10.0;
double yellowDragonZ = 18.0;
float yellowDragonAngle = 0.0f;
double minYellowDragonX = yellowDragonX - 1;
double maxYellowDragonX = yellowDragonX + 1;
double minYellowDragonZ = yellowDragonZ - 1;
double maxYellowDraginZ = yellowDragonZ + 1;
bool yellowDragonAlive = true;

//ORANGE DRAGON VARIABLES
double orangeDragonX = -5.0;
double orangeDragonZ = 30.0;
float orangeDragonAngle = 0.0f;
double minOrangeDragonX = orangeDragonX - 1;
double maxOrangeDragonX = orangeDragonX + 1;
double minOrangeDragonZ = orangeDragonZ - 1;
double maxOrangeDraginZ = orangeDragonZ + 1;
bool orangeDragonAlive = true;

//Car 1
int car1X = 18;
int car1Z = -1;

//Car 2 
int car2X = -17;
int car2Z = 0;

//Car 3
int  car3X = -10;
int car3Z = -15;


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
int cameraWidth = 0;
// Model Variables
Model_3DS model_house;
Model_3DS model_tree;
Model_3DS spiderman;
Model_3DS alien;
Model_3DS box;
Model_3DS gun;
Model_3DS stickman;
Model_3DS dragon;
Model_3DS model_car;
Model_3DS model_truck;

// Textures
GLTexture tex_ground;
GLTexture cobblestone_ground;

void print(float x, float y, float z, char* string)
{
	int len, i;
	glRasterPos3f(x, y, z);
	len = (int)strlen(string);
	for (i = 0; i < len; i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[i]);
	}
}


//=======================================================================
// Lighting Configuration Function
//=======================================================================
void InitLightSource()
{
	// Enable Lighting for this OpenGL Program
	glEnable(GL_LIGHTING);

	// Enable Light Source number 0
	// OpengL has 8 light sources
	glEnable(GL_LIGHT2);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHT0);

	// Define Light source 0 ambient light
	GLfloat ambient[] = { 0.1f, 0.1f, 0.1, 1.0f };
	glLightfv(GL_LIGHT1, GL_AMBIENT, ambient);

	// Define Light source 0 diffuse light
	GLfloat diffuse[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);

	// Define Light source 0 Specular light
	GLfloat specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glLightfv(GL_LIGHT1, GL_SPECULAR, specular);

	// Finally, define light source 0 position in World Space
	GLfloat light_position[] = { 0.0f, 10.0f, 0.0f, 1.0f };
	glLightfv(GL_LIGHT2, GL_POSITION, light_position);
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
void renderGroundCOBB(){
	glDisable(GL_LIGHTING);	// Disable lighting 
	glColor3f(0.6, 0.6, 0.6);	// Dim the ground texture a bit
	glEnable(GL_TEXTURE_2D);	// Enable 2D texturing
	glBindTexture(GL_TEXTURE_2D, cobblestone_ground.texture[0]);	// Bind the ground texture
	glPushMatrix();
	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);	// Set quad normal direction.
	glTexCoord2f(0, 0);		// Set tex coordinates ( Using (0,0) -> (5,5) with texture wrapping set to GL_REPEAT to simulate the ground repeated grass texture).
	glVertex3f(-40, 0, -40);
	glTexCoord2f(10, 0);
	glVertex3f(40, 0, -40);
	glTexCoord2f(10, 10);
	glVertex3f(40, 0, 40);
	glTexCoord2f(0, 10);
	glVertex3f(-40, 0, 40);
	glEnd();
	glPopMatrix();

	glEnable(GL_LIGHTING);	// Enable lighting again for other entites coming throung the pipeline.

	glColor3f(1, 1, 1);	// Set material back to white instead of grey used for the ground texture.
}
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
	glVertex3f(-50, 0, -50);
	glTexCoord2f(5, 0);
	glVertex3f(50, 0, -50);
	glTexCoord2f(5, 5);
	glVertex3f(50, 0, 50);
	glTexCoord2f(0, 5);
	glVertex3f(-50, 0, 50);
	glEnd();
	glPopMatrix();

	glEnable(GL_LIGHTING);	// Enable lighting again for other entites coming throung the pipeline.

	glColor3f(1, 1, 1);	// Set material back to white instead of grey used for the ground texture.
}

//=======================================================================
// Display Function
//=======================================================================
bool checkCarRange(){
	bool redx = posX >= 16.5 && posX <= 20;
	bool redz = posZ >= -4.5 && posZ <= 2;
	bool red_col = redx && redz;
	
	bool bluex = posX >= -18 && posX <= -15.5;
	bool bluez = posZ >= -2.5 && posZ <= 3;
	bool blue_col = bluex && bluez;

	bool greenx = posX >= -11 && posX <= -8;
	bool greenz = posZ >= -20 && posZ <= -10.5;
	bool green_col = greenx && greenz;

	bool tree = posX == 9.5 && posZ == 0;

	bool housex = posX >= -5.5 && posX <= 5;
	bool housez= posZ >= -3 && posZ <= 0;
	bool house = housex && housez;

	bool mapx = posX >= -49 && posX <= 49;
	bool mapz = posZ >= -49 && posZ <= 49;
	bool mapcn = mapx && mapz;

	bool blue_boiX = posX >= (bluX - 0.7) && posX <= (bluX + 0.7);
	bool blue_boiZ = posZ >= (bluZ - 0.7) && posZ <= (bluZ + 0.7);
	bool blue_boi = blue_boiX && blue_boiZ && bluAlive;
	
	bool green_boiX = posX >= (grnX - 0.7) && posX <= (grnX + 0.7);
	bool green_boiZ = posZ >= (grnZ - 0.7) && posZ <= (grnZ + 0.7);
	bool green_boi = green_boiX && green_boiZ && grnAlive;

	bool yellow_boiX = posX >= (ylwX - 0.7) && posX <= (ylwX + 0.7);
	bool yellow_boiZ = posZ >= (ylwZ - 0.7) && posZ <= (ylwZ + 0.7);
	bool yellow_boi = yellow_boiX && yellow_boiZ && ylwAlive;

	bool orange_boiX = posX >= (orgX - 0.7) && posX <= (orgX + 0.7);
	bool orange_boiZ = posZ >= (orgZ - 0.7) && posZ <= (orgZ + 0.7);
	bool orange_boi = orange_boiX && orange_boiZ && orgAlive;


	bool verdict = blue_col || red_col || green_col || blue_boi || green_boi || yellow_boi || orange_boi || house || !mapcn;
	
	return verdict;


}

bool checkCarRange2(){
	bool redx = posX >= -13.5 && posX <= -5.5;
	bool redz = posZ >= 19 && posZ <= 21.5;
	bool red_col = redx && redz;

	bool bluex = posX >= -3 && posX <= 4.5;
	bool bluez = posZ >= 19 && posZ <= 21.5;
	bool blue_col = bluex && bluez;

	bool greenx = posX >= -18.5 && posX <= -10;
	bool greenz = posZ >= -13.5 && posZ <= -16.5;
	bool green_col = greenx && greenz;

	bool tree = posX == 9.5 && posZ == 0;

	bool housex = posX >= -5.5 && posX <= 5;
	bool housez = posZ >= -3 && posZ <= 0;
	bool house = housex && housez;

	bool mapx = posX >= -49 && posX <= 49;
	bool mapz = posZ >= -49 && posZ <= 49;
	bool mapcn = mapx && mapz;

	bool blue_boiX = posX >= (blueDragonX - 0.5) && posX <= (blueDragonX + 0.5);
	bool blue_boiZ = posZ >= (blueDragonZ - 0.5) && posZ <= (blueDragonZ + 0.5);
	bool blue_boi = blue_boiX && blue_boiZ && bluAlive;

	bool green_boiX = posX >= (greenDragonX - 0.5) && posX <= (greenDragonX + 0.5);
	bool green_boiZ = posZ >= (greenDragonZ - 0.5) && posZ <= (greenDragonZ + 0.5);
	bool green_boi = green_boiX && green_boiZ && greenDragonAlive;

	bool yellow_boiX = posX >= (yellowDragonX - 0.5) && posX <= (yellowDragonX + 0.5);
	bool yellow_boiZ = posZ >= (yellowDragonZ - 0.5) && posZ <= (yellowDragonZ + 0.5);
	bool yellow_boi = yellow_boiX && yellow_boiZ && yellowDragonZ;

	bool orange_boiX = posX >= (orangeDragonX - 0.5) && posX <= (orangeDragonX + 0.5);
	bool orange_boiZ = posZ >= (orangeDragonZ - 0.5) && posZ <= (orangeDragonZ + 0.5);
	bool orange_boi = orange_boiX && orange_boiZ && orangeDragonAlive;

	bool red_boiX = posX >= (redDragonX - 0.5) && posX <= (redDragonX + 0.5);
	bool red_boiZ = posZ >= (redDragonZ - 0.5) && posZ <= (redDragonZ + 0.5);
	bool red_boi = red_boiX && red_boiZ && redDragonAlive;

	return red_col || blue_col || green_col || blue_boi || green_boi|| yellow_boi || orange_boi|| red_boi|| tree || house  ;
}
void myDisplay(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
	glTranslated(0.0f, -5.0f, 0.0f);
	glRotatef(sysAngle, 0, 1, 0);

	

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

	// Draw Car Model
	if (level1){
		glPushMatrix();
		glTranslatef(car1X, 0, car1Z);
		glScalef(1.2, 1.2, 1.2);
		model_car.Draw();
		glPopMatrix();
	}

	if (level1){
		glPushMatrix();
		glTranslatef(car2X, 0, car2Z);
		glScalef(1.2, 1.2, 1.2);
		glColor3f(0.0f, 0.0f, 1.0f);
		model_car.Draw();
		glPopMatrix();
	}

	if (level1){
		glPushMatrix();
		glTranslatef(car3X, 0, car3Z);
		glScalef(1.2, 1.2, 2);
		glColor3f(0.0f, 1.0f, 0.0f);
		model_car.Draw();
		glPopMatrix();
	}

	// Draw Truck Model
	if (!level1){
		glPushMatrix();
		glTranslatef(-10, 0, 20);
		glScalef(1, 1, 1);
		glColor3f(1.0, 0.0f, 0.0f);
		model_truck.Draw();
		glPopMatrix();
	}
	if (!level1){
		glPushMatrix();
		glTranslatef(0, 0, 20);
		glScalef(1, 1, 1);
		glColor3f(0.0f, 0.0f, 1.0f);
		model_truck.Draw();
		glPopMatrix();
	}
	if (!level1){
		glPushMatrix();
		glTranslatef(-15, 0, -15);
		glScalef(1, 1, 1);
		glColor3f(0.0f, 1.0f, 0.0f);
		model_truck.Draw();
		glPopMatrix();
	}

	//Draw Red Hero
	glPushMatrix();
	glTranslatef(0 + posX, 0, 0 + posZ);
	glRotatef(angleX,0 , 1,0);
	glScalef(0.04, 0.04, 0.04);
	glColor3f(1.0f, 0.0f, 0.0f);
	stickman.Draw();
	glPopMatrix();

	glPushMatrix();	
	glColor3f(1.0f, 1.0f, 1.0f);
	glTranslated(-1+posX, 4, -1+posZ);
	print(0.0f, 0.0f, 0.0f, skr);
	glPopMatrix();

	if (finished_game){
		glPushMatrix();
		glColor3f(1.0f, 0.0f, 0.0f);
		glTranslated(-1 + posX, 5, -1 + posZ);
		print(0.0f, 0.0f, 0.0f, "GAME OVER !");
		glPopMatrix();
	
	}
	if (times_up){
		glPushMatrix();
		glColor3f(1.0f, 0.0f, 0.0f);
		glTranslated(-1 + posX, 5, -1 + posZ);
		print(0.0f, 0.0f, 0.0f, "TIME IS UP !");
		glPopMatrix();
	}
	if (!level1 && redDragonAlive){
		//RED DRAGON
		glPushMatrix();
		glTranslatef(0 + redDragonX, 0, 0 + redDragonZ);
		glRotatef(bluAngle, 0, 0, 1);
		glScalef(0.02, 0.07, 0.03);
		glColor3f(1.0f, 0.0f, 0.0f);
		dragon.Draw();
		glPopMatrix();
	}
	if (!level1 && blueDragonAlive){
		//BLUE DRAGON
		glPushMatrix();
		glTranslatef(0 + blueDragonX, 0, 0 + blueDragonZ);
		glRotatef(blueDragonAngle, 0, 0, 1);
		glScalef(0.02, 0.07, 0.03);
		glColor3f(0.0f, 1.0f, 0.0f);
		dragon.Draw();
		glPopMatrix();
	}
	if (!level1 && yellowDragonAlive){
		//YELLOW DRAGON
		glPushMatrix();
		glTranslatef(0 + yellowDragonX, 0, 0 + yellowDragonZ);
		glRotatef(yellowDragonAngle, 0, 0, 1);
		glScalef(0.02, 0.07, 0.03);
		glColor3f(1.0f, 0.0f, 1.0f);
		dragon.Draw();
		glPopMatrix();
	}
	if (!level1 && greenDragonAlive){
		//GREEN DRAGON
		glPushMatrix();
		glTranslatef(0 + greenDragonX, 0, 0 + greenDragonZ);
		glRotatef(greenDragonAngle, 0, 0, 1);
		glScalef(0.02, 0.07, 0.03);
		glColor3f(0.0f, 0.0f, 1.0f);
		dragon.Draw();
		glPopMatrix();
	}
	if (!level1 && orangeDragonAlive){
		//ORANGE DRAGON
		glPushMatrix();
		glTranslatef(0 + orangeDragonX, 0, 0 + orangeDragonZ);
		glRotatef(orangeDragonAngle, 0, 0, 1);
		glScalef(0.02, 0.07, 0.03);
		glColor3f(1.0f, 0.27f, 0.0f);
		dragon.Draw();
		glPopMatrix();
	}
	

	//Draw Blu Boi 1
	if (bluAlive && level1){
		glPushMatrix();
		glTranslatef(0 + bluX, 0, 0 + bluZ);
		glRotatef(bluAngle, 0, 0, 1);
		glScalef(0.04, 0.04, 0.04);
		glColor3f(0.0f, 0.0f, 1.0f);
		stickman.Draw();
		glPopMatrix();
	}
	//Draw Grn Boi 1
	if (grnAlive && level1){
		glPushMatrix();
		glTranslatef(0 + grnX, 0, 0 + grnZ);
		glRotatef(grnAngle, 0, 1, 0);
		glScalef(0.04, 0.04, 0.04);
		glColor3f(0.0f, 1.0f, 0.0f);
		stickman.Draw();
		glPopMatrix();
	}
	if (ylwAlive && level1){
		glPushMatrix();
		glTranslatef(0 + ylwX, 0, 0 + ylwZ);
		glRotatef(ylwAngle, 0, 1, 0);
		glScalef(0.04, 0.04, 0.04);
		glColor3f(1.0f, 1.0f, 0.0f);
		stickman.Draw();
		glPopMatrix();
	}
	if (orgAlive && level1){
		glPushMatrix();
		glTranslatef(0 + orgX, 0, 0 + orgZ);
		glRotatef(orgAngle, 0, 1, 0);
		glScalef(0.04, 0.04, 0.04);
		glColor3f(1.0f, 0.27f, 0.0f);
		stickman.Draw();
		glPopMatrix();
	}

	
	glPopMatrix();
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
		 sprintf(skr, "%d", score);
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
		 sprintf(skr, "%d", score);
		 bool played = PlaySound(TEXT(oof), NULL, SND_ASYNC | SND_FILENAME);
	 }

	 //YELLOW BOI
	 bool condYx = posX >= minYlwX && posX <= maxYlwX;
	 bool condYz = posZ >= minYlwZ && posZ <= maxYlwZ;
	 printf("YELLOW BOI FROM X:%f -> %f AND Z: %f -> %f \n", minYlwX, maxYlwX, minYlwZ, maxYlwZ);
	 if (condYx && condYz && ylwAlive){
		 ylwAlive = false;
		 score = score + 100;
		 sprintf(skr, "%d", score);
		 bool played = PlaySound(TEXT(oof), NULL, SND_ASYNC | SND_FILENAME);

	 }
	 //ORANGE BOI
	 bool condOGx = posX >= minOrgX && posX <= maxOrgX;
	 bool condOGz = posZ >= minOrgZ && posZ <= maxOrgZ;
	 printf("ORANGE BOI FROM X:%f -> %f AND Z: %f -> %f \n", minOrgX, maxOrgX, minOrgZ, maxOrgZ);
	 if (condOGx && condOGz && orgAlive){
		 orgAlive = false;
		 score = score + 100;
		 sprintf(skr, "%d", score);
		 bool played = PlaySound(TEXT(oof), NULL, SND_ASYNC | SND_FILENAME);
	 }

	 printf("---------------------------------------------------------------------------------\n");
	 glutPostRedisplay();
}
 void attackDragon(){
	 printf("I am at (%f,%f) \n", posX, posZ);
	 bool punched_ = PlaySound(TEXT(whoosh), NULL, SND_ASYNC | SND_FILENAME);
	 //attackAnimation();
	 bool condRx = posX >= minRedDragonX && posX <= maxRedDragonX;
	 bool condRz = posZ >= minRedDragonZ && posZ <= maxRedDraginZ;
	 printf("RED DRAGON FROM X:%f -> %f AND Z: %f -> %f \n", minRedDragonX, maxRedDragonX, minRedDragonZ, maxRedDraginZ);
	 if (condRx && condRx &&  redDragonAlive){
		 score = score + 100;
		 sprintf(skr, "%d", score);
		 bool played = PlaySound(TEXT(oof), NULL, SND_ASYNC | SND_FILENAME);
		 redDragonAlive = false;

	 }

	 //BLUE DRAGON
	 bool condBx = posX >= minBlueDragonX && posX <= maxBlueDragonX;
	 bool condBz = posZ >= minBlueDragonZ && posZ <= maxBlueDraginZ;
	 printf("BLUE DRAGON FROM X:%f -> %f AND Z: %f -> %f \n", minBlueDragonX, maxBlueDragonX, minBlueDragonZ, maxBlueDraginZ);
	 if (condBx && condBz &&  blueDragonAlive){
		 score = score + 100;
		 sprintf(skr, "%d", score);
		 bool played = PlaySound(TEXT(oof), NULL, SND_ASYNC | SND_FILENAME);
		 blueDragonAlive = false;

	 }
	 //GREEN DRAGON

	 bool condGx = posX >= minGreenDragonX && posX <= maxGreenDragonX;
	 bool condGz = posZ >= minGreenDragonZ && posZ <= maxGreenDraginZ;
	 printf("GREEN DRAGON FROM X:%f -> %f AND Z: %f -> %f \n", minGreenDragonX, maxGreenDragonX, minGreenDragonZ, maxGreenDraginZ);
	 if (condGx && condGz && greenDragonAlive){
		 greenDragonAlive = false;
		 score = score + 100;
		 sprintf(skr, "%d", score);
		 bool played = PlaySound(TEXT(oof), NULL, SND_ASYNC | SND_FILENAME);
	 }

	 //YELLOW DRAGON
	 bool condYx = posX >= minYellowDragonX && posX <= maxYellowDragonX;
	 bool condYz = posZ >= minYellowDragonZ && posZ <= maxYellowDraginZ;
	 printf("YELLOW DRAGON FROM X:%f -> %f AND Z: %f -> %f \n", minYellowDragonX, maxYellowDragonX, minYellowDragonZ, maxYellowDraginZ);
	 if (condYx && condYz && yellowDragonAlive){
		 yellowDragonAlive = false;
		 score = score + 100;
		 sprintf(skr, "%d", score);
		 bool played = PlaySound(TEXT(oof), NULL, SND_ASYNC | SND_FILENAME);

	 }
	 //ORANGE DRAGON
	 bool condOGx = posX >= minOrangeDragonX && posX <= maxOrangeDragonX;
	 bool condOGz = posZ >= minOrangeDragonZ && posZ <= maxOrangeDraginZ;
	 printf("ORANGE DRAGON FROM X:%f -> %f AND Z: %f -> %f \n", minOrangeDragonX, maxOrangeDragonX, minOrangeDragonZ, maxOrangeDraginZ);
	 if (condOGx && condOGz && orangeDragonAlive){
		 orangeDragonAlive = false;
		 score = score + 100;
		 sprintf(skr, "%d", score);
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
			 if (level1 && checkCarRange()){
				 posZ = posZ - 0.5;
			 }
			  if (!level1 && checkCarRange2()){
				 posZ = posZ - 0.5;
			 }
		 }
		 else if (key == 's'){
			 //N7ot function el d EL ADEEMA
			 posZ = posZ - 0.5;
			 if (level1 && checkCarRange()){
				 posZ = posZ +0.5;
			 }
			  if (!level1 && checkCarRange2()){
				 posZ = posZ + 0.5;
			 }
		 }
		 else if (key == 'a'){
			 //N7ot Function el w EL ADEEMA
			 posX = posX + 0.5;
			 if (level1 && checkCarRange()){
				 posX = posX - 0.5;
			 }
			  if (!level1 && checkCarRange2()){
				 posX = posX - 0.5;
			 }

		 }
		 else if (key == 'd'){
			 //n7ot function el s EL ADEEMA
			 posX = posX - 0.5;
			 if (level1 && checkCarRange()){
				 posX = posX + 0.5;
			 }
			  if (!level1 && checkCarRange2()){
				 posX = posX + 0.5;
			 }

		 }
	 }
	 else if (angleX >= 90 && angleX < 180){
		 printf("Second Quadrant \n");
		 if (key == 'w'){
			 posX = posX + 0.5;
			 if (level1 && checkCarRange()){
				 posX = posX - 0.5;
			 }
			  if (!level1 && checkCarRange2()){
				 posX = posX - 0.5;
			 }

		 }
		 else if (key == 's'){
			 posX = posX - 0.5;
			 if (level1 && checkCarRange()){
				 posX = posX + 0.5;
			 }
			  if (!level1 && checkCarRange2()){
				 posX = posX - 0.5;
			 }


		 }
		 else if (key == 'a'){
			 posZ = posZ - 0.5;
			 if (level1 && checkCarRange()){
				 posZ = posZ + 0.5;
			 }
			  if (!level1 && checkCarRange2()){
				 posZ = posZ + 0.5;
			 }
		 }
		 else if (key == 'd'){
			 posZ = posZ + 0.5;
			 if (level1 && checkCarRange()){
				 posZ = posZ - 0.5;
			 }
			  if (!level1 && checkCarRange2()){
				 posZ = posZ - 0.5;
			 }


		 }
	 }
	 else if (angleX >= 180 && angleX < 270){
		 printf("Third Quadrant \n");
		 if (key == 'w'){
			 posZ = posZ - 0.5;
			 if (level1 && checkCarRange()){
				 posZ = posZ + 0.5;
			 }
			  if (!level1 && checkCarRange2()){
				 posZ = posZ + 0.5;
			 }
		 }
		 else if (key == 's'){
			 posZ = posZ + 0.5;
			 if (level1 && checkCarRange()){
				 posZ = posZ - 0.5;
			 }
			  if (!level1 && checkCarRange2()){
				 posZ = posZ - 0.5;
			 }
		 }
		 else if (key == 'a'){
			 posX = posX - 0.5;
			 if (level1 && checkCarRange()){
				 posX = posX + 0.5;
			 }
			  if (!level1 && checkCarRange2()){
				 posX = posX + 0.5;
			 }
		 }
		 else if (key == 'd'){
			 posX = posX + 0.5;
			 if (level1 && checkCarRange()){
				 posX = posX - 0.5;
			 }
			  if (!level1 && checkCarRange2()){
				 posX = posX - 0.5;
			 }
		 }

	 }
	 else if (angleX >= 270 && angleX < 360){
		 printf("Fourth Quadrant \n");

		 cameraWidth = 672;
		 if (key == 'w'){
			 posX = posX - 0.5;
			 if (level1 && checkCarRange()){
				 posX = posX + 0.5;
			 }
			  if (!level1 && checkCarRange2()){
				 posX = posX + 0.5;
			 }

		 }
		 else if (key == 's'){
			 posX = posX + 0.5;
			 if (level1 && checkCarRange()){
				 posX = posX - 0.5;
			 }
			  if (!level1 && checkCarRange2()){
				 posX = posX - 0.5;
			 }

		 }
		 else if (key == 'a'){
			 posZ = posZ + 0.5;
			 if (level1 && checkCarRange()){
				 posZ = posZ + 0.5;
			 }
			  if (!level1 && checkCarRange2()){
				 posZ = posZ + 0.5;
			 }
		 }
		 else if (key == 'd'){
			 posZ = posZ - 0.5;
			 if (level1 && checkCarRange()){
				 posZ = posZ - 0.5;
			 }
			  if (!level1 && checkCarRange2()){
				 posZ = posZ - 0.5;
			 }


		 }
	 }


 }
 void refreshCamera(){
	 if (posX > 0){
		 At.x = posX ;
	 }
	 else{
		 At.x = posX ;

	 }
	 if (posZ > 0){
		 At.z = posZ;
	 }
	 else{
		 At.z = posZ;
	 }
	
	 At.z = posZ;
	 Eye.x = posX - 10;
	 Eye.z = posZ - 10;
	 if (angleX >= 90 && angleX < 180){
		 Eye.x = posX - 10-3.6;
		 Eye.z = posZ - 10+7.0;
	 }
	 glLoadIdentity();
	 //Clear Model_View Matrix
	 
	 gluLookAt(Eye.x, Eye.y, Eye.z, At.x, At.y, At.z, Up.x, Up.y, Up.z);
	// glRotated(45, 0, 1, 0);
	// cameraWidth = 672;
	// glRotatef(angleX, 0.0f, 1.0f, 0.0f);
	 
	 
 }
 void refreshCamera1(){
	 if (posX > 0){
		 At.x = posX;
	 }
	 else{
		 At.x = posX;

	 }
	 if (posZ > 0){
		 At.z = posZ;
	 }
	 else{
		 At.z = posZ;
	 }

	 At.z = posZ;
	 Eye.x = posX - 10;
	 Eye.z = posZ - 10;
	 if (angleX >= 90 && angleX < 180){
		 Eye.x = posX - 10 - 3.6;
		 Eye.z = posZ - 10 + 7.0;
	 }
	 glLoadIdentity();
	 //Clear Model_View Matrix

	 gluLookAt(Eye.x, Eye.y - 5, Eye.z + 3, At.x, At.y, At.z - 8, Up.x, Up.y, Up.z);
	 // glRotated(45, 0, 1, 0);
	 // cameraWidth = 672;
	 // glRotatef(angleX, 0.0f, 1.0f, 0.0f);
 }
void myKeyboard(unsigned char button, int x, int y)
{
	if (finished_game || times_up)
		return;
	if (ability){
		ability_counter--;
		if (ability_counter > 0){
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);;
		}
	}
	switch (button)
	{
	case '1':
		third_person = false;
		break;
	case '3':
		third_person = true;
		break;
	case'p': 
		sysAngle=sysAngle+1;
		printf("THE ANGLE IS %f", sysAngle);
		break;
	case'o':
		sysAngle=sysAngle-1;
		printf("THE ANGLE IS %f", sysAngle);
		break;
	case 'i':
		car3X++;
		printf("THE CAR IS AT (%d,%d)", car3X, car3Z);
		break;
	case 'u':
		car3X--;
		printf("THE CAR IS AT (%d,%d)", car3X, car3Z);
		break;
	case 'h':
		car3Z++;
		printf("THE CAR IS AT (%d,%d)", car3X, car3Z);
		break;
	case 'j':
		car3Z--;
		printf("THE CAR IS AT (%d,%d)", car3X, car3Z);
		break;

	case'k':
		refreshCamera();
		break;
	case'l':
		refreshCamera();
		break;
	case 't':
		if (!ability){
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			ability = true;
		}	
		break;
	case 'r':
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		break;
	case 'w':
		move(button);
		if (third_person){
			refreshCamera();
		}
		if (!third_person){
			refreshCamera1();
		}
		break;
	case 's':
		move(button);
		if (third_person){
			refreshCamera();
		}
		if (!third_person){
			refreshCamera1();
		}
		break;
	case 'a':
		move(button);
		if (third_person){
			refreshCamera();
		}
		if (!third_person){
			refreshCamera1();
		}
		break;
	case 'd':
		move(button);
		if (third_person){
			refreshCamera();
		}
		if (!third_person){
			refreshCamera1();
		}
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
		//sysAngle = sysAngle +22.5;
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
		if (level1){
			attack();
		}
		else{
			attackDragon();
		}
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
	x = WIDTH - x;

	if (cameraWidth - x > 0)
	{
		Eye.z += -0.1;
		Eye.x += 0.1;
		printf("THE EYE is AT (%f,%f) \n",Eye.x,Eye.z);
	}
	else
	{
		Eye.z += 0.1;
		Eye.x += -0.1;
		printf("THE EYE is AT (%f,%f) \n", Eye.x, Eye.z);

	}

	cameraWidth = x;
	//cameraZoom = y;

	glLoadIdentity();													//Clear Model_View Matrix

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
	x = WIDTH - x;

	if (state == GLUT_DOWN)
	{
		cameraZoom = y;
		cameraWidth = x;
		printf("3RD PERSON CAMERA %d \n",cameraWidth);
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
		times_up = true;
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		//printf("GAME OVER ! \n");
		//exit(0);
	}
	else{
		//printf("TIME REMAING: %d \n", time);
		//printf("FRAMES REMAING: %d \n", frames);
		//printf("------------------------------------------\n");
	}


	if (!bluAlive && !grnAlive && !ylwAlive && !orgAlive &&incTime){
		level1 = false;
		incTime = false;
		time = time+60;
		glClearColor(0.0f, 0.0f, 0.2f, 0.0f);
	}
	if (!blueDragonAlive && !greenDragonAlive && !yellowDragonAlive && !orangeDragonAlive && !redDragonAlive && !finished_game){
		//calculate score
		finished_game = true;
		score = score + (time * 50);
		sprintf(skr, "%d", score);
		printf("YOU HAVE DEFEATED ALL ENEMIES \n");
		printf("YOUR SCORE IS %d \n",score);
		

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
	dragon.Load("Models/dragon/Dragon 2.5_3ds.3ds");
	model_car.Load("Models/car/Car.3ds");
	model_truck.Load("Models/truck/gaz.3DS");
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