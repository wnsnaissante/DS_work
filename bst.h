#ifndef bst_h
#define bst_h

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct Stack{
	int top;
	char** data;
}Stack;

typedef struct Node {
	char* data;
	int typeOfData;
	struct Node* lChild;
	struct Node* rChild;
}Node;

typedef struct NodeStack {
	int top;
	Node** node;
}NodeStack;

Node* GetNewNode(char* data);

char* TopStack(Stack* stack);
char* PopStack(Stack* stack);

int CheckValidateExpression(char* expression);
char* CorrectExpression(char* expression);
Stack* ParseExpression(char* expression);
Stack* InfixToPostfix(Stack* input);
Node* MakeExpressionTree(Stack* postfixExpressionStack);
Node* MakeExpressionTreeFromInfix(Stack* infixExpressionStack);

#endif