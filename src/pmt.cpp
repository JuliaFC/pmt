#include <iostream>
#include <getopt.h>
#include <string>
#include <vector>


using namespace std;

bool IsInArray(string needle, vector<string> haystack){
      for(vector<string>::iterator it = haystack.begin(); it != haystack.end(); it++){
            if(needle.compare(*it) == 0) 
                  return true;
      }
      return false;
}

enum Algorithm
{
      NONE,
      BOYER_MOORE,
      AHO_CORASICK,
      SELLERS,
      WU_MAMBER
};

typedef struct RunInfo {
      vector<string> patterns;
      vector<string> textFiles;
      int distance;
      bool isExact;
      bool isCountMode;
      Algorithm chosenAlgorithm;

} RunInfo;

vector<string> parserPatternFile(string filename){

}

Algorithm chooseAlgorithm(RunInfo info) {
      return AHO_CORASICK;
}

void executeAlgorithm(RunInfo info){

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
                        //printf("option -a with arg %s\n", optarg);
                        algorithm = optarg;
                        
                        for(int i=0; i < pmt_algorithms.size(); i++){
                              if (pmt_algorithms[i] == algorithm) {
                                    info.chosenAlgorithm = Algorithm(i+1);
                              }      
                        }

                        if (info.chosenAlgorithm == NONE) {
                              printf("Invalid algorithm name.\n");
                              exit(0);
                        }
                  
                  break;
                  }

                  case 'c':                  
                        //printf("option -c\n");
                        info.isCountMode = true;
                  break;

                  
                  case 'e':
                        int distance;                  
                        //("option -e with arg %s\n", optarg);
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
                        //printf("option -p with arg %s\n", optarg);
                        info.patterns = parserPatternFile(optarg);                  
                  break;

                  case '?':
                        printf("Invalid argument. Please try again.\n");
                        exit(0);
                  break;
                  default:
                        abort();
            }

      }

      int neededArgs = (info.patterns.empty()) ? 2 : 1;

      if (argc - optind < neededArgs) {
            printf("Not enought arguments.\n");
            exit(0);
      }

      if(info.patterns.empty()) info.patterns.push_back(argv[optind++]);

      for(; optind < argc; optind++) info.textFiles.push_back(argv[optind]);

      if (info.chosenAlgorithm == NONE) info.chosenAlgorithm = chooseAlgorithm(info);

      if(info.isExact && (info.chosenAlgorithm == SELLERS || info.chosenAlgorithm == WU_MAMBER)){
            printf("Error: Algorithm %s is not suitable to exact matching.\n", pmt_algorithms[info.chosenAlgorithm - 1].c_str());
            exit(0);
      }

      if (!info.isExact && (info.chosenAlgorithm == BOYER_MOORE || info.chosenAlgorithm == AHO_CORASICK)) {
            printf("Error: Algorithm %s is not suitable to approximate matching.\n", pmt_algorithms[info.chosenAlgorithm - 1].c_str());
            exit(0);
      }

      executeAlgorithm(info);

      return 0;
}