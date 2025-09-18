#include <bits/stdc++.h>
template <typename T>
class mySharedPtr
{
public:
    explicit mySharedPtr(T *ptr = nullptr) : ptr_(ptr), count_(ptr ? new int(1) : nullptr)
    {
    }

    mySharedPtr(const mySharedPtr &rhs) : ptr_(rhs.ptr_), count_(rhs.count_)
    {
        ++(*count_);
    }

    mySharedPtr &operator=(const mySharedPtr &rhs)
    {
        if (&rhs != this)
        {
            release();
            ptr_ = rhs.ptr_;
            count_ = rhs.count_;
            if (count_)
                ++(*count_);
        }
        return *this;
    }

    T &operator*() const
    {
        return *ptr_;
    }

    T *operator->() const
    {
        return ptr_;
    }

    ~mySharedPtr()
    {
        release();
    }

    int use_count() const
    {
        if (count_)
            return *count_;
        return 0;
    }

private:
    T *ptr_;
    int *count_;
    void release()
    {
        if (count_ && --(*count_) == 0)
        {
            delete (ptr_);
            delete (count_);
        }
        ptr_ = nullptr;
        count_ = nullptr;
    }
};
class MyClass
{
public:
    MyClass() { std::cout << "MyClass 构造\n"; }
    ~MyClass() { std::cout << "MyClass 析构\n"; }
    void say() { std::cout << "Hello from MyClass\n"; }
};

int main()
{
    mySharedPtr<MyClass> sp1(new MyClass());
    std::cout << "引用计数: " << sp1.use_count() << std::endl;

    {
        mySharedPtr<MyClass> sp2 = sp1;
        std::cout << "引用计数: " << sp1.use_count() << std::endl;
        sp2->say();
        (*sp1).say();
    }

    std::cout << "引用计数: " << sp1.use_count() << std::endl;

    return 0;
}