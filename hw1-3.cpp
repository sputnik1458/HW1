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
#include <vector>
#include <algorithm>
#include <initializer_list>

// returns dovetail alignment score
int align(std::string seq1, std::string seq2, int s, int r, int d) {

  int score = 0;
  int n = seq2.size()+1;
  int m = seq1.size()+1;
  int table[n][m][2];

  // initialize rows
  for (int j = 0; j < m; j++) {
    table[0][j][1] = 0;
  }

  // initialize cols
  for (int i = 0; i < n; i++) {
    table[i][0][1] = 0;
  }

  int score_d = 0;
  int score_v = 0;
  int score_h = 0;

  for (int i = 1; i <= n; i++) {
    for (int j = 1; j < m; j++) {
      score_d = 0; // score moving diagonally
      score_v = 0; // moving vertically
      score_h = 0; // moving horizontally

      // calculate diagonal score
      if (seq2[i-1] == seq1[j-1]) {
        score_d = table[i-1][j-1][1] + s;
      } else {
        score_d = table[i-1][j-1][1] + r;
      }

      // calculate vertical score
      score_v = table[i-1][j][1] + d;

      // calculate horizontal score
      score_h = table[i][j-1][1] + d;

      // assign max score to table
      int max_score = std::max({score_d, score_v, score_h});
      table[i][j][1] = max_score;

      // assign source to table
      if (max_score == score_d) {
        table[i][j][2] = 1; // diagonal source
      } else if (max_score == score_v) {
          table[i][j][2] = 2; // vertical source
      } else {
          table[i][j][2] = 0; // horizontal source
      }
    }
  }

  // for (int i = 0; i < n; i++) {
  //   for (int j = 0; j < m; j++) {
  //     std::cout << table[i][j] << " ";
  //   }
  //   std::cout << '\n';
  // }
  // std::cout << '\n';

  int max_i = 0;
  int loc_i;
  for (int i = 1; i < n; i++) {
    if (table[i][m-1][1] > max_i) {
      max_i = table[i][m-1][1];
      loc_i = i;
    }
  }

  int max_j = 0;
  int loc_j;
  for (int j = 1; j < m; j++) {
    if (table[n-1][j][1] > max_j) {
      max_j = table[n-1][j][1];
      loc_j = j;
    }
  }

  score = std::max(max_i, max_j);

  int loc[2];
  if (score == max_i) {
    loc[0] = loc_i;
    loc[1] = m-1;
  } else {
    loc[0] = n-1;
    loc[1] = loc_j;
  }

  // TODO: recursively backtrace
  std::cout << table[loc[0]][loc[1]][2];

  return score;
}

int main(int argc, char* argv[]) {

  std::string input_file = argv[1];
  int s = std::stoi(argv[2]);
  int r = std::stoi(argv[3]);
  int d = std::stoi(argv[4]);
  std::string output_file = argv[5];

  std::ifstream infile(input_file);
  std::string str;

  // read file into vector
  std::vector<std::string> frags;
  while (std::getline(infile, str)) {
    frags.push_back(str);
  }

  align(frags[0], frags[1], s, r, d);

  // compute alignment scores
  // std::vector<int> align_scores;
  // for (int i = 0; i < frags.size()-1; i++) {
  //   align_scores.push_back(align(frags[i], frags[i+1], s, r, d));
  // }

  // find best alignment
  // std::vector<int>::iterator i_max = std::max_element(align_scores.begin(), align_scores.end());
  // int index = std::distance(align_scores.begin(), i_max);
  // std::cout << frags[index] << '\n' << frags[index+1];
  //
  // std::vector<char> merge;

  return 0;
}
