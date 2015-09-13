#ifndef ENEMY_H
#define ENEMY_H
#include "rectangles.h"
#include "collision.h"
#include <stdlib.h>
class enemy:public rectangles{
public:
int timechange;
int timer;
float positions[4][2];
double xdir;
double ydir;
int image; 
enemy(){x=0;y=0;z=0;w=0;h=0;texture=0;EnemyPositions();}
enemy(double mx, double my, double mz, double mw, double mh,GLuint id){x=mx;y=my;z=mz;w=mw/2;h=mh/2;texture=id;
timechange=0;timer=0;xdir=0;ydir=0;EnemyPositions();}

void UpdatePosition(vector<rectangles*> list){
timer++;
if(timer>=timechange){timer=0;timechange=rand()%70+30;

xdir=(double)(rand()%3-1)/20;
ydir=(double)(rand()%3-1)/20;
}

if(collision(xdir,ydir,*this,list)==0)
{
x+=xdir;
y+=ydir;
}
}

void EnemyPositions(){
image = rand()%4;
positions[0][0]=0;positions[0][1]=207;
positions[1][0]=0;positions[1][1]=0;
positions[2][0]=0;positions[2][1]=148;
positions[3][0]=0;positions[3][1]=57;
}

void drawTex(){
float width=435,height=226;
float boxw=18,boxh=20;
float posx=positions[image][0],posy=positions[image][1];
float x1=0,y1=0,x2=0,y2=0;
x1=posx/width;
y1=posy/height;
x2=(posx+boxw)/width;
y2=(posy+boxh)/height;


 glColor3d(1, 1, 1);
    glLoadIdentity();                           
    glTranslatef(0.0f,0.0f,-5.0f);  
	glBindTexture(GL_TEXTURE_2D, texture);
	glBegin(GL_QUADS);
    glTexCoord2f(x1, y1); glVertex3f(x+w,y-h,z);
    glTexCoord2f(x2, y1); glVertex3f(x-w,y-h,z);
    glTexCoord2f(x2, y2); glVertex3f(x-w,y+h,z);
    glTexCoord2f(x1, y2); glVertex3f(x+w,y+h,z);
	glEnd();



}
void draw(){

 glColor3d(1, 0, 1);
	glBegin(GL_POLYGON);
		glVertex3f(x+w,y-h,z);
		glVertex3f(x-w,y-h,z);
		glVertex3f(x-w,y+h,z);
		glVertex3f(x+w,y+h,z);
	glEnd();
	}
};
#endif
