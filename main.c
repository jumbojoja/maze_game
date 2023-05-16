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
#include <math.h>

#include "imgui.h"

#define msize 10

// 全局变量
static double winwidth, winheight;   // 窗口尺寸
static int    enable_rotation = 1;   // 允许旋转
static int    show_more_buttons = 0; // 显示更多按钮
static int ccx = 0, ccy = 0;//玩家位置

int maze[msize][msize] = {0,0,0,1,1,1,0,0,0,0,
						  1,1,0,0,0,1,0,0,0,0,
						  0,1,0,0,0,1,1,1,0,0,
					      0,1,0,1,0,1,0,1,1,1,
				 	      0,0,0,1,0,0,0,1,0,0,
					      1,1,1,1,0,1,1,1,0,0,
					      0,1,0,0,0,0,0,0,0,0,
				          0,0,0,1,1,1,1,1,1,1,
					      0,1,0,0,0,1,0,0,0,0,
					      0,1,1,1,0,0,0,0,0,0}; 
	

 
// 清屏函数，provided in libgraphics
void DisplayClear(void); 

// 用户的显示函数
void display(void); 

//画中心圆 
void DrawCenteredCircle(double x, double y, double r);/*画中心圆*/



// 用户的键盘事件响应函数
void KeyboardEventProcess(int key, int event)
{
	double length = 0.5;
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
                	if(maze[ccx-1][ccy] == 0)
					{
						maze[ccx][ccy] = 0;
						ccx -=1;
						maze[ccx][ccy] = 2;
					}
                     break;
			     case VK_DOWN:
			         if(maze[ccx+1][ccy] == 0)  
                	{
                		maze[ccx][ccy] = 0;
                		ccx += 1;
						maze[ccx][ccy] = 2;
					}
                     break;
			     case VK_LEFT:
			         if(maze[ccx][ccy-1] == 0)  
                	{
                		maze[ccx][ccy] = 0;
                		ccy -= 1;
						maze[ccx][ccy] = 2;
					}
                     break;
			     case VK_RIGHT:
			         if(maze[ccx][ccy+1] == 0)  
                	{
                		maze[ccx][ccy] = 0;
                		ccy += 1;
						maze[ccx][ccy] = 2;
					}
                     break;
                default: break;
			}
			break;
		case KEY_UP:
			 break;
	}
	 // 刷新显示
}

// 用户的鼠标事件响应函数
void MouseEventProcess(int x, int y, int button, int event)
{
	uiGetMouse(x,y,button,event); //GUI获取鼠标
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

	
	SetPenColor("Red"); 
    SetPenSize(1);
    
}

//绘制迷宫
void drawmaze(int maze[msize][msize], int x, int y) {
	int i, j;
	double length = 0.5;
	for (i = 0; i < msize; i++) {
		for (j = 0; j < msize; j++) {
			if (maze[i][j] == 0 && abs(i-ccx) <= 3 && abs(j-ccy)<=3) {
				MovePen(x + length*j,y - length*i);
				DrawLine(length,0);
				DrawLine(0,-1.0*length);
				DrawLine(-1.0*length,0);
				DrawLine(0,length);
			} else if (maze[i][j] == 1 && abs(i-ccx) <= 3 && abs(j-ccy)<=3) {
				MovePen(x + length*j,y - length*i);
				StartFilledRegion(1); 
					DrawLine(length,0);
					DrawLine(0,-1.0*length);
					DrawLine(-1.0*length,0);
					DrawLine(0,length);
				EndFilledRegion(); 	
			}else if(maze[i][j] == 2){
				MovePen(x + length*j,y - length*i);
				StartFilledRegion(1); 
					DrawLine(length,0);
					DrawLine(0,-1.0*length);
					DrawLine(-1.0*length,0);
					DrawLine(0,length);
				EndFilledRegion(); 	
			}
		}	
	}
} 

// 菜单演示程序
void drawMenu()
{ 
	static char * menuListFile[] = {"File",  
		"Open  | Ctrl-O", // 快捷键必须采用[Ctrl-X]格式，放在字符串的结尾
		"Close",
		"Exit   | Ctrl-E"};
	static char * menuListTool[] = {"Tool",
		"Triangle",
		"Circle",
		"Stop Rotation | Ctrl-T"};
	static char * menuListHelp[] = {"Help",
		"Show More  | Ctrl-M",
		"About"};
	static char * selectedLabel = NULL;
	static int iff = 1;
	 
	double fH = GetFontHeight(); //字体高度？ 
	double x = 0; //fH/8;
	double y = winheight;
	double h = fH*1.5; // 控件高度
	double w = TextStringWidth(menuListHelp[0])*2; // 控件宽度
	double wlist = TextStringWidth(menuListTool[3])*1.2;
	double xindent = winheight/20; // 缩进
	int    selection;
	
	// File 菜单
	if (iff == 1) {
		selection = menuList(GenUIID(0), x, y-h, w, wlist, h, menuListFile, sizeof(menuListFile)/sizeof(menuListFile[0]));
		if( selection>0 ) selectedLabel = menuListFile[selection];
		if( selection==3 ){
			DisplayClear(); 
			iff = 0;
		}
			
	}
	
	// Tool 菜单
	menuListTool[3] = enable_rotation ? "Stop Rotation | Ctrl-T" : "Start Rotation | Ctrl-T";
	selection = menuList(GenUIID(0),x+w,  y-h, w, wlist,h, menuListTool,sizeof(menuListTool)/sizeof(menuListTool[0]));
	if( selection>0 ) selectedLabel = menuListTool[selection];
	if( selection==3 )
		enable_rotation = ! enable_rotation;
	
	// Help 菜单
	menuListHelp[1] = show_more_buttons ? "Show Less | Ctrl-M" : "Show More | Ctrl-M";
	selection = menuList(GenUIID(0),x+2*w,y-h, w, wlist, h, menuListHelp,sizeof(menuListHelp)/sizeof(menuListHelp[0]));
	if( selection>0 ) selectedLabel = menuListHelp[selection];
	if( selection==1 )
		show_more_buttons = ! show_more_buttons;
 
	x = winwidth/15;
	y = winheight/8*7;
	
	//绘制迷宫 
	
	drawmaze(maze,x+w,y);
	
}

void display()
{
	// 清屏
	DisplayClear();

	// 绘制和处理菜单
	drawMenu();
}


void DrawCenteredCircle(double x, double y, double r)
{
    MovePen(x + r, y);
    DrawArc(r, 0.0, 360.0);
}


