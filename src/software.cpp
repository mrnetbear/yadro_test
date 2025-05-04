#include "computer_club.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

std::vector<std::string> split(const std::string& s) {
    std::vector<std::string> result;
    std::istringstream iss(s);
    std::string item;
    
    while (iss >> item) {
        result.push_back(item);
    }
    
    return result;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <input_file>" << std::endl;
        return 1;
    }
    
    std::ifstream inputFile(argv[1]);
    if (!inputFile) {
        std::cerr << "Error: could not open file " << argv[1] << std::endl;
        return 1;
    }
    
    try {
        std::string line;
        
        // Read number of tables
        if (!std::getline(inputFile, line)) throw std::runtime_error("Missing number of tables");
        int tables_count = std::stoi(line);
        if (tables_count <= 0) throw std::runtime_error("Invalid number of tables");
        
        // Read working hours
        if (!std::getline(inputFile, line)) throw std::runtime_error("Missing working hours");
        auto hours_parts = split(line);
        if (hours_parts.size() != 2) throw std::runtime_error("Invalid working hours format");
        Time start_time = Time::fromString(hours_parts[0]);
        Time end_time = Time::fromString(hours_parts[1]);
        
        // Read hour cost
        if (!std::getline(inputFile, line)) throw std::runtime_error("Missing hour cost");
        int hour_cost = std::stoi(line);
        if (hour_cost <= 0) throw std::runtime_error("Invalid hour cost");
        
        ComputerClub club(tables_count, start_time, end_time, hour_cost);
        
        // Process events
        while (std::getline(inputFile, line)) {
            auto parts = split(line);
            if (parts.size() < 2) throw std::runtime_error("Invalid event format");
            
            Time time = Time::fromString(parts[0]);
            int event_id = std::stoi(parts[1]);
            
            std::vector<std::string> args(parts.begin() + 2, parts.end());
            club.processEvent(time, event_id, args);
        }
        
        club.closeClub();
        club.printResults();
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}