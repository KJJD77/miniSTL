#include <bits/stdc++.h>

struct controlBlock
{
    void *ptr_;
    int strong_count_;
    int weak_count_;
    controlBlock(void *ptr = nullptr) : ptr_(ptr), strong_count_(1), weak_count_(0) {}
};

template <typename T>
class myWeakPtr;

template <typename T>
class mySharedPtr
{
public:
    explicit mySharedPtr(T *ptr=nullptr) : ptr_(ptr), cb_(ptr ? new controlBlock(ptr_) : nullptr)
    {
    }

    explicit mySharedPtr(const mySharedPtr &other) : ptr_(other.ptr_), cb_(other.cb_)
    {
        if (cb_)
            cb_->strong_count_++;
    }

    explicit mySharedPtr(const myWeakPtr<T> &weakPtr);

    ~mySharedPtr()
    {
        release();
    }

    T *get() const
    {
        return ptr_;
    }

    T *operator->()const 
    {
        return ptr_;
    }

    T &operator*()const 
    {
        return *ptr_;
    }

    int use_count() const { return cb_ ? cb_->strong_count_ : 0; }

    void release()
    {
        if (cb_ && --cb_->strong_count_ == 0)
        {
            delete ptr_;
            ptr_ = nullptr;
            if (cb_->weak_count_ == 0)
            {
                delete cb_;
                cb_ = nullptr;
            }
        }
    }

    friend class myWeakPtr<T>;

private:
    T *ptr_;

    controlBlock *cb_;
};

template <typename T>
class myWeakPtr
{
public:
    myWeakPtr() : cb_(nullptr) {}

    myWeakPtr(const mySharedPtr<T>& sharedPtr) : cb_(sharedPtr.cb_)
    {
        if (cb_)
            cb_->weak_count_++;
    }
    myWeakPtr(const myWeakPtr &other) : cb_(other.cb_)
    {
        if (cb_)
            cb_->weak_count_++;
    }

    ~myWeakPtr()
    {
        if (cb_ && --cb_->weak_count_ == 0 && cb_->strong_count_ == 0)
        {
                delete cb_;
                cb_ = nullptr;
        }
    }

    mySharedPtr<T> lock()
    {
        if (cb_ && cb_->strong_count_)
        {
            return mySharedPtr<T>(*this);
        }

        return mySharedPtr<T>();
    }

    int use_count() const { return cb_ ? cb_->strong_count_ : 0; }

private:
    controlBlock *cb_;
    friend class mySharedPtr<T>;
};

template<typename T>
mySharedPtr<T>::mySharedPtr(const myWeakPtr<T> &weakPtr):cb_(nullptr),ptr_(nullptr){
    if(weakPtr.cb_)
    {
        cb_=weakPtr.cb_;
        ptr_=static_cast<T*>(weakPtr.cb_->ptr_);
        cb_->strong_count_++;
    }
}

struct Foo
{
    Foo() { std::cout << "Foo constructed\n"; }
    ~Foo() { std::cout << "Foo destroyed\n"; }
};

int main()
{
    mySharedPtr<Foo> sp1(new Foo());
    std::cout << "sp1 use_count: " << sp1.use_count() << "\n";

    myWeakPtr<Foo> wp(sp1); // 创建 weak_ptr
    std::cout << "wp use_count: " << wp.use_count() << "\n";

    {
        mySharedPtr<Foo> sp2 = wp.lock(); // 提升为 shared_ptr
        std::cout << "sp2 use_count: " << sp2.use_count() << "\n";
    } // sp2 离开作用域，strong_count 减一

    std::cout << "After sp2 scope, sp1 use_count: " << sp1.use_count() << "\n";

    sp1.release(); // 手动释放 sp1
    std::cout << "sp1 released\n";

    mySharedPtr<Foo> sp3 = wp.lock(); // 对象已销毁，返回空
    if (!sp3.get())
        std::cout << "lock failed, object expired\n";
}
