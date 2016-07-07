#pragma once
#include <vector>
#include <memory>
using namespace std;

class Graph
{
public:
	Graph() {};
	~Graph() {};

	/*shortest Distance*/
	struct Vertex;
	struct Edge
	{
		int weight;
		Vertex* source;
		Vertex* dest;
	};
	struct Vertex
	{
		int id;
		int value;
		int minDist;
		bool checked = false;

		vector<Edge*> outList;
		vector<Edge*> inList;
	};

	int ShortestDist(Vertex* s, Vertex* z);
	void BFS(Vertex* pStartNode);

	void insert(Vertex* pNode){
		vList.push_back(pNode);
		pNode->id = m_CurId;
		m_CurId++;
	};
	void insert(Edge* edge) {
		edge->source->outList.push_back(edge);
		edge->dest->inList.push_back(edge);
	};

private:
	int m_CurId = 0;
	vector<Vertex*> vList;
};