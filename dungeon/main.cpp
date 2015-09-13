#include "generate.h"
int main(){
generateFloor();
PrintMap();
int x,y;
while(true){
cout<<"x:";
cin>>x;
if(x==-1)break;
cout<<endl<<"y:";
cin>>y;
for(int i=0;i<4;i++){cout<<showmap[x][y]->connect[i];}
cout<<endl;}
return 0;
}
