#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <ctime>
#include <cstring>
#include <string>
#include "Utils.h"
using namespace std;
namespace sdds {
   Utils ut;
   void Utils::testMode(bool testmode) {
      m_testMode = testmode;
   }
   void Utils::getSystemDate(int* year, int* mon, int* day) {
      if (m_testMode) {
         if(day) *day = sdds_testDay;
         if(mon) *mon = sdds_testMon;
         if(year) *year = sdds_testYear;
      }
      else {
         time_t t = std::time(NULL);
         tm lt = *localtime(&t);
         if (day) *day = lt.tm_mday;
         if (mon) *mon = lt.tm_mon + 1;
         if (year) *year = lt.tm_year + 1900;
      }
   }
   int Utils::daysOfMon(int month, int year)const {
      int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, -1 };
      int mon = (month >= 1 && month <= 12 ? month : 13)-1;
      return days[mon] + int((mon == 1) * ((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0));
   }
   // Safely allocates memory in destinaiton and copies the source into it
   void Utils::alocpy(char*& destination, const char* source)
   {
       delete[] destination;
       destination = nullptr;
       if (source != nullptr)
       {
           destination = new char[strlen(source) + 1];
           strcpy(destination, source);
       }
   }
   // get an integer number from user
   int Utils::getint(const char* prompt)
   {
       int val = 0;
       bool flag = false;
       
       prompt != nullptr ? cout << prompt : cout << "";
           do
           {
               flag = true;
               cin >> val;
               if (cin.fail() != 0)
               {
                   flag = false;
                   cout << "Invalid Integer, retry: ";
                   cin.clear();
                   cin.ignore(2000, '\n');
               }
           } while (!flag);
       
       return val;
   }
   double Utils::getDouble(const char* prompt)
   {
       double val = 0;
       bool flag = false;

       prompt != nullptr ? cout << prompt : cout << "";
       do
       {
           flag = true;
           cin >> val;
           if (cin.fail() != 0)
           {
               flag = false;
               cout << "Invalid number, retry: ";
               cin.clear();
               cin.ignore(2000, '\n');
           }
       } while (!flag);

       return val;
   }
   double Utils::getDouble(double min, double max, const char* prompt, const char* errMes)
   {
       double val = 0, count = 0;
       bool flag = false;
       do
       {
           flag = true;

           val = count == 0 ? getDouble(prompt) : getDouble(nullptr);
           if (val < min || val > max)
           {
               flag = false;
               if (errMes)
               {
                   cout << errMes << ", retry: ";
               }
               else
               {
                   cout << "Value out of range [";
                   cout.setf(ios::fixed);
                   cout.precision(2);
                   cout << min;
                   cout << "<=val<=";
                   cout << max;
                   cout << "]: ";
                   count++;
               }
           }
       } while (!flag);
       return val;
   }

   int Utils::getint(int min, int max, const char* prompt, const char* errMes)
   {
       int val = 0, count = 0;
       bool flag = false;
       do
       {
           flag = true;
           
           val = count == 0? getint(prompt): getint(nullptr);
           if (val < min || val > max)
           {
               flag = false;
               if (errMes)
               {
                   cout << errMes << ", retry: ";
               }
               else
               {
                   cout << "Value out of range ["<< min <<"<=val<="<< max <<"]: ";
                   count++;
               }
           }
       } while (!flag);
       return val;
   }

   char* Utils::getCStr(std::istream& istr, char delim)
   {
           char* cstr = nullptr;
           string str;
           getline(istr, str, delim);
           if (istr)
           {
               alocpy(cstr, str.c_str());
           }
           return cstr;
   }
  
}