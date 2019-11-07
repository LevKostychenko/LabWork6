#include "pch.h"
#include "Coach.h"
#include "TextTable.h"

Coach::Coach(double fuelConsumption, int maxNumberOfPersons, double ticketCost, const char* name, int countOfSections)
	: PassengerVehicle(fuelConsumption, maxNumberOfPersons, ticketCost)
{
	int size = strlen(name) + 1;
	this->_vehicleInfo._vechicleName = new char[size];
	strcpy_s(this->_vehicleInfo._vechicleName, size, name);

	this->CountOfSections = countOfSections;

	std::cout << "Coach Connstructor \n";
}

int Coach::GetCountOfSections()
{
	return this->CountOfSections;
}

void Coach::SetCountOfSections(int sections)
{
	this->CountOfSections = sections;
}

Coach::~Coach()
{
	std::cout << "Coach destructor! \n";
}

void Coach::Move(double km)
{
	if (this->_vehicleInfo._vechicleFuelLevel == 0)
	{
		std::cout << "Fuel tank is empty! \n";
		return;
	}

	double maxTrevelDist = this->_vehicleInfo._vechicleFuelLevel / this->_vehicleInfo._fuelConsumption;

	if (maxTrevelDist < km)
	{
		std::cout << "Coach drove " << maxTrevelDist << " Km \n";
		this->_vehicleInfo._vechicleFuelLevel = 0;
		this->_vehicleInfo._vechicleDistanceTreveled += km;
	}
	else
	{
		std::cout << "Coach drove " << km << " Km";
		this->_vehicleInfo._vechicleFuelLevel -= this->_vehicleInfo._fuelConsumption * km;
		this->_vehicleInfo._vechicleDistanceTreveled += km;
	}
}

double Coach::GetProfit()
{
	return this->_ticketCost*this->_maxNumberOfPersons;
}

std::ostream & operator << (std::ostream &out, Coach& vehicle)
{	
	vehicle.SetHeader();
	//std::cout << dynamic_cast<PassengerVehicle&>(vehicle);
	return out;
}

std::istream & operator >> (std::istream &in, Coach& vehicle)
{
	char* countOfSections = new char[3];
	std::cout << "\nCount of sections: ";
	InputValidator::IsNumberInputCorrect(in, countOfSections);
	vehicle.SetCountOfSections(atoi(countOfSections));
	std::cin >> dynamic_cast<PassengerVehicle&>(vehicle);
	return in;
}

Coach& Coach::operator = (Coach& obj)
{
	if (this == &obj)
	{
		delete &obj;
		return *this;
	}

	this->CountOfSections = obj.CountOfSections;

	dynamic_cast<PassengerVehicle&>(*this) = dynamic_cast<PassengerVehicle&>(obj);

	return *this;
}

void Coach::SetHeader()
{
	texttable::TextTable t('-', '|', '+');

	t.add("Count of sections");
	PassengerVehicle::SetPassengerVehicleHeader(t);
	t.endOfRow();
	this->SetData(t);
}

void Coach::SetData(texttable::TextTable& t)
{
	t.add(std::to_string(this->GetCountOfSections()).c_str());
	PassengerVehicle::SetPessengerVehicleData(t);
	t.setAlignment(2, texttable::TextTable::Alignment::RIGHT);
	t.endOfRow();
	std::cout << t;
}