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
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <queue>
#include <cstring>
#include <ctime>
#include <cstdio>

#define debug
#define di(s) cout << "-----------" << s << "-----------" << '\n';
#define rt(s, e) cout << "Running time is: " << static_cast<double>(e - s) / CLOCKS_PER_SEC * 1000 << "ms" << '\n' << '\n';//输出运行时间为毫秒

using namespace std;

const string FILE_ADDRESS = "/Users/xumingfei/Desktop/git/Campus-navigation/基于清华大学的校园导游系统/SQL/"; //数据库地址
const string FILE_TYPE = ".txt"; //文件类型
const string GRAPH_INFO_FILE_NAME = FILE_ADDRESS + "graph" + FILE_TYPE;

const string ADMIN_PASSWORD = "123456";

//清空缓存区
void MY_FLUSH();
//按任意键返回
void MY_PAUSE();

#endif /* Global_hpp */
