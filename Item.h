/* Citation and Sources...
Final Project Milestone MS54
Module: Item
Filename: Item.cpp
Version 1.0
Author	Techatat Obun
Email : tobun@myseneca.ca
Student ID : 108135211
OOP244 NCC
Revision History
-----------------------------------------------------------
Date		Reason
2022/04/05  First submission of ms54
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------*/
#ifndef SDDS_ITEM_H
#define SDDS_ITEM_H
#include<iostream>
#include"iProduct.h"
#include"Status.h"
namespace sdds
{
	class Item : public iProduct
	{
		double m_price;
		int m_qty;
		int m_qtyNeeded;
		char* m_description;
		bool m_linear;
		void dealloc();// deallocate memory for m_description
		void deallocAndCopy(const char* desc);// deallocate memory and  set the m_description
	protected:
		Status m_state;
		int m_sku;
		bool Linear()const;// return the linear
	public:
		Item();
		//Rule of three
		Item(const Item& I);
		Item& operator = (const Item& I);
		~Item();
		//End rule of three
		operator double()const; // return price
		operator bool()const; // returns if the iProduct is in a good state
		int qtyNeeded()const;// returns the number of products needed
		int qty()const; // retuns the quantity on hand
		int operator-=(int qty); //to reduce the quantity on hand
		int operator+=(int qty); // to increase the quantity on hand
		void linear(bool isLinear);// determines if the iProduct is displayed in a linear format or descriptive format
		void clear();//sets the state of the Item object back to good, by resetting the state attribute.
		bool operator==(int sku)const;// return true if the sku is a match to the iProduct's sku
		bool operator==(const char* description)const;// returns true if the description is found in the iPorduct's description
		std::ofstream& save(std::ofstream& ofstr)const;// saves the iProduct into a file
		std::ifstream& load(std::ifstream& ifstr);// loads an iProduct from a file
		std::ostream& display(std::ostream& ostr)const ;// displays the iProduct on the screen
		int readSku(std::istream& istr);// displays the iProduct on the screen to read the Stock-Keeping Unit from console before main data entry
		std::istream& read(std::istream& istr);// reads the iProduct from the console
	};
}
#endif // !SDDS_ITEM_H
