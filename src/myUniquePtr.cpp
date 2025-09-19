#include <bits/stdc++.h>

template <typename T>
class myUniquePtr
{
public:
    explicit myUniquePtr(T *ptr = nullptr) : ptr_(ptr) {}

    myUniquePtr(const myUniquePtr &rhs) = delete;
    myUniquePtr &operator=(const myUniquePtr &rhs) = delete;

    myUniquePtr(myUniquePtr &&rhs) noexcept : ptr_(rhs.ptr_)
    {
        rhs.ptr_ = nullptr;
    }
    myUniquePtr &operator=(myUniquePtr &&rhs) noexcept
    {
        if (this != (&rhs))
        {
            if (ptr_)
                delete (ptr_);
            ptr_ = rhs.ptr_;
            rhs.ptr_ = nullptr;
        }
        return *this;
    }

    ~myUniquePtr() { delete ptr_; };

    T *operator->() const
    {
        return ptr_;
    }

    T &operator*() const
    {
        return *ptr_;
    }

    T *release()
    {
        T *tmp = ptr_;
        ptr_ = nullptr;
        return tmp;
    }

    T *get() const
    {
        return ptr_;
    }

    void reset(T *p = nullptr)
    {
        delete ptr_;
        ptr_ = p;
    }

private:
    T *ptr_;
};

struct Foo {
    Foo(int v) : value(v) { std::cout << "Foo(" << value << ") constructed\n"; }
    ~Foo() { std::cout << "Foo(" << value << ") destroyed\n"; }
    void show() { std::cout << "Value: " << value << "\n"; }
    int value;
};

int main() {
    myUniquePtr<Foo> p1(new Foo(10));  // 构造
    p1->show();                         // 访问成员
    (*p1).show();                       // 另一种访问方式

    myUniquePtr<Foo> p2 = std::move(p1); // 移动构造
    if (!p1.get()) std::cout << "p1 is empty after move\n";

    Foo* raw = p2.release();            // release 不删除对象
    if (!p2.get()) std::cout << "p2 is empty after release\n";

    delete raw;                          // 手动删除释放

    myUniquePtr<Foo> p3(new Foo(20));
    p3.reset(new Foo(30));              // reset 释放旧对象，管理新对象

    // 移动赋值测试
    myUniquePtr<Foo> p4(nullptr);
    p4 = std::move(p3);
    if (!p3.get()) std::cout << "p3 is empty after move assignment\n";

    return 0;
}