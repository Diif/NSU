#include <cstdlib>
#include <iostream>
#include <list>
#include <map>

#include "solution.h"

using namespace std;

#define ARG_COUNT_ERROR 10
#define FILE_ERROR 11
#define EMPTY_FILE_ERROR 12
void ValidateArgCount(int argc);
void ValidateFile(ifstream* file);
void CheckEOF(ifstream* file);
void ProcessMapWithWord(map<string, int>* words_freq_map, string word);
void CheckForEmptyFile(int total_words);
list<pair<int, string>>* GetSortedListFromMap(map<string, int>* words_freq);
void FillMapFromFile(WordReader* reader, map<string, int>* word_freq);
void WriteCSVToFile(WordReader* reader, list<pair<int, string>>* item_list,
                    string* output_file_name);

int main(int argc, char** argv) {
  ValidateArgCount(argc);

  string file_name(argv[1]);
  string input_file_name("input.txt");
  string output_file_name("out.csv");
  WordReader reader;
  ValidateFile(reader.GetFilePointer());

  map<string, int> words_freq;
  reader.OpenFile(input_file_name);

  FillMapFromFile(&reader, &words_freq);

  CheckForEmptyFile(reader.GetTotalWordsCount());

  list<pair<int, string>>* sorted_item_list = GetSortedListFromMap(&words_freq);
  sorted_item_list->reverse();

  int size = sorted_item_list->size();
  WriteCSVToFile(&reader, sorted_item_list, &output_file_name);

  delete sorted_item_list;
}

void ValidateArgCount(int argc) {
  if (argc != 3) {
    cerr << "Incorrect arg count!" << endl;
    exit(ARG_COUNT_ERROR);
  }
}

void ValidateFile(ifstream* file) {
  if (!(*file)) {
    cerr << "Can't open the file!" << endl;
    exit(FILE_ERROR);
  }
}

void CheckForEmptyFile(int total_words) {
  if (total_words == 0) {
    exit(EMPTY_FILE_ERROR);
  }
}

void ProcessMapWithWord(map<string, int>* words_freq_map, string word) {
  if (words_freq_map->count(word) <= 0) {
    words_freq_map->insert(make_pair(word, 1));
  } else {
    (*words_freq_map)[word]++;
  }
}

list<pair<int, string>>* GetSortedListFromMap(map<string, int>* words_freq) {
  map<string, int>::iterator map_it;
  list<pair<int, string>>* sorted_item_list = NULL;

  map_it = words_freq->begin();
  int num_of_items = words_freq->size();

  if (num_of_items > 0) {
    sorted_item_list = new list<pair<int, string>>;
  }

  for (int i = 0; i < num_of_items; i++) {
    sorted_item_list->push_back(make_pair((*map_it).second, (*map_it).first));
    map_it++;
  }

  sorted_item_list->sort();

  return sorted_item_list;
}

void FillMapFromFile(WordReader* reader, map<string, int>* word_freq) {
  reader->ReadWord();
  while (!reader->WasTextEndFound()) {
    ProcessMapWithWord(word_freq, reader->GetCurrentWord());
    reader->ReadWord();
    reader->IncreaseTotalWordsCount();
  }
  if (reader->GetTotalWordsCount() != 0) {
    ProcessMapWithWord(word_freq, reader->GetCurrentWord());
    reader->IncreaseTotalWordsCount();
  }
}

void WriteCSVToFile(WordReader* reader, list<pair<int, string>>* item_list,
                    string* output_file_name) {
  ofstream output_file;
  output_file.open(*output_file_name, ofstream::out);
  int size = item_list->size();
  int total_words = reader->GetTotalWordsCount();
  list<pair<int, string>>::iterator it = item_list->begin();
  for (int i = 0; i < size; i++) {
    output_file << (*it).second << "," << (*it).first << ","
                << static_cast<double>((*it).first) / total_words << endl;
    it++;
  }
  output_file.close();
}
