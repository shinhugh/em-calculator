#include "fileParser.h"

std::vector<std::vector<std::string> > parseFileStr
  (std::string filename, char wordBreak, int firstLine = 0,
  int lastLine = UNTIL_END) {

  // outer vector holds lines
  // inner vectors hold elements from that line
  // output[line][element]
  std::vector<std::vector<std::string> > output;

  std::ifstream ifs(filename.c_str());

  // skip lines at top to get to firstLine
  for(int l = 0; l < firstLine; l++) {
    std::string trash;
    std::getline(ifs, trash);
  }

  int lineNum = firstLine;
  bool lastLineParsed = false;

  ifs.peek();
  while(!ifs.eof() && !lastLineParsed) {

    // create vector for this line
    std::vector<std::string> elements;

    // pull entire line from stream
    std::string line;
    std::getline(ifs, line);

    // break up line into different elements separated by wordBreak
    // char and add each to elements
    bool moreWords = true;
    while(moreWords) {
      size_t breakPos = line.find(wordBreak);
      elements.push_back(line.substr(0, breakPos));
      if(breakPos != std::string::npos) {
        line = line.substr(breakPos + 1);
      } else {
        moreWords = false;
      }
    }

    // add this line's elements to output vector
    output.push_back(elements);

    lineNum++;

    if(lineNum == lastLine + 1) {
      lastLineParsed = true;
    }

    // update eof
    ifs.peek();
  }

  ifs.close();

  return output;
}



std::vector<std::vector<double> > parseFileDouble
  (std::string filename, char wordBreak, int firstLine = 0,
  int lastLine = UNTIL_END) {

  // outer vector holds lines
  // inner vectors hold elements from that line
  // output[line][element]
  std::vector<std::vector<double> > output;

  std::ifstream ifs(filename.c_str());

  // skip lines at top to get to firstLine
  for(int l = 0; l < firstLine; l++) {
    std::string trash;
    std::getline(ifs, trash);
  }

  int lineNum = firstLine;
  bool lastLineParsed = false;

  ifs.peek();
  while(!ifs.eof() && !lastLineParsed) {

    // create vector for this line
    std::vector<double> elements;

    // pull entire line from stream
    std::string line;
    std::getline(ifs, line);

    // break up line into different elements separated by wordBreak
    // char and add each to elements
    bool moreWords = true;
    while(moreWords) {
      size_t breakPos = line.find(wordBreak);
      std::string untranslated = line.substr(0, breakPos);

      // translate string to double and push into elements
      elements.push_back(atof(untranslated.c_str()));

      if(breakPos != std::string::npos) {
        line = line.substr(breakPos + 1);
      } else {
        moreWords = false;
      }
    }

    // add this line's elements to output vector
    output.push_back(elements);

    lineNum++;

    if(lineNum == lastLine + 1) {
      lastLineParsed = true;
    }

    // update eof
    ifs.peek();
  }

  ifs.close();

  return output;
}



std::vector<std::vector<bool> > parseFileBool
  (std::string filename, char wordBreak, int firstLine = 0,
  int lastLine = UNTIL_END) {

  // outer vector holds lines
  // inner vectors hold elements from that line
  // output[line][element]
  std::vector<std::vector<bool> > output;

  std::ifstream ifs(filename.c_str());

  // skip lines at top to get to firstLine
  for(int l = 0; l < firstLine; l++) {
    std::string trash;
    std::getline(ifs, trash);
  }

  int lineNum = firstLine;
  bool lastLineParsed = false;

  ifs.peek();
  while(!ifs.eof() && !lastLineParsed) {

    // create vector for this line
    std::vector<bool> elements;

    // pull entire line from stream
    std::string line;
    std::getline(ifs, line);

    // break up line into different elements separated by wordBreak
    // char and add each to elements
    bool moreWords = true;
    while(moreWords) {
      size_t breakPos = line.find(wordBreak);
      std::string untranslated = line.substr(0, breakPos);

      // translate string to bool and push into elements
      if(untranslated == "0") {
        elements.push_back(0);
      } else {
        elements.push_back(1);
      }

      if(breakPos != std::string::npos) {
        line = line.substr(breakPos + 1);
      } else {
        moreWords = false;
      }
    }

    // add this line's elements to output vector
    output.push_back(elements);

    lineNum++;

    if(lineNum == lastLine + 1) {
      lastLineParsed = true;
    }

    // update eof
    ifs.peek();
  }

  ifs.close();

  return output;
}