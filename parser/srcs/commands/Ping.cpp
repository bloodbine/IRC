#include "parser.hpp"

Ping::Ping(const std::vector<std::string>& cmd) { if (cmd.size() != 1) throw std::invalid_argument("Invalid syntax"); }
Ping::~Ping() {}
