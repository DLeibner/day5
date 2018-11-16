#pragma once
#include <sstream>

class Block
{
public:
  virtual ~Block() = default;

  virtual double Calculate(double input) = 0;
  virtual std::wstring GetName() = 0;
  virtual std::wstringstream GetArgumentsType() = 0;
  virtual int GetNumberOfParams() = 0;
  virtual std::wstringstream GetParamValues() = 0;
};

template<typename T>
class BlockWithOneParam : public Block
{
public:

  BlockWithOneParam(T a) : param(a)
  {
  }
  std::wstringstream GetArgumentsType() override
  {
    std::wstringstream ss;
    ss << "\nAdd 1 additional argument:" <<
      "\nargument type " << typeid(param).name() << std::endl;
    return ss;
  }

  int GetNumberOfParams() override
  {
    return 1;
  }

  std::wstringstream GetParamValues() override
  {
    std::wstringstream ss;
    ss << "(" << param << ")";
    return ss;
  }

protected:
  T param;
};

template<typename T1, typename T2>
class BlockWithTwoParams : public Block
{
public:
  BlockWithTwoParams(T1 a, T2 b) : param1(a), param2(b)
  {
  }

  std::wstringstream GetArgumentsType() override
  {
    std::wstringstream ss;
    ss << "\nAdd 2 additional arguments:" <<
      "\n1. argument type " << typeid(param1).name() <<
      "\n2. argument type " << typeid(param2).name() << std::endl;
    return  ss;
  }

  int GetNumberOfParams() override
  {
    return 2;
  }

  std::wstringstream GetParamValues() override
  {
    std::wstringstream ss;
    ss << "(" << param1 << ", " << param2 << ")";
    return ss;
  }

protected:
  T1 param1;
  T2 param2;
};

class identity : public Block
{
public:
  double Calculate(double input) override;
  std::wstring GetName() override;
  std::wstringstream GetArgumentsType() override;
  int GetNumberOfParams() override;
  std::wstringstream GetParamValues() override;
};

class addition : public BlockWithOneParam<double>
{
public:
  addition(double a);
  double Calculate(double input) override;
  std::wstring GetName() override;
};

class multiplication : public BlockWithOneParam<double>
{
public:
  multiplication(double a);
  double Calculate(double input) override;
  std::wstring GetName() override;
};

class power : public BlockWithOneParam<double>
{
public:
  power(double a);
  double Calculate(double input) override;
  std::wstring GetName() override;
};

class limit : public BlockWithTwoParams<double, double>
{
public:
  limit(double a, double b);
  double Calculate(double input) override;
  std::wstring GetName() override;
};

class condition : public BlockWithOneParam<double>
{
public:
  condition(double a);
  double Calculate(double input) override;
  std::wstring GetName() override;
};

enum class BlockId
{
  identity = 1,
  addition = 2,
  multiplication = 3,
  power = 4,
  limit = 5,
  condition = 6
};

const BlockId BlockIds[] = { BlockId::identity, BlockId::addition, BlockId::multiplication,
  BlockId::power, BlockId::limit, BlockId::condition };
