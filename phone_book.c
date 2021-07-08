
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

const char *DB = "directory.db";

struct entry0 
{
    char name[20];
    char phone[20];
    struct entry0 *next;
};

typedef struct entry0 entry;

/* Command handlers */
void add(char *,char *);
int search(FILE *,char *);
void list(FILE *);
int delete(FILE *,char *);

/* Utility functions  */
FILE * open_db_file(); // Opens the database file. Prints error and quits if it's not available

void print_usage(char *, char *); // Prints usage

entry *load_entries(FILE *); // Load all entries from the database file. Returns pointer to first entry

entry *create_entry_node(char *, char *); // Create a new entry node. Has to be freed by user

void free_entries(entry *); // TBD Given the first node of a linked list of entries, will free all the nodes

void write_all_entries(entry *); // Given the first node of a linked list of entries, will delete the database file on the disk and save the given entries into the file 


int main(int argc, char *argv[]) 
{
    if(argc == 1) 
    {
        print_usage("Insufficient arguments", argv[0]);
        exit(1);
    } 

    if(strcmp(argv[1], "add") == 0) 
    {   /* Handle add */
        if(argc != 4) 
        {
            print_usage("Improper arguments for add", argv[0]);
            exit(1);
        }
    
        char *name = argv[2];
        char *phone = argv[3];
        add(name, phone);
        exit(0);
    }
    else if(strcmp(argv[1], "list") == 0) 
    {  /* Handle list */
        if(argc != 2) 
        {
            print_usage("Improper arguments for list", argv[0]);
            exit(1);
        }
    
        FILE *fp = open_db_file();
        list(fp);
        fclose(fp);
        exit(0);
    } 
    else if(strcmp(argv[1], "search") == 0) 
    {  /* Handle search */
        if(argc != 3)
        {
            print_usage("Improper arguments for search",argv[0]);
            exit(1);
        }

        FILE *fp = open_db_file();
        char *name = argv[2];
        if(search(fp, name) == 0) 
        {
            printf("no match\n");
            fclose(fp);
            exit(1);
        }
        fclose(fp);
        exit(0);
    } 
    else if(strcmp(argv[1], "delete") == 0) 
    {  /* Handle delete */
        if(argc != 3) 
        {
            print_usage("Improper arguments for delete", argv[0]);
            exit(1);
        }
        FILE *fp = open_db_file();
        char *name = argv[2];
        if(delete(fp, name) == 0) 
        {
            printf("no match\n");
            fclose(fp);
            exit(1);
        }
        fclose(fp);
        exit(0);
    } 
    else
    {
        print_usage("Invalid command", argv[0]);
        exit(1);
    }
}

FILE *open_db_file() 
{
    FILE *fp=fopen(DB, "r");
    if(fp == NULL) 
    {
        perror("Couldn't open database file");
        exit(1);
    }
    return fp;
}
