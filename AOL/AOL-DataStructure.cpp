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
        newNode->isEndOfWord = slangWord[slangWord[strlen(slangWord)-1]] == '\0' ? true : false;
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

        puts("Successfully updated the slang word.\n");

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

        puts("Successfully released new slang word.\n");
    }
}

// function to validate the word is valid or not
bool validateWord(char *word)
{
    for(int i=0; i<strlen(word); i++)
    {
        if(word[i] == ' ')
        {
            return false;
        }
    }

    if(strlen(word) <= 1)
    {
        return false;
    }

    return true;
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
    do
    {
        printf("Enter the slang word: ");
        scanf("%s", slangWord);
        getchar();
    }
    while(!validateWord(slangWord));

    do
    {
        printf("Enter the description: ");
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
        printf("Enter the slang word: ");
        scanf("%s", slangWord);
        getchar();
    }
    while(!validateWord(slangWord));

    searchedNode = searchNode(node, slangWord);

    if(searchedNode != NULL)
    {
        printf("Slang word  : %s\n", slangWord);
        printf("Description : %s\n", searchedNode->desc);
    }
    else
    {
        printf("There is no word \"%s\" in the dictionary.\n", slangWord);
    }
}

void mainMenu(trieNode *node)
{
    int choice;

    printf("1. Realese a new slang word\n");
    printf("2. Search a slang word\n");
    puts("3. View all slang words starting with a certain prefix word");
    
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch(choice)
    {
        case 1:
            realeseNewSlangWord(node);
            break;
        case 2:
            searchSlangWord(node);
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


