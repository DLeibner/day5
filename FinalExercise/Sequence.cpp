#include "pch.h"
#include "Sequence.h"
#include <fstream>
#include <iterator>

Sequence::Sequence() : blocks()
{
}

void Sequence::addBlock(std::unique_ptr<Block> block)
{
  blocks.push_back(std::move(block));
}

double Sequence::executeSequence(double input)
{
  for (auto i = blocks.cbegin(); i != blocks.cend(); ++i)
  {
    input = (*i)->Calculate(input);
  }

  return input;
}

bool Sequence::deleteBlock(int index)
{
  --index;
  bool ok = false;
  if (index < blocks.size() && index >= 0)
  {
    blocks.erase(blocks.begin() + index);
    ok = true;
  }

  return ok;
}

bool Sequence::moveToBegin(int index)
{
  --index;
  bool ok = false;
  if (index < blocks.size() && index >= 0)
  {
    std::rotate(blocks.begin(), blocks.begin()+index, blocks.begin()+index+1);
    ok = true;
  }
  return ok;
}

std::wstringstream Sequence::displaySequence()
{
  std::wstringstream stream(L"");
  stream << "Sequence:" << '\n';
  int index = 1;

  for (auto i = blocks.cbegin(); i != blocks.cend(); ++i)
  {
    stream << index << "." << (*i)->GetName() << (*i)->GetParamValues().str() << " ";

    index++;
  }

  return stream;
}

bool Sequence::executeSequenceFromFile(const std::wstring& file)
{
  std::ifstream f(file);
  std::istream_iterator<double> in(f), ends;
  std::vector<double> inputs;
  std::copy(in, ends, std::back_inserter(inputs));

  if (inputs.size() == 0)
  {
    return false;
  }

  std::ofstream outFile("Results.txt");
  for(auto it = inputs.begin(); it != inputs.end(); ++it)
  {
    double output = executeSequence(*it);
    outFile << output << std::endl;
  }

  return true;
}
