//
//  Global.cpp
//  基于清华大学的校园导游系统
//
//  Created by Dousir9 on 2020/2/28.
//  Copyright © 2020 🍓XJK. All rights reserved.
//

#include "Global.hpp"

//清空缓存区
void MY_FLUSH() {
    char ch;
    while(~(ch = getchar()) && ch != '\n');
}
//按任意键返回
void MY_PAUSE() {
    MY_FLUSH();
    cout <<endl<< "                                                 按任意键返回..." << endl;
    getchar();
}

//MacOS区分Windows的清屏函数
void CLEAR() {
    system("clear");
}

//MacOS区分Windows的 40000微秒 = 40毫秒 的休眠函数
void SLEEP() {
    usleep(40000);
}

//MacOS区分Windows的 1秒 休眠函数
void SMALL_SLEEP() {
    usleep(1000000);
}

//MacOS区分Windows的 1.5秒 休眠函数
void BIG_SLEEP() {
    usleep(1500000);
}

//检查是否全为整形数据
int CHECK_INT(const string str) {
    int len = (int) str.size();
    for (int i = 0; i < len; i++) {
        if (!(str[i] >= '0' && str[i] <= '9'))
            return 0;
    }
    return 1;
}

//字符串转化为整数
int TO_INT(const string str) {
    int cnt = 0, len = (int) str.size();
    for (int i = len - 1, k = 1; i >= 0; i--) {
        cnt += (str[i] - '0') * k;
        k *= 10;
    }
    return cnt;
}
