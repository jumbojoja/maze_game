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
#include "file_store.h"
//必要头文件包含

#define msize 20

extern bool IsEditManually;

extern int maze[msize][msize];

extern char MazeName[30];

int MazeNumber=1;

void StoreMaze()
{
	FILE *fp;
	int i,j;
	
		if((fp=fopen("Maze_List.txt","a"))==NULL){
			exit(-1);
		}
		
		fprintf(fp,"\n");
		
		for(i=0;MazeName[i]!='\0';i++){
			fprintf(fp,"%c",MazeName[i]);
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
	struct EdittedMaze *head,*p1,*p2;
	int i,j;
	
	if((fp=fopen("Maze_List.txt","r"))==NULL){
		exit(-1);
	}
	
	head=CreateMazeList();
	p1=NULL;
	p2=head;
	
	while(!feof(fp)){
		p1=(struct EdittedMaze*)malloc(sizeof(struct EdittedMaze));
		
		fgetc(fp);//读掉换行符
		 
		p1->number=MazeNumber;
		MazeNumber++;//给迷宫编号 
		
		fgets(p1->name,30,fp);//读名字 
		
		for(i=0;i<msize;i++){
			for(j=0;j<msize;j++){
				fscanf(fp,"%d",&p1->Maze[i][j]);
			}
		}//读迷宫主体 
		
		p2->next=p1;
		p1->front=p2;
		p2=p2->next; 
	}
	
	p2->next=head;
	head->front=p2;
	
	return head;
}

struct EdittedMaze *CreateMazeList()
{
	struct EdittedMaze *head;
	head=(struct EdittedMaze*)malloc(sizeof(struct EdittedMaze));
	
	head->next=head->front=NULL;
	
	return head;
}

void InsertMaze(struct EdittedMaze *head)
{
	struct EdittedMaze *p;
	int    i,j;
	
	p=(struct EdittedMaze*)malloc(sizeof(struct EdittedMaze));
	
	p->number=MazeNumber;
	MazeNumber++;
	
	for(i=0;MazeName[i]!='\0';i++){
		p->name[i]=MazeName[i]; 
	}
	
	for(i=0;i<msize;i++){
		for(j=0;j<msize;j++){
			p->Maze[i][j]=maze[i][j];
		}
	}
	
	head->front->next=p;
	p->front=head->front;
	p->next=head;
	head->front=p;
	
}
