// BufferOverflow.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iomanip>
#include <iostream>
#include <string>      // Required for std::string
#include <limits>      // Required for std::numeric_limits
int main()
{
  std::cout << "Buffer Overflow Example" << std::endl;

  // TODO: The user can type more than 20 characters and overflow the buffer, resulting in account_number being replaced -
  //  even though it is a constant and the compiler buffer overflow checks are on.
  //  You need to modify this method to prevent buffer overflow without changing the account_number
  //  variable, and its position in the declaration. It must always be directly before the variable used for input.
  //  You must notify the user if they entered too much data.

  const std::string account_number = "CharlieBrown42";
  char user_input[20];

  std::cout << "Enter a value: ";
  std::cin.getline(user_input, sizeof(user_input));

  if (std::cin.fail()) { 
    std::cin.clear(); // Reset error flags in stream
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Skip any char still in buffer
    std::cerr << "Error: Input too long. Buffer overflow prevented." << std::endl;
    return 1;
  }

  std::cout << "You entered: " << user_input << std::endl;
  std::cout << "Account Number = " << account_number << std::endl;
  return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu
