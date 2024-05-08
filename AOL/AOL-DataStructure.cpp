/*
AOL Data Structure
Alfandi Rifa'ul Nurhuda
2703393673
LM01
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

const int ALPHABET_SIZE = 26;

void clearScreen() // Function to clear the screen with OS specific command
{
    #ifdef _WIN32 // Checks if _WIN32 is defined, _WIN32 is defined in all window OS
        system("cls");
    #else // else, assume we are on a unix based system in which system(`clear`) is the command
        system("clear");
    #endif
}

struct trieNode{
    bool isEndOfWord;
    char *desc;
    trieNode *child[ALPHABET_SIZE];
};

int charToIndex(char c)
{
    return (int)c - 'a';
}

trieNode *createNode(char *slangWord, char *desc)
{
    trieNode *newNode = (trieNode*)malloc(sizeof(trieNode));

    if(newNode)
    {
        newNode->isEndOfWord = false;
        newNode->desc = (char*)malloc(strlen(desc) + 1);
        strcpy(newNode->desc, desc);

        for(int i=0; i<ALPHABET_SIZE; i++)
        {
            newNode->child[i] = NULL;
        }
        
        return newNode;
    }
}

trieNode *searchNode(trieNode *node, const char *slangWord)
{
    trieNode *current = node;

    for(int i=0; i<strlen(slangWord); i++){
        int index = charToIndex(slangWord[i]);

        if(!current->child[index])
        {
            return NULL;
        }

        current = current->child[index];
    }

    return (current != NULL && current->isEndOfWord) ? current : NULL;
}

void insertNode(trieNode *node, char *word, char *desc)
{
    trieNode *existingNode = searchNode(node, word);

    if(existingNode != NULL)
    {
        free(existingNode->desc);
        existingNode->desc = (char*)malloc(strlen(desc) + 1);
        strcpy(existingNode->desc, desc);

        puts("\nSuccessfully updated a slang word.");

        return;
    }
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

// function to validate the word is valid or not
bool validateWord(char *word)
{
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

bool validateDescription(char *desc)
{
    int count = 0;
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

void realeseNewSlangWord(trieNode *node)
{   
    char slangWord[10];
    char desc[100];
    getchar();

    do
    {
        printf("Enter the slang word [Must be more than 1 characters and contains no space]: ");
        scanf("%[^\n]", slangWord);
        getchar();
    }
    while(!validateWord(slangWord));

    do
    {
        printf("Enter the description [Must be more than 2 words]: ");
        scanf("%[^\n]", desc);
        getchar();
    }
    while(!validateDescription(desc));

    insertNode(node, slangWord, desc);

}

void searchSlangWord(trieNode *node)
{
    char slangWord[10];
    trieNode *searchedNode;

    do
    {
        printf("Input a slang word to be searched [Must be more than 1 characters and contain no space]: ");
        scanf("%s", slangWord);
        getchar();
    }
    while(!validateWord(slangWord));

    searchedNode = searchNode(node, slangWord);

    if(searchedNode != NULL)
    {
        puts("");
        printf("Slang word  : %s\n", slangWord);
        printf("Description : %s\n", searchedNode->desc);
    }
    else
    {
        puts("");
        printf("There is no word \"%s\" in the dictionary.\n", slangWord);
    }
}

void printAllWords(trieNode *node, char *prefix, int index, int *count)
{   
    if(node->isEndOfWord)
    {   
        prefix[index] = '\0';
        printf("%d. %s\n",(*count)++, prefix);
    }

    for(int i=0; i<ALPHABET_SIZE; i++)
    {
        if(node->child[i])
        {
            char newPrefix[index + 2];
            strncpy(newPrefix, prefix, index);
            newPrefix[index] = 'a' + i;
            newPrefix[index + 1] = '\0';
            printAllWords(node->child[i], newPrefix, index + 1, count);
        }
    }
}

void printWordsWithPrefix(trieNode *node, char *prefix)
{
    trieNode *current = node;
    int len = strlen(prefix);
    char word[len + 1];
    int count = 1;

    for(int i=0; i<len; i++)
    {
        int index = charToIndex(prefix[i]);

        if(!current->child[index])
        {
            printf("There is no prefix \"%s\" in the dictionary\n", prefix);
            return;
        }
        
        word[i] = prefix[i];
        current = current->child[index];
    }

    // If we reach here, we have found the node where the prefix ends
    // Now we need to print all words in the sub-trie of this node
    word[len] = '\0'; // word contains the prefix now
    printAllWords(current, prefix, len, &count);
}


void viewAllSlangWordsWithPrefix(trieNode *node)
{
    char prefix[10];

    printf("Enter the prefix to be searched: ");
    scanf("%s", prefix);
    getchar();

    puts("");
    printWordsWithPrefix(node, prefix);
}

void pressEnterToContinue()
{   
    puts("Press enter to continue...");
    getchar();
    clearScreen();
}

void mainMenu(trieNode *node)
{   
    clearScreen();
    int choice;

    printf("1. Realese a new slang word\n");
    printf("2. Search a slang word\n");
    puts("3. View all slang words starting with a certain prefix word");
    
    printf("Enter your choice: ");
    scanf("%d", &choice);
    clearScreen();

    switch(choice)
    {
        case 1:
            realeseNewSlangWord(node);
            pressEnterToContinue();
            break;

        case 2:
            searchSlangWord(node);
            pressEnterToContinue();
            break;

        case 3:
            viewAllSlangWordsWithPrefix(node);
            pressEnterToContinue();
            break;

        case 4:
            // viewAll(node);
            pressEnterToContinue();
            break;

        default:
            puts("Invalid choice\n");
    }
}

int main()
{
    trieNode *root = createNode(" ", " ");

    while(true)
    {
        mainMenu(root);
    }

    return 0;
}


