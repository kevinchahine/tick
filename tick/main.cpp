#include <iostream>
#include <iomanip>
#include <string>
#include <chrono>

#include "CommandHandler.h"

using namespace std;

void pause()
{
	cout << "Press any key...";
	cin.get();
}

int main(int argc, char** argv)
{
	tick::CommandHandler handler;
	
	while (true)
	{
		cout << "Enter command: ";

		string cmdLine;
		getline(cin, cmdLine);

		if (cmdLine == "exit") {
			break;
		}

		handler.handle(cmdLine);
	}

	return 0;
}