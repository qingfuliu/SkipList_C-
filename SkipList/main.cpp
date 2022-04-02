#include <iostream>
#include<list>
#include <algorithm>
#include "SkipList.h"
void TestSkipList(){
    SkipList<int>s;
    std::cout<<s.ToString();
    std::cout<<s.ToString()<<std::endl;
    for(int i=0;i<=100000;++i){
        s.Insert_unique(i);
    }
    std::cout<<s.ToString()<<std::endl;
}
void TestList(){
    std::list<int>l;
    for(int i=0;i<=100000;++i){
        auto it=std::lower_bound(l.begin(),l.end(),i);
        l.insert(it,1);
    }
    for(int i=0;i<100000;++i){
        find(l.begin(),l.end(),i);
    }
}
int main() {
    TestSkipList();
    TestList();
}

//void* a[10];
//auto p1=malloc(sizeof(SkipList<int>::SkipNode)+sizeof(void*)*5);
//auto*p=static_cast<SkipList<int>::SkipNode*>(p1);
//for(int i=0;i<5;i++){
//p->next[i]=nullptr;
//}
//p->value=1;
//p->maxLevel=10;
//a[0]=p;
//std::cout<<p->next<<std::endl;
//// p->maxLevel=1;
//// p->value=0;
//free(a[0]);
//return 0;