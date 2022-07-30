#ifndef __LINE_H__
#define __LINE_H__
#include <cstdio>
#include "list.hpp"
const int STANDARD_LINE_BLOCK_CHAR_LEN = 81;
typedef char* Characters;
typedef struct LNode<Characters> LineBlock, * LineBlockList;
typedef struct LNode<LineBlockList> Line, * LineList;
void ReadLine(LineBlockList LB, FILE *fp);
#endif // __LINE_H__