#include <iostream>
#include <iomanip>
#include <string>
#include <chrono>

#include "CommandHandler.h"
#include "DeviceManager.h"

#include "TestPropertyTree.h"
#include "TestTimerManager.h"

using namespace std;

void stop()
{
	cout << "Press any key...";
	cin.get();
}

int main(int argc, char** argv)
{
	tick::DeviceManager devices;
	
	//tick::CommandHandler handler(devices);
	//
	//while (true)
	//{
	//	cout << "Enter command: ";
	//
	//	string cmdLine;
	//	getline(cin, cmdLine);
	//
	//	if (cmdLine == "exit") {
	//		break;
	//	}
	//
	//	// 1.) --- Load saved data ---
	//
	//	// 2.) --- Handle Commands ---
	//	handler.handle(cmdLine);
	//
	//	// 3.) --- Store data back to file ---
	//
	//}

	//tick::test::timerPropertyTree();
	tick::test::timerManagerInsert();
	tick::test::timerManagerPropertyTree();

	return 0;
}