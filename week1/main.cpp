#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

int main(int argc, char **argv) {
  if( argc < 2 ){
    cout << "Not enough command line argument"; 
    exit(1);
  }
    
  ifstream stopword_file ("../stop_words.txt");
  unordered_set<string> stopword;
  
  // store stop words
  if( stopword_file.is_open() ){
    string line;
    getline(stopword_file, line);

    int pos;
    while( (pos = line.find(",")) != string::npos ){
      stopword.insert(line.substr(0, pos)); // [0:pos-1]
      line = line.substr(pos+1);
    }
    // last word: no \n
    stopword.insert(line);
    
    stopword_file.close();
  }
  else{
    cout << "Unable to open stop word file"; 
    exit(1);
  }

  // count word freq
  ifstream rawtext_file (argv[1]);
  vector<pair<string, int>> word_freq;
  unordered_map<string, int> word_idx;
  
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
        else{ // i == line.size(), process last word
          if( start_index != -1 ){
            string word = line.substr(start_index, i-start_index);
            if( word.size() >= 2 && stopword.find(word) == stopword.end() ){
              if( word_idx.find(word) == word_idx.end() ){
                // appear first time
                word_idx[word] = word_freq.size();
                word_freq.push_back({word, 1});
              }
              else{
                // appear before
                word_freq[word_idx[word]].second += 1;
              }
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

  // sort vector by freq, and get top 25
  sort(word_freq.begin(), word_freq.end(), 
    [](const pair<string, int>& a, const pair<string, int>& b){
      if( a.second == b.second )
        return a.first < b.first;
      return a.second > b.second;}); // freq from large to small


  for( int i = 0 ; i < 25 ; i++ ){
    cout << word_freq[i].first << "  -  " << word_freq[i].second;
    if( i != 25-1 )
      cout << "\n";
  }
  

  return 0;
}