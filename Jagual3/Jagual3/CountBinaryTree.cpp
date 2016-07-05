#include <iostream>
#include "Tree.h"

void Tree::Node::insert(Node*  node)
{
	if (node == nullptr)
		return;
	if (node->value > value)
	{
		if (right == nullptr)
			right = node;
		else
			right->insert(node);
	}
	else
	{
		if (left == nullptr)
			left = node;
		else
			left->insert(node);
	}
}

int Tree::CountNode(Node* root)
{
	if (root == nullptr)
		return 0;
	return 1 + CountNode(root->left) + CountNode(root->right);
}

int Tree::CountLeafNode(Node* root)
{
	if (root == nullptr) return 0;
	if (root->left == nullptr && root->right == nullptr)
		return 1;
	return CountLeafNode(root->right) + CountLeafNode(root->left);
}

