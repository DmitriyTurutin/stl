#include <iostream>
#include <iomanip>
#include <exception>
#include "Container.h"
#include "Algorithms.h"
#include "Iterator.h"
#include <list>

// Clean Code: A Handbook of Agile Software Craftsmanship 
// You also don't need to prefix member variables with m_ anymore. 
// Your classes and functions should be small enough that you don't need them

// Task 1 
struct Goods
{
	int id;
	std::string name;
	std::string manufacturer; 
	std::string warehouse_address; 
	double weight;
	
	Goods(const int& id = 0, const std::string& name = "", 
							 const std::string& manufacturer = "", 
							 const std::string& warehouse_address = "", const double& weight = .0) : 
		  id(id), 
		  name(name), 
		  manufacturer(manufacturer),
		  warehouse_address(warehouse_address),
		  weight(weight)
		  
	{}

	bool operator>(const Goods& good) { return id > good.id; }
	bool operator==(const Goods& good) { return this == &good; }

	friend std::ostream& operator<<(std::ostream& os, const Goods& good)
	{
		os << "| id: " << good.id << std::endl;
		os << "| name: " << good.name << std::endl;
		os << "| manufacturer: " << good.manufacturer << std::endl;
		os << "| address: " << good.warehouse_address << std::endl;
		os << "| weight: " << good.weight << std::endl;

		return os;
	}

};


class Functor
{
public:
	auto operator()(const Goods& good)
	{
		return good.manufacturer == "Mercedes-Benz";
	}
};


int main()
{
	try
	{

		// Test Initializer lits constructor
		List<Goods> lst{ {1, "Bentayga", "Bentley", "London", 2404.32},
						 {2, "S-Class", "Mercedes-Benz", "Munich", 2000.1},
						 {3, "G-Class", "Mercedes-Benz", "Munich", 2789.12},
						 {4, "Rio", "Kia", "Seoul", 1605.21}};


		std::string header = std::string("+--------+--------------------+--------------------+--------------------+---------+\n") +
							 std::string("|  ID    |  NAME              |  MANUFACTURER      |	ADDRESS         |  WEIGHT |\n") +
							 std::string("+--------+--------------------+--------------------+--------------------+---------+\n");
		auto Print = [](const Goods& good) {
			std::cout << "| " << std::setw(6) << good.id << " | "
				<< std::setw(18) << good.name << " | " 
				<< std::setw(18) << good.manufacturer << " | " 
				<< std::setw(18) << good.warehouse_address << " | " 
				<< std::setw(7) << good.weight << " |" << '\n';
			std::cout << "+--------+--------------------+--------------------+--------------------+---------+\n";
		};
	
		// Task 2
		std::cout << "The list is obtained using the initialization list:\n";
		std::cout << "==========Print first list==========\n";
		std::cout << header;
		for_each(lst.begin(), lst.end(), Print);
		system("pause");
		system("cls");

		List<Goods> lst2;
		std::cout << "pushBack() / pushFront() / Insert()\n";
		std::cout << header;
		Goods rosin = { 14, "Pranito", "Pirastro", "Germany", 0.03 };
		Goods book = { 23, "Atlas Shrugged", "Ayn Rand", "USA", 0.1 };
		Goods fridge = { 41, "FAB28ULBE3", "Smeg", "Italy", 100.21 };
		lst2.pushBack(rosin);
		lst2.pushFront(book);
		lst2.Insert(lst2.at(1), fridge);
		for_each(lst2.begin(), lst2.end(), Print);
		
		system("pause");
		system("cls");

		
		std::cout << "Range Insert()\n";
		std::cout << header;
		lst.Insert(lst.at(2), lst2.begin(), lst2.end());
		for_each(lst.begin(), lst.end(), Print);
		system("pause");
		system("cls");


		std::cout << "Sort by weight\n";
		std::cout << header;
		Sort(lst.begin(), lst.end(), [](const Goods& good) { return good.weight; });
		for_each(lst.begin(), lst.end(), Print);
		system("pause");
		system("cls");
		

		std::cout << "FidnIf() 1000 < weight < 4000\n\n";
		List<Goods>::Iterator car = find_if(lst.begin(), lst.end(), [](const Goods& good) { return (good.weight > 1000
																     && good.weight < 4000); });

		std::cout << *car;


		std::cout << std::endl << std::endl <<"Change weight:\n" << std::endl;
		car->weight = 1700.36;
		std::cout << *car;
		system("pause");

		Functor func;
		system("cls");
		std::cout << "Mercedes cars:" << std::endl;
		std::cout << header;
		int mercedes_cars = count_if(lst.begin(), lst.end(), func);
		List<Goods> mercedes_list(mercedes_cars);
		copy_if(lst.begin(), lst.end(), mercedes_list.begin(), func);
		for_each(mercedes_list.begin(), mercedes_list.end(), Print);
	}
	catch (const std::exception& exception)
	{
		std::cout << exception.what();
	}
	return 0;
}

