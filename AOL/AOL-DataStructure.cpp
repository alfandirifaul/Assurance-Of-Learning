
/*
AOL Data Structure
Alfandi Rifa'ul Nurhuda
2703393673
LM01
*/


// Include the standard input/output header file 'stdio.h
#include <stdio.h> 
// Include the string header file 'string.h'
#include <string.h> 
// Include the standard library header file 'stdlib.h'
#include <stdlib.h> 
// Include the boolean header file 'stdbool.h'
#include <stdbool.h> 

// Constan variable to define the maximum length of the word
const int MAX_LENGTH = 100;

// Constan variable to define the amount of alphabet   
const int ALPHABET_SIZE = 26;

// Function to clear the screen with OS specific command
void clearScreen() 
{
    // Checks if _WIN32 is defined, _WIN32 is defined in all window OS
    #ifdef _WIN32 
        system("cls");
    // else, assume we are on a unix based system in which system(`clear`) is the command
    #else 
        system("clear");
    #endif
}

// Struct of trie node
struct trieNode{
    bool isEndOfWord;
    char *desc;
    trieNode *child[ALPHABET_SIZE];
};

// Function to convert character to index in range 0-25.
int charToIndex(char c)
{
    return (int)c - 'a';
}

// Function to create a new node
trieNode *createNode(char *slangWord, char *desc)
{
    trieNode *newNode = (trieNode*)malloc(sizeof(trieNode));

    // Initialize the node and set the isEndOfWord to false
    // Then allocate memory for the description and copy the description to the node
    if(newNode)
    {
        newNode->isEndOfWord = false;
        newNode->desc = (char*)malloc(strlen(desc) + 1);
        strcpy(newNode->desc, desc);

        // Initialize all child nodes to NULL
        // So that we can check if the child is present or not
        for(int i=0; i<ALPHABET_SIZE; i++)
        {
            newNode->child[i] = NULL;
        }
        
        return newNode;
    }
}

// Function to search a node in the trie
trieNode *searchNode(trieNode *node, const char *slangWord)
{
    trieNode *current = node;

    // Traverse the trie and check if the node is present or not
    // If the node is present, then return the node
    for(int i=0; i<strlen(slangWord); i++){
        int index = charToIndex(slangWord[i]);

        if(!current->child[index])
        {
            return NULL;
        }

        current = current->child[index];
    }

    // If the current node is the end of the word, then return the node
    return (current != NULL && current->isEndOfWord) ? current : NULL;
}

// Function to insert a node in the trie
void insertNode(trieNode *node, char *word, char *desc)
{   
    // Search the node in the trie
    trieNode *existingNode = searchNode(node, word);

    // If the node is exist, then update the description
    if(existingNode != NULL)
    {
        free(existingNode->desc);
        existingNode->desc = (char*)malloc(strlen(desc) + 1);
        strcpy(existingNode->desc, desc);

        puts("\nSuccessfully updated a slang word.");

        return;
    }

    // If the node is not exist, then create a new node
    else
    {
        trieNode *current = node;

        for(int i=0; i<strlen(word); i++)
        {
            int index = charToIndex(word[i]);

            if(!current->child[index])
            {
                current->child[index] = createNode(word, desc);
            }

            current = current->child[index];
        }

        current->isEndOfWord = true;

        strcpy(current->desc, desc);

        puts("\nSuccessfully released new slang word.");
    }
}

// Function to validate the word is valid or not valid
bool validateWord(char *word)
{   
    // Check the word length is more than 1 and contains space or not
    if(strlen(word) > 1)
    {
        for(int i=0; i<strlen(word); i++)
        {
            if(word[i] == ' ')
            {
                return false;
            }
        }
        return true;
    }
    
    return false;
}

// Function to validate the description is valid or not valid
bool validateDescription(char *desc)
{   
    // Variable to count the words in the description
    int count = 0;

    // Check the description contains more than 2 words or not
    for(int i=0; i<strlen(desc); i++)
    {
        if(desc[i] == ' ')
        {
            count++;
        }
    }

    if(count >= 1)
    {
        return true;
    }

    return false;
}

// Function to realese new slang word or updated existing slang word
void realeseNewSlangWord(trieNode *node)
{   
    char slangWord[100];
    char desc[100];
    getchar();

    // Ask the user for input the slang word
    // The slang word must be more than 1 characters and contains no space
    // And code will keep asking the user until the input is valid
    do
    {
        printf("Enter the slang word [Must be more than 1 characters and contains no space]: ");
        scanf("%[^\n]", slangWord);
        getchar();
    }
    while(!validateWord(slangWord));

    // Ask the user for input the description
    // The description must be more than 2 words
    // And code will keep asking the user until the input is valid
    do
    {
        printf("Enter the description [Must be more than 2 words]: ");
        scanf("%[^\n]", desc);
        getchar();
    }
    while(!validateDescription(desc));

    // Insert the node in the trie if all of the input requirement is valid
    insertNode(node, slangWord, desc);
}

// Function to search a slang word in the trie
void searchSlangWord(trieNode *node)
{
    char slangWord[10];
    trieNode *searchedNode;

    // Ask the user for input the slang word
    // The slang word must be more than 1 characters and contains no space
    // And code will keep asking the user until the input is valid
    do
    {
        printf("Input a slang word to be searched [Must be more than 1 characters and contain no space]: ");
        scanf("%s", slangWord);
        getchar();
    }
    while(!validateWord(slangWord));

    // Search the node in the trie
    searchedNode = searchNode(node, slangWord);

    // If the node is exist, then print the slang word and the description
    if(searchedNode != NULL)
    {
        puts("");
        printf("Slang word  : %s\n", slangWord);
        printf("Description : %s\n", searchedNode->desc);
        puts("");
    }

    // If the node is not exist, then print the message
    else
    {
        puts("");
        printf("There is no word \"%s\" in the dictionary.\n", slangWord);
    }
}

// Function to print all words in the trie
void printAllWords(trieNode *node, char *prefix, int index, int *count)
{   
    // If the node is the end of the word, then print the word
    if(node->isEndOfWord)
    {   
        prefix[index] = '\0';
        printf("%d. %s\n",(*count)++, prefix);
    }

    // Traverse all child nodes and print the word
    // If the child is exist, then call the function recursively to print the word
    for(int i=0; i<ALPHABET_SIZE; i++)
    {
        if(node->child[i])
        {
            char newPrefix[index + 2];
            strncpy(newPrefix, prefix, index);
            newPrefix[index] = 'a' + i;
            newPrefix[index + 1] = '\0';
            printAllWords(node->child[i], newPrefix, (index + 1), count);
        }
    }

    // Set the last character of the prefix to null character
    // So that the prefix will be empty
    prefix[index] = '\0';
}

// Function to print all words with prefix in the trie
void printWordsWithPrefix(trieNode *node, char *prefix)
{
    trieNode *current = node;
    int len = strlen(prefix);
    char word[len + 1];
    int count = 1;

    // Traverse the trie and check if the prefix is exist or not
    for(int i=0; i<len; i++)
    {
        // Convert the character to index
        int index = charToIndex(prefix[i]); 

        // If the child is not exist, then print the message
        if(!current->child[index])
        {
            printf("There is no prefix \"%s\" in the dictionary\n", prefix);
            return;
        }
        
        // Copy the prefix to the word so that the word will be the same as the prefix
        // Then set the current node to the child node
        word[i] = prefix[i];
        current = current->child[index];
    }

    // Set the last character of the word to null character
    // And then call the function to print all words with prefix
    word[len] = '\0'; 
    printf("Words start with \"%s\":\n", prefix);
    printAllWords(current, prefix, len, &count);
}

// Function to view all slang words with prefix
void viewAllSlangWordsWithPrefix(trieNode *node)
{
    char prefix[10];

    // Ask user to input prefix to search a slang word
    printf("Enter the prefix to be searched: ");
    scanf("%s", prefix);
    getchar();

    puts("");
    printWordsWithPrefix(node, prefix);
}

// Function to check if child is present or not
bool checkIfChildPresent(trieNode *node)
{
    for(int i=0; i<ALPHABET_SIZE; i++)
    {
        if(node->child[i] != NULL)
        {
            return true;
        }
    }

    return false;
}

// Function to view all slang words in the trie
void viewAllSlangWords(trieNode *node)
{   
    bool childPresent = checkIfChildPresent(node);

    if(!childPresent)
    {
        getchar();
        puts("There is no slang word in the dictionary.");
        return;
    }

    int count = 1;
    char prefix[100];
    
    puts("List of all slang words in the dictionary:");
    printAllWords(node, prefix, 0, &count);
    puts("");
    getchar();
}

// Function to create the line "press enter to continue..."
void pressEnterToContinue()
{   
    puts("Press enter to continue...");
    getchar();
    clearScreen();
}

// Function to display the menu of the program
// And call the function based on the user input
void mainMenu(trieNode *node)
{   
    clearScreen();
    int choice;

    // Display the menu to show to user
    puts("1. Realese a new slang word");
    puts("2. Search a slang word");
    puts("3. View all slang words starting with a certain prefix word");
    puts("4. View all slang words");
    puts("5. Exit");
    
    // Ask the user for input the choice
    printf("\nEnter your choice: ");
    scanf("%d", &choice);
    clearScreen();

    // Call the function based on the user input
    switch(choice)
    {
        // If the choice is 1, then call the function to realese new slang word 
        case 1:
            realeseNewSlangWord(node);
            pressEnterToContinue();
            break;

        // If the choice is 2, then call the function to search a slang word
        case 2:
            searchSlangWord(node);
            pressEnterToContinue();
            break;

        // If the choice is 3, then call the function to view all slang words with prefix
        case 3:
            viewAllSlangWordsWithPrefix(node);
            pressEnterToContinue();
            break;

        // If the choice is 4, then call the function to view all slang words
        case 4:
            viewAllSlangWords(node);
            pressEnterToContinue();
            break;
        
        // If the choice is 5, then exit the program
        case 5:
            puts("Thank you... Have a nice day :)");
            exit(0);
            break;

        // If the choice is invalid, then print the message
        default:
            puts("Invalid choice\n");
            break;
    }
}

int main()
{
    // Create a root node
    trieNode *root = createNode(" ", " ");

    // Display the menu to show to user
    while(true)
    {
        mainMenu(root);
    }

    return 0;
}

