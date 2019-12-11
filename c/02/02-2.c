#include <stdio.h>
#include "02-2.h"
#include "02.h"
#include "02helper.h"

void run02_2() {
    printf("Run advent of code day 2 (part 2)\n");
    int stmtList[145];
    struct product productList[145][PRODUCT_LIST_SIZE];
    getInput(stmtList);

    stmtList[1] = 12;
    stmtList[2] = 2;

    for (int i = 0; i < 145; ++i) {
        struct product constant = {stmtList[i], 0, 0};
        productList[i][0] = constant;
    }
    runProgramFromProductList(productList);
    printPolynom(productList[0]);
    printf("Done!\n");
}

void runProgramFromProductList(struct product productList[][PRODUCT_LIST_SIZE]) {
    int pc = 0;
    int opcode = 0;
    while(opcode != 99) {
        opcode = productList[pc][0].factor;
        switch(opcode) {
            case 1:
                executeAdd(pc, productList);
                break;
            case 2:
                executeMultiply(pc, productList);
                break;
            default:
                break;
        }
        pc+=4;
    }
}

void executeAdd(int pc, struct product productList[][PRODUCT_LIST_SIZE]) {
    //position in program memory
    int add1, add2, dest, i;
    add1 = productList[pc+1][0].factor;
    add2 = productList[pc+2][0].factor;
    dest = productList[pc+3][0].factor;
    if(
            productList[pc+1][0].nounExp != 0 ||
            productList[pc+2][0].nounExp != 0 ||
            productList[pc+3][0].nounExp != 0 ||
            productList[pc+1][0].verbExp != 0 ||
            productList[pc+2][0].verbExp != 0 ||
            productList[pc+3][0].verbExp != 0) {
        printf("Warning: variable as position at pc = %d\n", pc);
    }
    for (i = 0; i < PRODUCT_LIST_SIZE; ++i) {
        if(productList[add1][i].factor != 0) {
            productList[dest][i] = productList[add1][i];
        } else {
            productList[dest][i].factor = 0;
            productList[dest][i].nounExp = 0;
            productList[dest][i].verbExp = 0;
        }
    }
    addProducts(productList[dest], productList[add2]);
}

void addProducts(struct product dest[PRODUCT_LIST_SIZE], struct product add[PRODUCT_LIST_SIZE]) {
    int j, k, addedFlag;
    for (j = 0; j < PRODUCT_LIST_SIZE && add[j].factor != 0; ++j) {
        addedFlag = 0;
        for (k = 0; k < PRODUCT_LIST_SIZE && dest[k].factor != 0; ++k) {
            if(
                    dest[k].nounExp == add[j].nounExp &&
                    dest[k].verbExp == add[j].verbExp) {
                dest[k].factor += add[j].factor;
                addedFlag = 1;
                break;
            }
        }
        if(k >= PRODUCT_LIST_SIZE) {
            printf("Warning: array too small\n");
        } else if(addedFlag == 0) {
            dest[k] = add[j];
        }
    }
}

void executeMultiply(int pc, struct product productList[][PRODUCT_LIST_SIZE]) {
    //position in program memory
    int multi1, multi2, dest;
    multi1 = productList[pc+1][0].factor;
    multi2 = productList[pc+2][0].factor;
    dest = productList[pc+3][0].factor;
    if(
            productList[pc+1][0].nounExp != 0 ||
            productList[pc+2][0].nounExp != 0 ||
            productList[pc+3][0].nounExp != 0 ||
            productList[pc+1][0].verbExp != 0 ||
            productList[pc+2][0].verbExp != 0 ||
            productList[pc+3][0].verbExp != 0) {
        printf("Warning: variable as position at pc = %d\n", pc);
    }
    for (int d = 0; d < PRODUCT_LIST_SIZE; ++d) {
        productList[dest][d].factor = 0;
        productList[dest][d].nounExp = 0;
        productList[dest][d].verbExp = 0;
    }
    for (int i = 0; i < PRODUCT_LIST_SIZE && productList[multi1][i].factor != 0; ++i) {
        for (int j = 0; j < PRODUCT_LIST_SIZE && productList[multi2][j].factor != 0; ++j) {
            struct product product[PRODUCT_LIST_SIZE];
            product[0].factor = productList[multi1][i].factor * productList[multi2][j].factor;
            product[0].nounExp = productList[multi1][i].nounExp + productList[multi2][j].nounExp;
            product[0].verbExp = productList[multi1][i].verbExp + productList[multi2][j].verbExp;
            addProducts(productList[dest], product);
        }
    }
}

void printPolynom(struct product polynom[PRODUCT_LIST_SIZE]) {
    for (int i = 0; i < PRODUCT_LIST_SIZE; ++i) {
        printf("%d", polynom[i].factor);
        printVariable(noun, polynom[i].nounExp);
        printVariable(verb, polynom[i].verbExp);
        if(i < PRODUCT_LIST_SIZE - 1) {
            printf(" + ");
        }
    }
    printf("\n");
}

void printVariable(enum variable var, int value) {
    switch (value) {
        case 0:
            break;
        case 1:
            printf( (var == noun) ? "a" : "b");
            break;
        default:
            printf((var == noun) ? "a%d" : "b%d", value);
    }
}