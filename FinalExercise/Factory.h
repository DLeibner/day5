#pragma once
#include <memory>
#include <vector>
#include <map>
#include "Sequence.h"

class factory
{
public:
  factory();
  std::string run(const int input);
  std::string GetUserCommandsMessage();

private:
  Sequence seq;
  std::map<BlockId, std::unique_ptr<Block>> availableBlocks;
  std::wstring availableBlocksMessage;
  std::string userCommandsMessage;

  std::unique_ptr<Block> block_factory(const BlockId id, const std::vector<double>& params);
  void fillAvailableBlocks();
  std::pair<int, std::wstring> requestAdditionalParams(const int id);

  std::string CaseDisplaySequence();
  std::string CaseAddBlock();
  std::string CaseDeleteBlock();
  std::string CaseMoveToBegin();
  std::string CaseExecuteSequence();
  std::string CaseExecuteSequenceFromFile();

  void SaveSequenceToFile();
};

void StreamToConsole(const std::wostream& stream);
