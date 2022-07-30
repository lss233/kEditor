#ifndef __ACTIVEZONE_H__
#define __ACTIVEZONE_H__
#include "line.hpp"
#include <iostream>
const int ACTIVEZONE_MAX_LEN = 100;
const int ACTIVEZONE_KEEP_PREVIOUS_LINE = 2;

typedef struct {
    FILE * fp;
    FILE * dstfp;
    LineList lines;
    int firstRow;
    bool dirty = false;
    int makeup;
    int lastRow;
} ActiveZone;

int InitActiveZone(ActiveZone& zone, FILE * fp, FILE * dstfp);
int CreateActiveZone(ActiveZone& zone, ActiveZone& oldZone);
int PrintActiveZone(ActiveZone& zone);
int WriteActiveZone(ActiveZone& zone);
void RenderActiveZone(ActiveZone& zone);
void EditActiveZone(ActiveZone& zone);
#endif // __ACTIVEZONE_H__