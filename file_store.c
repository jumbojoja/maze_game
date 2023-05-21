//这一文件用于实现迷宫建立文件保存 
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
//必要头文件包含

#define msize 15

extern bool IsEditManually;
extern int maze[msize][msize];

struct EdittedMaze{
	int number;
	bool sight;//这一变量用于表示是否开启视野遮挡 
	char name[20];
	int Maze[msize][msize];
	struct EdittedMaze *next; 
};//链表结点 结构定义 

//用于保存Maze的函数 ，使用时直接调用即可 
void StoreMaze();

//用于加载MAZE的函数。每次打开游戏时调用，将已经保存的MAZE保存为一个链表，返回值为头结点指针 
struct EdittedMaze *LoadMazeList();

//用于删除结点的函数。还未实现 
void DeleteMaze(); 

void StoreMaze()
{
	FILE *fp;
	int i,j;
	
		if((fp=fopen("Maze_List.txt","a"))==NULL){
			exit(-1);
		}
		
		fprintf(fp,"\n");
		for(i=0;i<msize;i++){
			for(j=0;j<msize;j++){
				fprintf(fp,"%d ",maze[i][j]);
			}
			fprintf(fp,"\n");
		}
	
		if(fclose(fp)){
			exit(-1);
		}
}

struct EdittedMaze *LoadMazeList()
{
	FILE *fp;
	struct EdittedMaze *head,*p,*ptr;
	int number=1,i,j;
	
	if((fp=fopen("Maze_List.txt","a"))==NULL){
		exit(-1);
	}
	
	head=NULL;
	p=NULL;
	ptr=NULL;
	
	while(!feof(fp)){
		p=(struct EdittedMaze*)malloc(sizeof(struct EdittedMaze));
		
		p->number=number;
		number++;
		for(i=0;i<msize;i++){
			for(j=0;j<msize;j++){
				fscanf(fp,"%d",&p->Maze[i][j]);
			}
		}
		
		if(head==NULL){
			head=p;
			ptr=head;
			head->next=NULL;
		}else{
			ptr->next=p;
			ptr=ptr->next;
		}
	}
	
	return head;
}
