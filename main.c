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
static int FLAG = 0;	//�Թ��Ƿ��н� 
static double winwidth, winheight;   // ���ڳߴ�

//ð��ģʽ�жϱ��������������ʾ����ð��ģʽ 
bool IsAdventuring = FALSE; 

//�ֶ��༭�жϱ��� ���������ʾ�����ֶ��༭ 
bool IsEditManually = FALSE;

//��ͼѡ���жϱ��� ���������ʾ����ѡ���ͼ 
bool IsChoosingMap = FALSE;

//�Թ���ʼ�������꣬�ɹ����� 
static double startx,starty;

//�༭�Թ������� �����ַ���
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
int viewSize = 3; //�����Ұ������Ұ��̬ȡ���ˣ���Ϊ���ھ���������Ҫ����Ұ by LWJ 
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

 
// ����������provided in libgraphics
void DisplayClear(void);

// �û�����ʾ����
void display(void);

// ����תӢ�纯�� 
double ScaleXInches(int x);
double ScaleYInches(int y);

// �ж�����Ƿ����Թ��ں��� 
bool inBox(double x0, double y0, double x1, double x2, double y1, double y2);

// �Թ����� 
void CreateMaze(int maze[msize][msize], int x, int y); 
void mazehelper(int maze[msize][msize], int x, int y); 

// �������·��
void clean(int maze[msize][msize]);

// �Զ����
void Solve(int x, int y, int maze[msize][msize]);

// �û��ļ����¼���Ӧ����
void KeyboardEventProcess(int key, int event)
{
	double x = 0; //fH/8;
	double y = winheight;
	x = winwidth/15 + 0.3;
	y = winheight/8*7 - 0.2;
	uiGetKeyboard(key,event); // GUI��ȡ����
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
	 // ˢ����ʾ
}

// �û�������¼���Ӧ����
void MouseEventProcess(int x, int y, int button, int event)
{
	//GUI��ȡ��� 
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
					//�����ǽ ��������� �ر����յ� 
				}
			
		}
	}
	display(); // ˢ����ʾ
}

void CharEventProcess(char ch)
{
	uiGetChar(ch); // GUI�ַ�����
	display(); //ˢ����ʾ
}

// �û����������
// ����ʼ��ִ��һ��
void Main() 
{
	// ���������Թ���������ͷָ�������ָ��
	head=NULL;
	p=NULL;
	int i,j;
	
	// ��ʼ�����ں�ͼ��ϵͳ
	SetWindowTitle("CMAZE!");
	SetWindowSize(17, 10);
    InitGraphics();
    //����������ɫ
	DefineColor("face", 0.96, 0.96, 0.011);
	DefineColor("facialContour", 0.83, 0.54, 0.15);
	DefineColor("mouth", 0.69, 0.42, 0.28);
	DefineColor("brick", 0.54, 0.54, 0.44);
	DefineColor("brickJoint", 0.44, 0.41, 0.56);
	// ��ô��ڳߴ�
    winwidth = GetWindowWidth();
    winheight = GetWindowHeight();
    
	// ע����Ӧ����
	registerKeyboardEvent(KeyboardEventProcess);// ����
	registerMouseEvent(MouseEventProcess);      // ���
	registerCharEvent(CharEventProcess);		// �ַ�
	
	SetPenColor("Red"); 
    SetPenSize(1);
    
    //�����Թ� bug���޸� 
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
    }//�������*/
}

// �����Թ� 
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

// ״̬ת�� 
void change(int i);

// �˵�
void drawMenu()
{ 
	static char * menuListPause[] = {"Pause",  
		"Restart  | Ctrl-R", // ��ݼ��������[Ctrl-X]��ʽ�������ַ����Ľ�β
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
	

	double fH = GetFontHeight(); //����߶�
	double x = 0; //fH/8;
	double y = winheight;
	double h = fH*1.5; // �ؼ��߶�
	double w = TextStringWidth(menuListSolve[0])*2; // �ؼ����
	double wlist = TextStringWidth(menuListEdit[3])*1.2;
	int    selection;
	

	// ��ʼ��ť 
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
			player[ccx][ccy] = 6;//ȷ�����¿�ʼ�ٳ�����ң��ڱ༭ģʽ�²�������� 
			
			change(0);

		}
	}
	
	//��logo
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
	
	// ������ʾ
	if (ifInstr) {
		WriteInstructions(winwidth,winheight,w,fH); 
		if (ifInstrButton) {
			if (button(GenUIID(0), winwidth/2+1.8*w, winheight/2-9*fH, w, h, "Close")) {
				ifInstr = 0;
				ifInstrButton = 0;
			}
		}
	}
	
	// �˳���ť 
	if (ifExitbutton) {
		if (button(GenUIID(0), winwidth/2-0.5*w, winheight/2 - h*1.2, w, h, "Exit")) {
			exit(-1);
		}
	}
	
	// Pause �˵�
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
		if( selection==2 ) {	// �˻����˵� 
			
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
		
	
	// Edit �˵�
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
	
	// Solve �˵�
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
		
	// Help �˵�
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
	
	//View �˵�
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
	
	//�����Թ� 
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
			}//�������*/
		}//����������������� 
	}

	
	//�ж��Ƿ񵽴��յ�
	if(ifwin&&!IsAdventuring){
		int i, j; 
		DisplayClear();
		MovePen(winwidth/2 - TextStringWidth("You win!"), winheight/2);
		DrawTextString("You win!");
		ifwin = 0;
		mazehelper(maze,2,2);
		ccx = 2;
		ccy = 2;
		//����player
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
		//����player
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
		drawLabel(8, winheight/13, "�Թ�����");
		if( textbox(GenUIID(0), 8+TextStringWidth("�Թ�����"), winheight/13, 3*w, h, MazeName, sizeof(MazeName)) );
	}//�����Թ������ı���
	
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
	
	//ð��ģʽ��ť 
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
			ifLogo = 0;//һϵ�еİ�ť��״̬������
			
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
	 	// 0 - ��Ϸ���� 
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
			player[ccx][ccy] = 6;//ȷ�����¿�ʼ�ٳ�����ң��ڱ༭ģʽ�²�������� 
			break;
		// 1 - �˻ؿ�ʼ�˵� 
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
	// ����
	DisplayClear();

	// ���ƺʹ���˵�
	drawMenu();
}

bool inBox(double x, double y, double x1, double x2, double y1, double y2)
{
	return (x >= x1 && x <= x2 && y >= y1 && y <= y2);
}

// �Թ����� 
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
	//��ʼ�� 
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
 
	//�����Թ�����2��2��Ϊ���
	CreateMaze(maze, 2, 2);
	
	//��β����
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

// �������·��
void clean(int maze[msize][msize]) {
	int i, j;
	for (i = 0; i < msize; ++i) {
		for (j = 0; j < msize; ++j) {
			if (maze[i][j] == -3 || maze[i][j] == -2) maze[i][j] = 0;
		}
	}
} 

// �Զ����
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


























