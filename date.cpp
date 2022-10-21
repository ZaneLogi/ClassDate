#include <ctime>
#include <sstream>
#include <iomanip>
#include "date.h"

int Date::m_BaseYear = 1900; // 1900/01/01, Monday

Date::Date() : m_DaysSinceBaseDate(0)
{}

Date::Date(int y, int m, int d)
{
    m_DaysSinceBaseDate = ymd2dsbd(y, m, d);
}

void Date::set(int y, int m, int d)
{
    m_DaysSinceBaseDate = ymd2dsbd(y, m, d);
}

std::string Date::toString(bool brief)
{
    int y, m, d;
    getYMD(y, m, d);

    std::ostringstream stringStream;

    if (!brief)
    {
        stringStream << getWeekDay() << " " << monthName(m) << " " << d << " " << y;
    }
    else
    {
        stringStream << std::setw(4) << y << "/" << std::setw(2) << std::setfill('0') << m << "/" << std::setw(2) << d;
    }

    return stringStream.str();
}

void Date::setToToday()
{
    std::time_t t = std::time(0); // get time now
    std::tm* now = std::localtime(&t);
    m_DaysSinceBaseDate = ymd2dsbd(now->tm_year + 1900, now->tm_mon + 1, now->tm_mday);
}

std::string Date::getWeekDay()
{
    static const char* name[] = {
        "Monday", "Tuesday", "Wedsday", "Thursday", "Friday", "Saturday", "Sunday"
    };

    if (m_DaysSinceBaseDate >= 0)
    {
        return name[m_DaysSinceBaseDate % 7];
    }
    else
    {
        return name[(7 + (m_DaysSinceBaseDate % 7)) % 7];
    }
}

bool Date::lessThan(const Date& d)
{
    return m_DaysSinceBaseDate < d.m_DaysSinceBaseDate;
}

bool Date::equals(const Date& d)
{
    return m_DaysSinceBaseDate == d.m_DaysSinceBaseDate;
}

int Date::daysBetween(const Date& d)
{
    return d.m_DaysSinceBaseDate - m_DaysSinceBaseDate;
}

Date Date::addDays(int days)
{
    Date date;
    date.m_DaysSinceBaseDate = m_DaysSinceBaseDate + days;
    return date;
}

bool Date::leapYear(int year)
{
    if (year % 400 == 0)
        return true;
    if (year % 100 == 0)
        return false;
    if (year % 4 == 0)
        return true;

    return false;
}

std::string Date::monthName(int m)
{
    if (m < 1 || m > 12)
        return "Invalid Month";

    static const char* name[] = {
        "January", "February", "March", "April", "May", "June",
        "July", "August", "Septeber", "October", "November", "December"
    };

    return name[m - 1];
}

int Date::yearDays(int year)
{
    return leapYear(year) ? 366 : 365;
}

int Date::monthDays(int month, int year)
{
    if (month == 2)
        return leapYear(year) ? 29 : 28;
    if (month <= 7)
        return month % 2 ? 31 : 30;
    else
        return month % 2 ? 30 : 31;
}

int Date::ymd2dsbd(int y, int m, int d)
{
    // NOTE: no check for the valid of y, m, d

    int totalDays = 0;

    if (y >= m_BaseYear)
    {
        for (int i = m_BaseYear; i < y; i++)
        {
            totalDays += yearDays(i);
        }

        for (int i = 1; i < m; i++)
        {
            totalDays += monthDays(i, y);
        }

        totalDays += d - 1;
    }
    else
    {
        for (int i = m_BaseYear - 1; i > y; i--)
        {
            totalDays += yearDays(i);
        }

        for (int i = 12; i > m; i--)
        {
            totalDays += monthDays(i, y);
        }

        totalDays += monthDays(m, y) - d + 1;

        totalDays = -totalDays;
    }

    return totalDays;
}

void Date::getYMD(int& y, int& m, int& d)
{
    if (m_DaysSinceBaseDate >= 0)
    {
        int totalDays = m_DaysSinceBaseDate;
        for (y = m_BaseYear; ; y++)
        {
            int days = yearDays(y);
            if (days > totalDays)
                break;
            totalDays -= days;
        }
        for (m = 1; ; m++)
        {
            int days = monthDays(m, y);
            if (days > totalDays)
                break;
            totalDays -= days;
        }
        d = totalDays + 1;
    }
    else
    {
        int totalDays = -m_DaysSinceBaseDate;
        for (y = m_BaseYear - 1; ; y--)
        {
            int days = yearDays(y);
            if (days > totalDays)
                break;
            totalDays -= days;
        }
        if (totalDays == 0)
        {
            y++;
            m = 1;
            d = 1;
            return;
        }

        for (m = 12; ; m--)
        {
            int days = monthDays(m, y);
            if (days > totalDays)
                break;
            totalDays -= days;
        }
        if (totalDays == 0)
        {
            m++;
            d = 1;
            return;
        }

        d = monthDays(m, y) - totalDays + 1;
    }
}
