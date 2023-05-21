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

#include "imgui.h"

#define msize 15
#define length 0.35

static double winwidth, winheight;   // 窗口尺寸
bool IsEditManually = FALSE;

static double startx,starty;

int maze[msize][msize] = {0,0,0,1,1,1,0,0,0,0,0,1,1,0,0,
						  1,1,0,0,0,1,0,0,0,0,1,1,0,0,0,
						  0,1,0,0,0,1,1,1,0,0,0,0,0,0,0,
					      0,1,0,1,0,1,0,1,1,1,1,1,1,0,0,
				 	      0,0,0,1,0,0,0,1,0,0,1,0,0,1,1,
					      1,1,1,1,0,1,1,1,0,0,1,0,0,1,0,
					      0,1,0,0,0,0,0,0,0,0,0,0,1,1,0,
				          0,0,0,1,1,1,1,0,1,1,0,0,1,0,0,
					      0,1,0,0,0,1,0,0,0,1,0,0,1,0,1,
					      0,1,1,1,0,1,0,0,0,1,0,1,1,1,1,
						  0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,
						  1,1,1,1,1,0,0,0,1,0,0,0,1,1,1,
						  1,0,0,0,1,1,1,0,0,0,1,1,1,0,0,
						  1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,
						  0,0,0,0,1,1,1,1,1,0,0,0,0,1,1}; 

// 清屏函数，provided in libgraphics
void DisplayClear(void); 

// 用户的显示函数
void display(void);

// 画空迷宫函数 
//void DrawEmptyMaze(void);

//用于保存Maze的函数 ，使用时直接调用即可 
void StoreMaze(void);

//像素转英寸函数 
double ScaleXInches(int x);
double ScaleYInches(int y);

//判断鼠标是否在迷宫内函数 
bool inBox(double x0, double y0, double x1, double x2, double y1, double y2);

// 用户的键盘事件响应函数
void KeyboardEventProcess(int key, int event)
{
	uiGetKeyboard(key,event); // GUI获取键盘
	display(); // 刷新显示
}

// 用户的鼠标事件响应函数
void MouseEventProcess(int x, int y, int button, int event)
{
	//GUI获取鼠标 	
	if(IsEditManually == TRUE){
		switch(event){
			case BUTTON_DOWN:
				switch(button){
					case LEFT_BUTTON:{
						if(maze[(int)(((int)starty-ScaleYInches(y))/length)]
							[(int)((ScaleXInches(x)-(int)(startx))/length)]==0){
						maze[(int)(((int)starty-ScaleYInches(y))/length)]
							[(int)((ScaleXInches(x)-(int)(startx))/length)]=1;
						}else if(maze[(int)(((int)starty-ScaleYInches(y))/length)]
							[(int)((ScaleXInches(x)-(int)(startx))/length)]==1){
						maze[(int)(((int)starty-ScaleYInches(y))/length)]
							[(int)((ScaleXInches(x)-(int)(startx))/length)]=0;	
						}
						break;
					}
					case RIGHT_BUTTON:{
						if(maze[(int)(((int)starty-ScaleYInches(y))/length)]
							[(int)((ScaleXInches(x)-(int)(startx))/length)]==0){
						maze[(int)(((int)starty-ScaleYInches(y))/length)]
							[(int)((ScaleXInches(x)-(int)(startx))/length)]=2;
						}else if(maze[(int)(((int)starty-ScaleYInches(y))/length)]
							[(int)((ScaleXInches(x)-(int)(startx))/length)]==2){
						maze[(int)(((int)starty-ScaleYInches(y))/length)]
							[(int)((ScaleXInches(x)-(int)(startx))/length)]=0;	
						}
						break;
					}
					case MIDDLE_BUTTON:{
						if(maze[(int)(((int)starty-ScaleYInches(y))/length)]
							[(int)((ScaleXInches(x)-(int)(startx))/length)]==0){
						maze[(int)(((int)starty-ScaleYInches(y))/length)]
							[(int)((ScaleXInches(x)-(int)(startx))/length)]=3;
						}else if(maze[(int)(((int)starty-ScaleYInches(y))/length)]
							[(int)((ScaleXInches(x)-(int)(startx))/length)]==3){
						maze[(int)(((int)starty-ScaleYInches(y))/length)]
							[(int)((ScaleXInches(x)-(int)(startx))/length)]=0;	
						}
						break;
					}
					default: break;
					//红笔是墙 蓝笔是起点 棕笔是终点 
				}
			
		}
	}
	uiGetMouse(x,y,button,event);
	display(); // 刷新显示
}

// 用户主程序入口
// 仅初始化执行一次
void Main() 
{
	// 初始化窗口和图形系统
	SetWindowTitle("Graphics User Interface Demo");
	//SetWindowSize(10, 10); // 单位 - 英寸
	//SetWindowSize(20, 10);
	//SetWindowSize(10, 20);  // 如果屏幕尺寸不够，则按比例缩小
    InitGraphics();

	// 获得窗口尺寸
    winwidth = GetWindowWidth();
    winheight = GetWindowHeight();
    
	// 注册时间响应函数
	registerKeyboardEvent(KeyboardEventProcess);// 键盘
	registerMouseEvent(MouseEventProcess);      // 鼠标
    
	
	// 打开控制台，方便输出变量信息，便于调试
	// InitConsole() 

}

//绘制迷宫 
void drawmaze(int maze[msize][msize], int x, int y) 
{
	int i, j;
	SetPenColor("Red");
	for (i = 0; i < msize; i++) {
		for (j = 0; j < msize; j++) {
			if (maze[i][j] == 0) {
				MovePen(x + length*j,y - length*i);
				DrawLine(length,0);
				DrawLine(0,-1.0*length);
				DrawLine(-1.0*length,0);
				DrawLine(0,length);
			} else if (maze[i][j] == 1) {
				MovePen(x + length*j,y - length*i);
				StartFilledRegion(1); 
				DrawLine(length,0);
				DrawLine(0,-1.0*length);
				DrawLine(-1.0*length,0);
				DrawLine(0,length);
				EndFilledRegion(); 
			}else if (maze[i][j] == 2) {
				MovePen(x + length*j,y - length*i);
				StartFilledRegion(1); 
				SetPenColor("Blue");
				DrawLine(length,0);
				DrawLine(0,-1.0*length);
				DrawLine(-1.0*length,0);
				DrawLine(0,length);
				EndFilledRegion();
				SetPenColor("Red");
			}else if (maze[i][j] == 3) {
				MovePen(x + length*j,y - length*i);
				StartFilledRegion(1); 
				SetPenColor("Brown");
				DrawLine(length,0);
				DrawLine(0,-1.0*length);
				DrawLine(-1.0*length,0);
				DrawLine(0,length);
				EndFilledRegion();
				SetPenColor("Red");
			}
		}
	}
}

// 菜单
void drawMenu()
{ 
	static char * menuListPause[] = {"Pause",  
		"Restart  | Ctrl-R", // 快捷键必须采用[Ctrl-X]格式，放在字符串的结尾
		"Exit   | Ctrl-E"};
	static char * menuListEdit[] = {"Edit",
		"Size",
		"Regenerate",
		"Edit Manually | Ctrl-M"};
	static char * menuListHelp[] = {"Help",
		"Auto Solve  | Ctrl-A",
		"Tips"};
	static char * menuListSize[] = {"Set size",
		"15*15",
		"10*10"};
	static char * selectedLabel = NULL;
	
	static int ifStartbutton = 1;
	static int ifExitbutton = 1;
	static int ifListPause = 0;
	static int ifListEdit = 0;
	static int ifListHelp = 0;
	static int ifListSize = 1; 
	static int ifdrawmaze = 0;

	double fH = GetFontHeight(); //字体高度
	double x = 0; //fH/8;
	double y = winheight;
	double h = fH*1.5; // 控件高度
	double w = TextStringWidth(menuListHelp[0])*2; // 控件宽度
	double wlist = TextStringWidth(menuListEdit[3])*1.2;
	int    selection;
	
	// 开始按钮 
	if (ifStartbutton) {
		if (button(GenUIID(0), winwidth/2, winheight/2, w, h, "Start")) {
			ifStartbutton = 0;
			ifExitbutton = 0;
			ifListPause = 1;
			ifListEdit = 1;
			ifListHelp = 1;
			ifListSize = 0;
			ifdrawmaze = 1;
			IsEditManually = FALSE;
		}
	}
	
	// 退出按钮 
	if (ifExitbutton) {
		if (button(GenUIID(0), winwidth/2, winheight/2 - h*1.2, w, h, "Exit")) {
			exit(-1);
		}
	}
	
	// Pause 菜单
	if (ifListPause) {
		selection = menuList(GenUIID(0), x, y-h, w, wlist, h, menuListPause, sizeof(menuListPause)/sizeof(menuListPause[0]));
		if( selection>0 ) selectedLabel = menuListPause[selection];
		if( selection==2 ) {	// 退回主菜单 
			ifStartbutton = 1;
			ifExitbutton = 1;
			ifListPause = 0;
			ifListEdit = 0;
			ifListHelp = 0;
			ifListSize = 1;
			ifdrawmaze = 0;
		}
	}
		
	
	// Edit 菜单
	if (ifListEdit) {
		selection = menuList(GenUIID(0),x+w,  y-h, w, wlist,h, menuListEdit,sizeof(menuListEdit)/sizeof(menuListEdit[0]));
		if( selection>0 ) selectedLabel = menuListEdit[selection];
		if( selection==3 ){
			IsEditManually = TRUE;
			if(IsEditManually){
				ifdrawmaze = 1; 
				int i, j;
				for(i=0;i<msize;i++){
					for(j=0;j<msize;j++){
						maze[i][j]=0;
					}
				}
			}
		}
		if( selection==4 ){
			StoreMaze();
		}
	}
	
	// Help 菜单
	if (ifListHelp) {
		selection = menuList(GenUIID(0),x+2*w,y-h, w, wlist, h, menuListHelp,sizeof(menuListHelp)/sizeof(menuListHelp[0]));
		if( selection>0 ) selectedLabel = menuListHelp[selection];
	}
		
	// Size 菜单
	if (ifListSize) {
		selection = menuList(GenUIID(0),winwidth/2,winheight/2 - h*1.2*2, w, wlist, h, menuListSize,sizeof(menuListSize)/sizeof(menuListSize[0]));
		if( selection>0 ) selectedLabel = menuListSize[selection];
	}
	
	//绘制迷宫 
	if (ifdrawmaze) {
		x = winwidth/13;
		y = winheight/12*11;
		drawmaze(maze,x+5*w,y);
		startx=x+5*w;
		starty=y;
	}
	
	if(IsEditManually){
		if (button(GenUIID(0), 1, winheight/2, w, h, "Save")){
			IsEditManually=FALSE;
			StoreMaze();
		}
	}//新增保存按钮 
}

void display()
{
	// 清屏
	DisplayClear();

	// 绘制和处理菜单
	drawMenu();
}

/*void DrawEmptyMaze()
{
	int i, j;
	double w = TextStringWidth("Help")*2;
	double x=winwidth/13+5*w,y=winheight/12*11;
	SetPenColor("Blue");
	
	for (i = 0; i < msize; i++) {
		for (j = 0; j < msize; j++) {
				MovePen(x + length*j,y - length*i);
				DrawLine(length,0);
				DrawLine(0,-1.0*length);
				DrawLine(-1.0*length,0);
				DrawLine(0,length);
		}
	}
	MovePen(0,0);//做完之后将画笔移动至原点 
}*/

bool inBox(double x, double y, double x1, double x2, double y1, double y2)
{
	return (x >= x1 && x <= x2 && y >= y1 && y <= y2);
}
