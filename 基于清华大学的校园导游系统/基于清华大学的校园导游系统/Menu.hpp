//
//  Menu.hpp
//  基于清华大学的校园导游系统
//
//  Created by Dousir9 on 2020/2/28.
//  Copyright © 2020 🍓XJK. All rights reserved.
//

#ifndef Menu_hpp
#define Menu_hpp

#include "Global.hpp"
#include "Tourist.hpp"
#include "Admin.hpp"
#include "Graph.hpp"

//（主）菜单类
class Menu {
 public:
    Menu();
    void ShowMenuHead(); //输出菜单头部
    void ShowMenuInfo(); //输出菜单内容
    void ShowMenuBottom(); //输出菜单底部
    void ShowError(); //输出异常信息
    void MenuRun(Graph &G); //运行菜单
    char Input(); //从键盘接收指令
};

//游客菜单类，继承菜单类
class TouristMenu : public Menu {
 public:
    void ShowMenuInfo(); //输出菜单内容
    void MenuRun(const Graph &G); //运行菜单
};

//管理员菜单类，继承菜单类
class AdminMenu : public Menu {
 public:
    void ShowMenuInfo(); //输出菜单内容
    void MenuRun(Graph &G); //运行菜单
    const bool Login() const; //管理员登录
 private:
    const string admin_password = ADMIN_PASSWORD;
};

#endif /* Menu_hpp */
