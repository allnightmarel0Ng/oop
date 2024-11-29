#ifndef LAB7_NPC_H
#define LAB7_NPC_H

#include <string>
#include <sstream>

#include "visitor.h"

class NPC
{

protected:
    explicit NPC(const std::string &name, std::size_t coordX, std::size_t coordY, std::size_t moveRange, std::size_t attackRange);

public:
    virtual ~NPC() = default;

public:
    virtual void Accept(Visitor *visitor) = 0;

    virtual std::size_t GetMoveRange() const noexcept = 0;
    virtual std::size_t GetAttackRange() const noexcept = 0;

    virtual void SetAliveStatus(bool isAlive) noexcept = 0;
    virtual bool GetAliveStatus() const noexcept = 0;

    virtual std::size_t &GetXCoordinate() noexcept = 0;
    virtual std::size_t &GetYCoordinate() noexcept = 0;

    virtual std::string GetName() const noexcept = 0;

    virtual std::string GetDescription() const noexcept = 0;

protected:
    struct Point
    {
        std::size_t x, y;

        explicit Point(std::size_t x, std::size_t y);
    };

protected:
    const std::size_t _moveRange;
    const std::size_t _attackRange;

    const std::string _name;
    bool _isAlive = true;
    Point _place;
};

class Orc: 
    public NPC
{

public:
    explicit Orc(const std::string &name, std::size_t coordX, std::size_t coordY);

public:
    void Accept(Visitor *visitor) override;

    std::size_t GetMoveRange() const noexcept override;
    std::size_t GetAttackRange() const noexcept override;

    void SetAliveStatus(bool isAlive) noexcept override;
    bool GetAliveStatus() const noexcept override;

    std::size_t &GetXCoordinate() noexcept override;
    std::size_t &GetYCoordinate() noexcept override;

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

    std::size_t GetMoveRange() const noexcept override;
    std::size_t GetAttackRange() const noexcept override;

    void SetAliveStatus(bool isAlive) noexcept override;
    bool GetAliveStatus() const noexcept override;

    std::size_t &GetXCoordinate() noexcept override;
    std::size_t &GetYCoordinate() noexcept override;

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

    std::size_t GetMoveRange() const noexcept override;
    std::size_t GetAttackRange() const noexcept override;

    void SetAliveStatus(bool isAlive) noexcept override;
    bool GetAliveStatus() const noexcept override;

    std::size_t &GetXCoordinate() noexcept override;
    std::size_t &GetYCoordinate() noexcept override;

    std::string GetName() const noexcept override;

    std::string GetDescription() const noexcept override;
};

#endif