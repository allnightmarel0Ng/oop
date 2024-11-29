#ifndef LAB5_LIST_H
#define LAB5_LIST_H

#include <iostream>
#include <utility>

#include "allocator.h"

template <typename T, typename Allocator = Allocator<T>>
class List
{
public:
    explicit List();

public:
    virtual ~List();
    List(const List &other);
    List &operator=(const List &other);
    List(List &&other) noexcept;
    List &operator=(List &&other) noexcept;

private:
    struct Node
    {
        T val;
        Node *next;

        explicit Node(T val, Node *next = nullptr);
    };

private:
    Node *_first;
    Node *_last;
    std::size_t _size;

public:
    class Iterator final
    {
        friend List;

    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = T;
        using pointer = T *;
        using reference = T &;
        using difference_type = std::ptrdiff_t;

    private:
        explicit Iterator(typename List<T, Allocator>::Node *node);

    public:
        Iterator &operator++();
        Iterator operator++(int notUsed);
        bool operator==(const Iterator &other) const noexcept;
        bool operator!=(const Iterator &other) const noexcept;
        T &operator*() const;

    private:
        Node *_current;
    };

    class ConstIterator final
    {
        friend List;

    private:
        using iterator_category = std::forward_iterator_tag;
        using value_type = T;
        using pointer = T *;
        using reference = T &;
        using difference_type = std::ptrdiff_t;

    private:
        explicit ConstIterator(typename List<T, Allocator>::Node *node);

    public:
        ConstIterator &operator++();
        ConstIterator operator++(int notUsed);
        bool operator==(const ConstIterator &other) const noexcept;
        bool operator!=(const ConstIterator &other) const noexcept;
        const T &operator*() const;

    private:
        Node *_current;
    };

public:
    bool Empty() const noexcept;
    std::size_t Size() const noexcept;

public:
    void PushBack(const T &value);
    void PushFront(const T &value);
    void PopBack();
    void PopFront();

public:
    Iterator Insert(const Iterator &it, const T &value);
    Iterator Insert(const ConstIterator &it, const T &value);
    Iterator Erase(const Iterator &it);
    Iterator Erase(const ConstIterator &it);

public:
    using iterator = Iterator;
    using const_iterator = ConstIterator;
    using allocator_type = Allocator;

public:
    iterator begin() const;
    const_iterator cbegin() const;
    iterator end() const;
    const_iterator cend() const;

private:
    void clear() noexcept;
    void copy(const List &other);
    void move(List &&other) noexcept;
};

template <typename T, typename Allocator>
List<T, Allocator>::Iterator::Iterator(typename List<T, Allocator>::Node *node) : _current(node)
{
}

template <typename T, typename Allocator>
typename List<T, Allocator>::Iterator &List<T, Allocator>::Iterator::operator++()
{
    if (_current == nullptr)
    {
        throw std::runtime_error("Iterator out of bounds");
    }

    _current = _current->next;
    return *this;
}

template <typename T, typename Allocator>
typename List<T, Allocator>::Iterator List<T, Allocator>::Iterator::operator++(int notUsed)
{
    auto tmp = *this;
    *++this;
    return tmp;
}

template <typename T, typename Allocator>
bool List<T, Allocator>::Iterator::operator==(const List<T, Allocator>::Iterator &other) const noexcept
{
    return _current == other._current;
}

template <typename T, typename Allocator>
bool List<T, Allocator>::Iterator::operator!=(const List<T, Allocator>::Iterator &other) const noexcept
{
    return _current != other._current;
}

template <typename T, typename Allocator>
T &List<T, Allocator>::Iterator::operator*() const
{
    if (_current == nullptr)
    {
        throw std::invalid_argument("Invalid iterator pointer");
    }

    return _current->val;
}

template <typename T, typename Allocator>
List<T, Allocator>::ConstIterator::ConstIterator(typename List<T, Allocator>::Node *node) : _current(node)
{
}

template <typename T, typename Allocator>
typename List<T, Allocator>::ConstIterator &List<T, Allocator>::ConstIterator::operator++()
{
    if (_current == nullptr)
    {
        throw std::runtime_error("ConstIterator out of bounds");
    }

    _current = _current->next;
    return *this;
}

template <typename T, typename Allocator>
typename List<T, Allocator>::ConstIterator List<T, Allocator>::ConstIterator::operator++(int notUsed)
{
    auto tmp = *this;
    *++this;
    return tmp;
}

template <typename T, typename Allocator>
bool List<T, Allocator>::ConstIterator::operator==(const List<T, Allocator>::ConstIterator &other) const noexcept
{
    return _current == other._current;
}

template <typename T, typename Allocator>
bool List<T, Allocator>::ConstIterator::operator!=(const List<T, Allocator>::ConstIterator &other) const noexcept
{
    return _current != other._current;
}

template <typename T, typename Allocator>
const T &List<T, Allocator>::ConstIterator::operator*() const
{
    if (_current == nullptr)
    {
        throw std::invalid_argument("Invalid Constiterator pointer");
    }

    return _current->val;
}

template <typename T, typename Allocator>
List<T, Allocator>::List() : _first(nullptr),
                             _last(nullptr),
                             _size(0)
{
}

template <typename T, typename Allocator>
List<T, Allocator>::~List()
{
    clear();
}

template <typename T, typename Allocator>
List<T, Allocator>::List(const List &other)
{
    copy(other);
}

template <typename T, typename Allocator>
List<T, Allocator> &List<T, Allocator>::operator=(const List &other)
{
    if (this != &other)
    {
        clear();
        copy(other);
    }

    return *this;
}

template <typename T, typename Allocator>
List<T, Allocator>::List(List &&other) noexcept
{
    move(std::move(other));
}

template <typename T, typename Allocator>
List<T, Allocator> &List<T, Allocator>::operator=(List &&other) noexcept
{
    if (this != &other)
    {
        clear();
        move(other);
    }

    return *this;
}

template <typename T, typename Allocator>
List<T, Allocator>::Node::Node(T val, typename List<T, Allocator>::Node *next) : val(std::move(val)), next(next)
{
}

template <typename T, typename Allocator>
bool List<T, Allocator>::Empty() const noexcept
{
    return _size == 0;
}

template <typename T, typename Allocator>
std::size_t List<T, Allocator>::Size() const noexcept
{
    return _size;
}

template <typename T, typename Allocator>
void List<T, Allocator>::PushBack(const T &value)
{
    _size++;
    auto tmp = new Node(value, nullptr);
    if (_first == nullptr && _last == nullptr)
    {
        _first = _last = tmp;
        return;
    }

    _last->next = tmp;
    _last = tmp;
}

template <typename T, typename Allocator>
void List<T, Allocator>::PushFront(const T &value)
{
    _size++;
    auto tmp = new Node(value, nullptr);
    if (_first == nullptr)
    {
        _first = _last = tmp;
        return;
    }

    tmp->next = _first;
    _first = tmp;
}

template <typename T, typename Allocator>
void List<T, Allocator>::PopBack()
{
    if (_first == nullptr)
    {
        throw std::runtime_error("Popping from empty list");
    }

    _size--;
    if (_first == _last)
    {
        delete _first;
        _first = _last = nullptr;
        return;
    }

    auto current = _first;
    while (current->next != _last)
    {
        current = current->next;
    }
    delete _last;
    _last = current;
    _last->next = nullptr;
}

template <typename T, typename Allocator>
void List<T, Allocator>::PopFront()
{
    if (_first == nullptr)
    {
        throw std::runtime_error("Popping from empty list");
    }

    _size--;
    auto tmp = _first;
    _first = _first->next;
    delete tmp;

    if (_first == nullptr)
    {
        _last = nullptr;
    }
}

template <typename T, typename Allocator>
typename List<T, Allocator>::Iterator List<T, Allocator>::Insert(const Iterator &it, const T &value)
{
    _size++;
    if (_first == nullptr)
    {
        PushFront(value);
        return begin();
    }

    if (it._current == nullptr)
    {
        PushBack(value);
        return end();
    }

    auto tmp = new Node(value, it._current->next);
    it._current->next = tmp;
    if (it._current == _last)
    {
        _last = tmp;
    }

    return Iterator(tmp);
}

template <typename T, typename Allocator>
typename List<T, Allocator>::Iterator List<T, Allocator>::Insert(const ConstIterator &it, const T &value)
{
    return Insert(Iterator(it._current), value);
}

template <typename T, typename Allocator>
typename List<T, Allocator>::Iterator List<T, Allocator>::Erase(const Iterator &it)
{
    if (it._current == nullptr)
    {
        return end();
    }

    if (_first == nullptr)
    {
        throw std::runtime_error("Poppint from empty list");
    }

    _size--;
    if (it._current == _first)
    {
        PopFront();
        return begin();
    }

    if (it._current == _last)
    {
        PopBack();
        return end();
    }

    auto current = _first;
    while (current->next != it._current)
    {
        current = current->next;
    }

    current->next = it._current->next;
    delete it._current;
    return Iterator(current);
}

template <typename T, typename Allocator>
typename List<T, Allocator>::Iterator List<T, Allocator>::Erase(const ConstIterator &it)
{
    return Erase(Iterator(it._current));
}

template <typename T, typename Allocator>
typename List<T, Allocator>::iterator List<T, Allocator>::begin() const
{
    return Iterator(_first);
}

template <typename T, typename Allocator>
typename List<T, Allocator>::const_iterator List<T, Allocator>::cbegin() const
{
    return ConstIterator(_first);
}

template <typename T, typename Allocator>
typename List<T, Allocator>::iterator List<T, Allocator>::end() const
{
    return Iterator(nullptr);
}

template <typename T, typename Allocator>
typename List<T, Allocator>::const_iterator List<T, Allocator>::cend() const
{
    return ConstIterator(nullptr);
}

template<typename T, typename Allocator>
void List<T, Allocator>::clear() noexcept
{
    while (_first != nullptr)
    {
        auto tmp = _first;
        _first = _first->next;
        delete tmp;
    }
    _size = 0;
}

template<typename T, typename Allocator>
void List<T, Allocator>::copy(const List &other)
{
    auto current = other._first;
    while (current != nullptr)
    {
        PushBack(current->data);
        current = current->next;
    }
}

template<typename T, typename Allocator>
void List<T, Allocator>::move(List &&other) noexcept
{
    _size = other._size;
    _last = std::exchange(other._last, nullptr);
    _first = std::exchange(other._first, nullptr);
}

#endif // LAB5_LIST_H
