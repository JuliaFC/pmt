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

int main(int argc, char *argv[])
{
      vector<string> pmt_algorithms = {"boyer-moore", "aho-corasick", "sellers", "wu-manber"};
      int opt, opt_index; /* opt = value returned by the getopt_long function | opt_index = index of the chosen option, stored by the getopt_long function */
      string algorithm;

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
                        printf("option -a with arg %s\n", optarg);
                        algorithm = optarg;
                        if(!IsInArray(algorithm, pmt_algorithms)){
                             printf("Invalid algorithm name.\n");
                        }
                  
                  break;
                  }

                  case 'c':                  
                        printf("option -c\n");
                  break;

                  
                  case 'e':                  
                        printf("option -e with arg %s\n", optarg);                  
                  break;

                  case 'h':
                  
                        printf("Usage: $ pmt [options] pattern textfile [textfile...]\n");
                        printf("-a, --algorithm [algorithm_name]\n\t[boyer-moore]\n\t[aho-corasick]\n\t[sellers]\n\t[wu-manber]\n"
                              "-c, --count\n"
                              "-e, --edit [e_max]\n"
                              "-h, --help\n"
                              "-p, --pattern [pattern_file]\n");
                  break;

                  case 'p':                  
                        printf("option -p with arg %s\n", optarg);                  
                  break;

                  case '?':
                        printf("Invalid argument. Please try again.\n");
                  break;
            }

      }

      return 0;
}