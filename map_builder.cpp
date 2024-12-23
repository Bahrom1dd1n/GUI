#include <strings.h>

#include <cstdint>
#include <cstdio>
#include <fstream>
#include <ios>
#include <iostream>
#include <vector>

class Chart {
   public:
    uint16_t width = 0, length = 0;
    struct SpotBlock {
        inline SpotBlock() = default;
        inline SpotBlock(uint16_t start_index, uint16_t x, uint16_t y, uint16_t size, uint8_t car_type,
                         bool orientation)
            : start_index(start_index), x(x), y(y), size(size), car_type(car_type), orientation(orientation) {}
        uint16_t start_index = 0;
        uint16_t x = 0;
        uint16_t y = 0;
        uint16_t size = 0;
        uint8_t car_type = 2;
        bool orientation = 0;
    };
    std::vector<std::vector<SpotBlock*>*> floors;
    Chart() = default;
    Chart(const char* chart_path) { this->Load(chart_path); }

    inline void AddFloor() { this->floors.push_back(new std::vector<SpotBlock*>); };
    void Save(const char* chart_path) {
        std::ofstream plot(chart_path, std::ios::out | std::ios::binary | std::ios::trunc);
        plot.write((char*)&width, sizeof(uint16_t));
        plot.write((char*)&length, sizeof(uint16_t));

        uint16_t n = floors.size();
        plot.write((char*)&n, sizeof(uint16_t));
        for (auto i : floors) {
            n = i->size();
            plot.write((char*)&n, sizeof(uint16_t));
            for (auto sp : *i) {
                plot.write((char*)sp, sizeof(SpotBlock));
            }
        }
    }

    void Destroy() {
        for (auto i : floors) {
            for (auto y : *i) delete y;
            delete i;
        }
    }

    bool Load(const char* chart_path) {
        this->Destroy();
        std::ifstream plot(chart_path, std::ios::in | std::ios::binary);
        if (!plot) {
            return false;
        }

        plot.read((char*)&width, sizeof(uint16_t));
        plot.read((char*)&length, sizeof(uint16_t));
        uint16_t n = 0;
        plot.read((char*)&n, sizeof(uint16_t));
        floors.resize(n);
        for (int i = 0; i < n; i++) {
            uint16_t w = 0, h = 0;
            auto* fl = new std::vector<SpotBlock*>;
            floors[i] = fl;
            plot.read((char*)&w, sizeof(uint16_t));
            while (w) {
                Chart::SpotBlock* sp = new SpotBlock;
                plot.read((char*)sp, sizeof(Chart::SpotBlock));
                fl->push_back(sp);
                w--;
            }
        }
        return true;
    }
    void Display() const {
        if (floors.empty()) {
            std::cout << "No floors added yet.\n";
            return;
        }
    }
    ~Chart() { this->Destroy(); }
};
void AddFloorOption(Chart& chart) {
    chart.AddFloor();
    std::cout << "Floor added successfully.\n";
}

void AddSpotOption(Chart& chart) {
    if (chart.floors.empty()) {
        std::cout << "No floors available. Add a floor first.\n";
        return;
    }

    uint16_t floor_index, start_index, x, y, size;
    uint16_t car_type;
    bool orientation;

    std::cout << "Enter floor index (0 to " << chart.floors.size() - 1 << "): ";
    std::cin >> floor_index;

    if (floor_index >= chart.floors.size()) {
        std::cout << "Invalid floor index.\n";
        return;
    }
    std::cout << " Enter start index of Spot: ";
    std::cin >> start_index;
    std::cout << "Enter spot X: ";
    std::cin >> x;
    std::cout << "Enter spot Y: ";
    std::cin >> y;
    std::cout << "Enter spot size: ";
    std::cin >> size;
    std::cout << "Enter car type (0-255): ";
    std::cin >> car_type;
    std::cout << "Enter orientation (0 for horizontal, 1 for vertical): ";
    std::cin >> orientation;

    chart.floors[floor_index]->push_back(new Chart::SpotBlock(start_index, x, y, size, car_type, orientation));
    std::cout << "Parking spot added successfully.\n";
}

void SaveChartOption(Chart& chart) {
    std::string filename;
    std::cout << "Enter file name to save chart: ";
    std::cin >> filename;
    chart.Save(filename.c_str());
    std::cout << "Chart saved to " << filename << ".\n";
}

void DisplayChartOption(const Chart& chart) {
    chart.Display();
}
// Function to load the chart
void LoadChartOption(Chart& chart) {
    std::string filename;
    std::cout << "Enter file name to load chart: ";
    std::cin >> filename;
    if (chart.Load(filename.c_str()))
        std::cout << " ---> Successfully Loaded <---" << std::endl;
    else
        std::cout << " ---> Failed to Load <---" << std::endl;
}

// Function to change parking spot properties

void ChangeSpotProperties(Chart& chart) {
    if (chart.floors.empty()) {
        std::cout << "No floors available. Add a floor and spots first.\n";
        return;
    }

    uint16_t floor_index;
    std::cout << "Enter floor index (0 to " << chart.floors.size() - 1 << "): ";
    std::cin >> floor_index;

    if (floor_index >= chart.floors.size()) {
        std::cout << "Invalid floor index.\n";
        return;
    }

    auto& spots = chart.floors[floor_index];
    if (spots->empty()) {
        std::cout << "No spots available on this floor.\n";
        return;
    }

    uint16_t spot_index;
    std::cout << "Enter spot index (0 to " << spots->size() - 1 << "): ";
    std::cin >> spot_index;

    if (spot_index >= spots->size()) {
        std::cout << "Invalid spot index.\n";
        return;
    }

    Chart::SpotBlock* spot = (*spots)[spot_index];
    bool done = false;

    while (!done) {
        std::cout << "\n--- Modify Parking Spot Properties ---\n";
        std::cout << "1. Change X\n";
        std::cout << "2. Change Y\n";
        std::cout << "3. Change Size\n";
        std::cout << "4. Change Car Type\n";
        std::cout << "5. Change Orientation\n";
        std::cout << "6. Done\n";
        std::cout << "Enter your choice: ";
        int choice;
        std::cin >> choice;

        switch (choice) {
            case 1:
                std::cout << "Enter new X: ";
                std::cin >> spot->x;
                std::cout << "X updated successfully.\n";
                break;
            case 2:
                std::cout << "Enter new Y: ";
                std::cin >> spot->y;
                std::cout << "Y updated successfully.\n";
                break;
            case 3:
                std::cout << "Enter new size: ";
                std::cin >> spot->size;
                std::cout << "Size updated successfully.\n";
                break;
            case 4: {
                std::cout << "Enter new car type (0-255): ";
                uint16_t car_type = 0;
                std::cin >> car_type;
                spot->car_type = car_type;
                std::cout << "Car type updated successfully.\n";
                break;
            }
            case 5:
                std::cout << "Enter new orientation (0 for horizontal, 1 for vertical): ";
                std::cin >> spot->orientation;
                std::cout << "Orientation updated successfully.\n";
                break;
            case 6:
                done = true;
                break;
            default:
                std::cout << "Invalid choice. Try again.\n";
        }
    }
}

// Display menu
void DisplayMenu() {
    std::cout << "\n--- Parking Chart Menu ---\n";
    std::cout << "1. Add Floor\n";
    std::cout << "2. Add Block of Parking Spots\n";
    std::cout << "3. Save Chart\n";
    std::cout << "4. Load Chart\n";
    std::cout << "5. Change Parking Spot Properties\n";
    std::cout << "6. Display Chart\n";
    std::cout << "7. Set width of the Building\n";
    std::cout << "8. Set length of the Building\n";
    std::cout << "9. Exit\n";
    std::cout << "Enter your choice: ";
}
void ChangeAll(Chart& chart) {
    for (auto i : *chart.floors[0]) i->car_type = 3;
    for (auto i : *chart.floors[1]) i->car_type = 2;
}
int main() {
    Chart chart;
    bool running = true;

    while (running) {
        DisplayMenu();
        int choice;
        std::cin >> choice;

        switch (choice) {
            case 1:
                AddFloorOption(chart);
                break;
            case 2:
                AddSpotOption(chart);
                break;
            case 3:
                SaveChartOption(chart);
                break;
            case 4:
                LoadChartOption(chart);
                break;
            case 5:
                ChangeSpotProperties(chart);
                break;
            case 6:
                DisplayChartOption(chart);
                break;
            case 7: {
                uint16_t width;
                std::cout << " Enter new width: ";
                std::cin >> width;
                chart.width = width;
                break;
            }
            case 8: {
                uint16_t length;
                std::cout << " Enter new length: ";
                std::cin >> length;
                chart.length = length;
                break;
            }
            case 9:
                running = false;
                break;
            case 10:
                ChangeAll(chart);
                break;
            default:
                std::cout << "Invalid choice. Try again.\n";
        }
    }

    return 0;
}
