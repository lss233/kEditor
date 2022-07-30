#include "activezone.hpp"
#include "terminal.hpp"
#include<iostream>
using namespace std;

int InitActiveZone(ActiveZone& zone, FILE *fp, FILE * dstfp) {
    zone.fp = fp;
    zone.dstfp = dstfp;
    zone.firstRow = 1;
    zone.dirty = false;
    zone.makeup = 0;
    zone.lastRow = ACTIVEZONE_MAX_LEN;
    // fseek(fp, position);
    InitLinklist(zone.lines);
    for (int lineNumber = 0; lineNumber < ACTIVEZONE_MAX_LEN; lineNumber++)
    {
        if(feof(fp)) break;

        LineBlockList LB;
        InitLinklist(LB);
        CreateLinklist(zone.lines, LB);
        ReadLine(LB, fp);
    }
}
int CreateActiveZone(ActiveZone& zone, ActiveZone& oldZone) {
    zone.fp = oldZone.fp;
    zone.dstfp = oldZone.dstfp;
    zone.firstRow = oldZone.lastRow - ACTIVEZONE_KEEP_PREVIOUS_LINE;
    zone.dirty = false;
    zone.makeup = 0;
    zone.lastRow = ACTIVEZONE_MAX_LEN;
    InitLinklist(zone.lines);

    // First, copy from oldZone    
    int idx = oldZone.firstRow;
    Line * p = oldZone.lines;
    while(p->next && idx < zone.firstRow) {
        idx++;
        p = p->next;
    }
    while(p->next) {
        p = p->next;
        CreateLinklist(zone.lines, p->data);
    }
    // Read the rest from file
    for (int lineNumber = CountLinklist(zone.lines); lineNumber < ACTIVEZONE_MAX_LEN; lineNumber++)
    {
        if(feof(zone.fp)) break;

        LineBlockList LB;
        InitLinklist(LB);
        CreateLinklist(zone.lines, LB);
        ReadLine(LB, zone.fp);
    }
}

int PrintActiveZone(ActiveZone& zone) {
    int w, h;
    getscreensize(w, h);
    Line * p = zone.lines;
    int i = 0;
    int makeup = 2; // 算上保留位
    while(p->next) {
        p = p->next;
        LineBlock * lb = p->data;
        if(lb == NULL) break;

        setfontcolor(FONT_COLOR_HGHLIGHT);
        printf("%4d ", zone.firstRow + i++);
        setfontcolor(FONT_COLOR_DEFAULT);
        
        int charlen = 5; // 算上行号 + 空格
        while(lb->next){
            lb = lb->next;
            int currentlen = strlen(lb->data);
            if(i + makeup + (charlen + currentlen) / w > h) { // 如果输出了当前块，就会溢出窗口
                printf ("%.*s", w - charlen - 2, lb->data);
                setfontcolor(FONT_COLOR_ERROR);
                printf("..");
                setfontcolor(FONT_COLOR_DEFAULT);
                break;
            } else {
                charlen += currentlen;
                printf("%s", lb->data);
                fflush(stdout);
            }
            
        }
        cout << endl;
        makeup += charlen / w;
        setfontcolor(FONT_COLOR_DEFAULT);
        if(i + makeup >= h) {
            break;
        }
    }
    zone.makeup = makeup;
    zone.lastRow = i + zone.firstRow - 1;
    return 0;
}

int WriteActiveZone(ActiveZone& zone) {
    // PrintActiveZone(zone); // Makes sure we have the latest lastRow
    fflush(stdout);

    int w, h;
    getscreensize(w, h);

    Line * p = zone.lines;
    /*
    while(p->next) {
        p = p->next;
    }

    */

    int writeLine = zone.lastRow - zone.firstRow - ACTIVEZONE_KEEP_PREVIOUS_LINE;
    while(p->next) {
        p = p->next;
        LineBlock * LB = p->data;
        while(LB->next) {
            LB = LB->next;
            fprintf(zone.dstfp, "%s", LB->data);
        }
        fprintf(zone.dstfp, "\n");
        fflush(zone.dstfp);
        if(--writeLine <= 0) {
            break;
        }
    }
}