#ifndef EMFILEPARSER_H
#define EMFILEPARSER_H

#define WORDBREAK ' '

#include <vector>
#include <string>
#include <fstream>
#include <cstdlib>
#include "fileParser.h"

std::vector<double> parseInitY(std::string filename);

std::vector<std::vector<std::vector<double> > >
  parseInitX(std::string filename);

std::vector<std::vector<unsigned short> >
  parseData(std::string filename);

#endif