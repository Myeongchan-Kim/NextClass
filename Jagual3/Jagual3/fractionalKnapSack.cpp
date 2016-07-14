#include <iostream>
#include <vector>
#include <algorithm>

struct Item
{
	double weight;
	double value;
};

double MaxValueKnapSack(std::vector<Item*>& itemList, double capacity)
{
	//sort
	std::sort(itemList.begin(), itemList.end(), 
		[](Item*& lv, Item*& rv) { return (lv->value / lv->weight > rv->value / rv->weight);}
	);

	double value = 0;
	for (auto& item : itemList) //add value from the valuest item
	{
		if (item->weight <= capacity)
		{
			value += item->value;
			capacity -= item->weight;
		}
		else {
			value += (item->value / item->weight * capacity); 
			break;
		}
	}//for
	return value;
}// func