/* ��һ�ļ����ڻ�����ͷ�ļ�
 * ���ݰ�����
 * 1.����ǽ���� 
 * 2.����Һ���
 * 3.��Կ�׺���
 * 4.�������� 
 */
 
#ifndef _DRWAN_
#define _DRAWN_

/* ����ǽ���� 
 * �������ͣ�int, int, int, int  
 * ����ֵ���ͣ��޷���ֵ 
 */
void drawwall(int x, int y, int i, int j);

/* ����Һ���
 * �������ͣ�int, int, int, int  
 * ����ֵ���ͣ��޷���ֵ 
 */
void drawplayer(int x, int y, int i, int j);

/* ��Կ�׺���
 * �������ͣ�int, int, int, int  
 * ����ֵ���ͣ��޷���ֵ 
 */
void drawkey(int x, int y, int i, int j); 

/* ��������
 * �������ͣ�int, int, int, int  
 * ����ֵ���ͣ��޷���ֵ 
 */
void drawlock(int x, int y, int i, int j); 
#endif
