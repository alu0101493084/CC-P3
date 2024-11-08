#include "../include/Transition.hpp"

Transition:: Transition(std::string initial_state, char read_symbol, std::string final_state, char written_symbol, char movement) {
  initial_state_ = initial_state;
  read_symbol_ = read_symbol;
  written_symbol_ = written_symbol;
  final_state_ = final_state;
  movement_ = movement;
}

std::ostream& operator<<(std::ostream& os, const Transition& transition) {
  os << "Initial State: " << transition.initial_state_;
  os << " Read Symbol: " << transition.read_symbol_;
  os << " Final State: " << transition.final_state_;
  os << " Written Symbol: " << transition.written_symbol_;
  os << " Movement: " << transition.movement_;
  return os;
}