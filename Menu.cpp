
/* Citation and Sources...
Final Project Milestone MS54
Module: Menu
Filename: Menu.cpp
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
#include"Menu.h"
#include"Utils.h"
using namespace std;
namespace sdds
{
	void Menu::setEmpty()
	{
		dealloc();
		m_optionNumber = 0;
	}

	void Menu::dealloc()
	{
		delete[] m_menuContent;
		m_menuContent = nullptr;
	}
	//Constructors
	Menu::Menu()
	{
		m_menuContent = nullptr;
		setEmpty();
	}
	Menu::Menu(const char* content, unsigned int optionNum)
	{
		set(content, optionNum);
	}
	Menu::~Menu()
	{
		dealloc();
	}
	void Menu::set(const char* content, unsigned int optionNum)
	{
		m_menuContent = nullptr;
		ut.alocpy(m_menuContent, content);
		m_optionNumber = optionNum;
	}
	unsigned int Menu::run() const
	{
		unsigned int val;
		cout << m_menuContent;
		cout << "0- Exit" << endl;
		val = ut.getint(0, m_optionNumber, "> ");
		return val;
	}
}
