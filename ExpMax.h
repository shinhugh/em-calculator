#ifndef EXPMAX_H
#define EXPMAX_H

#define WORDBREAK ' '
#define INVALID_NAME ""
#define DNE_BOOL false

#include <string>
#include <vector>
#include <map>
#include <cctype>
#include <utility>
#include "EM.h"
#include "fileParser.h"
#include "caseChange.h"

/*
 * Format for input files:
 *
 * initY_file: File with initial probabilities for P(Y = i)
 *   List each probability on a new line, going down in
 *   increasing order
 *
 * initX_file: File with initial probabilities for
 * P(X_c = j | Y = i)
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
  EM* calculator;

  // same values from EM
  // m is one less; m doesn't include j = 0
  int k;
  int n;
  int m;
  int T;

  // key: sample/person name
  // value: t value (sample number)
  std::map<std::string, int> sampleID;

  // key: category name
  // value: c value
  std::map<std::string, int> paramID;

  // duplicate of paramID map but key-value reversed
  // index: c-value
  // value: category name
  std::vector<std::string> paramID_rev;

  // index: j value, where 0 is now the first valid response
  // value: input option name
  std::vector<std::string> inputID;

  // do not call the following 4 private helper functions
  // only meant for use within constructor implementation

  // call 2nd
  std::vector<double> parseInitY(std::string filename);

  // call 3rd
  std::vector<std::vector<std::vector<double> > >
    parseInitX(std::string filename);

  // call 4th
  std::vector<std::vector<unsigned short> >
    parseData(std::string filename);

  // call 1st
  void parseMeanings(std::string filename);

public:

  // constructor
  ExpMax(std::string initY_file, std::string initX_file,
    std::string data_file, std::string meaning_file);

  // alternate constructor that doesn't use initY_file
  // or initX_file
  // assumes even distribution across all initial prior and
  // conditional probabilities
  // instead, a k value (total # of possible Y values) must
  // be explicitly specified
  ExpMax(int hiddenParamCount, std::string data_file,
    std::string meaning_file);

  // destructor
  ~ExpMax();

  // get name of input option that is most likely for the
  // specified parameter given the specified sample
  // pair.first (bool):
  //   true if specified sample already has an input for
  //     the specified parameter/category
  //   false otherwise
  // pair.second (string):
  //   name of most likely / already input response
  std::pair<bool, std::string> mostProbVal
    (std::string sampleName, std::string paramName);

  // get list of samples' names, sorted alphabetically
  std::vector<std::string> getSampleNames();

  // get list of categories, sorted alphabetically
  std::vector<std::string> getCategoryNames();

  // get list of valid inputs (all possible X_c = j values)
  // sorted by order given in meanings file
  std::vector<std::string> getInputNames();

  // get list of categories specified sample lacks input for
  std::vector<std::string> noResponseList(std::string sampleName);

};

#endif