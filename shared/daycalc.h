#ifndef _DATE_CALC_HEADER_
#define _DATE_CALC_HEADER_

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <map>

class Date {

private:
    int year,month,day;
    
    void addOneDay(); 
    void subOneDay();
    int subSmallDate(const Date &date) const; 

public:
    Date(int y=0 ,int m=0, int d=0);
    
    int daysPerMonth(int m=-1) const; 
    int daysPerYear(int y=-1) const; 
    
    int compare(const Date &date) const; 
    bool isLeapYear(int y=-1) const; 
    
    int subDate(const Date &date) const; 
    Date subDays(int days) const; 
    Date addDays(int days) const; 
    
    void prtMsg(int m=1,int d=21) const; 
    
// overload ++ -- etc.,
public: 
    Date& operator++(); //++ Date
    Date operator++(int); //Date ++
    Date& operator--(); //-- Date
    Date operator--(int); //Date --
    Date operator+(int days); //Date + days
    Date operator-(int days); //Date - days
    int operator-(const Date &date); //Date1 - Date2

public:

    std::string get_format_date(const Date& datehere);
};

#endif /*_DATE_CALC_HEADER_*/

