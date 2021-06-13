//
// Created by 奉眠 on 2021/6/13.
//

#ifndef BOOKSTORE_MANAGER_BOOK_H
#define BOOKSTORE_MANAGER_BOOK_H


class book {
public:
    char name[20];
    char author[20];
    char sort[20];
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

bookshelf *locate_book(sort_bar *&H,bookshelf *&t, char name[20],char author[20]);

int in_shelf(sort_bar *&H, book B);

int out_shelf(sort_bar *&H, char name[20]);

void show_shelf(sort_bar *&H);

void show_sort(sort_bar *&H, char sort[20]);

#endif //BOOKSTORE_MANAGER_BOOK_H
