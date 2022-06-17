/* Citation and Sources...
Final Project Milestone MS54
Module: Status
Filename: Status.h
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
#ifndef SDDS_STATUS_H
#define SDDS_STATUS_H
#include <iostream>
#include "Utils.h"

namespace sdds
{
	class Status
	{
		char* m_errDesc;
		int m_errCode;
		void setEmpty();
	public:
		//Constructors
		Status();
		Status(const char* message);
		//Rule of three
		Status(const Status& state);
		Status& operator = (const Status& state);
		~Status();
		//Assignment operator
		Status& operator=(const char* desc);
		Status& operator=(int code);
		Status& set(const char* desc, int code);
		//Casting
		operator int() const;// return an error code
		operator const char* () const;// return an error description
		operator bool() const; // return true if the error description is null
		Status& clear(); // safely deallocates the description and sets the code to zero
	};
	std::ostream& operator <<(std:: ostream& ostr, const Status& state);
}
#endif // !SDDS_STATUS_H
