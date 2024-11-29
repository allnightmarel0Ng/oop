#ifndef LAB2_OCTAL_H
#define LAB2_OCTAL_H

#include <string>
#include <iostream>
#include <cstring>
#include <utility>

class Octal
{

public:
    Octal();
    Octal(const std::initializer_list<unsigned char> &values);
    Octal(const std::string &value);

public:
    virtual ~Octal() noexcept;
    Octal(const Octal &other);
    Octal &operator=(const Octal &other);
    Octal(Octal &&other) noexcept;
    Octal &operator=(Octal &&other) noexcept;

public:
    Octal &operator+=(const Octal &other);
    Octal operator+(const Octal &other) const;
    Octal &operator-=(Octal const &other);
    Octal operator-(Octal const &other) const;

public:
    bool operator==(Octal const &other) const;
    bool operator!=(Octal const &other) const;

public:
    bool operator<(Octal const &other) const;
    bool operator>(Octal const &other) const;
    bool operator<=(Octal const &other) const;
    bool operator>=(Octal const &other) const;

public:
    friend std::ostream &operator<<(std::ostream &os, const Octal &value);

private:
    void clear() noexcept;
    void copyFrom(const Octal &other);
    void moveFrom(Octal &&other) noexcept;

private:
    unsigned char getDigit(std::size_t index) const noexcept;
    void initializeFrom(unsigned char *array, std::size_t size);

private:
    std::size_t _size;
    unsigned char *_array;
    const static unsigned char BASE = 8;

};

#endif //LAB2_OCTAL_H
