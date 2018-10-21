/**
 * @file pmt.cpp
 * @author Junior Lima and Julia Feitosa (junior.lima.ivd.2@gmail.com and ...)
 * @brief Frontend of the pmt software
 * @version 0.1
 * @date 2018-10-18
 * 
 * @copyright Copyright (c) 2018
 * 
 */
#include <iostream>
#include <getopt.h>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include "file_reader.hpp"
#include "boyer_moore.hpp"
#include "sellers.hpp"
#include "wu_manber.hpp"


using namespace std;

/**
 * @brief Enum of algorithms supported in the software
 * 
 */
enum Algorithm
{
      NONE,
      BOYER_MOORE,
      AHO_CORASICK,
      SELLERS,
      WU_MAMBER
};

/**
 * @brief Stores all constraints about the string match to be performed
 * 
 */
typedef struct RunInfo {
      vector<string> patterns;
      vector<string> textFiles;
      int distance;
      bool isExact;
      bool isCountMode;
      Algorithm chosenAlgorithm;

} RunInfo;

/**
 * @brief Open the file and returns a vector where each line is a considered a pattern
 *        If the line is empty, the lien is not considered.
 * @param filename The path of the pattern file
 * @return vector<string> The vector of patterns
 */
vector<string> parserPatternFile(string filename){
      vector<string> p;
      FileReader f(filename);

      string fullline, line;

      int ret = f.getLine(line);
      if (ret == -1) return p;

      do {
            fullline += line;
            if (ret == 0){
                  if (!fullline.empty()) p.push_back(fullline);
                  fullline = "";
            }
            ret = f.getLine(line);
      } while(ret != -1);
}

/**
 * @brief Choose the best algorithm to process the matching acordingly to 
 *        the type of search, number of patterns and size of pattern
 * 
 * @param info Constraits about the string match 
 * @return Algorithm The selected algorithm
 */
Algorithm chooseAlgorithm(RunInfo info) {
      if (info.isExact) {
           if ( info.patterns.size() > 1 ) return AHO_CORASICK;
           else return BOYER_MOORE;
      } else {
            size_t maxSize = info.patterns[0].size();
            for(int i=1; i<info.patterns.size(); i++) maxSize = max(maxSize, info.patterns[i].size());
            if (maxSize > 64)
                  return SELLERS;
            else
                  return WU_MAMBER;
      }
}

/**
 * @brief Execute the string match considering all the information stored in info
 * 
 * @param info Constraits about the string match 
 */
void executeAlgorithm(RunInfo info){

      Searcher * s;
      std::vector<char> alph;

      for (int i = 0; i < 256; i++) {
            alph.push_back(char(i));
      }

      switch (info.chosenAlgorithm)
      {
            case BOYER_MOORE:{
                  s = new BoyerMoore(info.patterns[0], alph);
                  break;
            }
            case AHO_CORASICK:{
                  // TODO: implement aho corasick usage;
                  break;
            }
            case SELLERS:{
                  s = new Sellers(info.patterns[0], info.distance);
                  break;
            }
            case WU_MAMBER:{
                  s = new WuManber(info.patterns[0], alph, info.distance);
                  break;
            }
      }
      int i=1;
      
      do {
            for(string textname : info.textFiles) {
                  FileReader fr(textname);

                  std::stringstream fullline;
                  
                  string line;

                  int ret = fr.getLine(line);
                  if(ret == -1) continue;

                  int lineCount = 0;
                  bool countedLine = false, found = false;

                  do {
                        if(!info.isCountMode) fullline << line;

                        found = s->search(line, ret == 0);

                        if (found && !countedLine) {
                              lineCount++;
                              countedLine = true;
                        }

                        if(ret == 0 && countedLine && !info.isCountMode)
                              printf("%s\n", fullline.str().c_str());
                        
                        if(ret == 0){
                              fullline.str(std::string());
                              countedLine = false;
                        }

                        ret = fr.getLine(line);

                  } while(ret != -1);

                  if (info.isCountMode) {
                        printf("Total occurrences: %d match(es) found.\n", s->count());
                  } else {
                        printf("Number of lines: %d match(es) found.\n", lineCount);
                  }
            }

            if(i < info.patterns.size()) s->resetPattern(info.patterns[i]);
            i++;
      } while( i <= info.patterns.size());


}

int main(int argc, char *argv[])
{
      vector<string> pmt_algorithms = {"boyer-moore", "aho-corasick", "sellers", "wu-manber"};
      int opt, opt_index; /* opt = value returned by the getopt_long function | opt_index = index of the chosen option, stored by the getopt_long function */
      string algorithm;
      RunInfo info;
      info.chosenAlgorithm = NONE;
      info.distance = -1;
      info.isCountMode = false;
      info.isExact = true;
      info.patterns.clear();
      info.textFiles.clear();

      /* {long option name, argument, flag value, short option name} */
      static struct option long_options[]{
            {"algorithm", required_argument, 0, 'a'},
            {"count",     no_argument,       0, 'c'},
            {"edit",      required_argument, 0, 'e'},
            {"help",      no_argument,       0, 'h'},
            {"pattern",   required_argument, 0, 'p'}, 
            {0, 0, 0, 0}
      };

      while((opt = getopt_long(argc, argv, "a:e:cp:h", long_options, &opt_index)) != -1){
            switch(opt){

                  case 'a':
                  {
                        algorithm = optarg;
                        
                        for(int i=0; i < pmt_algorithms.size(); i++) {
                              if (pmt_algorithms[i] == algorithm) {
                                    info.chosenAlgorithm = Algorithm(i+1);
                              }      
                        }

                        if (info.chosenAlgorithm == NONE) {
                              printf("Invalid algorithm name.\n");
                              exit(-1);
                        }
                  
                  break;
                  }

                  case 'c':                  
                        info.isCountMode = true;
                  break;

                  
                  case 'e':
                        int distance;                  
                        sscanf(optarg, "%d", &distance);
                        info.isExact = false;
                        info.distance = distance;                  
                  break;

                  case 'h':
                  
                        printf("Usage: $ pmt [options] pattern textfile [textfile...]\n");
                        printf("-a, --algorithm [algorithm_name]\n\t[boyer-moore]\n\t[aho-corasick]\n\t[sellers]\n\t[wu-manber]\n"
                              "-c, --count\n"
                              "-e, --edit [e_max]\n"
                              "-h, --help\n"
                              "-p, --pattern [pattern_file]\n");
                        exit(0);
                        break;
                  break;

                  case 'p':                  
                        info.patterns = parserPatternFile(optarg);                  
                  break;

                  case '?':
                        printf("Invalid argument. Please try again.\n");
                        exit(-1);
                  break;
                  default:
                        abort();
            }

      }

      int neededArgs = (info.patterns.empty()) ? 2 : 1;

      if (argc - optind < neededArgs) {
            printf("Not enought arguments.\n");
            exit(1);
      }

      if(info.patterns.empty()) info.patterns.push_back(argv[optind++]);

      for(; optind < argc; optind++) info.textFiles.push_back(argv[optind]);

      if (info.chosenAlgorithm == NONE) info.chosenAlgorithm = chooseAlgorithm(info);

      if(info.isExact && (info.chosenAlgorithm == SELLERS || info.chosenAlgorithm == WU_MAMBER)){
            printf("Error: Algorithm %s is not suitable to exact matching.\n", pmt_algorithms[info.chosenAlgorithm - 1].c_str());
            exit(-1);
      }

      if (!info.isExact && (info.chosenAlgorithm == BOYER_MOORE || info.chosenAlgorithm == AHO_CORASICK)) {
            printf("Error: Algorithm %s is not suitable to approximate matching.\n", pmt_algorithms[info.chosenAlgorithm - 1].c_str());
            exit(-1);
      }

      executeAlgorithm(info);

      return 0;
}