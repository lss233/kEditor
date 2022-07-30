#include "list.hpp"
#include "line.hpp"
#include "terminal.hpp"
#include "activezone.hpp"

#include <cstring>
#include <cstdio>
#include <iostream>
using namespace std;

struct Cursor
{
    int x;
    int y;
} cursor;

void quit()
{
    exit(0);
}
int checkLineNumberActiveZone(ActiveZone &zone, int lineNumber)
{
    int w, h;
    getscreensize(w, h);

    int relevantNumber = lineNumber - zone.firstRow;

    if (relevantNumber <= 0)
    {
        gotoxy(0, h - 1);
        clrline();
        setfontcolor(FONT_COLOR_ERROR);
        cout << "   ! 错误：行号不能小于 1。" << endl;
        setfontcolor(FONT_COLOR_DEFAULT);
        cout << "   ! 按任意键继续……";
        getch();
        return -1;
    }
    else if (relevantNumber > h - zone.makeup)
    {
        gotoxy(0, h - 1);
        clrline();
        setfontcolor(FONT_COLOR_ERROR);
        cout << "   ! 错误：行号不能超过当前活区。" << endl;
        setfontcolor(FONT_COLOR_DEFAULT);
        cout << "   ! 按任意键继续……";
        getch();
        return 1;
    }
    return 0;
}
void InsertNewLine(ActiveZone &zone)
{
    int w, h;
    getscreensize(w, h);

    int lineNumber;
    cout << "请输入行号：";
    scanf("%d", &lineNumber);

    gotoxy(0, h - 1);
    clrline();
    fflush(stdin);

    if (checkLineNumberActiveZone(zone, lineNumber) != 0)
        return;
    int relevantNumber = lineNumber - zone.firstRow;

    cout << lineNumber << " 请输入内容：" << endl;
    LineBlockList LB;
    InitLinklist(LB);
    InsertLinklist(zone.lines, relevantNumber, LB);
    ReadLine(LB, stdin);
    ReadLine(LB, stdin);
}
void DeleteLine(ActiveZone &zone)
{
    int lineNumberBegin, lineNumberEnd;
    cout << "请输入起始行号：";
    scanf("%d", &lineNumberBegin);

    cout << "请输入结束行号：";
    scanf("%d", &lineNumberEnd);

    if (checkLineNumberActiveZone(zone, lineNumberBegin) != 0)
        return;
    if (checkLineNumberActiveZone(zone, lineNumberEnd) != 0)
        return;
    int relevantNumber = lineNumberBegin - zone.firstRow + 1;
    for (int i = lineNumberBegin; i <= lineNumberEnd; i++)
    {
        LineBlockList waste;
        DelLinklist(zone.lines, relevantNumber, waste);
    }
}
void EditActiveZone(ActiveZone &zone)
{
    int w, h;
    int ch;
    cursor.x = 6, cursor.y = 0;
    while (true)
    {
        getscreensize(w, h);
        gotoxy(cursor.x, cursor.y);
        ch = getch();
        if (ch >= -40 && ch <= -37)
        {
            switch (ch)
            {
            case -38:
                cursor.y--;
                // Cursor up
                break;
            case -40:
                cursor.y++;
                // Cursor down
                break;
            case -37:
                cursor.x--;
                // Cursor left
                break;
            case -39:
                cursor.x++;
                // Cursor right
                break;
            }
            if (cursor.y < 0)
                cursor.y = 0;
            if (cursor.y > h - 2)
                cursor.y = h - 2;
            if (cursor.x < 5)
                cursor.x = 5;
            if (cursor.x > w)
                cursor.x = w;
            gotoxy(cursor.x, cursor.y);
        }
        else if(ch == 27) { // Escape
            return;
        } else {
            RenderActiveZone(zone);
        }
    }
}
void Interactive(ActiveZone &zone)
{
    int w, h;
    getscreensize(w, h);
    gotoxy(0, h - 1);
    setfontcolor(FONT_COLOR_HGHLIGHT);
    cout << "   >";
    setfontcolor(FONT_COLOR_DEFAULT);
    cout << " 请选择：q = 退出,i = 插入行,d = 删除行,n = 活区切换,p = 刷新, e = 编辑模式";
    fflush(stdin);
    switch (getch())
    {
    case 'q':
        quit();
        break;
    case 'i':
        clrline();
        InsertNewLine(zone);
        break;
    case 'd':
        clrline();
        DeleteLine(zone);
        break;
    case 'n':
    {
        // Save ActiveZone
        WriteActiveZone(zone);
        ActiveZone newZone;
        CreateActiveZone(newZone, zone);
        zone = newZone;
        break;
    }

    case 'e':
        EditActiveZone(zone);
        break;
    }
}
void RenderActiveZone(ActiveZone &zone)
{
    clrscr();
    gotoxy(0, 0);
    PrintActiveZone(zone);
}
int main(int argc, const char **argv)
{
    if(argc < 3) {
        cout << argv[0] << " <src_file> <dst_file>" << endl;
        return -1;
    }
    FILE *fp = fopen(argv[1], "r");
    FILE *dstfp = fopen(argv[2], "w");
    ActiveZone zone;
    InitActiveZone(zone, fp, dstfp);
    cursor.x = 0;
    cursor.y = 0;
    while (true)
    {
        RenderActiveZone(zone);
        Interactive(zone);
    }
    return 0;
}
