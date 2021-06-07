#include <iostream>
#include <cstring>

using namespace std;

class book {
public:
    char name[20];
    char sort[20];
};

struct bookshelf {
    bool conbar= false;
    book B;
    bookshelf *pre;
    bookshelf *next;
    bookshelf *bottom;
};

struct sort_bar {
    sort_bar *up;
    sort_bar *down;
    char sort[20];
    bookshelf *right;
};

sort_bar *rs;//类的尾指针

int F = 1;

//bookshelf *rb;//书籍的尾指针

int set_shelf(sort_bar *&H) {
    H = new sort_bar;
    rs = H;
    H->right = NULL;
    H->down = NULL;
}

sort_bar *locate_sort(sort_bar *&H, book B) {
    sort_bar *p = H;
    while (p != NULL) {
        if (!strcmp(p->sort, B.sort))
            return p;
        p = p->down;
    }
    return 0;
}

void create_sort(sort_bar *&H, book B) {
    strcpy(H->sort, B.sort);
    H->right = new bookshelf;
    H->right->conbar= true;
    H->right->B = B;
    H->right->next = NULL;
    H->down = NULL;
}

int same_book(bookshelf *S,book B){//处理同样的书籍

}

int in_shelf(book B, sort_bar *&H) {
    sort_bar *a = locate_sort(H, B);
    bookshelf *b;
    if (a) {//该分类存在的情况下
        b = a->right;
        while (b->next != NULL) {
            b = b->next;
        }
        b->next = new bookshelf;
        b->next->pre=b;
        b = b->next;
        b->B = B;
        b->next = NULL;
    } else { //该分类不存在
        if ((rs == H) && F) {
            create_sort(rs, B);
            //cout << rs << " " << F << endl;
            F = 0;
        } else {
            rs->down = new sort_bar;
            rs->down->up=rs;
            rs = rs->down;
            //cout << rs << " " << F << endl;
            create_sort(rs, B);
        }
    }
}


int out_shelf(book B) {

}

int show_shelf(sort_bar *&H) {//显示全部书架
    bookshelf *b;
    sort_bar *p = H;
    while (p != NULL) {
        cout << p->sort;
        b = p->right;
        while (b != NULL) {
            cout << b->B.name;
            b = b->next;
        }
        p = p->down;
        cout <<"over"<< endl;
    }
}

int show_sort(sort_bar, char sort[20]) {//可以实现两种模式按分类显示书架和

}

int locate_book() {//按书名和编号定位

}

int main() {
    sort_bar *Head;
    set_shelf(Head);
    book a;
    for (int i = 0; i < 4; ++i) {
        cout << "书名";
        cin >> a.name;
        cout << "类别";
        cin >> a.sort;
        in_shelf(a, Head);
    }
    sort_bar *b=rs;
    show_shelf(Head);
    return 0;
}