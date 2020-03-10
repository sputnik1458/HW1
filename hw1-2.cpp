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
		// // cout << "LOCATION: " << loc << "   G =   "  << g << endl;
           for(int i = loc; i < g; i++) {    
                range = rand()%((max - min) + 1) + min;
				// cout << "Range:  " << range << endl;
				// cout << "Seq: ";

				for(int rangepos = 0; rangepos < range; rangepos++) {
               	
                	if((g - i) <= range+1) {
                    	i = g;
						rangepos = max + 1;
						//// cout << "IN HERE" << "   G :   " << g << "    I:  " << i << endl;
						// cout << "FOUND" << endl;
						ignore = true;
              		}
					else {
						newfasta.push_back(seq[i+rangepos]);
						// cout << seq[i+rangepos];
					}
				}
				if(!ignore) {
					i = i+range-1;
					// cout << "INN" << endl;
			//	newfasta.push_back('\n');

				}

				ignore = false;	
				// cout << endl << endl;
				newfasta.push_back('\n');
            }

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

    while(!file.eof()) {
        file.get(character);
        seq.push_back(character);
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

    for(int i = 0; i < newfasta.size(); i++) {
        outfile << newfasta[i];
      //  if(newfasta[i+1] == '\n')
      //      i++;
    }


    // cout << "Filename: " << filename << endl;

    // cout << "Char count: " << newfasta.size() << endl;






    return 0;
}
