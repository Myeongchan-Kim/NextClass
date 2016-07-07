#include "main.h"

int main()
{
	Tree::Node node(5);
	Tree::Node nodeList[10] = { 1, 3, 2, 6, 5, 9, 7, 8, 10, 4 };

	for (int i = 0; i < 10; i++)
	{
		node.insert(&nodeList[i]);
	}

	std::cout << Tree::CountNode(&node) << std::endl;
	std::cout << Tree::CountLeafNode(&node) << std::endl;
	return 0;


}