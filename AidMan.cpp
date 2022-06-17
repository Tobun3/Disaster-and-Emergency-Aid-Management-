/* Citation and Sources...
Final Project Milestone MS54
Module: AidMan
Filename: AidMan.cpp
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
#include<fstream>
#include"AidMan.h"
#include"Date.h"
using namespace std;

namespace sdds
{
	
	
	unsigned int AidMan::menu() const
	{	
		unsigned int val = 0;
		Date date;
		cout << "Aid Management System"<< endl;
		cout << "Date: " << date << endl;
		cout << "Data file: "; m_filename == nullptr ? cout << "No file" : cout << m_filename;
		cout << endl;
		cout << "---------------------------------" << endl;
		val = m_menu.run();

		return val;
	}

	void AidMan::save()
	{
		if (m_filename)
		{
			ofstream fout(m_filename);
			for (int i = 0; i < m_numberOfiProduct; i++)
			{
				m_iProduct[i]->save(fout);
				fout << endl;
			}
			fout.close();
		}
	}

	void AidMan::deallocate()
	{
		for(int i = 0; i < m_numberOfiProduct; i++) delete m_iProduct[i];
		delete[] m_filename;
		m_filename = nullptr;
		m_numberOfiProduct = 0;
	}

	bool AidMan::load()
	{
		bool isLoaded = false;
		int option = 0;
		save();
		deallocate();
		cout << "Enter file name: ";
		cin.ignore(2000, '\n');
		m_filename = ut.getCStr(cin);
		ifstream fin(m_filename);
		if (!fin.is_open())
		{
			fin.close();
			cout << "Failed to open " << m_filename << " for reading!" << endl;
			cout << "Would you like to create a new data file?" << endl;
			cout << "1- Yes!\n0- Exit\n>";
			option = ut.getint(0, 1);
			if (option == 1)
			{
				cout << "Enter file name: ";
				cin.ignore(2000, '\n');
				m_filename = ut.getCStr(cin);
				fin.open(m_filename);
				fin.close();
			}

		}
		else
		{
			char tempSku ;
			while (fin)
			{
				tempSku = fin.peek();
				if (tempSku >= '1' && tempSku < '4')
				{
					m_iProduct[m_numberOfiProduct] = new Perishable;
					m_iProduct[m_numberOfiProduct]->load(fin);

				}
				else if (tempSku >= '4' && tempSku <= '9')
				{
					m_iProduct[m_numberOfiProduct] = new Item;
					m_iProduct[m_numberOfiProduct]->load(fin);
					fin.ignore(1000, '\n');
				}
				else
				{
					fin.setstate(ios::failbit);
				}

				if (m_iProduct[m_numberOfiProduct])
				{
					m_numberOfiProduct++;
					isLoaded = true;
				}
				else
				{
					delete m_iProduct[m_numberOfiProduct];
				}
			}
		}

		cout << m_numberOfiProduct << " records loaded!" << "\n\n";
		fin.close();
		return isLoaded;
	}

	AidMan::AidMan()
	{
		m_filename = nullptr;
		m_menu.set("1- List Items\n2- Add Item\n3- Remove Item\n4- Update Quantity\n5- Sort\n6- Ship Items\n7- New/Open Aid Database\n---------------------------------\n", 7);
	}

	AidMan::~AidMan()
	{
		delete[] m_filename;
		m_filename = nullptr;
		m_menu.dealloc();
	}

	void AidMan::run()
	{
		bool flag = true;
		unsigned int option = 0;
		do
		{
			option = menu();
			if (option != 0 && m_filename == nullptr && option != 7) option = 7;
			switch (option)
			{
				case 1: 
					cout << "\n****List Items****\n";
					list();
					break;
				case 2: 
					cout << "\n****Add Item****\n";
					add();
					break;
				case 3:	
					cout << "\n****Remove Item****\n";
					cout << "Item description: ";

					char* chTemp;
					cin.ignore(1000, '\n');
					chTemp = ut.getCStr(cin);
					if (list(chTemp) > 0) // if matching desc it will list and return the number of matching
					{
						int idx;
						if ((idx = search(ut.getint(10000, 99999, "Enter SKU: "))) != -1)// if the sku found in iProduct
						{
							cout << "Following item will be removed: " << endl;
							m_iProduct[idx]->linear(false);
							cout << *m_iProduct[idx];

							cout << "\nAre you sure?\n1- Yes!\n0- Exit\n";
							int select = ut.getint(0, 1, "> ");
							switch (select)
							{
							case 1:
								remove(idx);
								cout << "Item removed!\n" << endl;
								break;
							case 0:
								cout << "Aborted!\n" << endl;
								break;
							}
						}
						else
						{
							cout << "SKU not found!" << endl;
						}
					}
					delete[] chTemp; // deallocate to prevent memory leak***
					chTemp = nullptr;
					break;
				case 4: 
					cout << "\n****Update Quantity****\n";
					update();
					break;
				case 5: 
					cout << "\n****Sort****\n" ;
					sort(); 
					cout << endl;
					break;
				case 6: 
					cout << "\n****Ship Items****\n";
					ship();
					cout<<endl;
					break;
				case 7: 
					cout << "\n****New/Open Aid Database****\n";
						load();
					break;
				case 0: 
					flag = false;
					cout << "Exiting Program!" << endl;
					break;
			}

		} while (flag);
		save();
		deallocate();
	}
	// list the iProduct
	int AidMan::list(const char* sub_desc)
	{
		int i = 0;
		int line;
		if (sub_desc == nullptr) //if sub_desc is null, print all the items in a linear format.
		{
			cout << " ROW |  SKU  | Description                         | Have | Need |  Price  | Expiry" << endl;
			cout << "-----+-------+-------------------------------------+------+------+---------+-----------" << endl;
			for (i = 0; i < m_numberOfiProduct; i++)
			{
				cout.width(4);
				cout.fill(' ');
				cout << i+1 << " |";
				m_iProduct[i]->linear(true);
				cout << *m_iProduct[i]<<endl;
			}
			cout << "-----+-------+-------------------------------------+------+------+---------+-----------" << endl;
			cout << "Enter row number to display details or <ENTER> to continue:" << endl;;
			cout << "> ";
			i = m_numberOfiProduct;
			cin.ignore(2000, '\n');
			if (cin.peek() != '\n') // see if user enter if yes go back to the menu
			{
				line = ut.getint(1, i);
				cout << *m_iProduct[line-1] << endl;
			}
			else
			{
				cout << endl;
			}
		}
		else //if sub_desc is not, null print only the items containing the sub_desc in their description.
		{
			i = 0;
			cout << " ROW |  SKU  | Description                         | Have | Need |  Price  | Expiry" << endl;
			cout << "-----+-------+-------------------------------------+------+------+---------+-----------" << endl;
			for (int j = 0; j < m_numberOfiProduct; j++)
			{
				if (*m_iProduct[j] == sub_desc)
				{
					cout.width(4);
					cout.fill(' ');
					cout << j + 1 << " |";
					m_iProduct[j]->linear(true);
					cout << *m_iProduct[j] << endl;
					i++;
				}

			}
			if (i == 0)cout << "The list is emtpy!" << "\n";
			cout << "-----+-------+-------------------------------------+------+------+---------+-----------" << endl;
			
		}
		return i;
	}
	// sort the Sorts the items in the iProduct Pointers array, based on difference between quantity needed and quantity on hand in descending order.
	void AidMan::sort()
	{
		iProduct* temp = nullptr;
		int i, j;
		for (i = 0; i < m_numberOfiProduct - 1; i++)

			for (j = 0; j < m_numberOfiProduct - i - 1; j++)
				if (m_iProduct[j]->qtyNeeded() - m_iProduct[j]->qty() < m_iProduct[j + 1]->qtyNeeded() - m_iProduct[j + 1]->qty())
				{
					temp = m_iProduct[j];
					m_iProduct[j] = m_iProduct[j + 1];
					m_iProduct[j + 1] = temp;
				}
		cout << "Sort completed!" << endl;
	}
	//Loops through all the iProduct Pointers elementsand if the SKU is a match it will return the index, otherwise it will return -1
	int AidMan::search(int sku) const
	{
		int found = -1;
		for (int i = 0; i < m_numberOfiProduct; i++)
		{
			if (*m_iProduct[i] == sku) found = i;
		}
		return found;
	}
	void AidMan::add()
	{
		int indx = m_numberOfiProduct;
		int temSku = 0;
		int option = 0;
		if (m_numberOfiProduct < sdds_max_num_items)
		{
			cout << "1- Perishable\n2- Non-Perishable\n-----------------\n0- Exit" << endl;
			option = ut.getint(0, 2, "> ");
			switch (option)
			{
			case 0: cout << "Aborted\n";
				break;
			case 1: m_iProduct[indx] = new Perishable; 
				if (search(temSku = m_iProduct[indx]->readSku(cin)) != -1) // if macthed will return index if not -1
				{
					cout <<"Sku: "<< temSku << " is already in the system, try updating quantity instead.\n";
					delete m_iProduct[indx];
				}
				else
				{
					cin >> *m_iProduct[indx];
					cout << endl;
					if (*m_iProduct[indx]) m_numberOfiProduct++;
					else delete m_iProduct[indx];
				}

				break;
			case 2: m_iProduct[indx] = new Item;
				if (search(temSku = m_iProduct[indx]->readSku(cin)) != -1) // if macthed will return index if not -1
				{
					cout << "Sku: " << temSku << " is already in the system, try updating quantity instead.\n\n";
					delete m_iProduct[indx];
				}
				else
				{
					cin >> *m_iProduct[indx];
					cout << endl;
					if (*m_iProduct[indx]) m_numberOfiProduct++;
					else delete m_iProduct[indx];
				}
				break;
			}
		}
		else
		{
			cout << "Database full!" << endl;
		}
	}
	void AidMan::remove(int index)
	{
		delete m_iProduct[index];
		for (int i = index; i < m_numberOfiProduct; i++)
		{
			m_iProduct[i] = m_iProduct[i + 1];
		}
		m_numberOfiProduct--;
	}
	void AidMan::ship()
	{
		Date* tempDate = new Date;
		int count = 0;
		ofstream fileShip("shippingOrder.txt");
		if (fileShip)
		{
			fileShip << "Shipping Order, Date: " << *tempDate << endl;
			fileShip << " ROW |  SKU  | Description                         | Have | Need |  Price  | Expiry" << endl;
			fileShip << "-----+-------+-------------------------------------+------+------+---------+-----------" << endl;
			for (int i = 0; i < m_numberOfiProduct; i++)
			{
				if (m_iProduct[i]->qtyNeeded() == m_iProduct[i]->qty()) // if the qty neeeded and qty on hand is the same amount, it will be shipped
				{
					fileShip.width(4);
					fileShip.fill(' ');
					fileShip << count + 1 << " |";
					m_iProduct[i]->linear(true);
					fileShip << *m_iProduct[i] << endl;
					delete m_iProduct[i]; // delete from the iProduct array
					for (int j = i; j < m_numberOfiProduct; j++) // shift the product up by one
					{
						m_iProduct[j] = m_iProduct[j + 1];
					}
					m_numberOfiProduct--;
					count++;
				}
			}
			fileShip << "-----+-------+-------------------------------------+------+------+---------+-----------" << endl;
		}
		cout << "Shipping Order for " << count << " times saved!" << endl;
		fileShip.close();
		delete tempDate;
	}
	void AidMan::update()
	{
		cout << "Item description: ";

		char* chTemp;
		cin.ignore(1000, '\n');
		chTemp = ut.getCStr(cin);
		if (list(chTemp) > 0) // if matching desc it will list and return the number of matching
		{
			int idx;
			if ((idx = search(ut.getint(10000, 99999, "Enter SKU: "))) != -1)// if the sku found in iProduct
			{
				cout << "1- Add\n2- Reduce\n0- Exit\n";
				int select = ut.getint(0, 2, "> ");
				switch (select)
				{
				case 1:
					if (m_iProduct[idx]->qtyNeeded() == m_iProduct[idx]->qty()) cout << "Quantity Needed already fulfilled!\n\n";
					else
					{
						int addQty = 0;
						addQty = ut.getint(1, m_iProduct[idx]->qtyNeeded() - m_iProduct[idx]->qty(), "Quantity to add: ");// add to the amount needed only
						*m_iProduct[idx] += addQty;
						cout << addQty << " items added!\n\n";
					}
					break;
				case 2:
					if (m_iProduct[idx]->qtyNeeded() == 0) cout << "Quaintity on hand is zero!\n\n";
					else
					{
						int reduceQty = 0;
						reduceQty = ut.getint(1, m_iProduct[idx]->qty(), "Quantity to reduce: ");// reduce to the number on hand only
						*m_iProduct[idx] -= reduceQty;
						cout << reduceQty << " items removed!\n\n";
					}
					break;
				case 0:
					cout << "Aborted!\n" << endl;
					break;
				}
			}
			else
			{
				cout << "SKU not found!" << endl;
			}
		}
		else
		{
			cout << "No matches found!\n";
		}

		delete[] chTemp; // prevent memory leak!
	}
}