#include <bits/stdc++.h>
using namespace std;

struct TrieNode {
    TrieNode* children[26];
    bool isEnd;

    TrieNode() {
        isEnd = false;
        for(int i = 0; i < 26; ++i)
            children[i] = nullptr;
    }
};

class Trie {
    TrieNode* root;

public:
    Trie() {
        root = new TrieNode();
    }

    void insert(const string& word) {
        TrieNode* node = root;
        for(char ch : word) {
            int index = ch - 'a';
            if (!node->children[index])
                node->children[index] = new TrieNode();
            node = node->children[index];
        }
        node->isEnd = true;
    }

    void suggestionsHelper(TrieNode* node, string current, vector<string>& result) {
        if (!node) return;
        if (node->isEnd)
            result.push_back(current);

        for (int i = 0; i < 26; ++i) {
            if (node->children[i]) {
                suggestionsHelper(node->children[i], current + char(i + 'a'), result);
            }
        }
    }

    vector<string> getSuggestions(const string& prefix) {
        TrieNode* node = root;
        for(char ch : prefix) {
            int index = ch - 'a';
            if (!node->children[index])
                return {};  
            node = node->children[index];
        }

        vector<string> result;
        suggestionsHelper(node, prefix, result);
        return result;
    }
};


int main() {
    Trie trie;
    vector<string> words = {
        "apple", "app", "apply", "ape", "bat", "ball", "bark", "banana"
    };

    for (auto& word : words)
        trie.insert(word);

    string query;
    cout << "Enter prefix to get word suggestions (type 'exit' to quit):\n";
    while (true) {
        cout << "\nPrefix: ";
        cin >> query;
        if (query == "exit") break;

        vector<string> suggestions = trie.getSuggestions(query);
        if (suggestions.empty())
            cout << "No suggestions found.\n";
        else {
            cout << "Suggestions:\n";
            for (auto& word : suggestions)
                cout << "  - " << word << '\n';
        }
    }
    return 0;
}
