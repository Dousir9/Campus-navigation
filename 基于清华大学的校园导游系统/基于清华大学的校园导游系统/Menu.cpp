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
    CLEAR();
    cout << HEAD;
}

//输出菜单底部
void Menu::ShowMenuBottom() {
    cout << BLANK << BOT << '\n' << '\n';
    cout << "                                                       ";
}
//输出错误信息
void Menu::ShowError() {
    CLEAR();
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n                                         ");
    printf("     无效的输入，请重新输入\n");
    BIG_SLEEP();
}

//接收指令，只接收第一个字母
char Menu::Input() {
    string ch;
    cin >> ch;
    MY_FLUSH();
    if (ch.size() > 1) {
        return -1;
    }
    return ch[0];
}

//主菜单运行
void Menu::MenuRun(Graph &G, Trie &T) {
    ShowMenuHead();
    ShowMenuInfo();
    ShowMenuBottom();
    char ch = Input();
    static TouristMenu tourist_menu;
    static AdminMenu admin_menu;
    switch (ch) {
        case '1': //游客入口
            tourist_menu.MenuRun(G, T);
            MenuRun(G, T);
            break;
        case '2': //管理员入口
            if (admin_menu.Login())
                admin_menu.MenuRun(G);
            MenuRun(G, T);
            break;
        case '3': //退出系统
            exit(0);
        default: //应对异常输入
            ShowError();
            MenuRun(G, T);
    }
}

//游客菜单运行
void TouristMenu::MenuRun(const Graph &G, Trie &T) {
    ShowMenuHead();
    ShowMenuInfo();
    ShowMenuBottom();
    char ch = Input();
    static Tourist tourist;
    switch (ch) {
        case '1': //查看地图
            ShowMenuHead();
            tourist.ShowMap(G);
            MY_PAUSE();
            MenuRun(G, T);
            break;
        case '2': //游览路线推荐
            ShowMenuHead();
            tourist.Recommend(G);
            MY_PAUSE();
            MenuRun(G, T);
            break;
        case '3': //搜索提示
            ShowMenuHead();
            tourist.SearchTip(T);
            MY_PAUSE();
            MenuRun(G, T);
            break;
        case '4': //热门景点
            ShowMenuHead();
            tourist.HotSights(G, T);
            MY_PAUSE();
            MenuRun(G, T);
            break;
        case '5': //热门搜索
            ShowMenuHead();
            tourist.HotSearch(T);
            MY_PAUSE();
            MenuRun(G, T);
            break;
        case '6': //多关键词搜索
            ShowMenuHead();
            tourist.MultiKeywordSearch(G, T);
            MY_PAUSE();
            MenuRun(G, T);
            break;
        case '7': //景点间最短路径
            ShowMenuHead();
            tourist.MinLength(G);
            MY_PAUSE();
            MenuRun(G, T);
            break;
        case '8': //返回主菜单
            T.SaveTrie();
            return ;
            break;
        case '9': //退出系统
            T.SaveTrie();
            exit(0);
        default: //应对异常输入
            ShowError();
            MenuRun(G, T);
    }
}

//管理员菜单运行
void AdminMenu::MenuRun(Graph &G) {
    ShowMenuHead();
    ShowMenuInfo();
    ShowMenuBottom();
    char ch = Input();
    static Admin admin;
    switch (ch) {
        case '1': //修改景点信息
            ShowMenuHead();
            admin.Change(G);
            MY_PAUSE();
            MenuRun(G);
            break;
        case '2': //添加景点
            ShowMenuHead();
            admin.AddSight(G);
            MY_PAUSE();
            MenuRun(G);
            break;
        case '3': //删除景点
            ShowMenuHead();
            admin.DeleteSight(G);
            MY_PAUSE();
            MenuRun(G);
            break;
        case '4': //添加路径
            ShowMenuHead();
            admin.AddEdge(G);
            MY_PAUSE();
            MenuRun(G);
            break;
        case '5': //删除路径
            ShowMenuHead();
            admin.DeleteEdge(G);
            MY_PAUSE();
            MenuRun(G);
            break;
        case '6': //信息检查
            ShowMenuHead();
            admin.CheckInfo(G);
            MY_PAUSE();
            MenuRun(G);
            break;
        case '7': //返回主菜单
            G.SaveGraph();
            return ;
            break;
        case '8': //退出系统
            G.SaveGraph();
            exit(0);
        default: //应对异常输入
            ShowError();
            MenuRun(G);
    }
}

//管理员登录
const bool AdminMenu::Login() const {
    cout << "\n                                            请输入管理员密码:";
    string password;
    cin >> password;
    getchar();
    if (password == admin_password) {
        printf("\n\n                                            密码正确，正在登录中...\n");
        SMALL_SLEEP();
        return true;
    } else {
        printf("\n\n                                          密码错误，正在返回主界面...\n");
        SMALL_SLEEP();
        return false;
    }
}

//输出菜单信息 (主菜单)
void Menu::ShowMenuInfo() {
    cout << BLANK << TOP; SLEEP();
    cout << BLANK << "║" << RIGHT_BLANK << "║" << '\n'; SLEEP();
    cout << BLANK << "║" << RIGHT_BLANK << "║" << '\n'; SLEEP();
    cout << BLANK << "║" << RIGHT_BLANK << "║" << '\n'; SLEEP();
    cout << BLANK << "║" << RIGHT_BLANK << "║" << '\n'; SLEEP();
    cout << BLANK << "║" << LEFT_BLANK << "①  游客入口       " << SMALL_BLANK << "║" << '\n'; SLEEP();
    cout << BLANK << "║" << RIGHT_BLANK << "║" << '\n'; SLEEP();
    cout << BLANK << "║" << RIGHT_BLANK << "║" << '\n'; SLEEP();
    cout << BLANK << "║" << RIGHT_BLANK << "║" << '\n'; SLEEP();
    cout << BLANK << "║" << RIGHT_BLANK << "║" << '\n'; SLEEP();
    cout << BLANK << "║" << LEFT_BLANK << "②  管理员入口     " << SMALL_BLANK << "║" << '\n'; SLEEP();
    cout << BLANK << "║" << RIGHT_BLANK << "║" << '\n'; SLEEP();
    cout << BLANK << "║" << RIGHT_BLANK << "║" << '\n'; SLEEP();
    cout << BLANK << "║" << RIGHT_BLANK << "║" << '\n'; SLEEP();
    cout << BLANK << "║" << RIGHT_BLANK << "║" << '\n'; SLEEP();
    cout << BLANK << "║" << LEFT_BLANK << "③  退出系统       " << SMALL_BLANK << "║" << '\n'; SLEEP();
    cout << BLANK << "║" << RIGHT_BLANK << "║" << '\n'; SLEEP();
    cout << BLANK << "║" << RIGHT_BLANK << "║" << '\n'; SLEEP();
    cout << BLANK << "║" << RIGHT_BLANK << "║" << '\n'; SLEEP();
    cout << BLANK << "║" << RIGHT_BLANK << "║" << '\n'; SLEEP();
}

//输出菜单信息 (游客菜单)
void TouristMenu::ShowMenuInfo() {
    cout << BLANK << TOP; SLEEP();
    cout << BLANK << "║" << RIGHT_BLANK << "║" << '\n'; SLEEP();
    cout << BLANK << "║" << LEFT_BLANK << "①  查看地图       " << SMALL_BLANK << "║" << '\n'; SLEEP();
    cout << BLANK << "║" << RIGHT_BLANK << "║" << '\n'; SLEEP();
    cout << BLANK << "║" << LEFT_BLANK << "②  游览路线推荐   " << SMALL_BLANK << "║" << '\n'; SLEEP();
    cout << BLANK << "║" << RIGHT_BLANK << "║" << '\n'; SLEEP();
    cout << BLANK << "║" << LEFT_BLANK << "③  搜索提示       " << SMALL_BLANK << "║" << '\n'; SLEEP();
    cout << BLANK << "║" << RIGHT_BLANK << "║" << '\n'; SLEEP();
    cout << BLANK << "║" << LEFT_BLANK << "④  热门景点       " << SMALL_BLANK << "║" << '\n'; SLEEP();
    cout << BLANK << "║" << RIGHT_BLANK << "║" << '\n'; SLEEP();
    cout << BLANK << "║" << LEFT_BLANK << "⑤  热门搜索       " << SMALL_BLANK << "║" << '\n'; SLEEP();
    cout << BLANK << "║" << RIGHT_BLANK << "║" << '\n'; SLEEP();
    cout << BLANK << "║" << LEFT_BLANK << "⑥  多关键词搜索   " << SMALL_BLANK << "║" << '\n'; SLEEP();
    cout << BLANK << "║" << RIGHT_BLANK << "║" << '\n'; SLEEP();
    cout << BLANK << "║" << LEFT_BLANK << "⑦  景点间最短路径 " << SMALL_BLANK << "║" << '\n'; SLEEP();
    cout << BLANK << "║" << RIGHT_BLANK << "║" << '\n'; SLEEP();
    cout << BLANK << "║" << LEFT_BLANK << "⑧  返回主菜单     " << SMALL_BLANK << "║" << '\n'; SLEEP();
    cout << BLANK << "║" << RIGHT_BLANK << "║" << '\n'; SLEEP();
    cout << BLANK << "║" << LEFT_BLANK << "⑨  退出系统       " << SMALL_BLANK << "║" << '\n'; SLEEP();
    cout << BLANK << "║" << RIGHT_BLANK << "║" << '\n'; SLEEP();
}

//输出菜单信息 (管理员菜单)
void AdminMenu::ShowMenuInfo() {
    cout << BLANK << TOP; SLEEP();
    cout << BLANK << "║" << RIGHT_BLANK << "║" << '\n'; SLEEP();
    cout << BLANK << "║" << LEFT_BLANK << "①  修改景点信息   " << SMALL_BLANK << "║" << '\n'; SLEEP();
    cout << BLANK << "║" << RIGHT_BLANK << "║" << '\n'; SLEEP();
    cout << BLANK << "║" << LEFT_BLANK << "②  添加景点       " << SMALL_BLANK << "║" << '\n'; SLEEP();
    cout << BLANK << "║" << RIGHT_BLANK << "║" << '\n'; SLEEP();
    cout << BLANK << "║" << LEFT_BLANK << "③  删除景点       " << SMALL_BLANK << "║" << '\n'; SLEEP();
    cout << BLANK << "║" << RIGHT_BLANK << "║" << '\n'; SLEEP();
    cout << BLANK << "║" << LEFT_BLANK << "④  添加路径       " << SMALL_BLANK << "║" << '\n'; SLEEP();
    cout << BLANK << "║" << RIGHT_BLANK << "║" << '\n'; SLEEP();
    cout << BLANK << "║" << LEFT_BLANK << "⑤  删除路径       " << SMALL_BLANK << "║" << '\n'; SLEEP();
    cout << BLANK << "║" << RIGHT_BLANK << "║" << '\n'; SLEEP();
    cout << BLANK << "║" << LEFT_BLANK << "⑥  信息检查       " << SMALL_BLANK << "║" << '\n'; SLEEP();
    cout << BLANK << "║" << RIGHT_BLANK << "║" << '\n'; SLEEP();
    cout << BLANK << "║" << LEFT_BLANK << "⑦  返回主菜单     " << SMALL_BLANK << "║" << '\n'; SLEEP();
    cout << BLANK << "║" << RIGHT_BLANK << "║" << '\n'; SLEEP();
    cout << BLANK << "║" << LEFT_BLANK << "⑧  退出系统       " << SMALL_BLANK << "║" << '\n'; SLEEP();
    cout << BLANK << "║" << RIGHT_BLANK << "║" << '\n'; SLEEP();
}
