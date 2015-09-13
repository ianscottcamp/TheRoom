#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include "room.h"
using namespace std;

	int xmax_floor_size=5;
	int ymax_floor_size=5;
	int minrooms=7;
	int maxrooms=10;
	//Build connections_allowed 0:clumped	1:normal  2:spread
	int connections_allowed=4;		
	vector<room*> roomlist;
	vector<vector<room*> > floormap;

	//Check Room Connections
	vector<int> NotConnected(bool connect[])
	{
		vector<int> list;
		for(int i=0;i<4;i++)
		{
			if(connect[i]==false){list.push_back(i);}
		}
		return list;
	}

	//INSERT NEW ROOM TO MAP
	void InsertRoom(int x,int y)
	{	//System.out.println("new room:"+x+","+y);
		roomlist.push_back(floormap[x][y]=new room(x,y));
		

	}

//FOOR GENERATOR
	void MakeFloor()
	{
		vector<int> link;
		int index;
		
		do{
		index=rand()%roomlist.size();
		link=NotConnected(roomlist[index]->connect);
		if(4-link.size()>=connections_allowed){roomlist.erase(roomlist.begin()+index);}
		else
		{	
			int choice=link[rand()%link.size()];

			int xchange=0,ychange=0;
			int xnew=0,ynew=0;
			switch(choice)
			{
			case 0:ychange=1;break;
			case 1:xchange=1;break;
			case 2:ychange=-1;break;
			case 3:xchange=-1;break;
			}

			xnew=roomlist[index]->x+xchange;
			ynew=roomlist[index]->y+ychange;

			if((xnew>=0&&xnew<xmax_floor_size)&&(ynew>=0&&ynew<ymax_floor_size))
			{
				if(floormap[xnew][ynew]==0)
				{	
				roomlist[index]->connect[choice]=true;
				floormap[roomlist[index]->x][roomlist[index]->y]->connect[choice]=true;
					InsertRoom(xnew,ynew);
					choice+=2;
					if(choice>3)choice-=4;
					roomlist.back()->connect[choice]=true;
					floormap[xnew][ynew]->connect[choice]=true;
					maxrooms--;
				}
			}
		}
		}while(maxrooms>0);
roomlist.clear();
	}


//PRINT THE MAP
	void PrintMap()
	{
		for(int i=ymax_floor_size-1;i>=0;i--)
		{
			for(int j=0;j<xmax_floor_size;j++)
			{
				if(floormap[j][i]!=0)cout<<"["<<floormap[j][i]->x<<","<<floormap[j][i]->y<<"]";
				else cout<<"  -  ";
			}
			cout<<endl;
		}
	}

void SetFloorBounds(int x,int y, int min, int max){
xmax_floor_size=x;
ymax_floor_size=y;
minrooms=min;
maxrooms=max;

}

	void generateFloor(){
  floormap.resize(ymax_floor_size);
  for (int i = 0; i < ymax_floor_size; ++i)
    floormap[i].resize(xmax_floor_size);
		srand (time(NULL));
		maxrooms=rand()%(1+maxrooms-minrooms)+minrooms-1;
		cout<<"Rooms:"<<maxrooms+1<<endl;
		InsertRoom(xmax_floor_size/2,ymax_floor_size/2);
		MakeFloor();
		
	}

