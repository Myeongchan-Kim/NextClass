#include "Graph.h"
#include "main.h"
#include <queue>
#include <vector>

using namespace std;

Graph::Graph()
{
	for (int i = 0; i < 10; i++)
	{
		Graph::Vertex* v1 = new Graph::Vertex;
		v1->value = i;
		insert(v1);
	}
}

Graph::~Graph()
{
	for (auto& vertex : vList)
	{
		for (auto& edge : vertex->outList)
		{
			if (edge != nullptr)
			{
				delete edge;
				edge = nullptr;
			}
		}
		delete vertex;
		vertex = nullptr;
	}
}

void Graph::initVertex()
{
	for (auto& pVtx : vList)
	{
		pVtx->checked = false;
		pVtx->minDist = -1;
	}
}

void Graph::BFS(Vertex* pStartNode)
{
	//ÃÊ±âÈ­
	for (auto& node : vList)
		node->checked = false;

	queue<Vertex*> que;
	que.push(pStartNode);
	pStartNode->checked = true;

	Vertex* curNode = nullptr;
	while (que.empty() == false)
	{
		curNode = que.front();
		que.pop();
		printf("%d ", curNode->id);

		for (auto& edge : curNode->outList)
		{
			auto& neighbor = edge->dest;
			if (neighbor->checked == false)
			{
				que.push(neighbor);
				neighbor->checked = true;
			}
		}
	}
	printf("\n");
}

int Graph::ShortestDist(Vertex* s, Vertex* z)
{
	if (s == z) return 0;
	if (z->minDist != -1) return z->minDist;

	int minResult = INF;
	int result;
	for (auto& edge : z->inList)
	{
		result = edge->weight + ShortestDist(s, edge->source);
		if (minResult > result)
			minResult = result;
	}

	z->minDist = minResult;
	return minResult;
}
