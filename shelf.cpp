#include <iostream>
#include <cstring>
#include <iomanip>
#include "book.h"

using namespace std;

sort_bar *rs;//类的尾指针

bool F = true;

void set_shelf(sort_bar *&H) {//初始化书架
    H = new sort_bar;
    rs = H;
    H->right = NULL;
    H->down = NULL;
}


void create_sort(sort_bar *&H, book B) {//创建分类
    strcpy(H->sort, B.sort);
    H->right = new bookshelf;
    H->right->conbar = true;
    H->right->B = B;
    H->right->next = NULL;
    H->right->pre = NULL;
    H->down = NULL;
}

sort_bar *locate_sort(sort_bar *&H, char sort[20]) {//定位分类
    sort_bar *p = H;
    while (p != NULL) {
        if (!strcmp(p->sort, sort))
            return p;
        p = p->down;
    }
    return 0;
}

void locate_book(sort_bar *&H, bookshelf *b[], char name[20], char author[20]) {//按书名作者定位
    for (int i = 1; i < 10; ++i) {
        if (!strcmp(name, b[i]->B.name) && !strcmp(author, b[i]->B.author))//找到目标书籍
            b[0] = b[i];
    }
}

bookshelf *locate_book(sort_bar *&H, char name[20]) {//按书名定位
    bookshelf *b;
    bookshelf *b1[10];
    int temp = 0;
    sort_bar *p = H;
    while (p != NULL) {
        b = p->right;//进入该分类
        while (b != NULL) {
            if (!strcmp(name, b->B.name))//判断该分类中有无此书
            {
                temp++;
                b1[temp] = b;
            }
            b = b->next;
        }
        p = p->down;
    }
    if (temp == 0) {
        cout << "书架中无此书，请重新输入" << endl;
        return 0;
    } else {
        if (temp == 1) {
            return b1[1];
        } else {
            cout << "该书存在不同作者，请输入作者名称查找" << endl;
            char author[20];
            locate_book(H, b1, name, author);
            return b1[0];
        }
    }
}

/*int same_book(bookshelf *S, book B) {//处理同样的书籍

}*/

int in_shelf(sort_bar *&H, book B) {//书籍入书架
    sort_bar *a = locate_sort(H, B.sort);
    bookshelf *b;
    if (a) {//该分类存在的情况下
        b = a->right;
        while (b->next != NULL) {
            if (!strcmp(B.name, b->B.name)) {//处理存在同名书籍
                b->B.count++;
                /*same_book(b, B);*/
                return 0;
            }
            b = b->next;
        }
        b->next = new bookshelf;
        b->next->pre = b;
        b = b->next;
        b->B = B;
        b->next = NULL;
        /*if (b->B.count > 1) {//处理一次性进货多本同类书;
            same_book(b,B);
        }*/
    } else { //该分类不存在
        if ((rs == H) && F) {
            create_sort(rs, B);
            F = false;
        } else {
            rs->down = new sort_bar;
            rs->down->up = rs;
            rs = rs->down;
            create_sort(rs, B);
        }
    }
}


int out_shelf(sort_bar *&H, char name[20]) {//书籍出书架
    bookshelf *p = locate_book(H, name);//获取该书籍地址
    if (!p) {
        return 0;
    }
    bookshelf *q;//前一本书
    sort_bar *r = locate_sort(H, p->B.sort);
    if (!r) {
        cout << "无此书或此书不再该分类中，请重新输入" << endl;
        return 0;
    }
    p->B.count--;
    if ((p->B.count == 0) && (p->conbar)) {//该书为分类中第一本
        if (p->next == NULL) {//后面无书
            if (r == H)
                H = H->down;
            else {
                if (r->down == NULL)
                    r->up->down = NULL;
                else {
                    r->up->down = r->down;
                    r->down->up = r->up;
                }
            }
            delete r;
            delete p;
        } else {//后面还有书
            r->right = p->next;
            p->next->conbar = true;
            delete p;
        }
    }
    if ((p->B.count == 0) && !(p->conbar)) {//该书为分类中非第一本
        if (p->next == NULL) {//后面无书
            p->pre->next = NULL;
            delete p;
        } else {//后面还有书
            p->pre->next = p->next;
            p->next->pre = p->pre;
            delete p;
        }
    }
}

void show_shelf(sort_bar *&H) {//显示全部书架，图形化待完善
    bookshelf *b;
    sort_bar *p = H;
    cout << "| Book Sort" << setw(15) << "| Book Name" << setw(20) << "| Count" << endl;
    while (p != NULL) {
        cout << "|--------------|-----------------------|------" << endl;
        cout << "| " << p->sort << setw(14);
        b = p->right;
        while (b != NULL) {
            cout << "| " << b->B.name << setw(21) << "| " << b->B.count;
            cout << endl;
            if (b->next != NULL) {
                cout << "|              |-----------------------|------" << endl;
                cout << "|" << setw(16);
            }
            b = b->next;
        }
        p = p->down;
    }
}

void show_sort(sort_bar *&H, char sort[20]) {//按分类显示书架，图形化待完善
    sort_bar *p = locate_sort(H, sort);
    bookshelf *b;
    b = p->right;
    cout << "| Book Sort" << setw(15) << "| Book Name" << setw(20) << "| Count" << endl;
    cout << "|--------------|-----------------------|------" << endl;
    cout << "| " << p->sort << setw(14);
    while (b != NULL) {
        cout << "| " << b->B.name << setw(21) << "| " << b->B.count;
        cout << endl;
        if (b->next != NULL) {
            cout << "|              |-----------------------|------" << endl;
            cout << "|" << setw(16);
        }
        b = b->next;
    }
    cout << "|--------------|-----------------------|------" << endl;
}