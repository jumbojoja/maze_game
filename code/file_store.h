#ifndef _FILE_STORE_
#define _FILE_STORE_
#define msize 20
struct EdittedMaze{
	int number;
	char name[30];
	int Maze[msize][msize];
	struct EdittedMaze *next;
	struct EdittedMaze *front; 
};//链表结点 结构定义 

//用于保存当前迷宫至Maze_List文件的函数，直接调用，没有参数 
void StoreMaze(void);

//用于加载MAZE的函数，每次打开游戏时调用，将已经保存的MAZE保存为一个链表
//返回值:头结点指针 
struct EdittedMaze *LoadMazeList(char str[]);

//用于删除结点的函数。
void DeleteMaze(struct EdittedMaze *head);

//创建链表函数，文件开始时调用，创建一个双向链表
//返回值:一个类型为struct EdittedMaze* 的链表头指针 
struct EdittedMaze *CreateMazeList();

//用于插入新地图至当前链表的函数。在save按钮点了之后和写文件一起执行，将新建地图插入当前序列 
void InsertMaze(struct EdittedMaze *head); 

#endif
