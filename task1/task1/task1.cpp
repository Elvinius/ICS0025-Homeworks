#pragma once
#include "Data.h"
#include <iostream>

using namespace std;

int main()
{
	Data data(300);
	int user_value = 0;
	printf("Check our bird catalog and select the respective number to perform your requested operation:\n");
	while (user_value != 20) {

		printf("\nCatalog:\n1) Print all the birds\n2) Count all the birds\n3) Print all the birds in the selected group\n4) Count the birds in the selected group\n5) Print the birds in the selected subgroup ordered by the name\n6) Print the birds in a selected subgroup ordered by dates\n7) Count the birds in a selected subgroup\n8) Print the selected bird\n9) Insert a bird\n10) Insert a subgroup\n11) Insert a group\n12) Delete the bird\n13) Delete a subgroup\n14) Delete a group\n20) Exit\n");
		cin >> user_value;
		user_value = (int)(user_value);
		switch (user_value)
		{
		case 1:
			data.PrintAll();
			break;
		case 2:{
			cout << "Counted items: " << data.CountItems() << endl;
			break; }
		case 3: {
			char group;
			printf("Select group: ");
			cin >> group;
			try {
				data.PrintGroup(group);
			}
			catch (exception & e) {
				cout << e.what() << endl;
			}
			break; }
		case 4: {
			char group;
			printf("Select group: ");
			cin >> group;
			cout << data.CountGroup(group) << endl;
			break; }
		case 5: {
			char group;
			printf("Select group: ");
			cin >> group;
			int subgroup;
			printf("Select subgroup: ");
			cin >> subgroup;
			try {
				data.PrintSubgroupByNames(group, subgroup);
			}
			catch(exception &e){
				cout << e.what() << endl;
			}
			break; }
		case 6: {
			char group;
			printf("Select group: ");
			cin >> group;
			int subgroup;
			printf("Select subgroup: ");
			cin >> subgroup;
			try {
				data.PrintSubgroupByDates(group, subgroup);
			}
			catch (exception & e) {
				cout << e.what() << endl;
			}
			  break;}
		case 7: {
			char group;
			printf("Select group: ");
			cin >> group;
			int subgroup;
			printf("Select subgroup: ");
			cin >> subgroup;
			cout << data.CountSubgroup(group, subgroup) << endl;
			break; }
		case 8: {
			char group;
			printf("Select group: ");
			cin >> group;
			int subgroup;
			printf("Select subgroup: ");
			cin >> subgroup;
			cout << "Select name: ";
			cin.ignore();
			string name;
			getline(cin, name);
			try { 
				data.PrintItem(group, subgroup, name);
			}
			catch (exception & e) {
				cout << e.what() << endl;
			}
			break;
		}
		case 9: {
			char group;
			printf("Select group: ");
			cin >> group;
			int subgroup;
			printf("Select subgroup: ");
			cin >> subgroup;
			string name;
			printf("Select name: ");
			cin.ignore();
			getline(cin, name);
			int day;
			printf("Select day: ");
			cin >> day;
			int month;
			printf("Select month: ");
			cin >> month;
			int year;
			printf("Select year: ");
			cin >> year;
			Date date(day, month, year);
			data.InsertItem(group, subgroup, name, date);
			break;
		}
		case 10: {
			char group;
			int subgroup;
			Date date;
			printf("Select group: ");
			cin >> group;
			printf("Select subgroup: ");
			cin >> subgroup;
			Item* pItem1 = new Item(group, subgroup, string(""), date.CreateRandomDate(Date(1, 1, 2000), Date(31, 12, 2020)));
			Item* pItem2 = new Item(group, subgroup, string(""), date.CreateRandomDate(Date(1, 1, 2000), Date(31, 12, 2020)));
			Item* pItem3 = new Item(group, subgroup, string(""), date.CreateRandomDate(Date(1, 1, 2000), Date(31, 12, 2020)));
			initializer_list<Item*> initList{ pItem1, pItem2, pItem3 };
			data.InsertSubgroup(group, subgroup, initList);
			break;
		}
		case 11: {
			char group;
			int subgroup;
			int subgroup1;
			int subgroup2;
			int subgroup3;
			Date date;
			printf("Select group: ");
			cin >> group;
			
			printf("Select the subgroup of the first three items: ");
			cin >> subgroup;
			Item* pItem1 = new Item(group, subgroup, string(""), date.CreateRandomDate(Date(1, 1, 2000), Date(31, 12, 2020)));
			Item* pItem2 = new Item(group, subgroup, string(""), date.CreateRandomDate(Date(1, 1, 2000), Date(31, 12, 2020)));
			Item* pItem3 = new Item(group, subgroup, string(""), date.CreateRandomDate(Date(1, 1, 2000), Date(31, 12, 2020)));
			initializer_list<Item*> initList1{ pItem1, pItem2, pItem3 };
			printf("Select the subgroup of the other three items: ");
			cin >> subgroup1;
			Item* pItem4 = new Item(group, subgroup1, string(""), date.CreateRandomDate(Date(1, 1, 2000), Date(31, 12, 2020)));
			Item* pItem5 = new Item(group, subgroup1, string(""), date.CreateRandomDate(Date(1, 1, 2000), Date(31, 12, 2020)));
			Item* pItem6 = new Item(group, subgroup1, string(""), date.CreateRandomDate(Date(1, 1, 2000), Date(31, 12, 2020)));
			initializer_list<Item*> initList2{ pItem3, pItem4, pItem5 };
			printf("Select the subgroup of the other three items: ");
			cin >> subgroup2;
			Item* pItem7 = new Item(group, subgroup2, string(""), date.CreateRandomDate(Date(1, 1, 2000), Date(31, 12, 2020)));
			Item* pItem8 = new Item(group, subgroup2, string(""), date.CreateRandomDate(Date(1, 1, 2000), Date(31, 12, 2020)));
			Item* pItem9 = new Item(group, subgroup2, string(""), date.CreateRandomDate(Date(1, 1, 2000), Date(31, 12, 2020)));
			initializer_list<Item*> initList3{ pItem7, pItem8, pItem9 };
			printf("Select the subgroup of the last three items: ");
			cin >> subgroup3;
			Item* pItem10 = new Item(group, subgroup3, string(""), date.CreateRandomDate(Date(1, 1, 2000), Date(31, 12, 2020)));
			Item* pItem11 = new Item(group, subgroup3, string(""), date.CreateRandomDate(Date(1, 1, 2000), Date(31, 12, 2020)));
			Item* pItem12 = new Item(group, subgroup3, string(""), date.CreateRandomDate(Date(1, 1, 2000), Date(31, 12, 2020)));
			initializer_list<Item*> initList4{ pItem10, pItem11, pItem12 };
			initializer_list<int> initInt = { subgroup, subgroup1, subgroup2, subgroup3 };
			initializer_list<initializer_list<Item*>> itemList = {initList1, initList2, initList3, initList4 };
			data.InsertGroup(group, initInt, itemList);
			break;
		}
		case 12: {
			char group;
			printf("Select group: ");
			cin >> group;
			int subgroup;
			printf("Select subgroup: ");
			cin >> subgroup;
			string name;
			printf("Select name: ");
			cin.ignore();
			getline(cin, name);
			data.RemoveItem(group, subgroup, name);
			break;
		}
		case 13: {
			char group;
			printf("Select group: ");
			cin >> group;
			int subgroup;
			printf("Select subgroup: ");
			cin >> subgroup;
			data.RemoveSubgroup(group, subgroup);
			break;
		}
		case 14: {
			char group;
			printf("Select group: ");
			cin >> group;
			data.RemoveGroup(group);
			break;
		}
		case 20: {
			break;
		}
		default:
			printf("Number not valid");
			user_value = 0;
			break;
		}

	}

	return 0;

}