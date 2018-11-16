#include "pch.h"
#include <iostream>
#include "Factory.h"

int main()
{
  int input;
  factory f;

  std::cout << f.GetUserCommandsMessage();

  while (std::cin >> input)
  {
    std::string output = f.run(input);
    std::cout << output;
  }
}
