#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <list>
#include <algorithm>
#include <stdexcept>
#include "Transition.hpp"

class MTD {
 public:
  MTD() {}
  MTD(std::string filename);
  bool recognized_string(std::string string);
  void check_string(const std::string& string);
  void checking_formal_definition(std::vector<std::string> states, std::vector<std::string> final_states, std::vector<char> alphabet, std::vector<char> tape_alphabet, std::string initial_state, char white_symbol, std::vector<Transition> transitions);
  friend std::ostream& operator<<(std::ostream& os, const MTD& mtd);
 private:
  bool recursive_recognition(std::string actual_state, std::list<char>::iterator head, std::vector<Transition> transitions);
  std::vector<std::string> states_;
  std::vector<std::string> final_states_;
  std::vector<char> alphabet_;
  std::vector<char> tape_alphabet_;
  char white_symbol_;
  std::vector<Transition> transitions_;
  std::string initial_state_;
  std::list<char> tape_;
};