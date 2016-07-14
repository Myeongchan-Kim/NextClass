#include <iostream>
#include <vector>

struct Act { // [start, end)
 	int startTime;
	int endTime;
};

int MaxCountAct(std::vector<Act*>& orderedList)
{
	int count = 0, startTime = 0;
	for (auto& act : orderedList)
	{
		if (startTime <= act->startTime)
		{
			count++;
			startTime = act->endTime;
		}
	}// for
	return count;
}