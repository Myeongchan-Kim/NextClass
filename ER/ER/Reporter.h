#pragma once
#include <iostream>
using namespace std;

class TestModule;

class Reporter
{
public:
	Reporter();
	~Reporter();
	void makeReport(const TestModule * test);
};

