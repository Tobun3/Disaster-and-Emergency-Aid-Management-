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
#ifndef SDDS_MENU_H
#define SDDS_MUNU_H

namespace sdds
{
	const int MAX_MENU_OPTION = 15;
	class Menu
	{
		char* m_menuContent{};
		unsigned int m_optionNumber{};
		void setEmpty();

	public:
		//Constructor
		Menu();
		Menu(const char* content, unsigned int optionNum = 0);
		//Rule of three
		Menu(const Menu& menu) = delete;
		Menu& operator=(const Menu& menu) = delete;
		~Menu();
		//End rule of three
		void set(const char* content, unsigned int optionNum);
		unsigned int run() const;
		void dealloc();
	};
}

#endif // !SDDS_MENU_H
