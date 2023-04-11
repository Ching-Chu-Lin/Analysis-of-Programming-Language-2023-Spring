#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<string> lines, words, stop_words;
vector<pair<string, int>> word_freqs;

void read_file(string file_path){
  ifstream f (file_path);
  if( f.is_open() ){
    string line;
    while( getline(f,line) ){
      if( line.back() == '\n' )
        line.pop_back(); // strip
  
      lines.push_back(line);
    }

    f.close();
  }
  else{
    cout << "Unable to open file path: " << file_path; 
    exit(1);
  }

  return;
}

void splitText(string token, vector<string>& dest){
  for( string line : lines ){
    int pos;
    while( (pos = line.find(token)) != string::npos ){
      dest.push_back(line.substr(0, pos)); // [0:pos-1]
      line = line.substr(pos+1);
    }  
    // last word: no \n
    dest.push_back(line);
  }

  return;
}

void filter_chars_and_normalize(){
  for( string& line : lines ){
    for( int i = 0 ; i < line.size() ; i++ ){
      if( isalnum(line[i]) )
        line[i] = tolower(line[i]);
      else
        line[i] = ' ';
    }
  }

  return;
}

void remove_stop_words(){
  for( int i = words.size()-1 ; i >= 0 ; i-- ){
    auto iter = find(stop_words.begin(), stop_words.end(), words[i]);
    if( words[i].size() < 2 || iter != stop_words.end() )
      words.erase(words.begin() + i);
  }
  return;
}

void calculate_frequency(){
  vector<string> keys;
  for( string w : words ){
    auto iter = find(keys.begin(), keys.end(), w);
    if( iter != keys.end() )
      word_freqs[iter-keys.begin()].second++;
    else{
      word_freqs.push_back({w, 1});
      keys.push_back(w);
    }
  }

  return;
}

void sort(){
  sort(word_freqs.begin(), word_freqs.end(), 
    [](const pair<string, int>& a, const pair<string, int>& b){
      return a.second > b.second;}); // freq from large to small
}
    

int main(int argc, char **argv) {
  if( argc < 2 ){
    cout << "Not enough command line argument"; 
    exit(1);
  }
  
  // store stop words
  read_file("../stop_words.txt");
  splitText(",", stop_words);
  lines.clear();

  // count word freq
  read_file(argv[1]);
  filter_chars_and_normalize();
  splitText(" ", words);
  lines.clear();
  remove_stop_words(); // filter out words.size() == 1
  calculate_frequency();
  sort();
  

  for( int i = 0 ; i < 25 ; i++ ){
    cout << word_freqs[i].first << "  -  " << word_freqs[i].second;
    if( i != 25-1 )
      cout << "\n";
  }
  

  return 0;
}