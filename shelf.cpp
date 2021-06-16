#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>
#include "book.h"

using namespace std;

sort_bar *rs;//类的尾指针

bool F = true;

double cost = 0;

ostream &operator<<(ostream &output, book &B) {//重载流操作符<<
    cout << "| " << setw(23) << B.get_n() << "| " << setw(18) << B.get_a() << "| " << setw(8)
         << *B.get_sp() << "| " << *B.get_c();
    return output;
}

ifstream &operator>>(ifstream &in, book &B) {//重载文件读取的>>
    in >> B.get_n() >> B.get_a() >> B.get_s() >> *B.get_c() >> *B.get_ip() >> *B.get_sp();
    cost += *B.get_ip() * *B.get_c();
    return in;
}

istream &operator>>(istream &input, book &B) {//重载流操作的>>
    cout << "请输入进货的书籍名称：";
    cin >> B.get_n();
    cout << "请输入进货的书籍作者：";
    cin >> B.get_a();
    cout << "请输入进货的书籍分类：";
    cin >> B.get_s();
    cout << "请输入进货的书籍数量：";
    cin >> *B.get_c();
    cout << "请输入进货的书籍售价：";
    cin >> *B.get_sp();
    cout << "请输入进货的书籍进价：";
    cin >> *B.get_ip();
    return input;
}

void set_shelf(sort_bar *&H) {//初始化书架
    H = new sort_bar;
    rs = H;
    H->right = nullptr;
    H->down = nullptr;
}


void create_sort(sort_bar *&H, book B) {//创建分类
    strcpy(H->sort, B.get_s());
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
        if (!strcmp(name, b[i]->B.get_n()) && !strcmp(author, b[i]->B.get_a()))//找到目标书籍
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
            if (!strcmp(name, b->B.get_n()))//判断该分类中有无此书
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

int book_info(sort_bar *&H) {//获取书籍信息
    char name[20];
    cout << "请输入要显示信息的书籍名称：";
    cin >> name;
    bookshelf *p = locate_book(H, name);
    if (!p) {
        return 0;
    }
    cout << setiosflags(ios::left);
    cout << setw(15) << "| Book Sort" << setw(25) << "| Book Name" << setw(20) << "| Author" << "| Count" << endl;
    cout << "|--------------|------------------------|-------------------|------" << endl;
    cout << "| " << setw(13) << p->B.get_s();
    cout << "| " << setw(23) << p->B.get_n() << "| " << setw(18) << p->B.get_a() << "| " << *p->B.get_c() << endl;
    cout << "|--------------|------------------------|-------------------|------" << endl;
    return 1;
}

double in_shelf(sort_bar *&H, book B) {//书籍入书架
    sort_bar *a = locate_sort(H, B.get_s());//定位分类
    bookshelf *b;
    if (a) {//该分类存在的情况下
        b = a->right;
        while (b != nullptr) {
            if (!strcmp(B.get_n(), b->B.get_n()) && !strcmp(B.get_a(), b->B.get_a())) {//处理存在相同书籍
                (*b->B.get_c()) += *B.get_c();
                return (*B.get_ip()) * (*B.get_c());
            }
            if (b->next != nullptr)
                b = b->next;
            else
                break;
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
    return (*B.get_ip()) * (*B.get_c());
}

double in_books(sort_bar *&H) {//进货
    book B;
    cin >> B;
    in_shelf(H, B);
    return (*B.get_ip()) * (*B.get_c());
}

double out_shelf(sort_bar *&H, char name[20], bool f) {//书籍出书架 f为真时出售模式，为假时为该书全部移出书架
    bookshelf *p = locate_book(H, name);//获取该书籍地址
    double money;
    if (!p) {
        return 0;
    }
    sort_bar *r = locate_sort(H, p->B.get_s());
    if (!r) {
        cout << "无此书或此书不再该分类中，请重新输入" << endl;
        return 0;
    }
    if (f) {
        cout << "请输入出售数量：";
        int n;
        cin >> n;
        (*p->B.get_c()) -= n;
        money = *p->B.get_sp();
        if ((*p->B.get_c()) < 0) {
            cout << "库存不足" << endl;
            return 0;
        }
    } else {
        *p->B.get_c() = 0;
        money = *p->B.get_sp();
    }
    if ((*p->B.get_c() == 0) && (p->conbar)) {//该书为分类中第一本
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
    if ((*p->B.get_c() == 0) && !(p->conbar)) {//该书为分类中非第一本
        if (p->next == nullptr) {//后面无书
            p->pre->next = nullptr;
            delete p;
        } else {//后面还有书
            p->pre->next = p->next;
            p->next->pre = p->pre;
            delete p;
        }
    }
    return money;
}

int fix_book(sort_bar *&H) {//修改书籍信息
    char name[20];
    cout << "请输入要修改的书籍名称：";
    cin >> name;
    bookshelf *p = locate_book(H, name);
    if (!p) {
        return 0;
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
                cin >> q.B.get_s();
                out_shelf(H, name, false);
                in_shelf(H, q.B);
                cout << "修改完成，输入其他属性继续或输入'*'退出";
                break;
            case 'N':
                cout << "请输入要修改后的书名：";
                cin >> p->B.get_n();
                cout << "修改完成，输入其他属性继续或输入'*'退出";
                break;
            case 'C':
                cout << "请输入要修改后的数量：";
                cin >> *p->B.get_c();
                cout << "修改完成，输入其他属性继续或输入'*'退出";
                break;
            case 'A':
                cout << "请输入要修改后的作者：";
                cin >> p->B.get_a();
                cout << "修改完成，输入其他属性继续或输入'*'退出";
                break;
            case 'I':
                cout << "请输入要修改后的进价：";
                cin >> *p->B.get_ip();
                cout << "修改完成，输入其他属性继续或输入'*'退出";
                break;
            case 'D':
                out_shelf(H, name, false);
                break;
            case 'P':
                cout << "请输入要修改后的售价：";
                cin >> *p->B.get_sp();
                cout << "修改完成，输入其他属性继续或输入'*'退出";
                break;
            default:
                cout << "输入错误，请输入S(分类),N(名称),C(数量),A(作者),D(删除),P(售价)等对应信息首字母(输入'*'退出)";
                break;
        }
        cin >> option;
    }
    return 1;
}

void show_shelf(sort_bar *&H) {//显示全部书架，图形化
    bookshelf *b;
    sort_bar *p = H;
    cout << setiosflags(ios::left);
    cout << setw(15) << "| Book Sort" << setw(25) << "| Book Name" << setw(20) << "| Author" << setw(10) << "| Price"
         << "| Count" << endl;
    while (p != nullptr) {
        cout << "|--------------|------------------------|-------------------|---------|------" << endl;
        cout << "| " << setw(13) << p->sort;
        b = p->right;
        while (b != nullptr) {
            cout << b->B;
            cout << endl;
            if (b->next != nullptr) {
                cout << "|              |------------------------|-------------------|---------|------" << endl;
                cout << setw(15) << "|";
            }
            b = b->next;
        }
        p = p->down;
    }
    cout << "|--------------|------------------------|-------------------|---------|------" << endl;
}

int show_sort(sort_bar *&H) {//按分类显示书架，图形化
    char sort[20];
    cout << "请输入要显示的分类：";
    cin >> sort;
    sort_bar *p = locate_sort(H, sort);
    if (!p) {
        cout << "无此分类，请重新输入" << endl;
        return 0;
    }
    bookshelf *b;
    b = p->right;
    cout << setiosflags(ios::left);
    cout << setw(15) << "| Book Sort" << setw(25) << "| Book Name" << setw(20) << "| Author" << setw(10) << "| Price"
         << "| Count" << endl;
    cout << "|--------------|------------------------|-------------------|---------|------" << endl;
    cout << "| " << setw(13) << p->sort;
    while (b != nullptr) {
        cout << "| " << setw(23) << b->B.get_n() << "| " << setw(18) << b->B.get_a() << "| " << setw(8)
             << *b->B.get_sp() << "| " << *b->B.get_c();
        cout << endl;
        if (b->next != nullptr) {
            cout << "|              |------------------------|-------------------|---------|------" << endl;
            cout << setw(15) << "|";
        }
        b = b->next;
    }
    cout << "|--------------|------------------------|-------------------|---------|------" << endl;
    return 1;
}

int show_author(sort_bar *&H) {//按作者显示书籍
    char author[20];
    cout << "请输入要显示的作者：";
    cin >> author;
    bookshelf *b1[100];
    bookshelf *b;
    int temp = 0;
    sort_bar *p = H;
    while (p != nullptr) {
        b = p->right;//进入该分类
        while (b != nullptr) {
            if (!strcmp(author, b->B.get_a())) {
                temp++;
                b1[temp] = b;
            }
            b = b->next;
        }
        p = p->down;
    }
    if (temp == 0) {
        cout << "书架中无此作者书籍，请重新输入" << endl;
        return 0;
    }
    cout << setiosflags(ios::left);
    cout << setw(15) << "| Author" << setw(25) << "| Book Name" << setw(10) << "| Price" << "| Count" << endl;
    cout << "|--------------|------------------------|---------|------" << endl;
    cout << "| " << setw(13) << author;
    for (int i = 1; i <= temp; ++i) {
        cout << "| " << setw(23) << b1[i]->B.get_n() << "| " << setw(8) << *b1[i]->B.get_sp() << "| "
             << *b1[i]->B.get_c();
        cout << endl;
        if (i < temp) {
            cout << "|              |------------------------|---------|------" << endl;
            cout << setw(15) << "|";
        }
    }
    cout << "|--------------|------------------------|---------|------" << endl;
    return 1;
}


void save_shelf(sort_bar *&H) {//保存书架
    fstream out("../bookstore.txt");
    bookshelf *b;
    sort_bar *p = H;
    while (p != nullptr) {
        b = p->right;
        while (b != nullptr) {
            out << b->B.get_n() << " " << b->B.get_a() << " " << b->B.get_s() << " " << *b->B.get_c() << " "
                << *b->B.get_ip() << " " << *b->B.get_sp() << endl;
            b = b->next;
        }
        p = p->down;
    }
    cout << "已保存书架。";
}

void read_shelf(sort_bar *&H) {//读取书架内容
    book B;
    ifstream in("../bookstore.txt");
    while (!in.eof()) {
        in >> B;
        if (in.fail())//防止重复读去最后一行两次
            break;
        in_shelf(H, B);
    }
    cout << "书架读取完成。" << endl;
    cout << "欢迎使用书籍管理系统v1.0" << endl;
    cout<<"该项目已上传至Github(https://github.com/Astral-cyber/BookStore-Manager)"<<endl;
}

void menu() {
    cout << "----------菜单---------" << endl;
    cout << setiosflags(ios::left);
    cout << setw(20) << "1）书架" << "2）出售" << endl;
    cout << setw(20) << "3）进货" << "4）查找" << endl;
    cout << setw(20) << "5）修改" << "6）资金" << endl;
    cout<<setw(20)<<"0）退出系统"<<endl;
}
