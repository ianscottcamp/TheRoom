#ifndef COLLISION_H
#define COLLISION_H
#include "rectangles.h"
bool overlap(rectangles a, rectangles b){
if(a.x+a.w<b.x-b.w || a.x-a.w>b.x+b.w){return false;}
if(a.y+a.h<b.y-b.h || a.y-a.h>b.y+b.h){return false;}
return true;
}

rectangles* collision(double x, double y,rectangles obj,vector<rectangles*> list)
{

obj.x+=x;
obj.y+=y;

for(int i=0;i<list.size();i++){
if(overlap(obj,*list[i])){return list[i];}
}

return false;
}


#endif
