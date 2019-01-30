#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

// ==== Constant ====

#define INITIAL_BLOCK_COUNT 1000
#define BLOCK_SIZE 10
#define LEFT_FLAG 1
#define RIGHT_FLAG 5
#define END_FLAG 9
#define NULL_INDEX -1

// ==== aobTree ====

typedef struct tree
{
    char *data;
    int root;
    int curr;
    int size;
} tree;

tree *create_tree();
bool search_tree(tree *t, char *s);
void insert_tree(tree *t, char *s);
void load_tree(tree *t, char *filename);
void save_tree(tree *t, char *filename);
void print_memory_tree(tree *t);
void print_tree(tree *t, int idx, int deep);

int main(){

    int deep = 0;
    char cmd, *arg;
    tree *t = create_tree();

    load_tree(t, "pohon2");

    // insert_tree(t, "domba");
    // insert_tree(t, "cicak");
    // insert_tree(t, "candaan");
    // insert_tree(t, "candi");
    // insert_tree(t, "bebek");
    // insert_tree(t, "dambaan");

    // print_memory_tree(t);
    print_tree(t, t->root, deep);
    printf("\n");

    // save_tree(t, "pohon2");



    // printf("\ncommand : ");
    // scanf("%c", &cmd);

    // while (cmd != 'x')
    // {
    //     if (cmd == 'a')
    //     {
    //         scanf("%s", arg);
    //         insert_tree(t, arg);
    //         printf("Word '%s' added successfully\n", arg);
    //     }
    //     else if (cmd == 'q')
    //     {
    //         scanf("%s", arg);
    //         if (search_tree(t, arg))
    //         {
    //             printf("Word '%s' exist\n", arg);
    //         }
    //         else
    //         {
    //             printf("Word '%s' does not exist\n", arg);
    //         }
    //     }
    //     else if (cmd == 's')
    //     {
    //         scanf("%s", arg);
    //         save_tree(t, arg);
    //         printf("Tree successfully saved to %s\n", arg);
    //     }
    //     else if (cmd == 'l')
    //     {
    //         scanf("%s", arg);
    //         load_tree(t, arg);
    //         printf("Tree successfully loaded from %s\n", arg);
    //     }
    //     else if (cmd == 'm')
    //     {
    //         printf("\n");
    //         print_memory_tree(t);
    //     }
    //     else
    //     {
    //         printf("wrong command!\n");
    //     }

    //     getchar();
    //     printf("\ncommand : ");
    //     scanf("%c", &cmd);
    // }


    return 0;
}


// ==== Initializer ====

tree *create_tree()
{
    tree *t = malloc(sizeof(tree));
    char *d = malloc(sizeof(char) * BLOCK_SIZE * INITIAL_BLOCK_COUNT);

    t->data = d;
    t->root = NULL_INDEX;
    t->curr = 0;
    t->size = BLOCK_SIZE * INITIAL_BLOCK_COUNT;

    return t;
}

// ==== Getter & Setter ====

char get_value_node(tree *t, int n_idx)
{
    return t->data[n_idx];
}

bool get_mark_node(tree *t, int n_idx)
{
    return t->data[n_idx + END_FLAG];
}

int get_left_node(tree *t, int n_idx)
{
    int l_idx;
    memcpy(&l_idx, &t->data[n_idx + LEFT_FLAG], sizeof(int));

    return l_idx;
}

int get_right_node(tree *t, int n_idx)
{
    int r_idx;
    memcpy(&r_idx, &t->data[n_idx + RIGHT_FLAG], sizeof(int));

    return r_idx;
}

void set_value_node(tree *t, int n_idx, char c)
{
    t->data[n_idx] = c;
}

void set_mark_node(tree *t, int n_idx, bool b)
{
    t->data[n_idx + END_FLAG] = b;
}

void set_left_node(tree *t, int n_idx, int l_idx)
{
    memcpy(&t->data[n_idx + LEFT_FLAG], &l_idx, sizeof(int));
}

void set_right_node(tree *t, int n_idx, int r_idx)
{
    memcpy(&t->data[n_idx + RIGHT_FLAG], &r_idx, sizeof(int));
}

// ==== Basic Function ====

bool is_empty_tree(tree *t)
{
    return t->curr == 0;
}

bool is_full_tree(tree *t)
{
    return !(t->curr < t->size);
}

int add_node(tree *t, char *s, int s_idx, int s_length)
{
    if (s_idx < s_length)
    {
        int n_idx = t->curr, l_idx;

        t->curr += BLOCK_SIZE;
        l_idx = add_node(t, s, s_idx + 1, s_length);

        set_value_node(t, n_idx, s[s_idx]);
        set_mark_node(t, n_idx, s_length == s_idx + 1);
        set_left_node(t, n_idx, l_idx);
        set_right_node(t, n_idx, NULL_INDEX);

        return n_idx;
    }
    else
    {
        return NULL_INDEX;
    }
}

// ==== Helper Function ====

bool search_word(tree *t, char *s, int s_idx, int s_length, int n_idx)
{
    char c = get_value_node(t, n_idx);

    if (s_length - s_idx == 1)
    {
        return c == s[s_idx] && get_mark_node(t, n_idx);
    }
    else
    {
        int l_idx, r_idx;

        if (n_idx == NULL_INDEX || s[s_idx] < c)
        {
            return false;
        }
        else if (s[s_idx] > c)
        {
            r_idx = get_right_node(t, n_idx);
            return r_idx == NULL_INDEX ? false : search_word(t, s, s_idx, s_length, r_idx);
        }
        else
        {
            l_idx = get_left_node(t, n_idx);
            return l_idx == NULL_INDEX ? false : search_word(t, s, s_idx + 1, s_length, l_idx);
        }
    }
}

int insert_word(tree *t, char *s, int s_idx, int s_length, int n_idx)
{
    if (s_idx < s_length)
    {
        char c = get_value_node(t, n_idx);
        int l_idx, r_idx, t_idx;

        if (n_idx == NULL_INDEX || s[s_idx] < c)
        {
            t_idx = add_node(t, s, s_idx, s_length);
            set_right_node(t, t_idx, n_idx);

            return t_idx;
        }
        else if (s[s_idx] > c)
        {
            r_idx = get_right_node(t, n_idx);
            t_idx = r_idx == NULL_INDEX ? add_node(t, s, s_idx, s_length) : insert_word(t, s, s_idx, s_length, r_idx);
            set_right_node(t, n_idx, t_idx);

            return n_idx;
        }
        else
        {
            l_idx = get_left_node(t, n_idx);
            t_idx = l_idx == NULL_INDEX ? add_node(t, s, s_idx + 1, s_length) : insert_word(t, s, s_idx + 1, s_length, l_idx);
            set_left_node(t, n_idx, t_idx);

            if (s_length == s_idx + 1)
            {
                set_mark_node(t, n_idx, true);
            }

            return n_idx;
        }
    }
    else
    {
        return n_idx;
    }
}

// ==== Main Function ====

bool search_tree(tree *t, char *s)
{
    return search_word(t, s, 0, strlen(s), t->root);
}

void insert_tree(tree *t, char *s)
{
    t->root = insert_word(t, s, 0, strlen(s), t->root);
}

void load_tree(tree *t, char *filename)
{
    FILE *f;

    f = fopen(filename, "r");
    fread(&t->root, sizeof(int), 1, f);
    fread(&t->curr, sizeof(int), 1, f);
    fread(t->data, sizeof(char), t->curr, f);
}

void save_tree(tree *t, char *filename)
{
    FILE *f;

    f = fopen(filename, "w");
    fwrite(&t->root, sizeof(int), 1, f);
    fwrite(&t->curr, sizeof(int), 1, f);
    fwrite(t->data, sizeof(char), t->curr, f);
    fclose(f);
}

void print_memory_tree(tree *t)
{
    int l_idx, r_idx;

    printf("Root : %05d\n", t->root);
    printf("Curr : %05d\n\n", t->curr);
    printf(" index | v |   l   |   r   |\n");
    printf(" ------+---+-------+-------+\n");

    for (int i = 0; i < t->curr; i += BLOCK_SIZE)
    {
        printf(" %05d |", i);
        printf(" %c |", get_value_node(t, i));

        l_idx = get_left_node(t, i);
        if (l_idx != NULL_INDEX)
        {
            printf(" %05d |", l_idx);
        }
        else
        {
            printf("       |");
        }

        r_idx = get_right_node(t, i);
        if (r_idx != NULL_INDEX)
        {
            printf(" %05d |", r_idx);
        }
        else
        {
            printf("       |");
        }

        printf(" %c\n", get_mark_node(t, i) ? '*' : ' ');
    }
}

void print_tree(tree *t, int idx, int deep){
    printf("%c", get_value_node(t,idx));

    int l_idx = get_left_node(t, idx);
    if (l_idx != NULL_INDEX) {
        deep++;
        printf("-");
        print_tree(t, l_idx, deep);
        deep--;
    }

    int r_idx = get_right_node(t, idx);
    if (r_idx != NULL_INDEX) {
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
        print_tree(t, r_idx, deep);
    }
    
    
}
