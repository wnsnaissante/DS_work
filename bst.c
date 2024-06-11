#include "bst.h"

Node* GetNewNode(char* data) {
	Node* temp = (Node*)malloc(sizeof(Node));
	temp->lChild = NULL;
	temp->rChild = NULL;
	temp->data = strdup(data);
	if (data[0] == '+' || data[0] == '-' || data[0] == '*' || data[0] == '/' || data[0] == '%' || data[0] == '^')
	{
		temp->typeOfData = 0;
	}
	else {
		temp->typeOfData = 1;
	}

	return temp;
}

Stack* InitStack() {
	Stack* temp = (Stack*)malloc(sizeof(Stack));
	temp->data = (char**)malloc(sizeof(char*) * 1024);
	temp->top = -1;
	return temp;
}

NodeStack* InitNodeStack() {
	NodeStack* temp = (NodeStack*)malloc(sizeof(NodeStack));
	temp->node = (Node**)malloc(sizeof(Node*) * 1024);
	temp->top = -1;
	return temp;
}

Node* ConvertTokenIntoNode(char* token) {
	Node* temp = (Node*)malloc(sizeof(Node));
	temp->data = strdup(token);
	if (isdigit(token[0]) != 0) {
		temp->typeOfData = 1;
	}
	else {
		temp->typeOfData = 0;
	}
	return temp;
}

void PushNodeStack(NodeStack* stack, Node* node) {
	if (stack->top < 127) {
		stack->top += 1;
		stack->node[stack->top] = node;
	}
}

void PushStack(Stack* stack, char* data) {
	if (stack->top < 127) {
		stack->top += 1;
		stack->data[stack->top] = strdup(data);
	}
}
char* PopStack(Stack* stack) {
	if (stack == NULL || stack->top == -1)
	{
		return NULL;
	}
	else {
		char* str = (stack->data[stack->top]);
		stack->top -= 1;
		return str;
	}
}
Node* PopNodeStack(NodeStack* stack) {
	if (stack == NULL || stack->top == -1)
	{
		return NULL;
	}
	else {
		Node* temp = stack->node[stack->top];
		stack->top -= 1;
		return temp;
	}
}
char* TopStack(Stack* stack) {
	if (stack == NULL || stack->top == -1)
	{
		return NULL;
	}
	else {
		return stack->data[stack->top];
	}
}
int IsStackEmpty(Stack* stack) {
	if (stack->top == -1) {
		return 1;
	}
	else {
		return 0;
	}
}
int IsStackFull(Stack* stack) {
	if (stack->top == 127) {
		return 1;
	}
	else {
		return 0;
	}
}
Stack* ReverseStack(Stack* stack) {
	Stack* tempStack = InitStack();
	while (IsStackEmpty(stack) != 1)
	{
		PushStack(tempStack, PopStack(stack));
	}
	free(stack);
	return tempStack;
}
int GetOperatorPriority(char op) {
	if (op == '+' || op == '-') {
		return 1;
	}
	else if (op == '*' || op == '/' || op == '%') {
		return 2;
	}
	else if (op == '^')
	{
		return 3;
	}
	else if (op == '(' || op==')') {
		return 4;
	}
}
int GetOperatorPriorityInStack(char op) {
	if (op == '(') {
		return 0;
	}
	return GetOperatorPriority(op);
}
int IsOperator(char op) {
	if (op == '+' || op == '-' || op == '*' || op == '/' || op == '%' || op == '^') {
		return 1;
	}
	else {
		return 0;
	}
}
int IsBracket(char op) {
	if (op == '(' || op == ')') {
		return 1;
	}
	else {
		return 0;
	}
}

//!DONE : 괄호 짝 확인
//!DONE : 연산자,숫자,괄호로만 돼있는지 확인
//
//!TODO : 수식 올바른지 확인 | 꼭 해야함
//!TODO: 좀 더 깔끔하게 정리하기 | 안되면말고
int CheckValidateExpression(char* expression) {
	int bracketCount = 0;
	int lengthOfExpression = strlen(expression);
	
	for (int i = 0; i < lengthOfExpression; i++) {
		if (expression[i] == '(') {
			bracketCount += 1;
		}
		else if (expression[i] == ')') {
			bracketCount -= 1;
		}
	}
	if (bracketCount != 0)
	{
		return 0;
	}

	for (int i = 0; i < lengthOfExpression; i++)
	{
		if ((IsOperator(expression[i]) || isdigit(expression[i]) || IsBracket(expression[i])) != 1)
		{
			return 0;
		}
	}
	return 1;
}


//! DONE : 공백제거
//! DONE : 음수 처리 / 맨 첨 '-' 앞, 괄호뒤 0 넣기
char* CorrectExpression(char* expression) {
	size_t len = strlen(expression);
	int index = 0;
	char* newExpression = (char*)malloc(sizeof(char)*1024);

	if (expression[0] == '-')
	{
		newExpression[0] = '0';
		index += 1;
	}
	
	for (int i = 0; i < len; i++) {
		if (expression[i] != ' ') {
			newExpression[index] = expression[i];
			index += 1;
			if (expression[i] == '(') {
				if (i + 1 < len && expression[i + 1] == '-') {
					newExpression[index] = '0';
					index += 1;
				}
			}
		}
	}
	newExpression[index] = '\0';
	return newExpression;
}

Stack* ParseExpression(char* expression) {
	char temp[1024];
	Stack* parsedExpressionStack = InitStack();
	int currentIndex = 0;
	int tempIndex = 0;
	while (currentIndex < strlen(expression))
	{
		if (IsOperator(expression[currentIndex])== 1)
		{
			temp[0] = expression[currentIndex];
			temp[1] = '\0';
			currentIndex += 1;
			PushStack(parsedExpressionStack, temp);
		}
		else if (IsBracket(expression[currentIndex]) ==1)
		{
			temp[0] = expression[currentIndex];
			temp[1] = '\0';
			currentIndex += 1;
			PushStack(parsedExpressionStack, temp);
		}
		else {
			while ((currentIndex< strlen(expression))&&isdigit(expression[currentIndex])) {
				temp[tempIndex++] = expression[currentIndex++];
			}
			temp[tempIndex] = '\0';
			PushStack(parsedExpressionStack, temp);
			tempIndex = 0;
		}
	}
	return parsedExpressionStack;
}

Stack* InfixToPostfix(Stack* inputParsedExpressionStack) {
	Stack* ExpressionStack = inputParsedExpressionStack;

	ExpressionStack = ReverseStack(ExpressionStack);

	Stack* tempStack = InitStack();

	Stack* resultStack = InitStack();
	while (IsStackEmpty(ExpressionStack) != 1)
	{
		char* currentToken = PopStack(ExpressionStack);
		if (isdigit(currentToken[0]) != 0) {
			PushStack(resultStack, currentToken);
		}
		else if (IsOperator(currentToken[0]) == 1)
		{
			if (IsStackEmpty(tempStack) == 1) {
				PushStack(tempStack, currentToken);
			}
			else {
				if (GetOperatorPriorityInStack(TopStack(tempStack)[0]) >= GetOperatorPriority(currentToken[0])) {
					while (IsStackEmpty(tempStack) != 1 && (GetOperatorPriorityInStack(TopStack(tempStack)[0]) >= GetOperatorPriority(currentToken[0]))) {
						PushStack(resultStack, PopStack(tempStack));
					}
				}
				PushStack(tempStack, currentToken);
			}
		}
		else if ((currentToken[0]) == '(')
		{
			PushStack(tempStack, currentToken);
		}
		else if ((currentToken[0]) == ')')
		{
			while (IsStackEmpty(tempStack) != 1 && TopStack(tempStack)[0] != '(') {
				PushStack(resultStack, PopStack(tempStack));
			}
			if (IsStackEmpty(tempStack) != 1 && TopStack(tempStack)[0] == '(') {
				PopStack(tempStack);
			}
		}
	}
	while (IsStackEmpty(tempStack) != 1)
	{
		PushStack(resultStack, PopStack(tempStack));
	}
	resultStack = ReverseStack(resultStack);
	return resultStack;
}	  

Node* MakeExpressionTree(Stack* postfixExpressionStack) {
	NodeStack* postfixExpressionNodeStack = InitNodeStack();
	while (IsStackEmpty(postfixExpressionStack) != 1)
	{
		Node* currentTokenNode = ConvertTokenIntoNode(PopStack(postfixExpressionStack));
		if (currentTokenNode->typeOfData == 1) {
			PushNodeStack(postfixExpressionNodeStack, currentTokenNode);
		}
		else
		{
			Node* tempRChild = PopNodeStack(postfixExpressionNodeStack);
			Node* tempLChild = PopNodeStack(postfixExpressionNodeStack);
			currentTokenNode->rChild = tempRChild;
			currentTokenNode->lChild = tempLChild;
			PushNodeStack(postfixExpressionNodeStack, currentTokenNode);
			
		}
	}
	return PopNodeStack(postfixExpressionNodeStack);
}