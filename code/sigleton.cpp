/*************************************************************************
	> File Name: sigleton.cpp
	> Brief:线程安全的单例类 
	> Author: Chen Kai(http://www.chenkai.me)
	> Mail: ischenkai@qq.com
	> Created Time: 二  5/ 9 21:46:51 2017
 ************************************************************************/
#include<iostream>
#include<pthread.h>
using namespace std;

class Sigleton;
class Sigleton 
{
    private:
        static Sigleton* p;
        static pthread_mutex_t mutex;
        Sigleton(){}
    public:
        static Sigleton* get_obj()
        {
            if(p!=NULL)
            {
                return p;
            }
            pthread_mutex_lock(&mutex);
            if(p==NULL)
            {
                pthread_mutex_unlock(&mutex);
                p = new Sigleton;
                return p;
            }
            else
            {
                pthread_mutex_unlock(&mutex);
                return p;
            }
        }
};

//const 类型的静态成员可以在类里面直接初始化，非静态的在类声明以外初始化
pthread_mutex_t Sigleton::mutex;
Sigleton* Sigleton::p = NULL;;

int main()
{
    Sigleton* s1 = Sigleton::get_obj();
    Sigleton* s2 = Sigleton::get_obj();
    Sigleton* s3 = Sigleton::get_obj();
    cout << s1 << endl;
    cout << s2 << endl;
    cout << s3 << endl;
    return 0;
}
