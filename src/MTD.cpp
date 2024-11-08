#include "../include/MTD.hpp"
#include "../include/Transition.hpp"

MTD::MTD(std::string file_name) {
  std::ifstream file;
  std::string input;
  std::vector<std::string> states;
  std::vector<std::string> final_states;
  std::istringstream line;
  std::string state;
  std::vector<char> alphabet;
  char symbol;
  std::vector<char> tape_alphabet;
  char tape_symbol;
  std::string initial_state;
  char white_symbol;
  std::string final_state;
  std::vector<Transition> transitions;
  std::string transition_initial_state;
  char transition_read_symbol;
  std::string transition_final_state;
  char transition_written_symbol;
  char transition_movement;
  file.open(file_name.c_str(), std::ios_base::in);
  while (getline(file, input)) {
    if (input[0] == '#') {
      continue;
    } else {
      line.str(input);
      while (line >> state) {
        states.push_back(state);
      }
      break;
    }
  }
  getline(file, input);
  line.clear();
  line.str(input);
  while (line >> symbol) {
    alphabet.push_back(symbol);
  }
  getline(file, input);
  line.clear();
  line.str(input);
  while (line >> tape_symbol) {
    tape_alphabet.push_back(tape_symbol);
  }
  file >> initial_state;
  file >> white_symbol;
  getline(file, input);
  getline(file, input);
  line.clear();
  line.str(input);
  while (line >> final_state) {
    final_states.push_back(final_state);
  }
  while(getline(file, input)) {
    line.clear();
    line.str(input);
    line >> transition_initial_state;
    line >> transition_read_symbol;
    line >> transition_final_state;
    line >> transition_written_symbol;
    line >> transition_movement;
    Transition transition(transition_initial_state, transition_read_symbol, transition_final_state, transition_written_symbol, transition_movement);
    transitions.push_back(transition);
  }
  checking_formal_definition(states, final_states, alphabet, tape_alphabet, initial_state, white_symbol, transitions);
  states_ = states;
  final_states_ = final_states;
  alphabet_ = alphabet;
  tape_alphabet_ = tape_alphabet;
  initial_state_ = initial_state;
  white_symbol_ = white_symbol;
  transitions_ = transitions;
  file.close();
}

void MTD::checking_formal_definition(std::vector<std::string> states, std::vector<std::string> final_states, std::vector<char> alphabet, std::vector<char> tape_alphabet, std::string initial_state, char white_symbol, std::vector<Transition> transitions) {
  if (std::find(states.begin(), states.end(), initial_state) == states.end()) {
    throw std::invalid_argument("El estado inicial no es parte de los estados.");
  }

  for (const auto& final_state : final_states) {
    if (std::find(states.begin(), states.end(), final_state) == states.end()) {
      throw std::invalid_argument("Un estado final no es parte de los estados.");
    }
  }

  if (std::find(tape_alphabet.begin(), tape_alphabet.end(), white_symbol) == tape_alphabet.end()) {
    throw std::invalid_argument("El símbolo blanco no es parte del alfabeto de la cinta.");
  }

  for (const auto& transition : transitions) {
    if (std::find(states.begin(), states.end(), transition.get_initial_state()) == states.end()) {
      throw std::invalid_argument("El estado inicial de la transición no es parte de los estados.");
    }

    if (std::find(states.begin(), states.end(), transition.get_final_state()) == states.end()) {
      throw std::invalid_argument("El estado final de la transición no es parte de los estados.");
    }

    if (std::find(tape_alphabet.begin(), tape_alphabet.end(), transition.get_read_symbol()) == tape_alphabet.end()) {
      throw std::invalid_argument("El símbolo leído de la cinta en una transición no es parte del alfabeto de la cinta.");
    }

    if (std::find(tape_alphabet.begin(), tape_alphabet.end(), transition.get_written_symbol()) == tape_alphabet.end()) {
      throw std::invalid_argument("El símbolo escrito en la cinta en una transición no es parte del alfabeto de la cinta.");
    }

    if (transition.get_movement() != 'R' && transition.get_movement() != 'L') {
      throw std::invalid_argument("El movimiento de la cinta en una transición no es válido.");
    }
  }
}

bool MTD::recognized_string(std::string string) {
  bool result;
  tape_.clear();
  if (string.size() == 0) {
    tape_.push_back(white_symbol_);
  } else {
  for (int i = 0; i < string.size(); i++) {
    tape_.push_back(string[i]);
  }
  }
  std::list<char>::iterator head = tape_.begin();
  result = recursive_recognition(initial_state_, head, transitions_);
  while (tape_.size() > 1 && tape_.front() == white_symbol_) {
    tape_.pop_front();
  }
  if (tape_.front() != white_symbol_) {
    tape_.push_front(white_symbol_);
  }
  while (tape_.size() > 1 && tape_.back() == white_symbol_) {
    tape_.pop_back();
  }
  if (tape_.back() != white_symbol_) {
    tape_.push_back(white_symbol_);
  }
  std::cout << "Cinta final: ";
  for (char symbol : tape_) {
    std::cout << symbol;
  }
  std::cout << std::endl;
  return result;
}

bool MTD::recursive_recognition(std::string actual_state, std::list<char>::iterator head, std::vector<Transition> transitions) {
  if (std::find(final_states_.begin(), final_states_.end(), actual_state) != final_states_.end()) {
    return true;
  } else {
    for (int i = 0; i < transitions.size(); i++) {
      if (actual_state == transitions[i].get_initial_state() && *head == transitions[i].get_read_symbol()) {
        *head = transitions[i].get_written_symbol();
        if (transitions[i].get_movement() == 'R') {
          head++;
          if (head == tape_.end()) {
            tape_.push_back(white_symbol_);
            head = --tape_.end();
          }
        } else if (transitions[i].get_movement() == 'L') {
          if (head == tape_.begin()) {
            tape_.push_front(white_symbol_);
            head = tape_.begin();
          } else {
            head--;
          }
        }
        return (recursive_recognition(transitions[i].get_final_state(), head, transitions));
      }
    }
  }
  return false;
}

std::ostream& operator<<(std::ostream& os, const MTD& mtd) {
  os << "States: ";
  for (int i = 0; i < mtd.states_.size(); i++) {
    os << mtd.states_[i] << " ";
  }
  os << "\nAlphabet: ";
  for (int i = 0; i < mtd.alphabet_.size(); i++) {
    os << mtd.alphabet_[i] << " ";
  }
  os << "\nTape Alphabet: ";
   for (int i = 0; i < mtd.tape_alphabet_.size(); i++) {
    os << mtd.tape_alphabet_[i] << " ";
  }
  os << "\nInitial State: " << mtd.initial_state_;
  os << "\nWhite Symbol: " << mtd.white_symbol_;
  os << "\nFinal States: ";
  for (int i = 0; i < mtd.final_states_.size(); i++) {
    os << mtd.final_states_[i] << " ";
  }
  os << "\nTransitions:\n";
  for (int i = 0; i < mtd.transitions_.size(); i++) {
    os << mtd.transitions_[i] << std::endl;
  }
  return os;
}

void MTD::check_string(const std::string& string) {
  for (char symbol : string) {
    if (std::find(alphabet_.begin(), alphabet_.end(), symbol) == alphabet_.end()) {
      throw std::invalid_argument("La cadena contiene símbolos que no están en el alfabeto del lenguaje que reconoce la MTD.");
    }
  }
}