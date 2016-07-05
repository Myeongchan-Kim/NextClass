#include <iostream>
#include <thread>
#include "App.h"

int main()
{
	App app;
	app.Init();

	std::thread logicThread([&]() {
		app.Run(); }
	);

	std::cout << "press any key to exit...";
	getchar();

	app.Stop();
	logicThread.join();

	return 0;
}