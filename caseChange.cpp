#include "caseChange.h"

std::string toUpper(std::string str) {
  std::string translated;
  for(int i = 0; i < str.size(); i++) {
    translated.push_back(toupper(str[i]));
  }
  return translated;
}

std::string toLower(std::string str) {
  std::string translated;
  for(int i = 0; i < str.size(); i++) {
    translated.push_back(tolower(str[i]));
  }
  return translated;
}