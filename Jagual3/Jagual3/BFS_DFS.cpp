#include <iostream>
#include <queue>
#include "Graph.h"
using namespace std;

void Graph::BFS( Node* pStartNode)
{
	//ÃÊ±âÈ­
	for (auto& node : nodeList)
		node->checked = false;

	queue<Node*> que;
	que.push(pStartNode);
	pStartNode->checked = true;

	Node* curNode = nullptr;
	while (que.empty() == false)
	{
		curNode = que.front();
		que.pop();
		printf("%d ", curNode->value);
	
		for (auto& neighbor : curNode->neighbors)
		{
			if (neighbor->checked == false)
			{
				que.push(neighbor);
				neighbor->checked = true;
			}
		}
	}
	printf("\n");
}
