#ifndef LAB6_NPC_H
#define LAB6_NPC_H

#include <sstream>

#include "visitor.h"

class NPC
{

public:
    explicit NPC(const std::string &name, std::size_t coordX, std::size_t coordY);
    virtual ~NPC() = default;

public:
    virtual void Accept(Visitor *visitor) = 0;

    virtual void SetAttackRange(std::size_t attackRange) noexcept = 0;
    virtual std::size_t GetAttackRange() const noexcept = 0;

    virtual void SetAliveStatus(bool isAlive) noexcept = 0;
    virtual bool GetAliveStatus() const noexcept = 0;

    virtual std::size_t GetXCoordinate() const noexcept = 0;
    virtual std::size_t GetYCoordinate() const noexcept = 0;

    virtual std::string GetName() const noexcept = 0;

    virtual std::string GetDescription() const noexcept = 0;

protected:
    struct Point
    {
        std::size_t x, y;

        explicit Point(std::size_t x, std::size_t y);
    };

protected:
    std::size_t _attackRange = 0;
    const std::string _name;
    bool _isAlive = true;
    const Point _place;
};

class Orc: 
    public NPC
{

public:
    explicit Orc(const std::string &name, std::size_t coordX, std::size_t coordY);

public:
    void Accept(Visitor *visitor) override;

    void SetAttackRange(std::size_t attackRange) noexcept override;
    std::size_t GetAttackRange() const noexcept override;

    void SetAliveStatus(bool isAlive) noexcept override;
    bool GetAliveStatus() const noexcept override;

    std::size_t GetXCoordinate() const noexcept override;
    std::size_t GetYCoordinate() const noexcept override;

    std::string GetName() const noexcept override;

    std::string GetDescription() const noexcept override;
};

class Squirrel: 
    public NPC
{

public:
    explicit Squirrel(const std::string &name, std::size_t coordX, std::size_t coordY);

public:
    void Accept(Visitor *visitor) override;

    void SetAttackRange(std::size_t attackRange) noexcept override;
    std::size_t GetAttackRange() const noexcept override;

    void SetAliveStatus(bool isAlive) noexcept override;
    bool GetAliveStatus() const noexcept override;

    std::size_t GetXCoordinate() const noexcept override;
    std::size_t GetYCoordinate() const noexcept override;

    std::string GetName() const noexcept override;

    std::string GetDescription() const noexcept override;
};

class Bear: 
    public NPC
{

public:
    explicit Bear(const std::string &name, std::size_t coordX, std::size_t coordY);

public:
    void Accept(Visitor *visitor) override;

    void SetAttackRange(std::size_t attackRange) noexcept override;
    std::size_t GetAttackRange() const noexcept override;

    void SetAliveStatus(bool isAlive) noexcept override;
    bool GetAliveStatus() const noexcept override;

    std::size_t GetXCoordinate() const noexcept override;
    std::size_t GetYCoordinate() const noexcept override;

    std::string GetName() const noexcept override;

    std::string GetDescription() const noexcept override;
};

#endif