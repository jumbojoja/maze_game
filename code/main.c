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

#define msize 20
#define length 0.45 

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
						  -1, 1, 0, 4, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 1,-1,
						  -1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 3,-1,
						  -1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,-1,
						  -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1}; 

int player[msize][msize] = {0};

static int ccx = 2, ccy = 2;

struct EdittedMaze *head,*p,*adventure_head;

static int haveKey = 0;
static int ifwin = 0;
int viewSize = 3; 
static int ClearSolve = 1;

 
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
void KeyboardEventProcess(int key, int event) {
	double x = 0; //fH/8;
	double y = winheight;
	x = winwidth/15 + 0.3;
	y = winheight/8*7 - 0.2;
	uiGetKeyboard(key,event); // GUI��ȡ����
	if (ClearSolve == 0) clean(maze);
	display();
	switch(event) {
		case KEY_DOWN:
			switch(key) {
				case VK_UP:
					if(ccx == 0)
						break;     
                	if(maze[ccx-1][ccy] == 0 || maze[ccx-1][ccy] == -2 || maze[ccx-1][ccy] == -3) {
						player[ccx][ccy] = 0;
						ccx -=1;
						player[ccx][ccy] = 6;
					}
					else if(maze[ccx-1][ccy] == 4) {
						haveKey = 1;
						player[ccx][ccy] = 0;
                		ccx -= 1;
						player[ccx][ccy] = 6;
						maze[ccx][ccy] = 0;
					}
					else if(maze[ccx-1][ccy] == 3) {
						if(haveKey) {
							player[ccx][ccy] = 0;
                			ccx -= 1;
							player[ccx][ccy] = 6;	
						}
						else {
							MovePen(6, 6);
							DrawTextString("You don't have a key to unlock the lock, go find the key.");
						}						
					}
                     break;
			     case VK_DOWN:
			     	if(ccx == msize-1)
			     		break;
			         if(maze[ccx+1][ccy] == 0 || maze[ccx+1][ccy] == -2 || maze[ccx+1][ccy] == -3) {
                		player[ccx][ccy] = 0;
                		ccx += 1;
						player[ccx][ccy] = 6;
					}
					else if(maze[ccx+1][ccy] == 4) {
						haveKey = 1;
						player[ccx][ccy] = 0;
                		ccx += 1;
						player[ccx][ccy] = 6;
						maze[ccx][ccy] = 0;	
					}
					else if(maze[ccx+1][ccy] == 3) {
						if(haveKey) {
							player[ccx][ccy] = 0;
                			ccx += 1;
							player[ccx][ccy] = 6;	
						}
						else {
							MovePen(6, 6);
							DrawTextString("You don't have a key to unlock the lock, go find the key.");
						}
					}
                     break;
			     case VK_LEFT:
			     	if(ccy == 0)
			     		break;
			         if(maze[ccx][ccy-1] == 0 || maze[ccx][ccy-1] == -2 || maze[ccx][ccy-1] == -3) {
                		player[ccx][ccy] = 0;
                		ccy -= 1;
						player[ccx][ccy] = 6;
					}
					else if(maze[ccx][ccy-1] == 4) {
						haveKey = 1;
						player[ccx][ccy] = 0;
                		ccy -= 1;
						player[ccx][ccy] = 6;
						maze[ccx][ccy] = 0;	
					}
					else if(maze[ccx][ccy-1] == 3) {
						if(haveKey) {
							player[ccx][ccy] = 0;
                			ccy -= 1;
							player[ccx][ccy] = 6;	
						}
						else {
							MovePen(6, 6);
							DrawTextString("You don't have a key to unlock the lock, go find the key.");
						}
					}
                     break;
			     case VK_RIGHT:
			     	if(ccy == msize-1)
			     		break;
			         if(maze[ccx][ccy+1] == 0 || maze[ccx][ccy+1] == -2 || maze[ccx][ccy+1] == -3) {
                		player[ccx][ccy] = 0;
                		ccy += 1;
						player[ccx][ccy] = 6;
					}
					else if(maze[ccx][ccy+1] == 4) {
						haveKey = 1;
						player[ccx][ccy] = 0;
                		ccy += 1;
						player[ccx][ccy] = 6;
						maze[ccx][ccy] = 0;	
					}
					else if(maze[ccx][ccy+1] == 3) {
						if(haveKey) {
							player[ccx][ccy] = 0;
                			ccy += 1;
							player[ccx][ccy] = 6;	
						}
						else {
							MovePen(6, 6);
							DrawTextString("You don't have a key to unlock the lock, go find the key.");
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
void MouseEventProcess(int x, int y, int button, int event) {
	//GUI��ȡ��� 
	uiGetMouse(x,y,button,event);
	if(IsEditManually == TRUE&&(inBox(ScaleXInches(x), ScaleYInches(y), (double)((int)startx), (double)((int)startx+msize*length), (double)((int)starty)-msize*length, (double)((int)starty)))){
		switch(event) {
			case BUTTON_DOWN:
				switch(button){
					case LEFT_BUTTON: {
						if(maze[(int)(((int)starty-ScaleYInches(y))/length)]
							[(int)((ScaleXInches(x)-(int)(startx))/length)] == 0) {
						maze[(int)(((int)starty-ScaleYInches(y))/length)]
							[(int)((ScaleXInches(x)-(int)(startx))/length)] = 1;
						}else if(maze[(int)(((int)starty-ScaleYInches(y))/length)]
							[(int)((ScaleXInches(x)-(int)(startx))/length)] == 1) {
						maze[(int)(((int)starty-ScaleYInches(y))/length)]
							[(int)((ScaleXInches(x)-(int)(startx))/length)] = 0;	
						}
						break;
					}
					case RIGHT_BUTTON: {
						if(maze[(int)(((int)starty-ScaleYInches(y))/length)]
							[(int)((ScaleXInches(x)-(int)(startx))/length)] == 0) {
						maze[(int)(((int)starty-ScaleYInches(y))/length)]
							[(int)((ScaleXInches(x)-(int)(startx))/length)] = 4;
						}else if(maze[(int)(((int)starty-ScaleYInches(y))/length)]
							[(int)((ScaleXInches(x)-(int)(startx))/length)] == 4) {
						maze[(int)(((int)starty-ScaleYInches(y))/length)]
							[(int)((ScaleXInches(x)-(int)(startx))/length)] = 0;	
						}
						break;
					}
					/*case MIDDLE_BUTTON:{
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
					}*/
					default: break;
					//�����ǽ ��������� �ر����յ� 
				}
			
		}
	}
	display(); // ˢ����ʾ
}

void CharEventProcess(char ch) {
	uiGetChar(ch); // GUI�ַ�����
	display(); //ˢ����ʾ
}

// �û����������
// ����ʼ��ִ��һ��
void Main() {
	// ���������Թ���������ͷָ�������ָ��
	head=NULL;
	p=NULL;
	int i,j;
	
	// ��ʼ�����ں�ͼ��ϵͳ
	SetWindowTitle("CMAZE!");
	SetWindowSize(17, 10);
    InitGraphics();
    // ����������ɫ
	DefineColor("face", 0.96, 0.96, 0.011);
	DefineColor("facialContour", 0.83, 0.54, 0.15);
	DefineColor("mouth", 0.69, 0.42, 0.28);
	DefineColor("brick", 0.3, 0.66, 0.67);
	DefineColor("brickCenter", 0.31, 0.52, 0.67);
	DefineColor("brickJoint", 0.44, 0.41, 0.56);
	DefineColor("keyUpper", 0.86, 0.86, 0.11);
	DefineColor("keyLower", 0.93, 0.93, 0.04);
	DefineColor("lock", 0.88, 0.81, 0.09);
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
    head=LoadMazeList("data\\Maze_List.txt");
    p=head;
    adventure_head=LoadMazeList("data\\Adventure_List.txt");
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
void drawmaze(int maze[msize][msize], int x, int y) {
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
					drawlock(x, y, i, j); 
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
				}else if (maze[i][j] == 4 && abs(i-ccx) <= viewSize && abs(j-ccy)<=viewSize && haveKey == 0) {
					drawkey(x, y, i, j);
				}
				if(player[i][j] == 6){
					drawplayer(x, y, i, j);
				}
		}
	}
}

// �˵�
void drawMenu() { 
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
	static int CurrentLevel = 1;
	

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
		if(selection > 0) selectedLabel = menuListPause[selection];
		if(selection == 1) {
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
		 	haveKey = 0;
		}
		if(selection == 2) {	// �˻����˵� 
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
		 	haveKey = 0;
			
		}
	}
		
	
	// Edit �˵�
	if (ifListEdit) {
		selection = menuList(GenUIID(0),x+w,  y-h, w, wlist,h, menuListEdit,sizeof(menuListEdit)/sizeof(menuListEdit[0]));
		if (selection > 0) selectedLabel = menuListEdit[selection];
		if (selection == 3) {
			IsEditManually = TRUE;
			IsAdventuring = FALSE;
			IsChoosingMap = FALSE;
			player[ccx][ccy] = 0;
			if (IsEditManually) {
				viewSize = 100;
				ifdrawmaze = 1; 
				int i, j;
				for(i = 0; i < msize; ++i){
					for(j = 0; j < msize; ++j){
						maze[i][j] = 0;
					}
				}
				for (i = 0; i < msize; ++i){
					maze[i][0] = -1;
					maze[0][i] = -1;
					maze[i][msize - 1] = -1;
					maze[msize - 1][i] = -1;
				}
				maze[2][1] = 2;
				maze[msize-3][msize-2] = 3;
			}
		}
		if (selection == 2) {
			mazehelper(maze,2,2);
			IsEditManually = FALSE;
			IsChoosingMap = FALSE;
		}
		if (selection == 1) {
			clean(maze);
			IsEditManually = FALSE;
			IsChoosingMap = FALSE;
			ClearSolve = 1;
		}
		if (selection == 4) {
			int i,j;
			IsChoosingMap = TRUE;
			IsEditManually = FALSE;
			IsAdventuring = FALSE;
			p = head;
			for(i = 0; i < msize; ++i){
				for(j = 0; j < msize; ++j){
					maze[i][j] = p->Maze[i][j];
				}
			}
		}
	}
	
	// Solve �˵�
	if (ifListSolve) {
		selection = menuList(GenUIID(0),x+2*w,y-h, w, wlist, h, menuListSolve,sizeof(menuListSolve)/sizeof(menuListSolve[0]));
		if (selection > 0) selectedLabel = menuListSolve[selection];
		if (selection == 1) {
			int i, j, m, n;
			for (i = 2; i < msize-1; ++i) {
				for (j = 2; j < msize-1; ++j) {
					if (maze[i][j] == 4) {
						maze[i][j] = 0;
						m = i;
						n = j;
					}
				}
			}
			Solve(ccx,ccy,maze);
			maze[m][n] = 4;
			FLAG = 0;
			ClearSolve = 1;
		}
		if (selection == 2) {
			int i, j, m, n;
			for (i = 2; i < msize-1; ++i) {
				for (j = 2; j < msize-1; ++j) {
					if (maze[i][j] == 4) {
						maze[i][j] = 0;
						m = i;
						n = j;
					}
				}
			}
			Solve(ccx,ccy,maze);
			maze[m][n] = 4;
			FLAG = 0;
			ClearSolve = 0;
		}
	}
		
	// Help �˵�
	if (ifListHelp) {
		selection = menuList(GenUIID(0),winwidth/2-0.5*w,winheight/2 - h*1.2*2, w, wlist, h, menuListHelp,sizeof(menuListHelp)/sizeof(menuListHelp[0]));
		if ( selection > 0) selectedLabel = menuListHelp[selection];
		if ( selection == 1) {
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
	
	// View �˵�
	if (ifListView) {
		selection = menuList(GenUIID(0),x+3*w,y-h, w*1.2, wlist/2, h, menuListView,sizeof(menuListView)/sizeof(menuListView[0]));
		if (selection > 0) selectedLabel = menuListView[selection];
		if (selection == 1)
			viewSize = 2;
		if (selection == 2)
			viewSize = 1;
		if (selection == 3)
			viewSize = 0;
		if (selection == 4)
			viewSize = 100;
	}
	
	// �����Թ� 
	if (ifdrawmaze) {
		x = winwidth/13;
		y = winheight;
		drawmaze(maze,x+5*w,y);
		startx=x+5*w;
		starty=y;
	}

	// �ֶ��༭ 
	if (IsEditManually) {
		if (button(GenUIID(0), 6, winheight/15, w, h, "Save")){
			IsEditManually = FALSE;
			StoreMaze();
			InsertMaze(head);
			int i,j; 
			for(i = 0; i < 30; ++i) {
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
	if (ifwin&&!IsAdventuring) {
		int i, j; 
		DisplayClear();
		MovePen(winwidth/2-w*3, winheight/2+h*7);
		DrawTextString("888      888           88888888                   &&&            &&&               &&&           &&&          &&&           &&           &&88          &&");
		MovePen(winwidth/2-w*3, winheight/2+h*7-fH);
		DrawTextString("  &&&  &&&          888        888                 &&&            &&&               &&&        &&  &&        &&&            ..             88  88        88");
		MovePen(winwidth/2-w*3, winheight/2+h*7-2*fH);
		DrawTextString("    &&&&&          888            888                &&&            &&&               &&&     &&      &&     &&&             88            88    88      88");
		MovePen(winwidth/2-w*3, winheight/2+h*7-3*fH);
		DrawTextString("      &&&             888            888               &&&            &&&                &&&  &&          &&  &&&              88            88      88    88");
		MovePen(winwidth/2-w*3, winheight/2+h*7-4*fH);
		DrawTextString("      &&&               888        888                   &&&&    &&&&                    &&&&              &&&&                88            88        88  88");
		MovePen(winwidth/2-w*3, winheight/2+h*7-5*fH);
		DrawTextString("      &&&                 88888888                       &&&&&&&&                        &&                  &&                   88            88          8888");
		ifwin = 0;
		haveKey = 0;
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

	} else if(ifwin&&IsAdventuring) {
		int i, j; 
		DisplayClear();
		if (p == adventure_head->front) {
			MovePen(winwidth/2 - 0.5*TextStringWidth("Thank you for playing our game!"), winheight/2+2*fH);
			DrawTextString("Thank you for playing our game!");
			MovePen(winwidth/2 - 0.5*TextStringWidth("Now it's time to start your own adventure."), winheight/2);
			DrawTextString("Now it's time to start your own adventure.");
			CurrentLevel = 1;
		} else {
			CurrentLevel++;
			JudgeLevel(winwidth, winheight, fH, CurrentLevel);
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
	 
	
	if (IsEditManually){
		WriteEditManually(winwidth,winheight,fH);
		SetPenColor("Brown"); 
		drawLabel(8, winheight/14, "�Թ�����");
		if( textbox(GenUIID(0), 8+TextStringWidth("�Թ�����"), winheight/15, 3*w, h, MazeName, sizeof(MazeName)) );
	}//�����Թ������ı���
	
	if (IsChoosingMap){
		viewSize = 100; 
		drawLabel(1,winheight/2,p->name);
		if (button(GenUIID(0), 12, winheight/15, w, h, "NEXT")){
			p = p->next;
			int i,j;
			for (i = 0; i < msize; ++i){
				for (j = 0; j < msize; ++j){
					maze[i][j] = p->Maze[i][j];
				}
			}
		}
		if (button(GenUIID(0), 6, winheight/15, w, h, "FRONT")){
			p=p->front;
			int i,j;
			for(i=0;i<msize;i++){
				for(j=0;j<msize;j++){
					maze[i][j]=p->Maze[i][j];
				}
			}
		}
		if (button(GenUIID(0), 1, winheight/2 - 1.2*h , w, h, "Play")){
			IsChoosingMap = FALSE;
			player[ccx][ccy] = 6;
		}
	}
	
	//ð��ģʽ��ť 
	if (ifAdventureButton) {
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
	
	if (IsDisplayAbout) {
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

// ��ʾ���� 
void display() {
	// ����
	DisplayClear();

	// ���ƺʹ���˵�
	drawMenu();
}

// �ж�����Ƿ����Թ��ں��� 
bool inBox(double x, double y, double x1, double x2, double y1, double y2) {
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
 
		int range = 1 + rand() % 1;
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

// �Թ����ɸ������� 
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
	
	i = 2 + rand() % (msize-4);
	j = 2 + rand() % (msize-4);
	while (maze[i][j] != 0) {
		if (i < msize/2) ++i;
		else --i;
		if (j < msize/2) ++j;
		else --j;
	} 
	maze[i][j] = 4;
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


























