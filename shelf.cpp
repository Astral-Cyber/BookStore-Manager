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
    H->right = nullptr;
    H->down = nullptr;
}


void create_sort(sort_bar *&H, book B) {//创建分类
    strcpy(H->sort, B.sort);
    H->right = new bookshelf;
    H->right->conbar = true;
    H->right->B = B;
    H->right->next = nullptr;
    H->right->pre = nullptr;
    H->down = nullptr;
}

sort_bar *locate_sort(sort_bar *&H, char sort[20]) {//定位分类
    sort_bar *p = H;
    while (p != nullptr) {
        if (!strcmp(p->sort, sort))
            return p;
        p = p->down;
    }
    return nullptr;
}

void locate_book(sort_bar *&H, bookshelf *b[], char name[20], char author[20], int temp) {//按书名作者定位
    for (int i = 1; i <= temp; ++i) {
        if (!strcmp(name, b[i]->B.name) && !strcmp(author, b[i]->B.author))//找到目标书籍
            b[0] = b[i];
    }
}

bookshelf *locate_book(sort_bar *&H, char name[20]) {//按书名定位
    bookshelf *b;
    bookshelf *b1[10];
    int temp = 0;
    sort_bar *p = H;
    while (p != nullptr) {
        b = p->right;//进入该分类
        while (b != nullptr) {
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
        return nullptr;
    } else {
        if (temp == 1) {
            return b1[1];
        } else {
            cout << "该书存在不同作者，请输入作者名称查找" << endl;
            char author[20];
            locate_book(H, b1, name, author, temp);
            return b1[0];
        }
    }
}

void book_info(sort_bar *&H, char *name) {
    bookshelf *p = locate_book(H, name);
    cout << setw(15) << "| Book Sort" << setw(25) << "| Book Name" << setw(20) << "| Author" << "| Count" << endl;
    cout << "|--------------|------------------------|-------------------|------" << endl;
    cout << "| " << setw(13) << p->B.sort;
    cout << "| " << setw(23) << p->B.name << "| " << setw(18) << p->B.author << "| " << p->B.count<<endl;
    cout << "|--------------|------------------------|-------------------|------" << endl;
}

int in_shelf(sort_bar *&H, book B) {//书籍入书架
    sort_bar *a = locate_sort(H, B.sort);//定位分类
    bookshelf *b;
    if (a) {//该分类存在的情况下
        b = a->right;
        while (b->next != nullptr) {
            if (!strcmp(B.name, b->B.name) && !strcmp(B.author, b->B.author)) {//处理存在相同书籍
                b->B.count++;
                return 0;
            }
            b = b->next;
        }
        b->next = new bookshelf;
        b->next->pre = b;
        b = b->next;
        b->B = B;
        b->next = nullptr;
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
    return 1;
}


int out_shelf(sort_bar *&H, char name[20]) {//书籍出书架
    bookshelf *p = locate_book(H, name);//获取该书籍地址
    if (!p) {
        return 0;
    }
    sort_bar *r = locate_sort(H, p->B.sort);
    if (!r) {
        cout << "无此书或此书不再该分类中，请重新输入" << endl;
        return 1;
    }
    p->B.count--;
    if ((p->B.count == 0) && (p->conbar)) {//该书为分类中第一本
        if (p->next == nullptr) {//后面无书
            if (r == H)
                H = H->down;
            else {
                if (r->down == nullptr)
                    r->up->down = nullptr;
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
        if (p->next == nullptr) {//后面无书
            p->pre->next = nullptr;
            delete p;
        } else {//后面还有书
            p->pre->next = p->next;
            p->next->pre = p->pre;
            delete p;
        }
    }
    return 2;
}

void fix_book(sort_bar *&H, char name[20]) {
    bookshelf *p = locate_book(H, name);
    if (!p) {
        return;
    }
    bookshelf q;
    char option = 'a';
    cout << "请输入要修改的属性：";
    while (option != '*') {
        if (option == 'a')
            cin >> option;
        switch (option) {
            case 'S':
                cout << "请输入要修改后的分类：";
                q.B = p->B;
                cin >> q.B.sort;
                out_shelf(H, name);
                in_shelf(H, q.B);
                cout << "修改完成，输入其他属性继续或输入'*'退出";
                break;
            case 'N':
                cout << "请输入要修改后的书名：";
                cin >> p->B.name;
                cout << "修改完成，输入其他属性继续或输入'*'退出";
                break;
            case 'C':
                cout << "请输入要修改后的数量：";
                cin >> p->B.count;
                cout << "修改完成，输入其他属性继续或输入'*'退出";
                break;
            case 'A':
                cout << "请输入要修改后的作者：";
                cin >> p->B.author;
                cout << "修改完成，输入其他属性继续或输入'*'退出";
                break;
            default:
                cout << "输入错误，请输入例如S(分类),N(名称),C(数量),A(作者)等对应信息首字母(输入'*'退出)";
                break;
        }
        cin >> option;
    }
}

void show_shelf(sort_bar *&H) {//显示全部书架，图形化
    bookshelf *b;
    sort_bar *p = H;
    cout << setiosflags(ios::left);
    cout << setw(15) << "| Book Sort" << setw(25) << "| Book Name" << setw(20) << "| Author" << "| Count" << endl;
    while (p != nullptr) {
        cout << "|--------------|------------------------|-------------------|------" << endl;
        cout << "| " << setw(13) << p->sort;
        b = p->right;
        while (b != nullptr) {
            cout << "| " << setw(23) << b->B.name << "| " << setw(18) << b->B.author << "| " << b->B.count;
            cout << endl;
            if (b->next != nullptr) {
                cout << "|              |------------------------|-------------------|------" << endl;
                cout << setw(15) << "|";
            }
            b = b->next;
        }
        p = p->down;
    }
    cout << "|--------------|------------------------|-------------------|------" << endl;
}

void show_sort(sort_bar *&H, char sort[20]) {//按分类显示书架，图形化
    sort_bar *p = locate_sort(H, sort);
    if (!p) {
        cout << "无此分类，请重新输入" << endl;
        return;
    }
    bookshelf *b;
    b = p->right;
    cout << setiosflags(ios::left);
    cout << setw(15) << "| Book Sort" << setw(25) << "| Book Name" << setw(20) << "| Author" << "| Count" << endl;
    cout << "|--------------|------------------------|-------------------|------" << endl;
    cout << "| " << setw(13) << p->sort;
    while (b != nullptr) {
        cout << "| " << setw(23) << b->B.name << "| " << setw(18) << b->B.author << "| " << b->B.count;
        cout << endl;
        if (b->next != nullptr) {
            cout << "|              |------------------------|-------------------|------" << endl;
            cout << setw(15) << "|";
        }
        b = b->next;
    }
    cout << "|--------------|------------------------|-------------------|------" << endl;
}

void show_author(sort_bar *&H, char author[20]) {
    bookshelf *b1[100];
    bookshelf *b;
    int temp = 0;
    sort_bar *p = H;
    while (p != nullptr) {
        b = p->right;//进入该分类
        while (b != nullptr) {
            if (!strcmp(author, b->B.author)) {
                temp++;
                b1[temp] = b;
            }
            b = b->next;
        }
        p = p->down;
    }
    if (temp == 0) {
        cout << "书架中无此作者书籍，请重新输入" << endl;
        return;
    }
    cout << setw(15) << "| Author" << setw(25) << "| Book Name" << "| Count" << endl;
    cout << "|--------------|------------------------|------" << endl;
    cout << "| " << setw(13) << author;
    for (int i = 1; i <= temp; ++i) {
        cout << "| " << setw(23) << b1[i]->B.name << "| " << b1[i]->B.count;
        cout << endl;
        if (i < temp) {
            cout << "|              |------------------------|------" << endl;
            cout << setw(15) << "|";
        }
    }
    cout << "|--------------|------------------------|------" << endl;
}