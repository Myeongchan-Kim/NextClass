#include <iostream>
#include <vector>
#include "Graph.h"
#define MAX_VAL 987654321;
using namespace std;

int ShortestDist(Vertex* s, Vertex* z)
{
	if (s == z) return 0;
	if (z->minDist != -1) return z->minDist;

	int minResult = MAX_VAL;
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

