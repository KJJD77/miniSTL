#include <bits/stdc++.h>
template <class T> class myVector
{
  private:
    T *elements;
    size_t current_size;
    size_t capacity;

  public:
    myVector() : current_size(0), capacity(0), elements(nullptr)
    {
    }
    myVector(const myVector &other) : current_size(other.current_size), capacity(other.capacity)
    {
        elements = new T[capacity];
        std::copy(other.elements, other.elements + current_size, elements);
    }
    myVector &operator=(const myVector &other)
    {
        if (&other != this)
        {
            T *newElements = new T[capacity];
            std::copy(other.elements, other.elements + current_size, newElements);

            if (elements)
                release();
            capacity = other.capacity;
            current_size = other.current_size;
            elements = newElements;
        }
        return *this;
    }
    ~myVector()
    {
        release();
    }

    void reserve(size_t newCapacity)
    {
        if (newCapacity > capacity)
        {
            // std::cout<<newCapacity<<'\n';
            T *newelements = new T[newCapacity];
            std::copy(elements, elements + current_size, newelements);
            delete[] elements;
            capacity = newCapacity;
            elements = newelements;
        }
    }

    void push_back(const T &input)
    {
        if (current_size == capacity)
            capacity ? reserve(2 * capacity) : reserve(1);
        elements[current_size++] = input;
    }

    size_t size()
    {
        return current_size;
    }

    size_t getCapacity()
    {
        return capacity;
    }

    T &operator[](size_t index)
    {
        if (index >= current_size)
            throw std::out_of_range("out of size");
        return elements[index];
    }

    const T &operator[](size_t index) const
    {
        if (index >= current_size)
            throw std::out_of_range("out of size");
        return elements[index];
    }

    void clear()
    {
        current_size = 0;
    }

    void pop_back()
    {
        if (current_size)
            current_size--;
    }

    void insert(const size_t index, T &input)
    {
        if (index >= current_size)
        {
            throw std::out_of_range("Index overstap");
        }
        if (current_size == capacity)
            capacity ? reserve(2 * capacity) : reserve(1);
        for (int i = current_size; i > index; i--)
        {
            elements[i] = elements[i - 1];
        }
        elements[index] = input;
        current_size++;
    }

    T *begin()
    {
        return elements;
    }
    const T *begin() const
    {
        return elements;
    }

    T *end()
    {
        return elements + current_size;
    }

    const T *end() const
    {
        return elements + current_size;
    }

  private:
    void release()
    {
        delete[] elements;
        elements = nullptr;
    }
};
struct alignas(128) Big
{
    char buf[128];
    Big() = default;
    Big(const Big &) = default;
};
int main()
{
    /* 1. 默认构造空容器 */
    myVector<int> v0;
    std::cout << "Test 1: size=" << v0.size() << " capacity=" << v0.getCapacity() << '\n';

    /* 2. 连续 push_back + 边界访问 */
    myVector<int> v1;
    for (int i = 0; i < 10; ++i)
        v1.push_back(i * 2);
    std::cout << "Test 2: front=" << v1[0] << " back=" << v1[9] << '\n';

    /* 3. 拷贝构造 */
    myVector<int> v2(v1);
    std::cout << "Test 3: copy size=" << v2.size() << '\n';

    /* 4. 拷贝赋值 */
    myVector<int> v3;
    v3 = v1;
    std::cout << "Test 4: assign size=" << v3.size() << '\n';

    /* 5. 自赋值（不应崩溃） */
    v3 = v3;
    std::cout << "Test 5: self-assign size=" << v3.size() << '\n';

    /* 6. 清空后再用 */
    v3.clear();
    v3.push_back(99);
    std::cout << "Test 6: after clear size=" << v3.size() << " data=" << v3[0] << '\n';

    /* 7. 插入 + 迭代器遍历 */
    myVector<std::string> vs;
    vs.push_back("A");
    vs.push_back("C");
    std::string s = "B";
    vs.insert(1, s);
    std::cout << "Test 7: ";
    for (auto &s : vs)
        std::cout << s << ' ';
    std::cout << '\n';

    /* 8. 非平凡类型（std::string）拷贝/移动正确性 */
    myVector<std::string> vs2(vs);
    vs2.pop_back();
    std::cout << "Test 8: vs2.size=" << vs2.size() << " vs.size=" << vs.size() << '\n';

    /* 9. 边界越界访问（应抛异常或打印警告） */
    try
    {
        std::cout << "Test 9: v1[99]=" << v1[99] << '\n';
    }
    catch (...)
    {
        std::cout << "Test 9: caught exception\n";
    }

    /* 10. 大容量 reserve 不丢数据 */
    v2.reserve(1000);
    std::cout << "Test 10: after reserve size=" << v2.size() << " capacity=" << v2.getCapacity() << " v2[5]=" << v2[5]
              << '\n';

    /* 11. 128 字节位域结构体（非默认构造） */

    myVector<Big> vb;
    vb.push_back(Big{});
    vb.push_back(Big{});
    std::cout << "Test 11: Big obj capacity=" << vb.getCapacity() << " size=" << vb.size() << '\n';
    // std::cout << "All tests passed.\n";
    return 0;
}