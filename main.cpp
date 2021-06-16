#include <iostream>
#include "book.h"

using namespace std;

int main() {
    sort_bar *Head;
    double income = 0;
    extern double cost;
    set_shelf(Head);//初始化书架
    read_shelf(Head);//读取书架
    /*show_shelf(Head);//显示书架
    show_author(Head);
    show_sort(Head);
    fix_book(Head);
    show_shelf(Head);
    char name[20];
    for (int i = 0; i < 5; ++i) {
        cin >> name;
        out_shelf(Head, name, true);
        show_shelf(Head);
    }*/
    int option = 1;
    while (option != 0) {
        menu();
        cin >> option;
        switch (option) {
            case 1: {//显示书架
                int a = 1;
                while (a != 0) {
                    cout << "请选择书架显示模式 1）完全显示模式 2）作者模式 3）分类模式 0) 返回上级菜单" << endl;
                    cin >> a;
                    if (a == 1)
                        show_shelf(Head);
                    else {
                        if (a == 2)
                            show_author(Head);
                        else {
                            if (a == 3)
                                show_sort(Head);
                            else {
                                if (a == 0)
                                    cout << "正在返回上级菜单" << endl;
                                else
                                    cout << "输入错误，请重新输入。" << endl;
                            }
                        }
                    }
                }
                break;
            }
            case 2: {//出售
                int a = 1;
                while (a != 0) {
                    cout << "1）出售 0) 返回上级菜单" << endl;
                    cin >> a;
                    if (a == 1) {
                        char name[20];
                        cout << "请输入出售的书籍名称：";
                        cin >> name;
                        double money = out_shelf(Head, name, true);
                        if (money) {
                            income += money;
                            cout << "出售成功。" << endl;
                        }
                    } else {
                        if (a == 0)
                            cout << "正在返回上级菜单" << endl;
                        else
                            cout << "输入错误，请重新输入。" << endl;
                    }
                }
                break;
            }
            case 3: {//进货
                cost += in_books(Head);
                cout << "入库成功。" << endl;
                break;
            }
            case 4: {//查找书籍
                int a = 1;
                while (a != 0) {
                    cout << "1）查找 0) 返回上级菜单" << endl;
                    cin >> a;
                    if (a == 1) {
                        book_info(Head);
                    } else {
                        if (a == 0) {
                            cout << "正在返回上级菜单" << endl;
                        } else
                            cout << "输入错误，请重新输入。" << endl;
                    }
                }
                break;
            }
            case 5: {//修改书籍信息
                int a = 1;
                while (a != 0) {
                    cout << "1）修改或删除 0) 返回上级菜单" << endl;
                    cin >> a;
                    if (a == 1) {
                        fix_book(Head);
                    } else if (a == 0) {
                        cout << "正在返回上级菜单" << endl;
                    } else {
                        cout << "输入错误，请重新输入。" << endl;
                    }
                }
                break;
            }
            case 6:{//显示利润、成本、收入
                cout<<"从启动系统到当前收入为："<<income<<endl;
                cout<<"从启动系统到当前成本为："<<cost<<endl;
                cout<<"从启动系统到当前利润为："<<income-cost<<endl;
                break;
            }
            default: {//menu
                menu();
                break;
            }
        }
    }
    save_shelf(Head);//保存书架
    cout<<"本次关闭前收入为："<<income<<endl;
    cout<<"本次关闭前成本为："<<cost<<endl;
    cout<<"本次关闭前利润为："<<income-cost<<endl;
    cout<<"感谢您的使用。";
    return 0;
}