//
//  Admin.cpp
//  基于清华大学的校园导游系统
//
//  Created by Dousir9 on 2020/2/28.
//  Copyright © 2020 🍓XJK. All rights reserved.
//

#include "Admin.hpp"

//信息修改
void Admin::Change(Graph &G) {
    int n_name, n_len, n_inf;//n:要修改的内容表示  n_name:修改名称返回值    n_len:修改长度返回值
    string newname, newinformation, NAME, NAME1, NAME2;
    string newlen;
    cout << NEXT_BLANK; printf("    请输入您要修改的内容:\n\n");
    cout << NEXT_BLANK; cout << "        ①  路径长度" << '\n' << '\n';
    cout << NEXT_BLANK; cout << "        ②  景点名称" << '\n' << '\n';
    cout << NEXT_BLANK; cout << "        ③  景点名称" << '\n' << '\n';
    cout << "\n                                                       ";
    string ch;
    cin >> ch;
    if (ch == "1") { //路径长度修改
        printf("\n                                       请分别输入两个景点和修改后的路径长度\n");
        cout << NEXT_BLANK; printf("  (格式: 景点 景点 长度):");
        cout << "\n\n                                                  ";
        cin >> NAME1 >> NAME2 >> newlen;
        if (!CHECK_INT(newlen)) {
            cout << NEXT_BLANK; printf("        你的输入有误\n\n");
            return;
        }
        int len = TO_INT(newlen);
        n_len = G.changelength(NAME1, NAME2, len);
        if (n_len == 1) {
            cout << '\n' << "                                        " << NAME1 << "与" << NAME2 << "之间的路径长度已修改为" << newlen << '\n';
        } else if (n_len == -1) {
            cout << NEXT_BLANK; cout << "    " << NAME1 << "和" << NAME2 << "都不存在" << '\n';
        } else if (n_len == -2) {
            cout << NEXT_BLANK; cout << "        " << NAME1 << "不存在" << '\n';
        } else if (n_len == -3){
            cout << NEXT_BLANK; cout << "        " << NAME2 << "不存在" << '\n';
        } else {
            cout << NEXT_BLANK; cout << "  " << NAME1 << "与" << NAME2 << "之间不存在路径" << '\n';
        }
    } else if(ch == "2") { //景点名称修改
        printf("\n                                     请输入要修改的景点名称以及修改后的名称\n");
        cout << "\n                                                   ";
        cin >> NAME >> newname;
        n_name = G.changename(NAME,newname);
        if (n_name==1) {
            cout << NEXT_BLANK; cout << "     " << NAME << "已被修改为" << newname << '\n';
        } else {
            cout << NEXT_BLANK; cout << "        " << NAME << "不存在" << '\n';
        }
    } else if(ch == "3") { //景点信息修改
        cout << NEXT_BLANK; printf("   请输入要修改信息的景点:");
        cout << "\n\n                                                      ";
        cin >> NAME;
        cout << NEXT_BLANK; printf("     请输入修改后的信息:\n");
        cout << "\n\n   ";
        cin >> newinformation;
        n_inf = G.changeinfo(NAME,newinformation);
        if (n_inf == 1) {
            cout << NEXT_BLANK; cout << "      " << NAME << "的信息已更新" << '\n';
        } else {
            cout << NEXT_BLANK; cout << "        " << NAME << "不存在" << '\n';
        }
    } else {
        cout << NEXT_BLANK; printf("        你的输入有误\n\n");
    }
    cout << '\n';
}

//添加景点
void Admin::AddSight(Graph &G) {
    cout << NEXT_BLANK; printf("请输入您要添加的景点的名称:");
    string name;
    cin >> name;
    cout << NEXT_BLANK; printf("     请输入景点的介绍:");
    cout << "\n\n   ";
    string info;
    cin >> info;
    cout << NEXT_BLANK; printf(" 请输入景点相连的路径数量:");
    string str;
    cin >> str;
    if (!CHECK_INT(str)) {
        cout << NEXT_BLANK; printf("        你的输入有误\n\n");
        return;
    }
    vector<string> sights;
    vector<int> length;
    int n = TO_INT(str);
    string len;
    for (int i = 0; i < n; i++) {
        cout << "\n                                   请输入" << name << "第" << i + 1 << "条路径相连的景点与长度:";
        cin >> str >> len;
        if (!CHECK_INT(len)) {
            cout << NEXT_BLANK; printf("        你的输入有误\n\n");
            return;
        }
        sights.push_back(str);
        length.push_back(TO_INT(len));
    }
    
#ifdef debug
    clock_t s, e;
    s = clock();
#endif
    
    auto it = G.AddNode(name, info, sights, length);
    if (it.first == -1) {
        cout << NEXT_BLANK; cout << "        " << name << "已存在" << '\n';
    } else if (n != 0) {
        if (it.second.first.size() == 0) {
            cout << NEXT_BLANK; cout << name << "已添加,但所有路径添加失败" << '\n';
        } else {
            printf("\n                                成功添加的路径数量为:%d，添加成功的路径连接的景点如下:", (int) it.second.first.size());
            for (int i = 0; i < it.second.first.size(); i++) {
                cout << NEXT_BLANK; cout << "             " << it.second.first[i];
            }
            cout << '\n';
            if (it.second.second.size() != 0) {
                printf("\n                                添加失败的路径数量为:%d，添加失败的路径连接的景点如下:", (int) it.second.second.size());
                for (int i = 0; i < it.second.second.size(); i++) {
                    cout << NEXT_BLANK; cout << "             " << it.second.second[i];
                }
            }
        }
    } else {
        cout << NEXT_BLANK; cout << "        " << name << "已添加" << '\n';
    }
    cout << '\n';
    
#ifdef debug
    e = clock();
    di("添加景点")
    rt(s, e);
    cout << '\n';
#endif
}

//删除景点
void Admin::DeleteSight(Graph &G)//景点删除
{
    string NAME;
    int n_del;
    cout << NEXT_BLANK; printf("   请输入要删除景点的名称:\n");
    cout << "\n                                                      ";
    cin>>NAME;
    
#ifdef debug
    clock_t s, e;
    s = clock();
#endif
    
    n_del=G.G_delete(NAME);
    if (n_del == -1) {
        cout << NEXT_BLANK; cout << "    " << NAME << "不存在，删除失败" << '\n';
    } else {
        cout << NEXT_BLANK; cout << "        " << NAME << "已删除" << '\n';
    }
    cout << '\n';
    
#ifdef debug
    e = clock();
    di("删除景点")
    rt(s, e);
    cout << '\n';
#endif
}

void Admin::AddEdge(Graph &G) {
    string name1, name2, length;
    printf("\n                                     请输入路径相连的两个景点以及路径的长度\n");
    cout << NEXT_BLANK; printf("  (格式: 景点 景点 长度):");
    cout << "\n\n                                                  ";
    cin >> name1 >> name2 >> length;
    if (!CHECK_INT(length)) {
        cout << NEXT_BLANK; printf("       你的输入有误\n\n");
        return;
    }
    
#ifdef debug
    clock_t s, e;
    s = clock();
#endif
    
    int x = G.AddEdge(name1, name2, TO_INT(length));
    if (x == 1) {
        cout << "\n\n                                   " << name1 << "与" << name2 << "之间成功添加一条路径，长度为:" << length << '\n';
    } else if (x == -1) {
        cout << NEXT_BLANK; cout << "    " << name1 << "和" << name2 << "都不存在" << '\n';
    } else if (x == -2) {
        cout << NEXT_BLANK; cout << "        " << name1 << "不存在" << '\n';
    } else if (x == -3) {
        cout << NEXT_BLANK; cout << "        " << name2 << "不存在" << '\n';
    } else {
        cout << "\n                                     " << name1 << "与" << name2 << "之间存在路径，无法重复添加" << '\n';
    }
    cout << '\n';
    
#ifdef debug
    e = clock();
    di("添加路径")
    rt(s, e);
    cout << '\n';
#endif
}

//删除路径
void Admin::DeleteEdge(Graph &G)
{
    string s1, s2;
    printf("\n                                         请输入要删除的路径连接的两个景点:\n");
    cout << NEXT_BLANK; printf("     (格式: 景点 景点):");
    cout << "\n\n                                                    ";
    cin >> s1 >> s2;
    
#ifdef debug
    clock_t s, e;
    s = clock();
#endif
    
    int x = G.E_delete(s1, s2);
    if (x == 1) {
        cout << NEXT_BLANK; cout << "  " << s1 << "与" << s2 << "之间的路径已删除" << '\n';
    } else if (x == -1) {
        cout << NEXT_BLANK; cout << "    " << s1 << "和" << s2 << "都不存在" << '\n';
    } else if (x == -2) {
        cout << NEXT_BLANK; cout << "        " << s1 << "不存在" << '\n';
    } else if (x == -3) {
        cout << NEXT_BLANK; cout << "        " << s2 << "不存在" << '\n';
    } else {
        cout << NEXT_BLANK; cout << " " << s1 << "与" << s2 << "之间没有路径相连" << '\n';
    }
    cout << '\n';
    
#ifdef debug
    e = clock();
    di("删除路径")
    rt(s, e);
    cout << '\n';
#endif
}

//信息检查
void Admin::CheckInfo(Graph &G) {
    G.Puts();
}
