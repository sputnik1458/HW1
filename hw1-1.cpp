/* CIS4930 - Data Science in Bioinformatics Spring 2020
  University of Florida
  HW1
  Jacob Frank & Pedro Sicilia
*/

#include <iostream>
#include <random>
#include <ctime>
#include <cstdlib>
#include <cstring>
#include <fstream>

// returns a deletion or random nucleotide based on given probabilities
char genNucleotide(int a, int c, int g, int s) {

  int r = std::rand() % s + 1;

  if (r < a) {
      return 'A';
  } else if (r < a+c) {
      return 'C';
  } else if (r < a+c+g) {
      return 'G';
  } else {
      return 'T';
  }
}

int main(int argc, char* argv[]) {

  int n = std::atoi(argv[1]); // sequence length
  int a = std::atoi(argv[2]);
  int c = std::atoi(argv[3]);
  int g = std::atoi(argv[4]);
  int t = std::atoi(argv[5]);
  int s = a + c + g + t;

  int k = std::atoi(argv[6]); // # sequences
  float p = std::atof(argv[7]); // mutation prob

  std::ofstream outfile;
  outfile.open(argv[8]);

  std::srand((unsigned)std::time(0));

  char nt;
  char f[n];

  // generates first sequence
  outfile << ">SEQUENCE #1\n";
  for (int i = 0; i < n; i++) {
    nt = genNucleotide(a, c, g, s);
    f[i] = nt;
    outfile << nt;
  }
  outfile << '\n';

  // generates k-1 sequences with mutation probability
  for (int j = 0; j < k-1; j++) {
    outfile << ">SEQUENCE #" << j+2 << '\n';
    for (int i = 0; i < n; i++) {
      bool mut = std::rand() % 1000 + 1 < p*1000;
      if (mut) {
        // 50% chance of deletion
        int d = std::rand() % 3;
        if (d) {
          outfile << genNucleotide(a, c, g, s);
        } else {
          outfile << '-';
        }
      } else {
        outfile << f[i];
      }
    }
    outfile << '\n';
  }
  outfile.close();

  return 0;

}
