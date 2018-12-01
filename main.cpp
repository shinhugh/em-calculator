#define IN_DIR "/"
#define INIT_Y "_initY.txt"
#define INIT_X "_initX.txt"
#define DATA "_data.txt"
#define MEANINGS "_meanings.txt"

#include <iostream>
#include "ExpMax.h"

// Command line interface for expecation-maximization utility.
int main(int argc, char **argv)
{
  // must specify file names prefix
  if (argc == 1)
  {
    std::cout << "Specify name of file set." << std::endl;
    return 0;
  }

  // file names prefix
  std::string fileSetName(argv[1]);
  // file location directory
  std::string fileDir("./sampleinput"); // <- change if necessary

  // setting up file names
  std::string initY_file = fileDir + IN_DIR + fileSetName + INIT_Y;
  std::string initX_file = fileDir + IN_DIR + fileSetName + INIT_X;
  std::string data_file = fileDir + IN_DIR + fileSetName + DATA;
  std::string meanings_file = fileDir + IN_DIR + fileSetName + MEANINGS;

  int responseNum = -1;
  while (!(responseNum == 0 || responseNum == 1))
  {
    std::cout << "Please choose what file inputs to use.\n";
    std::cout << "(0) 4 files (data, initX, initY, meanings)\n";
    std::cout << "(1) 2 files (data, meanings)\n";
    std::cin >> responseNum;
  }

  ExpMax em(initY_file, initX_file, data_file, meanings_file);
  if (responseNum == 1)
  {
    ExpMax em(4, data_file, meanings_file);
  }
  while (true)
  {
    std::vector<std::string> names = em.getSampleNames();
    // list all people/sample names
    responseNum = -1;
    while (!(responseNum >= 0 && responseNum < names.size()))
    {
      std::cout << "Choose a Name:\n";
      for (int i = 0; i < static_cast<int>(names.size()); i++)
      {
        std::cout << "(" << i << ")"
                  << " - " << names[i] << std::endl;
      }

      std::cin >> responseNum;
      if (!(responseNum >= 0 && responseNum < names.size()))
      {
        std::cout << "Invalid input\n";
      }
    }
    std::string selectedName = names[responseNum];

    responseNum = -1;
    std::vector<std::string> categories = em.getCategoryNames();
    while (!(responseNum >= 0 && responseNum < categories.size()))
    {
      std::cout << "Please choose a category.\n";
      for (int i = 0; i < static_cast<int>(categories.size()); i++)
      {
        std::cout << "(" << i << ") - " << categories[i] << std::endl;
      }
      std::cin >> responseNum;
      if (!(responseNum >= 0 && responseNum < categories.size()))
      {
        std::cout << "Invalid input\n";
      }
    }
    std::string selectedCategory = categories[responseNum];
    std::pair<bool, std::string> result = em.mostProbVal(selectedName, selectedCategory);
    if (result.first)
    {
      std::cout << selectedName << " responded that " << selectedCategory
                << " goes well with " << result.second << " moods.\n\n";
    }
    else
    {
      std::cout << selectedName << " is most likely to feel that "
                << selectedCategory << " goes well with " << result.second
                << " moods.\n\n";
    }
  }
  return 0;
}