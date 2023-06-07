/* 这一文件用于实现迷宫建立文件保存 */
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
#include <string.h>

#include "imgui.h"
#include "file_store.h"
#include "drawn.h"
#include "paperwork.h"
#include "adventure.h"

#define msize 20

extern bool IsEditManually;

extern int maze[msize][msize];

extern char MazeName[30];

extern struct EdittedMaze *head;
extern struct EdittedMaze *p;

int MazeNumber=1;

void StoreMaze()
{
	FILE *fp;
	int i,j;
	
		if((fp=fopen("data\\Maze_List.txt","a"))==NULL){
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

struct EdittedMaze *LoadMazeList( char str[] )
{
	char ch;
	char temp[30]; 
	FILE *fp;
	struct EdittedMaze *head,*p1,*p2;
	int i,j,k=0;
	int flag=0;
	
	if((fp=fopen(str,"r"))==NULL){
		exit(-1);
	}
	
	head=NULL;
	p1=NULL;
	p2=NULL;
	
	while(!feof(fp)){
		p1=(struct EdittedMaze*)malloc(sizeof(struct EdittedMaze));
		
		ch=fgetc(fp);
		if(ch == '\0'||ch == -1){
			continue;
		}
		if(flag){
			ch=fgetc(fp);
			if(ch == '\0'||ch == -1){
				continue;
			}
		}
		 
		p1->number=MazeNumber;
		MazeNumber++;/* 给迷宫编号 */
		
		fgets(p1->name,30,fp);
		
		for(i=0;i<msize;i++){
			for(j=0;j<msize;j++){
				fscanf(fp,"%d",&p1->Maze[i][j]);
			}
		}/* 读迷宫主体 */
		
		fgetc(fp);/* 读掉末尾换行符 */
		
		if(head == NULL){
			head=p1;
			p2=head;
		}else{
			p2->next=p1;
			p1->front=p2;
			p2=p2->next;
		}
		flag=1;
	}
	
	p2->next=head;
	head->front=p2;
	
	if(fclose(fp)){
		exit(-1);
	}
	
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

void DeleteMaze(struct EdittedMaze *head)
{
	FILE *fp;
	struct EdittedMaze *p1,*p2;
	int i,j;
	
	if((fp=fopen("data\\Maze_List.txt","w"))==NULL){
		exit(-1);
	}
	if(p==p->next){
		exit(-1);
	}
	if(p==head){
		head=head->next;
	}
	p1=p->front;
	p->next->front=p1;
	p1->next=p->next;
	
	p->front=NULL;
	p->next=NULL;
	free(p);
	p=p1->next;/* 游戏中的链表操作 */
	
	for(p2=head;p2->number!=head->front->number;p2=p2->next){
    	fprintf(fp,"\n");
    	fputs(p2->name,fp);
    	for(i=0;i<msize;i++){
    		for(j=0;j<msize;j++){
    			fprintf(fp,"%d ",p2->Maze[i][j]);
    		}
    		fprintf(fp,"\n");
    	}
    } 
	fprintf(fp,"\n");
    fputs(p2->name,fp);
    for(i=0;i<msize;i++){
    	for(j=0;j<msize;j++){
    		fprintf(fp,"%d ",p2->Maze[i][j]);
    	}
    	fprintf(fp,"\n");
    }
    if(fclose(fp)){
		exit(-1);
	}
	
}
