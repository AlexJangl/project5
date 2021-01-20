#include <iostream>
#include <typeinfo>	
#include <cstring>	
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
template <class T>
class String
{
public:
    typedef T* iterator;

    String() {}
    String(const char* var)
    {      
       m_size = strlen(var) + 1;
       m_var = new char[m_size];
       strcpy_s(m_var, m_size, var);      
    }

    String(const T* var, size_t true_size)
    {
        std::string typeT = "char";
        std::cout << "String(const char *const c_string)\n";
        if (typeid(T).name() == typeT) {
            m_size = true_size + 1;
            m_var = new T[m_size];
            
        }
        else
        {
            m_size = true_size;
            m_var = new T[m_size];
            
        }
        for (size_t i = 0; i < m_size; i++)
        {
            m_var[i] = var[i];
        }
    }

    String(const String& other)
    {
        std::cout << "String(const String& other)\n";
        m_var = new T[other.m_size];
        for (size_t i = 0; i < other.m_size; i++)
        {
            m_var[i] = other.m_var[i];
        }
        m_size = other.m_size;
    }
    String(String&& other)
    {
        std::cout << " String(String&& other)\n";
        for (size_t i = 0; i < other.m_size; i++)
        {
            m_var[i] = other.m_var[i];
        }
        m_size = other.m_size;
        other.m_var = nullptr;
        other.m_size = 0;
    }
    String& operator=(const String& other)
    {
        std::cout << " operator=(const String& other)\n";
        m_var = new T[other.m_size];
        for (size_t i = 0; i <other.m_size; i++)
        {
            m_var[i] = other.m_var[i];
        }
        m_size = other.m_size;
        return *this;
    }
    String& operator=(String&& other)
    {
        std::cout << " operator=(String&& other)\n";
        for (size_t i = 0; i < other.m_size; i++)
        {
            m_var[i] = other.m_var[i];
        }
        m_size = other.m_size;
        other.m_var = nullptr;
        other.m_size = 0;
        return *this;
    }
    String& operator+(const String& other) {
        char* tmpStr = m_var;
        m_var = new T[m_size + other.m_size];
        strcpy_s(m_var, m_size, tmpStr);
        strcpy_s(m_var + m_size - 1, other.m_size, other.m_var);
        delete[] tmpStr;
        m_size += other.m_size;
        return *this;
    }
    ~String() noexcept
    {
        std::cout << " ~String()\n";
        if (m_var) {
            delete[] m_var;
            m_var = nullptr;
        }
    }

private:
    T* m_var = nullptr;
    size_t m_size;
};


int main()
{
    
    MyVector<String<char>>vectChar;
    MyVector<String<int>>vectInt;
    String<char> strChar("Hello");
    int mas[] = { 1, 2 };
    String<int> strInt(mas, 2);
    vectChar.EmplaceBack("Hello vars", 12);
    vectInt.EmplaceBack(strInt);
    String<int> strInt1(mas, 2);
    vectInt.EmplaceBack(strInt1);
}

