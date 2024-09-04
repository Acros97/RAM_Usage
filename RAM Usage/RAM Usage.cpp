// RAMUsage.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include "windows.h"
using namespace std;

void SetConsoleDimensions(int width, int height) {
	// OBtiene el manejador de la consola
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	// Define el tamaño del búfer de pantalla (debe ser al menos tan grande como la ventana)
	COORD bufferSize = { static_cast<SHORT>(width), static_cast<SHORT>(height) };
	SetConsoleScreenBufferSize(hConsole, bufferSize);

	// Define las dimensiones de la ventana
	SMALL_RECT windowSize = { 0, 0, static_cast<SHORT>(width - 1), static_cast<SHORT>(height - 1) };
	SetConsoleWindowInfo(hConsole, TRUE, &windowSize);
}

string StatusScreen(int percentage) {
	string LSTATUS = "[                  ]";

	if (percentage >= 10)
		LSTATUS = "[..                ]";
	if (percentage >= 20)
		LSTATUS = "[....              ]";
	if (percentage >= 40)
		LSTATUS = "[.......           ]";
	if (percentage >= 55)
		LSTATUS = "[.........         ]";
	if (percentage >= 60)
		LSTATUS = "[..........        ]";
	if (percentage >= 65)
		LSTATUS = "[...........       ]";
	if (percentage >= 75)
		LSTATUS = "[.............     ]";
	if (percentage >= 80)
		LSTATUS = "[................  ]";
	if (percentage >= 90)
		LSTATUS = "[................. ]";

	return LSTATUS;
}

int main()
{
	SetConsoleDimensions(60, 10);
	while (true) {
		system("CLS");
		cout << "RAM Usage - Console version. Written by Daniel Fros. \n\n";
		// TOTAL PHYSICAL MEMORY (RAM):
		MEMORYSTATUSEX memoryData;
		memoryData.dwLength = sizeof(MEMORYSTATUSEX);
		GlobalMemoryStatusEx(&memoryData);
		DWORDLONG totalPhysMem = memoryData.ullTotalPhys;
		cout << "TOTAL PHYSICAL MEMORY AVAILABLE: " << totalPhysMem << "\n";

		MEMORYSTATUSEX memInfo;
		memInfo.dwLength = sizeof(MEMORYSTATUSEX);
		GlobalMemoryStatusEx(&memInfo);

		// PHYSICAL MEMORY CURRENTLY USED
		DWORDLONG physMemMemUsed = memInfo.ullTotalPhys - memInfo.ullAvailPhys;
		int percentage = (physMemMemUsed * 100) / totalPhysMem;
		cout << "MEMORY CURRENTLY USED: " << physMemMemUsed << "(" << percentage << "%)" << " " << StatusScreen(percentage) << endl;

		// YOU CAN ADJUST UPDATE TIME
		Sleep(3000);
	}

	return 0;
}