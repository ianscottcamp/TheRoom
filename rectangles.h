#ifndef RECTANGLES_H
#define RECTANGLES_H
class rectangles{

public:
int base_counter;
double x,y,z,w,h;
double r,g,b;
GLuint texture;
rectangles(){x=0;y=0;z=0;w=0;h=0;texture=0;r=1;g=1;b=1;base_counter=0;}
rectangles(double mx, double my, double mz, double mw, double mh,GLuint id){x=mx;y=my;z=mz;w=mw/2;h=mh/2;texture=id;r=1;g=1;b=1;base_counter=0;}
void CountUp(){
base_counter++;
}
void Color(double r1,double g1,double b1){
r=r1;g=g1;b=b1;
}
void drawTex(){

 glColor3d(r, g, b);
    glLoadIdentity();                           
    glTranslatef(0.0f,0.0f,-5.0f);  
	glBindTexture(GL_TEXTURE_2D, texture);
	glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(x+w,y-h,z);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(x-w,y-h,z);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(x-w,y+h,z);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(x+w,y+h,z);
	glEnd();


}
void draw(){

 glColor3d(r, g, b);
	glBegin(GL_POLYGON);
		glVertex3f(x+w,y-h,z);
		glVertex3f(x-w,y-h,z);
		glVertex3f(x-w,y+h,z);
		glVertex3f(x+w,y+h,z);
	glEnd();
	}
};
#endif
