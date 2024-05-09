#include <bits/stdc++.h>
using namespace std;

class Flight
{
public:
    string flightNumber;
    string departure;
    string destination;
    string departureTime;

public:
    Flight(string number, string dep, string dest, string time)
        : flightNumber(number), departure(dep), destination(dest), departureTime(time) {}

    string getFlightNumber() const
    {
        return flightNumber;
    }

    string getDepartureTime() const
    {
        return departureTime;
    }
    string getDeparture() const
    {
        return departure;
    }
    string getDestination() const
    {
        return destination;
    }
    bool overlaps(const Flight &other) const
    {
        return departure == other.departure && departureTime == other.departureTime;
    }

    void display() const
    {
        cout << "Flight: " << flightNumber << ", Departure: " << departure
             << ", Destination: " << destination << ", Departure Time: " << departureTime << endl;
    }
};

class AirlineSystem
{
public:
    vector<Flight> flights;

    bool isFlightOverlapping(const Flight &newFlight) const
    {
        for (const Flight &flight : flights)
        {
            if (flight.overlaps(newFlight))
            {
                return true;
            }
        }
        return false;
    }
    string adjustTime(string time, int adjFac)
    {
        int hours = stoi(time.substr(0, 2));
        int minutes = stoi(time.substr(3));

        // Add 1 hour
        hours = (hours + adjFac) % 24;

        // Convert hours and minutes back to string format
        string newTime = (hours < 10 ? "0" : "") + to_string(hours) + ":" + (minutes < 10 ? "0" : "") + to_string(minutes);
        return newTime;
    }
    void addFlight(const Flight &newFlight)
    {
        if (!isFlightOverlapping(newFlight))
        {
            flights.push_back(newFlight);
            cout << "Flight added successfully." << endl;
        }
        else
        {
            cout << "Error: Flight overlaps with existing flights. Please choose a different schedule." << endl;
            cout << "Expert Opinion:------" << endl;
            cout << "You can schedule your flight:" << endl;
            cout << "1. 1 hour after " << newFlight.departureTime << " that is " << adjustTime(newFlight.departureTime, 1) << endl;
            cout << "2. 1 hour before " << newFlight.departureTime << " that is " << adjustTime(newFlight.departureTime, -1) << endl;
            cout << "3. To cancel your flight" << endl;
            cout << "Enter your Choice:";
            int ch;
            cin >> ch;
            int adjFac;
            if (ch == 1 || ch == 2)
            {
                if (ch == 1)
                    adjFac = 1;
                else
                    adjFac = -1;
                Flight temp = Flight(newFlight.getFlightNumber(), newFlight.getDeparture(), newFlight.getDestination(), adjustTime(newFlight.getDepartureTime(), adjFac));
                addFlight(temp);
            }
            else
            {
                cout << "Your Flight Scheduling Request has been cancelled" << endl;
            }
        }
    }

    void removeFlight(const string &flightNumber)
    {
        auto it = find_if(flights.begin(), flights.end(), [&flightNumber](const Flight &flight)
                          { return flight.getFlightNumber() == flightNumber; });

        if (it != flights.end())
        {
            flights.erase(it);
            cout << "Flight " << flightNumber << " removed successfully." << endl;
        }
        else
        {
            cout << "Error: Flight " << flightNumber << " not found." << endl;
        }
    }

    void displayFlights() const
    {
        if (flights.empty())
        {
            cout << "No flights scheduled." << endl;
        }
        else
        {
            cout << "Scheduled Flights:" << endl;
            for (const Flight &flight : flights)
            {
                flight.display();
            }
        }
    }
    void searchFlightsByDepartureCity(const string &depCity) const
    {
        bool found = false;
        cout << "Flights departing from " << depCity << ":" << endl;
        for (const Flight &flight : flights)
        {
            if (flight.getDeparture() == depCity)
            {
                flight.display();
                found = true;
            }
        }
        if (!found)
        {
            cout << "No flights found departing from " << depCity << endl;
        }
    }

    void displayFlightsSortedByDepartureTime() const
    {
        vector<Flight> sortedFlights = flights;
        sort(sortedFlights.begin(), sortedFlights.end(), [](const Flight &a, const Flight &b)
             { return a.getDepartureTime() < b.getDepartureTime(); });
        cout << "Flights Sorted by Departure Time:" << endl;
        for (const Flight &flight : sortedFlights)
        {
            flight.display();
        }
    }
};

int main()
{
    AirlineSystem system;
    int choice;

    do
    {
        cout << "\nAirline Scheduling System\n";
        cout << "1. Add Flight\n";
        cout << "2. Remove Flight\n";
        cout << "3. View Flights\n";
        cout << "4. Search Flights by Departure City\n";
        cout << "5. Display Flights Sorted by Departure Time\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            string number, dep, dest, time;
            cout << "Enter flight number: ";
            cin >> number;
            cout << "Enter departure city: ";
            cin >> dep;
            cout << "Enter destination city: ";
            cin >> dest;
            cout << "Enter departure time (HH:MM): ";
            cin >> time;
            system.addFlight(Flight(number, dep, dest, time));
            break;
        }
        case 2:
        {
            string number;
            cout << "Enter flight number to remove: ";
            cin >> number;
            system.removeFlight(number);
            break;
        }
        case 3:
            system.displayFlights();
            break;
        case 4:
        {
            string depCity;
            cout << "Enter departure city to search for flights: ";
            cin >> depCity;
            system.searchFlightsByDepartureCity(depCity);
            break;
        }
        case 5:
            system.displayFlightsSortedByDepartureTime();
            break;
        case 6:
            cout << "Exiting program.\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 6);

    return 0;
}