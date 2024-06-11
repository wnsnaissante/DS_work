#ifndef calc_h
#define calc_h
#include <stdlib.h> 
#include <stdio.h>
#include <math.h>
#include "bst.h"

char* Calculate(char* operandA, char* operandB, char* operator);
char* ExecuteOperation(Node* node);


#endif