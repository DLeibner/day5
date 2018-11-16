#include "pch.h"
#include "Factory.h"
#include <iostream>
#include <tuple>
#include <fstream>

void StreamToConsole(const std::wostream& stream)
{
  std::wcout << stream.rdbuf() << std::endl;
}

factory::factory() : seq(), availableBlocks(),
  userCommandsMessage("0 = display sequence\n"
      "1 = add block\n"
      "2 = delete block\n"
      "3 = move desired block to begin\n"
      "4 = insert input value and evaluate through sequence\n"
    "5 = insert file name with input values, evaluate for each input and store result to file \n\n")
{
  fillAvailableBlocks();
}

std::string factory::GetUserCommandsMessage()
{
  return userCommandsMessage;
}

std::unique_ptr<Block> factory::block_factory(const BlockId id, const std::vector<double>& params)
{
  switch (id)
  {
  case BlockId::identity:
    return std::make_unique<identity>();
  case BlockId::addition:
    return std::make_unique<addition>(params[0]);
  case BlockId::multiplication:
    return std::make_unique<multiplication>(params[0]);
  case BlockId::power:
    return std::make_unique<power>(params[0]);
  case BlockId::limit:
    return std::make_unique<limit>(params[0], params[1]);
  case BlockId::condition:
    return std::make_unique<condition>(params[0]);
  default:
    return nullptr;
  }
}

std::string factory::run(const int input)
{
  std::string userMessage;
  bool save = false;
  switch (input)
  {
  case 0:
    userMessage = CaseDisplaySequence();
    break;
  case 1:
    userMessage = CaseAddBlock();
    save = true;
    break;
  case 2:
    userMessage = CaseDeleteBlock();
    save = true;
    break;
  case 3:
    userMessage = CaseMoveToBegin();
    save = true;
    break;
  case 4:
    userMessage = CaseExecuteSequence();
    break;
  case 5:
    userMessage = CaseExecuteSequenceFromFile();
    break;
  default:
    std::string message("\nUndefined input value, please enter valid command \n\n");
    userMessage = message.append(userCommandsMessage);
    break;
  }

  if (save)
  {
    SaveSequenceToFile();
  }

  return userMessage;
}

void factory::fillAvailableBlocks()
{
  std::wstringstream ss;
  ss << "Available blocks: " << std::endl;
  std::vector<double> v = { 0.0, 0.0 };
  for (auto it = std::begin(BlockIds); it != std::end(BlockIds); ++it)
  {
    availableBlocks[*it] = block_factory(*it, v);
    ss << static_cast<int>(*it) << " - " <<
      availableBlocks[*it]->GetName() << std::endl;
  }

  availableBlocksMessage = ss.str();
}

std::string factory::CaseDisplaySequence()
{
  std::wstringstream stream = seq.displaySequence();
  StreamToConsole(stream);

  return std::string("\nSequence displayed \n\n");
}

std::pair<int, std::wstring> factory::requestAdditionalParams(const int id)
{
  int num = 0;
  std::wstringstream ss(L"");
  auto it = availableBlocks.find(static_cast<BlockId>(id));
  if (it != availableBlocks.end())
  {
    ss = it->second->GetArgumentsType();
    num = it->second->GetNumberOfParams();
  }
  else
  {
    ss << L"Block with id " << id << " doesn't exist!" << std::endl;
  }

  return std::make_pair(num, ss.str());
}

std::string factory::CaseAddBlock()
{
  std::wcout << availableBlocksMessage;

  int id;
  std::cin >> id;

  std::pair<int, std::wstring> pair = requestAdditionalParams(id);
  std::wcout << pair.second;

  // store additional params to vector and call block_factory
  std::vector<double> v;
  double param;
  for (int i = 0; i < pair.first; ++i)
  {
    std::cin >> param;
    v.push_back(param);
  }

  seq.addBlock(block_factory(static_cast<BlockId>(id), v));

  return std::string("\nBlock added \n\n");
}

std::string factory::CaseDeleteBlock()
{
  std::cout << "\nEnter index of the block in the sequence that will be deleted\n";
  int index;
  std::cin >> index;

  bool ok = seq.deleteBlock(index);
  std::string message = ok ? "\nBlock deleted \n\n" :
    "\nBlock with entered index doesn't exist \n\n";

  return message;
}

std::string factory::CaseMoveToBegin()
{
  std::cout << "\nEnter index of block that will be moved to begin\n";

  int index;
  std::cin >> index;
  bool ok = seq.moveToBegin(index);
  std::string message = ok ? "\nSelected block moved to begin \n\n" :
    "\nBlock with entered index doesn't exist \n\n";

  return message;
}

std::string factory::CaseExecuteSequence()
{
  std::cout << "\nInsert input value for sequence evaluation" << std::endl;
  double value;
  std::cin >> value;
  value = seq.executeSequence(value);
  std::cout << "\nResult = " << value << std::endl;

  return std::string("\nInput value evaluated through sequence \n\n");
}

std::string factory::CaseExecuteSequenceFromFile()
{
  std::cout << "\nEnter file name with input values:\n";

  std::wstring file;
  std::wcin >> file;

  bool ok = seq.executeSequenceFromFile(file);

  std::string message = ok ? "\nSequence executed with values from selected file and result stored in Results.txt \n\n"
    : "\nFile with input values not found!";

  return message;
}

void factory::SaveSequenceToFile()
{
  std::wstringstream stream = seq.displaySequence();

  std::wofstream f("Sequence.txt");
  std::wstring s;
  while (stream >> s)
  {
    f << s << std::endl;
  }
}
