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

#define msize 20
#define length 0.5

#include "paperwork.h"

#define msize 20
#define length 0.35
static int Rank = 1;
static int FLAG = 0;	//迷宫是否有解 
static double winwidth, winheight;   // 窗口尺寸

//冒险模式判断变量，如果开启表示正在冒险模式 
bool IsAdventuring = FALSE; 

//手动编辑判断变量 如果开启表示正在手动编辑 
bool IsEditManually = FALSE;

//地图选择判断变量 如果开启表示正在选择地图 
bool IsChoosingMap = FALSE;

//迷宫开始画的坐标，可供调用 
static double startx,starty;

//编辑迷宫的名字 所用字符串
char MazeName[30];

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

struct EdittedMaze *head,*p,*adventure_head;

static int haveKey = 0;
static int ifwin = 0;
int viewSize = 3; //这里我把这个视野静态取消了，因为我在剧情里面需要调视野 by LWJ 
static int ClearSolve = 1;
static int ifStartbutton = 1;
static int ifExitbutton = 1;
static int ifListPause = 0;
static int ifListEdit = 0;
static int ifListSolve = 0;
static int ifListHelp = 1; 
static int ifListView = 0;
static int ifdrawmaze = 0;
static int ifLogo = 1;
static int ifInstr = 0; 
static int ifInstrButton = 1;

 
// 清屏函数，provided in libgraphics
void DisplayClear(void);

// 用户的显示函数
void display(void);

// 像素转英寸函数 
double ScaleXInches(int x);
double ScaleYInches(int y);

// 判断鼠标是否在迷宫内函数 
bool inBox(double x0, double y0, double x1, double x2, double y1, double y2);

// 迷宫生成 
void CreateMaze(int maze[msize][msize], int x, int y); 
void mazehelper(int maze[msize][msize], int x, int y); 

// 擦除求解路径
void clean(int maze[msize][msize]);

// 自动求解
void Solve(int x, int y, int maze[msize][msize]);

// 用户的键盘事件响应函数
void KeyboardEventProcess(int key, int event)
{
	double x = 0; //fH/8;
	double y = winheight;
	x = winwidth/15 + 0.3;
	y = winheight/8*7 - 0.2;
	uiGetKeyboard(key,event); // GUI获取键盘
	if (ClearSolve == 0) clean(maze);
	display();
	switch(event)
	{
		case KEY_DOWN:
			switch(key)
			{
				case VK_UP:
					if(ccx == 0)
						break;     
                	if(maze[ccx-1][ccy] == 0 || maze[ccx-1][ccy] == -2 || maze[ccx-1][ccy] == -3 || maze[ccx-1][ccy] == 3)
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
			         if(maze[ccx+1][ccy] == 0 || maze[ccx+1][ccy] == -2 || maze[ccx+1][ccy] == -3 || maze[ccx+1][ccy] == 3)  
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
			         if(maze[ccx][ccy-1] == 0 || maze[ccx][ccy-1] == -2 || maze[ccx][ccy-1] == -3 || maze[ccx][ccy-1] == 3)  
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
			         if(maze[ccx][ccy+1] == 0 || maze[ccx][ccy+1] == -2 || maze[ccx][ccy+1] == -3 || maze[ccx][ccy+1] == 3)  
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
	uiGetMouse(x,y,button,event);
	if(IsEditManually == TRUE&&(inBox(ScaleXInches(x), ScaleYInches(y), (double)((int)startx), (double)((int)startx+msize*length), (double)((int)starty)-msize*length, (double)((int)starty)))){
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
	display(); // 刷新显示
}

void CharEventProcess(char ch)
{
	uiGetChar(ch); // GUI字符输入
	display(); //刷新显示
}

// 用户主程序入口
// 仅初始化执行一次
void Main() 
{
	// 新增加载迷宫程序，这是头指针与操作指针
	head=NULL;
	p=NULL;
	int i,j;
	
	// 初始化窗口和图形系统
	SetWindowTitle("CMAZE!");
	SetWindowSize(17, 10);
    InitGraphics();
    //设置所需颜色
	DefineColor("face", 0.96, 0.96, 0.011);
	DefineColor("facialContour", 0.83, 0.54, 0.15);
	DefineColor("mouth", 0.69, 0.42, 0.28);
	DefineColor("brick", 0.54, 0.54, 0.44);
	DefineColor("brickJoint", 0.44, 0.41, 0.56);
	// 获得窗口尺寸
    winwidth = GetWindowWidth();
    winheight = GetWindowHeight();
    
	// 注册响应函数
	registerKeyboardEvent(KeyboardEventProcess);// 键盘
	registerMouseEvent(MouseEventProcess);      // 鼠标
	registerCharEvent(CharEventProcess);		// 字符
	
	SetPenColor("Red"); 
    SetPenSize(1);
    
    //加载迷宫 bug已修复 
    head=LoadMazeList("Maze_List.txt");
    p=head;
    adventure_head=LoadMazeList("Adventure_List.txt");
    /*InitConsole();
    for(p=adventure_head;p->number!=adventure_head->front->number;p=p->next){
    	printf("%d",p->number);
    	printf("\n");
    	puts(p->name);
    	printf("\n");
    	for(i=0;i<msize;i++){
    		for(j=0;j<msize;j++){
    			printf("%d ",p->Maze[i][j]);
    		}
    	}
    	printf("\n");
    }//输出测试*/
}

// 绘制迷宫 
void drawmaze(int maze[msize][msize], int x, int y) 
{
	int i, j;
	SetPenColor("Red");
	for (i = 0; i < msize; i++) {
		for (j = 0; j < msize; j++) {
			if ((maze[i][j] == 0 || maze[i][j] == -3) && abs(i-ccx) <= viewSize && abs(j-ccy)<=viewSize) {
				SetPenColor("brickJoint");
				MovePen(x + length*j,y - length*i);
				DrawLine(length,0);
				DrawLine(0,-1.0*length);
				DrawLine(-1.0*length,0);
				DrawLine(0,length);
				SetPenColor("Red");
			}
				if (maze[i][j] == 1 && abs(i-ccx) <= viewSize && abs(j-ccy)<=viewSize) {
				drawwall(x, y, i, j);
				/*MovePen(x + length*j,y - length*i);
				StartFilledRegion(1); 
					DrawLine(length,0);
					DrawLine(0,-1.0*length);
					DrawLine(-1.0*length,0);
					DrawLine(0,length);
					EndFilledRegion(); */	
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
				}else if (maze[i][j] == -2 && ClearSolve || maze[i][j] == -2 && abs(i-ccx) <= viewSize && abs(j-ccy)<=viewSize) {
					MovePen(x + length*j,y - length*i);
					StartFilledRegion(1); 
					SetPenColor("Green");
					DrawLine(length,0);
					DrawLine(0,-1.0*length);
					DrawLine(-1.0*length,0);
					DrawLine(0,length);
					EndFilledRegion();
					SetPenColor("Red");
				}
				if(player[i][j] == 6){
					drawplayer(x, y, i, j);
				}
		}
	}
}

// 状态转换 
void change(int i);

// 菜单
void drawMenu()
{ 
	static char * menuListPause[] = {"Pause",  
		"Restart  | Ctrl-R", // 快捷键必须采用[Ctrl-X]格式，放在字符串的结尾
		"Exit   | Ctrl-E"};
	static char * menuListEdit[] = {"Edit",
		"Clean",
		"Regenerate",
		"Edit Manually | Ctrl-M",
		"Choose Maps"};
	static char * menuListSolve[] = {"Solve",
		"Auto Solve  | Ctrl-A",
		"Tips"};
	static char * menuListHelp[] = {"    Help",
		"Instructions",
		"About"};
	static char * menuListView[] = {"Set view",
		"easy",
		"difficult",
		"blind",
		"God"};
	static char * selectedLabel = NULL;
	

	static int ifStartbutton = 1;
	static int ifExitbutton = 1;
	static int ifAdventureButton = 1;
	static int ifListPause = 0;
	static int ifListEdit = 0;
	static int ifListSolve = 0;
	static int ifListHelp = 1; 
	static int ifListSize = 0; 
	static int ifListView = 0;
	static int ifdrawmaze = 0;
	static int ifLogo = 1;
	static int ifInstr = 0; 
	static int ifInstrButton = 1;
	static int IsDisplayAbout = 0;
	

	double fH = GetFontHeight(); //字体高度
	double x = 0; //fH/8;
	double y = winheight;
	double h = fH*1.5; // 控件高度
	double w = TextStringWidth(menuListSolve[0])*2; // 控件宽度
	double wlist = TextStringWidth(menuListEdit[3])*1.2;
	int    selection;
	

	// 开始按钮 
	if (ifStartbutton) {
		if (button(GenUIID(0), winwidth/2-0.5*w, winheight/2, w, h, "Start")) {
			ifStartbutton = 0;
			ifExitbutton = 0;
			ifAdventureButton = 0;
			ifListPause = 1;
			ifListEdit = 1;
			ifListSolve = 1;
			ifListView = 1;
			ifListHelp = 0;
			ifdrawmaze = 1;
			IsEditManually = FALSE;
			IsChoosingMap = FALSE; 
			ifLogo = 0;
			ifInstr = 0;
			ifInstrButton = 0;
			player[ccx][ccy] = 6;//确保按下开始再出现玩家，在编辑模式下不出现玩家 
			
			change(0);

		}
	}
	
	//画logo
	if (ifLogo) {
		SetPenColor("Red");
		MovePen(winwidth/2-w*3, winheight/2+h*7);
		DrawTextString(" .ooooo.      ooo.    .oo.    .oo.          .oooo.          oooooooo    .ooooo.    ");
		MovePen(winwidth/2-w*3, winheight/2+h*7-fH);
		DrawTextString("d88'  `'Y8    `888P'Y88bP'Y88b    `P    )88b      d'''7d8P      d88'  `88b  ");
		MovePen(winwidth/2-w*3, winheight/2+h*7-2*fH);
		DrawTextString("888               888      888      888      .oP'888          .d8P'      888ooo888  ");
		MovePen(winwidth/2-w*3, winheight/2+h*7-3*fH);
		DrawTextString("888      .o8    888      888      888    d8(   888      .d8P'    .P   888        .o ");
		MovePen(winwidth/2-w*3, winheight/2+h*7-4*fH);
		DrawTextString("`Y8bod8P'  o888o  o888o  o888o  `Y888""8o  d8888888P    `Y8bod8P'  ");
	} 
	
	// 操作提示
	if (ifInstr) {
		WriteInstructions(winwidth,winheight,w,fH); 
		if (ifInstrButton) {
			if (button(GenUIID(0), winwidth/2+1.8*w, winheight/2-9*fH, w, h, "Close")) {
				ifInstr = 0;
				ifInstrButton = 0;
			}
		}
	}
	
	// 退出按钮 
	if (ifExitbutton) {
		if (button(GenUIID(0), winwidth/2-0.5*w, winheight/2 - h*1.2, w, h, "Exit")) {
			exit(-1);
		}
	}
	
	// Pause 菜单
	if (ifListPause) {
		selection = menuList(GenUIID(0), x, y-h, w, wlist, h, menuListPause, sizeof(menuListPause)/sizeof(menuListPause[0]));
		if( selection>0 ) selectedLabel = menuListPause[selection];
		if( selection==1) {
			int i, j;
			clean(maze);
			for (i = 0; i < msize; ++i) {
		 		for (j = 0; j < msize; ++j) {
		 			player[i][j] = 0;
			 	}
		 	}
		 	ccx = 2;
		 	ccy = 2;
		 	player[ccx][ccy] = 6;
		}
		if( selection==2 ) {	// 退回主菜单 
			
			ifStartbutton = 1;
			ifExitbutton = 1;
			ifAdventureButton = 1;
			ifListPause = 0;
			ifListEdit = 0;
			ifListSolve = 0;
			ifListHelp = 1;
			ifdrawmaze = 0;
			ifListView = 0;
			ifLogo = 1;
			IsEditManually = FALSE;
			IsChoosingMap = FALSE;
			IsAdventuring = FALSE;
			change(1);
		}
	}
		
	
	// Edit 菜单
	if (ifListEdit) {
		selection = menuList(GenUIID(0),x+w,  y-h, w, wlist,h, menuListEdit,sizeof(menuListEdit)/sizeof(menuListEdit[0]));
		if( selection>0 ) selectedLabel = menuListEdit[selection];
		if( selection==3 ){
			IsEditManually = TRUE;
			IsAdventuring = FALSE;
			IsChoosingMap = FALSE;
			player[ccx][ccy] = 0;
			if(IsEditManually){
				viewSize = 100;
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
				maze[2][1]=2;
				maze[msize-3][msize-2]=3;
			}
		}
		if( selection==2){
			mazehelper(maze,2,2);
			IsEditManually = FALSE;
			IsChoosingMap = FALSE;
		}
		if ( selection==1){
			clean(maze);
			IsEditManually = FALSE;
			IsChoosingMap = FALSE;
			ClearSolve = 1;
		}
		if( selection == 4){
			int i,j;
			IsChoosingMap = TRUE;
			IsEditManually = FALSE;
			IsAdventuring = FALSE;
			p = head;
			for(i=0;i<msize;i++){
				for(j=0;j<msize;j++){
					maze[i][j]=p->Maze[i][j];
				}
			}
		}
	}
	
	// Solve 菜单
	if (ifListSolve) {
		selection = menuList(GenUIID(0),x+2*w,y-h, w, wlist, h, menuListSolve,sizeof(menuListSolve)/sizeof(menuListSolve[0]));
		if( selection>0 ) selectedLabel = menuListSolve[selection];
		if ( selection == 1) {
			Solve(ccx,ccy,maze);
			FLAG = 0;
			ClearSolve = 1;
		}
		if ( selection == 2) {
			Solve(ccx,ccy,maze);
			FLAG = 0;
			ClearSolve = 0;
		}
	}
		
	// Help 菜单
	if (ifListHelp) {
		selection = menuList(GenUIID(0),winwidth/2-0.5*w,winheight/2 - h*1.2*2, w, wlist, h, menuListHelp,sizeof(menuListHelp)/sizeof(menuListHelp[0]));
		if( selection>0 ) selectedLabel = menuListHelp[selection];
		if( selection == 1) {
			ifInstr = 1;
			ifInstrButton = 1;
		}
		if( selection == 2) {
			DisplayClear();
			IsDisplayAbout = 1;
			ifStartbutton = 0;
			ifExitbutton = 0;
			ifAdventureButton = 0;
			ifListPause = 0;
			ifListEdit = 0;
			ifListSolve = 0;
			ifListView = 0;
			ifListHelp = 0;
			ifdrawmaze = 0;
			IsEditManually = FALSE;
			IsChoosingMap = FALSE; 
			ifLogo = 0;
			ifInstr = 0;
			ifInstrButton = 0;
		}
	}
	
	//View 菜单
	if (ifListView) {
		selection = menuList(GenUIID(0),x+3*w,y-h, w*1.2, wlist/2, h, menuListView,sizeof(menuListView)/sizeof(menuListView[0]));
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
		if (button(GenUIID(0), 6, winheight/13, w, h, "Save")){
			IsEditManually = FALSE;
			StoreMaze();
			InsertMaze(head);
			int i,j; 
			for(i=0;i<30;i++){
				MazeName[i] = '\0';
			}
			/*InitConsole();
    		for(p=head;p->number!=head->front->number;p=p->next){
    			printf("%d",p->number);
    			printf("\n");
    			puts(p->name);
    			printf("\n");
    			for(i=0;i<msize;i++){
    				for(j=0;j<msize;j++){
    					printf("%d ",p->Maze[i][j]);
    				}
    			}
    			printf("\n");
			}//输出测试*/
		}//保存后清零名称数组 
	}

	
	//判断是否到达终点
	if(ifwin&&!IsAdventuring){
		int i, j; 
		DisplayClear();
		MovePen(winwidth/2 - TextStringWidth("You win!"), winheight/2);
		DrawTextString("You win!");
		ifwin = 0;
		mazehelper(maze,2,2);
		ccx = 2;
		ccy = 2;
		//更新player
		 for (i = 0; i < msize; ++i) {
		 	for (j = 0; j < msize; ++j) {
		 		player[i][j] = 0;
			 }
		 }
		 player[ccx][ccy] = 6;

	}else if(ifwin&&IsAdventuring){
		int i, j; 
		DisplayClear();
		if(p==adventure_head->front){
			MovePen(winwidth/2 - TextStringWidth("You win!"), winheight/2);
			DrawTextString("You win!");
		}else{
			MovePen(winwidth/2 - TextStringWidth("next one"), winheight/2);
			DrawTextString("next one");
		}
		ifwin = 0;
		p=p->next;
		for (i = 0; i < msize; ++i) {
		 	for (j = 0; j < msize; ++j) {
		 		maze[i][j]=p->Maze[i][j];
			 }
		 }
		ccx = 2;
		ccy = 2;
		//更新player
		 for (i = 0; i < msize; ++i) {
		 	for (j = 0; j < msize; ++j) {
		 		player[i][j] = 0;
			 }
		 }
		 player[ccx][ccy] = 6;
	}
	 
	
	if(IsEditManually){
		WriteEditManually(winwidth,winheight,fH);
		SetPenColor("Brown"); 
		drawLabel(8, winheight/13, "迷宫名称");
		if( textbox(GenUIID(0), 8+TextStringWidth("迷宫名称"), winheight/13, 3*w, h, MazeName, sizeof(MazeName)) );
	}//新增迷宫名称文本框
	
	if(IsChoosingMap){
		viewSize = 100; 
		drawLabel(1,winheight/2,p->name);
		if (button(GenUIID(0), 6, winheight/13, w, h, "NEXT")){
			p=p->next;
			int i,j;
			for(i=0;i<msize;i++){
				for(j=0;j<msize;j++){
					maze[i][j]=p->Maze[i][j];
				}
			}
		}
		if (button(GenUIID(0), 8, winheight/13, w, h, "FRONT")){
			p=p->front;
			int i,j;
			for(i=0;i<msize;i++){
				for(j=0;j<msize;j++){
					maze[i][j]=p->Maze[i][j];
				}
			}
		}
		if (button(GenUIID(0), 10, winheight/13, w, h, "DELETE")){
			DeleteMaze(head);
		}
		if (button(GenUIID(0), 1, winheight/2 - 1.2*h , w, h, "Play")){
			IsChoosingMap = FALSE;
			player[ccx][ccy] = 6;
		}
	}
	
	//冒险模式按钮 
	if(ifAdventureButton){
		if (button(GenUIID(0), winwidth/2-w, winheight/2 + h*1.2, 2*w, h, "ADVENTURE")){
			IsAdventuring = TRUE;
			ifStartbutton = 0;
			ifExitbutton = 0;
			ifAdventureButton = 0;
			ifListPause = 1;
			ifListEdit = 0;
			ifListHelp = 0;
			ifListView = 0;
			ifListSize = 0;
			ifdrawmaze = 1;
			IsEditManually = FALSE;
			IsChoosingMap = FALSE; 
			ifLogo = 0;//一系列的按钮和状态量操作
			
			StartAdventure(); 
		}
	}
	
	if(IsDisplayAbout){
		WriteAbout(winwidth,winheight,fH);
		if (button(GenUIID(0), winwidth/2-0.5*w, winheight/13, w, h, "Close")){
			IsDisplayAbout = 0;
			ifStartbutton = 1;
			ifExitbutton = 1;
			ifAdventureButton = 1;
			ifListPause = 0;
			ifListEdit = 0;
			ifListSolve = 0;
			ifListView = 0;
			ifListHelp = 1;
			ifdrawmaze = 0;
			IsEditManually = FALSE;
			IsChoosingMap = FALSE; 
			ifLogo = 1;
			ifInstr = 0;
			ifInstrButton = 0;
			;
		}
	}
}

void change(int i) {
	 switch(i) {
	 	// 0 - 游戏界面 
	 	case 0:
	 		ifStartbutton = 0;
			ifExitbutton = 0;
			ifListPause = 1;
			ifListEdit = 1;
			ifListSolve = 1;
			ifListView = 1;
			ifListHelp = 0;
			ifdrawmaze = 1;
			IsEditManually = FALSE;
			IsChoosingMap = FALSE; 
			ifLogo = 0;
			ifInstr = 0;
			ifInstrButton = 0;
			player[ccx][ccy] = 6;//确保按下开始再出现玩家，在编辑模式下不出现玩家 
			break;
		// 1 - 退回开始菜单 
		case 1:
			ifStartbutton = 1;
			ifExitbutton = 1;
			ifListPause = 0;
			ifListEdit = 0;
			ifListSolve = 0;
			ifListHelp = 1;
			ifdrawmaze = 0;
			ifListView = 0;
			ifLogo = 1;
			IsEditManually = FALSE;
			IsChoosingMap = FALSE;
			break;
		
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

// 迷宫生成 
void CreateMaze(int maze[msize][msize], int x, int y) {
	maze[x][y] = 0;
 	int i, j, k;
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
 
	for (i = 0; i < 4; i++) {
		int dx = x;
		int dy = y;
 
		int range = 1 + (Rank == 0 ? 0 : rand() % Rank);
		while (range>0) {
			dx += direction[i][0];
			dy += direction[i][1];
 
			if (maze[dx][dy] == 0) {
				break;
			}
 
			int count = 0;
			for (j = dx - 1; j < dx + 2; j++) {
				for (k = dy - 1; k < dy + 2; k++) {
					if (abs(j - dx) + abs(k - dy) == 1 && maze[j][k] == 0) {
						count++;
					}
				}
			}
 
			if (count > 1) {
				break;
			}
 
			--range;
			maze[dx][dy] = 0;
		}
 
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
 
	for (i = 0; i < msize; i++){
		maze[i][0] = 0;
		maze[0][i] = 0;
		maze[i][msize - 1] = 0;
		maze[msize - 1][i] = 0;
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
 
	maze[2][1] = 2;
 
	for (i = msize - 3; i >= 0; i--) {
		if (maze[i][msize - 3] == 0) {
			maze[i][msize - 2] = 3;
			break;
		}
	}
}

// 擦除求解路径
void clean(int maze[msize][msize]) {
	int i, j;
	for (i = 0; i < msize; ++i) {
		for (j = 0; j < msize; ++j) {
			if (maze[i][j] == -3 || maze[i][j] == -2) maze[i][j] = 0;
		}
	}
} 

// 自动求解
void Solve(int x, int y, int maze[msize][msize]) {
	int direction[4][2] = { {0,1},  {1,0}, {0,-1}, {-1,0} };
	int i, j, flag = 0;
	for (i = 0; i < 4; ++i) {
		if (maze[x+direction[i][0]][y+direction[i][1]] == 0 || maze[x+direction[i][0]][y+direction[i][1]] == 3) flag = 1;
	}
	if (!flag) {
		maze[x][y] = -3;
		return;
	} else {
		maze[x][y] = -2;
		for (i = 0; i < 4; ++i) {
			if (FLAG) return;
			if (maze[x+direction[i][0]][y+direction[i][1]] == 0) {
				Solve(x+direction[i][0],y+direction[i][1],maze);
			} else if (maze[x+direction[i][0]][y+direction[i][1]] == 3) {
				FLAG = 1;
				return;
			}
		}
		for (flag = 0,i = 0; i < 4; ++i) {
			if (maze[x+direction[i][0]][y+direction[i][1]] == 0 || maze[x+direction[i][0]][y+direction[i][1]] == 3) flag = 1;
		}
		if (!flag && !FLAG) {
			maze[x][y] = -3;
			return;
		}
	}
	return;
} 


























