#pragma once

#include <utility>
#include <vector>
#include <chrono>

class path
{
public:

    struct point{
        long millis;
        int x;
        int y;
    };

    path();
    ~path();

    void add_raw(long time_millis, int x, int y);
    int size();

    std::chrono::milliseconds absolute_milliseconds();
    std::chrono::milliseconds current_milliseconds();

private:
    std::vector< point > m_pairs;
    std::chrono::milliseconds m_current_ms;
};