#include <iostream>
#include <string>
#include<stack>

// #include "trieHash.h"
#include "singleton.h"

using namespace std;

int main() {


  // struct trieNode *root = createNode();

  // loadFile("english3.txt", root);

  // // vector<string> sug = getNSuggestions(root,"quee",3);
  
  // vector<string> corr = correct(root,"sandwish");

  // for(auto x: corr){
  //   cout<<x<<endl;
  // }

	loadFileSingleton("english.txt");


  for(string i: correctSingleton("sandwishes")) {
    cout<<i<<endl;
  }

	// if(i == true) { cout<< "true"<<endl;}

	// if(i == false) { cout<< "false"<<endl;}



}