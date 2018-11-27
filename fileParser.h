#ifndef FILEPARSER_H
#define FILEPARSER_H

#define UNTIL_END -1

#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>

// parse into strings
std::vector<std::vector<std::string> > parseFileStr(std::string filename,
  char wordBreak);

// parse into doubles
std::vector<std::vector<double> > parseFileDouble
  (std::string filename, char wordBreak);

// parse into booleans
std::vector<std::vector<bool> > parseFileBool(std::string filename,
  char wordBreak);

#endif