// LabWork5.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "Coach.h"
#include "DumpTrack.h"
#include "GarbageTruck.h"
#include "TrolleyBus.h"

int main()
{	
	GarbageTruck dt;
	std::cin >> dt;
	std::cout << dt;
	std::cout << "\n----------------------------------------------\n";

	Vehicle* vehicles[4] = {
		new Coach(),
		new TrolleyBus(),
		new DumpTrack(),
		new GarbageTruck() };

	for (int i = 0; i < 4; i++)
	{
		std::cout << "\n----------------------------------------------\n";
		std::cin >> vehicles[i][0];
		std::cout << "\n----------------------------------------------\n";
		std::cout << vehicles[i][0];
		std::cout << "\n----------------------------------------------\n";
		delete vehicles[i];
	}
}
