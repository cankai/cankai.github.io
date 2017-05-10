/*************************************************************************
	> File Name: sigleton2.cpp
	> Brief: 
	> Author: Chen Kai(http://www.chenkai.me)
	> Mail: ischenkai@qq.com
	> Created Time: 二  5/ 9 22:18:16 2017
 ************************************************************************/
#include<iostream>
#include<pthread.h>
using namespace std;

class singleton1
{
    protected:
        singleton1()
    {
                pthread_mutex_init(&mutex, NULL);
            
    }
    private:
        static singleton1* p;
    public:
        static pthread_mutex_t mutex;
        static singleton1* initance();

};

pthread_mutex_t singleton1::mutex;
singleton1* singleton1::p = NULL;
singleton1* singleton1::initance()
{
        if (p == NULL)
    {
                pthread_mutex_lock(&mutex);
                if (p == NULL)
                    p = new singleton1();
                pthread_mutex_unlock(&mutex);
            
    }
        return p;

}

class singleton2
{
    protected:
        singleton2()
    {
                pthread_mutex_init(&mutex, NULL);
            
    }
    public:
        static pthread_mutex_t mutex;
        static singleton2* initance();

};

pthread_mutex_t singleton2::mutex;
singleton2* singleton2::initance()
{
        pthread_mutex_lock(&mutex);
        //静态局部变量
        static singleton2 obj;
        pthread_mutex_unlock(&mutex);
        return &obj;

}

class singleton
{
    protected:
        singleton()
        {}
    private:
        static singleton* p;
    public:
        static singleton* initance();

};
singleton* singleton::p = new singleton;
singleton* singleton::initance()
{
        return p;

}
int main()
{
    singleton *s1 = singleton::initance();
    singleton *s2 = singleton::initance();
    singleton *s3 = singleton::initance();
    singleton *s4 = singleton::initance();
    cout << s1 << endl;
    cout << s2 << endl;
    cout << s3 << endl;
    cout << s4 << endl;
    return 0;
}
