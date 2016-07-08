#include <iostream>
#include <string>
using namespace std;

enum FROM {
	NOTYET = 0,
	BOTH = 1,
	FROMX = 2,
	FROMY,
};

struct RetEle
{
	int maxLen = -1;
	FROM from = NOTYET;
};

void PrintLongestCommonString(RetEle** retTable, string& strX, string& strY)
{
	int Xsize = strX.size();
	int Ysize = strY.size();
	string answerStack = "";
	while (Xsize != 0 && Ysize != 0)
	{
		if (retTable[Xsize][Ysize].from == BOTH)
		{
			answerStack += strX[Xsize - 1];
			Xsize--;
			Ysize--;
		}else if(retTable[Xsize][Ysize].from == FROMX){
			Xsize--;
		}else{
			Ysize--;
		}
	}

	cout << "reverse answer : " << answerStack << endl;
	answerStack.reserve(answerStack.size());
	cout << "answer : " << answerStack << endl;
}

void LongestCommonBotup(string& strX, string& strY)
{
	int rows = strX.size() - 1;
	int cols = strY.size() - 1;

	//ÃÊ±âÈ­
	RetEle ** retTable = new RetEle*[rows];
	for (int i = 0; i < cols; i++)
		retTable[i] = new RetEle[cols];

	for (int i = 0; i < rows; i++)
		retTable[i][0].maxLen = 0;
	for (int j = 0; j < cols; j++)
		retTable[0][j].maxLen = 0;


	//make table
	for (int i = 1; i < rows; i++)
	{
		for (int j = 1; j < cols; j++)
		{
			if (strX[i] == strY[j])
			{
				retTable[i][j].maxLen = 1 + retTable[i - 1][j - 1].maxLen;
				retTable[i][j].from = BOTH;
			}
			else
			{
				if (retTable[i - 1][j].maxLen > retTable[i][j - 1].maxLen)
				{
					retTable[i][j].maxLen = retTable[i - 1][j].maxLen;
					retTable[i][j].from = FROMX;
				}
				else
				{
					retTable[i][j].maxLen = retTable[i][j - 1].maxLen;
					retTable[i][j].from = FROMY;
				}
			}
		} //col
	} //row

	int maxLen = retTable[strX.size()][strY.size()].maxLen;
	cout << " Max Common length : " << maxLen << endl;
	PrintLongestCommonString(retTable, strX, strY);

	//delete
	for (int i = 0; i < rows; i++)
		delete[] retTable[i];
	delete[] retTable;

	return;
}