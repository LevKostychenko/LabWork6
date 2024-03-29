#include "pch.h"
#include "GarbageTruck.h"
#include "TextTable.h"

GarbageTruck::GarbageTruck(double fuelConsumption, double maxCapacity, const char* name, const char* transportedGarbage) 
	: FreightVehicle(fuelConsumption, maxCapacity)
{	
	int size = strlen(name) + 1;
	this->_vehicleInfo._vechicleName = new char[size];
	strcpy_s(this->_vehicleInfo._vechicleName, size, name);

	int resSize = strlen(transportedGarbage) + 1;
	this->TransportedGarbage = new char[resSize];
	strcpy_s(this->TransportedGarbage, resSize, transportedGarbage);

	std::cout << "Garbage Truck Connstructor \n";
}

GarbageTruck::~GarbageTruck()
{
	delete this->TransportedGarbage;
	std::cout << "Garbage truck destructor! \n";
}

char* GarbageTruck::GetTransportedGarbage()
{
	return this->TransportedGarbage;
}

void GarbageTruck::SetTransportedGarbage(const char * garbage)
{
	int size = strlen(garbage) + 1;
	this->TransportedGarbage = new char[size];
	strcpy_s(this->TransportedGarbage, size, garbage);
}

void GarbageTruck::Move(double km)
{
	if (this->_vehicleInfo._vechicleFuelLevel == 0)
	{
		std::cout << "Fuel tank is empty! \n";
		return;
	}

	double maxTrevelDist = this->_vehicleInfo._vechicleFuelLevel / this->_vehicleInfo._fuelConsumption;

	if (maxTrevelDist < km)
	{
		std::cout << "Garbage Truck drove " << maxTrevelDist << " Km \n";
		this->_vehicleInfo._vechicleFuelLevel = 0;
		this->_vehicleInfo._vechicleDistanceTreveled += km;
	}
	else
	{
		std::cout << "Garbage Truck drove " << km << " Km";
		this->_vehicleInfo._vechicleFuelLevel -= this->_vehicleInfo._fuelConsumption * km;
		this->_vehicleInfo._vechicleDistanceTreveled += km;
	}
}

std::ostream & operator << (std::ostream &out, GarbageTruck& vehicle)
{	
	vehicle.SetHeader();

	//std::cout << dynamic_cast<FreightVehicle&>(vehicle);
	return out;
}

std::istream & operator >> (std::istream &in, GarbageTruck& vehicle)
{
	char* trspGarb = new char[20];

	std::cout << "\nTransorted grabage: ";
	InputValidator::IsInputCorrect(in, trspGarb);
	vehicle.SetTransportedGarbage(trspGarb);

	std::cin >> dynamic_cast<FreightVehicle&>(vehicle);
	return in;
}

GarbageTruck& GarbageTruck::operator = (GarbageTruck& obj)
{
	if (this == &obj)
	{
		delete &obj;
		return *this;
	}

	this->TransportedGarbage = obj.TransportedGarbage;

	dynamic_cast<FreightVehicle&>(*this) = dynamic_cast<FreightVehicle&>(obj);

	return *this;
}

void GarbageTruck::SetHeader()
{
	texttable::TextTable t('-', '|', '+');

	t.add("Tratsported garbage");
	FreightVehicle::SetFreightVehicleHeader(t);
	t.endOfRow();
	this->SetData(t);
}

void GarbageTruck::SetData(texttable::TextTable& t)
{
	t.add(this->GetTransportedGarbage());
	FreightVehicle::SetFreightVehicleData(t);
	t.setAlignment(2, texttable::TextTable::Alignment::RIGHT);
	t.endOfRow();
	std::cout << t;
}