// VALENT NATHANAEL LJ01 DATA STRUCTURES
// NIM: 2702343706

#include <bits/stdc++.h>
#define consumeNewline() cin.ignore(numeric_limits<streamsize>::max(),'\n');
using namespace std;

const int ALPHABET_NUMS = 26;

void clearScreen() // Function to clear the screen with OS specific command
{
    #ifdef _WIN32 // Checks if _WIN32 is defined, _WIN32 is defined in all window OS
        system("cls");
    #else // else, assume we are on a unix based system in which system(`clear`) is the command
        system("clear");
    #endif
}

struct Node {

    // pointer array for child nodes of each node
    Node* childNode[ALPHABET_NUMS];

    // Used for indicating ending of string
    string description;

    Node()
    {
        // constructor
        // initialize the description variable with NULL
        // initialize every index of childNode array with NULL
        description = "";
        for (int i = 0; i < ALPHABET_NUMS; i++) {
            childNode[i] = NULL;
        }
    }
};

struct Trie {
    private: // Contains stuffs that are not for usage outside of the trie struct
   Node* root; // The root of the node
    //Helper function to get words recursively 
    void getWordsWithPrefixRecursive(Node* cur, string word, vector<pair<string,string>>& wordArray )
    {
        if(cur->description != "")
        {
            wordArray.push_back(make_pair(word, cur->description));
        }
        for(int i = 0; i < 26; i++)
        {
            if(cur->childNode[i] != NULL)
            {
                getWordsWithPrefixRecursive(cur->childNode[i], word + char('a' + i), wordArray);
            }
        }
    }

    public: // Contains stuffs that are available from outside the trie struct, used to easily store and get information from and to the trie

    Trie()
    {
        root = NULL;
    }

    bool isEmpty()
    {
        return root == NULL;
    }

    // Method to insert a word in to the trie
    void insert(string key, string desc)
    {
        //Force the key to consists of lowercase characters
        // We assume its not case sensitive and we have 26 buckets for each char in the alphabet
        transform(key.begin(), key.end(), key.begin(), [](unsigned char c){ return std::tolower(c); }); 

        if(root == NULL) // If we are here that means there are no member in the trie yet
        {
            root = new Node(); // Create the root, represents an empty string
        }
        Node* cur = root;

        for(auto character: key) 
        {
            // We assume the key consists of lowercase alphabet
            int index = character-'a'; 
            if(cur->childNode[index] == NULL) 
            {
                Node* newNode = new Node();

                cur->childNode[index] = newNode;
            }
            cur = cur->childNode[index];
        }

        // Having description indicates that there is a word that consists of all the prefix char we just traversed
        cur->description = desc; 
    }

    //Search for a word, returns the description if found
    //Empty / "" description means that the word doesnt exist in the trie
    string search(string key)
    {
        //Force the key to consists of lowercase characters
        // We assume its not case sensitive and we have 26 buckets for each char in the alphabet
        transform(key.begin(), key.end(), key.begin(), [](unsigned char c){ return std::tolower(c); }); 
    
        if(root == NULL) // If we are here that means there are no member in the trie yet
        {
            root = new Node(); // Create the root, represents an empty string
        }
        Node* cur = root;
        for(auto character: key)
        {
            int index = character-'a';
            if(cur->childNode[index] == NULL)
            {
                return "";
            }
            cur = cur->childNode[index];
        }
        return cur->description;
        
    }
    // string pair, first is the word, second is the description
    vector<pair<string,string>> getWordsWithPrefix(string prefix)
    {
        vector<pair<string, string>> words;
        Node* cur = root;
        for(auto character: prefix)
        {
            int index = character-'a';
            if(cur->childNode[index] == NULL)
            {
                return words; // No words start with the prefix
            }
            cur = cur->childNode[index];
        }

        // Now cur points to the node corresponding to the last character of the prefix.
        // We need to find all words that start with this prefix.
        // We can do this using the getWordsWithPrefixRecursive function.

        getWordsWithPrefixRecursive(cur, prefix, words);

        return words;
    }

    vector<pair<string, string>> getAllWords()
    {
        vector<pair<string, string>> words;
        for(int i = 0; i < 26; i++)
        {
            if(root->childNode[i] != NULL)
            {
                getWordsWithPrefixRecursive(root->childNode[i], string(1, 'a' + i), words);
            }
        }
        return words;
    }

}slangWords;

bool validateWord(string word)// words need to consits of more than 1 character, with no space
{
    for(auto c: word)
        {
            if(c == ' ')// If the word has space, return false
            {
               return false;
            }
        }
        if(word.length() <= 1) // words need to consits of more than 1 character
        {
            return false;
        }
        return true;
}
bool validateDescription(string desc)
{
    // We get each word that the user input as a string vector
     // Each word is indicated by a space as a sepparator
    istringstream iss(desc);
    vector<string> words((istream_iterator<string>(iss)), istream_iterator<string>());
    if(words.size() >= 2) // Means that the description is valid
    {
        return true;
    }
    return false;
}

void insertSlangWord()
{
    string inp;
    string desc;

    while(true){
        bool pass = true;
        cout<<"Input a new slang word [Must be more than 1 characters and contains no space]: ";
        getline(cin, inp);
        if(validateWord(inp)){
            break;
        }
    }

    while(true)
    {
        cout<<"Input a new slang word description [Must be more than 2 words]: ";
        getline(cin, desc);
        if(validateDescription(desc))
        {
            break;
        }
    }

    if(slangWords.search(inp) != "")
    {
        cout<<"Successfully updated a slang word\n";
    }else{
        cout<<"Successfully released new slang word\n";
    }

    slangWords.insert(inp,desc);
}

void searchSlangWord()
{
    string inp;
    
    while(true)
    {
        bool pass = true;
        //Same validation mechanism as inserting
        cout<<"Input a slang word to be searched [Must be more than 1 characters and contains no space]: ";
        getline(cin, inp);
        if(validateWord(inp))
        {
            break;   
        }
    }
    string searchDesRes = slangWords.search(inp);
    if(searchDesRes == "")
    {
        cout<<"There is no word \""<<inp<<"\" in the dictionary"<<endl;
    }else{
        cout<<"Slang word : "<<inp<<endl;
        cout<<"Description : "<<searchDesRes<<endl;
    }
}
void searchPrefix()
{
    string prefixSearch;
    cout<<"Input a prefix to be searched: ";
    cin>>prefixSearch;
    
    if(slangWords.isEmpty())
    {
        cout<<"There is no slang word yet in the dictionary."<<endl;
        return;
    }
    vector<pair<string,string>> words = slangWords.getWordsWithPrefix(prefixSearch);
    int wordsCount = words.size();
    if(wordsCount == 0)
    {
        cout<<"There is no prefix \""<<prefixSearch<<"\" in the dictionary"<<endl;
    }else{
         cout<<"Words starts with \""<<prefixSearch<<"\":"<<endl;
          for(int i =0;i<wordsCount;i++)
        {
            pair<string,string> currentWordDescriptionPair = words[i];
            cout<<i+1<<". "<<currentWordDescriptionPair.first<<endl;
        }
    }
    consumeNewline();
}
void searchLexicographically()
{
    
     if(slangWords.isEmpty())
    {
        cout<<"There is no slang word yet in the dictionary."<<endl;
        return;
    }
    vector<pair<string,string>> words = slangWords.getAllWords();
    int wordsCount = words.size();
    cout<<"List of all slang words in the dictionary:"<<endl;
    for(int i =0;i<wordsCount;i++)
    {
        pair<string,string> currentWordDescriptionPair = words[i];
        cout<<i+1<<". "<<currentWordDescriptionPair.first<<endl;
    }
}
bool drawMenu()
{
    cout<<"1.Release a new slang word"<<endl;
    cout<<"2.Search a slang word"<<endl;
    cout<<"3.View all slang words starting with a certain prefix word"<<endl;
    cout<<"4.View all slang words"<<endl;
    cout<<"5.Exit"<<endl;
    int choice;
    do{
        cin>>choice;
    }while((choice <= 0 || choice >=6));
    consumeNewline();
    switch(choice)
        {
        case 1:
        insertSlangWord();
        break;
        case 2:
        searchSlangWord();
        break;
        case 3:
        searchPrefix();
        break;
        case 4:
        searchLexicographically();
        break;
        case 5:
        return true;
        break;
    }
    return false;
}

int main()
{
    while(true)
    {
        bool exit = drawMenu();
        if(exit)
        {
            break;
        }
        cout<<"Press enter to continue....";
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
        clearScreen();
    }
    cout<<"Thank you... Have a nice day :)"<<endl;
}