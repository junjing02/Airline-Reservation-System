# Flight Booking System

**Course:** Programming Concepts and Practices

## Overview

This C++ console application implements a simple flight booking system. It allows users to:

* **View Available Flights:** Reads `flight.txt` to list flight IDs, destinations, and departure times.
* **User Account Management:** Sign up, log in, and store credentials in `user.txt`.
* **Book Flights:** Logged-in users can choose a destination, select a flight, pick a seat type (premium or standard), and complete a mock payment. Bookings are saved to `reserved.txt`.
* **Booking History:** Users can view and edit their past bookings.

Administrators (default credentials: `admin`/`admin`) can:

* **Manage Users:** View all registered users.
* **Manage Flights:** Add or remove flights from `flight.txt`.
* **Generate Reports:** Produce a simple booking report.

## Technical Details

* Built using standard C++ libraries (`<iostream>`, `<fstream>`, `<string>`, etc.).
* Uses Windows-specific API (`<windows.h>`) for console handling and window maximization.
* Data persistence via plain text files:

  * `flight.txt` for flight schedules
  * `user.txt` for account credentials
  * `reserved.txt` for booked tickets

## Usage

1. Compile with a Windows-compatible C++ compiler.
2. Run the executable; the console window will maximize at startup.
3. Follow on-screen prompts to navigate user or admin menus.




