#ifndef __TERMINAL_H__
#define __TERMINAL_H__
#define FONT_COLOR_HGHLIGHT 1
#define FONT_COLOR_ERROR 2
#define FONT_COLOR_DEFAULT 0
int getch();
void gotoxy(int x, int y);
void clrscr();
void clrline();
void getscreensize(int& width, int& height);
void setfontcolor(int color);
#endif // __TERMINAL_H__