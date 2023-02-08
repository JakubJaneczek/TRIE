#include <iostream>
#include <string>

using namespace std;

const int SIZE = 26;

// trie node
struct TrieNode
{
    struct TrieNode* children[SIZE];

    string translation;
    bool isEndOfWord;
};

struct TrieNode* getNode(void)
{
    struct TrieNode* node = new TrieNode;

    node->isEndOfWord = false;

    for (int i = 0; i < SIZE; i++)
        node->children[i] = NULL;

    return node;
}

void insert(struct TrieNode* root, const string &key, const string &translation)
{
    struct TrieNode* tmp = root;

    for (unsigned int i = 0; i < key.length(); i++)
    {
        int index = key[i] - 'a';
        if (tmp->children[index] == nullptr)
            tmp->children[index] = getNode();

        tmp = tmp->children[index];
    }
    tmp->translation = translation;
    tmp->isEndOfWord = true;
}

void deleteAll(struct TrieNode* root)
{
    for (int i = 0; i < SIZE; i++) 
    {
        if (root->children[i] != nullptr)
        {
            deleteAll(root->children[i]);
        }
    }
    delete root;
}

bool search(struct TrieNode* root, const string &key)
{
    struct TrieNode* tmp = root;

    for (unsigned int i = 0; i < key.length(); i++)
    {
        int index = key[i] - 'a';
        if (tmp->children[index] == nullptr)
        {
            return false;
        }

        tmp = tmp->children[index];
    }
    cout << tmp->translation << "\n";
    return (tmp->isEndOfWord);
}

void findAll(struct TrieNode* tmp)
{
    if (tmp->translation != "-")
    {
        cout << tmp->translation << "\n";
    }
    for (int i = 0; i < SIZE; i++)
    {
        if (tmp->children[i] != nullptr)
        {
            findAll(tmp->children[i]);
        }
    }
}

bool searchAll(struct TrieNode* root, const string &key)
{
    struct TrieNode* tmp = root;

    for (unsigned int i = 0; i < key.length(); i++)
    {
        int index = key[i] - 'a';
        if (tmp->children[index] == nullptr)
        {
            return false;
        }
        tmp = tmp->children[index];
    }
    
    findAll(tmp);
    return true;
}


int main()
{
    struct TrieNode* root = getNode();
    char command;
    string key, translation;

    while (cin >> command)
    {
        cin >> key;
        switch (command)
        {
        case '+':
            cin >> translation;
            insert(root, key, translation);
            break;
        case '?':
            if(!search(root, key))
                cout << '-' << "\n";
            break;
        case '*':
            if(!searchAll(root, key))
                cout << '-' << "\n";
            break;
        }
    }   
    deleteAll(root);
    return 0;
}