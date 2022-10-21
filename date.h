#ifndef __DATE_H__
#define __DATE_H__

#include <string>

class Date {
public:
    Date();
    Date(int y, int m, int d);
    void set(int y, int m, int d);
    std::string toString(bool brief);
    void setToToday();
    std::string getWeekDay();
    bool lessThan(const Date& d);
    bool equals(const Date& d);
    int daysBetween(const Date& d);
    Date addDays(int days);

    static bool leapYear(int year);
    static std::string monthName(int m);
    static int yearDays(int year);
    static int monthDays(int month, int year);

private:
    int ymd2dsbd(int y, int m, int d);
    void getYMD(int& y, int& m, int& d);

    static int m_BaseYear;
    int m_DaysSinceBaseDate;

};

#endif // __DATE_H__
