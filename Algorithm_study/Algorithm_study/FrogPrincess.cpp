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

void problem_input()
{

	std::cin >> N >> K >> move;
	for(int i = 0; i < N ; i++)
	{
		std::cin >> nodePool[i].x >> nodePool[i].y;
		nodePool[i].a = &nodePool[i];
		nodePool[i].b = &nodePool[i];
		nodePool[i].c = &nodePool[i];
		nodePool[i].d = &nodePool[i];
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
		if(oldNode == nullptr)
		{
			curNode->b = curNode;
		}
		else if(oldNode->x + oldNode->y != curNode->x + curNode->y)
		{
			oldNode->c = oldNode;
			curNode->b = curNode;
		}
		else{
			oldNode->c = curNode;
			curNode->b = oldNode;
		}
		oldNode = curNode;
	}

	std::sort(nodelist.begin(), nodelist.end(), cmp2);
	
	oldNode = nullptr;
	for( auto& curNode : nodelist)
	{
		if(oldNode == nullptr)
		{
			curNode->a = curNode;
		}
		else if(oldNode->x - oldNode->y != curNode->x - curNode->y)
		{
			oldNode->d = oldNode;
			curNode->a = curNode;
		}
		else{
			oldNode->d = curNode;
			curNode->a = oldNode;
		}
		oldNode = curNode;
	}

	Node* curPos = &nodePool[0];
	Node* oldPos = nullptr;
	for(std::string::iterator c = move.begin(); c != move.end(); c++)
	{
		
		if(*c == 'A' && curPos != oldPos)
		{
			oldPos = curPos;
			curPos = oldPos->a;
			
			oldPos->d->a = curPos;
			curPos->d = oldPos->d;
			
			oldPos->b->c = oldPos->c;
			oldPos->c->b = oldPos->b;
		}else if (*c == 'B' && curPos != oldPos)
		{
			oldPos = curPos;
			curPos = oldPos->b;
			
			oldPos->c->b = curPos;
			curPos->c = oldPos->c;
			
			oldPos->d->a = oldPos->a;
			oldPos->a->d = oldPos->d;
		}else if (*c == 'C' && curPos != oldPos)
		{
			oldPos = curPos;
			curPos = oldPos->c;

			oldPos->b->c = curPos;
			curPos->b = oldPos->b;

			oldPos->d->a = oldPos->a;
			oldPos->a->d = oldPos->d;
		}else if (*c == 'D' && curPos != oldPos)
		{
			oldPos = curPos;
			curPos = oldPos->d;
			
			oldPos->a->d = curPos;
			curPos->a = oldPos->a;
			
			oldPos->b->c = oldPos->c;
			oldPos->c->b = oldPos->b;
		}else{
			throw "wrong input";
		}
			
	} 

	printf("%d %d\n", curPos->x, curPos->y);
}

int main ()
{
	problem_input();
	problem_solev();
	return 0;
}