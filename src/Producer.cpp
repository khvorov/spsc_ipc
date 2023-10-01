#include "Types.h"

#include <iostream>
#include <string>
#include <thread>

#include <unistd.h>

int main(int argc, char* argv[]) {
    size_t count = 0;

    try {
        if (argc != 2) {
            throw std::invalid_argument("Usage: Producer <number of elements>");
        }

        count = std::stoull(argv[1]);
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return -1;
    }

    bip::managed_shared_memory segment(bip::open_or_create, "MySharedMemory", 65536);
    shm::RingBuffer* queue = segment.find_or_construct<shm::RingBuffer>("queue")();

    for (; count; --count) {
        auto now = shm::Now();
        while (!queue->push(now)) {
            // sleep a bit if queue is full and consumer is slow
            ::usleep(1);
        }
    }

    // indicate to consumer that we are done
    queue->push(-1);

    return 0;
}
