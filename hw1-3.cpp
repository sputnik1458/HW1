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

struct table_element {
  int score;
  int source;
};

class Alignment {
  public:
    std::vector<std::vector<table_element>> table;
    int score;
    std::pair<int, int> score_loc;

    int calc_score();
    void print_table();
};

int Alignment::calc_score() {

  int n = this->table.size();
  int m = this->table[0].size();
  int score = 0;

  int max_i = 0;
  int loc_i = 0;
  for (int i = 1; i < n; i++) {
    if (this->table[i][m-1].score > max_i) {
      max_i = this->table[i][m-1].score;
      loc_i = i;
    }
  }

  int max_j = 0;
  int loc_j = 0;
  for (int j = 1; j < m; j++) {
    if (this->table[n-1][j].score > max_j) {
      max_j = this->table[n-1][j].score;
      loc_j = j;
    }
  }

  score = std::max(max_i, max_j);
  std::pair<int, int> loc;
  if (score == max_i) {
    loc.first = loc_i;
    loc.second = m-1;
  } else {
    loc.first = n-1;
    loc.second = loc_j;
  }

  this->score_loc = loc;
  return score;
}

void Alignment::print_table() {
  int n = this->table.size();
  int m = this->table[0].size();

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      std::cout << this->table[i][j].score << "  ";
    }
    std::cout << '\n';
  }
  std::cout << '\n';
}

std::string merge(std::string seq1, std::string seq2, Alignment a) {
  int score;
  std::pair<int, int> loc = a.score_loc;
  table_element e;
  std::string align_seg;

  std::string main_seq;
  std::string b_seq;
  int align_size = 0;

  if (a.table.size()-1 == loc.first){
    main_seq = seq2;
    b_seq = seq1;
  } else {
    main_seq = seq1;
    b_seq = seq2;
  }

  // calculate length of alignment overlap
  e = a.table[loc.first][loc.second];
  do {
    //align_seg.push_back(seq2[loc.first-1]);
    align_size++;
    switch (e.source) {
      case 0:
        loc.first--;
        break;
      case 1:
        loc.first--;
        loc.second--;
        break;
      case 2:
        loc.second--;
        break;
    }
    e = a.table[loc.first][loc.second];
    score = e.score;
  } while (score > 0);

  // merge the aligned segments
  std::string merged_seq;
  for (int i = 0; i < main_seq.size(); i++) {
    merged_seq.push_back(main_seq[i]);
  }
  for (int j = align_size; j < b_seq.size(); j++) {
   merged_seq.push_back(b_seq[j]);
  }

  return merged_seq;
}

// returns dovetail alignment table
std::vector<std::vector<table_element>> align(std::string seq1, std::string seq2, int s, int r, int d) {

  int score = 0;
  int n = seq2.size()+1;
  int m = seq1.size()+1;
  //int table[n][m][2];
  std::vector<std::vector<table_element>> table(n, std::vector<table_element>(m));


  // initialize rows
  for (int j = 0; j < m; j++) {
    table[0][j].score = 0;
  }

  // initialize cols
  for (int i = 0; i < n; i++) {
    table[i][0].score = 0;
  }

  int score_d = 0;
  int score_v = 0;
  int score_h = 0;

  for (int i = 1; i < n; i++) {
    for (int j = 1; j < m; j++) {
      score_d = 0; // score moving diagonally
      score_v = 0; // moving vertically
      score_h = 0; // moving horizontally

      // calculate diagonal score
      if (seq2[i-1] == seq1[j-1]) {
        score_d = table[i-1][j-1].score + s;
      } else {
        score_d = table[i-1][j-1].score + r;
      }

      // calculate vertical score
      score_v = table[i-1][j].score + d;

      // calculate horizontal score
      score_h = table[i][j-1].score + d;

      // assign max score to table
      int max_score = std::max({score_d, score_v, score_h});
      table[i][j].score = max_score;

      // assign source to table
      if (max_score == score_d) {
        table[i][j].source = 1; // diagonal source
      } else if (max_score == score_v) {
          table[i][j].source = 2; // vertical source
      } else {
          table[i][j].source = 0; // horizontal source
      }
    }
  }

  // std::vector<std::vector<table_element>> table1(n, std::vector<table_element>(m));
  //
  // for (int i = 0; i < n; i++) {
  //   for (int j = 0; j < m; j++) {
  //     table1[i][j].score = table[i][j][1];
  //     table1[i][j].source = table[i][j][2];
  //   }
  // }

  return table;
}

int main(int argc, char* argv[]) {

  std::string input_file = argv[1];
  int s = std::stoi(argv[2]);
  int r = std::stoi(argv[3]);
  int d = std::stoi(argv[4]);
  std::string output_file = argv[5];

  std::ifstream infile(input_file);
  std::string str;

  std::ofstream outfile(output_file);

  // read file into vector
  std::vector<std::string> frags;
  while (std::getline(infile, str)) {
    frags.push_back(str);
  }

  int i_max, best_score;

  while (frags.size() > 1) {
    i_max = 0;
    best_score = 0;

    // compute alignment scores
    std::vector<Alignment> align_tables;
    Alignment a;
    for (int i = 0; i < frags.size()-1; i++) {
      a.table = align(frags[i], frags[i+1], s, r, d);
      a.score = a.calc_score();
      align_tables.push_back(a);
    }

    // find best alignment
    for (int k = 0; k < align_tables.size(); k++) {
      if (align_tables[k].score > best_score) {
        i_max = k;
        best_score = align_tables[k].score;
      }
    }


    if (best_score < 0) {
      break;
    }

    // merge and replace
    std::string merged_seq = merge(frags[i_max], frags[i_max+1], align_tables[i_max]);
    frags[i_max] = merged_seq;
    //std::cout << merged_seq << '\n';
    frags.erase(frags.begin() + i_max + 1);

  }

  std::string largest_align = "";
  for (int w = 0; w < frags.size(); w++) {
    if (frags[w].size() > largest_align.size()) {
      largest_align = frags[w];
    }
  }

  outfile << largest_align << '\n';

  return 0;
}
