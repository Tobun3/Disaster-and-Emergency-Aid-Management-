/* Citation and Sources...
Final Project Milestone MS54
Module: Date
Filename: Date.cpp
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
#include <iostream>
#include "Date.h"
using namespace std;

namespace sdds
{
	//This function validates the year, month and day, in the following order(and it stops if an invalid value is found)
	bool Date::validate()
	{
		bool valid = true;
		int currentYear ,  currentMonth, currentDay;
		ut.getSystemDate(&currentYear, &currentMonth, &currentDay);
		int maxDay;
		maxDay = ut.daysOfMon(m_month, m_year);

		if (m_month < 1 || m_month > 12) maxDay = 31;

		if (m_day >= 1 && m_day <= maxDay)
		{
			if (m_month >= 1 && m_month <= 12)
			{
				if (m_year >= currentYear && m_year <= MAXIMUM_YEAR_VALUE)
				{
					valid = true;
				}
				else
				{
					m_state.set("Invalid year in date", 1);
					valid = false;
				}
			}
			else
			{
				m_state.set("Invalid month in date", 2);
				valid = false;
			}
		}
		else
		{
			m_state.set("Invalid day in date", 3);
			valid = false;
		}

		return valid;
	}
	int Date::uniqueDate(const int& year,const int& month,const int& day) const
	{
		return year * 372 + month * 31 + day;
	}
	Date::Date()
	{
		ut.getSystemDate(&m_year, &m_month, &m_day);
	}
	Date::Date(int year, int month,int day)
	{
		m_year = year;
		m_month = month;
		m_day = day;
		validate();
	}
	bool Date::operator==(const Date& D) const
	{
		return uniqueDate(m_year, m_month, m_day) == uniqueDate(D.m_year, D.m_month, D.m_day);
	}
	bool Date::operator!=(const Date& D) const
	{
		return uniqueDate(m_year, m_month, m_day) != uniqueDate(D.m_year, D.m_month, D.m_day);
	}
	bool Date::operator>(const Date& D)const
	{
		return uniqueDate(m_year, m_month, m_day) > uniqueDate(D.m_year, D.m_month, D.m_day);
	}
	bool Date::operator<(const Date& D)const
	{
		return uniqueDate(m_year, m_month, m_day) < uniqueDate(D.m_year, D.m_month, D.m_day);
	}
	bool Date::operator>=(const Date& D)const
	{
		return uniqueDate(m_year, m_month, m_day) >= uniqueDate(D.m_year, D.m_month, D.m_day);
	}
	bool Date::operator<=(const Date& D)const
	{
		return uniqueDate(m_year, m_month, m_day) <= uniqueDate(D.m_year, D.m_month, D.m_day);
	}
	Status& Date::state() 
	{
		return m_state;
	}
	Date& Date::formatted(bool flag)
	{
		m_formatted = flag;
		return *this;
	}
	Date::operator bool() const
	{
		return this->m_state;
	}
	ostream& Date::write(ostream& ostr) const
	{
		
		if (m_formatted)
		{
			ostr << m_year <<"/";
			ostr.fill('0');
			ostr.width(2);
			ostr << m_month << "/";
			ostr.fill('0');
			ostr.width(2);
			ostr<< m_day;
		}
		else
		{
			ostr << m_year % 100;
			ostr.fill('0');
			ostr.width(2);
			ostr << m_month;
			ostr.fill('0');
			ostr.width(2);
			ostr << m_day;
		}
		return ostr;
	}
	std::istream& Date::read(std::istream& istr)
	{
		if (istr)
		{
			int val = 0;
			istr >> val;
			if (val != 0)
			{
				if (val <= 99)
				{
					ut.getSystemDate(&m_year);
					m_day = val;
					m_month = 0;
				}
				else if (val > 99 && val < 9999)
				{
					m_day = val % 100;
					m_month = val / 100;
					ut.getSystemDate(&m_year);
				}
				else if (val > 9999 && val < 999999)
				{
					m_day = val % 100;
					m_month = (val / 100) % 100;
					m_year = (val / 10000) + 2000;
				}
				if (!validate())
				{
					istr.setstate(ios::badbit);
				}
			}
			else
			{
				cout << "Invalid date value";
			}
		}

		return istr;
	}
	ostream& operator<<(ostream& ostr, const Date& D)
	{
		return D.write(ostr);
	}
	std::istream& operator>>(std::istream& istr, Date& D)
	{
		return D.read(istr);
	}
}