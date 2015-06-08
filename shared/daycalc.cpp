#include "daycalc.h"

void Date::addOneDay()
{
    if(++day > daysPerMonth()) 
    {
        day=1;
        month++;
    }
    if(month>12) 
    {
        month=1;
        year++;
    }
}

void Date::subOneDay()
{
    if(--day < 1) 
    {
        if(--month < 1) 
        {
            month=12;   
            year--;
        }
        day=daysPerMonth();
    }
}

int Date::subSmallDate(const Date &dat) const
{
    int days=0;
    Date date(dat);

    while(year>(date.year+1)) 
    {
        days+=date.daysPerYear();
        date.year++;
    }
    while(month>(date.month+1))
    {
        days+=date.daysPerMonth();
        date.month++;
    }
    while(day>(date.day+1))
    {
        days++;
        date.day++;
    }
    while(compare(date)>0)
    {
        days++;
        date.addOneDay();
    }

    return days;
}

/*************** Public Methods ****************/
// initalized and check.
Date::Date(int y,int m,int d) : year(y),month(m),day(d) 
{
    if(year<0) 
    {
        std::cout<<"*Error : Year "<<year<<" can't be negative..."<<std::endl;
        delete this;
    }
    else if(month<1 || month>12) 
    {
        std::cout<<"*Error : "<<month<<" is a wrong Month..."<<std::endl;
        delete this;
    }
    else if(day<1 || day>daysPerMonth())
    {
        std::cout<<"*Error : "<<day<<" is a wrong Day by Month "<<month<<" ..."<<std::endl;
        delete this;
    }

}

int Date::daysPerMonth(int m) const
{
    m = (m < 0) ? month : m;

    switch(m)
    {
        case 1: return 31;
        case 2: return isLeapYear(year) ? 29 : 28;
        case 3: return 31;
        case 4: return 30;
        case 5: return 31;
        case 6: return 30;
        case 7: return 31;
        case 8: return 31;
        case 9: return 30;
        case 10: return 31;
        case 11: return 30;
        case 12: return 31;
        default: return -1;
    }
}

int Date::daysPerYear(int y) const
{
    y=(y<0) ? year : y;

    if(isLeapYear(y))
    {
        return 366;
    }
    return 365;
}

int Date::compare(const Date &date) const
{
    if(year>date.year)
        return 1;
    else if(year<date.year)
        return -1;
    else
    {
        if(month>date.month)
            return 1;
        else if(month<date.month)
            return -1;
        else 
        {
            if(day>date.day)
                return 1;
            else if(day<date.day)
                return -1;
            else return 0;
        }
    }
}

bool Date::isLeapYear(int y) const
{
    y=(y<0) ? year : y;

    if(0==y%400 || (0==y%4 && 0!=y%100))
    {
        return true;
    }
    return false;
}

int Date::subDate(const Date &date) const
{
    if(compare(date)>0)
    {
        return subSmallDate(date);
    }
    else if(compare(date)<0)
    {
        return -(date.subSmallDate(*this));
    }
    else 
    {
        return 0;
    }
}

Date Date::addDays(int days) const
{
    Date newDate(year,month,day);
    if(days>0) {
        for(int i=0;i<days;i++)
        {
            newDate.addOneDay();
        }
    }
    else if (days<0)
    {
        for(int i=0;i<(-days);i++)
        {
            newDate.subOneDay();
        }
    }

    return newDate;
}

Date Date::subDays(int days) const
{
    return addDays(-days);
}

/********** Operator Overloading ***********/
Date& Date::operator++()
{ //++Date
    addOneDay();
    return *this;
}

Date Date::operator++(int)
{ //Date++
    Date date(*this);
    addOneDay();
    return date;
}

Date& Date::operator--()
{ //--Date
    subOneDay();
    return *this;
}

Date Date::operator--(int)
{ //Date--
    Date date(*this);
    subOneDay();
    return date;
}

Date Date::operator+(int days)
{ //Date+days
    return addDays(days);
}

Date Date::operator-(int days)
{ //Date-days
    return subDays(days);
}

int Date::operator-(const Date &date)
{ //Date1-Date2
    return subDate(date);
}

std::string Date::get_format_date(const Date& datehere)
{
    char format[32];
    memset(format, 0, 32);
    if (datehere.month < 10)
        sprintf(format, "%d-0%d-%d", datehere.year, datehere.month, datehere.day);
    else
        sprintf(format, "%d-%d-%d", datehere.year, datehere.month, datehere.day);

    return format;
}
