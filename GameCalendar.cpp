#include "GameCalendar.h"

// Initialize the calendar to start on September 1st, 1999
GameCalendar::GameCalendar() : day(1), month(10), year(1999) {}

void GameCalendar::AdvanceDay() {
    day++;
    if (day > DaysInMonth(month, year)) {
        day = 1;  // Reset to the 1st
        month++;
        if (month > 12) {
            month = 1;  // Reset to January
            year++;
        }
    }
}

std::string GameCalendar::GetDate() const {
    const std::string months[] = { "", "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December" };
    return months[month] + " " + std::to_string(day) + ", " + std::to_string(year);
}

int GameCalendar::DaysInMonth(int month, int year) const {
    switch (month) {
        case 4: case 6: case 9: case 11:
            return 30;
        case 2:
            return (IsLeapYear(year)) ? 29 : 28;
        default:
            return 31;
    }
}

bool GameCalendar::IsLeapYear(int year) const {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}
