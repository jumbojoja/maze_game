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
//ǽ��·���ı�ʶ
#define WALL  1
#define ROUTE 0
//�����Թ��ĸ��Ӷȣ���ֵԽ���Ӷ�Խ�ͣ���СֵΪ0
static int Rank = 1;

static double winwidth, winheight;   // ���ڳߴ�
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

// ����������provided in libgraphics
void DisplayClear(void); 

// �û�����ʾ����
void display(void);

// �����Թ����� 
//void DrawEmptyMaze(void);

//���ڱ���Maze�ĺ��� ��ʹ��ʱֱ�ӵ��ü��� 
void StoreMaze(void);

//����תӢ�纯�� 
double ScaleXInches(int x);
double ScaleYInches(int y);

//�ж�����Ƿ����Թ��ں��� 
bool inBox(double x0, double y0, double x1, double x2, double y1, double y2);

// �û��ļ����¼���Ӧ����
void KeyboardEventProcess(int key, int event)
{
	uiGetKeyboard(key,event); // GUI��ȡ����
	display(); // ˢ����ʾ
}

// �û�������¼���Ӧ����
void MouseEventProcess(int x, int y, int button, int event)
{
	//GUI��ȡ��� 	
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
					//�����ǽ ��������� �ر����յ� 
				}
			
		}
	}
	uiGetMouse(x,y,button,event);
	display(); // ˢ����ʾ
}

// �û����������
// ����ʼ��ִ��һ��
void Main() 
{
	// ��ʼ�����ں�ͼ��ϵͳ
	SetWindowTitle("Graphics User Interface Demo");
	//SetWindowSize(10, 10); // ��λ - Ӣ��
	//SetWindowSize(20, 10);
	//SetWindowSize(10, 20);  // �����Ļ�ߴ粻�����򰴱�����С
    InitGraphics();

	// ��ô��ڳߴ�
    winwidth = GetWindowWidth();
    winheight = GetWindowHeight();
    
	// ע��ʱ����Ӧ����
	registerKeyboardEvent(KeyboardEventProcess);// ����
	registerMouseEvent(MouseEventProcess);      // ���
    
	
	// �򿪿���̨���������������Ϣ�����ڵ���
	// InitConsole() 

}

//�����Թ� 
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
			
		}
	}
}

// �˵�
void drawMenu()
{ 
	static char * menuListPause[] = {"Pause",  
		"Restart  | Ctrl-R", // ��ݼ��������[Ctrl-X]��ʽ�������ַ����Ľ�β
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

	double fH = GetFontHeight(); //����߶�
	double x = 0; //fH/8;
	double y = winheight;
	double h = fH*1.5; // �ؼ��߶�
	double w = TextStringWidth(menuListHelp[0])*2; // �ؼ����
	double wlist = TextStringWidth(menuListEdit[3])*1.2;
	int    selection;
	
	// ��ʼ��ť 
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
	
	// �˳���ť 
	if (ifExitbutton) {
		if (button(GenUIID(0), winwidth/2, winheight/2 - h*1.2, w, h, "Exit")) {
			exit(-1);
		}
	}
	
	// Pause �˵�
	if (ifListPause) {
		selection = menuList(GenUIID(0), x, y-h, w, wlist, h, menuListPause, sizeof(menuListPause)/sizeof(menuListPause[0]));
		if( selection>0 ) selectedLabel = menuListPause[selection];
		if( selection==2 ) {	// �˻����˵� 
			ifStartbutton = 1;
			ifExitbutton = 1;
			ifListPause = 0;
			ifListEdit = 0;
			ifListHelp = 0;
			ifListSize = 1;
			ifdrawmaze = 0;
		}
	}
		
	
	// Edit �˵�
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
	
	// Help �˵�
	if (ifListHelp) {
		selection = menuList(GenUIID(0),x+2*w,y-h, w, wlist, h, menuListHelp,sizeof(menuListHelp)/sizeof(menuListHelp[0]));
		if( selection>0 ) selectedLabel = menuListHelp[selection];
	}
		
	// Size �˵�
	if (ifListSize) {
		selection = menuList(GenUIID(0),winwidth/2,winheight/2 - h*1.2*2, w, wlist, h, menuListSize,sizeof(menuListSize)/sizeof(menuListSize[0]));
		if( selection>0 ) selectedLabel = menuListSize[selection];
	}
	
	//�����Թ� 
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
	}//�������水ť 
}

void display()
{
	// ����
	DisplayClear();

	// ���ƺʹ���˵�
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
	MovePen(0,0);//����֮�󽫻����ƶ���ԭ�� 
}*/

bool inBox(double x, double y, double x1, double x2, double y1, double y2)
{
	return (x >= x1 && x <= x2 && y >= y1 && y <= y2);
}

//�Թ����� 
void CreateMaze(int maze[msize][msize], int x, int y) {
	maze[x][y] = ROUTE;
 	int i, j, k;
	//ȷ���ĸ��������
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
 
	//���ĸ�������
	for (i = 0; i < 4; i++) {
		int dx = x;
		int dy = y;
 
		//�����ڵľ��룬��Rank��������С
		int range = 1 + (Rank == 0 ? 0 : rand() % Rank);
		while (range>0) {
			dx += direction[i][0];
			dy += direction[i][1];
 
			//�ų�����ͷ·
			if (maze[dx][dy] == ROUTE) {
				break;
			}
 
			//�ж��Ƿ��ڴ�·��
			int count = 0;
			for (j = dx - 1; j < dx + 2; j++) {
				for (k = dy - 1; k < dy + 2; k++) {
					//abs(j - dx) + abs(k - dy) == 1 ȷ��ֻ�жϾŹ�����ĸ��ض�λ��
					if (abs(j - dx) + abs(k - dy) == 1 && maze[j][k] == ROUTE) {
						count++;
					}
				}
			}
 
			if (count > 1) {
				break;
			}
 
			//ȷ�������ڴ�ʱ��ǰ��
			--range;
			maze[dx][dy] = ROUTE;
		}
 
		//û���ڴ�Σ�գ��Դ�Ϊ�ڵ�ݹ�
		if (range <= 0) {
			CreateMaze(maze, dx, dy);
		}
	}
}

void mazehelper(int maze[msize][msize], int x, int y) {
	//��ʼ�� 
	int i, j;
	for (i = 0; i < msize; ++i) {
		for (j = 0; j < msize; ++j) {
			maze[i][j] = 1;
		}
	} 
    srand((unsigned)time(NULL));
 
	//����Χ����Ϊ·����ԭ��Ϊ�˷�ֹ��·ʱ�ڳ��߽磬ͬʱΪ�˱����Թ��������һȦǽ�屻�ڴ�
	for (i = 0; i < msize; i++){
		maze[i][0] = ROUTE;
		maze[0][i] = ROUTE;
		maze[i][msize - 1] = ROUTE;
		maze[msize - 1][i] = ROUTE;
	}
 
	//�����Թ�����2��2��Ϊ���
	CreateMaze(maze, 2, 2);
	
	//��β����
	for (i = 0; i < msize; i++){
		maze[i][0] = -1;
		maze[0][i] = -1;
		maze[i][msize - 1] = -1;
		maze[msize - 1][i] = -1;
	}
 
	//���Թ�����ںͳ���
	maze[2][1] = 2;
 
	//�����㷨����ԣ�������һ�����ʲ��ڣ�L-3,L-2��������ʱ��ҪѰ�ҳ���
	for (i = msize - 3; i >= 0; i--) {
		if (maze[i][msize - 3] == ROUTE) {
			maze[i][msize - 2] = 3;
			break;
		}
	}
}
