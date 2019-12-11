#ifndef C_02_2_H
#define C_02_2_H

#define PRODUCT_LIST_SIZE 20

struct product {
    int factor;
    int nounExp;
    int verbExp;
};

enum variable {
    noun, verb
};

void run02_2();
void runProgramFromProductList(struct product productList[][PRODUCT_LIST_SIZE]);
void executeAdd(int pc, struct product productList[][PRODUCT_LIST_SIZE]);
void addProducts(struct product dest[PRODUCT_LIST_SIZE], struct product add[PRODUCT_LIST_SIZE]);
void executeMultiply(int pc, struct product productList[][PRODUCT_LIST_SIZE]);
void printPolynom(struct product polynom[PRODUCT_LIST_SIZE]);
void printVariable(enum variable var, int value);
int solveEquivalence(struct product productList[][PRODUCT_LIST_SIZE], int right, enum variable var, int value);

#endif
