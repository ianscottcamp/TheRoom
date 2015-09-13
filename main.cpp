using namespace std;
#include <iostream>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include "math.h"
#include "SOIL.h"
#include <GL/glut.h>
#include "LoadTextures.h"
#include "collision.h"
#include "player.h"
#include "enemy.h"
#include "dungeon/generate.h"

int gamestatus=0;
bool camera=false;
double camx=0,camy=0,camvx=0,camvy=0;
double speed = 0.06; 
bool r = false, l = false, u = false, d = false; 

room* current_room;
vector<rectangles*> walls;

player* p1;
rectangles* bg;
rectangles* tri;
rectangles* win;
rectangles* lose;
vector<rectangles*> hearts;
void BuildObjects(){
SetFloorBounds(5,5,10,20);
generateFloor();
PrintMap();
vector<room*> tri_room;

		
for(int i=ymax_floor_size-1;i>=0;i--)
	{
	for(int j=0;j<xmax_floor_size;j++)
		{
		if(floormap[j][i]!=0)
		{
		floormap[j][i]->PopulateRoom();
		tri_room.push_back(floormap[j][i]); 
		}
		}
	}
current_room=floormap[xmax_floor_size/2][ymax_floor_size/2];
current_room->enemies.clear();
for(int i=0;i<tri_room.size();i++){
if(current_room==tri_room[i]){tri_room.erase(tri_room.begin() + i);}
}
tri_room[rand()%tri_room.size()]->triforce=true;


current_room=floormap[xmax_floor_size/2][ymax_floor_size/2];
bg=new rectangles(0,0,0,10,10,texture[2]);
p1=new player(0,0,5,.7,.7,texture[0]);
tri=new rectangles(0,0,1,.7,.7,texture[6]);
win=new rectangles(0,0,7,2,1.5,texture[7]);
lose=new rectangles(0,0,7,3,2,texture[10]);
walls.push_back(new rectangles(0,-5,0,10,1.15,0));
walls.push_back(new rectangles(0,5,0,10,1.15,0));
walls.push_back(new rectangles(-5,0,0,.7,10,0));
walls.push_back(new rectangles(5,0,0,.7,10,0));
hearts.push_back(new rectangles(3,4.6,10,.5,.5,texture[8]));
hearts.push_back(new rectangles(3.5,4.6,10,.5,.5,texture[8]));
hearts.push_back(new rectangles(4,4.6,10,.5,.5,texture[8]));
}
void resize(int w, int h)

{
   glViewport(0, 0, (GLsizei) w, (GLsizei) h); 
   glMatrixMode(GL_PROJECTION); 
   glLoadIdentity();
   if (w <= h)  
      glOrtho(-5.0, 5.0, -5.0*(GLfloat)h/(GLfloat)w, 
               5.0*(GLfloat)h/(GLfloat)w, -5.0, 5.0);

   else
      glOrtho(-5.0*(GLfloat)w/(GLfloat)h, 
               5.0*(GLfloat)w/(GLfloat)h, -5.0, 5.0, -5.0, 5.0);

   glMatrixMode(GL_MODELVIEW); 
   glLoadIdentity();
}
void processNormalKeys(unsigned char key, int x, int y) {

	if (key == 27){	exit(0);}
	if (key =='c'){if(camera){camera=false;}else camera=true;}

}

void keypress(int key,int x,int y){

  if(key == GLUT_KEY_RIGHT ){r = true; }
  else if(key == GLUT_KEY_LEFT){l = true; }
  else if(key == GLUT_KEY_UP){u = true; }
  else if(key == GLUT_KEY_DOWN){d = true; }

}

void keyrelease(int key,int x,int y){

  if(key == GLUT_KEY_RIGHT){r = false;p1->SpriteFrame(7); }
  else if(key == GLUT_KEY_LEFT){l = false; p1->SpriteFrame(5);}
  else if(key == GLUT_KEY_UP){u = false;p1->SpriteFrame(6); }
  else if(key == GLUT_KEY_DOWN){d = false; p1->SpriteFrame(4);}

}


void Updatep1(){
if(current_room->triforce){if(overlap(*p1,*tri)){current_room->triforce=false;
gamestatus=1;
}}
p1->invulnerable();
for(int i=0; i<current_room->enemies.size();i++){
if(overlap(*p1,*current_room->enemies[i])){if(!p1->Health()){gamestatus=-1;}}
}
if(r && (collision(speed,0,*p1,walls)==0)){p1->x+=speed;p1->SpriteFrame(3);}
if(l && (collision(-speed,0,*p1,walls)==0)){p1->x-=speed;p1->SpriteFrame(1);} 
if(u && (collision(0,speed,*p1,walls)==0)){p1->y+=speed;p1->SpriteFrame(2);} 
if(d && (collision(0,-speed,*p1,walls)==0)){p1->y-=speed;p1->SpriteFrame(0);}

rectangles* opendoor=collision(0,0,*p1,current_room->doors);
if(opendoor!=0){

int choice = current_room->OpenDoor(opendoor);
int xchange=current_room->x,ychange=current_room->y;
switch(choice)
			{
			case 0:ychange+=1;p1->y=p1->y*-1+speed;break;
			case 1:xchange+=1;p1->x=p1->x*-1+speed;break;
			case 2:ychange-=1;p1->y=p1->y*-1-speed;break;
			case 3:xchange-=1;p1->x=p1->x*-1-speed;break;
			}

current_room=floormap[xchange][ychange];


}
}

void Draw(void)
{
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


if(gamestatus==0)Updatep1();
if(gamestatus==1){
if(win->base_counter<10){win->Color(1,0,1);}
if(win->base_counter>10){win->Color(1,1,1);}
if(win->base_counter>20){win->base_counter=0;}
win->CountUp();
win->drawTex();
p1->SpriteFrame(8);
}
if(gamestatus==-1){
lose->drawTex();
p1->SpriteFrame(9);
}
bg->drawTex();
p1->drawTex();
for(int i=0; i<hearts.size();i++){
if(p1->hp<=i){hearts[i]->texture=texture[9];}
hearts[i]->drawTex();
}
for(int i=0; i<current_room->enemies.size();i++){
if(!gamestatus){current_room->enemies[i]->UpdatePosition(walls);}
current_room->enemies[i]->drawTex();
}
for(int i=0;i<current_room->doors.size();i++)
{
current_room->doors[i]->drawTex();
}

if(current_room->triforce)tri->drawTex();


glutSwapBuffers();
}


int main(int argc, char **argv)
{

glutInit(&argc, argv);
glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(300,100);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Triforce Quest");

glutReshapeFunc(resize);
glutDisplayFunc(Draw);
glutIdleFunc(Draw);
	glutKeyboardFunc(processNormalKeys);
glutSpecialFunc(keypress);
glutSpecialUpFunc(keyrelease);

	/////////////////////////////////////

    glEnable(GL_TEXTURE_2D);                     
    glShadeModel(GL_SMOOTH);               
    glAlphaFunc(GL_GREATER, 0.1);
    glEnable(GL_ALPHA_TEST);
    glClearColor(0.0f, 0.0f, 0.0f, 0.5f);            
    glClearDepth(1.0f);                   
    glEnable(GL_DEPTH_TEST);                   
    glDepthFunc(GL_LEQUAL);                   
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); 
imageFiles();
LoadGLTextures();
	BuildObjects();
    glutMainLoop();
return 1;
}

