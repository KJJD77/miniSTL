#include <bits/stdc++.h>
using namespace std;
class myString
{
public:
    myString() : len(0), data(new char[1]{'\0'})
    {
    }

    myString(const char *s)
    {
        if (s)
        {
            len = strlen(s);
            data = new char[len+1];
            str_copy(data, s, len+1);
        }
        else
        {
            len = 0;
            data = new char[1]{'\0'};
        }
    }

    myString(const myString &other) noexcept
    {
        len = other.len;
        data = new char[len + 1];
        str_copy(data, other.data, len+1);
    }

    myString(myString &&other) noexcept : len(other.len), data(other.data)
    {
        other.len = 0;
        other.data = nullptr;
    }

    myString &operator=(const myString &other)
    {
        if (this == &other)
            return *this;
        delete[] data;
        len = other.len;
        data = new char[len+1];
        str_copy(data, other.data, len+1);
        return *this;
    }

    myString operator+(const myString &other)
    {
        myString temp(*this);
        temp.append(other);
        return temp;
    }

    myString &operator+=(const myString &other)
    {
        append(other);
        return *this;
    }

    myString &append(const myString &other)
    {
        char *newDate = new char[len + other.len + 1];
        str_copy(newDate, data, len);
        str_copy(newDate + len, other.data, other.len+1);
        delete[] data;
        data = newDate;
        len += other.len;
        return *this;
    }

    void clear()
    {
        delete[] data;
        len = 0;
        data = new char[1]{'\0'};
    }

    bool operator==(const myString &other) const
    {
        if (len != other.len)
            return false;
        for (int i = 0; i < len; i++)
            if (other.data[i] != data[i])
                return false;
        return true;
    }

    bool operator!=(const myString &other) const
    {
        return !(*this == other);
    }

    friend std::ostream &operator<<(std::ostream &os, const myString &str)
    {
        os << str.data;
        return os;
    }

    friend std::istream &operator>>(std::istream &is, myString &str)
    {
        char buffer[1024];       // 临时缓冲区，足够大
        is >> buffer;            // 读取到缓冲区
        str = buffer;
        return is;
    }

private:
    char *data;
    size_t len;
    static size_t strlen(const char *str)
    {
        size_t len = 0;
        while (str && *str)
            len++,str++;
        return len;
    }
    static void str_copy(char *dest, const char *src, size_t n)
    {
        for (int i = 0; i < n; i++)
            dest[i] = src[i];
    }
};
int main() {
    myString s1("Hello");
    myString s2(" ");
    myString s3("World");

    // 链式拼接
    s1 += s2 += s3;
    std::cout << "s1: " << s1 << std::endl; // Hello World

    // operator+
    myString s4 = s1 + myString("!!!");
    std::cout << "s4: " << s4 << std::endl; // Hello World!!!

    return 0;
}
