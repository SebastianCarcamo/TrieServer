#pragma once

#include <iostream>
#include <unordered_map>
#include <string>
#include<vector>
#include <unordered_set>

using namespace std;

vector<string> deletions(string s) {
  vector<string> result;
  for(int i =0; i<s.size();i++) {
    string tmp = s;
    tmp.erase(tmp.begin()+i);
    result.push_back(tmp);
  }
  return result;
}

vector<string> transposition(string s) {
  vector<string> result;
  for(int i =0;i<s.size()-1;i++) {
    string tmpString = s;
    swap(tmpString[i],tmpString[i+1]);
    result.push_back(tmpString);
  }
  return result;
}

vector<string> replacement(string s) {
  string letters = "abcdefghijklmnopqrstuvwxyz";
  vector<string> result;

  for(int i = 0; i<s.size();i++) {
    string tmp = s;
    for(int j=0;j<letters.size();j++) {
        tmp[i] = letters[j];
        result.push_back(tmp);
    }
  }
  return result;
}

vector<string> insertion(string s) {
  string letters = "abcdefghijklmnopqrstuvwxyz";
  vector<string> result;
  for(int i=0;i<s.size()+1;i++) {
    string tmp = s;
    for(int j=0;j<letters.size();j++) {
      tmp.insert(i,letters.substr(j,1));
      result.push_back(tmp);
      tmp = s;
    }
  }
  return result;
}

vector<string> edit1(string s) {
  vector<string> result;
  vector<string> del = deletions(s);
  vector<string> tra = transposition(s);
  vector<string> rep = replacement(s);
  vector<string> ins = insertion(s);
  
  result.insert(result.end(),del.begin(),del.end());
  result.insert(result.end(),tra.begin(),tra.end());
  result.insert(result.end(),rep.begin(),rep.end());
  result.insert(result.end(),ins.begin(),ins.end());

  unordered_set<string> us;
  for(string i: result) {
    us.insert(i);
  }
  result.assign(us.begin(),us.end());
  return result;
}

vector<string> edit2(vector<string> v) {
  vector<string> result;
  for(auto i: v) {
    vector<string> tmp = edit1(i);
    result.insert(result.end(),tmp.begin(),tmp.end());
  }
  unordered_set<string> us;
  for(string i: result) {
    us.insert(i);
  }
  result.assign(us.begin(),us.end());
  return result;
}