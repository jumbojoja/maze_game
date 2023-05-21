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

static double winwidth, winheight;   // ���ڳߴ�
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
			}
		}
		if( selection==4 ){
			StoreMaze();
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
