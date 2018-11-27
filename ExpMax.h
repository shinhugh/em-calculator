#ifndef EXPMAX_H
#define EXPMAX_H

#define WORDBREAK ' '
#define INVALID_NAME ""

#include <string>
#include <vector>
#include <map>
#include <cctype>
#include "EM.h"
#include "emFileParser.h"

/*
 * Format for input files:
 *
 * initY_file: File with initial probabilities for P(Y = i)
 *   List each probability on a new line, going down in
 *   increasing order
 *
 * initX_file: File with initial probabilities for
 * P(X_c = j | Y = i)
 *   State max value of c (n) on first line (nothing else)
 *   i increases downward in segments of lines
 *   c increases downward in new lines, resetting at new i
 *   j goes rightward in inputs separated by single spaces
 *   i.e.:
 *
 *   3 (<- max value of c)
 *   ^ ^ ---j-->
 *   | c
 *   i v
 *   | ^
 *   | c
 *   v v
 *
 * data_file: File with all sample data
 *   Each sample is represented by a single line
 *   Separate each entry for x_c with single spaces
 *   t increases downward
 *   c increases rightward
 *   0: no input
 *   Assign values 1+ to some meaning, not skipping any #s
 */

// wrapper class for EM, narrowing down usage
class ExpMax {
private:

  // does all the math
  EM calculator;

  // key: sample/person name
  // value: t value (sample number)
  std::map<std::string, int> sampleID;

  // key: parameter/subject name
  // value: c value
  std::map<std::string, int> paramID;

  // key: j value
  // value: input option name
  std::map<int, std::string> inputID;

public:

  // constructor
  ExpMax(std::string initY_file, std::string initX_file,
    std::string data_file);

  // get name of input option that is most likely for the
  // specified parameter given the specified sample
  std::string mostProbVal(std::string sampleName,
    std::string paramName);
};

#endif