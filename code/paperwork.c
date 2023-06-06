//这一文件用于存放写文案的函数 
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
#include <time.h>
#include <math.h>

#include "imgui.h"
#include "file_store.h"
#include "paperwork.h"

#define msize 20
#define length 0.25

void WriteInstructions(double winwidth, double winheight, double w, double fH)
{
	SetPenColor("Orange");
	MovePen(winwidth/2+1.8*w, winheight/2);
	DrawTextString("Use <- ^ v -> to move.");
	MovePen(winwidth/2+1.8*w, winheight/2-fH);
	DrawTextString("Pause->Restart to restart.");
	MovePen(winwidth/2+1.8*w, winheight/2-2*fH);
	DrawTextString("Edit->Clean to clear solved path.");
	MovePen(winwidth/2+1.8*w, winheight/2-3*fH);
	DrawTextString("Edit->Regenerate to regenerate maze.");
	MovePen(winwidth/2+1.8*w, winheight/2-4*fH);
	DrawTextString("Edit->Edit Manually to edit maze.");
	MovePen(winwidth/2+1.8*w, winheight/2-5*fH);
	DrawTextString("Solve->Auto Solve to solve maze.");
	MovePen(winwidth/2+1.8*w, winheight/2-6*fH);
	DrawTextString("Solve->Tips to see tips.");
	MovePen(winwidth/2+1.8*w, winheight/2-7*fH);
	DrawTextString("Set view to set your view.");
} 

void WriteAbout(double winwidth, double winheight, double fH)
{
	SetPenColor("Orange");
	MovePen(winwidth/2-0.5*TextStringWidth("We are a C team from Zhejiang University."), winheight*0.8);
	DrawTextString("We are a C team from Zhejiang University.");
	MovePen(winwidth/2-0.5*TextStringWidth("This maze game has cost us over a month to finish."), winheight*0.8-2*fH);
	DrawTextString("This maze game has cost us over a month to finish.");
	MovePen(winwidth/2-0.5*TextStringWidth("In this procedure, we came across many difficulties..."), winheight*0.8-4*fH);
	DrawTextString("In this procedure, we came across many difficulties...");
	MovePen(winwidth/2-0.5*TextStringWidth("However, we were having great fun too."), winheight*0.8-6*fH);
	DrawTextString("However, we were having great fun too.");
	MovePen(winwidth/2-0.5*TextStringWidth("Our work is small, but it does contain some very interesting functions."), winheight*0.8-8*fH);
	DrawTextString("Our work is small, but it does contain some very interesting functions.");
	MovePen(winwidth/2-0.5*TextStringWidth("Hope you will like it."), winheight*0.8-10*fH);
	DrawTextString("Hope you will like it.");
	MovePen(winwidth/2-0.5*TextStringWidth("Oh, yes. We have designed some plots in the adventure."), winheight*0.8-12*fH);
	DrawTextString("Oh, yes. We have designed some plots in the adventure.");
	MovePen(winwidth/2-0.5*TextStringWidth("It's a story about a man saving himself from depression."), winheight*0.8-14*fH);
	DrawTextString("It's a story about a man saving himself from depression.");
	MovePen(winwidth/2-0.5*TextStringWidth("Hope you could slow down your pace and enjoy our story."), winheight*0.8-16*fH);
	DrawTextString("Hope you could slow down your pace and enjoy our story.");
	MovePen(winwidth/2-0.5*TextStringWidth("Thank you for playing our game."), winheight/13+2*fH);
	DrawTextString("Thank you for playing our game.");
}

void WriteEditManually(double winwidth, double winheight, double fH){
	SetPenColor("Orange");
	MovePen(0, winheight*0.8-fH);
	DrawTextString("Use the left button of your mouse to add walls.");
	MovePen(0, winheight*0.8-2*fH);
	DrawTextString("Use the right button of your mouse to add keys.");
	MovePen(0, winheight*0.8-5*fH);
	DrawTextString("If you have finished your edit work,");
	MovePen(0, winheight*0.8-6*fH);
	DrawTextString("you can type in the name of your maze");
	MovePen(0, winheight*0.8-7*fH);
	DrawTextString("and click save to save it.");
	MovePen(0, winheight*0.8-8*fH);
	DrawTextString("You can later find your maze in Choosing Maps.");
	MovePen(0, winheight*0.8-10*fH);
	DrawTextString("The blue cell stands for the start point.");
	MovePen(0, winheight*0.8-11*fH);
	DrawTextString("The orange cell stands for the finish point.");
}

void WriteAdventure2(double winwidth, double winheight, double fH)
{
	SetPenColor("Orange");
	MovePen(winwidth/2-0.5*TextStringWidth("It has been several years since I was diagnosed with depression."), winheight/2 + 6*fH);
	DrawTextString("It has been several years since I was diagnosed with depression.");
	MovePen(winwidth/2-0.5*TextStringWidth("Every night, I dreamed of mazes. Millions of them."), winheight/2 + 4*fH);
	DrawTextString("Every night, I dreamed of mazes. Millions of them.");
	MovePen(winwidth/2-0.5*TextStringWidth("Sometimes I feel my life is like a maze, too."), winheight/2 + 2*fH);
	DrawTextString("Sometimes I feel my life is like a maze, too.");
	MovePen(winwidth/2-0.5*TextStringWidth("And I am the person who gets stuck in all those cells."), winheight/2 );
	DrawTextString("And I am the person who gets stuck in all those cells.");
	MovePen(winwidth/2-0.5*TextStringWidth("I keep walking, trying to find a way out."), winheight/2 - 2*fH);
	DrawTextString("I keep walking, trying to find a way out.");
	MovePen(winwidth/2-0.5*TextStringWidth("Tantacles of fear grab me by my neck. I am suffocating to death."), winheight/2 - 4*fH);
	DrawTextString("Tantacles of fear grab me by my neck. I am suffocating to death.");
	MovePen(winwidth/2-0.5*TextStringWidth("Perhaps when I arrive at the destination, things will get better."), winheight/2 - 6*fH);
	DrawTextString("Perhaps when I arrive at the destination, things will get better.");
	MovePen(winwidth/2-0.5*TextStringWidth("Press any direction key to continue"), winheight/3);
	SetPenColor("Blue");
	DrawTextString("Press any direction key to continue");
	
}

void WriteAdventure3(double winwidth, double winheight, double fH)
{
	SetPenColor("Orange");
	MovePen(winwidth/2-0.5*TextStringWidth("We are going on. Cells."), winheight/2 + 8*fH);
	DrawTextString("We are going on. Cells.");
	MovePen(winwidth/2-0.5*TextStringWidth("They were all put together at a time. Cells."), winheight/2 + 6*fH);
	DrawTextString("They were all put together at a time. Cells.");
	MovePen(winwidth/2-0.5*TextStringWidth("Millions and billions of them. Cells."), winheight/2 + 4*fH);
	DrawTextString("Millions and billions of them. Cells.");
	MovePen(winwidth/2-0.5*TextStringWidth("Were you ever arrested? Cells."), winheight/2 + 2*fH);
	DrawTextString("Were you ever arrested? Cells.");
	MovePen(winwidth/2-0.5*TextStringWidth("Have you been in an institution? Cells."), winheight/2 );
	DrawTextString("Have you been in an institution? Cells.");
	MovePen(winwidth/2-0.5*TextStringWidth("Do they keep you in a cell? Cells."), winheight/2 - 2*fH);
	DrawTextString("Do they keep you in a cell? Cells.");
	MovePen(winwidth/2-0.5*TextStringWidth("When you're not performing your duties do they keep you in a little box? Cells."), winheight/2 - 4*fH);
	DrawTextString("When you're not performing your duties do they keep you in a little box? Cells.");
	MovePen(winwidth/2, winheight/2 - 6*fH);
	DrawTextString("from <<Blade Runner 2049>>");
	MovePen(winwidth/2-0.5*TextStringWidth("Press any direction key to continue"), winheight/3);
	SetPenColor("Blue");
	DrawTextString("Press any direction key to continue");
	
}

void WriteAdventure4(double winwidth, double winheight, double fH)
{
	SetPenColor("Orange");
	MovePen(winwidth/2-0.5*TextStringWidth("Forgive me."), winheight/2 + 4*fH);
	DrawTextString("Forgive me.");
	MovePen(winwidth/2-0.5*TextStringWidth("I just can't help thinking of strange things."), winheight/2 + 2*fH);
	DrawTextString("I just can't help thinking of strange things.");
	MovePen(winwidth/2-0.5*TextStringWidth("Thank you, I never go such deep into my dream maze."), winheight/2);
	DrawTextString("Thank you, I have never gone such deep into my dream maze.");
	MovePen(winwidth/2-0.5*TextStringWidth("But why do I have a feeling that the darkness is approaching?"), winheight/2 - 2*fH);
	DrawTextString("But why do I have a feeling that the darkness is approaching?");
	SetPenColor("Blue");
	MovePen(winwidth/2-0.5*TextStringWidth("Press any direction key to continue"), winheight/3);
	DrawTextString("Press any direction key to continue");
}

void WriteAdventure5(double winwidth, double winheight, double fH)
{
	SetPenColor("Red");
	MovePen(winwidth/2-0.5*TextStringWidth("A blood black nothingness began to spin."), winheight/2 + 2*fH);
	DrawTextString("A blood black nothingness began to spin.");
	MovePen(winwidth/2-0.5*TextStringWidth("It's getting darker!"), winheight/2);
	DrawTextString("It's getting darker!");
	SetPenColor("Black");
	MovePen(winwidth/2-0.5*TextStringWidth("A blood black nothingness began to spin."), winheight/2 + 2*fH);
	DrawTextString("             black");
	SetPenColor("Blue");
	MovePen(winwidth/2-0.5*TextStringWidth("Press any direction key to continue"), winheight/3);
	DrawTextString("Press any direction key to continue");
}

void WriteAdventure6(double winwidth, double winheight, double fH)
{
	SetPenColor("Orange");
	MovePen(winwidth/2-0.5*TextStringWidth("I knew it!"), winheight/2 + 4*fH);
	DrawTextString("I knew it!");
	MovePen(winwidth/2-0.5*TextStringWidth("Things can only become darker!!!"), winheight/2 + 2*fH);
	DrawTextString("Things can only become darker!!!");
	MovePen(winwidth/2-0.5*TextStringWidth("But..."), winheight/2);
	DrawTextString("But...");
	MovePen(winwidth/2-0.5*TextStringWidth("Changes seem to take place on my body..."), winheight/2 - 2*fH);
	DrawTextString("Changes seem to take place on my body...");
	MovePen(winwidth/2-0.5*TextStringWidth("Fight on...Fight on...Fight on..."), winheight/2 - 4*fH);
	DrawTextString("Fight on...Fight on...Fight on...");
	SetPenColor("Blue");
	MovePen(winwidth/2-0.5*TextStringWidth("Press any direction key to continue"), winheight/3);
	DrawTextString("Press any direction key to continue");
}

void WriteAdventure7(double winwidth, double winheight, double fH)
{
	SetPenColor("Orange");
	MovePen(winwidth/2-0.5*TextStringWidth("What's it like to hold your child in your arms? Interlinked."), winheight/2 + 6*fH);
	DrawTextString("What's it like to hold your child in your arms? Interlinked.");
	MovePen(winwidth/2-0.5*TextStringWidth("What's it like to play with your dog? Interlinked."), winheight/2 + 4*fH);
	DrawTextString("What's it like to play with your dog? Interlinked.");
	MovePen(winwidth/2-0.5*TextStringWidth("Do you feel that there's a part of you that's missing? Interlinked."), winheight/2 + 2*fH);
	DrawTextString("Do you feel that there's a part of you that's missing? Interlinked.");
	MovePen(winwidth/2-0.5*TextStringWidth("Do you like to connect to things? Interlinked."), winheight/2);
	DrawTextString("Do you like to connect to things? Interlinked.");
	MovePen(winwidth/2-0.5*TextStringWidth("What happens when that linkage is broken? Interlinked."), winheight/2 - 2*fH);
	DrawTextString("What happens when that linkage is broken? Interlinked.");
	MovePen(winwidth/2-0.5*TextStringWidth("Have they let you feel heartbreak? Interlinked."), winheight/2 - 4*fH);
	DrawTextString("Have they let you feel heartbreak? Interlinked.");
	MovePen(winwidth/2, winheight/2 - 6*fH);
	DrawTextString("from <<Blade Runner 2049>>");
	SetPenColor("Black");
	MovePen(winwidth/2-0.5*TextStringWidth("You have arrived at the darkest moment."), winheight/3);
	DrawTextString("You have arrived at the darkest moment.");
	SetPenColor("Blue");
	MovePen(winwidth/2-0.5*TextStringWidth("Press any direction key to continue"), winheight/3 - 2*fH);
	DrawTextString("Press any direction key to continue");
}

void WriteAdventure8(double winwidth, double winheight, double fH)
{
	SetPenColor("Red");
	MovePen(winwidth/2-0.5*TextStringWidth("Love is blind."), winheight/2 + 6*fH);
	DrawTextString("Love is blind.");
	SetPenColor("Orange");
	MovePen(winwidth/2-0.5*TextStringWidth("I will fight on even if I lose my sight."), winheight/2 + 4*fH);
	DrawTextString("I will fight on even if I lose my sight.");
	
	SetPenColor("Blue");
	MovePen(winwidth/2-0.5*TextStringWidth("Press any direction key to continue"), winheight/3);
	DrawTextString("Press any direction key to continue");
}

void WriteAdventure9(double winwidth, double winheight, double fH)
{
	SetPenColor("Orange");
	MovePen(winwidth/2-0.5*TextStringWidth("What..."), winheight/2 + 6*fH);
	DrawTextString("What...");
	MovePen(winwidth/2-0.5*TextStringWidth("This is..."), winheight/2 + 4*fH);
	DrawTextString("This is...");
	SetPenColor("Blue");
	MovePen(winwidth/2-0.5*TextStringWidth("Press any direction key to continue"), winheight/3);
	DrawTextString("Press any direction key to continue");
}
