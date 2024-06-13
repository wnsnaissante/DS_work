#include "calc.h"
#include "bst.h"

char* Calculate(char* operandA, char* operandB, char* operator) {
	char* result = (char*)malloc(sizeof(char) * 1024);
	int tempA = strtol(operandA, NULL, 13);
	int tempB = strtol(operandB, NULL, 13);
	if (operator[0] =='+')
	{
		sprintf(result, "%d", tempA + tempB);
	}
	else if (operator[0] =='-') {
		sprintf(result, "%d", tempA - tempB);
	}
	else if (operator[0] =='*') {
		sprintf(result, "%d", tempA * tempB);
	}
	else if (operator[0] =='/') {
		if (tempB == 0)
		{
			return "D"; // Division by zero
		}
		sprintf(result, "%d", (tempA / tempB));
	}
	else if (operator[0] =='%') {
		if (tempB == 0)
		{
			return "M"; // Modulo by zero
		}
		sprintf(result, "%d", tempA % tempB);
	}
	else if (operator[0] =='^') {
		if (tempA == 0 && tempB == 0)
		{
			return "Z"; // Zero to the power of zero
		}
		sprintf(result, "%d", (int)pow(tempA,tempB));
	}

	strcat(result, "\0");
	return result;
}

char* ExecuteOperation(Node* node) {
	if (node==NULL)
	{
		return NULL;
	}
	if (node->typeOfData == 1)
	{
		return node->data;
	}
	if (node->lChild == NULL && node->rChild == NULL)
	{
		return node->data;
	}

	char* left = ExecuteOperation(node->lChild);
	char* right = ExecuteOperation(node->rChild);

	return Calculate(left, right, node->data);
}