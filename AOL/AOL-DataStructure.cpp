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
#define charToIndex(c) (((int)c) - ((int)'a'))
const int ALPHABET_SIZE = 26;

struct trieNode{
    bool isEndOfWord;
    char *desc;
    trieNode *child[ALPHABET_SIZE];
};

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

    if(count > 0)
    {
        return true;
    }

    return false;
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

        free(current->desc);
        current->desc = (char*)malloc(strlen(desc) + 1);
        strcpy(current->desc, desc);
    }
}

void realeseNewSlangWord(trieNode *node)
{   
    char *slangWord = (char*)malloc(10);
    char *desc = (char*)malloc(100);

    printf("Input a new slang word [Must be more than 1 characters and contains no space]: ");
    scanf("%s", slangWord);
    getchar();

    void descInput()
    {
        printf("Input a new slang word description [Must be more than 2 words]: ");
        scanf("%[^\n]", desc);
        getchar();
    }

    if(validateWord(slangWord))
    {
        descInput();
    }
    else
    {
        while(true)
        {
            printf("Input a new slang word [Must be more than 1 characters and contains no space]: ");
            scanf("%s", slangWord);
            getchar();
            if(validateWord(slangWord))
            {
                descInput();
                break;
            }
        }
    }

    insertNode(node, slangWord, desc);

    printf("Successfully released new slang word\n");

    free(slangWord);
    free(desc);
}



