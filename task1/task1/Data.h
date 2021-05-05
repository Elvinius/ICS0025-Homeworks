#pragma once
#include <map>
#include <list>
#include "Item.h"
#include <iostream>

using namespace std;

class Data
{
	map<char, map<int, list<Item*>*>*> datastructure;

public:
	Data();
	Data(int );
	~Data();
	void PrintAll() const;
	int CountItems() const;
	map<int, list<Item*>*> *GetGroup(char) const;
	void PrintGroup(char) const;
	int CountGroup(char) const;
	list<Item*>* GetSubgroup(char, int) const;
	void PrintSubgroupByNames(char, int) const;
	void PrintSubgroupByDates(char, int) const;
	int CountSubgroup(char, int) const;
	Item* GetItem(char, int, string) const;
	void PrintItem(char, int, string) const;
	Item* InsertItem(char, int, string, Date);
	list<Item*>* InsertSubgroup(char, int, initializer_list<Item*>);
	map<int, list<Item*>*>* InsertGroup(char, initializer_list<int>, initializer_list<initializer_list<Item*>>);
	bool RemoveItem(char, int, string);
	bool RemoveSubgroup(char, int);
	bool RemoveGroup(char);

};

