//
// Created by 奉眠 on 2021/6/13.
//

#ifndef BOOKSTORE_MANAGER_BOOK_H
#define BOOKSTORE_MANAGER_BOOK_H

class book {
public:
    char *get_n() { return name; }

    char *get_a() { return author; }

    char *get_s() { return sort; }

    int *get_c() { return &count; }

    double *get_sp() { return &sell_price; }

    double *get_ip() { return &in_price; }

private:
    char name[20] = "name";
    char author[20] = "author";
    char sort[20];
    double sell_price = 100.78;
    double in_price = 10;
    int count;
};

struct bookshelf {
    bool conbar = false;
    book B;
    bookshelf *pre;
    bookshelf *next;
};

struct sort_bar {
    sort_bar *up;
    sort_bar *down;
    char sort[20];
    bookshelf *right;
};

void set_shelf(sort_bar *&H);

void create_sort(sort_bar *&H, book B);

sort_bar *locate_sort(sort_bar *&H, char sort[20]);

bookshelf *locate_book(sort_bar *&H, char name[20]);

bookshelf *locate_book(sort_bar *&H, bookshelf *&t, char name[20], char author[20], int temp);

int book_info(sort_bar *&H);

double in_shelf(sort_bar *&H, book B);

double in_books(sort_bar *&H);

double out_shelf(sort_bar *&H, char name[20], bool f);

int fix_book(sort_bar *&H);

void show_shelf(sort_bar *&H);

int show_sort(sort_bar *&H);

int show_author(sort_bar *&H);

void read_shelf(sort_bar *&H);

void save_shelf(sort_bar *&H);

void menu();
#endif //BOOKSTORE_MANAGER_BOOK_H