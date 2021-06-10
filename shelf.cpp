#include <iostream>
#include <cstring>

using namespace std;

class book {
public:
    char name[20];
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

sort_bar *rs;//类的尾指针

bool F = true;

int set_shelf(sort_bar *&H) {//初始化书架
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

bookshelf *locate_book(sort_bar *&H, char name[20]) {//按书名定位
    bookshelf *b;
    sort_bar *p = H;
    while (p != NULL) {
        b = p->right;//进入该分类
        while (b != NULL) {
            if (!strcmp(name, b->B.name))//判断该分类中有无此书
                return b;
            b = b->next;
        }
        p = p->down;
    }
    cout << "书架中无此书，请重新输入";
    return 0;
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
        cout << "无此书或此书不再该分类中";
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

int show_shelf(sort_bar *&H) {//显示全部书架，图形化待完善
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
        cout << "over" << endl;
    }
}

int show_sort(sort_bar *&H, char sort[20]) {//按分类显示书架，图形化待完善
    sort_bar *p = locate_sort(H, sort);
}


int main() {
    sort_bar *Head;
    set_shelf(Head);
    book a;
    for (int i = 0; i < 12; ++i) {
        cout << "书名";
        cin >> a.name;
        cout << "类别";
        cin >> a.sort;
        cout << "数量";
        cin >> a.count;
        in_shelf(Head, a);
    }
    show_shelf(Head);//显示书架
    char q[20];
    cin >> q;
    cout << locate_book(Head, q);//测试查找功能
    for (int i = 0; i < 12; ++i) {
        cin >> q;
        out_shelf(Head, q);
        show_shelf(Head);
    }
    return 0;
}