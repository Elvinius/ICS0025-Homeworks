#pragma once
#include <iostream>
#include "Date.h"
#include <fstream>
#include <string>
#include <set>

using namespace std;

class Item
{
private:
	char group;
	int subgroup;
	string name;
	Date timestamp;
	static const string filename;
    static fstream file;
	static set<string> randomStrings;
	static set<string> init_set();

	

public:
	Item();
	Item(char, int, string, Date);
	Item(const Item&);
	Item& operator=(const Item&);
	bool operator==(const Item&) const;
	bool operator<(const Item&) const;
	friend ostream& operator<<(ostream&, const Item&);
	virtual ~Item();
	char GetGroup() const;
	int GetSubgroup() const;
	string getName() const;
	Date getDate() const;
};

