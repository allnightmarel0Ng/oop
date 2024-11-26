#ifndef LAB6_COMMON_H
#define LAB6_COMMON_H

#include <atomic>
#include <cstddef>
#include <string>
#include <sstream>
#include <thread>
#include <memory>
#include <mutex>
#include <fstream>
#include <vector>
#include <iostream>
#include <shared_mutex>
#include <queue>

class NPC;
class Orc;
class Squirrel;
class Bear;

struct Cell
{
    enum class Type: std::uint8_t
    {
        Orc,
        Squirrel,
        Bear,
        Empty
    };

    Type CellType;
    std::shared_ptr<NPC> Object;

    Cell(Cell::Type type = Cell::Type::Empty, std::shared_ptr<NPC> &&object = nullptr);
};

class Observer
{

public:
    virtual void HandleEvent(const Cell &killer, const Cell &victim) noexcept = 0;

protected:
    static inline std::string CellTypeToString(Cell::Type type) noexcept;
};

class FileLogger : public Observer
{

public:
    explicit FileLogger() = default;

public:
    void HandleEvent(const Cell &killer, const Cell &victim) noexcept override;

private:
    std::ofstream ofs = std::ofstream("logs.txt", std::ios::out);
};

class ConsoleLogger : public Observer
{

public:
    explicit ConsoleLogger() = default;

public:
    void HandleEvent(const Cell &killer, const Cell &victim) noexcept override;
};

class Visitor
{

public:
    explicit Visitor() = default;
    virtual ~Visitor() = default;

public:
    virtual bool Visit(Orc &ref) noexcept = 0;
    virtual bool Visit(Squirrel &ref) noexcept = 0;
    virtual bool Visit(Bear &ref) noexcept = 0;
};

class Fighter : public Visitor
{

public:
    explicit Fighter(std::vector<std::vector<Cell>> &field, const std::vector<std::shared_ptr<Observer>> &observers, std::mutex &fieldMutex);

public:
    bool Visit(Orc &ref) noexcept override;
    bool Visit(Squirrel &ref) noexcept override;
    bool Visit(Bear &ref) noexcept override;

public:
    void operator()();

private:
    void move(NPC *ptr, std::size_t &x, std::size_t &y);
    void notify(const Cell &killer, const Cell &victim) const noexcept;

private:
    struct Fight
    {
        Cell &attacker, &defender;
    };    

private:
    std::atomic<bool> &_run;
    std::mutex &_mutex;
    std::queue<Fight> _fights;
    std::vector<std::vector<Cell>> &_field;
    const std::vector<std::shared_ptr<Observer>> _observers;
};

class NPC
{

protected:
    explicit NPC(const std::string &name, std::size_t coordX, std::size_t coordY, std::size_t moveRange, std::size_t attackRange);

public:
    virtual ~NPC() = default;

public:
    virtual bool Accept(Visitor *visitor) = 0;

    // virtual void SetAttackRange(std::size_t attackRange) noexcept = 0;
    virtual std::size_t GetMoveRange() const noexcept = 0;
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
    const std::size_t _moveRange;
    const std::size_t _attackRange;

    const std::string _name;
    bool _isAlive = true;
    const Point _place;
};

class Orc : public NPC
{

public:
    explicit Orc(const std::string &name, std::size_t coordX, std::size_t coordY);

public:
    bool Accept(Visitor *visitor) override;

    // void SetAttackRange(std::size_t attackRange) noexcept override;
    std::size_t GetMoveRange() const noexcept override;
    std::size_t GetAttackRange() const noexcept override;

    void SetAliveStatus(bool isAlive) noexcept override;
    bool GetAliveStatus() const noexcept override;

    std::size_t GetXCoordinate() const noexcept override;
    std::size_t GetYCoordinate() const noexcept override;

    std::string GetName() const noexcept override;

    std::string GetDescription() const noexcept override;

};

class Squirrel : public NPC
{

public:
    explicit Squirrel(const std::string &name, std::size_t coordX, std::size_t coordY);

public:
    bool Accept(Visitor *visitor) override;

    // void SetAttackRange(std::size_t attackRange) noexcept override;
    std::size_t GetMoveRange() const noexcept override;
    std::size_t GetAttackRange() const noexcept override;

    void SetAliveStatus(bool isAlive) noexcept override;
    bool GetAliveStatus() const noexcept override;

    std::size_t GetXCoordinate() const noexcept override;
    std::size_t GetYCoordinate() const noexcept override;

    std::string GetName() const noexcept override;

    std::string GetDescription() const noexcept override;

};

class Bear : public NPC
{

public:
    explicit Bear(const std::string &name, std::size_t coordX, std::size_t coordY);

public:
    bool Accept(Visitor *visitor) override;

    // void SetAttackRange(std::size_t attackRange) noexcept override;
    std::size_t GetMoveRange() const noexcept override;
    std::size_t GetAttackRange() const noexcept override;

    void SetAliveStatus(bool isAlive) noexcept override;
    bool GetAliveStatus() const noexcept override;

    std::size_t GetXCoordinate() const noexcept override;
    std::size_t GetYCoordinate() const noexcept override;

    std::string GetName() const noexcept override;

    std::string GetDescription() const noexcept override;
};

class Factory
{

public:
    Factory() = delete;

public:
    static Cell CreateNPC(const std::string &description);

private:
    static std::vector<std::string> tokenize(const std::string &description) noexcept;

};

class GameHandler
{

    using Field = std::vector<std::vector<Cell>>;

public:
    explicit GameHandler() = delete;

// public:
//     static void Game(std::istream &is, std::ostream &os);

// private:
//     static void HandleAddNPC(std::istream &is, std::vector<std::vector<Cell>> &field);
//     static void HandleLoadFile(const std::string &filepath, std::vector<std::vector<Cell>> &field);
//     static void PrintObjects(std::ostream &os, const std::vector<std::vector<Cell>> &field) noexcept;
//     static void HandleSaveFile(const std::string &filepath, const std::vector<std::vector<Cell>> &field) noexcept;
//     static void HandleFight(const std::unique_ptr<Visitor> &visitor, std::vector<std::vector<Cell>> &field, std::size_t attackRange) noexcept;
//     static void PrintMenu() noexcept;

public:
    static void Game(std::size_t size);
};

#endif