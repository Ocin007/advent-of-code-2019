#include <stdio.h>
#include <zconf.h>
#include <stdlib.h>
#include "02.h"

void run02() {
    printf("Run advent of code day 2\n");
    int i, j;
    int stmtList[145];

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

    stmtList[1] = 12;
    stmtList[2] = 2;
    runProgram(stmtList);
    printf("Result (position 0) is: %d\n", stmtList[0]);
    printf("Done!\n");
}

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

/**
 * executes the program "stmtList"
 * @param stmtList the program as int array
 */
void runProgram(int stmtList[]) {
    int pc = 0;
    while(execOpCode(pc, stmtList)) {
        pc+=4;
    }
}

/**
 * executes opcode in "stmtList" at position "pc"
 * @param pc the program counter
 * @param stmtList the program as int array
 * @return
 *  1: opcode executed successfully,
 *  0: opcode 99, program terminated,
 * -1: unknown opcode
 */
int execOpCode(int pc, int stmtList[]) {
    switch(stmtList[pc]) {
        case 1:
            stmtList[stmtList[pc+3]] = stmtList[stmtList[pc+1]] + stmtList[stmtList[pc+2]];
            break;
        case 2:
            stmtList[stmtList[pc+3]] = stmtList[stmtList[pc+1]] * stmtList[stmtList[pc+2]];
            break;
        case 99:
            return 0;
        default:
            return -1;
    }
    return 1;
}