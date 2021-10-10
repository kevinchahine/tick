#include <iostream>
#include <iomanip>
#include <string>
#include <chrono>

#include "CommandHandler.h"
#include "DeviceManager.h"
#include "FileManager.h"

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
	// ------------------------- TEST CODE ---------------------------------------
	//tick::test::timerPropertyTree();
	//tick::test::timerManagerInsert();
	//tick::test::timerManagerPropertyTree();
	//tick::test::deviceManagerPT();

	// ------------------------- MAIN CODE ---------------------------------------

	tick::DeviceManager devMan;
	tick::FileManager fileMan;

	tick::CommandHandler handler(devMan);
	
	std::unique_ptr<tick::DeviceBase> ptr = std::make_unique<tick::Timer>();

	while (true)
	{
		cout << "Enter command: ";
	
		string cmdLine;
		getline(cin, cmdLine);
	
		if (cmdLine == "exit") {
			break;
		}
		
		// 1.) --- Load saved data ---
		fileMan.read(devMan);
	
		// 2.) --- Handle Commands ---
		handler.handle(cmdLine);
	
		// 3.) --- Store data back to file ---
		fileMan.write(devMan);
	}

	return 0;
}