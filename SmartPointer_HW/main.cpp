#include <iostream>
#include <string>
#include <vector>
#include <memory>


class Harvest {               
public:
	Harvest(std::string name, std::string color, double weight) : name_(name), color_(color), weight(weight) {}
	
	virtual std::string getName() const
	{
		return name_;
	}
	virtual std::string getColor_() const
	{
		return color_;
	}
	virtual double getWeight() const
	{
		return weight;
	}

private:
	std::string name_;
	std::string color_;
	double weight;
};

class Plants {                 
public:
	Plants(std::string name, std::string size, std::string color, int maxHarvest) : name_(name), size_(size), color_(color), maxHarvest(maxHarvest) {}

	virtual std::string getName() const
	{
		return name_;
	}
	virtual std::string getSize() const
	{
		return size_;
	}
	virtual std::string getColor() const
	{
		return color_;
	}
	virtual int getMaxHarvest() const
	{
		return maxHarvest;
	}
	virtual std::vector <std::unique_ptr<Harvest>> getHarvest() = 0;

private:
	std::string name_;
	std::string size_;
	std::string color_;
	int maxHarvest;
};


class AppleTree :public Plants {
public:
	AppleTree(std::string name_, std::string size_, std::string color_, int capacity_) :
		Plants(name_, size_, color_, capacity_) {}

	virtual std::vector <std::unique_ptr<Harvest>> getHarvest() override {
		std::vector<std::unique_ptr<Harvest>>harvests;
		for (int i = 0; i < getMaxHarvest(); i++) {
			harvests.push_back(std::make_unique<Harvest>("Apple", "Green", 3));
		}
		return harvests;
	}
};

class RaspberryBush :public Plants {
public:
	RaspberryBush(std::string name_, std::string size_, std::string color_, int capacity_) :
		Plants(name_, size_, color_, capacity_) {}

	virtual std::vector <std::unique_ptr<Harvest>> getHarvest() override {
		std::vector<std::unique_ptr<Harvest>>harvests;
		for (int i = 0; i < getMaxHarvest(); i++) {
			harvests.push_back(std::make_unique<Harvest>("RaspberryBush", "Red", 0.2));
		}
		return harvests;
	}
};

int main() {
	setlocale(LC_ALL, "ru");
	std::vector<std::unique_ptr<Harvest>>garden;

	AppleTree appleTree("Apple", "Large", "Green", 1);
	std::vector<std::unique_ptr<Harvest>>appleHarvest = appleTree.getHarvest();
	garden.insert(garden.end(), std::make_move_iterator(appleHarvest.begin()),
		std::make_move_iterator(appleHarvest.end()));



	RaspberryBush strawberry("Strawberry", "Small", "Red", 3);
	std::vector<std::unique_ptr<Harvest>>strawberryHarvest = strawberry.getHarvest();
	garden.insert(garden.end(), std::make_move_iterator(strawberryHarvest.begin()),
		std::make_move_iterator(strawberryHarvest.end()));


	for (const auto& harvests : garden) {
		std::cout << harvests->getName() << std::endl;
		std::cout << harvests->getColor_() << std::endl; 
		std::cout << harvests->getWeight() << std::endl;

	}

	return 0;
}