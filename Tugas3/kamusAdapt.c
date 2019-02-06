#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

// ==== Constant ====

#define HEADER 16
#define ROOT 0
#define CURRENT 4
#define SIZE 8
#define SYSTEM 12

#define NULL_INDEX 0

#define INITIAL_BLOCK_COUNT 1000

// ==== aobTree ====

char *create_tree();
bool search_tree(char *t, char *s);
void insert_tree(char *t, char *s);
char *load_tree(char *t, char *filename);
void save_tree(char *t, char *filename);
void print_memory_tree(char *t);
void print_tree(char *t, unsigned int idx, unsigned int deep);

unsigned int get_block_size(char *t);

// HEADER
void set_root_node(char *t, unsigned int root_idx)
{
    memcpy(&t[ROOT], &root_idx, sizeof(unsigned int));
}

void set_curr_node(char *t, unsigned int curr_idx)
{
    memcpy(&t[CURRENT], &curr_idx, sizeof(unsigned int));
}

void set_size_max(char *t, unsigned int size_max)
{
    unsigned int size = size_max;
    memcpy(&t[SIZE], &size, sizeof(unsigned int));
}


void set_address_size(char *t, unsigned int addrSize)
{
    memcpy(&t[SYSTEM], &addrSize, sizeof(unsigned int));
}


unsigned int get_address_size(char *t)
{
    unsigned int addrSize = 0;
    memcpy(&addrSize, &t[SYSTEM], sizeof(unsigned int));

    return addrSize;
}

unsigned int get_root_node(char *t)
{
    unsigned int root_idx = 0;
    memcpy(&root_idx, &t[ROOT], sizeof(unsigned int));

    return root_idx;
}

unsigned int get_curr_node(char *t)
{
    unsigned int curr_idx = 0;
    memcpy(&curr_idx, &t[CURRENT], sizeof(unsigned int));

    return curr_idx;
}

unsigned int get_size_max(char *t)
{
    unsigned int size_max = 0;
    memcpy(&size_max, &t[SIZE], sizeof(unsigned int));

    return size_max;
}

// ================== getter address =========================

unsigned int get_left_flag(char *t){
    return 1;
}
unsigned int get_right_flag(char *t){
    return get_left_flag(t) + get_address_size(t);
}
unsigned int get_end_flag(char *t){
    return get_right_flag(t) + get_address_size(t); 
}
unsigned int get_block_size(char *t)
{
    return get_end_flag(t) + 1;
}


// ==== Initializer ====

char *create_tree(unsigned int addrSize)
{
    char *t = malloc(sizeof(char) * pow(256, addrSize) );

    set_address_size(t, addrSize);
    set_size_max(t, (unsigned int) pow(256, addrSize) - 1 );

    set_root_node(t, 0);
    set_curr_node(t, HEADER);

    return t;
}

// ==== Getter & Setter ====

char get_value_node(char *t, unsigned int n_idx)
{
    return t[n_idx];
}

bool get_mark_node(char *t, unsigned int n_idx)
{
    return t[n_idx + get_end_flag(t)];
}

unsigned int get_left_node(char *t, unsigned int n_idx)
{
    int l_idx  = 0;
    memcpy(&l_idx, &t[n_idx + get_left_flag(t)], get_address_size(t));

    return l_idx;
}

unsigned int get_right_node(char *t, unsigned int n_idx)
{
    unsigned int r_idx = 0;
    memcpy(&r_idx, &t[n_idx + get_right_flag(t)], get_address_size(t));

    return r_idx;
}

void set_value_node(char *t, unsigned int n_idx, char c)
{
    t[n_idx] = c;
}

void set_mark_node(char *t, unsigned int n_idx, bool b)
{
    t[n_idx + get_end_flag(t)] = b;
}

void set_left_node(char *t, unsigned int n_idx, unsigned int l_idx)
{
    memcpy(&t[n_idx + get_left_flag(t)], &l_idx, get_address_size(t));
}

void set_right_node(char *t, unsigned int n_idx, unsigned int r_idx)
{
    memcpy(&t[n_idx + get_right_flag(t)], &r_idx, get_address_size(t));
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

unsigned int add_node(char *t, char *s, unsigned int s_idx, unsigned int s_length)
{
    if (!is_full_tree(t))
    if (s_idx < s_length)
    {
        unsigned int n_idx = get_curr_node(t), l_idx;

        set_curr_node(t, get_curr_node(t) + get_block_size(t));
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
    else
    {
        printf("Memori penuh pada input kata %s \n", s);
        return get_curr_node(t);
    }
    
}

// ==== Helper Function ====

bool search_word(char *t, char *s, unsigned int s_idx, unsigned int s_length, unsigned int n_idx)
{
    char c = get_value_node(t, n_idx);

    if (s_length - s_idx == 1)
    {
        if (c == s[s_idx]){
            return get_mark_node(t, n_idx);
        }else{
            unsigned int r_idx = get_right_node(t, n_idx);
            return r_idx == NULL_INDEX ? false : search_word(t, s, s_idx, s_length, r_idx);
        }
    }
    else
    {
        unsigned int l_idx, r_idx;

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

unsigned int insert_word(char *t, char *s, unsigned int s_idx, unsigned int s_length, unsigned int n_idx)
{
    if (s_idx < s_length)
    {
        char c = get_value_node(t, n_idx);
        unsigned int l_idx, r_idx, t_idx;

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
    // if ( is_full_tree(t) ) {
    //     printf("Memori sudah penuh \n");
    // }else
    // {
        unsigned int root_idx = get_root_node(t);
        root_idx = insert_word(t, s, 0, strlen(s), root_idx);
        set_root_node(t, root_idx);    
    // }
    
    
    
}

char* load_tree(char *t, char *filename)
{
    t = malloc(sizeof(char) * HEADER );

    unsigned int curr;
    FILE *f = fopen(filename, "rb");

    fread(t, sizeof(char), HEADER, f);
    fseek(f, 0, SEEK_SET);

    char *res = realloc(t, sizeof(char) * get_size_max(t) );
    // free(t);

    fread(res, sizeof(char), get_curr_node(t), f);
    fclose(f);

    return res;
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
    unsigned int l_idx, r_idx;

    printf("*---------------------------*\n");
    printf("| index |        ISI        |\n");
    printf("|---------------------------|\n");

    printf("| 00000 |       %05u       | <-- Root\n", get_root_node(t));
    printf("| 00004 |       %05u       | <-- Curr\n", get_curr_node(t));
    printf("| 00008 |       %05u       | <-- SizeMax\n", get_size_max(t));
    printf("| 00012 |       %u Byte      | <-- Address Size\n", get_address_size(t));
    
    // printf("|-------|---|-------|-------|\n");

    for (unsigned int i = HEADER; i < get_curr_node(t); i += get_block_size(t))
    {
        printf("| %05u |", i);
        printf(" %c |", get_value_node(t, i));

        l_idx = get_left_node(t, i);
        if (l_idx != NULL_INDEX)
        {
            printf(" %05u |", l_idx);
        }
        else
        {
            printf("       |");
        }

        r_idx = get_right_node(t, i);
        if (r_idx != NULL_INDEX)
        {
            printf(" %05u |", r_idx);
        }
        else
        {
            printf("       |");
        }

        printf(" %s\n", get_mark_node(t, i) ? "EOW" : " " );
    }
}

void print_tree(char *t, unsigned int idx, unsigned int deep)
{
    printf("%c", get_value_node(t, idx));

    unsigned int l_idx = get_left_node(t, idx);
    if (l_idx != NULL_INDEX)
    {
        deep++;
        printf("-");
        print_tree(t, l_idx, deep);
        deep--;
    }

    unsigned int r_idx = get_right_node(t, idx);
    if (r_idx != NULL_INDEX)
    {
        printf("\n");
        // printf("%d", deep);
        if (deep != 0)
            for (unsigned int i = 0; i < (deep); i++)
            {
                printf("  ");
            }

        printf("|\n");

        if (deep != 0)
            for (unsigned int i = 0; i < deep; i++)
            {
                printf("  ");
            }
        print_tree(t, r_idx, deep);
    }
}

char* convert_tree(char *t, unsigned int addres_size)
{
    char *conv_tree = malloc(sizeof(char) * HEADER );

    // memcpy(&conv_tree, &t, HEADER);

    set_address_size(conv_tree, addres_size);
    set_root_node(conv_tree, (get_block_size(conv_tree) * (get_root_node(t) - HEADER) / get_block_size(t)) + HEADER );
    set_curr_node(conv_tree, (get_block_size(conv_tree) * (get_curr_node(t) - HEADER) / get_block_size(t)) + HEADER );
    set_size_max(conv_tree, (unsigned int) pow(256, addres_size) - 1 );

    char *res = realloc(conv_tree, sizeof(char) * get_size_max(conv_tree) );

    for (unsigned int i = HEADER; i < get_curr_node(t); i += get_block_size(t))
    {
        int new_index = (get_block_size(conv_tree) * (i - HEADER) / get_block_size(t)) + HEADER;
        int new_left  = get_left_node(t,i)==0 ? 0 : (get_block_size(conv_tree) * (get_left_node(t, i) - HEADER) / get_block_size(t)) + HEADER;
        int new_right = get_right_node(t,i)==0 ? 0 : (get_block_size(conv_tree) * (get_right_node(t, i) - HEADER) / get_block_size(t)) + HEADER;
        
        set_value_node(res, new_index, get_value_node(t, i));
        set_left_node(res, new_index, new_left);
        set_right_node(res, new_index, new_right);
        set_mark_node(res, new_index, get_mark_node(t,i));
    }

    return res;
}

unsigned int get_line_number(char *filename){
    FILE *fileptr;
    int count_lines = 0;
    char chr;
 
    fileptr = fopen(filename, "r");
   //extract character from file and store in chr
    chr = getc(fileptr);
    while (chr != EOF)
    {
        //Count whenever new line is encountered
        if (chr == '\n')
        {
            count_lines = count_lines + 1;
        }
        //take next character from file.
        chr = getc(fileptr);
    }
    fclose(fileptr); 

    return count_lines;
}

typedef char *string;

char* String_Lower(char *kata) 
{
	int i = 0; 
	while (kata[i] != '\0') 
	{
    	if (kata[i] >= 'A' && kata[i] <= 'Z') {
        	kata[i] = kata[i] + 32;
    	}
      	i++;
	}
    return kata;
}

void insert_tree_by_file(char* t, char* filename){
    unsigned int num_of_line = get_line_number(filename);

    unsigned int i;
    string array[num_of_line];
    int cur_size = 0;

    FILE *my;
    my = fopen(filename,"r");
    for(i = 0; i < num_of_line; i++){
        fscanf(my, "%*s%n", &cur_size);
        array[i] = malloc((cur_size+1)*sizeof(*array[i]));
    }
    fclose(my);

    my = fopen(filename,"r");
    for(i = 0; i < num_of_line; i++){
        fscanf(my, "%s", array[i]);
        // printf("%s\n", String_Lower(array[i]));
        insert_tree(t, String_Lower(array[i]));
    }
    fclose(my);

    // and when done:
    for(i = 0; i < num_of_line; i++){
            free(array[i]);
    }

}





// =============================== MAIN PROGRAM ====================================

int main()
{

    // =================== PLAY GROUND ============================




    // int LEFT_FLAG = 1;                          // 1
    // int RIGHT_FLAG = LEFT_FLAG + addrSize;      // 5
    // int END_FLAG = RIGHT_FLAG + addrSize;       // 9
    // int BLOCK_SIZE = END_FLAG + addrSize;       // 10

    unsigned int deep = 0;

    char *t;

    // ==================== TREE LOADER =============================
    // t = load_tree(t, "pohonFull1Byte");
    // t = load_tree(t, "pohonFull2Byte");
    // t = load_tree(t, "pohonFull3Byte");
    // t = load_tree(t, "pohonFull4Byte");

    t = load_tree(t, "kamusKataIndonesia");
    

    // ===================== TREE CONVERTER =========================
    // int new_address_size = 2;
    // t = convert_tree(t, new_address_size);


    // ===================== TREE CONSTRUCTOR ========================
    // unsigned int addrSize = 3;
    // t = create_tree(addrSize);
    
    // ===================== INPUT TREE BY FILE =======================
    // insert_tree_by_file(t, "kata-dasar-indonesia.txt");
    // insert_tree_by_file(t, "kata_a.txt");

    // insert_tree_by_file(t, "kata_a_new.txt");

    // ===================== INPUT TREE MANUALY ========================
    // insert_tree(t, "domba");
    // insert_tree(t, "dombaf");
    // insert_tree(t, "dombak");

    // insert_tree(t, "domba");
    // insert_tree(t, "cicak");
    // insert_tree(t, "candaan");
    // insert_tree(t, "candi");
    // insert_tree(t, "bebek");
    // insert_tree(t, "dambaan");
    // insert_tree(t, "celah");

    // insert_tree(t, "satu");
    // insert_tree(t, "dua");
    // insert_tree(t, "tiga");
    // insert_tree(t, "empat");
    // insert_tree(t, "lima");
    // insert_tree(t, "enam");
    // insert_tree(t, "tujuh");
    // insert_tree(t, "delapan");
    // insert_tree(t, "sembilan");
    // insert_tree(t, "sepuluh");
    // insert_tree(t, "payung");


    // ====================== PRINTING TREE ====================
    // ------- print by memory -------------
    
    // print_memory_tree(t);
    // printf("\n");
    
    // ------- print by sturcture -------------
    
    // print_tree(t, get_root_node(t), deep);
    // printf("\n");

    // ------- print by information -------------
  
    printf("*---------------------------*\n");
    printf("|   Dictionary Information  |\n");
    printf("*---------------------------*\n");

    printf(" Root         |> %u\n", get_root_node(t));
    printf(" Curr         |> %u\n", get_curr_node(t));
    printf(" SizeMax      |> %u\n", get_size_max(t));
    printf(" Address Size |> %u Byte\n", get_address_size(t));

    // char * kata = "domba";
    // printf("Kata %s kondisi %d \n", kata, search_tree(t, kata));
    
    // char ayam[] = "Aku Seorang Kapiten Yeay\n";
    // printf("%s", strlwr(ayam));
    // char stop;
    // scanf("%c", stop);

    // ======================= SAVING TREEE ========================
    // save_tree(t, "kamusKataIndonesia");

    return 0;
}