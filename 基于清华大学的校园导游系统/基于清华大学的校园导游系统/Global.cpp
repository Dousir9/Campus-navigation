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
    cout <<endl<< "                                              按任意键返回..." << endl;
    getchar();
}
