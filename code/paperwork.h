/* 这一文件用于写文案的函数的头文件
 * 内容包含：
 * 1.写指南用的函数
 * 2.写关于用的函数
 * 3.写手动编辑文案用的函数
 * 4.一系列关卡文案函数
 */

#ifndef _PAPERWORK_
#define _PAPERWORK_

/* 写指南用的函数 
 * 参数类型：double 窗口宽度， double 窗口高度， double 控件宽度， double 字符高度
 * 返回值类型：无返回值 
 */
void WriteInstructions(double winwidth, double winheight, double w, double fH);

/* 写关于用的函数 
 * 参数类型：double 窗口宽度， double 窗口高度， double 字符高度
 * 返回值类型：无返回值 
 */
void WriteAbout(double winwidth, double winheight, double fH);

/* 写手动编辑文案用的函数
 * 参数类型：double 窗口宽度， double 窗口高度， double 字符高度
 * 返回值类型：无返回值 
 */
void WriteEditManually(double winwidth, double winheight, double fH);

/* 一系列关卡文案函数
 * 参数类型：double 窗口宽度， double 窗口高度， double 字符高度
 * 返回值类型：无返回值 
 */
void WriteAdventure2(double winwidth, double winheight, double fH);
void WriteAdventure3(double winwidth, double winheight, double fH);
void WriteAdventure4(double winwidth, double winheight, double fH);
void WriteAdventure5(double winwidth, double winheight, double fH);
void WriteAdventure6(double winwidth, double winheight, double fH);
void WriteAdventure7(double winwidth, double winheight, double fH);
void WriteAdventure8(double winwidth, double winheight, double fH);
void WriteAdventure9(double winwidth, double winheight, double fH);
#endif
