#include <iostream>
#include <string>
#include<vector>
#include<stack>
#include <set>
#include <fstream>
#include <sstream>
#include <algorithm>

#define alpha_size 26
#define CHAR_TO_INDEX(c) ((int)c - (int)'a')
using namespace std;

struct trieNode {
  bool isWord;
  trieNode* childs[alpha_size];
};

struct trieNode *createNode() {
  trieNode* newNode = new trieNode;
  newNode->isWord = false;

  for(int i = 0; i<alpha_size; i++){
    newNode->childs[i] = nullptr;
  }
  return newNode;
}

void insert(string word, trieNode* root) {
  trieNode* tmp = root;

  for(int i =0; i < word.length(); i++) {
    int index = word[i] - 'a';

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
    int index = word[i] - 'a';

    if(!tmp->childs[index]) {
      return false;
    }

    tmp = tmp->childs[index];
  }
  return(tmp != nullptr && tmp->isWord==true);
}

bool isLastNode(trieNode* node) {
  for(int i =0; i< alpha_size; i++) {
    if(node->childs[i]) {
      return false;
    }
  }
  return true;
}

vector<string> suggestWords(string prefix, trieNode *root) {
    vector<string> result;
    if (root->isWord == true) {
      result.push_back(prefix);
    }

    if (isLastNode(root)) {
        return result;
    }

    for (int t = 0; t < alpha_size; t++) {
        if (root->childs[t] != nullptr) {
            prefix.push_back(97 + t);
            vector<string> partialRes = suggestWords(prefix, root->childs[t]);
            result.insert(result.end(),partialRes.begin(), partialRes.end());
            prefix.pop_back();
        }
    }
    return result;
}

vector<string> autoSuggest(trieNode *root, const string query) {
    trieNode *crawl = root;
    int level;
    int n = query.length();
    vector<string> result;
      
    for (level = 0; level < n; level++) {
        int ind = CHAR_TO_INDEX(query[level]);

        if (!crawl->childs[ind])
            return result;

        crawl = crawl->childs[ind];
    }

    bool isAWord = (crawl->isWord == true);
    bool isLast = isLastNode(crawl);

    if (isAWord && isLast) {
        return result;
    }

    if (!isLast) {
        string prefix = query;
        vector<string> partialResult = suggestWords(prefix, crawl);
        result.insert(result.end(), partialResult.begin(),partialResult.end());
        return result;
    }
    return result;
}

set<string> correct(trieNode* root, const string query) {
  stack<string> subs;
  vector<string> result;
  for(int i =query.size(); i > 0;i--) {
    subs.push(query.substr(0,i));
  }

  while(!subs.empty()) {
    vector<string> partialResult = autoSuggest(root,subs.top());
    result.insert(result.end(), partialResult.begin(), partialResult.end());
    subs.pop();
  }
  set<string> resultSet(result.begin(),result.end());
  return resultSet;
}

void loadFile (string fileName, trieNode* root) {
  std::ifstream infile(fileName);
  string word;
  while(getline(infile,word)) {
    insert(word, root);
    // cout<<word<<endl;
  }
}