#include "parser.hpp"

void	printError(const std::string& msg)
{
	std::cerr << BOLD_ON << RED_COLOR << "[ERROR]: " << BOLD_OFF << RESET_COLOR << msg << std::endl;
}