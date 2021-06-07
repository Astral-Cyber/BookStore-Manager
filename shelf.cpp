#include <iostream>
#include <cstring>

using namespace std;

class book {
public:
    char name[20];
    char sort[20];
};

struct bookshelf {
    book B;
    bookshelf *next;
    bookshelf *bottom;
};

struct sort_bar {
    sort_bar *down;
    char sort[20];
    bookshelf *right;
};


int set_shelf(sort_bar *&H){
    H = new sort_bar;
    H->right = NULL;
    H->down = NULL;
}

sort_bar *locate_sort(book B, sort_bar *&H) {
    sort_bar *p = H;
    /*while (p->down != NULL) {
        if (!strcmp(p->sort, B.sort))
            return p;
        p = p->down;
    }*/
    return p;
}

void create_sort(sort_bar *&H, book B,int f) {
    if (f)
        H=new sort_bar;
    strcpy(H->sort, B.sort);
    H->right = new bookshelf;
    H->right->B = B;
    H->right->next = NULL;
    H->down = NULL;
}

int in_shelf(book B, sort_bar *&H) {
    sort_bar *a = locate_sort(B, H);
    bookshelf *b;
    if (0) {//该分类存在的情况下
        sort_bar *p = a;
        b = p->right;
        while (b->next != NULL) {
            b = b->next;
        }
        b->next = new bookshelf;
        b = b->next;
        b->B = B;
        b->next = NULL;
    } else//该分类不存在
    if (a==H)
        create_sort(a, B,0);
    else
        create_sort(a->down,B,1);
}


int out_shelf() {

}

int show_shelf(sort_bar *&H) {//可以实现两种模式按分类显示书架和显示全部书架
    bookshelf *b;
    cout << H->sort << endl;
    b = H->right;
    cout << b->B.name;
}

int locate_book() {//按书名和编号定位

}

int main() {
    sort_bar *Head;
    set_shelf(Head);
    book a;
    cin >> a.name;
    cin >> a.sort;
    cout << Head << endl;
    in_shelf(a, Head);
    show_shelf(Head);
    return 0;
}