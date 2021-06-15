#include <iostream>
#include "book.h"

using namespace std;

int main() {
    sort_bar *Head;
    set_shelf(Head);//初始化书架
    read_shelf(Head);//读取书架
    show_shelf(Head);//显示书架
    show_author(Head);
    show_sort(Head);
    fix_book(Head);
    show_shelf(Head);
    char name[20];
    for (int i = 0; i < 5; ++i) {
        cin >> name;
        out_shelf(Head, name, true);
        show_shelf(Head);
    }

    /*int option = 1;
    while (option != 0) {
        cin >> option;
        switch (option) {
            case 1://出售
                char name[20];
                cout<<"请输入出售的书籍名称：";
                cin >> name;
                out_shelf(Head, name);
                break;
            case 2://进货
                book b;//属性输入待完成
                in_shelf(Head, b);
                break;
*//*            default://menu
                cout<<"菜单";//待完善*//*
        }
    }*/
    save_shelf(Head);//保存书架
/*    show_shelf(Head);
    cin >> q;
    show_sort(Head, q);//分类显示测试
    cin >> q;
    show_author(Head, q);//作者显示测试
    cin >> q;
    book_info(Head, q);//测试查找功能
    for (int i = 0; i < 12; ++i) {//测试删除
        cin >> q;
        out_shelf(Head, q);
        show_shelf(Head);
    }*/
    return 0;
}