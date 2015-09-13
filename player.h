#ifndef PLAYER_H
#define PLAYER_H
#include "rectangles.h"
class player:public rectangles{
float positions[10][2];
float boxw,boxh;
int startframe,endframe;
int framespeed,timer;
int frame;
public:
int hp;
int i_timer; 
bool invul; 
player(){x=0;y=0;z=0;w=0;h=0;texture=0;hp=3;i_timer=70;invul=false;boxw=22;boxh=25;}
player(double mx, double my, double mz, double mw, double mh,GLuint id){x=mx;y=my;z=mz;w=mw/2;h=mh/2;texture=id;
SpritePositions();hp=3;i_timer=70;invul = false;boxw=22;boxh=25;}
bool Health()
{
if (!invul)
{
hp-=1;
invul=true;
if(hp<=0){return false;}
}

return true; 
}
void invulnerable()
{
 if(invul){
i_timer--;
if (i_timer <= 0){
i_timer = 70; 
invul=false;
}
}

}
void SpritePositions(){
frame=0;
framespeed=6;
timer=0;
startframe=0;
endframe=0;
//down
positions[0][0]=30;positions[0][1]=274;
positions[1][0]=0;positions[1][1]=244;
//left
positions[2][0]=329;positions[2][1]=155;
positions[3][0]=239;positions[3][1]=155;
//up
positions[4][0]=90;positions[4][1]=155;
positions[5][0]=120;positions[5][1]=155;
//right
positions[6][0]=329;positions[6][1]=245;
positions[7][0]=239;positions[7][1]=245;
//triforce
positions[8][0]=355;positions[8][1]=39;
//dead
positions[9][0]=88;positions[9][1]=68;
}
void SpriteFrame(int choice){
switch(choice){
//moving
case 0:startframe=0;endframe=1;break;
case 1:startframe=2;endframe=3;break;
case 2:startframe=4;endframe=5;break;
case 3:startframe=6;endframe=7;break;
//standing
case 4:startframe=0;endframe=0;break;
case 5:startframe=2;endframe=2;break;
case 6:startframe=4;endframe=4;break;
case 7:startframe=6;endframe=6;break;
//triforce
case 8:w=0.5;h=0.5;boxw=30;boxh=45;startframe=8;endframe=8;break;
//dead
case 9:w=0.4;h=0.4;boxw=25;boxh=22;startframe=9;endframe=9;break;

}
}

void drawTex(){

timer++;

if(timer>=framespeed){frame++;timer=0;}
if(frame>endframe||frame<startframe){frame=startframe;}


float width=441,height=298;
float posx=positions[frame][0],posy=positions[frame][1];
float x1=0,y1=0,x2=0,y2=0;
x1=posx/width;
y1=posy/height;
x2=(posx+boxw)/width;
y2=(posy+boxh)/height;


if(invul){ 
if(timer<=framespeed/2)glColor3d(1, 0, 1);
else glColor3d(1, 1, 1);
}
else glColor3d(1, 1, 1);
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
