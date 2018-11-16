#include "CppUnitTest.h"
#include "../FinalExercise/Blocks.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

TEST_CLASS(test_blocks)
{
public:

  TEST_METHOD(IdentityBlock)
  {
    identity i;
    double result = i.Calculate(5.6);
    Assert::AreEqual(5.6, result);
    Assert::AreEqual(std::wstring(L"identity"), i.GetName());
    Assert::AreEqual(0, i.GetNumberOfParams());
  }

  TEST_METHOD(additionBlock)
  {
    addition a(115.5);
    double result = a.Calculate(10.0);
    Assert::AreEqual(125.5, result);
    Assert::AreEqual(std::wstring(L"addition"), a.GetName());
    Assert::AreEqual(1, a.GetNumberOfParams());
  }

  TEST_METHOD(multiplicationBlock)
  {
    multiplication m(2.5);
    double result = m.Calculate(10.0);
    Assert::AreEqual(25.0, result);
    Assert::AreEqual(std::wstring(L"multiplication"), m.GetName());
    Assert::AreEqual(1, m.GetNumberOfParams());
  }

  TEST_METHOD(powerBlock)
  {
    power p(3.0);
    double result = p.Calculate(5.0);
    Assert::AreEqual(125.0, result);
    Assert::AreEqual(std::wstring(L"power"), p.GetName());
    Assert::AreEqual(1, p.GetNumberOfParams());
  }

  TEST_METHOD(limitBlock)
  {
    limit l(10.0, 550.0);
    double result = l.Calculate(200.7);
    Assert::AreEqual(200.7, result);
    result = l.Calculate(0.0);
    Assert::AreEqual(10.0, result);
    result = l.Calculate(1000.0);
    Assert::AreEqual(550.0, result);
    Assert::AreEqual(std::wstring(L"limit"), l.GetName());
    Assert::AreEqual(2, l.GetNumberOfParams());
  }

  TEST_METHOD(conditionBlock)
  {
    condition c(105.5);
    double result = c.Calculate(40.0);
    Assert::AreEqual(-1.0, result);
    result = c.Calculate(105.5);
    Assert::AreEqual(0.0, result);
    result = c.Calculate(5555.5);
    Assert::AreEqual(1.0, result);
    Assert::AreEqual(std::wstring(L"condition"), c.GetName());
    Assert::AreEqual(1, c.GetNumberOfParams());
  }
};
