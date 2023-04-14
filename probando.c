#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


// Definición de la estructura para un nodo trie
typedef struct TrieNode {
    char key;
    int count;
    struct TrieNode* children[26];
} TrieNode;

// Función para crear un nuevo nodo trie
TrieNode* createTrieNode(char key) {
    TrieNode* node = (TrieNode*) malloc(sizeof(TrieNode));
    node->key = key;
    node->count = 0;
    for (int i = 0; i < 26; i++) {
        node->children[i] = NULL;
    }
    return node;
}

// Función para insertar una cadena en el trie
void insert(TrieNode* root, char* str) {
    TrieNode* curr = root;
    for (int i = 0; str[i] != '\0'; i++) {
        int index = str[i] - 'a';
        if (curr->children[index] == NULL) {
            curr->children[index] = createTrieNode(str[i]);
        }
        curr = curr->children[index];
    }
    curr->count++;
}

// Función para buscar una cadena en el trie
int search(TrieNode* root, char* str) {
    TrieNode* curr = root;
    for (int i = 0; str[i] != '\0'; i++) {
        int index = str[i] - 'a';
        if (curr->children[index] == NULL) {
            return 0;
        }
        curr = curr->children[index];
    }
    return curr->count;
}

// Función para imprimir todas las cadenas en el trie
void printTrie(TrieNode* node, char* str, int level) {
    if (node->count > 0) {
        str[level] = '\0';
        printf("%s (%d)\n", str, node->count);
    }
    for (int i = 0; i < 26; i++) {
        if (node->children[i] != NULL) {
            str[level] = node->children[i]->key;
            printTrie(node->children[i], str, level + 1);
        }
    }
}

int main() {
    TrieNode* root = createTrieNode('\0');

    FILE *fp;
    int iii = 0;
    char word;
    char arr[100];

    fp = fopen("leeme.txt", "r");

    if(fp == NULL) {
        printf("No se pudo abrir");
        return 1;
    }

    char anterior;

    while(fscanf(fp, "%c", &word) == 1){
        if(word == ' ' || word == '\n' && anterior != ',' && anterior != '.') {
            insert(root, arr);
            for (int j = 0; j <= iii; j++) {
                arr[j] = '\0';
            }
            iii = 0;
        } else if(word != ',' && word != '.'){
            arr[iii++] = word;
        }
        anterior = word;
    }

    fclose(fp);

    char str[100];
    printf("Todas las cadenas en el trie:\n");
    printTrie(root, str, 0);
    return 0;
}
