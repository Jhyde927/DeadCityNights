#ifndef GAMECALENDAR_H
#define GAMECALENDAR_H

#include <string>

class GameCalendar {
public:
    GameCalendar();  // Constructor to initialize the date

    void AdvanceDay();            // Advances the day by one
    std::string GetDate() const;  // Returns the current date as a string

private:
    int day;
    int month;
    int year;

    // Helper functions
    int DaysInMonth(int month, int year) const;
    bool IsLeapYear(int year) const;
};

extern GameCalendar gameCalendar;

#endif // GAMECALENDAR_H
