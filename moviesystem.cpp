#include <iostream>
#include <string>
#include <vector>
#include <chrono>

using namespace std;
using namespace std::chrono;

class Movie {
private:
    string title;
    string about;
    string genre;
    int runningTime;
    string mainStar;
    string filmDistributor;
    string releaseDate;

public:

    Movie(string title, string about, string genre, int runningTime, string mainStar, string filmDistributor, string releaseDate)
        : title(title), about(about), genre(genre), runningTime(runningTime), mainStar(mainStar), filmDistributor(filmDistributor), releaseDate(releaseDate) {}

    string getTitle() const {
    return title;
}


    void displayMovieInfo() {
        cout << "Title: " << title << endl;
        cout << "Description: " << about << endl;
        cout << "Genre of the movie: " << genre << endl;
        cout << "Total time of the movie: " << runningTime << " minutes" << endl;
        cout << "Lead Actor of the movie: " << mainStar << endl;
        cout << "Distributor of the film: " << filmDistributor << endl;
        cout << "Date of Release: " << releaseDate << endl;
    }
};

class Screen {
private:
    int screenNumber;
    string assignedMovie;
    int maximumSeatingCapacity;
    string screenFacilities;
    time_point<system_clock> startTime;
    time_point<system_clock> endTime;

public:
    Screen(int screenNumber, int maximumSeatingCapacity, string screenFacilities)
        : screenNumber(screenNumber), maximumSeatingCapacity(maximumSeatingCapacity), screenFacilities(screenFacilities) {}

    int getScreenNumber() {
        return screenNumber;
    }

    void displayScreenInfo() {
        cout << "Screen number " << screenNumber << ":" << endl;
        cout << "Set movie on the screen is: " << assignedMovie << endl;
        cout << "Seating capacity maximum of this screen is: " << maximumSeatingCapacity << endl;
        cout << "This Screen has Facilities: " << screenFacilities << endl;
        cout << endl;
    }

    void assignMovie(string movieTitle) {
        assignedMovie = movieTitle;
    }

    void setMovieTiming(string startTimeStr, string endTimeStr) {
        // Parse start time
        int startTimeHour, startTimeMinute;
        sscanf(startTimeStr.c_str(), "%d:%d", &startTimeHour, &startTimeMinute);
        auto now = system_clock::now();
        auto startDuration = hours(startTimeHour) + minutes(startTimeMinute);
        startTime = now + startDuration;

        // Parse end time
        int endTimeHour, endTimeMinute;
        sscanf(endTimeStr.c_str(), "%d:%d", &endTimeHour, &endTimeMinute);
        auto endDuration = hours(endTimeHour) + minutes(endTimeMinute);
        endTime = now + endDuration;
    }

    bool isMovieTimingSet() {
        return startTime != time_point<system_clock>() && endTime != time_point<system_clock>();
    }

    bool isMovieCurrentlyPlaying() {
        auto now = system_clock::now();
        return startTime <= now && now <= endTime;
    }
};

class CinemaBookingSystem {
private:
    vector<Movie> movies;
    vector<Screen> screens;

public:
    void addMovie(const Movie& movie) {
        movies.push_back(movie);
    }

    void addScreen(const Screen& screen) {
        screens.push_back(screen);
    }

    void run() {
        int choice;
        do {
            displayMainMenu();
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
                case 1:
                    displayMovieInfo();
                    break;
                case 2:
                    displayScreenInfo();
                    break;
                case 3:
                    bookTickets();
                    break;
                case 4:
                    managerSection();
                    break;
                case 5:
                    cout << "I hope you liked your ecperience. Goodbye user :)" << endl;
                    return;
                default:
                    cout << "OOps! you have chosen wrong input. please select right option." << endl;
            }
        } while (choice!=5);
    }

    void displayMainMenu() {
        cout << "-------------------------------------------------" << endl;
        cout << "|                                                |" << endl;
        cout << "|******Welcome to the Cinema Booking System******|" << endl;
        cout << "|                                                |" << endl;
        cout << "-------------------------------------------------" << endl;
cout << endl;
        cout << "In order to use the sytem please take a look at the menu:" << endl;
        cout << "1. Choose this to know about movies in this cinema" << endl;
        cout << "2. Choose this to know about screens available and movies assigned" << endl;
        cout << "3. Choose this option to Book the tickets for the movie" << endl;
        cout << "4. This section is only for manager" << endl;
        cout << "5. Exit Option" << endl;
        cout << "-----------------------------" << endl;
    }

    void displayMovieInfo() {
        cout << "Information about the movies" << endl;
        cout << "------------" << endl;
        cout << "Available movies are:" << endl;
        for (int i = 0; i < movies.size(); i++) {
            cout << i + 1 << ". " << movies[i].getTitle() << endl;
        }
        cout << "Enter a number corresponding to the movie that you wish to know more about ";
        int movieNumber;
        cin >> movieNumber;

        if (movieNumber >= 1 && movieNumber <= movies.size()) {
            Movie selectedMovie = movies[movieNumber - 1];
            selectedMovie.displayMovieInfo();
        } else {
            cout << "Invalid movie number. Please try again." << endl;
        }
        cout << "-----------------------------" << endl;
    }

    void displayScreenInfo() {
        cout << "Screen Info" << endl;
        cout << "------------" << endl;
        for (Screen& screen : screens) {
            screen.displayScreenInfo();
        }
        cout << "-----------------------------" << endl;
    }

    void managerSection() {
        int choice;
        do {
            displayManagerMenu();
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
                case 1:
                    assignMoviesToScreens();
                    break;
                case 2:
                    setMovieTimings();
                    break;
                case 3:
                    return;
                default:
                    cout << "Invalid choice. Please try again." << endl;
            }
        } while (true);
    }

    void displayManagerMenu() {
        cout << "Manager Section" << endl;
        cout << "------------" << endl;
        cout << "Please select an option:" << endl;
        cout << "1. Assign Movies to Screens" << endl;
        cout << "2. Set Movie Timings" << endl;
        cout << "3. Go back to Main Menu" << endl;
        cout << "-----------------------------" << endl;
    }

    void assignMoviesToScreens() {
        cout << "Set the desired movie to the screen" << endl;
        cout << "The available movies are:" << endl;
        for (int i = 0; i < movies.size(); i++) {
            cout << i + 1 << ". " << movies[i].getTitle() << endl;
        }

        for (Screen& screen : screens) {
            int movieNumber;
            cout << "Enter the movie number to set that movie to Screen " << screen.getScreenNumber() << ": ";
            cin >> movieNumber;

            if (movieNumber >= 1 && movieNumber <= movies.size()) {
                Movie selectedMovie = movies[movieNumber - 1];
                screen.assignMovie(selectedMovie.getTitle());
                cout << "Movie " << selectedMovie.getTitle() << " assigned to Screen " << screen.getScreenNumber() << "." << endl;
            } else {
                cout << "Oops! you chose wrong movie number . Please try again." << endl;
            }
        }
        cout << "**************************" << endl;
    }

    void setMovieTimings() {
    cout << "Set the timings for the movie" << endl;
    for (Screen& screen : screens) {
        cout << "The timing for the screen " << screen.getScreenNumber() << endl;

        int startTimeHour, startTimeMinute, endTimeHour, endTimeMinute;
        char colon;

        cout << "Start time (HH:MM): ";
        if (!(cin >> startTimeHour >> colon >> startTimeMinute) || colon != ':') {
            cout << "Invalid start time format. Please enter the time in HH:MM format." << endl;
            return;
        }

        cout << "End time (HH:MM): ";
        if (!(cin >> endTimeHour >> colon >> endTimeMinute) || colon != ':') {
            cout << "Invalid end time format. Please enter the time in HH:MM format." << endl;
            return;
        }

        // Check if the start time is earlier than the end time
        if (startTimeHour > endTimeHour || (startTimeHour == endTimeHour && startTimeMinute >= endTimeMinute)) {
            cout << "Invalid time range. The end time must be later than the start time." << endl;
            return;
        }

        string startTime = to_string(startTimeHour) + ":" + to_string(startTimeMinute);
        string endTime = to_string(endTimeHour) + ":" + to_string(endTimeMinute);
        screen.setMovieTiming(startTime, endTime);
        cout << "The timings of the movie are set: " << startTime << " - " << endTime << endl;
    }
    cout << "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^" << endl;
}

    void bookTickets() {
    cout << "Book Tickets" << endl;
    cout << "------------" << endl;
    string movieTitle;
    cout << "Enter the movie title: ";
    cin.ignore();
    getline(cin, movieTitle);

    // Check if the entered movie title is valid
    bool validMovie = false;
    for (const Movie& movie : movies) {
        if (movie.getTitle() == movieTitle) {
            validMovie = true;
            break;
        }
    }

    if (!validMovie) {
        cout << "Invalid movie title. Please try again." << endl;
        cout << "-----------------------------" << endl;
        return;
    }

    int adultTickets, childrenTickets, seniorTickets, studentTickets;
    cout << "Enter the number of adult tickets: ";
    cin >> adultTickets;
    cin.ignore(); // Clear the newline character

    cout << "Enter the number of children tickets: ";
    cin >> childrenTickets;
    cin.ignore(); // Clear the newline character

    cout << "Enter the number of senior tickets: ";
    cin >> seniorTickets;
    cin.ignore(); // Clear the newline character

    cout << "Enter the number of student tickets: ";
    cin >> studentTickets;
    cin.ignore(); // Clear the newline character

    // Check if the ticket quantities are non-negative
    if (adultTickets < 0 || childrenTickets < 0 || seniorTickets < 0 || studentTickets < 0) {
        cout << "Invalid ticket quantity. Please enter non-negative values." << endl;
        cout << "-----------------------------" << endl;
        return;
    }

    double totalPrice = calculateTotalPrice(adultTickets, childrenTickets, seniorTickets, studentTickets);

    string paymentMethod;
    cout << "Enter the payment method (Cash or Card): ";
    cin.ignore(); // Clear the newline character
    getline(cin, paymentMethod);

    string showDate;
    cout << "Enter the date of the show (YYYY MM DD): ";
    cin.ignore(); // Clear the newline character
    getline(cin, showDate);

    cout << "Tickets booked successfully!" << endl;
    cout << "Receipt:" << endl;
    cout << "Movie: " << movieTitle << endl;
    cout << "Date: " << showDate << endl;
    cout << "Total Amount: $" << totalPrice << endl;
    cout << "Payment Method: " << paymentMethod << endl;
    cout << "Enjoy the show!" << endl;
    cout << "-----------------------------" << endl;
}


    double calculateTotalPrice(int adultTickets, int childrenTickets, int seniorTickets, int studentTickets) {
    // Define the prices for each ticket type
    double adultPrice = 9.50;
    double childrenPrice = 5.50;
    double seniorPrice = 6.50;
    double studentPrice = 7.50;

    // Calculate the total price based on the ticket quantities and prices
    double totalPrice = adultTickets * adultPrice +
                        childrenTickets * childrenPrice +
                        seniorTickets * seniorPrice +
                        studentTickets * studentPrice;

    return totalPrice;
}

};

int main() {
    // Create CinemaBookingSystem instance
    CinemaBookingSystem cinemaBookingSystem;

    // Add movies
    Movie movie1("Troy", "This is a demo movie A.", "Action", 120, "Tom", "Sony Pictures", "2023-06-29");
    Movie movie2("Dunkirk", "This is a demo movie B.", "Musical", 90, "Emma", "Lionsgate", "2023-06-29");
    Movie movie3("Fury", "This is a demo movie C.", "Drama", 120, "George", "Universal Pictures", "2023-06-29");

    cinemaBookingSystem.addMovie(movie1);
    cinemaBookingSystem.addMovie(movie2);
    cinemaBookingSystem.addMovie(movie3);

    // Add screens
    Screen screen1(1, 100, "Dolby Atmos");
    Screen screen2(2, 150, "IMAX");
    Screen screen3(3, 80, "Standard");

    cinemaBookingSystem.addScreen(screen1);
    cinemaBookingSystem.addScreen(screen2);
    cinemaBookingSystem.addScreen(screen3);

    // Run the cinema booking system
    cinemaBookingSystem.run();

    return 0;
}
