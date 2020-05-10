//
//  RBTree.hpp
//  基于清华大学的校园导游系统
//
//  Created by Dousir9 on 2020/3/15.
//  Copyright © 2020 🍓XJK. All rights reserved.
//

#ifndef RBTree_hpp
#define RBTree_hpp

#include "Global.hpp"

template < class T1, class T2>
struct event {
    T1 first; //键
    T2 second; //值
    event() {}
    event(T1 a, T2 b) {
        first = a;
        second = b;
    }
    bool operator < (const event &other) const {
        return first < other.first;
    }
    bool operator > (const event &other) const {
        return first > other.first;
    }
    bool operator == (const event &other) const {
        return first == other.first;
    }
};

template < class T1, class T2>
struct Node {
    event < T1, T2 > key;
    int color; // 0代表黑结点，1代表红结点
    Node *son[2];
    Node *pre;
};

//红黑树
template < class T1, class T2 >
class RBTree {
 public:
    RBTree();
    
    /*
     对外接口：插入操作
     参数介绍：一个结点的键值对，T1是键，T2是值
     操作示例：
     RBTree<string, int> name; 创建红黑树
     name.Insert(event<string, int>("北京", 5)); 插入结点
     注意：插入是先用FindIndex查找一下红黑树中是否存在该结点(event中的first是否存在)
     */
    void Insert(const event < T1, T2 > key);
    
    
    /*
     对外接口：删除操作
     返回值介绍：删除成功返回1，失败返回-1
     参数介绍：一个结点的键T1
     操作示例：
     int x = name.Delete("青岛");
     */
    int Delete(const T1 first);
    
    
    /*
     对外接口：查找操作，用来修改值T2
     返回值介绍：二元组指针，值T2的指针，用来修改，第二元是bool型变量，若为true，则查找成功，若为false，查找失败T1
     参数介绍：一个结点的键T1
     操作示例：
     auto it = name.Find(str); 或 pair <int*, bool > *it = name.Find(str);
     if (it->second == true) { //如果找到
        *it->first = 100; //进行修改
     }
     */
    pair < T2*, bool >* Find(const T1 first) ;
    
    
    /*
     对外接口：查找键返回值
     返回值介绍：查找成功返回值，查找失败返回-1
     参数介绍：一个结点的键T1
     操作示例：
     int v = name.FindIndex("北京");
     */
    int FindIndex(const T1 first) const;
    
    
    /*
     对外接口 修改键：先删除在插入
     返回值介绍：修改成功返回值，不存在该键返回-1
     参数介绍：要修改结点的键T1，修改后的T1
     操作示例：
     int x = ModifyKey("济南", "北京"); //济南修改为北京
     */
    int ModifyKey(const T1 first1, const T1 first2);
    
    void Pre(); //对外接口: 先序遍历
    void In(); //对外接口: 中序遍历
    void Post(); //对外接口: 后序遍历
 private:
    Node < T1, T2 > *root; //树根
    pair < T2*, bool > *p; //用来修改的指针
    inline Node < T1, T2 > * NewNode(event < T1, T2 > key); //生成新结点
    inline void Rorate(Node < T1, T2 > * o, int d); //旋转，0代表左旋，1代表右旋
    void InsertNode(Node < T1, T2 > * &o, Node < T1, T2 > * &pre, const event < T1, T2 > key); //内部接口: 插入结点
    void Check(Node < T1, T2 > * &o); //插入情况3: 父节点为红色时不断向上调整
    int DeleteNode(Node < T1, T2 > * &o, const T1 first); //内部接口: 删除结点
    Node < T1, T2 > * GetMax(Node < T1, T2 > * o); //获取左子树的最大值作为真正删除点
    void TransferDeleteNode(Node < T1, T2 > * o); //转移待删除点的位置
    inline void TransferInfo(Node < T1, T2 > * &a, Node < T1, T2 > * &b); //待删除结点信息转移b->a
    void Case1(Node < T1, T2 >  *o); //删除情况1: 删除红色叶子结点
    void Case2(Node < T1, T2 >  *o, int c); //删除情况2: 只有左子树或右子树，本身一定是黑结点，左孩子或有孩子一定为红结点
    void Case3(Node < T1, T2 >  *o); //删除情况3: 删除黑色叶子结点
    void Case3_1(Node < T1, T2 >  *o, int c); //删除情况3.1: 兄弟结点为黑，远侄子结点存在且为红
    void Case3_2(Node < T1, T2 >  *o, int c); //删除情况3.2: 兄弟结点为黑，远侄子结点不符合条件，近侄子结点为红
    void Case3_3(Node < T1, T2 >  *o, int c); //删除情况3.3: 兄弟结点为黑，没有侄子结点，父节点为红
    void Case3_4(Node < T1, T2 >  *o); //删除情况3.4: 兄弟结点为黑，没有侄子结点，父节点为黑，不断向上调整
    void RemoveNode(Node < T1, T2 >  *o, int c); //删除结点
    pair < T2*, bool >* BinarySearch(Node < T1, T2 > * &o, const T1 first); //内部接口: 二分查找,返回指针，用于增删
    int BinarySearchIndex(const Node < T1, T2 > * o, const T1) const; //内部接口: 二分查找,返回对应下标
    void Pr(Node < T1 , T2 > * &root); //内部接口: 先序遍历
    void I(Node < T1 , T2 > * &root); //内部接口: 中序遍历
    void Po(Node < T1 , T2 > * &root); //内部接口: 后序遍历
};



//默认构造函数
template < class T1, class T2 >
RBTree < T1, T2 > :: RBTree() {
    root = NULL;
    T2 *t;
    p = new pair<T2*, bool>(t, false);
}

//生成新结点
template < class T1, class T2 >
inline Node < T1, T2 > * RBTree < T1, T2 > :: NewNode(event < T1, T2 > key) {
    Node < T1, T2 >  *p = new Node < T1, T2 > ;
    p->color = 1;
    p->key = key;
    p->son[0] = p->son[1] = NULL;
    p->pre = NULL;
    return p;
};

//对外接口: 插入操作
template < class T1, class T2 >
void RBTree < T1, T2 > :: Insert(event < T1, T2 > key) {
    if (root == NULL) { // 情况1: 插入的结点为根节点
        root = NewNode(key);
        root->color = 0;
    } else if (key < root->key) {
        InsertNode(root->son[0], root, key);
    } else {
        InsertNode(root->son[1], root, key);
    }
}

//旋转，0代表左旋，1代表右旋
template < class T1, class T2 >
inline void RBTree < T1, T2 > :: Rorate(Node < T1, T2 > * o, int d) {
    Node < T1, T2 >  *p = o->son[d ^ 1];
    o->son[d ^ 1] = p->son[d];
    if (p->son[d] != NULL)
        p->son[d]->pre = o;
    Node < T1, T2 >  *pr = o->pre;
    p->pre = pr;
    if (pr != NULL) {
        int d = pr->son[1] == o;
        pr->son[d] = p;
    }
    p->son[d] = o;
    o->pre = p;
    if (p->pre == NULL)
        root = p;
}

// 情况3: 父节点为红色时不断向上调整
template < class T1, class T2 >
void RBTree < T1, T2 > :: Check(Node < T1, T2 > * &o) {
    Node < T1, T2 > * &pre = o->pre; //注意，是引用
    if (pre == NULL) { //回退到根节点，将根节点由红变黑
        o->color = 0;
        return;
    } else if (pre->color == 0) { //父节点为黑，无需继续调整
        return;
    }
    int c1 = pre->son[0] == o; //c1为1则插入结点为左孩子，为0即为右孩子
    int c2 = pre->pre->son[0] == pre;
    if (pre->pre->son[c2] == NULL || pre->pre->son[c2]->color == 0) {// 情况3.1: 叔叔结点为不存在或为黑色
        if (c1 == c2) { //情况3.1.1: 插入结点、父节点、祖父节点三点共线
            swap(pre->pre->color, pre->pre->son[!c2]->color); //旋转前互换颜色
            Rorate(pre->pre, c2);
        } else { //情况3.1.2: 插入结点、父节点、祖父节点三点不共线
            Rorate(pre, c1);
            swap(pre->color, pre->son[!c2]->color); //旋转前互换颜色
            Rorate(pre, c2);
        }
    } else { //情况3.2: 叔叔结点为红色
        o->pre->color = o->pre->pre->son[c2]->color = 0; //将父节点和叔叔结点由红变黑
        o->pre->pre->color = 1; //祖父节点变红
        Check(pre->pre);
    }
}

//插入节点
template < class T1, class T2 >
void RBTree < T1, T2 > :: InsertNode(Node < T1, T2 > * &o, Node < T1, T2 > * &pre, const event < T1, T2 > key) {
    if (o == NULL) {
        o = NewNode(key);
        o->pre = pre;
        if (pre->color != 0) { //情况3: 父节点为红色
            Check(o);
        } else { //情况2: 父节点为黑色
            return;
        }
    } else if (key < o->key) {
        InsertNode(o->son[0], o, key);
    } else {
        InsertNode(o->son[1], o, key);
    }
}

//对外接口: 删除操作
template < class T1, class T2 >
int RBTree < T1, T2 > :: Delete(const T1 first) {
    if (root == NULL) {
        return -1;//树为空，删除失败
    } else if (root->key.first == first && root->son[0] == NULL && root->son[1] == NULL) { //根节点为最后一个结点且根节点是待删除结点
        delete root;
        root = NULL;
        return 1;
    } else {
        return DeleteNode(root, first);
    }
}

//删除转移
template < class T1, class T2 >
Node < T1, T2 > * RBTree < T1, T2 > :: GetMax(Node < T1, T2 > * o) {
    if (o->son[1] != NULL) {
        return GetMax(o->son[1]);
    } else {
        return o;
    }
}

//信息转移
template < class T1, class T2 >
inline void RBTree < T1, T2 > :: TransferInfo(Node < T1, T2 > * &a, Node < T1, T2 > * &b) {
    a->key = b->key;
}

//删除情况1: 删除红色叶子结点
template < class T1, class T2 >
void RBTree < T1, T2 > :: Case1(Node < T1, T2 >  *o) {
    o->pre->son[o->pre->son[1] == o] = NULL;
    delete o;
}

//删除情况2: 只有左子树或右子树，本身一定是黑结点，左孩子或有孩子一定为红结点
template < class T1, class T2 >
void RBTree < T1, T2 > :: Case2(Node < T1, T2 >  *o, int c) {
    o->son[c]->pre = o->pre;
    if (o->pre != NULL) {
        o->pre->son[o->pre->son[1] == o] = o->son[c];
    } else {
        root = o->son[c];
    }
    o->son[c]->color = 0;
    delete o;
}

//删除结点
template < class T1, class T2 >
void RBTree < T1, T2 > :: RemoveNode(Node < T1, T2 >  *o, int c) {
    Node < T1, T2 >  *p = o->son[!c];
    o->son[!c] = NULL;
    delete p;
}

//删除情况3.1: 兄弟结点为黑，远侄子结点存在且为红
template < class T1, class T2 >
void RBTree < T1, T2 > :: Case3_1(Node < T1, T2 >  *o, int c) {
    swap(o->color, o->son[c]->color); //父节点和兄弟结点互换颜色
    o->son[c]->son[c]->color = 0; //远侄子结点染成黑色
    Rorate(o, !c);
}

//删除情况3.2: 兄弟结点为黑，远侄子结点不符合条件，近侄子结点为红,转换为情况3.1
template < class T1, class T2 >
void RBTree < T1, T2 > :: Case3_2(Node < T1, T2 >  *o, int c) {
    swap(o->color, o->son[!c]->color); //兄弟结点和近侄子结点互换颜色
    Rorate(o, c);
}

//删除情况3.3: 兄弟结点为黑，没有侄子结点，父节点为红
template < class T1, class T2 >
void RBTree < T1, T2 > :: Case3_3(Node < T1, T2 >  *o, int c) {
    swap(o->color, o->son[c]->color); //兄弟结点与父节点互换颜色
}

//删除情况3.4: 兄弟结点为黑，没有侄子结点，父节点为黑，不断向上调整
template < class T1, class T2 >
void RBTree < T1, T2 > :: Case3_4(Node < T1, T2 >  *o) {
    if (o == root) { //调整到根，说明树的黑高度-1，停止调整
        return;
    }
    int c = o->pre->son[0] == o;
    Node < T1, T2 >  *bro = o->pre->son[c];
    if (bro->color == 1) { //若兄弟结点为红，它的左右孩子一定为黑来满足黑平衡，并且父节点一定为黑，此时转化为兄弟结点为黑的情况
        swap(o->pre->color, bro->color); //兄弟结点和父节点互换颜色
        Rorate(o->pre, !c);
        bro = o->pre->son[c]; //更改兄弟结点，此时兄弟结点为黑
    }
    //讨论兄弟结点为黑的情况
    if (bro->son[c] != NULL && bro->son[c]->color == 1) { //远侄子结点存在且为红
        Case3_1(o->pre, c);
    } else if (bro->son[!c] != NULL && bro->son[!c]->color == 1) { //远侄子结点不符合条件，近侄子结点存在且近侄子结点为红
        Case3_2(bro, c);
        bro = o->pre->son[c]; //更改兄弟结点为近侄子
        Case3_1(o->pre, c);
    } else if (o->pre->color == 1) { //侄子结点不可能为黑，此时讨论父节点，若父节点为红
        Case3_3(o->pre, c);
    } else { //父节点为黑，再向上递推调整颜色
        bro->color = 1; //兄弟结点变红
        Case3_4(o->pre);
    }
}

//删除情况3: 删除黑色叶子结点
template < class T1, class T2 >
void RBTree < T1, T2 > :: Case3(Node < T1, T2 > * o) {
    int c = o->pre->son[0] == o;
    Node < T1, T2 >  *bro = o->pre->son[c];
    if (bro->color == 1) { //若兄弟结点为红，它的左右孩子一定为黑来满足黑平衡，并且父节点一定为黑，此时转化为兄弟结点为黑的情况
        swap(o->pre->color, bro->color); //兄弟结点和父节点互换颜色
        Rorate(o->pre, !c);
        bro = o->pre->son[c]; //更改兄弟结点，此时兄弟结点为黑
    }
    //讨论兄弟结点为黑的情况
    if (bro->son[c] != NULL && bro->son[c]->color == 1) { //远侄子结点存在且为红
        RemoveNode(o->pre, c);
        Case3_1(o->pre, c);
    } else if (bro->son[!c] != NULL && bro->son[!c]->color == 1) { //远侄子结点不符合条件，近侄子结点存在且近侄子结点为红
        Case3_2(bro, c);
        bro = o->pre->son[c]; //更改兄弟结点为近侄子
        RemoveNode(o->pre, c);
        Case3_1(o->pre, c);
    } else if (o->pre->color == 1) { //侄子结点不可能为黑，此时讨论父节点，若父节点为红
        RemoveNode(o->pre, c);
        Case3_3(o->pre, c);
    } else { //父节点为黑，先删除，再向上递推调整颜色
        RemoveNode(o->pre, c);
        bro->color = 1; //兄弟结点变红
        Case3_4(o->pre);
    }
}

//删除结点
template < class T1, class T2 >
int RBTree < T1, T2 > :: DeleteNode(Node < T1, T2 > * &o, const T1 first) {
    if (o == NULL) {
        return -1; //未找到删除结点
    }
    if (first == o->key.first) {
        if (o->son[0] != NULL && o->son[1] != NULL) { //既有左子树，又有右子树，则进行转移
            Node < T1, T2 >  *del = GetMax(o->son[0]); //得到的结点为叶子结点或者只有左子树
            if (del->son[0] == NULL) { //得到叶子结点
                TransferInfo(o, del); //转移值
                if (del->color == 1) { //若为红色叶子结点，直接删除
                    Case1(del);
                } else { //若为黑色叶子结点
                    Case3(del);
                }
            } else { //只有左子树，本身一定是黑结点，左孩子为红结点
                Case2(del, 0);
            }
        } else if (o->son[0] != NULL) { //只有左子树，本身一定是黑结点，左孩子为红结点
            Case2(o, 0);
        } else if (o->son[1] != NULL) { //只有右子树，本身一定为黑结点，右孩子为红结点
            Case2(o, 1);
        } else { //本身为叶子结点
            if (o->color == 1) { //若为红色叶子结点，直接删除
                Case1(o);
            } else { //若为黑色叶子结点，
                Case3(o);
            }
        }
        return 1; //删除成功
    } else if (first < o->key.first) {
        return DeleteNode(o->son[0], first);
    } else {
        return DeleteNode(o->son[1], first);
    }
}

//对外接口: 查找操作，返回指针,用于修改
template < class T1, class T2 >
pair < T2*, bool >* RBTree < T1, T2 > :: Find(const T1 first) {
    return BinarySearch(root, first);
}

//内部接口: 二分查找
template < class T1, class T2 >
pair < T2*, bool >* RBTree < T1, T2 > :: BinarySearch(Node < T1, T2 > * &o, const T1 first) {
    if (o == NULL) {
        p->second = false;
        return p;
    } else if (first == o->key.first) {
        p->first = &o->key.second;
        p->second = true;
        return p;
    } else if (first < o->key.first) {
        return BinarySearch(o->son[0], first);
    } else {
        return BinarySearch(o->son[1], first);
    }
    p->second = false;
    return p;
}

//对外接口: 查找操作，返回对应下标
template < class T1, class T2 >
int RBTree < T1, T2 > :: FindIndex(const T1 first) const {
    return BinarySearchIndex(root, first);
}

//内部接口: 二分查找，返回对应下标, -1代表没找到
template < class T1, class T2 >
int RBTree < T1, T2 > :: BinarySearchIndex(const Node < T1, T2 > * o, const T1 first) const {
    if (o == NULL) {
        return -1;
    } else if (first == o->key.first) {
        return o->key.second;
    } else if (first < o->key.first) {
        return BinarySearchIndex(o->son[0], first);
    } else {
        return BinarySearchIndex(o->son[1], first);
    }
    return -1;
}

template < class T1, class T2 >
int RBTree < T1, T2 > :: ModifyKey(const T1 first1, const T1 first2) {
    int x = FindIndex(first1);
    if (x != -1) {
        event<T1, T2> a(first2, x);
        Delete(first1);
        Insert(a);
        return 1;
    } else {
        return -1;
    }
}

//外部接口: 先序遍历
template <class T1, class T2>
void RBTree < T1, T2 > :: Pre() {
    Pr(root);
}

//内部接口: 先序遍历
template <class T1, class T2>
void RBTree < T1, T2 > :: Pr(Node < T1 , T2 > * &root) {
    if (root == NULL)
        return;
    cout << root->key.first << '\n';
    Pr(root->son[0]);
    Pr(root->son[1]);
}

//外部接口: 中序遍历
template <class T1, class T2>
void RBTree < T1, T2 > :: In() {
    I(root);
}

//内部接口: 中序遍历
template <class T1, class T2>
void RBTree < T1, T2 > :: I(Node < T1 , T2 > * &root) {
    if (root == NULL)
        return;
    I(root->son[0]);
    cout << root->key.first << '\n';
    I(root->son[1]);
}

//外部接口: 后序遍历
template <class T1, class T2>
void RBTree < T1, T2 > :: Post() {
    Po(root);
}

//内部接口: 后序遍历
template <class T1, class T2>
void RBTree < T1, T2 > :: Po(Node < T1 , T2 > * &root) {
    if (root == NULL)
        return;
    Po(root->son[0]);
    Po(root->son[1]);
    cout << root->key.first << '\n';
}

#endif /* RBTree_hpp */
