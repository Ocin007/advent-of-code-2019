#include <stdlib.h>
#include <zconf.h>
#include <stdio.h>
#include "02helper.h"

/**
 * writes src (e.g. 1,2,3,10,5,...) into dest
 * @param src
 * @param sizeSrc
 * @param dest
 */
void writeToIntArray(char *src, int sizeSrc, int *dest) {
    char helper[4];
    int h = 0, d = 0;
    for (int i = 0; i < sizeSrc; ++i) {
        if(src[i] != ',' && src[i] != '\0') {
            helper[h] = src[i];
            h++;
        } else {
            helper[h] = '\0';
            dest[d] = atoi(helper);
            h = 0;
            d++;
        }
    }
}

void getInput(int stmtList[]) {
    int i, j;

    //create path to input file
    char currentDirPath[PATH_MAX];
    getcwd(currentDirPath, sizeof(currentDirPath));
    char inputPath[] = "\\..\\..\\input\\02\\input.txt";
    for(i=0; currentDirPath[i] != '\0'; i++) {}
    for(j=0; j < 26 && i < PATH_MAX; j++) {
        currentDirPath[i] = inputPath[j];
        i++;
    }

    //read input file, prepare the program as int[]
    FILE *inputfile = fopen(currentDirPath, "r");
    char fileContent[381];
    fgets(fileContent, 381, inputfile);
    fclose(inputfile);
    writeToIntArray(fileContent, 381, stmtList);
}