/* Citation and Sources...
Final Project Milestone MS54
Module: Perishable
Filename: Perishable.h
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
#ifndef SDDS_PERISHABLE_H
#define SDDS_PERISHABLE_H
#include "Item.h"
#include "Date.h"
namespace sdds
{
	class Perishable : public Item
	{
		Date m_expiry;
		char* m_handling;
	public:
		Perishable();
	//Rule of three
		Perishable(const Perishable& source);
		Perishable& operator=(const Perishable& source);
		~Perishable();
		const Date& expiry()const;//returns a constant reference of the expiry date
		int readSku(std::istream& istr);//SKU numbers between 10000 and 39999 (only SKUs starting with digits 1 to 3)-override
		std::ofstream& save(std::ofstream& ofstr)const;// override
		std::ifstream& load(std::ifstream& ifstr);// override
		std::ostream& display(std::ostream& ostr)const;// override
		std::istream& read(std::istream& istr);//override
	};

	
}
#endif // !SDDS_PERISHABLE_H
