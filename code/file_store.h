/* 这一文件用于用于迷宫建立文件保存的头文件 
 * 内容包含：
 * 1.链表结点 结构定义
 * 2.用于保存当前迷宫至Maze_List文件的函数
 * 3.用于加载MAZE的函数
 * 4.用于删除结点的函数
 * 5.创建链表函数
 * 6.插入新地图至当前链表的函数
 */
 
#ifndef _FILE_STORE_
#define _FILE_STORE_
#define msize 20

struct EdittedMaze{
	int number;
	char name[30];
	int Maze[msize][msize];
	struct EdittedMaze *next;
	struct EdittedMaze *front; 
};/* 链表结点 结构定义 */

/* 用于保存当前迷宫至Maze_List文件的函数，
 * 参数类型：没有参数
 * 返回值：没有返回值
 */
void StoreMaze(void);

/* 用于于加载MAZE的函数
 * 参数类型：char [], 存放数据的文件名 
 * 返回值：类型为 struct EdittedMaze* 的头结点指针
 */
struct EdittedMaze *LoadMazeList(char str[]);

/* 用于删除结点的函数。
 * 参数类型：struct EdittedMaze * ，头结点指针 
 * 返回值：没有返回值
 */
void DeleteMaze(struct EdittedMaze *head);

/* 用于创建链表函数，文件开始时调用，创建一个双向链表
 * 参数类型：没有参数 
 * 返回值：类型为 struct EdittedMaze* 的头结点指针
 */
struct EdittedMaze *CreateMazeList(void);

/* 用于插入新地图至当前链表的函数。在save按钮点了之后和写文件一起执行，将新建地图插入当前序列
 * 参数类型：struct EdittedMaze * ，头结点指针 
 * 返回值：没有返回值
 */
void InsertMaze(struct EdittedMaze *head); 

#endif
