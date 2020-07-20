#pragma once

#include "trie.h"
#include <vector>
#include <string>
#include <mutex>

using namespace std;

class TrieSingleton {
private:
	static TrieSingleton* instance;
	static mutex mutex_;

protected:
	TrieSingleton( ) {

	}
	~TrieSingleton() {}

public:
	struct trieNode* root = createNode();
	TrieSingleton( TrieSingleton& other) = delete;
	void operator=( const TrieSingleton& other) = delete;

	static TrieSingleton *GetInstance();
};

TrieSingleton* TrieSingleton::instance(nullptr);
mutex TrieSingleton::mutex_;

TrieSingleton* TrieSingleton::GetInstance() {
	if (instance == nullptr) {
		lock_guard<mutex> lock(mutex_);
		if (instance == nullptr) {
			instance = new TrieSingleton();
		}
	}
	return instance;
}


void loadFileSingleton (string fileName) {
	TrieSingleton* s = TrieSingleton::GetInstance();
	loadFile (fileName, s->root);
}

void insertSingleton (string query) {
	TrieSingleton* s = TrieSingleton::GetInstance();
	insert(query, s->root);
}

bool searchSingleton (string query) {
	TrieSingleton* s = TrieSingleton::GetInstance();
	return search(query, s->root);
}

vector<string> nFirstSuggestionsSingleton(string query, int num) {
	TrieSingleton* s = TrieSingleton::GetInstance();
	return getNSuggestions(s->root, query, num);
}

vector<string> correctSingleton(string query) {
	TrieSingleton* s = TrieSingleton::GetInstance();
	return correct(s->root, query);
}