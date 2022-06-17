/* Citation and Sources...
Final Project Milestone MS54
Module: iProduct
Filename: iProduct.cpp
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
#include<iostream>
#include"iProduct.h"
namespace sdds
{
	std::ostream& operator<<(std::ostream& ostr, const iProduct& P)
	{
		return P.display(ostr);
	}
	std::istream& operator>>(std::istream& istr, iProduct& P)
	{
		return P.read(istr);
	}
	iProduct::~iProduct()
	{
		//empty body
	}
}