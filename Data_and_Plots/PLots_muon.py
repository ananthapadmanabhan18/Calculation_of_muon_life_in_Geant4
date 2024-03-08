
#include <iostream>
#include <fstream>
#include <vector>
int main() {
    std::ifstream inputFile("c:\\Users\\apmna\\OneDrive\\Documents\\GitHub\\Calculation_of_muon_life_in_Geant4\\Data_and_Plots\\Real_Data\\650_196.5.data");
    std::vector<std::string> secondColumn;
    if (inputFile.is_open()) {
        std::string line;
        while (std::getline(inputFile, line)) {
            std::istringstream iss(line);
            std::string column1, column2;
            if (iss >> column1 >> column2) {
                secondColumn.push_back(column2);
            }
        }
        inputFile.close();
    } else {
        std::cout << "Failed to open the file." << std::endl;
        return 1;
    }
    // Use the secondColumn vector as needed
    return 0;
}

