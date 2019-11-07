#include "pch.h"
#include "TrolleyBus.h"
#include "TextTable.h"

TrolleyBus::TrolleyBus(double fuelConsumption, int maxNumberOfPersons, double ticketCost, const char* name, double chargeLevel)
	: PassengerVehicle(fuelConsumption, maxNumberOfPersons, ticketCost)
{
	int size = strlen(name) + 1;
	this->_vehicleInfo._vechicleName = new char[size];
	strcpy_s(this->_vehicleInfo._vechicleName, size, name);

	this->ChargeLevel;

	std::cout << "Trolley Bus Connstructor \n";
}

double TrolleyBus::GetChargeLevel()
{
	return this->ChargeLevel;
}

void TrolleyBus::SetChargeLevel(double level)
{
	this->ChargeLevel = level;
}

TrolleyBus::~TrolleyBus()
{
	std::cout << "Trolley Bus destructor! \n";
}

void TrolleyBus::Move(double km)
{
	if (this->_vehicleInfo._vechicleFuelLevel == 0)
	{
		std::cout << "Fuel tank is empty! \n";
		return;
	}

	double maxTrevelDist = this->_vehicleInfo._vechicleFuelLevel / this->_vehicleInfo._fuelConsumption;

	if (maxTrevelDist < km)
	{
		std::cout << "Trolley Bus drove " << maxTrevelDist << " Km \n";
		this->_vehicleInfo._vechicleFuelLevel = 0;
		this->_vehicleInfo._vechicleDistanceTreveled += km;
	}
	else
	{
		std::cout << "Trolley Bus drove " << km << " Km";
		this->_vehicleInfo._vechicleFuelLevel -= this->_vehicleInfo._fuelConsumption * km;
		this->_vehicleInfo._vechicleDistanceTreveled += km;
	}
}

std::ostream & operator << (std::ostream &out, TrolleyBus& vehicle)
{	
	vehicle.SetHeader();
	//std::cout << dynamic_cast<PassengerVehicle&>(vehicle);
	return out;
}

std::istream & operator >> (std::istream &in, TrolleyBus& vehicle)
{
	char* charge = new char[4];
	std::cout << "\nCharge level: ";
	InputValidator::IsNumberInputCorrect(in, charge);
	vehicle.SetChargeLevel(atoi(charge));

	std::cin >> dynamic_cast<PassengerVehicle&>(vehicle);
	return in;
}

double TrolleyBus::GetProfit()
{
	return this->_ticketCost*this->_maxNumberOfPersons;
}

TrolleyBus& TrolleyBus::operator = (TrolleyBus& obj)
{
	if (this == &obj)
	{
		delete &obj;
		return *this;
	}

	this->ChargeLevel = obj.ChargeLevel;

	dynamic_cast<PassengerVehicle&>(*this) = dynamic_cast<PassengerVehicle&>(obj);

	return *this;
}

void TrolleyBus::SetHeader()
{
	texttable::TextTable t('-', '|', '+');

	t.add("Level of charge");
	PassengerVehicle::SetPassengerVehicleHeader(t);
	t.endOfRow();
	this->SetData(t);
}

void TrolleyBus::SetData(texttable::TextTable& t)
{
	t.add(std::to_string(this->GetChargeLevel()).c_str());
	PassengerVehicle::SetPessengerVehicleData(t);
	t.setAlignment(2, texttable::TextTable::Alignment::RIGHT);
	t.endOfRow();
	std::cout << t;
}