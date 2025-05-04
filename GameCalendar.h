#ifndef GAMECALENDAR_H
#define GAMECALENDAR_H

#include <string>

//we don't show the date anymore. couldn't find a way to work it in. keep it as a reference if I ever need to make a calendar. 
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
