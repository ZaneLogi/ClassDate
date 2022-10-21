#include <iostream>
#include "date.h"

void testYear(int year)
{
    Date date0101(year, 1, 1);
    std::cout << date0101.toString(true) << std::endl;
    std::cout << "Week Day: " << date0101.getWeekDay() << std::endl;
    std::cout << std::endl;

    Date date0131(year, 1, 31);
    std::cout << date0131.toString(true) << std::endl;
    std::cout << "Week Day: " << date0131.getWeekDay() << std::endl;
    std::cout << std::endl;

    Date date0201(year, 2, 1);
    std::cout << date0201.toString(true) << std::endl;
    std::cout << "Week Day: " << date0201.getWeekDay() << std::endl;
    std::cout << std::endl;

    Date date02end(year, 2, Date::monthDays(2, year));
    std::cout << date02end.toString(true) << std::endl;
    std::cout << "Week Day: " << date02end.getWeekDay() << std::endl;
    std::cout << std::endl;
}

int main()
{
    testYear(1900);
    testYear(1901);
    testYear(1600);

    Date date_today;
    date_today.setToToday();
    std::cout << "Today" << std::endl;
    std::cout << date_today.toString(false) << std::endl;
    std::cout << "Week Day: " << date_today.getWeekDay() << std::endl;
    std::cout << std::endl;

    Date same_date_next_year = date_today.addDays(Date::yearDays(2022));
    std::cout << "Same date next year" << std::endl;
    std::cout << same_date_next_year.toString(false) << std::endl;
    std::cout << "Week Day: " << same_date_next_year.getWeekDay() << std::endl;
    std::cout << std::endl;

    std::cout << "1900 is a leap year => " << (Date::leapYear(1900) ? "true" : "false") << std::endl;
    std::cout << "2000 is a leap year => " << (Date::leapYear(2000) ? "true" : "false") << std::endl;
    std::cout << "2020 is a leap year => " << (Date::leapYear(2020) ? "true" : "false") << std::endl;
    std::cout << "2022 is a leap year => " << (Date::leapYear(2022) ? "true" : "false") << std::endl;
    std::cout << std::endl;

    Date date20210101(2021, 1, 1), date20220101(2022, 1, 1);
    std::cout << "Days between 2021/01/01 and 2022/01/01: " << date20210101.daysBetween(date20220101) << std::endl;
    std::cout << std::endl;

    std::cout << "1600/01/01 is less than 1900/01/01: " << (Date(1600, 1, 1).lessThan(Date(1900, 1, 1)) ? "true" : "false") << std::endl;
    std::cout << std::endl;

    std::cout << "TODAY is less than 1900/01/01: " << (date_today.lessThan(Date(1900, 1, 1)) ? "true" : "false") << std::endl;
    std::cout << std::endl;

    std::cout << "TODAY equals 1900/01/01: " << (date_today.equals(Date(1900, 1, 1)) ? "true" : "false") << std::endl;
    std::cout << std::endl;

    return 0;
}