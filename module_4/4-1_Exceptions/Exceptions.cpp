// Exceptions.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

// Define a custom exception derived from std::exception
class CustomException : public std::exception {
public:
    const char* what() const noexcept override {
        return "Custom exception occurred.";
    }
};

bool do_even_more_custom_application_logic()
{
  // DONE: Throw any standard exception

  std::cout << "Running Even More Custom Application Logic." << std::endl;
  // Throwing a standard exception
  throw std::logic_error("Logic error occurred in even more custom logic.");

  return true; // This line will not be reached due to the exception
}
void do_custom_application_logic()
{
  // DONE: Wrap the call to do_even_more_custom_application_logic()
  //  with an exception handler that catches std::exception, displays
  //  a message and the exception.what(), then continues processing
  std::cout << "Running Custom Application Logic." << std::endl;

  try {
      if (do_even_more_custom_application_logic()) {
          std::cout << "Even More Custom Application Logic Succeeded." << std::endl;
      }
  } catch (const std::exception& e) {
      // Catching and reporting std::exception from nested logic
      std::cerr << "\tStandard exception caught in custom logic: " << e.what() << std::endl;
  }

  // DONE: Throw a custom exception derived from std::exception
  //  and catch it explictly in main

  // Throw a custom exception to be caught in main
  throw CustomException();

  std::cout << "Leaving Custom Application Logic." << std::endl;

}

float divide(float num, float den)
{
  // DONE: Throw an exception to deal with divide by zero errors using
  //  a standard C++ defined exception✓
  if (den == 0) {
    throw std::runtime_error("Attempted to divide by zero.\n");
  }
  return (num / den);
}

void do_division() noexcept
{
  //  DONE: create an exception handler to capture ONLY the exception thrown
  //  by divide.✓

  float numerator = 10.0f;
  float denominator = 0;

  try {
      auto result = divide(numerator, denominator);
      std::cout << "divide(" << numerator << ", " << denominator << ") = " << result << std::endl;
  } catch (const std::runtime_error& e) {
      std::cerr << "\tException occurred during division: " << e.what();
  }
}

int main()
{
  std::cout << "Exceptions Tests!" << std::endl;

  // DONE: Create exception handlers that catch (in this order):
  //  your custom exception
  //  std::exception
  //  uncaught exception 
  //  that wraps the whole main function, and displays a message to the console.
  try {
        do_division();

        try {
            do_custom_application_logic();
        } catch (const CustomException& ce) {
            // Explicitly catching the custom exception
            std::cerr << "\tCustom exception caught in main: " << ce.what() << std::endl;
        }

    } catch (const std::exception& e) {
        // Fallback for other unhandled standard exceptions
        std::cerr << "\tUnhandled std::exception: " << e.what() << std::endl;
    } catch (...) {
        // Catch-all handler for any other unexpected exceptions
        std::cerr << "\tUnhandled unknown exception occurred." << std::endl;
    }

    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu
