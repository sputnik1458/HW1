/* CIS4930 - Data Science in Bioinformatics Spring 2020
  University of Florida
  HW1
  Jacob Frank & Pedro Sicilia
*/

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <random>
#include <vector>


using namespace std;


vector<char> splitsequence(int min, int max, vector<char> seq) {

  int length = seq.size();
  vector<char> newfasta;
  int range;
  std::vector<int>::iterator it;
  int loc = 0;
  bool ignore = false;


  for(int g = 0; g < seq.size(); g++) {

    if(seq[g] == '\n') {
      for(int i = loc; i < g; i++) {
        range = rand()%((max - min) + 1) + min;

				for(int rangepos = 0; rangepos < range; rangepos++) {

          if((g - i) <= range+1) {
            i = g;
  					rangepos = max + 1;
          	ignore = true;
          }
					else {
            newfasta.push_back(seq[i+rangepos]);
					}
				}

				if(!ignore) {
          i = i+range-1;
				}

				ignore = false;
				newfasta.push_back('\n');
      }
      newfasta.pop_back();
			loc = g+1;

    }
  }
  return newfasta;

}


int main(int argc, char* argv[]) {

    int min;
    int max;
    vector<char> seq;
    vector<char> newfasta;
    char character;
    std::srand((unsigned)std::time(0));
    std::ofstream outfile;

    min = stoi(argv[2]);
    max = stoi(argv[3]);


    string filename = argv[1];

    ifstream file;
    file.open(filename, ios::in);

    std::string str;

    while (std::getline(file, str)) {
      if (str[0] != '>') {
        for (int i = 0; i < str.size(); i++) {
          seq.push_back(str[i]);
        }
        seq.push_back('\n');
      }
    }

    int seqlength = 0;

/*
    for(int i = 0; i < seq.size; i++) {
        if(seq[i] == '\n') {
            newfasta = splitsequence(min, max, seq);
        }
    }
*/

    newfasta = splitsequence(min, max, seq);

    outfile.open(argv[4]);

    int n = 1;
    outfile << ">FRAGMENT #" << n << '\n';
    n++;
    for(int i = 0; i < newfasta.size(); i++) {
        outfile << newfasta[i];
        if (newfasta[i] == '\n') {
          outfile << ">FRAGMENT #" << n << '\n';
          n++;
        }
      //  if(newfasta[i+1] == '\n')
      //      i++;
    }


    // cout << "Filename: " << filename << endl;

    // cout << "Char count: " << newfasta.size() << endl;






    return 0;
}
