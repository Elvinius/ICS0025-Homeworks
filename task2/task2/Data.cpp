#include "Data.h"

Data::Data()
{

}

Data::Data(int n)
{
	list<Item*>* pItemList = new list<Item*>;

	for (int i = 0; i < n; ++i) {
		Item* item = new Item;
		pItemList->push_back(item);
	}
	auto sort = [](Item* item, Item* other) -> bool {return *item < *other; };
	pItemList->sort(sort);
	for_each(pItemList->begin(), pItemList->end(), [this](Item* pItem) {this->InsertItem(pItem->GetGroup(), pItem->GetSubgroup(), pItem->getName(), pItem->getDate()); });
	for_each(pItemList->begin(), pItemList->end(), [](Item* item) {delete item; });
	delete pItemList;
}

Data::~Data()
{
	for (auto dit = datas.begin(); dit != datas.end(); ++dit) {
		map<int, list<Item*>*>* subgroupMap = dit->second;
		
		for (auto subit = subgroupMap->begin(); subit != subgroupMap->end(); ++subit) {
			for_each(subit->second->begin(), subit->second->end(), [](Item* item) {delete item; }); 
			delete subit->second;
		}
		delete subgroupMap;
	}
	datas.clear();
}

void Data::PrintAll() const
{
	if (datas.size() > 0) {
		for (auto dit = datas.begin(); dit != datas.end(); ++dit) {

			cout << dit->first << ": " << endl;
			map<int, list<Item*>*>* subgroupMap = dit->second;

			for (auto subit = subgroupMap->begin(); subit != subgroupMap->end(); ++subit) {
				cout << subit->first << ": ";
				for_each(subit->second->begin(), subit->second->end(), [](Item* item) {cout << item->getName() << " " << item->getDate().ToString() << endl << "    "; });
				cout << endl;
			}
		}
	}
	else {
		cout << "empty map" << endl;
	}
}

int Data::CountItems() const
{
	int elements = 0;
	if (datas.empty()) {
		return elements;
	}
	for (auto dit = datas.begin(); dit != datas.end(); ++dit) {
		map<int, list<Item*>*>* subGroupList = dit->second;

		for (auto subIt = subGroupList->begin(); subIt != subGroupList->end(); ++subIt) {
			for_each(subIt->second->begin(), subIt->second->end(), [&elements](Item *item) { elements++; });
		}
	}
	return elements;
}

map<int, list<Item*>*>* Data::GetGroup(char group) const 
{
	map<int, list<Item*>*>* groupMap;
	map<char, map<int, list<Item*>*>*>::const_iterator it = datas.find(group);
	it == datas.end() ? groupMap = nullptr : groupMap = it->second;
	return groupMap;
}

void Data::PrintGroup(char group) const
{
	map<int, list<Item*>*>* groupMap = GetGroup(group);

	if (!groupMap) {
		throw exception("error");
	}
	else {
		for (auto it = groupMap->begin(); it != groupMap->end(); ++it) {
			cout << it->first << ": " << endl;
			for_each(it->second->begin(), it->second->end(), [](Item* item) {cout << *item << endl; });
		}
	}
}

int Data::CountGroup(char group) const
{
	int groupElements = 0;
	map<int, list<Item*>*>* groupMap = GetGroup(group);
	if (groupMap) {
		for_each(groupMap->begin(), groupMap->end(), [&groupElements](pair<int, list<Item*>*> mapPair) {groupElements += mapPair.second->size(); });
	}
	return groupElements;
}


list<Item*>* Data::GetSubgroup(char group, int subgroup) const
{
    map<int, list<Item*>*>* groupMap = GetGroup(group);
	list<Item*>* subgroupList = nullptr;
	if (!groupMap) {
		return nullptr;
	}

	map<int, list<Item*>*>::const_iterator subgroupMap = groupMap->find(subgroup);

	subgroupMap == groupMap->end() ? subgroupList = nullptr : subgroupList = subgroupMap->second;

	return subgroupList;
}


void Data::PrintSubgroupByNames(char group, int subgroup) const
{
	list<Item*>* subgroupList = GetSubgroup(group, subgroup);
	if (!subgroupList){
		throw exception("error");
	}
	else {
		for_each(subgroupList->begin(), subgroupList->end(), [](Item* item) {cout << *item << endl; });
	}
	
}

void Data::PrintSubgroupByDates(char group, int subgroup) const
{
	list<Item*>* subgroupList = GetSubgroup(group, subgroup);
	if (!subgroupList) {
		throw exception("error");
	}
	else {
		auto sortByDates = [](Item* item, Item* other) {return item->getDate() < other->getDate(); };

		subgroupList->sort(sortByDates);
		for_each(subgroupList->begin(), subgroupList->end(), [](Item* item) {cout << *item << endl; });
	}
}

int Data::CountSubgroup(char group, int subgroup) const
{
	list<Item*>* subgroupList = GetSubgroup(group, subgroup);
	if (!subgroupList) {
		return 0;
	}
	return subgroupList->size();
}

Item* Data::GetItem(char group, int subgroup, string name) const
{
	list<Item*>* pSubgroupList = GetSubgroup(group, subgroup);
	if (!pSubgroupList) {
		return nullptr;
	}
	auto predicate = [&name](Item* item) -> bool {return item->getName() == name; };
	list<Item*>::iterator element = find_if(pSubgroupList->begin(), pSubgroupList->end(), predicate);
	if (element == pSubgroupList->end()) {
		return nullptr;
	}
	return *element;
}

void Data::PrintItem(char group, int subgroup, string name) const
{
	Item* item = GetItem(group, subgroup, name);
	if (item) {
		cout << endl << "Found: " << *item << endl;
	}
	else {
		throw exception("error");
	}
}
Item* Data::InsertItem(char group, int subg, string name, Date date)
{
	if (GetItem(group, subg, name) && GetItem(group, subg, name)->getDate() == date) {
		cout << "The item exist" << endl;
		return nullptr;
	}

	Item* pItem = new Item(group, subg, name, date);

	list<Item*>* subgroupList = GetSubgroup(group, subg);
	if (subgroupList) {
		subgroupList->push_back(pItem);
		subgroupList->sort();
	}
	else {
		subgroupList = new list<Item*>;
		subgroupList->push_back(pItem);
		map<int, list<Item*>*>* subgroupMap = GetGroup(group);

		if (subgroupMap) { 
			subgroupMap->insert(make_pair(pItem->GetSubgroup(), subgroupList));
		}
		else { 
			map<int, list<Item*>*>* subgroupMap = new map<int, list<Item*>*>;
			subgroupMap->insert(make_pair(pItem->GetSubgroup(), subgroupList));
			datas.insert(make_pair(pItem->GetGroup(), subgroupMap));
		}
	}
	return pItem;
}

list<Item*>* Data::InsertSubgroup(char group, int subgroup, initializer_list<Item*> items)
{
	map<int, list<Item*>*>* groupMap = GetGroup(group);
	if (subgroup < 0 || !groupMap || GetSubgroup(group, subgroup)) {
		cout << "error with the subgroup" << endl;
		return nullptr;
	}
	for_each(items.begin(), items.end(), [this, &groupMap, group, subgroup](Item* item) {InsertItem(group, subgroup, item->getName(), item->getDate()); });
	return GetSubgroup(group, subgroup);
}

map<int, list<Item*>*>* Data::InsertGroup(char group, initializer_list<int> subgroup, initializer_list<initializer_list<Item*>> items)
{
	map<char, map<int, list<Item*>*>*>::iterator groupIterator = datas.find(group);
	if (groupIterator != datas.end() || group < 'A' || group > 'Z' || subgroup.size() != items.size()) {
		cout << "Error with the group" << endl;
		return nullptr;
	}
	initializer_list<initializer_list<Item*>>::iterator itemListIt = items.begin();

	map<int, list<Item*>*>* pGroup = new map<int, list<Item*>*>;
	datas.insert(make_pair(group, pGroup));

	for_each(subgroup.begin(), subgroup.end(), [this, &group, &itemListIt](int subg) {InsertSubgroup(group, subg, *itemListIt); ++itemListIt; });

	return GetGroup(group);
}

bool Data::RemoveItem(char group, int subgroup, string name)
{
	list<Item*>* itemList = GetSubgroup(group, subgroup);
	if (!itemList) {
		cout << "subgroup not found" << endl;
		return false;
	}
	Item* toDelete = GetItem(group, subgroup, name);
	if (!toDelete) {
		cout << "item not found" << endl;
		return false;
	}

	itemList->erase(find_if(itemList->begin(), itemList->end(), [&name](Item* item) {return item->getName() == name; }));
	delete toDelete;
	if (itemList->empty()) {
		map<int, list<Item*>*>* subgroupMap = GetGroup(group);
		delete itemList;
		subgroupMap->erase(subgroupMap->find(subgroup));
		if (subgroupMap->empty()) {
			delete subgroupMap;
			datas.erase(datas.find(group));
		}
	}

	return true;
}

bool Data::RemoveSubgroup(char group, int subgroup)
{
	map<int, list<Item*>*>* subgroupMap = GetGroup(group);

	if (!subgroupMap) {
		cout << "Group not found" << endl;
		return false;
	}

	list<Item*>* itemList = GetSubgroup(group, subgroup);

	if (!itemList) {
		cout << "Subgroup not found" << endl;
		return false;
	}

	for_each(itemList->begin(), itemList->end(), [](Item* item) {delete item; });
	delete itemList;
	subgroupMap->erase(subgroup);

	if (subgroupMap->empty()) {
		delete subgroupMap;
		datas.erase(group);
	}

	return true;
}

bool Data::RemoveGroup(char group)
{
	map<int, list<Item*>*>* toDelete = GetGroup(group);
	if (!toDelete) {
		cout << "Group not found" << endl;
		return false;
	}

	for_each(toDelete->begin(), toDelete->end(), [this, &group](pair<int, list<Item*>*> pairToDelete) {
		list<Item*>* listToDelete = pairToDelete.second;
		for_each(listToDelete->begin(), listToDelete->end(), [](Item* item) {delete item; });
		delete listToDelete;
		});

	delete toDelete;
	datas.erase(group);
	return true;
}


