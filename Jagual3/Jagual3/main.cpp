#include "main.h"
#include <iostream>

int main()
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
	
	//BFS
	//linear graph 0-> 1 -> 2 -> 3-> 4-> 5-> 6-> 7-> 8-> 9
	std::cout << "**** BFS ****" << std::endl;
	Graph G;
	for (int i = 0; i < 10; i++)
	{
		Graph::Vertex v1;
		v1.value = i;
		G.insert(&v1);
	}
	


	return 0;
}