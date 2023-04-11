#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main(int argc, char **argv) {
  if( argc < 2 ){
    cout << "Not enough command line argument"; 
    exit(1);
  }
    
  ifstream stopword_file ("../stop_words.txt");
  vector<string> stopword;
  // store stop words
  if( stopword_file.is_open() ){
    string line;
    getline(stopword_file, line);

    int pos;
    while( (pos = line.find(",")) != string::npos ){
      stopword.push_back(line.substr(0, pos)); // [0:pos-1]
      line = line.substr(pos+1);
    }
    // last word: no \n
    stopword.push_back(line);
    
    stopword_file.close();
  }
  else{
    cout << "Unable to open stop word file"; 
    exit(1);
  }

  // count word freq
  ifstream rawtext_file (argv[1]);
  vector<pair<string, int>> word_freqs;
  
  if( rawtext_file.is_open() ){
    string line;
    while( getline(rawtext_file,line) ){
      // strip
      if( line.back() == '\n' )
        line.pop_back();

      // split words
      int start_index = -1;
      for( int i = 0 ; i <= line.size() ; i++ ){
        if( i < line.size() && isalnum(line[i]) ){
          line[i] = tolower(line[i]);
          if( start_index == -1 )
            start_index = i;
        }
        else{ 
          // i == line.size(), process last word
          if( start_index != -1 ){
            string word = line.substr(start_index, i-start_index);
            
            auto iter = find(stopword.begin(), stopword.end(), word);
            if( word.size() >= 2 && iter == stopword.end() ){
              bool found = false;
              for( int j = 0 ; j < word_freqs.size() && !found ; j++ ){
                if( word_freqs[j].first == word ){
                  word_freqs[j].second++;
                  found = true;

                  // bubble up
                  for( int k = j-1 ; k >= 0 && word_freqs[k].second < word_freqs[k+1].second ; k-- )
                    swap(word_freqs[k], word_freqs[k+1]);
                  
                }
              }
              
              if( !found )
                word_freqs.push_back({word, 1});
            }

            start_index = -1;
          }
        }
      }
    }
    rawtext_file.close();
  }
  else{
    cout << "Unable to open text file"; 
    exit(1);
  }

  for( int i = 0 ; i < 25 ; i++ ){
    cout << word_freqs[i].first << "  -  " << word_freqs[i].second;
    if( i != 25-1 )
      cout << "\n";
  }
  

  return 0;
}