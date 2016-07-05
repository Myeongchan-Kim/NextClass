#pragma once
#include <vector>
using namespace std;

/*BFS DFS*/
struct Node
{
	int value;
	bool checked = false;
	vector<Node*> neighbors;

	bool isNeighbor(Node * pNode)
	{
		for (auto neighbor : neighbors)
			if (pNode == neighbor)
				return true;
		return false;
	}

	void connect(Node* pNode) //단방향 연결
	{
		if (isNeighbor(pNode))
			return;

		neighbors.push_back(pNode);
	}
};

struct Graph
{
	vector<Node*> nodeList;
	void insert(Node* pNode)
	{
		nodeList.push_back(pNode);
	}


	void BFS(Node* pStartNode);
};


/*shortest Distance*/
struct Edge
{
	int weight;
	Vertex* source;
	Vertex* dest;
};

struct Vertex
{
	int minDist;
	vector<Edge*> outList;
	vector<Edge*> inList;
};

int ShortestDist(Vertex* s, Vertex* z);
