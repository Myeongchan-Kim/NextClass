#include <iostream>
#include <vector>
#include <cstdio>
#include <algorithm>
#include <string>

int N, K;
std::string move;
struct Node
{
	int x;
	int y;
	Node* a;
	Node* b;
	Node* c;
	Node* d;
};

std::vector<Node*> nodelist;
Node nodePool[100002] = {0,};
Node NIL;

void problem_input()
{

	std::cin >> N >> K >> move;
	for(int i = 0; i < N ; i++)
	{
		std::cin >> nodePool[i].x >> nodePool[i].y;
		nodePool[i].a = &NIL;
		nodePool[i].b = &NIL;
		nodePool[i].c = &NIL;
		nodePool[i].d = &NIL;
		nodelist.push_back(&nodePool[i]);
	}
}

bool cmp1(const Node* n1, const Node* n2)
{
	int n1XY = n1->x+n1->y;
	int n2XY = n2->x+n2->y;
	if(n1XY == n2XY)
		return n1->x > n2->x;
	else
		return n1XY > n2XY;
}

bool cmp2(const Node* n1, const Node* n2)
{
	int n1XY = n1->x-n1->y;
	int n2XY = n2->x-n2->y;
	if(n1XY == n2XY)
		return n1->x > n2->x;
	else
		return n1XY > n2XY;
}

void problem_solev()
{
	std::sort(nodelist.begin(), nodelist.end(), cmp1);

	Node* oldNode = nullptr;
	for( auto& curNode : nodelist)
	{
		if(oldNode != nullptr && oldNode->x + oldNode->y == curNode->x + curNode->y){
			oldNode->c = curNode;
			curNode->b = oldNode;
		}
		oldNode = curNode;
	}

	std::sort(nodelist.begin(), nodelist.end(), cmp2);
	
	oldNode = nullptr;
	for( auto& curNode : nodelist)
	{
		if(oldNode != nullptr && oldNode->x - oldNode->y == curNode->x - curNode->y){
			oldNode->d = curNode;
			curNode->a = oldNode;
		}
		oldNode = curNode;
	}

	Node* curPos = &nodePool[0];
	Node* oldPos = nullptr;
	for(std::string::iterator c = move.begin(); c != move.end(); c++)
	{
		if(*c == 'A' && curPos->a != &NIL)
		{
			Node* next = curPos->a;
			oldPos = curPos;
			
			next->d = oldPos->d;
			
			Node* newC = oldPos->c;
			Node* newB = oldPos->b;
			oldPos->b->c = newC;
			oldPos->c->b = newB;
			
			curPos = next;
		}else if (*c == 'B' && curPos->b != &NIL)
		{
			Node* next = curPos->b;
			oldPos = curPos;
			
			next->c = oldPos->c;
			
			Node* newA = oldPos->a;
			Node* newD = oldPos->d;
			oldPos->d->a = newA;
			oldPos->a->d = newD;
			
			curPos = next;

		}else if (*c == 'C'  && curPos->c != &NIL)
		{
			Node* next = curPos->c;
			oldPos = curPos;
			
			next->b = oldPos->b;
			
			Node* newA = oldPos->a;
			Node* newD = oldPos->d;
			oldPos->d->a = newA;
			oldPos->a->d = newD;
			
			curPos = next;

		}else if (*c == 'D'  && curPos->d != &NIL)
		{
			Node* next = curPos->d;
			oldPos = curPos;
			
			next->a = oldPos->a;
			
			Node* newC = oldPos->c;
			Node* newB = oldPos->b;
			oldPos->b->c = newC;
			oldPos->c->b = newB;
			
			curPos = next;
		}
			
	} 

	printf("%d %d\n", curPos->x, curPos->y);
}

int main ()
{

	NIL.x = -1;
	NIL.y = -1;
	NIL.a = &NIL;
	NIL.b = &NIL;
	NIL.c = &NIL;
	NIL.d = &NIL;

	problem_input();
	problem_solev();
	return 0;
}