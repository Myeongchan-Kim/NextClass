#include "main.h"
#include <iostream>

int main()
{
	BinaryCodeTest();

	GraphTest();
	return 0;
}

void BinaryCodeTest()
{
	//Binary tree node count
	std::cout << "**** Binary tree count ****" << std::endl;
	Tree::Node node(5);
	Tree::Node nodeList[10] = { 1, 3, 2, 6, 5, 9, 7, 8, 10, 4 };

	for (int i = 0; i < 10; i++)
	{
		node.insert(&nodeList[i]);
	}

	std::cout << "Node Count : " << Tree::CountNode(&node) << std::endl;
	std::cout << "Leaf Count : " << Tree::CountLeafNode(&node) << std::endl;
}

void GraphTest()
{
	//BFS
	//linear graph 0-> 1 -> 2 -> 3-> 4-> 5-> 6-> 7-> 8-> 9
	std::cout << "**** BFS ****" << std::endl;
	Graph testGraph;
	for (int i = 0; i < 9; i++)
	{
		testGraph.NewEdge(i, i + 1);
	}

	cout << "linear" << endl;
	testGraph.BFS(testGraph.vList[0]);

	//new edge : 1->5 5->9 3->5
	cout << "add 1->5 5->9 3->5 " << endl;
	testGraph.NewEdge(1, 5);
	testGraph.NewEdge(5, 9);
	testGraph.NewEdge(3, 5);

	testGraph.BFS(testGraph.vList[0]);


	/////////shortest way
	//init for shortestDist
	cout << "Shortest 0 to 9 : " 
		<< testGraph.ShortestDist(testGraph.vList[0], testGraph.vList[9]) 
		<< endl; //maybe 3

	//init for shortestDist
	for (auto& pVtx : testGraph.vList)
	{
		pVtx->minDist = -1;
	}
	cout << "Shortest 0 to 8 : " 
		<< testGraph.ShortestDist(testGraph.vList[0], testGraph.vList[8]) 
		<< endl; //maybe 5


}
