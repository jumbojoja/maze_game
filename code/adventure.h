/* ��һ�ļ�����ð��ģʽ��ͷ�ļ�
 * ���ݰ�����
 * 1.ð��ģʽ���������ü���ʼð��ģʽ
 * 2.�ؿ��жϺ���
 */
 
#ifndef _ADVENTURE_
#define _ADVENTURE_

/* ð��ģʽ���������ü���ʼð��ģʽ 
 * �������ͣ��޲���
 * ����ֵ���ͣ��޷���ֵ 
 */
void StartAdventure(void);

/* �ؿ��жϺ��� 
 * �������ͣ�double ���ڿ�ȣ� double ���ڸ߶ȣ� double �ַ��߶ȣ� int ��ǰ�ؿ� 
 * ����ֵ���ͣ��޷���ֵ 
 */
void JudgeLevel(double winwidth, double winheight, double fH, int CurrentLevel);

#endif 
