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

#define _CRT_SECURE_NO_WARNINGS
#include "Train.h"
#include <cstdio>
#include <cstring>
#include <iostream>
#include <iomanip> 

using namespace std;

namespace sdds {
	void Train::initialize() {
		trainName = nullptr;
		noOfPeople = -1;
		departureTime = -1;
	}

	bool Train::validTime(int value)const {
		unsigned int digit = value % 100;
		return (value >= MIN_TIME && value <= MAX_TIME) && (digit >= 0 && digit <= 59);
	}

	bool Train::validNoOfPassengers(int value)const {
		return (value > 0 && value <= MAX_NO_OF_PASSENGERS);
	}

	void Train::set(const char* name) {
		delete[] trainName;
		trainName = nullptr;
		if (name != nullptr && name[0] != '\0') {
			trainName = new char[strlen(name) + 1];

			strcpy(trainName, name);
		}
	}

	void Train::set(int noOfPassengers, int departure) {
		if (validNoOfPassengers(noOfPassengers) && validTime(departure)) {
			noOfPeople = noOfPassengers;
			departureTime = departure;
		}
		else {
			noOfPeople = -1;
			departureTime = -1;
		}
	}

	void Train::set(const char* name, int noOfPassengers, int departure) {
		set(name);
		set(noOfPassengers, departure);
	}

	void Train::finalize() {
		delete[] trainName;
		trainName = nullptr;
	}

	bool Train::isInvalid()const {
		return trainName == nullptr || noOfPeople == -1 || departureTime == -1;
	}

	int Train::noOfPassengers() const {
		return (noOfPeople);
	}

	const char* Train::getName() const {
		return (trainName);
	}

	int Train::getDepartureTime() const {
		return (departureTime);
	}

	void Train::display() const {
		if (isInvalid()) {
			cout << "Train in an invalid State!" << endl;
		}
		else {
			cout << "NAME OF THE TRAIN:    " << trainName << endl;
			cout << "NUMBER OF PASSENGERS: " << noOfPeople << endl;
			cout << "DEPARTURE TIME:       " << departureTime << endl;
		}
	}

	/* Part 2 -  Implementation Code */

// This function is part of a Train class and is responsible for loading passengers onto the train.

	bool Train::load(int& notBoarded) {
		// Prompt the user to enter the number of passengers boarding.
		cout << "Enter number of passengers boarding:" << endl;
		cout << "> ";

		// Initialize a boolean variable to track whether passengers boarded successfully or not.
		bool boarded = false;

		// Declare an int variable to store the number of passengers entered by the user.
		int passengers;
		// Read the number of passengers from the user's input.
		cin >> passengers;

		// Increase the total number of people on the train by the number of boarding passengers.
		noOfPeople += passengers;

		// Checking if the current total number of people on the train is within the valid limits.
		if (validNoOfPassengers(noOfPeople)) {
			//And if the total number of people is valid, mark the boarding process as successful.
			boarded = true;

			// Reset the "notBoarded" variable to 0 since all passengers boarded successfully.
			notBoarded = 0;
		}
		else {
			// If the total number of people exceeds the maximum allowed, calculate the excess.
			notBoarded = noOfPeople - MAX_NO_OF_PASSENGERS;

			// Set the total number of people to the maximum allowed capacity.
			noOfPeople = MAX_NO_OF_PASSENGERS;
		}

		// Return whether passengers successfully boarded.
		return boarded;
	}


	// This function is part of a Train class and is responsible for updating the departure time of the train.
	bool Train::updateDepartureTime() {
		// Prompt the user to enter the new departure time.
		cout << "Enter new departure time:" << endl;
		cout << "> ";

		// Declare an int variable to store the new departure time entered by the user.
		int newDepartureTime;

		// Initialize a boolean variable to track whether the entered time is valid or not.
		bool isTime = false;

		// Read the new departure time from the user's input.
		cin >> newDepartureTime;

		// Checking if the entered departure time is valid using the 'validTime' function.
		if (validTime(newDepartureTime)) {
			// If the entered time is valid, then update the departure time.
			departureTime = newDepartureTime;

			// then mark that the time update was successful.
			isTime = true;
		}
		else {
			// If the entered time is not valid, set the departure time to -1 as an indicator.
			departureTime = -1;
		}

		// Return whether the departure time update was successful.
		return isTime;
	}


	// This function is part of a Train class and it responsible for transferring passengers 
	// and combining train names from one train ('from') to another ('this').

	bool Train::transfer(const Train& from) {
		// Initialize a boolean variable to track whether the transfer was successful.
		bool transfer = false;

		// Checking if both 'this' and 'from' trains are valid (not marked as invalid).
		if (!this->isInvalid() && !from.isInvalid()) {
			// Calculate the combined length of the train names, including a comma and a space.
			size_t combinedLength = strlen(this->trainName) + strlen(", ") + strlen(from.trainName) + 1;

			// Dynamically allocate memory for the new name.
			char* newTName = new char[combinedLength];

			// Checking if memory allocation was successful.
			if (newTName != nullptr) {
				// Copy the current train's name to the new buffer.
				strcpy(newTName, this->trainName);

				// Concatenate the train names using strcat.
				strcat(newTName, ", ");
				strcat(newTName, from.trainName);

				// Free old name and update the pointer to new name.
				delete[] this->trainName;
				this->trainName = newTName;

				// Increase the total number of people on 'this' train by the number of people on 'from' train.
				this->noOfPeople += from.noOfPeople;

				// Check if the total number of people on 'this' train is within valid limits.
				if (validNoOfPassengers(this->noOfPeople)) {
					// If within limits, mark the transfer as successful.
					transfer = true;
				}
				else {
					// If the total number of people exceeds the maximum allowed, report the excess passengers and set it to the maximum.
					cout << "Train is full; " << this->noOfPeople - MAX_NO_OF_PASSENGERS << " passengers of " << from.trainName << " could not be boarded!" << endl;
					this->noOfPeople = MAX_NO_OF_PASSENGERS;

					// Still mark the transfer as successful, even if some passengers could not be boarded.
					transfer = true;
				}
			}
			else {
				// If memory allocation fails, report an error.
				cout << "Memory allocation failed for the new name." << endl;
			}
		}

		// Return whether the transfer was successful.
		return transfer;
	}

	/* Have a safe trip :) */
}