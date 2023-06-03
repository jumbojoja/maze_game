#include "graphics.h"
#include "extgraph.h"
#include "genlib.h"
#include "simpio.h"
#include "conio.h"
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

#include <windows.h>
#include <olectl.h>
#include <mmsystem.h>
#include <wingdi.h>
#include <ole2.h>
#include <ocidl.h>
#include <winuser.h>
#include <time.h>
#include <math.h>

#include "imgui.h"
#include "file_store.h"

extern bool IsAdventuring;

extern int maze[msize][msize];

extern int player[msize][msize];

extern int viewSize;

extern struct EdittedMaze *adventure_head,*p;

//冒险模式函数，调用即开始冒险模式 
void StartAdventure(void);

void StartAdventure()
{
	if(IsAdventuring){
		p = adventure_head;
		
		player[2][2]=6;
		viewSize = 100; 
		int i,j;
		for(i=0;i<msize;i++){
			for(j=0;j<msize;j++){
				maze[i][j]=p->Maze[i][j];
			}
		}
			
		//获胜条件判断 
		
		if(p->name == "ADVENTURE_2"){
			
		}
	}
}


 
