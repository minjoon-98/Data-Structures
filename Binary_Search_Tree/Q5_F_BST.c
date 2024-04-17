//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section F - Binary Search Trees Questions
Purpose: Implementing the required functions for Question 5
		 Implementing 'remove node' operation for BST*/
//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////////////

typedef struct _bstnode
{
	int item;
	struct _bstnode *left;
	struct _bstnode *right;
} BSTNode; // You should not change the definition of BSTNode

typedef struct _stackNode
{
	BSTNode *data;
	struct _stackNode *next;
} StackNode; // You should not change the definition of StackNode

typedef struct _stack
{
	StackNode *top;
} Stack; // You should not change the definition of Stack

///////////////////////// function prototypes ////////////////////////////////////

// You should not change the prototypes of these functions
void postOrderIterativeS2(BSTNode *root);

void insertBSTNode(BSTNode **node, int value);

void push(Stack *stack, BSTNode *node);
BSTNode *pop(Stack *s);
BSTNode *peek(Stack *s);
int isEmpty(Stack *s);
void removeAll(BSTNode **node);
BSTNode *removeNodeFromTree(BSTNode *root, int value);

///////////////////////////// main() /////////////////////////////////////////////

int main()
{
	int c, i;
	c = 1;

	// Initialize the Binary Search Tree as an empty Binary Search Tree
	BSTNode *root;
	root = NULL;

	printf("1: Insert an integer into the binary search tree;\n");
	printf("2: Print the post-order traversal of the binary search tree;\n");
	printf("0: Quit;\n");

	while (c != 0)
	{
		printf("Please input your choice(1/2/0): ");
		scanf("%d", &c);

		switch (c)
		{
		case 1:
			printf("Input an integer that you want to insert into the Binary Search Tree: ");
			scanf("%d", &i);
			insertBSTNode(&root, i);
			break;
		case 2:
			printf("The resulting post-order traversal of the binary search tree is: ");
			postOrderIterativeS2(root); // You need to code this function
			printf("\n");
			break;
		case 0:
			removeAll(&root);
			break;
		default:
			printf("Choice unknown;\n");
			break;
		}
	}

	return 0;
}

//////////////////////////////////////////////////////////////////////////////////

void postOrderIterativeS2(BSTNode *root)

// 이전 방법과 똑같지만 한번 더 제대로 이해하여 다시 구현함. (feat.이연준의 설명)
// 간단한 방법으로 후위 순회를 구현한 방법.
// 전위순회를 하며 stack1에 넣고, stack1을 팝하여 그 자식들을 대상으로 또 stack1에 넣는다.
// 이런 방법을 사용하면 오른쪽 자식을 다 탐색하며 stack2에 저장하고, 왼쪽 자식을 끝으로 stack2에 저장하게 된다.
// stack2를 pop해가면서 출력하면 후위순회 구현 완료.
{
	if (root == NULL)
		return;

	Stack stack1, stack2;
	stack1.top = NULL;
	stack2.top = NULL;
	BSTNode *current = root;

	push(&stack1, current);
	while (!isEmpty(&stack1))
	{
		current = pop(&stack1);
		push(&stack2, current);
		if (current->left)
		{
			push(&stack1, current->left);
		}
		if (current->right)
		{
			push(&stack1, current->right);
		}
	}
	while (!isEmpty(&stack2))
	{
		current = pop(&stack2);
		printf("%d ", current->item);
	}
}

/* Given a binary search tree and a key, this function
   deletes the key and returns the new root. Make recursive function. */
/*
BSTNode *removeNodeFromTree(BSTNode *root, int value)
{
	// 빈 트리인 경우
	if (root == NULL)
		return root;

	// 찾는 값이 현재 노드의 값보다 작은 경우, 왼쪽 서브트리에서 제거를 시도
	if (value < root->item)
	{
		root->left = removeNodeFromTree(root->left, value);
	}
	// 찾는 값이 현재 노드의 값보다 큰 경우, 오른쪽 서브트리에서 제거를 시도
	else if (value > root->item)
	{
		root->right = removeNodeFromTree(root->right, value);
	}
	else // 현재 노드가 제거할 노드인 경우
	{
		// Case 1: 자식이 없는 경우 또는 한 개의 자식만 있는 경우
		if (root->left == NULL)
		{
			BSTNode *temp = root->right;
			free(root);
			return temp;
		}
		else if (root->right == NULL)
		{
			BSTNode *temp = root->left;
			free(root);
			return temp;
		}

		// Case 2: 두 개의 자식이 모두 있는 경우
		// 오른쪽 서브트리에서 가장 작은 값을 가진 노드를 찾음
		BSTNode *temp = root->right;
		while (temp->left != NULL)
		{
			temp = temp->left;
		}

		// 가장 작은 값을 가진 노드의 값을 현재 노드로 복사
		root->item = temp->item;

		// 오른쪽 서브트리에서 가장 작은 값을 가진 노드를 제거
		root->right = removeNodeFromTree(root->right, temp->item);
	}
	return root;
}
*/
///////////////////////////////////////////////////////////////////////////////

void insertBSTNode(BSTNode **node, int value)
{
	if (*node == NULL)
	{
		*node = malloc(sizeof(BSTNode));

		if (*node != NULL)
		{
			(*node)->item = value;
			(*node)->left = NULL;
			(*node)->right = NULL;
		}
	}
	else
	{
		if (value < (*node)->item)
		{
			insertBSTNode(&((*node)->left), value);
		}
		else if (value > (*node)->item)
		{
			insertBSTNode(&((*node)->right), value);
		}
		else
			return;
	}
}

//////////////////////////////////////////////////////////////////////////////////

void push(Stack *stack, BSTNode *node)
{
	StackNode *temp;

	temp = malloc(sizeof(StackNode));

	if (temp == NULL)
		return;
	temp->data = node;

	if (stack->top == NULL)
	{
		stack->top = temp;
		temp->next = NULL;
	}
	else
	{
		temp->next = stack->top;
		stack->top = temp;
	}
}

BSTNode *pop(Stack *s)
{
	StackNode *temp, *t;
	BSTNode *ptr;
	ptr = NULL;

	t = s->top;
	if (t != NULL)
	{
		temp = t->next;
		ptr = t->data;

		s->top = temp;
		free(t);
		t = NULL;
	}

	return ptr;
}

BSTNode *peek(Stack *s)
{
	StackNode *temp;
	temp = s->top;
	if (temp != NULL)
		return temp->data;
	else
		return NULL;
}

int isEmpty(Stack *s)
{
	if (s->top == NULL)
		return 1;
	else
		return 0;
}

void removeAll(BSTNode **node)
{
	if (*node != NULL)
	{
		removeAll(&((*node)->left));
		removeAll(&((*node)->right));
		free(*node);
		*node = NULL;
	}
}
