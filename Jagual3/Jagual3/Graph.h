#pragma once
#include <vector>
#include <memory>
using namespace std;

class Graph
{
public:
	Graph();
	~Graph();
	void initVertex();

	/*shortest Distance*/
	struct Vertex;
	struct Edge
	{
		int weight; //for shortest
		Vertex* source;
		Vertex* dest;
	};
	struct Vertex
	{
		int id; //
		int value; 
		int minDist; //for shortest
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
	void NewEdge(int srcId, int dstId, int weight = 1) {
		Edge* e = new Edge;
		e->weight = weight;
		e->source = vList[srcId];
		e->dest = vList[dstId];
		insert(e);
	}
	void insert(Edge* edge) {
		edge->source->outList.push_back(edge);
		edge->dest->inList.push_back(edge);
	};

	vector<Vertex*> vList;
private:
	int m_CurId = 0;
};