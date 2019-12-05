#include <stdio.h>
#include <zconf.h>
#include <stdlib.h>
#include "02.h"
#include "02helper.h"

void run02() {
    printf("Run advent of code day 2 (part 1)\n");
    int stmtList[145];
    getInput(stmtList);

    stmtList[1] = 12;
    stmtList[2] = 2;
    runProgram(stmtList);
    printf("Result (position 0) is: %d\n", stmtList[0]);
    printf("Done!\n");
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