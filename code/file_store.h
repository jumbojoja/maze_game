/* ��һ�ļ����������Թ������ļ������ͷ�ļ� 
 * ���ݰ�����
 * 1.������ �ṹ����
 * 2.���ڱ��浱ǰ�Թ���Maze_List�ļ��ĺ���
 * 3.���ڼ���MAZE�ĺ���
 * 4.����ɾ�����ĺ���
 * 5.����������
 * 6.�����µ�ͼ����ǰ����ĺ���
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
};/* ������ �ṹ���� */

/* ���ڱ��浱ǰ�Թ���Maze_List�ļ��ĺ�����
 * �������ͣ�û�в���
 * ����ֵ��û�з���ֵ
 */
void StoreMaze(void);

/* �����ڼ���MAZE�ĺ���
 * �������ͣ�char [], ������ݵ��ļ��� 
 * ����ֵ������Ϊ struct EdittedMaze* ��ͷ���ָ��
 */
struct EdittedMaze *LoadMazeList(char str[]);

/* ����ɾ�����ĺ�����
 * �������ͣ�struct EdittedMaze * ��ͷ���ָ�� 
 * ����ֵ��û�з���ֵ
 */
void DeleteMaze(struct EdittedMaze *head);

/* ���ڴ������������ļ���ʼʱ���ã�����һ��˫������
 * �������ͣ�û�в��� 
 * ����ֵ������Ϊ struct EdittedMaze* ��ͷ���ָ��
 */
struct EdittedMaze *CreateMazeList(void);

/* ���ڲ����µ�ͼ����ǰ����ĺ�������save��ť����֮���д�ļ�һ��ִ�У����½���ͼ���뵱ǰ����
 * �������ͣ�struct EdittedMaze * ��ͷ���ָ�� 
 * ����ֵ��û�з���ֵ
 */
void InsertMaze(struct EdittedMaze *head); 

#endif
