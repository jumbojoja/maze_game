#ifndef _FILE_STORE_
#define _FILE_STORE_

//用于保存当前迷宫至Maze_List文件的函数，直接调用，没有参数 
void StoreMaze(void);

//用于加载MAZE的函数，每次打开游戏时调用，将已经保存的MAZE保存为一个链表
//返回值:头结点指针 
struct EdittedMaze *LoadMazeList(void);

//用于删除结点的函数。还未实现 
void DeleteMaze(void);

#endif
