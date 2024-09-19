#include "octal.h"

Octal::Octal():
    _size(1), _array(new unsigned char[_size * sizeof(unsigned char)])
{
    std::memset(_array, 0, _size * sizeof(unsigned char));
}

Octal::Octal(const std::initializer_list<unsigned char> &value):
    _size(value.size())
{
    if (_size == 0)
    {
        _size = 1;
        _array = new unsigned char[_size * sizeof(unsigned char)];
        std::memset(_array, 0, _size * sizeof(unsigned char));
        return;
    }

    _array = new unsigned char[_size * sizeof(unsigned char)];

    size_t index = 0;
    for (auto const &digit: value)
    {
        if (digit > 7)
        {
            throw std::invalid_argument("Not an octal digit");
        }

        _array[_size - index - 1] = digit;
        index++;
    }

    while (_size > 1 && _array[_size - 1] == 0)
    {
        _size--;
    }
}

Octal::Octal(const std::string &value):
    _size(value.size())
{
    if (_size == 0)
    {
        _size = 1;
        _array = new unsigned char[_size * sizeof(unsigned char)];
        std::memset(_array, 0, _size * sizeof(unsigned char));
        return;
    }

    _array = new unsigned char[_size * sizeof(unsigned char)];

    size_t index = 0;
    for (auto const &digit: value)
    {
        if (digit > '7' || digit < '0')
        {
            throw std::invalid_argument("Not an octal digit");
        }

        _array[_size - index - 1] = digit - '0';
        index++;
    }

    while (_size > 1 && _array[_size - 1] == 0)
    {
        _size--;
    }
}

Octal::~Octal() noexcept
{
    clear();
}

Octal::Octal(const Octal &other)
{
    copyFrom(other);
}

Octal &Octal::operator=(const Octal &other)
{
    if (this != &other)
    {
        clear();
        copyFrom(other);
    }

    return *this;
}

Octal::Octal(Octal &&other) noexcept
{
    moveFrom(std::move(other));
}

Octal &Octal::operator=(Octal &&other) noexcept
{
    if (this != &other)
    {
        clear();
        moveFrom(std::move(other));
    }

    return *this;
}

Octal &Octal::operator+=(const Octal &other)
{
    std::size_t resultSize = std::max(_size, other._size) + 1;
    auto result = new unsigned char[resultSize * sizeof(unsigned char)];

    unsigned char carry = 0;
    for (std::size_t i = 0; i < resultSize - 1; i++)
    {
        unsigned char sum = getDigit(i) + other.getDigit(i) + carry;
        result[i] = sum % BASE;
        carry = sum / BASE;
    }

    result[resultSize - 1] = carry;

    while (resultSize > 1 && result[resultSize - 1] == 0)
    {
        resultSize--;
    }

    clear();
    initializeFrom(result, resultSize);

    return *this;
}

Octal Octal::operator+(const Octal &other) const
{
    return Octal(*this) += other;
}

Octal &Octal::operator-=(const Octal &other)
{
    if (other > *this)
    {
        throw std::invalid_argument("Octal class represents unsigned octal number");
    }

    std::size_t resultSize = _size;
    auto result = new unsigned char[resultSize * sizeof(unsigned char)];

    unsigned char borrow = 0;
    for (std::size_t i = 0; i < resultSize; i++)
    {
        char diff = getDigit(i) - other.getDigit(i) - borrow;
        if (diff < 0)
        {
            diff += BASE;
            borrow = 1;
        }
        else
        {
            borrow = 0;
        }

        result[i] = diff;
    }

    while (resultSize > 1 && result[resultSize - 1] == 0)
    {
        resultSize--;
    }

    clear();
    initializeFrom(result, resultSize);

    return *this;
}

Octal Octal::operator-(const Octal &other) const
{
    return Octal(*this) -= other;
}

bool Octal::operator==(const Octal &other) const
{
    if (_size != other._size)
    {
        return false;
    }

    for (size_t i = 0; i < _size; ++i)
    {
        if (getDigit(i) != other.getDigit(i))
        {
            return false;
        }
    }

    return true;
}

bool Octal::operator!=(const Octal &other) const
{
    return !(*this == other);
}

bool Octal::operator<(const Octal &other) const
{
    if (_size != other._size)
    {
        return _size < other._size;
    }

    for (int i = _size - 1; i >= 0; --i)
    {
        auto lhsDigit = getDigit(i);
        auto rhsDigit = other.getDigit(i);

        if (lhsDigit != rhsDigit)
        {
            return lhsDigit < rhsDigit;
        }
    }

    return false;
}

bool Octal::operator>(const Octal &other) const
{
    return !(*this < other || *this == other);
}

bool Octal::operator<=(const Octal &other) const
{
    return !(*this > other);
}

bool Octal::operator>=(const Octal &other) const
{
    return !(*this < other);
}

std::ostream &operator<<(std::ostream &os, const Octal &value)
{
    for (int i = value._size - 1; i >= 0; --i)
    {
        os << static_cast<int>(value.getDigit(i));
    }

    return os;
}

void Octal::clear() noexcept
{
    _size = 0;
    delete[] _array;
}

void Octal::copyFrom(const Octal &other)
{
    _size = other._size;
    _array = new unsigned char[_size * sizeof(unsigned char)];
    std::memcpy(_array, other._array, _size * sizeof(unsigned char));
}

void Octal::moveFrom(Octal &&other) noexcept
{
    _size = other._size;
    _array = std::exchange(other._array, nullptr);
}

unsigned char Octal::getDigit(std::size_t index) const noexcept
{
    return index < _size ? _array[index] : 0;
}

void Octal::initializeFrom(unsigned char *array, std::size_t size)
{
    _size = size;
    _array = new unsigned char[_size * sizeof(unsigned char)];
    std::memcpy(_array, array, _size * sizeof(unsigned char));
}
