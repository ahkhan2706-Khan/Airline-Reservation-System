#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#define _ITERATOR_DEBUG_LEVEL 2

template<typename T>
class DynamicArray
{
private:
    T* data;
    int capacity;
    int size;

    void ensureCapacity(int desired)
    {
        if (desired <= capacity)
        {
            return;
        }

        int newCapacity = capacity == 0 ? 1 : capacity;
        while (newCapacity < desired)
        {
            newCapacity *= 2;
        }

        T* newData = new T[newCapacity];
        for (int i = 0; i < size; i++)
        {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
        capacity = newCapacity;
    }

    void resize()
    {
        ensureCapacity(size + 1);
    }

public:
    DynamicArray() : data(nullptr), capacity(0), size(0) {}

    DynamicArray(const DynamicArray& other) : data(nullptr), capacity(0), size(0)
    {
        ensureCapacity(other.size);
        size = other.size;
        for (int i = 0; i < size; i++)
        {
            data[i] = other.data[i];
        }
    }

    DynamicArray& operator=(const DynamicArray& other)
    {
        if (this == &other)
        {
            return *this;
        }

        ensureCapacity(other.size);
        size = other.size;
        for (int i = 0; i < size; i++)
        {
            data[i] = other.data[i];
        }
        return *this;
    }

    ~DynamicArray()
    {
        delete[] data;
    }

    void push_back(const T& value)
    {
        resize();
        data[size++] = value;
    }

    void pop_back()
    {
        if (size > 0)
        {
            size--;
        }
    }

    T& operator[](int index)
    {
        return data[index];
    }

    const T& operator[](int index) const
    {
        return data[index];
    }

    int getSize() const
    {
        return size;
    }

    bool isEmpty() const
    {
        return size == 0;
    }

    void clear()
    {
        size = 0;
    }

    T* begin()
    {
        return data;
    }

    T* end()
    {
        return data + size;
    }

    const T* begin() const
    {
        return data;
    }

    const T* end() const
    {
        return data + size;
    }

    T& back()
    {
        return data[size - 1];
    }

    const T& back() const
    {
        return data[size - 1];
    }

    void insert(int index, const T& value)
    {
        if (index < 0 || index > size)
        {
            return;
        }
        resize();
        for (int i = size; i > index; i--)
        {
            data[i] = data[i - 1];
        }
        data[index] = value;
        size++;
    }

    void erase(int index)
    {
        if (index < 0 || index >= size)
        {
            return;
        }
        for (int i = index; i < size - 1; i++)
        {
            data[i] = data[i + 1];
        }
        size--;
    }
};

#endif
