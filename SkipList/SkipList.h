/*
 * @Autor: qing fu liu
 * @Email: 1805003304@qq.com
 * @Github: https://github.com/qingfuliu
 * @Date: 2022-04-02 15:31:57
 * @LastEditors: qingfu liu
 * @LastEditTime: 2022-04-02 18:01:49
 * @FilePath: \c++\SkipList\SkipList.h
 * @Description: 
 */
#include<random>
#include <sstream>
#define MAXSKIPLIST_LEVEL 32
#define SKIPLIST_P 0.25

struct Init{
    Init(){
        srand(time(NULL));
    }
};

static Init init;
int randomLevel(void){
    int level=1;
    std::default_random_engine e(time(NULL));
    std::uniform_int_distribution<int>u;
    while((rand()&0xFFFF)<(SKIPLIST_P*0xFFFF))
        level++;
    return level<MAXSKIPLIST_LEVEL?level:MAXSKIPLIST_LEVEL;
}

template<class T>
class SkipList{
public:
    SkipList(const SkipList&)=delete;
    SkipList& operator=(const SkipList&)=delete;
    SkipList& operator=(SkipList&&)=delete;
    struct SkipNode{
        T value;
        int maxLevel;
        SkipNode* next[1];
    };
public:
    SkipNode* head;
    int maxLevel;
public:
    SkipList(){
        head=(SkipNode*)newNode(T(),MAXSKIPLIST_LEVEL);
        maxLevel=1;
    }
private:
    SkipNode*newNode(const T&value,int level){
        auto node=static_cast<SkipNode*>(malloc(sizeof(SkipNode)+sizeof(SkipNode*)*(level-1)));
        for(int i=0;i<level;++i){
            node->next[i]=nullptr;
        }
        node->value=value;
        node->maxLevel=level;
        return node;
    }
public:
    SkipNode*Find(SkipNode*node){
        return Find(node->value);
    }
    SkipNode*Find(const T&value)const{
        SkipNode*temp=head;
        for(int i=maxLevel-1;i>-1;--i){
            while(temp->next[i]!=nullptr&&temp->next[i]->value<value){
                temp=temp->next[i];
            }
            if(temp->next[i]!=nullptr&&temp->next[i]->value==value){
                return temp->next[i];
            }
        }
        return nullptr;
    }
    SkipNode*Insert_unique(const T&value){
        auto*node=Find(value);
        if(node!=nullptr){
            node->value=value;
            return node;
        }
        int level=randomLevel();
        level=level>maxLevel?maxLevel+1:level;
        node=newNode(value,level);
        auto temp=head;
        for(int i=maxLevel-1;i>-1;--i){
            while(temp->next[i]!=nullptr&&temp->next[i]->value>value){
                temp=temp->next[i];
            }
            if(i<level){
                node->next[i]=temp->next[i];
                temp->next[i]=node;
            }
        }
        if(maxLevel<level){
            head->next[maxLevel++]=node;
        }
        return node;
    }
    void Delete(const T&value){
        if(maxLevel==0){
            return;
        }
        auto temp=head;
        for(int i=maxLevel-1;i>-1;--i){
            while(temp->next[i]!= nullptr&&temp->next[i]->value>value){
                temp=temp->next[i];
            }
            if(temp->next[i]!= nullptr&&temp->next[i]->value==value){
                auto target=temp->next[i];
                temp->next[i]=temp->next[i]->next[i];
                if(i==0){
                    free((void*)target);
                }
            }
        }
        while(maxLevel>1&&head->next[maxLevel-1]== nullptr)--maxLevel;
    }
    std::ostream& dump(std::ostream &os)const{
        os<<"================================================================================="<<std::endl;
        for(int i=maxLevel-1;i>-1;--i){
            auto temp=head->next[i];
            while(temp!= nullptr){
                os<<temp->value<<" ";
                temp=temp->next[i];
            }
            os<<std::endl;
            os<<"================================================================================="<<std::endl;
        }
        os<<"MaxLevel is "<<maxLevel<<std::endl;
        os<<"================================================================================="<<std::endl;
        return os;
    }

    std::string ToString()const{
        std::stringstream ss;
        dump(ss);
       return ss.str();
    }
};
