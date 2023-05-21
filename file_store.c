//��һ�ļ�����ʵ���Թ������ļ����� 
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
//��Ҫͷ�ļ�����

#define msize 15

extern bool IsEditManually;
extern int maze[msize][msize];

struct EdittedMaze{
	int number;
	bool sight;//��һ�������ڱ�ʾ�Ƿ�����Ұ�ڵ� 
	char name[20];
	int Maze[msize][msize];
	struct EdittedMaze *next; 
};//������ �ṹ���� 

//���ڱ���Maze�ĺ��� ��ʹ��ʱֱ�ӵ��ü��� 
void StoreMaze();

//���ڼ���MAZE�ĺ�����ÿ�δ���Ϸʱ���ã����Ѿ������MAZE����Ϊһ����������ֵΪͷ���ָ�� 
struct EdittedMaze *LoadMazeList();

//����ɾ�����ĺ�������δʵ�� 
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
