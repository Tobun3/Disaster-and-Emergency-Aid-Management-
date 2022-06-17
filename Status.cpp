
/* Citation and Sources...
Final Project Milestone MS54
Module: Status
Filename: Status.cpp
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
#include <iostream>
#include "Status.h"
using namespace std;

namespace sdds
{
	void Status::setEmpty()
	{
		m_errDesc = nullptr;
		m_errCode = 0;
	}
	//Constructors
	Status::Status()
	{
		setEmpty();
	}

	Status::Status(const char* message)
	{
		ut.alocpy(m_errDesc, message);
		m_errCode = 0;
	}
	//Rule of three
	Status::Status(const Status& state)
	{
		m_errDesc = nullptr;
		*this = state;
	}
	Status& Status::operator = (const Status& state)
	{
		if (this != &state)
		{
			ut.alocpy(m_errDesc, state.m_errDesc);
			m_errCode = state.m_errCode;
		}
		return *this;
	}
	Status::~Status()
	{
		clear();
	}
	//Assignment operator
	Status& Status::operator=(const char* desc)
	{
		ut.alocpy(m_errDesc, desc);
		return *this;
	}
	Status& Status::operator=(int code)
	{
		m_errCode = code;
		return *this;
	}
	Status& Status::set(const char* desc, int code)
	{
		ut.alocpy(m_errDesc, desc);
		m_errCode = code;
		return *this;
	}
	//Casting 
	Status::operator int() const
	{
		return m_errCode;
	}
	Status::operator const char* () const
	{
		return m_errDesc;
	}
	Status::operator bool() const
	{
		return m_errDesc == nullptr;
	}
	// Clear method
	Status& Status::clear()
	{
		delete[] m_errDesc;
		m_errDesc = nullptr;
		m_errCode = 0;
		return *this;
	}
	ostream& operator<<(ostream& ostr, const Status& state)
	{
		if (!state)
		{
			if((int)state != 0)
				ostr << "ERR#" << (int)state << ": " << (const char*)state;
			else
				ostr << (const char*)state;
		}
		return ostr;
	}
}
