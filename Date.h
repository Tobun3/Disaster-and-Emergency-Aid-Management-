/* Citation and Sources...
Final Project Milestone MS54
Module: Date
Filename: Date.h
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
#ifndef SDDS_DATE_H
#define SDDS_DATE_H
#include"Status.h"

namespace sdds
{
	const int MAXIMUM_YEAR_VALUE(2030);
	class Date
	{
		int m_year;
		int m_month;
		int m_day;
		Status m_state;
		bool m_formatted = true;
		bool validate(); //This function validates the year, month and day, in the following order (and it stops if an invalid value is found)
		int uniqueDate(const int& year, const int& month,const int& day) const;// return a unique value integer tied to the date
	public:
		//Constructors
		Date();
		Date(int year, int month, int day);

		//operator overloads for comparison
		bool operator==(const Date& D) const;
		bool operator!=(const Date& D) const;
		bool operator>(const Date& D) const;
		bool operator<(const Date& D) const;
		bool operator>=(const Date& D) const;
		bool operator<=(const Date& D) const;
		Status& state(); // return the state of data
		Date& formatted(bool flag = false);
		operator bool() const; // return the state of the object 
		std::ostream& write(std::ostream& ostr) const;
		std::istream& read(std::istream& istr);
	};
	std::ostream& operator<<(std::ostream& ostr, const Date& D);
	std::istream& operator>>(std::istream& istr, Date& D);
}
#endif // !SDDS_DATE_H
