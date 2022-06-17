#ifndef SDDS_UTILS_H
#define SDDS_UTILS_H
#include<iostream>
namespace sdds {
   const int sdds_testYear = 2022;
   const int sdds_testMon = 03;
   const int sdds_testDay = 31;
   class Utils {
      bool m_testMode = false;
   public:
      void getSystemDate(int* year = nullptr, int* mon = nullptr, int* day = nullptr);
      int daysOfMon(int mon, int year)const;
      void testMode(bool testmode = true);
      void alocpy(char*& destination, const char* source);// Safely allocates memory in destinaiton and copies the source into it
      int getint(const char* prompt = nullptr); // get an integer number from user
      double getDouble(const char* prompt = nullptr);
      double getDouble(double min, double max, const char* prompt = nullptr, const char* errMes = nullptr); // get double number from user
      int getint(int min, int max, const char* prompt = nullptr, const char* errMes = nullptr); // get an integer in a range
      char* getCStr(std::istream& istr, char delim='\n');
   };
   extern Utils ut;
}

#endif // !SDDS_UTILS_H
