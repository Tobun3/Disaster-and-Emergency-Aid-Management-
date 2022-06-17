/* Citation and Sources...
Final Project Milestone MS54
Module: AidMan
Filename: AidMan.cpp
Version 1.0
Author	Techatat Obun
Email : tobun@myseneca.ca
Student ID : 108135211
OOP244 NCC
Revision History
-----------------------------------------------------------
Date		Reason
2022/04/05  First submission for MS54
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------*/
#ifndef SDDS_AID_MAN_H
#define SDDS_AID_MAIN_H
#include "Menu.h"
#include "Perishable.h"
namespace sdds
{
	const int sdds_max_num_items = 100;
	class AidMan
	{
		char* m_filename{};
		Menu m_menu;
		iProduct* m_iProduct[sdds_max_num_items]{};
		int m_numberOfiProduct{};
		unsigned int menu()const; 
		void save();
		void deallocate();
		bool load(); //Loads data records from a data file and returns true if at least one record is loaded.


	public:
		AidMan(); // only one default constructor for this class
		//Rule of three
		AidMan(const AidMan& source) = delete;
		AidMan& operator=(const AidMan& source) = delete;
		~AidMan();
		void run();
		int list(const char* sub_desc = nullptr);// list all iProduct items
		void sort(); // sort the Sorts the items in the iProduct Pointers array, based on difference between quantity needed and quantity on hand in descending order.
		int search(int sku) const; //Loops through all the iProduct Pointers elements and if the SKU is a match it will return the index, otherwise it will return -1
		void add(); // add item to iProduct
		void remove(int index);
		void ship();
		void update();
	};

}
#endif // !SDDS_AID_MAN_H
