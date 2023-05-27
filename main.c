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

#define msize 20
#define length 0.25
//墙和路径的标识
#define WALL  1
#define ROUTE 0
//控制迷宫的复杂度，数值越大复杂度越低，最小值为0
static int Rank = 1;

static double winwidth, winheight;   // 窗口尺寸

bool IsEditManually = FALSE;

static double startx,starty;

int maze[msize][msize] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
						  -1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,-1,
						  -1, 2, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1,-1,
					      -1, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1, 1, 1, 0, 0, 0, 1, 0, 1,-1,
				 	      -1, 1, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 1, 1, 1, 1, 1,-1,
					      -1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1,-1,
					      -1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 0, 1,-1,
				          -1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 0, 0, 0, 1, 0, 1,-1,
					      -1, 1, 0, 0, 0, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 0, 0, 0, 1,-1,
					      -1, 1, 1, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 1, 1,-1,
						  -1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 1, 1,-1,
						  -1, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 1, 0, 0, 1,-1,
						  -1, 1, 0, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 1,-1,
						  -1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1,-1,
						  -1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 1,-1,
						  -1, 1, 0, 0, 1, 0, 1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1,-1,
						  -1, 1, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 1,-1,
						  -1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 3,-1,
						  -1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,-1,
						  -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1}; 

int player[msize][msize] = {0};
static int ccx = 2, ccy = 2;
static haveKey = 0;
static int ifwin = 0;
static int viewSize = 3;
 
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

//画中心圆 
void DrawCenteredCircle(double x, double y, double r);/*画中心圆*/



// 用户的键盘事件响应函数
void KeyboardEventProcess(int key, int event)
{
	double x = 0; //fH/8;
	double y = winheight;
	x = winwidth/15 + 0.3;
	y = winheight/8*7 - 0.2;
	//uiGetKeyboard(key,event); // GUI获取键盘
	display();
	switch(event)
	{
		case KEY_DOWN:
			switch(key)
			{
				case VK_UP:
					if(ccx == 0)
						break;     
                	if(maze[ccx-1][ccy] == 0 || maze[ccx-1][ccy] == 3)
					{
						player[ccx][ccy] = 0;
						ccx -=1;
						player[ccx][ccy] = 6;
					}
					else if(maze[ccx-1][ccy] == 4)
					{
						haveKey = 1;
						player[ccx][ccy] = 0;
                		ccx -= 1;
						player[ccx][ccy] = 6;	
					}
					else if(maze[ccx-1][ccy] == 5)
					{
						if(haveKey)
						{
							player[ccx][ccy] = 0;
                			ccx -= 1;
							player[ccx][ccy] = 6;	
						}
						
					}
                     break;
			     case VK_DOWN:
			     	if(ccx == msize-1)
			     		break;
			         if(maze[ccx+1][ccy] == 0 || maze[ccx+1][ccy] == 3)  
                	{
                		player[ccx][ccy] = 0;
                		ccx += 1;
						player[ccx][ccy] = 6;
					}
					else if(maze[ccx+1][ccy] == 4)
					{
						haveKey = 1;
						player[ccx][ccy] = 0;
                		ccx += 1;
						player[ccx][ccy] = 6;	
					}
					else if(maze[ccx+1][ccy] == 5)
					{
						if(haveKey)
						{
							player[ccx][ccy] = 0;
                			ccx += 1;
							player[ccx][ccy] = 6;	
						}
						
					}
                     break;
			     case VK_LEFT:
			     	if(ccy == 0)
			     		break;
			         if(maze[ccx][ccy-1] == 0 || maze[ccx][ccy-1] == 3)  
                	{
                		player[ccx][ccy] = 0;
                		ccy -= 1;
						player[ccx][ccy] = 6;
					}
					else if(maze[ccx][ccy-1] == 4)
					{
						haveKey = 1;
						player[ccx][ccy] = 0;
                		ccy -= 1;
						player[ccx][ccy] = 6;	
					}
					else if(maze[ccx][ccy-1] == 5)
					{
						if(haveKey)
						{
							player[ccx][ccy] = 0;
                			ccy -= 1;
							player[ccx][ccy] = 6;	
						}
						
					}
                     break;
			     case VK_RIGHT:
			     	if(ccy == msize-1)
			     		break;
			         if(maze[ccx][ccy+1] == 0 || maze[ccx][ccy+1] == 3)  
                	{
                		player[ccx][ccy] = 0;
                		ccy += 1;
						player[ccx][ccy] = 6;
					}
					else if(maze[ccx][ccy+1] == 4)
					{
						haveKey = 1;
						player[ccx][ccy] = 0;
                		ccy += 1;
						player[ccx][ccy] = 6;	
					}
					else if(maze[ccx][ccy+1] == 5)
					{
						if(haveKey)
						{
							player[ccx][ccy] = 0;
                			ccy += 1;
							player[ccx][ccy] = 6;	
						}
						
					}
                     break;
                default: break;
			}
			if(maze[ccx][ccy] == 3)
				ifwin = 1;
			break;
		case KEY_UP:
			 break;
	}
	 // 刷新显示
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
	player[ccx][ccy] = 6;
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

	
	SetPenColor("Red"); 
    SetPenSize(1);
    
}

//绘制迷宫 
void drawmaze(int maze[msize][msize], int x, int y) 
{
	int i, j;
	SetPenColor("Red");
	for (i = 0; i < msize; i++) {
		for (j = 0; j < msize; j++) {
			if (maze[i][j] == 0 && abs(i-ccx) <= viewSize && abs(j-ccy)<=viewSize) {
				MovePen(x + length*j,y - length*i);
				DrawLine(length,0);
				DrawLine(0,-1.0*length);
				DrawLine(-1.0*length,0);
				DrawLine(0,length);
			} else if (maze[i][j] == 1 && abs(i-ccx) <= viewSize && abs(j-ccy)<=viewSize) {
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
				SetPenColor("Orange");
				DrawLine(length,0);
				DrawLine(0,-1.0*length);
				DrawLine(-1.0*length,0);
				DrawLine(0,length);
				EndFilledRegion();
				SetPenColor("Red");
			}else if (maze[i][j] == -1) {
				MovePen(x + length*j,y - length*i);
				StartFilledRegion(1); 
				SetPenColor("Gray");
				DrawLine(length,0);
				DrawLine(0,-1.0*length);
				DrawLine(-1.0*length,0);
				DrawLine(0,length);
				EndFilledRegion();
				SetPenColor("Red");
			}
			if(player[i][j] == 6){
				MovePen(x + length*j,y - length*i);
				SetPenColor("Black");
				StartFilledRegion(1); 
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
	static char * menuListView[] = {"Set view",
		"easy",
		"difficult",
		"blind",
		"God's perspective"};
	static char * selectedLabel = NULL;
	
	static int ifStartbutton = 1;
	static int ifExitbutton = 1;
	static int ifListPause = 0;
	static int ifListEdit = 0;
	static int ifListHelp = 0;
	static int ifListSize = 1; 
	static int ifListView = 0;
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
			ifListView = 1;
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
				for (i = 0; i < msize; i++){
					maze[i][0] = -1;
					maze[0][i] = -1;
					maze[i][msize - 1] = -1;
					maze[msize - 1][i] = -1;
				}
			}
		}
		if( selection==4 ){
			StoreMaze();
		}
		if( selection==2){
			mazehelper(maze,2,2);
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
	
	//View 菜单
	if (ifListView) {
		selection = menuList(GenUIID(0),x+3*w,y-h, w, wlist, h, menuListView,sizeof(menuListView)/sizeof(menuListView[0]));
		if( selection>0 ) selectedLabel = menuListView[selection];
		if( selection == 1)
			viewSize = 2;
		if( selection == 2)
			viewSize = 1;
		if( selection == 3)
			viewSize = 0;
		if( selection == 4)
			viewSize = 100;
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
	
	//判断是否到达终点
	if(ifwin){
		ifdrawmaze = 0;
		MovePen(4, 4);
		DrawTextString("You win!");
		ifwin = 0;
		ccx = 2;
		ccy = 2;
	}
	 
}

void display()
{
	// 清屏
	DisplayClear();

	// 绘制和处理菜单
	drawMenu();
}

bool inBox(double x, double y, double x1, double x2, double y1, double y2)
{
	return (x >= x1 && x <= x2 && y >= y1 && y <= y2);
}

//迷宫生成 
void CreateMaze(int maze[msize][msize], int x, int y) {
	maze[x][y] = ROUTE;
 	int i, j, k;
	//确保四个方向随机
	int direction[4][2] = { { 1,0 },{ -1,0 },{ 0,1 },{ 0,-1 } };
	for (i = 0; i < 4; i++) {
		int r = rand() % 4;
		int temp = direction[0][0];
		direction[0][0] = direction[r][0];
		direction[r][0] = temp;
 
		temp = direction[0][1];
		direction[0][1] = direction[r][1];
		direction[r][1] = temp;
	}
 
	//向四个方向开挖
	for (i = 0; i < 4; i++) {
		int dx = x;
		int dy = y;
 
		//控制挖的距离，由Rank来调整大小
		int range = 1 + (Rank == 0 ? 0 : rand() % Rank);
		while (range>0) {
			dx += direction[i][0];
			dy += direction[i][1];
 
			//排除掉回头路
			if (maze[dx][dy] == ROUTE) {
				break;
			}
 
			//判断是否挖穿路径
			int count = 0;
			for (j = dx - 1; j < dx + 2; j++) {
				for (k = dy - 1; k < dy + 2; k++) {
					//abs(j - dx) + abs(k - dy) == 1 确保只判断九宫格的四个特定位置
					if (abs(j - dx) + abs(k - dy) == 1 && maze[j][k] == ROUTE) {
						count++;
					}
				}
			}
 
			if (count > 1) {
				break;
			}
 
			//确保不会挖穿时，前进
			--range;
			maze[dx][dy] = ROUTE;
		}
 
		//没有挖穿危险，以此为节点递归
		if (range <= 0) {
			CreateMaze(maze, dx, dy);
		}
	}
}

void mazehelper(int maze[msize][msize], int x, int y) {
	//初始化 
	int i, j;
	for (i = 0; i < msize; ++i) {
		for (j = 0; j < msize; ++j) {
			maze[i][j] = 1;
		}
	} 
    srand((unsigned)time(NULL));
 
	//最外围层设为路径的原因，为了防止挖路时挖出边界，同时为了保护迷宫主体外的一圈墙体被挖穿
	for (i = 0; i < msize; i++){
		maze[i][0] = ROUTE;
		maze[0][i] = ROUTE;
		maze[i][msize - 1] = ROUTE;
		maze[msize - 1][i] = ROUTE;
	}
 
	//创造迷宫，（2，2）为起点
	CreateMaze(maze, 2, 2);
	
	//收尾工作
	for (i = 0; i < msize; i++){
		maze[i][0] = -1;
		maze[0][i] = -1;
		maze[i][msize - 1] = -1;
		maze[msize - 1][i] = -1;
	}
 
	//画迷宫的入口和出口
	maze[2][1] = 2;
 
	//由于算法随机性，出口有一定概率不在（L-3,L-2）处，此时需要寻找出口
	for (i = msize - 3; i >= 0; i--) {
		if (maze[i][msize - 3] == ROUTE) {
			maze[i][msize - 2] = 3;
			break;
		}
	}
}
