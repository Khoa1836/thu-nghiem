#include "PrintCommand.h"

PrintCommand::PrintCommand(std::string message) :
	message(message)
{
}

void PrintCommand::execute()
{
	std::cout << this->message << '\n';
} 
