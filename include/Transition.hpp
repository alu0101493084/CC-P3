#pragma once

#include <string>
#include <vector>
#include <iostream>

class Transition {
 public:
  Transition() {}
  Transition(std::string initial_state, char read_symbol, std::string final_state, char written_symbol, char movement);
  friend std::ostream& operator<<(std::ostream& os, const Transition& transition);
  std::string get_initial_state() const { return initial_state_; }
  char get_read_symbol() const { return read_symbol_; }
  char get_written_symbol() const { return written_symbol_; }
  std::string get_final_state() const { return final_state_; }
  char get_movement() const { return movement_; }
 private:
  std::string initial_state_;
  char read_symbol_;
  std::string final_state_;
  char written_symbol_;
  char movement_;
};