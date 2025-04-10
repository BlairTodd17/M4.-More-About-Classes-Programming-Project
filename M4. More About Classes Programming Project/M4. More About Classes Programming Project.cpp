#include <iostream>
#include <string>
#include <sstream>
#include <cmath>
#include <algorithm>
using namespace std;

class Date {
private:
    int day, month, year;

    static const int daysInMonth[12];
    static const string monthNames[12];

    bool isLeapYear(int y) const {
        return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
    }

    int getDaysInMonth(int m, int y) const {
        if (m == 2) return isLeapYear(y) ? 29 : 28;
        return daysInMonth[m - 1];
    }

    bool isValidDate(int d, int m, int y) const {
        return (y > 0 && m >= 1 && m <= 12 && d >= 1 && d <= getDaysInMonth(m, y));
    }

public:
    Date(int d = 1, int m = 1, int y = 2000) {
        if (isValidDate(d, m, y)) {
            day = d; month = m; year = y;
        }
        else {
            day = 1; month = 1; year = 2000;
        }
    }

    void setDate(int d, int m, int y) {
        if (isValidDate(d, m, y)) {
            day = d; month = m; year = y;
        }
        else {
            cout << "Invalid date: " << m << "/" << d << "/" << y << endl;
        }
    }

    Date& operator++() {
        day++;
        if (day > getDaysInMonth(month, year)) {
            day = 1;
            month++;
            if (month > 12) {
                month = 1;
                year++;
            }
        }
        return *this;
    }

    Date operator++(int) {
        Date temp = *this;
        ++(*this);
        return temp;
    }

    Date& operator--() {
        day--;
        if (day == 0) {
            month--;
            if (month == 0) {
                month = 12;
                year--;
            }
            day = getDaysInMonth(month, year);
        }
        return *this;
    }

    Date operator--(int) {
        Date temp = *this;
        --(*this);
        return temp;
    }

    int operator-(const Date& other) const {
        return abs(toDays() - other.toDays());
    }

    int toDays() const {
        int totalDays = day;
        for (int i = 1; i < year; ++i)
            totalDays += isLeapYear(i) ? 366 : 365;
        for (int i = 1; i < month; ++i)
            totalDays += getDaysInMonth(i, year);
        return totalDays;
    }

    friend ostream& operator<<(ostream& out, const Date& d) {
        out << monthNames[d.month - 1] << " " << d.day << ", " << d.year;
        return out;
    }

    friend istream& operator>>(istream& in, Date& d) {
        string input;
        cout << "Enter date (MM/DD/YYYY): ";
        getline(in, input);
        replace(input.begin(), input.end(), '/', ' ');
        stringstream ss(input);
        int m, day, y;
        ss >> m >> day >> y;
        if (d.isValidDate(day, m, y)) {
            d.day = day; d.month = m; d.year = y;
        }
        else {
            cout << "Invalid date entered.\n";
        }
        return in;
    }
};

const int Date::daysInMonth[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
const string Date::monthNames[12] = {
    "January","February","March","April","May","June",
    "July","August","September","October","November","December"
};

int main() {
    Date d1(4, 10, 2014), d2(4, 18, 2014);
    cout << "Date 1: " << d1 << "\n";
    cout << "Date 2: " << d2 << "\n";
    cout << "Days between: " << (d2 - d1) << " days\n\n";

    Date leap(2, 29, 2008);
    cout << "Original leap day: " << leap << "\n";
    cout << "After pre-decrement: " << --leap << "\n";
    cout << "After pre-increment: " << ++leap << "\n";

    Date dec31(12, 31, 2024);
    cout << "\nOriginal date: " << dec31 << "\n";
    cout << "After post-increment: " << dec31++ << "\n";
    cout << "Now: " << dec31 << "\n";
    cout << "After post-decrement: " << dec31-- << "\n";
    cout << "Now: " << dec31 << "\n";

    Date inputDate;
    cin >> inputDate;
    cout << "You entered: " << inputDate << "\n";

    return 0;
}
