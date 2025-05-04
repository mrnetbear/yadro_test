#include "computer_club.hpp"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <algorithm>

bool Time::operator <(const Time& other) const{
    return this->hours < other.hours || (hours == other.hours && minutes < other.minutes);
}
bool Time::operator == (const Time& other) const{
    return this->hours == other.hours && this->minutes == other.minutes;
}
bool Time::operator <=(const Time& other) const{
    return (*this < other) || (*this == other);
}
bool Time::operator >(const Time& other) const{
    return !(*this <= other);
}
bool Time::operator >= (const Time& other) const{
    return !(*this < other); 
}

Time Time::operator + (uint32_t minutes) const{
    uint32_t totalMinutes = this->hours * 60 + this->minutes + minutes;
    return Time(totalMinutes / 60 % 24, totalMinutes % 60);
}

uint16_t Time::operator-(const Time& other) const {
    return (hours - other.hours) * 60 + (minutes - other.minutes);
}

Time Time::fromString(const std::string& str) {
    size_t colonPos = str.find(':');
    if (colonPos == std::string::npos || colonPos == 0 || colonPos == str.length() - 1) {
        throw std::invalid_argument("Invalid time format");
    }
    
    uint32_t h = std::stoi(str.substr(0, colonPos));
    uint32_t m = std::stoi(str.substr(colonPos + 1));
    
    if (h < 0 || h > 23 || m < 0 || m > 59) {
        throw std::invalid_argument("Invalid time value");
    }
    
    return Time(h, m);
}

std::string Time::toString() const {
    std::ostringstream oss;
    oss << std::setw(2) << std::setfill('0') << hours << ":"
        << std::setw(2) << std::setfill('0') << minutes;
    return oss.str();
}

ComputerClub::ComputerClub(uint16_t tablesCount, Time startTime, Time endTime, uint32_t hourCost)
    : tablesCount(tablesCount), startTime(startTime), endTime(endTime), hourCost(hourCost) {
    for (size_t i = 1; i <= tablesCount; ++i) {
        tables.emplace_back(i);
    }
}

void ComputerClub::processEvent(const Time& time, uint16_t id, const std::vector<std::string>& args) {
    std::cout << time.toString() << " " << id;
    for (const auto& arg : args) {
        std::cout << " " << arg;
    }
    std::cout << std::endl;
    
    switch (id) {
        case 1: clientArrives(time, args[0]); break;
        case 2: clientSits(time, args[0], std::stoi(args[1])); break;
        case 3: clientWaits(time, args[0]); break;
        case 4: clientLeaves(time, args[0]); break;
        default: throw std::invalid_argument("Unknown event ID");
    }
}

void ComputerClub::closeClub() {
    std::vector<std::string> remainingClients;
    for (const auto& client : clients) {
        if (client.second != 0) { // Not in queue
            remainingClients.push_back(client.first);
        }
    }
    
    std::sort(remainingClients.begin(), remainingClients.end());
    
    for (const auto& client : remainingClients) {
        std::cout << endTime.toString() << " 11 " << client << std::endl;
        freeTable(endTime, clients[client]);
        clients.erase(client);
    }
}

void ComputerClub::printResults() const {
    std::cout << startTime.toString() << std::endl;
    
    for (const auto& table : tables) {
        std::cout << table.number << " " << table.revenue << " " << table.occupiedTime.toString() << std::endl;
    }
}

void ComputerClub::clientArrives(const Time& time, const std::string& clientName) {
    if (time < startTime || time >= endTime) {
        generateError(time, "NotOpenYet");
        return;
    }
    
    if (clients.find(clientName) != clients.end()) {
        generateError(time, "YouShallNotPass");
        return;
    }
    
    clients[clientName] = 0; // 0 means not at any table
}

void ComputerClub::clientSits(const Time& time, const std::string& clientName, uint16_t tableNum) {
    if (clients.find(clientName) == clients.end()) {
        generateError(time, "ClientUnknown");
        return;
    }
    
    if (tableNum < 1 || tableNum > tablesCount) {
        generateError(time, "PlaceIsBusy"); // Assuming invalid table number is treated as busy
        return;
    }
    
    if (tables[tableNum - 1].currentClient != "") {
        generateError(time, "PlaceIsBusy");
        return;
    }
    
    // If client was sitting at another table, free it
    if (clients[clientName] != 0) {
        freeTable(time, clients[clientName]);
    }
    
    clientSitsAtTable(time, clientName, tableNum);
}

void ComputerClub::clientWaits(const Time& time, const std::string& clientName) {
    if (clients.find(clientName) == clients.end()) {
        generateError(time, "ClientUnknown");
        return;
    }
    
    if (findFreeTable() != -1) {
        generateError(time, "ICanWaitNoLonger!");
        return;
    }
    
    if (waitingQueue.size() >= tablesCount) {
        std::cout << time.toString() << " 11 " << clientName << std::endl;
        clients.erase(clientName);
        return;
    }
    
    waitingQueue.push(clientName);
    clients[clientName] = 0; // Mark as waiting
}

void ComputerClub::clientLeaves(const Time& time, const std::string& clientName) {
    if (clients.find(clientName) == clients.end()) {
        generateError(time, "ClientUnknown");
        return;
    }
    
    uint16_t tableNum = clients[clientName];
    if (tableNum == 0) {
        // Client was in queue, just remove
        std::queue<std::string> tempQueue;
        while (!waitingQueue.empty()) {
            if (waitingQueue.front() != clientName) {
                tempQueue.push(waitingQueue.front());
            }
            waitingQueue.pop();
        }
        waitingQueue = tempQueue;
    } else {
        freeTable(time, tableNum);
    }
    
    clients.erase(clientName);
}

void ComputerClub::generateError(const Time& time, const std::string& message) {
    std::cout << time.toString() << " 13 " << message << std::endl;
}

void ComputerClub::clientSitsAtTable(const Time& time, const std::string& clientName, uint16_t tableNum) {
    tables[tableNum - 1].currentClient = clientName;
    tables[tableNum - 1].occupiedTime = time;
    clients[clientName] = tableNum;
}

int ComputerClub::findFreeTable() const {
    for (const auto& table : tables) {
        if (table.currentClient.empty()) {
            return table.number;
        }
    }
    return -1;
}

void ComputerClub::freeTable(const Time& time, uint16_t tableNum) {
    Table& table = tables[tableNum - 1];
    if (table.currentClient.empty()) return;
    
    addRevenue(tableNum, table.occupiedTime, time);
    table.currentClient.clear();
    
    if (!waitingQueue.empty()) {
        std::string nextClient = waitingQueue.front();
        waitingQueue.pop();
        clientSitsAtTable(time, nextClient, tableNum);
        std::cout << time.toString() << " 12 " << nextClient << " " << tableNum << std::endl;
    }
}

void ComputerClub::addRevenue(uint16_t tableNum, const Time& start, const Time& end) {
    int minutes = end - start;
    int hours = minutes / 60;
    if (minutes % 60 != 0) hours++;
    
    tables[tableNum - 1].revenue += hours * hourCost;
    tables[tableNum - 1].occupiedTime = Time(hours, minutes % 60);
}