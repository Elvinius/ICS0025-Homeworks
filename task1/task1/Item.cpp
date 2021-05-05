#include "Item.h"

set<string> Item::init_set()
{

	file.open(filename, ios::in);
	set<string> stringset;
	if (file.is_open()) {
		string files;
		while (getline(file, files)) {
			if (files.length() > 2) {
				stringset.insert(files);
			}
		}
		file.close();
	}
	else {
		cout << "file not found" << endl;
	}
	return stringset;
}

fstream Item::file;
const string Item::filename = "Birds.txt";
set<string> Item::randomStrings = Item::init_set();

Item::Item()
{
	random_device device;
	mt19937 generator(device());
	uniform_int_distribution<int> distribution(0, randomStrings.size() - 1);
	string name = *(next(randomStrings.begin(), distribution(generator)));
	this->name = name;
	Date date;
	date = date.CreateRandomDate(Date(1, 1, 2000), Date(31, 12, 2020));
	this->timestamp = date;
	uniform_int_distribution<int>subgroupDistribution(0, 99); 
	this->subgroup =subgroupDistribution(generator);
	uniform_int_distribution<int>groupDistribution(65, 90);
	this->group = static_cast<char>(groupDistribution(generator));
}

Item::Item(char group, int subgroup, string name, Date timestamp)
{
	random_device device;
	mt19937 generator(device());
	uniform_int_distribution<int> groupDistribution(65, 90);
	if (static_cast<int>(group) < 65) {
		cout << endl << "Group not found" << endl;
		this->group = static_cast<char>(groupDistribution(generator));
	}
	else if (static_cast<int>(group) > 90) {
		cout << endl << "Group not found" << endl;
		if (static_cast<int>(group) - 32 < 64 || static_cast<int>(group) - 32 > 90) {
			this->group = static_cast<char>(groupDistribution(generator));
		}
		else {
			this->group = static_cast<char>(group - 32);
		}

	}else{
		this->group = group;
	}

	if (subgroup < 0 || subgroup > 99) {
		cout << "Bad subgroup" << endl;
		uniform_int_distribution<int> subgroupDistribution(0, 99);
		this->subgroup = subgroupDistribution(generator);
	}else {
		this->subgroup = subgroup;
	}

	if (name.empty()) {
		randomStrings = init_set();
		uniform_int_distribution<int> nameDistribution(0, randomStrings.size() - 1);
		string name = *(next(randomStrings.begin(), nameDistribution(generator)));
		this->name = name;

	}else{
		this->name = name;
	}

	this->timestamp = timestamp;

}

Item::Item(const Item& other)
{

	this->group = other.group;
	this->subgroup = other.subgroup;
	this->name = other.name;
	this->timestamp = other.timestamp;

}

Item& Item::operator=(const Item& right)
{
	this->group = right.group;
	this->subgroup = right.subgroup;
	this->name = right.name;
	this->timestamp = right.timestamp;
	return *this;
}

bool Item::operator==(const Item& right) const
{
	if (this->group != right.group) {
		return false;
	}if (this->subgroup != right.subgroup) {
		return false;
	}
	if (this->name.length() != right.name.length()) {
		return false;
	}
	else {
		return this->name.compare(right.name) && this->timestamp == right.timestamp;
	}		
}

bool Item::operator<(const Item& right) const
{
	if (this->group != right.group) {
		return this->group < right.group;
	}
	else if (this->subgroup != right.subgroup) {
		return this->subgroup < right.subgroup;
	}
	else if (this->name != right.name) {
		return this->name < right.name;
	}
	return this->timestamp < right.timestamp;
}

Item::~Item()
{
}

char Item::GetGroup() const
{
	return this->group;
}

int Item::GetSubgroup() const
{
	return this->subgroup;
}

string Item::getName() const
{
	return this->name;
}

Date Item::getDate() const
{
	return this->timestamp;
}

ostream& operator<<(ostream& out, const Item& item)
{
	out << item.group << item.subgroup << " " << item.name << " - " << item.timestamp.ToString();
	return out;
}
