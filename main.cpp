#include <iostream>
#include "book.h"

using namespace std;

int main() {
    sort_bar *Head;
    char q[20];
    set_shelf(Head);
    book a;
    for (int i = 0; i < 12; ++i) {
        //cout << "书名";
        cin >> a.name;
        //cout << "类别";
        cin >> a.sort;
        //cout << "数量";
        cin >> a.count;
        in_shelf(Head, a);
    }
    show_shelf(Head);//显示书架
    cin >> q;
    show_sort(Head, q);
    cin >> q;
    cout << locate_book(Head, q);//测试查找功能
    for (int i = 0; i < 12; ++i) {
        cin >> q;
        out_shelf(Head, q);
        show_shelf(Head);
    }
    return 0;
}