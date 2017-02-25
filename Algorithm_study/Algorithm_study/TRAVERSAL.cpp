#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <functional>
#include <string>
#include <sstream>
#include <memory>

#define INF 987654321
int N;

std::vector<int> preorder;
std::vector<int> inorder;

void printPostOrderByVec(std::vector<int>& pre, std::vector<int>& in)
{
	if (pre.size() != in.size())
	{
		printf("\n!!!!!Wrong input!!!!\n");
		printf("pre: ");
		for (auto i : pre)
		{
			printf("%d ", i);
		}
		printf("\n");
		printf("in: ");
		for (int i : in)
		{
			printf("%d ", i);
		}
		printf("\n");

	}
	if (in.size() == 0)
		return;

	int me = pre[0];
	int pre_i = 1;
	int in_i = pre_i - 1;
	std::vector<int> leftIn;
	std::vector<int> rightIn;
	std::vector<int> leftPre;
	std::vector<int> rightPre;

	while (in[in_i] != me)
	{
		leftIn.push_back(in[in_i]);
		leftPre.push_back(pre[pre_i]);
		pre_i++;
		in_i++;
	}

	int meId = in_i;
	in_i++; // pre_i == in_i

	if (in_i != pre_i)
	{
		printf("!!! woring Idx");
		return;
	}
	while (in_i < in.size())
	{
		rightIn.push_back(in[in_i]);
		rightPre.push_back(pre[pre_i]);
		pre_i++;
		in_i++;
	}
	printPostOrderByVec(leftPre, leftIn);
	printPostOrderByVec(rightPre, rightIn);
	printf("%d ", me);
}

void problem_solve() 
{
	scanf("%d", &N);
	preorder.clear();
	inorder.clear();

	for (int i = 0; i < N; i++)
	{
		int val = 0;
		scanf("%d", &val);
		preorder.push_back(val);
	}

	for (int i = 0; i < N; i++)
	{
		int val = 0;
		scanf("%d", &val);
		inorder.push_back(val);
	}

	printPostOrderByVec(preorder, inorder);
	printf("\n");
}


int main() {

	int C;
	scanf("%d", &C);

	for (int i = 0; i < C; i++)
	{
		problem_solve();
	}

	return 0;
}