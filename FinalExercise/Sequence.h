#pragma once
#include <vector>
#include "Blocks.h"

class Sequence
{
public:
  Sequence();
  void addBlock(std::unique_ptr<Block>);
  double executeSequence(double input);
  bool deleteBlock(int index);
  bool moveToBegin(int index);
  std::wstringstream displaySequence();
  bool executeSequenceFromFile(const std::wstring& file);

private:
  std::vector<std::unique_ptr<Block>> blocks;
};
