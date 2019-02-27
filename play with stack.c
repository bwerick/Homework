#include <stdio.h>
#include <stdlib.h>
#include <limits.h>


//make a Stack struct
struct Stack{
	int top; //the top index of stack
	unsigned capacity; //how many spaces allowed in stack
	int* array; //int array
};



//make a Stack of a specified capacity, stack is initialized as 0
struct Stack* makeStack(unsigned capacity1) {
	struct Stack* stk = (struct Stack*) malloc(sizeof(struct Stack)); //allocates memory for stack "object"
	stk->capacity = capacity1;
	stk->top = -1; //initializes top 
	stk->array = (int*)malloc(stk->capacity * sizeof(int)); //allocates space for the array acting as stack "objects" witht the spaces indicated
	return stk;
}

//stack is full when top is equal to capacity index
int isFull(struct Stack* stk) {
	return stk->top == stk->capacity - 1;
}

//stack is epmty when equal to -1
int isEmpty(struct Stack* stk) {
	return stk->top == -1;
}
//adds item to the stack inreases top by 1
void push(struct Stack* stk, int item) {
	if (isFull(stk)) {
		return;
	}
	stk->array[++stk->top] = item;
	printf("%d pushed to stack\n", item);
}

//removes item from stack decreases top by 1
int pop(struct Stack* stk) {

	if (isEmpty(stk)) {
		return INT_MIN;
	}
	return stk->array[stk->top--];

}






int main() {
	int cpc=0; //hoow many items will be entered
	int input=0; //holds input for stack

	printf("How many items? Please enter a positive number.\n");
	scanf("%d", &cpc); //input of intem number
	struct Stack* stk = makeStack(cpc); //creates stack the saize of the item numbers

	for (int i=0; i < cpc; i++) { //loop that intakes the user input
		printf("Please enter item #%d ", i + 1);
		scanf("%d", &input);
		push(stk, input); //adds to stack
	}
	printf("--------LAST ITEM ENTERED--------\n"); 
	printf("\nThis is your reversed array:\n");

	for (int i = 0; i < cpc; i++) {
		printf("[%d] ", pop(stk)); //printsout the numbers entered in reverse order entered
	}

	printf("\n\n---------------------------------");
	
	return 0;
}