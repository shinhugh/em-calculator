#define IN_DIR "/"
#define INIT_Y "_initY.txt"
#define INIT_X "_initX.txt"
#define DATA "_data.txt"
#define MEANINGS "_meanings.txt"
#define CATEGORIES_COUNT 48
#define INPUTS_COUNT 5
#include <limits>
#include <iostream>
#include <sstream>
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

  // int responseNum = -1;
  // while (!(responseNum == 0 || responseNum == 1))
  // {
  //   std::cout << "Please choose what file inputs to use.\n";
  //   std::cout << "(0) 4 files (data, initX, initY, meanings)\n";
  //   std::cout << "(1) 2 files (data, meanings)\n";
  //   std::cin >> responseNum;
  //   if (std::cin.fail())
  //   {
  //     std::cin.clear();
  //     std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  //     responseNum = -1;
  //   }
  // }

  // ExpMax em(initY_file, initX_file, data_file, meanings_file);
  // if (responseNum == 1)
  // {
  //   numFiles = 2;
  //   ExpMax em(4, data_file, meanings_file);
  // }

  int responseNum = -1;
  while (!(responseNum == 0 || responseNum == 1))
  {
    std::cout << "Would you like to take the survey or view the results?\n";
    std::cout << "(0) View the results\n";
    std::cout << "(1) Take the survey\n";
    std::cin >> responseNum;
    if (std::cin.fail())
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      responseNum = -1;
    }
  }

  if (!responseNum)
  {
    ExpMax em(4, data_file, meanings_file);

    while (true)
    {
      std::vector<std::string> names = em.getSampleNames();
      // list all people/sample names
      responseNum = -1;
      while (!(responseNum >= 0 && responseNum < static_cast<int>(names.size())))
      {
        std::cout << "\nChoose a Name:\n";
        for (int i = 0; i < static_cast<int>(names.size()); i++)
        {
          std::cout << "(" << i << ")"
                    << " - " << names[i] << std::endl;
        }

        std::cin >> responseNum;
        if (std::cin.fail())
        {
          std::cin.clear();
          std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
          responseNum = -1;
        }
        if (!(responseNum >= 0 && responseNum < static_cast<int>(names.size())))
        {
          std::cout << "Invalid input\n";
        }
      }
      std::string selectedName = names[responseNum];

      responseNum = -1;
      std::vector<std::string> categories = em.getCategoryNames();
      while (!(responseNum >= 0 && responseNum < static_cast<int>(categories.size())))
      {
        std::cout << "\nPlease choose a category.\n";
        for (int i = 0; i < static_cast<int>(categories.size()); i++)
        {
          std::cout << "(" << i << ") - " << categories[i] << std::endl;
        }
        std::cin >> responseNum;
        if (std::cin.fail())
        {
          std::cin.clear();
          std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
          responseNum = -1;
        }
        if (!(responseNum >= 0 && responseNum < static_cast<int>(categories.size())))
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
      do
      {
        std::cout << '\n'
                  << "Press enter to continue...";
      } while (std::cin.get() != '\n');
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
  }
  else
  {

    std::string inputName = "";
    std::cout << "Enter your name: \n";
    std::cin >> inputName;

    const char* categories_arr[] = {"Test the quality of parts before shipment",
                                           "Study the structure of the human body",
                                           "Conduct a musical choir",
                                           "Give career guidance to people",
                                           "Sell restaurant franchises to individuals",
                                           "Generate the monthly payroll checks for an office",
                                           "Lay brick or tile",
                                           "Study animal behavior",
                                           "Direct a play",
                                           "Do volunteer work at a non-profit organization",
                                           "Sell merchandise at a department store",
                                           "Inventory supplies using a hand-held computer",
                                           "Work on an offshore oil-drilling rig",
                                           "Do research on plants or animals",
                                           "Design artwork for magazines",
                                           "Help people who have problems with drugs or alcohol",
                                           "Manage the operations of a hotel",
                                           "Use a computer program to generate customer bills",
                                           "Assemble electronic parts",
                                           "Develop a new medical treatment or procedure",
                                           "Write a song",
                                           "Teach an individual an exercise routine",
                                           "Operate a beauty salon or barber shop",
                                           "Maintain employee records",
                                           "Operate a grinding machine in a factory",
                                           "Conduct biological research",
                                           "Write books or plays",
                                           "Help people with family-related problems",
                                           "Manage a department within a large company",
                                           "Compute and record statistical and other numerical data",
                                           "Fix a broken faucet",
                                           "Study whales and other types of marine life",
                                           "Play a musical instrument",
                                           "Supervise the activities of children at a camp",
                                           "Manage a clothing store",
                                           "Operate a calculator",
                                           "Assemble products in a factory",
                                           "Work in a biology lab",
                                           "Perform stunts for a movie or television show",
                                           "Teach children how to read",
                                           "Sell houses",
                                           "Handle customers bank transactions",
                                           "Install flooring in houses",
                                           "Make a map of the bottom of an ocean",
                                           "Design sets for plays",
                                           "Help elderly people with their daily activities",
                                           "Run a toy store",
                                           "Keep shipping and receiving records"};
    std::vector<std::string> categories(categories_arr, categories_arr + CATEGORIES_COUNT);
    std::vector<int> userInputs;

    const char* inputMeanings_arr[] = {"Angry",
                                       "Upset",
                                       "Indifferent",
                                       "Enjoyable",
                                       "Exciting"};
    std::vector<std::string> inputMeanings(inputMeanings_arr, inputMeanings_arr + INPUTS_COUNT);
    for (int i = 0; i < static_cast<int>(categories.size()); i++)
    {
      int responseNum = -1;
      std::cout << "\nHow do you feel about " << categories[i] << "?\n";
      while (!(responseNum >= 0 && responseNum <= static_cast<int>(inputMeanings.size())))
      {

        std::cout << "(" << 0 << ") - "
                  << "skip" << std::endl;
        for (int i = 0; i < static_cast<int>(inputMeanings.size()); i++)
        {
          std::cout << "(" << i + 1 << ") - " << inputMeanings[i] << std::endl;
        }

        std::cin >> responseNum;
        if (std::cin.fail())
        {
          std::cin.clear();
          std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
          responseNum = -1;
        }
        if (!(responseNum >= 0 && responseNum <= static_cast<int>(inputMeanings.size())))
        {
          std::cout << "Invalid input\n";
        }
      }
      userInputs.push_back(responseNum);
    }
    std::ofstream outfile;

    outfile.open(meanings_file.c_str(), std::ios_base::app);
    outfile << "\n"
            << inputName;
    outfile.close();
    std::ofstream outfile2;

    outfile2.open(data_file.c_str(), std::ios_base::app);
    std::string outMsg = "\n";
    for (int i = 0; i < static_cast<int>(userInputs.size()); i++)
    {
      // translate int to string
      std::ostringstream ss;
      ss << userInputs[i];
      outMsg.append(ss.str() + " ");
    }
    outMsg = outMsg.substr(0, outMsg.size() - 1);
    outfile2 << outMsg;
    outfile2.close();

    ExpMax em(4, data_file, meanings_file);

    for (int i = 0; i < static_cast<int>(categories.size()); i++)
    {
      std::string selectedCategory = categories[i];
      std::pair<bool, std::string> result = em.mostProbVal(inputName, selectedCategory);
      if (result.first)
      {
        std::cout << inputName << " responded that " << selectedCategory
                  << " goes well with " << result.second << " moods.\n\n";
      }
      else
      {
        std::cout << inputName << " is most likely to feel that "
                  << selectedCategory << " goes well with " << result.second
                  << " moods.\n\n";
      }
    }
  }

  return 0;
}