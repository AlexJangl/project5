#include <iostream>
template <class T>
class MyVector {
public:

    typedef T* iterator;
    MyVector() {
        m_size = 0;
        m_buffer = 0;
        m_capasity = 10;

    }
   /* MyVector(const MyVector<T>& vect) {
        m_size = vect.m_size;
        push_capacity(m_size);
        m_buffer = new T[m_capasity];
        for (size_t i = 0; i < m_size; i++)
        {
            m_buffer[i] = vect.m_buffer[i];
        }
    }
    */
    MyVector(MyVector<T>&& vect) {
        m_size = vect.m_size;
        m_capasity = vect.m_capasity;
        m_buffer = new T[m_capasity];
        for (size_t i = 0; i < m_size; i++)
        {
            m_buffer[i] = vect.m_buffer[i];
        }
       // vect.m_size=0;
       // vect.m_capasity=0;
       // delete[] vect.m_buffer;
    }
    ~MyVector() {
        if (m_buffer) {
            delete[] m_buffer;
        }
    }
    void push_capacity(size_t size) {
        if (size < 10)
        {
            m_capasity = 12;
        }
        else {
            m_capasity = size * 1.3;
        }
    }

    void push_back(const T& value) {
        m_size++;
        T* buffer;
        if (m_size > m_capasity) {
            push_capacity(m_size);

        }

        buffer = new T[m_size];
        for (size_t i = 0; i < m_size - 1; i++)
        {
            buffer[i] = m_buffer[i];
        }
        buffer[m_size - 1] = value;
        delete[] m_buffer;
        m_buffer = new T[m_capasity];
        for (size_t i = 0; i < m_size; i++)
        {
            m_buffer[i] = buffer[i];
        }
        delete[] buffer;

    }
    MyVector& operator=(MyVector&& vect)
    {
        m_size = vect.m_size;
        m_capasity = vect.m_capasity;
        m_buffer = new T[m_capasity];
        for (size_t i = 0; i < m_size; i++)
        {
            m_buffer[i] = vect.m_buffer[i];
        }
        return *this;
    }
    
    T* getBuffer() {
        return m_buffer;
    }
    size_t getSize() {
        return m_size;
    }
    int  pop_back() {
        return m_buffer[m_size--];
    }
    
private:
    size_t m_size;
    size_t m_capasity;
    T* m_buffer;
};
class String
{
public:
    String() {}
    String(const char* str)
    {
        std::cout << "String(const char *const c_string)\n";
        m_size = strlen(str) + 1;
        m_string = new char[m_size];
        strcpy_s(m_string, m_size, str);
    }

    String(const String& other)
    {
        std::cout << "String(const String& other)\n";
        m_string = new char[other.m_size];
        strcpy_s(m_string, other.m_size, other.m_string);
        m_size = other.m_size;
    }
    String(String&& other)
    {
        std::cout << " String(String&& other)\n";
        m_string = other.m_string;
        m_size = other.m_size;
        other.m_string = nullptr;
        other.m_size = 0;
    }
    String& operator=(const String& other)
    {
        std::cout << " operator=(const String& other)\n";
        m_string = new char[other.m_size];
        strcpy_s(m_string, other.m_size, other.m_string);
        m_size = other.m_size;
        return *this;
    }
    String& operator=(String&& other)
    {
        std::cout << " operator=(String&& other)\n";
        m_string = other.m_string;
        m_size = other.m_size;
        other.m_string = nullptr;
        other.m_size = 0;
        return *this;
    }
    String& operator+(const String& other) {
        char* tmpStr = m_string;
        m_string = new char[m_size + other.m_size];
        strcpy_s(m_string, m_size, tmpStr);
        strcpy_s(m_string + m_size - 1, other.m_size, other.m_string);
        delete[] tmpStr;
        m_size += other.m_size;
        return *this;
    }
    ~String() noexcept
    {
        std::cout << " ~String()\n";
        if (m_string) {
            delete[] m_string;
            m_string = nullptr;
        }
    }

private:
    char* m_string = nullptr;
    size_t m_size;
};



int main()
{
    MyVector<int> a;
    a.push_back(1);
    a.push_back(2);
    a.push_back(3);
    MyVector<int> b;
    b = std::move(a);
    MyVector<int> d(std::move(a));




}

