/* Citation and Sources...
Final Project Milestone MS54
Module: Perishable
Filename: Perishable.cpp
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
#include<cstring>
#include<string>
#include"Perishable.h"
using namespace std;
namespace sdds
{
	Perishable::Perishable()
	{
		//the m_expiry will have its own constructor in the date class
		m_handling = nullptr;

	}
	Perishable::Perishable(const Perishable& source): Item(source)
	{
		m_handling = nullptr;
		*this = source;
	}
	Perishable& Perishable::operator=(const Perishable& source)
	{
		if (this != &source)
		{
			Item::operator=(source);
			m_expiry = source.m_expiry;
			if (source.m_handling != nullptr)
			{
				delete[] m_handling;
				m_handling = new char[strlen(source.m_handling) + 1];
				strcpy(m_handling, source.m_handling);
			}
		}
		return *this;
	}
	//Destructor
	Perishable::~Perishable()
	{
		delete[] m_handling;
		m_handling = nullptr;
	}
	////returns a constant reference of the expiry date
	const Date& Perishable::expiry() const
	{
		return m_expiry;
	}
	int Perishable::readSku(std::istream& istr)
	{
		m_sku = ut.getint(10000, 39999, "SKU: "); // get integer start with 4 and the length is 5 digits
		return m_sku;
	}
	ofstream& Perishable::save(ofstream& ofstr) const
	{
		Date tempDate = m_expiry; // make a copy of the Date object so we can change the content and write it later
		if (m_state)
		{
			Date tempDate = m_expiry; // make a copy of the Date object so we can change the content and write it later
			Item::save(ofstr);// Call save of the base class
			ofstr << '\t';
			if (m_handling && m_handling[0] != '\0') ofstr << m_handling;
			ofstr << '\t';
			tempDate.formatted(false);
			ofstr << tempDate; // writes an unformatted copy of the expiry date
		}
		return ofstr;
	}
	ifstream& Perishable::load(ifstream& ifstr)
	{
		string str;
		delete[] m_handling;
		Item::load(ifstr);
		ifstr.ignore(1000, '\t');
		getline(ifstr, str, '\t');
		m_handling = new char[str.length() + 1];
		strcpy(m_handling, str.c_str());
		m_expiry.read(ifstr);
		ifstr.ignore(2000, '\n');
		if (!ifstr)
		{
			m_state = "Input file stream read(perishable) failed!"; // set the state of the item
		}
		return ifstr;
	}
	std::ostream& Perishable::display(std::ostream& ostr) const
	{
		if (m_sku != 0)
		{
			if (m_state)
			{
				if (Linear())
				{
					Item::display(ostr);
					if (m_handling != nullptr && m_handling[0] != '\0') // if there is a handling instruction put *
					{
						ostr << '*';
					}
					else
					{
						ostr << ' ';
					}
					ostr << m_expiry;
				}
				else
				{
					ostr << "Perishable ";
					Item::display(ostr);
					ostr << "Expiry date: ";
					ostr << m_expiry << endl;
					if (m_handling != nullptr && m_handling[0] != '\0')
					{
						ostr << "Handling Instructions: " << m_handling << endl;
					}
				}
			}
			else
			{
				ostr << m_state;
			}
		}
		return ostr;
	}
	std::istream& Perishable::read(std::istream& istr)
	{
		string str;
		Item::read(istr);
		delete[] m_handling;
		m_handling = nullptr;
		cout << "Expiry date (YYMMDD): ";
		m_expiry.read(istr);
		istr.ignore(2000, '\n');
		cout << "Handling Instructions, ENTER to skip: ";
		if (istr.peek() != '\n')
		{
			getline(istr, str, '\n');
			m_handling = new char[str.length() + 1];
			strcpy(m_handling, str.c_str());
		}if (!istr)
		{
			m_state = "Perishable console date entry failed!";
		}
		return istr;
	}
}