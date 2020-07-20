#pragma once

#include <iostream>
#include <string>
#include<vector>
#include<stack>
#include <set>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <unordered_map>

#include "utils.h"

using namespace std;

struct trieNode {
  bool isWord;
  unordered_map<char,trieNode*> childs;
};

struct trieNode *createNode() {
  trieNode* newNode = new trieNode;
  newNode->isWord = false;

  return newNode;
}

void insert(string word, trieNode* root) {
  trieNode* tmp = root;

  for(int i =0; i < word.length(); i++) {
    int index = word[i];

    if(!tmp->childs[index]) {
      tmp->childs[index] = createNode();
    }

    tmp = tmp->childs[index];
  }
  tmp->isWord = true;
}

bool search(string word, trieNode* root) {
  trieNode* tmp = root;
  for_each(word.begin(),word.end(), [](char & c) {
    c = ::tolower(c);
  });

  for(int i =0; i < word.length(); i++) {
    int index = word[i];

    if(!tmp->childs[index]) {
      return false;
    }

    tmp = tmp->childs[index];
  }
  return(tmp != nullptr && tmp->isWord==true);
}

bool isLastNode(trieNode* node) {
  return !(node->childs.size());
}

vector<string> suggestWords(string prefix, trieNode *root) {
    vector<string> result;
    if (root->isWord == true) {
      result.push_back(prefix);
    }

    if (isLastNode(root)) {
        return result;
    }

    for(auto child: root->childs) {
      prefix.push_back(child.first);
      vector<string> partialRes = suggestWords(prefix, child.second);
      result.insert(result.end(),partialRes.begin(), partialRes.end());
      prefix.pop_back();
    }
    return result;
}

vector<string> nFirst(vector<string> vec, int n) {

  std::partial_sort(vec.begin(), vec.begin() + n,vec.end(), [](const std::string& first, const std::string& second){
        return first.size() < second.size();
    });
  vec.resize(n);
  return vec;
}

vector<string> getNSuggestions(trieNode *root, const string query, int num) {
    trieNode *crawl = root;
    int n = query.length();
    vector<string> result;
      
    for (int i = 0; i < n; i++) {
        int ind = query[i];

        if (!crawl->childs[ind])
            return nFirst(result,num);

        crawl = crawl->childs[ind];
    }

    bool isAWord = (crawl->isWord == true);
    bool isLast = isLastNode(crawl);

    if (isAWord && isLast) {
        return nFirst(result,num);
    }

    if (!isLast) {
        string prefix = query;
        vector<string> partialResult = suggestWords(prefix, crawl);
        result.insert(result.end(), partialResult.begin(),partialResult.end());
        return nFirst(result,num);
    }
    return nFirst(result,num);
}

vector<string> correct(trieNode* root, const string query) {
  vector<string> candidates = edit2(edit1(query));
  vector<string> result;
  for(auto i: candidates) {
    if(search(i,root)) {
      result.push_back(i);
    }
  }
  return result;
}

void loadFile (string fileName, trieNode* root) {
  std::ifstream infile(fileName);
  string word;
  while(getline(infile,word)) {
    insert(word, root);
  }
}