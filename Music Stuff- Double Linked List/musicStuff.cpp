#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100

struct Node{
    char song[MAX];
    char artist[MAX];
    char duration[MAX];
    Node *prev;
    Node *next;
};

Node *head = NULL;
Node *tail = NULL;

Node *createNode(char *song, char *artist, char *duration){
    Node *newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode->song, song);
    strcpy(newNode->artist, artist);
    strcpy(newNode->duration, duration);
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

void insertSong(char *song, char *artist, char *duration){
    Node *newNode = createNode(song, artist, duration);
    if(head == NULL){
        head = tail = newNode;
        return;
    }else{
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
        return;
    }
}

void clearPlaylist(){
    if(head == NULL){
        puts("Cannot remove, playlist is empty.");
        return;
    }
    Node *current = head;
    while(current != NULL){
        Node *temp = current;
        current = current->next;
        free(temp);
    }
    head = tail = NULL;
    puts("Playlist cleared.");
    return;
}

void insertAfter(char *oldSong, char *newSong, char *newArtist, char *newDuration){
    if(head == NULL){
        puts("Invalid, playlist is empty.");
        return;
    }
    Node *current = head;
    while(current != NULL){
        if(strcmp(current->song, oldSong) == 0){
           Node *newNode = createNode(newSong, newArtist, newDuration);
           newNode->next = current->next;
           newNode->prev = current;
           if(current->next != NULL){
                current->next->prev = newNode;
           }else{
                tail = newNode;
           }
           current->next = newNode;
           printf("Song \'%s\' inserted after \'%s\'.\n", newSong, oldSong);
           return;
        }
        current = current->next;
    }
    puts("Invalid, song not found.");
    return;
}

void insertBefore(char *oldSong, char *newSong, char *newArtist, char *newDuration){
    if(head == NULL){
        puts("Invalid, playlist is empty.");
        return;
    }
    Node *current = head;
    while(current != NULL){
        if(strcmp(current->song, oldSong) == 0){
           Node *newNode = createNode(newSong, newArtist, newDuration);
           newNode->next =current;
           newNode->prev = current->prev;
           if(current->prev != NULL){
                current->prev->next = newNode;
           }else{
                head = newNode;
           }
           current->prev = newNode;
           printf("Song \'%s\' inserted before \'%s\'.\n", newSong, oldSong);
           return;
        }
        current = current->next;
    }
    puts("Invalid, song not found.");
    return;
}

void removeSong(char *song){
    if(head == NULL){
        puts("Invalid, playlist is empty.");
        return;
    }
    Node *current = head;
    while(current != NULL){
        if(strcmp(current->song, song) == 0){
            if(current == head){
                head = current->next;
                if(head != NULL){
                    head->prev = NULL;
                }
            }else if(current == tail){
                tail = current->prev;
                if(tail != NULL){
                    tail->next = NULL;
                }
            }else{
                current->next->prev = current->prev;
                current->prev->next = current->next;
            }
            free(current);
            printf("Song \'%s\' removed from the playlist.\n", song);
            return;
        }
        current = current->next;
    }
}

void showPlaylist(){
    if(head == NULL){
        puts("Playlist is empty.");
        return;
    }
    Node *current = head;
    puts("Playlist:");
    while(current != NULL){
        printf("Title: %s | Artist: %s | Duration: %s\n",
        current->song, current->artist, current->duration);
        current = current->next;
    }
}

int main(){

    insertSong("Song Title 1", "Artist 1", "03.30");
    insertSong("Song Title 2", "Artist 2", "04.15");
    insertSong("Song Title 3", "Artist 3", "02.50");
    insertSong("Song Title 4", "Artist 4", "05.00");

    showPlaylist();

    insertAfter("Song Title 2", "Song Title 2.5", "Artist 2.5", "01.45");
    insertBefore("Song Title 4", "Song Title 3.5", "Artist 3.5", "02.30");

    showPlaylist();

    removeSong("Song Title 2.5");
    removeSong("Song Title 4");

    showPlaylist();

    clearPlaylist();

    showPlaylist();

    return 0;
}


