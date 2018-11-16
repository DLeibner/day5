#include "pch.h"
#include "Blocks.h"
#include <algorithm>

double identity::Calculate(const double input)
{
  return input;
}

std::wstring identity::GetName()
{
  return L"identity";
}

std::wstringstream identity::GetArgumentsType()
{
  std::wstringstream ss(L"\nNo additional params");
  return ss;
}

int identity::GetNumberOfParams()
{
  return 0;
}

std::wstringstream identity::GetParamValues()
{
  std::wstringstream ss;
  ss << "()";
  return ss;
}

addition::addition(const double a) : BlockWithOneParam(a)
{
}

double addition::Calculate(const double input)
{
  return input + param;
}

std::wstring addition::GetName()
{
  return L"addition";
}

multiplication::multiplication(double a) : BlockWithOneParam(a)
{
}

double multiplication::Calculate(const double input)
{
  return input * param;
}

std::wstring multiplication::GetName()
{
  return L"multiplication";
}

power::power(double a) : BlockWithOneParam(a)
{
}

double power::Calculate(const double input)
{
  return std::pow(input, param);
}

std::wstring power::GetName()
{
  return L"power";
}

limit::limit(double a, double b) : BlockWithTwoParams(a, b)
{
}

double limit::Calculate(const double input)
{
  return std::clamp(input, param1, param2);
}

std::wstring limit::GetName()
{
  return L"limit";
}

condition::condition(double a) : BlockWithOneParam(a)
{
}

double condition::Calculate(const double input)
{
  if (input == param)
  {
    return 0;
  }
  else if (input < param)
  {
    return -1;
  }
  else
  {
    return 1;
  }
}

std::wstring condition::GetName()
{
  return L"condition";
}
