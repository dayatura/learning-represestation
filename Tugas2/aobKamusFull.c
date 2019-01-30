#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

// ==== Constant ====

#define HEADER 12
#define ROOT 0
#define CURRENT 4
#define SIZE 8

#define BLOCK_SIZE 10
#define LEFT_FLAG 1
#define RIGHT_FLAG 5
#define END_FLAG 9
#define NULL_INDEX -1

#define INITIAL_BLOCK_COUNT 1000

// ==== aobTree ====

char *create_tree();
bool search_tree(char *t, char *s);
void insert_tree(char *t, char *s);
void load_tree(char *t, char *filename);
void save_tree(char *t, char *filename);
void print_memory_tree(char *t);
void print_tree(char *t, int idx, int deep);

// HEADER
void set_root_node(char *t, int root_idx)
{
    memcpy(&t[ROOT], &root_idx, sizeof(int));
}

void set_curr_node(char *t, int curr_idx)
{
    memcpy(&t[CURRENT], &curr_idx, sizeof(int));
}

void set_size_max(char *t, int size_max)
{
    int size = size_max * BLOCK_SIZE;
    memcpy(&t[SIZE], &size, sizeof(int));
}

int get_root_node(char *t)
{
    int root_idx;
    memcpy(&root_idx, &t[ROOT], sizeof(int));

    return root_idx;
}

int get_curr_node(char *t)
{
    int curr_idx;
    memcpy(&curr_idx, &t[CURRENT], sizeof(int));

    return curr_idx;
}

int get_size_max(char *t)
{
    int size_max;
    memcpy(&size_max, &t[SIZE], sizeof(int));

    return size_max;
}

int main()
{

    int deep = 0;
    char cmd, *arg;
    char *t;
    t = create_tree();

    load_tree(t, "pohonFull");

    // insert_tree(t, "domba");
    // insert_tree(t, "cicak");
    // insert_tree(t, "candaan");
    // insert_tree(t, "candi");
    // insert_tree(t, "bebek");
    // insert_tree(t, "dambaan");
    // insert_tree(t, "celah");

    print_memory_tree(t);
    printf("\n");
    print_tree(t, get_root_node(t), deep);
    printf("\n");

    // save_tree(t, "pohonFull");

    return 0;
}

// ==== Initializer ====

char *create_tree()
{
    char *t = malloc(sizeof(char) * (HEADER + BLOCK_SIZE * INITIAL_BLOCK_COUNT));

    set_size_max(t, 1000);
    set_root_node(t, -1);
    set_curr_node(t, HEADER);

    return t;
}

// ==== Getter & Setter ====

char get_value_node(char *t, int n_idx)
{
    return t[n_idx];
}

bool get_mark_node(char *t, int n_idx)
{
    return t[n_idx + END_FLAG];
}

int get_left_node(char *t, int n_idx)
{
    int l_idx;
    memcpy(&l_idx, &t[n_idx + LEFT_FLAG], sizeof(int));

    return l_idx;
}

int get_right_node(char *t, int n_idx)
{
    int r_idx;
    memcpy(&r_idx, &t[n_idx + RIGHT_FLAG], sizeof(int));

    return r_idx;
}

void set_value_node(char *t, int n_idx, char c)
{
    t[n_idx] = c;
}

void set_mark_node(char *t, int n_idx, bool b)
{
    t[n_idx + END_FLAG] = b;
}

void set_left_node(char *t, int n_idx, int l_idx)
{
    memcpy(&t[n_idx + LEFT_FLAG], &l_idx, sizeof(int));
}

void set_right_node(char *t, int n_idx, int r_idx)
{
    memcpy(&t[n_idx + RIGHT_FLAG], &r_idx, sizeof(int));
}

// ==== Basic Function ====

bool is_empty_tree(char *t)
{
    return get_curr_node(t) == 12;
}

bool is_full_tree(char *t)
{
    return !(get_curr_node(t) < get_size_max(t));
}

int add_node(char *t, char *s, int s_idx, int s_length)
{
    if (s_idx < s_length)
    {
        int n_idx = get_curr_node(t), l_idx;

        set_curr_node(t, get_curr_node(t) + BLOCK_SIZE);
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

bool search_word(char *t, char *s, int s_idx, int s_length, int n_idx)
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

int insert_word(char *t, char *s, int s_idx, int s_length, int n_idx)
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

bool search_tree(char *t, char *s)
{
    return search_word(t, s, 0, strlen(s), get_root_node(t));
}

void insert_tree(char *t, char *s)
{
    int root_idx = get_root_node(t);
    root_idx = insert_word(t, s, 0, strlen(s), root_idx);
    set_root_node(t, root_idx);
}

void load_tree(char *t, char *filename)
{

    int curr;
    FILE *f = fopen(filename, "rb");

    fread(t, sizeof(char), 12, f);
    fseek(f, 0, SEEK_SET);
    fread(t, sizeof(char), get_curr_node(t), f);
    fclose(f);
}

void save_tree(char *t, char *filename)
{
    FILE *f;

    f = fopen(filename, "wb");
    fwrite(t, sizeof(char), get_curr_node(t), f);
    fclose(f);
}

void print_memory_tree(char *t)
{
    int l_idx, r_idx;

    printf("*---------------------------*\n");
    printf("| index |        ISI        |\n");
    printf("|---------------------------|\n");

    printf("| 00000 |       %05d       | <-- Root\n", get_root_node(t));
    printf("| 00004 |       %05d       | <-- Curr\n", get_curr_node(t));
    printf("| 00008 |       %05d       | <-- SizeMax\n", get_size_max(t));
    // printf("|-------|---|-------|-------|\n");

    for (int i = HEADER; i < get_curr_node(t); i += BLOCK_SIZE)
    {
        printf("| %05d |", i);
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

        printf(" %s\n", get_mark_node(t, i) ? "EOW" : " " );
    }
}

void print_tree(char *t, int idx, int deep)
{
    printf("%c", get_value_node(t, idx));

    int l_idx = get_left_node(t, idx);
    if (l_idx != NULL_INDEX)
    {
        deep++;
        printf("-");
        print_tree(t, l_idx, deep);
        deep--;
    }

    int r_idx = get_right_node(t, idx);
    if (r_idx != NULL_INDEX)
    {
        printf("\n");
        // printf("%d", deep);
        if (deep != 0)
            for (int i = 0; i < (deep); i++)
            {
                printf("  ");
            }

        printf("|\n");

        if (deep != 0)
            for (int i = 0; i < deep; i++)
            {
                printf("  ");
            }
        print_tree(t, r_idx, deep);
    }
}
