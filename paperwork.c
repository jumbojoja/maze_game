//这一文件用于存放写文案的函数 
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
#include "paperwork.h"

#define msize 20
#define length 0.35

void WriteInstructions(double winwidth, double winheight, double w, double fH)
{
	SetPenColor("Orange");
	MovePen(winwidth/2+1.8*w, winheight/2);
	DrawTextString("Use <- ^ v -> to move.");
	MovePen(winwidth/2+1.8*w, winheight/2-fH);
	DrawTextString("Pause->Restart to restart.");
	MovePen(winwidth/2+1.8*w, winheight/2-2*fH);
	DrawTextString("Edit->Clean to clear solved path.");
	MovePen(winwidth/2+1.8*w, winheight/2-3*fH);
	DrawTextString("Edit->Regenerate to regenerate maze.");
	MovePen(winwidth/2+1.8*w, winheight/2-4*fH);
	DrawTextString("Edit->Edit Manually to edit maze.");
	MovePen(winwidth/2+1.8*w, winheight/2-5*fH);
	DrawTextString("Solve->Auto Solve to solve maze.");
	MovePen(winwidth/2+1.8*w, winheight/2-6*fH);
	DrawTextString("Solve->Tips to see tips.");
	MovePen(winwidth/2+1.8*w, winheight/2-7*fH);
	DrawTextString("Set view to set your view.");
} 

void WriteAbout(double winwidth, double winheight, double fH)
{
	SetPenColor("Orange");
	MovePen(1, winheight*0.8);
	DrawTextString("We are a C team from Zhejiang University.");
	MovePen(1, winheight*0.8-fH);
	DrawTextString("This maze game has cost us over a month to finish.");
	MovePen(1, winheight*0.8-2*fH);
	DrawTextString("In this procedure, we came across many difficulties...");
	MovePen(1, winheight*0.8-3*fH);
	DrawTextString("However, we were having great fun too.");
	MovePen(1, winheight*0.8-4*fH);
	DrawTextString("Our work is small, but it does contain some very interesting functions.");
	MovePen(1, winheight*0.8-5*fH);
	DrawTextString("Hope you will like it.");
	MovePen(winwidth/2-0.5*TextStringWidth("Thank you for playing our game."), winheight/13+2*fH);
	DrawTextString("Thank you for playing our game.");
}

void WriteEditManually(double winwidth, double winheight, double fH){
	SetPenColor("Orange");
	MovePen(0, winheight*0.8-fH);
	DrawTextString("Use the left button of your mouse to add walls(Red).");
	MovePen(0, winheight*0.8-2*fH);
	DrawTextString("Use the right button of your mouse to add keys.");
	MovePen(0, winheight*0.8-3*fH);
	DrawTextString("Use the middle button of your mouse to add events.");
	MovePen(0, winheight*0.8-5*fH);
	DrawTextString("If you have finished your edit work,");
	MovePen(0, winheight*0.8-6*fH);
	DrawTextString("you can type in the name of your maze");
	MovePen(0, winheight*0.8-7*fH);
	DrawTextString("and click save to save it.");
	MovePen(0, winheight*0.8-8*fH);
	DrawTextString("You can later find your maze in Choosing Maps.");
	MovePen(0, winheight*0.8-10*fH);
	DrawTextString("The blue cell stands for the start point.");
	MovePen(0, winheight*0.8-11*fH);
	DrawTextString("The orange cell stands for the finish point.");
}
