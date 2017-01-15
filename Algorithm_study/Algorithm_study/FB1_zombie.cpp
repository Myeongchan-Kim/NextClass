#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <functional>
#include <string>
#include <sstream>
#include <memory>

struct Rect {
	int topY;
	int botY;
	int leftX;
	int rightX;

	int width() {
		abs(leftX - rightX);
	}
	int height() {
		abs(topY - botY);
	}

	std::set<int> elements;
};

bool operator== (const Rect& r1, const Rect& r2)
{
	return (r1.topY == r2.topY &&
		r1.botY == r2.botY &&
		r1.leftX == r2.leftX &&
		r1.rightX == r2.rightX);
};

bool operator< (const Rect& r1, const Rect& r2)
{
	if (r1.topY == r2.topY)
	{
		if (r1.botY == r2.botY)
		{
			if (r1.leftX == r1.leftX)
				return r1.rightX < r2.rightX;
			else
				return r1.leftX < r1.leftX;
		}else{
			return r1.botY < r2.botY;
		}
	}
	else {
		return r1.topY < r2.topY;
	}

};

int size, R;

std::vector<std::pair<int,int>> full_points;
std::vector<std::set<int>> groups; // group of point indicis.

void MakeRectList(std::set<Rect>& rects, std::vector<std::pair<int,int>>&points) {
	int size = points.size();
	
	//make groups by every four full_points.
	for (int top = 0; top < size; top++)
	{
		for (int bot = 0; bot < size; bot++)
		{
			if (top == bot)
				continue;
			int height = points[top].second - points[bot].second;
			if (height < 0 || height > R)
				continue;

			for (int left = 0; left < size; left++)
			{
				if (points[left].second > points[top].second ||
					points[left].second < points[bot].second)
					continue;
				if (points[left].first > points[top].first ||
					points[left].first > points[bot].first)
					continue;

				for (int right = 0; right < size; right++)
				{

					if (left == right)
						continue;
					if (points[right].second > points[top].second ||
						points[right].second < points[bot].second)
						continue;
					if (points[right].first < points[top].first ||
						points[right].first < points[bot].first)
						continue;
					int width = points[right].first - points[left].first;
					if (width < 0 || width > R)
						continue;

					std::set<int> newGroup;
					newGroup.insert(top);
					newGroup.insert(bot);
					newGroup.insert(left);
					newGroup.insert(right);

					Rect newRect;
					newRect.topY = points[top].second;
					newRect.botY = points[bot].second;
					newRect.leftX = points[left].first;
					newRect.rightX = points[right].first;
					newRect.elements = newGroup;
					rects.insert(newRect);
				}
			}
		}
	}

	//insert point for each groups
	for (auto& rect : rects)
	{
		for (int i = 0; i < size; i++)
		{
			auto point = full_points[i];
			if (point.first <= rect.rightX && point.first >= rect.leftX &&
				point.second <= rect.topY && point.second >= rect.botY)
			{
				const_cast<Rect&>(rect).elements.insert(i);
			}
		}
	}

	//make single point rect
	for (int i = 0; i < size; i++)
	{
		auto point = points[i];
		Rect newSingleRect;
		newSingleRect.topY = point.second;
		newSingleRect.botY = point.second;
		newSingleRect.leftX = point.first;
		newSingleRect.rightX = point.first;
		newSingleRect.elements.insert(i);
		rects.insert(newSingleRect);
	}
}

void CheckRects(std::set<Rect>& rects)
{
	printf("\n\n\n");
	//check rect
	for (auto& rect : rects)
	{
		printf("Rect:\ttop:%d bot:%d left:%d right:%d ele:%d\n", rect.topY, rect.botY, rect.leftX, rect.rightX, rect.elements.size());
	}
}

Rect MaxRect(std::set<Rect> rect_list)
{
	Rect maxRect;
	int maxNum = 0;
	for (auto& rect : rect_list)
	{
		if (maxNum < rect.elements.size())
		{
			maxNum = rect.elements.size();
			maxRect = rect;
		}
		//printf("Rect:\ttop:%d bot:%d left:%d right:%d ele:%d\n", rect.topY, rect.botY, rect.leftX, rect.rightX, rect.elements.size());
		//printf("\tMaxNum:%d\n", maxNum);
	}
	return maxRect;
}

void problem_solve(int case_num)
{
	full_points.clear();
	groups.clear();
	std::set<Rect> rects;
	scanf("%d %d", &size, &R);

	for (int i = 0; i < size; i++)
	{
		int X, Y;
		scanf("%d %d", &X, &Y);
		full_points.push_back({ X, Y });
	}
	sort(full_points.begin(), full_points.end(), [=]( std::pair<int,int>&p1, std::pair<int,int>&p2) {
		return p1.first < p2.first;
	});

	MakeRectList(rects, full_points);
	//CheckRects(rects);

	Rect maxRect = MaxRect(rects);
	std::vector<std::pair<int,int>> rest_points;
	std::set<Rect> restRects;
	for (int i =0 ; i< size; i++)
	{
		if (maxRect.elements.find(i) == maxRect.elements.end())
			rest_points.push_back(full_points[i]);
	}
	//printf("rest count : %d\n", rest_points.size());

	MakeRectList(restRects, rest_points);
	//CheckRects(restRects);
	Rect restMaxRect = MaxRect(restRects);
	int result = maxRect.elements.size() + restMaxRect.elements.size();
	//printf("maxRect:%d maxRestRect:%d\n", maxRect.elements.size(), restMaxRect.elements.size());
	printf("Case #%d: %d\n", case_num, result);
}

int main() {
	int T;
	scanf("%d", &T);
	for (int i = 0; i < T; i++)
	{
		problem_solve(i + 1);
	}
	return 0;
}