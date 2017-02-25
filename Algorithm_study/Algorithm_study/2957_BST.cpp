#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <functional>
#include <string>
#include <sstream>
#include <memory>

#define INF 987654321
struct Node {
	int key = 0;
	int height = 1;
};

long long counter;
std::map<int, Node*> tree;

Node* findParent(int key)
{
	auto fatherPair = tree.lower_bound(key);
	auto motherPair = tree.lower_bound(key);
	motherPair--;

	if (fatherPair == tree.end())
		return motherPair->second;
	if (motherPair == tree.end())
		return fatherPair->second;

	auto mother = motherPair->second;
	auto father = fatherPair->second;

	if (mother->height > father->height)
		return mother;
	else
		return father;
}

void count_insert(int ele)
{
	Node* new_node = new Node();
	new_node->key = ele;

	if (!tree.empty())
	{
		Node* parent = findParent(ele);
		new_node->height = (parent->height) + 1;
		counter += parent->height;
	}
	tree.insert({ ele, new_node });
}

int main() 
{
	tree.clear();
	counter = 0;

	int C;
	scanf("%d", &C);

	for (int i = 0; i < C; i++)
	{
		int ele;
		scanf("%d", &ele);
		count_insert(ele);
		printf("%lld\n", counter);
	}

	return 0;
}