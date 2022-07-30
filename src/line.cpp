#include "line.hpp"
#include <cstring>
#include <cstdio>
void ReadLine(LineBlockList LB, FILE *fp)
{
    char *newLine;
    char *buffer;
    bool exhaustedLine = false;
    do
    {
        buffer = new char[STANDARD_LINE_BLOCK_CHAR_LEN];
        fgets(buffer, STANDARD_LINE_BLOCK_CHAR_LEN - 1, fp);
        CreateLinklist(LB, buffer);

        if ((newLine = strchr(buffer, '\n')) != NULL)
        {
            *newLine = 0;
        }
    } while (newLine == NULL && !feof(fp));
}