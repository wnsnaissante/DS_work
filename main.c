#include "bst.h"
#include "calc.h"


//!TODO : 메모리 누수 고치기 || 못 고칠듯
//!TODO : 파싱함수, 파싱된수식으로 포스트픽스 만드는거 없애고 바로 인픽스에서 트리만드는거로 수정하기
//!TODO : 전처리 함수들 하나로 묶기
void main(void) {
	char expression[10001];
	while (1) {
		printf(">> ");
		if (scanf("%[^\n]s", expression) == 0) {
			printf("종료됨");
			break;
		} getchar();
		if (strlen(expression) != 0)
		{
			char* correctExpression = (char*)malloc(sizeof(char) * 1001);
			correctExpression = CorrectExpression(expression);
			if (CheckValidateExpression(correctExpression) == 1)
			{
				Stack* stack = ParseExpression(correctExpression);
				stack = InfixToPostfix(stack);
				Node* root = MakeExpressionTree(stack);
				//Node* root = MakeExpressionTreeFromInfix(stack);
				if (ExecuteOperation(root)[0] == 'M')
				{
					printf("Modulo by zero\n");
				}
				else if (ExecuteOperation(root)[0] == 'D')
				{
					printf("Division by zero\n");
				}
				else if (ExecuteOperation(root)[0] == 'Z') {
					printf("Zero to the power of zero\n");
				}
				else
				{
					printf("result: %s\n", ExecuteOperation(root));
				}
			}
			else {
				printf("Input error\n");
			}
			free(correctExpression);
		}
		else {
			printf("종료됨\n");
			break;
		}

	}

}
