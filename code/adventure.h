/* 这一文件用于冒险模式的头文件
 * 内容包含：
 * 1.冒险模式函数，调用即开始冒险模式
 * 2.关卡判断函数
 */
 
#ifndef _ADVENTURE_
#define _ADVENTURE_

/* 冒险模式函数，调用即开始冒险模式 
 * 参数类型：无参数
 * 返回值类型：无返回值 
 */
void StartAdventure(void);

/* 关卡判断函数 
 * 参数类型：double 窗口宽度， double 窗口高度， double 字符高度， int 当前关卡 
 * 返回值类型：无返回值 
 */
void JudgeLevel(double winwidth, double winheight, double fH, int CurrentLevel);

#endif 
