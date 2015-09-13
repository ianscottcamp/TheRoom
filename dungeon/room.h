//#include "rectangles.h"
#include <vector>
class room{
public:
bool triforce;
int x,y;
vector<enemy*> enemies;
vector<rectangles*> doors;
//connect order : 0)North, 1)East, 2)South, 3)West 
bool connect[4];
room(){x=y=0;for(int i=0;i<4;i++)connect[i]=false;triforce=false;}
room(int a, int b){x=a;y=b;for(int i=0;i<4;i++)connect[i]=false;triforce=false;}

void PopulateRoom(){
PlaceDoors();
PlaceEnemies();
}

void PlaceEnemies(){
int count=rand()%6;

for(int i=0;i<count;i++){
enemies.push_back(new enemy(rand()%3,rand()%3,1,.7,.7,texture[5]));
}
}

void PlaceDoors(){

if(connect[0]){doors.push_back(new rectangles(0,4.66,0,2,.65,texture[4]));}
if(connect[1]){doors.push_back(new rectangles(4.78,0,0,.55,2.4,texture[3]));}
if(connect[2]){doors.push_back(new rectangles(0,-4.66,0,2,.65,texture[4]));}
if(connect[3]){doors.push_back(new rectangles(-4.78,0,0,.55,2.4,texture[3]));}
}
int OpenDoor(rectangles* door){
if(door->y>0)return 0;
if(door->x>0)return 1;
if(door->y<0)return 2;
if(door->x<0)return 3;
return -1;
}
};
