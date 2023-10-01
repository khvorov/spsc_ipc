#include "Types.h"

#include <iostream>
#include <tuple>
#include <vector>

int main() {
    bip::managed_shared_memory segment(bip::open_or_create, "MySharedMemory", 65536);
    shm::RingBuffer* queue = segment.find_or_construct<shm::RingBuffer>("queue")();

    std::vector<std::tuple<int64_t, size_t>> results;
    results.reserve(1000000);

    while (true) {
        if (int64_t v; queue->pop(v)) {
            if (v == -1) {
                break;
            }

            int64_t now = shm::Now();
            results.emplace_back(now - v, queue->read_available());
        }
    }

    for (auto [latency, count] : results) {
        std::cout << latency << ',' << count << std::endl;
    }
}
