/*****************************************************************************
                        Workshop 3 - Part 2
Full Name  : Yusuff Oyediran
Student ID#: 142813203
Email      : yooyediran@myseneca.ca
Section    : ZEE
Authenticity Declaration:
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider. This submitted
piece of work is entirely of my own creation.
*****************************************************************************/

#ifndef SDDS_TRAIN_H
#define SDDS_TRAIN_H
#include <iostream>

namespace sdds {
    const int MIN_TIME = 700;
    const int MAX_TIME = 2300;
    const int MAX_NO_OF_PASSENGERS = 1000;
    class Train {
        char* trainName;
        int noOfPeople;
        int departureTime;

    public:
        bool validTime(int value)const;
        bool validNoOfPassengers(int value)const;
        void initialize();
        void set(const char* name);
        void set(int noOfPassengers, int departure);
        void set(const char* name, int noOfPassengers, int departure);
        void finalize();
        bool isInvalid()const;
        int noOfPassengers() const;
        const char* getName() const;
        int getDepartureTime() const;
        void display() const;

        /*Part two Header*/
        bool load(int& notBoarded);
        bool updateDepartureTime();
        bool transfer(const Train& from);
    };
}
#endif // !SDDS_TRAIN_H
