/* 这一文件用于冒险模式的具体实现 */
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
#include "drawn.h"
#include "paperwork.h"
#include "adventure.h"

extern bool IsAdventuring;

extern int maze[msize][msize];

extern int player[msize][msize];

extern int viewSize;

extern struct EdittedMaze *adventure_head,*p;

void StartAdventure()
{
	if(IsAdventuring){
		p = adventure_head;
		
		player[2][2]=6;
		viewSize = 3; 
		int i,j;
		for(i=0;i<msize;i++){
			for(j=0;j<msize;j++){
				maze[i][j]=p->Maze[i][j];
			}
		}
	}
}

void JudgeLevel(double winwidth, double winheight, double fH, int CurrentLevel)
{
	switch(CurrentLevel){
		case 1: 
				break;
		case 2: WriteAdventure2(winwidth, winheight, fH);
				break;
		case 3: WriteAdventure3(winwidth, winheight, fH);
				break;
		case 4: WriteAdventure4(winwidth, winheight, fH);
				break;
		case 5: WriteAdventure5(winwidth, winheight, fH);
				viewSize = 1;
				break;
		case 6: WriteAdventure6(winwidth, winheight, fH);
				break;
		case 7: WriteAdventure7(winwidth, winheight, fH);
				viewSize = 0;
				break;
		case 8: WriteAdventure8(winwidth, winheight, fH);
				break;
		case 9: WriteAdventure9(winwidth, winheight, fH);
				viewSize = 100;
				break;
		default:break;
	}
	
}


 
