#pragma once

#include "ICommand.h"
#include <iostream>

class PrintCommand : public ICommand
{
private:
	std::string message;
public:
	PrintCommand(std::string message);
	void execute() override;
};

