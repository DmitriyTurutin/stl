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

};


int main()
{
	try
	{

		// Test Initializer lits constructor
		List<Goods> lst{ {1, "Bentayga", "Bentley", "London", 2404.32},
						 {2, "S-Class", "Mercedes-Benz", "Munich", 2000.1},
						 {3, "Rio", "Kia", "Seoul", 1605.21}};


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
		std::cout << "==========Print first list==========\n";
		std::cout << header;
		for_each(lst.begin(), lst.end(), Print);
		// Sort
		/*lst.pushFront({0, "M5", "BMW", "Berlin", 3431.1});
		lst.pushBack({ 4, "911", "Porsche", "Moscow", 1241.21 });
		std::cout << header;
		for_each(lst.begin(), lst.end(), Print);
		std::cout << lst.getSize();
*/

		Goods good1 = { 1, "asdfj", "asd", "asdfj", 123.1 };
		List<Goods> list2;
		list2.pushBack(good1);
		list2.Insert(list2.begin(), lst.begin(), lst.end());
		std::cout << header;
		list2.popFront();
		for_each(list2.begin(), list2.end(), Print);


	}
	catch (const std::exception& exception)
	{
		std::cout << exception.what();
	}
	return 0;
}

