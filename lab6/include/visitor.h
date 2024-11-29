#ifndef LAB6_VISITOR_H
#define LAB6_VISITOR_H

#include <vector>

#include "observer.h"

class Visitor
{

public:
    explicit Visitor() = default;
    virtual ~Visitor() = default;

public:
    virtual void Visit(Orc &ref) noexcept = 0;
    virtual void Visit(Squirrel &ref) noexcept = 0;
    virtual void Visit(Bear &ref) noexcept = 0;
};

class Fighter: 
    public Visitor
{

public:
    explicit Fighter(std::vector<std::vector<Cell>> &field, const std::vector<std::shared_ptr<Observer>> &observers);

public:
    void Visit(Orc &ref) noexcept override;
    void Visit(Squirrel &ref) noexcept override;
    void Visit(Bear &ref) noexcept override;

private:
    void notify(const Cell &killer, const Cell &victim) const noexcept;

private:
    std::vector<std::vector<Cell>> &_field;
    const std::vector<std::shared_ptr<Observer>> _observers;
};

#endif