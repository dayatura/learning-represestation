#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct Node
{ 
    char data; 
    struct Node *left; 
    struct Node *right; 
} Node;

Node* Kamus(char *data);
void printKamus(Node* kamus);
void addWord(Node* kamus, char* word);

int main(){
    Node *kamus  = Kamus("ayam");

    // printKamus(kamus);
    addWord(kamus, "domba");
    addWord(kamus, "cicak");
    addWord(kamus, "bebek");
    addWord(kamus, "bkbek");

    printKamus(kamus);

    return 0;
}

Node* Kamus(char *data) 
{
    // printf("%c \n", data);

    Node *node = (Node*)malloc(sizeof(Node)); 
    node->data = *(data);
    
    if(strlen(data) != 1) 
        node->left = Kamus((data+1));
    else
        node->left = NULL;
    node->right = NULL; 
    
    return(node); 
}

void printKamus(Node* kamus){
    
    printf("%c", kamus->data);

    if (kamus->left) {
        printf("-");
        printKamus(kamus->left);
    }

    if (kamus->right) {
        printf("\n|\n");
        printKamus(kamus->right);
    }
    
    // printf("%d ", kamus);
    // printf("%c ", kamus->data);

    // if (!kamus->right) {
    //     printf("kanan kosong %d ", kamus->right);
    //     // printKamus(kamus->right);
    // }

    // if(!kamus->left){
    //     printf("kiri kosong %d\n", kamus->left);
    // }else{
    //     printf("kiri tidak kosong, %d\n", kamus->left);
    //     printKamus(kamus->left);
    // }
    
    

}

void addWord(Node* kamus, char* word){
    // printf( &kamus->data);
    char a = word[0];
    char b = kamus->data;
    // printf("%c", a);

    if (a > kamus->data) {
        if (!kamus->right) {
            kamus->right = Kamus(word);
        }else
        {
            addWord(kamus->right, word);
        }
    }else if (a < kamus->data) {
        Node* right = kamus->right;
        Node* left = kamus->left;

        kamus->right = Kamus(&kamus->data);
        kamus->data = *(word);
        kamus->left = Kamus((word+1));

        kamus->right->left = left;
        kamus->right->right = right;
    }else{
        if (!kamus->left) {
            kamus->left = Kamus((word+1));
        }else{
            addWord(kamus->left, (word+1));
        }
        
    }
    
    
    
}