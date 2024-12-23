#ifndef __CHART__
#define __CHART__
#include <cstdint>
#include <fstream>
#include <vector>
class Chart {
   public:
    uint16_t width = 0, height = 0;
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
        plot.write((char*)&height, sizeof(uint16_t));

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
        plot.read((char*)&height, sizeof(uint16_t));
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

    ~Chart() { this->Destroy(); }
};
#endif  //!__CHART__
