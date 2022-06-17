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
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<fstream>
#include<string>
#include<cstring>
#include<math.h>
#include"Item.h"
#include"Utils.h"

using namespace std;
namespace sdds
{
	void Item::dealloc()
	{
		delete[] m_description;
		m_description = nullptr;
	}
	void Item::deallocAndCopy(const char* desc)
	{
		delete[] m_description;
		m_description = nullptr;
		m_description = new char[strlen(desc) + 1];
		strcpy(m_description, desc);
	}
	bool Item::Linear() const
	{
		return m_linear;
	}
	Item::Item()
	{
		m_price = 0;
		m_qty = m_qtyNeeded = m_sku = 0;
		m_linear = false;
		m_description = nullptr;
	}
	Item::Item(const Item& I)
	{
		m_description = nullptr;
		*this = I;
		
	}
	Item& Item::operator=(const Item& I)
	{
		if (this != &I)
		{
			m_price = I.m_price;
			m_qty = I.m_qty;
			m_qtyNeeded = I.m_qtyNeeded;
			m_sku = I.m_sku;
			m_linear = I.m_linear;
			m_state = I.m_state;
			if (I.m_description != nullptr)
			{
				deallocAndCopy(I.m_description);
			}

		}
		return *this;
	}
	Item::~Item()
	{
		dealloc();
	}
	// return price
	Item::operator double() const
	{
		return m_price;
	}
	// returns if the iProduct is in a good state
	Item::operator bool() const
	{
		return m_state && m_sku != 0;
	}
	// returns the number of products needed
	int Item::qtyNeeded() const
	{
		return m_qtyNeeded;
	}
	// retuns the quantity on hand
	int Item::qty() const
	{
		return m_qty;
	}
	//to reduce the quantity on hand
	int Item::operator-=(int qty)
	{
		m_qty = m_qty - qty;
		return m_qty > 0? m_qty : 0;
	}
	// to increase the quantity on hand
	int Item::operator+=(int qty)
	{
		return m_qty = m_qty + qty;;
	}
	// determines if the iProduct is displayed in a linear format or descriptive format
	void Item::linear(bool isLinear)
	{
		m_linear = isLinear;
	}
	//sets the state of the Item object back to good, by resetting the state attribute.
	void Item::clear()
	{
		m_state.clear();
	}
	// return true if the sku is a match to the iProduct's sku
	bool Item::operator==(int sku) const
	{
		return m_sku==sku;
	}
	// returns true if the description is found in the iPorduct's description
	bool Item::operator==(const char* description) const
	{
		char* found = nullptr;
		if (m_description != nullptr && description != nullptr)
		{
			found = strstr(m_description, description);
		}
		return found != nullptr;
	}
	// saves the iProduct into a file
	ofstream& Item::save(ofstream& ofstr) const
	{
		if (m_state)
		{
			ofstr << m_sku << '\t' << m_description << '\t' << m_qty << '\t' << m_qtyNeeded << '\t';
			ofstr.setf(ios::fixed);
			ofstr.precision(2);
			ofstr << m_price;
		}
		return ofstr;
	}
	// loads an iProduct from a file
	ifstream& Item::load(ifstream& ifstr)
	{
		int sku, qty, qtyNeeded;
		double price;
		string desc;
		ifstr >> sku;
		ifstr.get();// extract tab
		getline(ifstr, desc, '\t');
		ifstr >> qty;
		ifstr.get();// extract tab
		ifstr >> qtyNeeded;
		ifstr.get();// extract tab
		ifstr >> price;
		if(!ifstr)
		{
			ifstr.ignore(1000, '\n');
			m_state = "Input file stream read failed!"; // set the state of the item
		}
		else
		{
			m_sku = sku;
			m_qty = qty;
			m_qtyNeeded = qtyNeeded;
			m_price = price;
			deallocAndCopy(desc.c_str());
		}
		return ifstr;
	}
	ostream& Item::display(ostream& ostr) const
	{
		if (m_state)
		{
			if (m_linear) //If in linear format
			{
				// ##### | AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA | #### | #### | ####.## |
				ostr << " " << m_sku << " | ";
				ostr.fill(' ');
				if (strlen(m_description) > 35) // if the length is more than 35 print only 35 characters
				{
					for (int i = 0; i < 35; i++)
					{
						ostr << m_description[i];
					}
				}
				else
				{
					ostr.width(35);
					ostr.setf(ios::left);
					ostr << m_description;
				}
				ostr.unsetf(ios::left);
				ostr << " | ";
				ostr.width(4);
				ostr << m_qty;
				ostr << " | ";
				ostr.width(4);
				ostr << m_qtyNeeded;
				ostr << " | ";
				ostr.width(7);
				ostr.setf(ios::fixed);
				ostr.precision(2);
				ostr << m_price << " |";
			}
			else
			{
			  /*AMA Item:
				SKU: The description is printed fully
				Quantity Needed: ###
				Quantity Available: ###
				Unit Price: $####.##
				Needed Purchase Fund: $##.##*/
				ostr << "AMA Item:" << endl;
				ostr << m_sku<< ": " << m_description << endl;
				ostr << "Quantity Needed: " << m_qtyNeeded << endl;
				ostr << "Quantity Available: " << m_qty << endl;
				ostr << "Unit Price: $";
				ostr.setf(ios::fixed);
				ostr.precision(2);
				ostr << m_price << endl;
				ostr << "Needed Purchase Fund: $";
				ostr.setf(ios::fixed);
				ostr.precision(2);
				ostr << double(m_qtyNeeded - m_qty) * m_price << endl; // Need fund is the amount needed minus what we have on hand x by unit price
			}
			
		}else{
			ostr << m_state; // print the state of item
		}
		return ostr;
	}
	// displays the iProduct on the screen to read the Stock-Keeping Unit from console before main data entry
	int Item::readSku(std::istream& istr)
	{
		
		m_sku = ut.getint(40000, 99999, "SKU: "); // get integer start with 4 and the length is 5 digits
		return m_sku;
	}
	istream& Item::read(istream& istr)
	{
		string desc;
		clear();
		cout << "AMA Item:" << endl;
		cout << "SKU: "<< m_sku << endl;
		cout << "Description: ";
		istr.ignore(2000, '\n');
		getline(istr,desc,'\n');
		cout << "Quantity Needed: ";
		m_qtyNeeded = ut.getint(1,9999);
		cout << "Quantity On Hand: ";
		m_qty = ut.getint(0,m_qtyNeeded);
		cout << "Unit Price: $";
		m_price = ut.getDouble(0, 9999);
		istr.ignore(2000, '\n');
		if (!istr)
		{
			istr.ignore(1000, '\n');
			m_state = "Console entry failed!"; // set the state of the item
		}
		else
		{
			deallocAndCopy(desc.c_str());
		}
		return istr;
	}
}