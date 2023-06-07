/* 这一文件用于画画的头文件
 * 内容包含：
 * 1.绘制墙函数 
 * 2.画玩家函数
 * 3.画钥匙函数
 * 4.画锁函数 
 */
 
#ifndef _DRWAN_
#define _DRAWN_

/* 绘制墙函数 
 * 参数类型：int, int, int, int  
 * 返回值类型：无返回值 
 */
void drawwall(int x, int y, int i, int j);

/* 画玩家函数
 * 参数类型：int, int, int, int  
 * 返回值类型：无返回值 
 */
void drawplayer(int x, int y, int i, int j);

/* 画钥匙函数
 * 参数类型：int, int, int, int  
 * 返回值类型：无返回值 
 */
void drawkey(int x, int y, int i, int j); 

/* 画锁函数
 * 参数类型：int, int, int, int  
 * 返回值类型：无返回值 
 */
void drawlock(int x, int y, int i, int j); 
#endif
