#include <iostream>
#include <sstream>
#include <vector>
#include <utility>  // For pair
#include <fstream>  // For file operations
#include <string>
#include <ctime>    // For current date and time
#include <filesystem>




#ifdef _WIN32
#include <direct.h> // For mkdir on Windows
#define mkdir _mkdir
#else
#include <sys/stat.h> // For mkdir on Unix/Linux
#include <sys/types.h>
#endif


std::string getCurrentDate() {
    time_t now = time(nullptr);
    char buffer[160];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d_(%H:%M)", localtime(&now));
    return buffer;
}

// Function to convert a pair<int, int> to string
std::string pairToString(const std::pair<int, int>& p) {
    std::stringstream ss;
    ss << "(" << p.first << "," << p.second << ")";
    return ss.str();
}

// Function to convert a vector<int> to string
std::string vectorToString(const std::vector<int>& vec) {
    std::stringstream ss;
    ss << "[";
    for (size_t i = 0; i < vec.size(); ++i) {
        ss << vec[i];
        if (i != vec.size() - 1) {
            ss << ",";
        }
    }
    ss << "]";
    return ss.str();
}

// Function to convert a vector<vector<int>> to string
std::string vectorOfVectorsToString(const std::vector<std::vector<int>>& vec) {
    std::stringstream ss;
    ss << "[";
    for (size_t i = 0; i < vec.size(); ++i) {
        ss << vectorToString(vec[i]);
        if (i != vec.size() - 1) {
            ss << ",";
        }
    }
    ss << "]";
    return ss.str();
}

// Function to convert the entire game state to a unique string representation
std::string gameStateToString(GameState *gp) {
    std::stringstream ss;

    ss << "player1:" << (gp->player1 ? "true" : "false") << ",";
    ss << "size:" << gp->size << ",";
    ss << "num_walls:" << gp->num_walls << ",";
    ss << "walls_dim:" << gp->walls_dim << ",";
    ss << "player1_pos:" << pairToString(gp->player1_pos) << ",";
    ss << "player2_pos:" << pairToString(gp->player2_pos) << ",";
    ss << "walls_per_player:" << pairToString(gp->walls_per_player) << ",";
    ss << "ver_walls:" << vectorToString(gp->ver_walls) << ",";
    ss << "hor_walls:" << vectorToString(gp->hor_walls) << ",";
    ss << "player1_walls:" << vectorToString(gp->player1_walls) << ",";
    ss << "player2_walls:" << vectorToString(gp->player2_walls) << ",";
    ss << "saved_wall_placements:" << vectorOfVectorsToString(gp->saved_wall_placements) << ",";

    return ss.str();
}

int logGame(std::string currentDate, std::string p1, std::string p2, std::string data, int round) {
    std::string folderName = "/" + currentDate + "_(" + p1 + " | " + p2 + ")";

    std::string prevFold = "../saved_games/";

    // Create directory/folder
    // #ifdef _WIN32
    // if (_mkdir(folderName.c_str()) != 0) {
    // #else
    std::filesystem::create_directories(prevFold + folderName);

    // Create and write to a file inside the directory
    std::string filePath = prevFold + folderName + "/round_" + std::to_string(round) + ".txt";
    std::ofstream outFile(filePath);
    if (!outFile) {
        std::cerr << "Error creating file: " << filePath << std::endl;
        return 1;
    }

    // Write some content to the file
    outFile << data << std::endl;
    outFile.close();

    std::cout << "Successfully created folder '" << folderName << "' and wrote file for round " << std::to_string(round) << std::endl;

    return 0;
}