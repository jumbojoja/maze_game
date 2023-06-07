#include "graphics.h"
#include "extgraph.h"
#include "genlib.h"
#include "simpio.h"
#include "conio.h"
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

#include <windows.h>
#include <olectl.h>
#include <mmsystem.h>
#include <wingdi.h>
#include <ole2.h>
#include <ocidl.h>
#include <winuser.h>

#include "imgui.h"
#include "drawn.h"
#define length 0.45
#define msize 20

//»­Íæ¼Ò
void drawplayer(int x, int y, int i, int j)
{
	//Ä¬ÈÏ×´Ì¬ÏÂ£¬PenSizeÊÇ1 
	MovePen(x+length*j + 0.9*length, y - length*i - 0.5*length);
	StartFilledRegion(1);
	SetPenColor("face");
	DrawArc(0.4*length, 0, 360);
	EndFilledRegion();
	SetPenColor("facialContour");
	SetPenSize(2);
	
	MovePen(x+length*j + 0.92*length, y - length*i - 0.52*length);
	DrawArc(0.4*length, 0, 360);
	SetPenSize(1);
	SetPenColor("Red");
	
	MovePen(x+length*j + 0.225*length, y - length*i - 0.58*length);
	SetPenColor("mouth");
	SetPenSize(2);
	DrawArc(0.315*length, 195, 150);
	SetPenSize(1);
	SetPenColor("Red");
	
	MovePen(x+length*j + 0.16*length, y - length*i - 0.32*length);
	SetPenColor("White");
	SetPenSize(2);
	StartFilledRegion(1);
	DrawArc(0.06*length, 130, 180);
	DrawArc(0.12*length, 130, -80);
	DrawArc(0.06*length, 230, 180);
	DrawArc(0.24*length, 50, 80);
	EndFilledRegion();
	SetPenColor("mouth");
	DrawArc(0.06*length, 130, 180);
	DrawArc(0.12*length, 130, -80);
	DrawArc(0.06*length, 230, 180);
	DrawArc(0.24*length, 50, 80);
	MovePen(x+length*j + 0.56*length, y - length*i - 0.32*length);
	SetPenColor("White");
	StartFilledRegion(1);
	DrawArc(0.06*length, 130, 180);
	DrawArc(0.12*length, 130, -80);
	DrawArc(0.06*length, 230, 180);
	DrawArc(0.24*length, 50, 80);
	EndFilledRegion();
	SetPenColor("mouth");
	DrawArc(0.06*length, 130, 180);
	DrawArc(0.12*length, 130, -80);
	DrawArc(0.06*length, 230, 180);
	DrawArc(0.24*length, 50, 80);
	SetPenSize(1);
	SetPenColor("Red");
	
	//»­ÑÛ¾¦
	MovePen(x+length*j + 0.23*length, y - length*i - 0.36*length);
	SetPenColor("Brown");
	StartFilledRegion(1);
	DrawArc(0.025*length, 0, 360);
	EndFilledRegion(); 
	MovePen(x+length*j + 0.63*length, y - length*i - 0.36*length);
	SetPenColor("Brown");
	StartFilledRegion(1);
	DrawArc(0.025*length, 0, 360);
	EndFilledRegion(); 
	SetPenSize(1);
	SetPenColor("Red");
} 

//»æÖÆÇ½
void drawwall(int x, int y, int i, int j)
{
	//»­×© 
	MovePen(x + length*j, y - length*i);
	StartFilledRegion(1); 
	SetPenColor("brick");
	DrawLine(2.0*length/3.0,0);
	DrawLine(0,-1.0*length/3.0);
	DrawLine(-2.0*length/3.0,0);
	DrawLine(0,1.0*length/3.0);
	EndFilledRegion();
	MovePen(x + length*j+2.0*length/3.0, y - length*i);
	StartFilledRegion(1); 
	DrawLine(1.0*length/3.0,0);
	DrawLine(0,-2.0*length/3.0);
	DrawLine(-1.0*length/3.0,0);
	DrawLine(0,2.0*length/3.0);
	EndFilledRegion();
	MovePen(x + length*j + 1.0*length/3.0, y - length*i - 2.0*length/3.0);
	StartFilledRegion(1); 
	DrawLine(2.0*length/3.0,0);
	DrawLine(0,-1.0*length/3.0);
	DrawLine(-2.0*length/3.0,0);
	DrawLine(0,1.0*length/3.0);
	EndFilledRegion();
	MovePen(x + length*j, y - length*i - 1.0*length/3.0);
	StartFilledRegion(1); 
	DrawLine(1.0*length/3.0,0);
	DrawLine(0,-2.0*length/3.0);
	DrawLine(-1.0*length/3.0,0);
	DrawLine(0,2.0*length/3.0);
	EndFilledRegion();
	MovePen(x + length*j + 1.0*length/3.0, y - length*i - 1.0*length/3.0);
	StartFilledRegion(1);
	SetPenColor("brickCenter"); 
	DrawLine(1.0*length/3.0,0);
	DrawLine(0,-1.0*length/3.0);
	DrawLine(-1.0*length/3.0,0);
	DrawLine(0,1.0*length/3.0);
	EndFilledRegion();
	SetPenColor("Red");
	
	//»­×©·ì
	SetPenColor("brickJoint"); 
	MovePen(x + length*j, y - length*i);
	DrawLine(2.0*length/3.0,0);
	DrawLine(0,-1.0*length/3.0);
	DrawLine(-2.0*length/3.0,0);
	DrawLine(0,1.0*length/3.0);
	MovePen(x + length*j+2.0*length/3.0, y - length*i); 
	DrawLine(1.0*length/3.0,0);
	DrawLine(0,-2.0*length/3.0);
	DrawLine(-1.0*length/3.0,0);
	DrawLine(0,2.0*length/3.0);
	MovePen(x + length*j + 1.0*length/3.0, y - length*i - 2.0*length/3.0);
	DrawLine(2.0*length/3.0,0);
	DrawLine(0,-1.0*length/3.0);
	DrawLine(-2.0*length/3.0,0);
	DrawLine(0,1.0*length/3.0);
	MovePen(x + length*j, y - length*i - 1.0*length/3.0); 
	DrawLine(1.0*length/3.0,0);
	DrawLine(0,-2.0*length/3.0);
	DrawLine(-1.0*length/3.0,0);
	DrawLine(0,2.0*length/3.0);
	MovePen(x + length*j + 1.0*length/3.0, y - length*i - 1.0*length/3.0);
	DrawLine(1.0*length/3.0,0);
	DrawLine(0,-1.0*length/3.0);
	DrawLine(-1.0*length/3.0,0);
	DrawLine(0,1.0*length/3.0);
	SetPenColor("Red");
}

//»­Ô¿³×
void drawkey(int x, int y, int i, int j)
{
	MovePen(x + length*j + 0.66*length, y - length*i - 0.34*length);
	SetPenColor("keyUpper");
	StartFilledRegion(1);
	DrawArc(0.11*length, 225, -180);
	DrawLine(0.06*length, 0.06*length);
	DrawArc(0.29*length, 45, 180);
	DrawLine(0.20*length, 0.20*length);
	EndFilledRegion();
	
	MovePen(x + length*j + 0.5*length, y - length*i - 0.5*length);
	StartFilledRegion(1);
	DrawLine(-0.06*length, 0.06*length);
	DrawLine(-0.32*length, -0.32*length);
	DrawLine(0, -0.12*length);
	DrawLine(0.48*length, 0.48*length);
	EndFilledRegion();
	
	SetPenColor("keyLower");
	MovePen(x + length*j + 0.66*length, y - length*i - 0.34*length);
	StartFilledRegion(1);
	DrawArc(0.11*length, 225, 180);
	DrawLine(0.06*length, 0.06*length);
	DrawArc(0.29*length, 45, -180);
	DrawLine(0.20*length, 0.20*length);
	EndFilledRegion();
	
	MovePen(x + length*j + 0.5*length, y - length*i - 0.5*length);
	StartFilledRegion(1);
	DrawLine(0.04*length, -0.04*length);
	DrawLine(-0.16*length, -0.16*length);
	DrawLine(0, -0.07*length);
	DrawLine(-0.07*length, 0);
	DrawLine(0, -0.07*length);
	DrawLine(-0.15*length, 0);
	EndFilledRegion();
	SetPenColor("Red");
}

//»­Ëø
void drawlock(int x, int y, int i, int j)
{
	MovePen(x + length*j, y - length*i);
	SetPenColor("lock");
	StartFilledRegion(1);
	DrawLine(length,0);
	DrawLine(0,-1.0*length);
	DrawLine(-1.0*length,0);
	DrawLine(0,length);
	EndFilledRegion();
	
	MovePen(x + length * j + 0.247*length, y - length*i - 0.447*length);
	SetPenColor("White");
	StartFilledRegion(1);
	DrawLine(0, -0.39*length);
	DrawLine(0.506*length, 0);
	DrawLine(0, 0.39*length);
	DrawLine(-0.506*length, 0);
	EndFilledRegion();
	
	MovePen(x + length*j + 0.73*length, y - length*i - 0.4*length);
	SetPenSize(3);
	DrawArc(0.22*length, 0, 180);
	SetPenSize(1);
	
	MovePen(x + length*j + 0.5*length, y - length*i - 0.5*length);
	StartFilledRegion(1);
	SetPenColor("lock");
	DrawArc(0.06*length, 90, 360);
	EndFilledRegion();
	MovePen(x + length*j + 0.51*length, y - length*i - 0.5*length);
	SetPenSize(2);
	DrawLine(0, -0.25*length);
	SetPenSize(1);
	/*StartFilledRegion(1);
	DrawLine(-0.06*length, -0.3*length);
	DrawLine(0, 0.12*length);
	DrawLine(-0.06*length, 0.3*length);
	EndFilledRegion();*/
	
 } 
