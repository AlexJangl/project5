#include <iostream>
template <class T>
class MyVector {
public:

    typedef T* iterator;
    MyVector() {
        m_size = 0;
        m_buffer = 0;
        m_capasity = 10;
        m_buffer = new T[m_capasity];
    }
  
    MyVector(MyVector<T>&& vect) {
        m_size = vect.m_size;
        m_capasity = vect.m_capasity;
        m_buffer = new T[m_capasity];
        for (size_t i = 0; i < m_size; i++)
        {
            m_buffer[i] = std::move(vect.m_buffer[i]);
        }
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
        auto buffer = m_buffer;
        m_buffer = new T[m_capasity];
        for (size_t i = 0; i < m_size; i++)
        {
            m_buffer[i] = std::move(buffer[i]);
        }
        delete[] buffer;
    }

    void push_back(const T& value) {
        m_size++;
        if (m_size > m_capasity) {
            push_capacity(m_size);
        }
        m_buffer[m_size - 1] = value;
    }
    template<typename... U>
    void EmplaceBack(U&&... value) {
        m_size++;
        if (m_size > m_capasity) {
            push_capacity(m_size);

        }
        new (&m_buffer[m_size - 1]) T(std::forward<U>(value)...);
    }
    MyVector& operator=(MyVector&& vect)
    {
        m_size = vect.m_size;
        m_capasity = vect.m_capasity;
        m_buffer = new T[m_capasity];
        for (size_t i = 0; i < m_size; i++)
        {
            m_buffer[i] = std::move(vect.m_buffer[i]);
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

    String(const char* str, size_t true_size)
    {
        std::cout << "String(const char *const c_string)\n";
        m_size = true_size+1;
        m_string = new char[m_size];
        strcpy_s(m_string, true_size, str);
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
/*template<typename T, typename... Args>

T make_unique(Args&&... args)
{
    return T(std::forward<Args>(args)...);
}*/


int main()
{
    
    MyVector<String>e;
    String e1("Hello");
    e.EmplaceBack("Hello");
    e.EmplaceBack("Hello vars", 12);
   
    //auto string = make_unique<String>("Hello, vars", 6);


}

