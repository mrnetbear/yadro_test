#ifndef COMPUTER_CLUB_H
#define COMPUTER_CLUB_H

#include <string>
#include <vector>
#include <map>
#include <queue>
#include <ctime>

struct Time {
    uint32_t hours;
    uint32_t minutes;

    Time() : hours(0), minutes(0) {}
    Time(uint32_t h, uint32_t m) : hours(h), minutes(m) {}

    bool operator < (const Time& other) const;
    bool operator <= (const Time& other) const;
    bool operator > (const Time& other) const;
    bool operator >= (const Time& other) const;
    bool operator == (const Time& other) const;
    
    Time operator + (uint32_t minutes)const;
    uint16_t operator - (const Time& other) const;

    static Time fromString(const std::string& str);
    std::string toString() const;
};

struct Table{
    uint16_t number;
    uint32_t revenue;
    Time occupiedTime = Time(0,0);
    Time lastLaunchTime;
    std::string currentClient;

    Table(int num) : number(num), revenue(0), currentClient("") {}
};

class ComputerClub{
public:
    ComputerClub(uint16_t tablesCount, Time startTime, Time endTime, uint32_t hourCost);

    void processEvent(const Time& time, uint16_t id, const std::vector<std::string>& args);
    void closeClub();

    void printStartTime() const;
    void printResults() const;

private:
    uint16_t tablesCount;
    Time startTime;
    Time endTime;
    uint32_t hourCost;

    std::vector<Table> tables;
    std::map<std::string, uint32_t> clients;
    std::queue<std::string> waitingQueue;

    void clientArrives(const Time& time, const std::string& clientName);
    void clientSits(const Time& time, const std::string& clientName, uint16_t tableNum);
    void clientWaits(const Time& time, const std::string& clientName);
    void clientLeaves(const Time& time, const std::string& clientName);

    void generateError(const Time& time, const std::string& message);
    void clientSitsAtTable(const Time& time, const std::string& clientName, uint16_t tableNum);
    int findFreeTable() const;
    void freeTable(const Time& time, uint16_t tableNum);
    void addRevenue(uint16_t tableNum, const Time& start, const Time& end);
};

#endif //COMPUTER_CLUB_H