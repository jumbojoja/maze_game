#ifndef _FILE_STORE_
#define _FILE_STORE_

//���ڱ��浱ǰ�Թ���Maze_List�ļ��ĺ�����ֱ�ӵ��ã�û�в��� 
void StoreMaze(void);

//���ڼ���MAZE�ĺ�����ÿ�δ���Ϸʱ���ã����Ѿ������MAZE����Ϊһ������
//����ֵ:ͷ���ָ�� 
struct EdittedMaze *LoadMazeList(void);

//����ɾ�����ĺ�������δʵ�� 
void DeleteMaze(void);

#endif
