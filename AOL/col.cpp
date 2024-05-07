#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define ALPHABET_SIZE 26

struct TrieNode {
    struct TrieNode* children[ALPHABET_SIZE];
    bool isEndOfWord;
    char description[200]; // Changed to character array
};

// Fungsi untuk membuat dan menginisialisasi sebuah simpul Trie baru
struct TrieNode* createNode() {
    struct TrieNode* newNode = (struct TrieNode*)malloc(sizeof(struct TrieNode));
    if (newNode) {
        newNode->isEndOfWord = false;
        newNode->description[0] = '\0'; // Deskripsi kosong pada awalnya
        for (int i = 0; i < ALPHABET_SIZE; i++) {
            newNode->children[i] = NULL; // Semua anak-anak diatur ke NULL
        }
    }
    return newNode;
}

bool contains_space(char str[]) {
    int i;
    for (i = 0; str[i] != '\0'; i++) {
        if (str[i] == ' ') {
            return true;
        }
    }
    return false;
}

// Fungsi utk menhitung berapa total kata 
bool count_words(char str[]) {
    int count = 0;
    int in_word = 0;
    int i;
    for (i = 0; str[i] != '\0'; i++) {
        if (str[i] == ' ') {
            in_word = 0;
        } else if (!in_word) {
            in_word = 1;
            count++;
        }
    }
    return count > 2; // Jika lebih dari 2 maka akan return true
}

// Fungsi untuk memasukkan kata dan deskripsi ke dalam trie
void insert(struct TrieNode* root, char key[200], char description[200]) {
    struct TrieNode* current = root;
    for (int i = 0; key[i] != '\0'; i++) {
        int index = key[i] - 'a'; // Hitung indeks anak berdasarkan huruf
        if (!current->children[index]) {
            current->children[index] = createNode(); // Buat simpul baru jika belum ada
        }
        current = current->children[index]; // Pindah ke anak yang sesuai
    }
    current->isEndOfWord = true; // Tandai akhir dari kata
    strcpy(current->description, description); // Salin deskripsi kata ke dalam simpul
}

// Fungsi untuk mencari sebuah kata dalam trie
bool search(struct TrieNode* root, char key[200]) {
    struct TrieNode* current = root;
    for (int i = 0; key[i] != '\0'; i++) {
        int index = key[i] - 'a'; // Hitung indeks anak berdasarkan huruf
        if (!current->children[index]) {
            printf("Not Found\n"); 
            return false;
        }
        current = current->children[index]; // Pindah ke anak yang sesuai
    }
    if (current && current->isEndOfWord) {
        printf("Found '%s': %s\n", key, current->description); // Kata ditemukan
        return true;
    } else {
        printf("Not Found\n"); 
        return false;
    }
}

// Fungsi untuk mengubah deskripsi sebuah kata jika kata tersebut sudah ada di dalam trie
void updateDescription(struct TrieNode* root, char key[200], char newDescription[200]) {
    struct TrieNode* current = root;
    for (int i = 0; key[i] != '\0'; i++) {
        int index = key[i] - 'a'; // Hitung indeks anak berdasarkan huruf
        if (!current->children[index]) {
            printf("Word does not exist\n"); 
            return;
        }
        current = current->children[index]; // Pindah ke anak yang sesuai
    }
    if (current && current->isEndOfWord) {
        strcpy(current->description, newDescription); // Perbarui deskripsi kata
        printf("Description updated for '%s': %s\n", key, current->description); // Deskripsi diperbarui
    } else {
        printf("Word does not exist\n");
    }
}

// Fungsi rekursif untuk mencari dan menampilkan semua kata yang dimulai dengan sebuah prefiks
void suggestionsUtil(struct TrieNode* root, char prefix[], int idx) {
    if (root->isEndOfWord) {
        prefix[idx] = '\0'; 
        printf("%s: %s\n", prefix, root->description); // Tampilkan kata dan deskripsinya
    }
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (root->children[i]) {
            prefix[idx] = i + 'a'; // Tambahkan huruf ke prefiks
            suggestionsUtil(root->children[i], prefix, idx + 1); // Lanjutkan pencarian ke anak berikutnya
        }
    }
}

// Fungsi untuk menemukan dan menampilkan semua kata yang dimulai dengan sebuah prefiks
void findSuggestions(struct TrieNode* root, char prefix[200]) {
    struct TrieNode* current = root;
    int n = strlen(prefix);
    char word[n + 1];
    for (int i = 0; i < n; i++) {
        int index = prefix[i] - 'a'; // Hitung indeks anak berdasarkan huruf
        if (!current->children[index]) {
            printf("No words found with prefix '%s'\n", prefix); // Tidak ada kata yang ditemukan
            return;
        }
        word[i] = prefix[i]; // Salin prefiks ke array kata
        current = current->children[index]; // Pindah ke anak yang sesuai
    }
    word[n] = '\0'; 
    suggestionsUtil(current, word, n); // Panggil fungsi rekursif untuk menampilkan kata-kata
}

// Fungsi untuk menambahkan kata baru atau memperbarui deskripsi jika kata sudah ada
void addOrUpdate(struct TrieNode* root) {
    char key[200];
    char description[200];
    
    do {
    	printf("Enter the new slang word [More than 1 character]: ");
    	scanf("%[^\n]", key); getchar();
	} while(strlen(key) < 2 || contains_space(key));

	do {
		printf("Enter its description [More than 2 Words]: ");
    	scanf("%[^\n]", description); getchar();
	} while(!count_words(description));

    
    struct TrieNode* current = root;
    int length = strlen(key);
    for (int i = 0; i < length; i++) {
        int index = key[i] - 'a'; // Hitung indeks anak berdasarkan huruf
        if (!current->children[index]) {
            current->children[index] = createNode(); // Buat simpul baru jika belum ada
        }
        current = current->children[index]; // Pindah ke anak yang sesuai
    }
    
    if (current->isEndOfWord) {
        strcpy(current->description, description); // Perbarui deskripsi jika kata sudah ada
        printf("Description updated for '%s': %s\n", key, current->description); // Deskripsi diperbarui
    } else {
        current->isEndOfWord = true;
        strcpy(current->description, description); // Salin deskripsi kata ke dalam simpul
        printf("New word added: '%s' with description: %s\n", key, current->description); // Kata baru ditambahkan
    }
}

// Fungsi rekursif untuk menampilkan semua kata dalam trie secara urut
void viewAllUtil(struct TrieNode* root, char word[], int level) {
    if (root->isEndOfWord) {
        word[level] = '\0'; // Tambahkan pengahpusan string
        printf("%s: %s\n", word, root->description); // Tampilkan kata dan deskripsinya
    }
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (root->children[i]) {
            word[level] = i + 'a'; // Tambahkan huruf ke array kata
            viewAllUtil(root->children[i], word, level + 1); // Lanjutkan ke child berikutnya
        }
    }
}

// Fungsi untuk menampilkan semua kata dalam trie secara urut
void viewAll(struct TrieNode* root) {
    char word[200];
    viewAllUtil(root, word, 0); // Panggil fungsi rekursif untuk menampilkan kata-kata
}

// Fungsi untuk menampilkan menu dan mengarahkan ke fungsi yang sesuai berdasarkan pilihan pengguna
void showMenu(struct TrieNode* root) {
    int choice;
    
    printf("1. Add or Update a slang word\n");
    printf("2. Search a slang word\n");
    printf("3. View all slang words starting with a certain prefix word\n");
    printf("4. View all slang words\n");
    printf("5. Exit\n");
    printf("Enter your choice: ");
    scanf("%d", &choice); // Baca pilihan pengguna
    getchar(); // Clear input buffer
    
    switch(choice) {
        case 1:
            addOrUpdate(root); // Tambahkan atau perbarui kata
            break;
        case 2:
            {
                char input[200];
                
				do{
					printf("Enter the word you want to search [More than 1 character & No Space]: ");
                	scanf("%[^\n]", input); getchar();
				} while(contains_space(input) || strlen(input) < 2);
                search(root, input);
                break;
            }
        case 3:
            {
                char prefix[200];
                printf("Enter the prefix word: ");
                scanf("%s", prefix); 
                findSuggestions(root, prefix); // Cari dan tampilkan kata-kata yang dimulai dengan prefiks
                break;
            }
        case 4:
            viewAll(root);
            break;
        case 5:
            exit(0); // Keluar dari program
        default:
            printf("Invalid choice\n");
    }
}

// Fungsi utama program
int main() {
    struct TrieNode* root = createNode(); 
    insert(root, "hello", "Greeting hello hello"); 
    insert(root, "hellob", "Another Greeting Hello"); 
    insert(root, "world", "The planet 1"); 
    insert(root, "worlda", "The planet 2"); 
    insert(root, "worldb", "The planet 3"); 
    insert(root, "worldc", "The planet 4"); 
    insert(root, "worldd", "The planet 5"); 
    insert(root, "worlde", "The planet 6"); 
    insert(root, "worldf", "The planet 7"); 
    insert(root, "worldg", "The planet 8"); 
    insert(root, "worldh", "The planet 9"); 
    insert(root, "worldi", "The planet 10"); 
    insert(root, "worldj", "The planet 11"); 
    insert(root, "worldk", "The planet 12"); 
    insert(root, "worldl", "The planet 13"); 

    while (1) {
        showMenu(root);
    }

    return 0;
}

