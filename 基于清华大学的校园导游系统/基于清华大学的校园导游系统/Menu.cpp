//
//  Menu.cpp
//  基于清华大学的校园导游系统
//
//  Created by Dousir9 on 2020/2/28.
//  Copyright © 2020 🍓XJK. All rights reserved.
//

#include "Menu.hpp"

//默认构造函数(基类及其派生类)
Menu::Menu() {}

//输出菜单头部
void Menu::ShowMenuHead() {
    printf("\n菜单头部\n");
}

//输出菜单底部
void Menu::ShowMenuBottom() {
    printf("菜单底部\n\n");
}
//输出错误信息
void Menu::ShowError() {
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n                                         ");
    printf(" 无效的输入，请重新输入\n");
    //usleep(1500000);
    //system("clear");
}

//接收指令，只接收第一个字母
char Menu::Input() {
    char ch;
    ch = getchar();
    MY_FLUSH();
    return ch;
}

//输出菜单信息 (主菜单)
void Menu::ShowMenuInfo() {
    printf("1.游客入口\n");
    printf("2.管理员入口\n");
    printf("3.退出系统\n");
}

//主菜单运行
void Menu::MenuRun(Graph &G) {
    ShowMenuHead();
    ShowMenuInfo();
    ShowMenuBottom();
    char ch = Input();
    static TouristMenu tourist_menu;
    static AdminMenu admin_menu;
    switch (ch) {
        case '1': //游客入口
            tourist_menu.MenuRun(G);
            MenuRun(G);
            break;
        case '2': //管理员入口
            if (admin_menu.Login())
                admin_menu.MenuRun(G);
            MenuRun(G);
            break;
        case '3': //退出系统
            exit(0);
        default: //应对异常输入
            ShowError();
            MenuRun(G);
    }
}

//输出菜单信息 (游客菜单)
void TouristMenu::ShowMenuInfo() {
    printf("1.遍历地图\n");
    printf("2.游客功能2\n");
    printf("3.返回\n");
    printf("4.退出系统\n");
}

//游客菜单运行
void TouristMenu::MenuRun(const Graph &G) {
    ShowMenuHead();
    ShowMenuInfo();
    ShowMenuBottom();
    char ch = Input();
    static Tourist tourist;
    switch (ch) {
        case '1':
            //游客操作1
            tourist.Travel(G);
            MenuRun(G);
            break;
        case '2':
            //游客操作2
            
            MenuRun(G);
            break;
        case '3': //返回主菜单
            return ;
            break;
        case '4': //退出系统
            exit(0);
        default: //应对异常输入
            ShowError();
            MenuRun(G);
    }
}

//输出菜单信息 (管理员菜单)
void AdminMenu::ShowMenuInfo() {
    printf("1.管理员操作1\n");
    printf("2.管理员操作2\n");
    printf("3.返回\n");
    printf("4.退出系统\n");
}

//管理员菜单运行
void AdminMenu::MenuRun(Graph &G) {
    ShowMenuHead();
    ShowMenuInfo();
    ShowMenuBottom();
    char ch = Input();
    static Admin admin;
    switch (ch) {
        case '1':
            //system("clear");
            //管理员操作1
            MenuRun(G);
            break;
        case '2':
            //system("clear");
            //管理员操作2
            MenuRun(G);
            break;
        case '3': //返回主菜单
            return ;
            break;
        case '4': //退出系统
            exit(0);
        default: //应对异常输入
            ShowError();
            MenuRun(G);
    }
}

//管理员登录
const bool AdminMenu::Login() const {
    cout << "请输入管理员密码:";
    string password;
    cin >> password;
    getchar();
    if (password == admin_password) {
        printf("密码正确，正在登录中...\n");
        return true;
    } else {
        printf("密码错误，正在返回主界面...\n");
        return false;
    }
}
