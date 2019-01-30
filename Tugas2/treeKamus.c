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
void printKamus(Node* kamus, int deep);
void addWord(Node* kamus, char* word);


int main(){
    int deep = 0;

    ///////////////////kamus dengan tree
    Node *kamus  = Kamus("ayam");
    // printKamus(kamus);
    addWord(kamus, "domba");
    addWord(kamus, "cicak");
    addWord(kamus, "candaan");
    addWord(kamus, "candi");
    addWord(kamus, "bebek");
    addWord(kamus, "dambaan");
    printKamus(kamus, deep);
    printf("\n");

	
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

void printKamus(Node* kamus, int deep){
    
    printf("%c", kamus->data);

    if (kamus->left) {
        // printf("(%d)", deep);
        deep++;
        printf("-");
        printKamus(kamus->left, deep);
        deep--;
    }

    if (kamus->right) {
        
        printf("\n");
        // printf("%d", deep);
        if(deep != 0)
        for(int i = 0; i < (deep); i++)
        {
            printf("  ");
        }
        
        printf("|\n");

        if(deep != 0)
        for(int i = 0; i < deep; i++)
        {
            printf("  ");
        }

        printKamus(kamus->right, deep);
    }

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