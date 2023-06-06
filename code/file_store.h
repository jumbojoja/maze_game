#ifndef _FILE_STORE_
#define _FILE_STORE_
#define msize 20
struct EdittedMaze{
	int number;
	char name[30];
	int Maze[msize][msize];
	struct EdittedMaze *next;
	struct EdittedMaze *front; 
};//������ �ṹ���� 

//���ڱ��浱ǰ�Թ���Maze_List�ļ��ĺ�����ֱ�ӵ��ã�û�в��� 
void StoreMaze(void);

//���ڼ���MAZE�ĺ�����ÿ�δ���Ϸʱ���ã����Ѿ������MAZE����Ϊһ������
//����ֵ:ͷ���ָ�� 
struct EdittedMaze *LoadMazeList(char str[]);

//����ɾ�����ĺ�����
void DeleteMaze(struct EdittedMaze *head);

//�������������ļ���ʼʱ���ã�����һ��˫������
//����ֵ:һ������Ϊstruct EdittedMaze* ������ͷָ�� 
struct EdittedMaze *CreateMazeList();

//���ڲ����µ�ͼ����ǰ����ĺ�������save��ť����֮���д�ļ�һ��ִ�У����½���ͼ���뵱ǰ���� 
void InsertMaze(struct EdittedMaze *head); 

#endif
