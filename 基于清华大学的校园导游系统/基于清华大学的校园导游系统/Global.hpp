//
//  Global.hpp
//  基于清华大学的校园导游系统
//
//  Created by Dousir9 on 2020/2/28.
//  Copyright © 2020 🍓XJK. All rights reserved.
//

#ifndef Global_hpp
#define Global_hpp

#include <iostream>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <map>
#include <iomanip>
#include <unistd.h>

//#define debug
#define di(s) cout << "                                          -----------" << s << '\n';
#define rt(s, e) cout << "\n                                            Running time is: " << static_cast<double>(e - s) / CLOCKS_PER_SEC * 1000 << "ms" << '\n' << '\n';//输出运行时间为毫秒

using namespace std;

//数据库：
const string FILE_ADDRESS = "/Users/xumingfei/Desktop/git/Campus-navigation/基于清华大学的校园导游系统/SQL/"; //数据库地址
const string FILE_TYPE = ".txt"; //文件类型
#ifdef debug
    const string GRAPH_INFO_FILE_NAME = FILE_ADDRESS + "data" + FILE_TYPE; //图信息
    const string SIGHT_INFO_FILE_NAME = FILE_ADDRESS + "testinformation" + FILE_TYPE; //景点信息
#else
    const string GRAPH_INFO_FILE_NAME = FILE_ADDRESS + "graph" + FILE_TYPE; //图信息
    const string SIGHT_INFO_FILE_NAME = FILE_ADDRESS + "information" + FILE_TYPE; //景点信息
#endif
const string SEARCH_INFO_FILE_NAME = FILE_ADDRESS + "search" + FILE_TYPE; //搜索信息
const string TAG_INFO_FILE_NAME = FILE_ADDRESS + "tag" + FILE_TYPE; //标记数组

//管理员密码
const string ADMIN_PASSWORD = "123456";

//最大值：
const int INF = 0x3f3f3f3f;
//汉字大小：MacOS为3，Windows为2
const int CN_SIZE = 3;

//界面优化：
const string HEAD = "\n                 ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★  青岛科技大学校园导游系统  ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★\n\n";
const string BLANK = "                   ";
const string LEFT_BLANK = "                             ";
const string RIGHT_BLANK = "                                                                        ";
const string SMALL_BLANK = "                         ";
const string NEXT_BLANK = "\n\n                                          ";
const string TOP = "╔════════════════════════════════════════════════════════════════════════╗\n";
const string BOT = "╚════════════════════════════════════════════════════════════════════════╝\n";

//清空缓存区
void MY_FLUSH();

//按任意键返回
void MY_PAUSE();

//MacOS区分Windows的清屏函数
void CLEAR();

//MacOS区分Windows的 40000微秒 = 40毫秒 的休眠函数
void SLEEP();

//MacOS区分Windows的 1秒 休眠函数
void SMALL_SLEEP();

//MacOS区分Windows的 1.5秒 休眠函数
void BIG_SLEEP();

//检查是否全为整形数据
int CHECK_INT(const string str);

//字符串转化为整数
int TO_INT(const string str);

#endif /* Global_hpp */
