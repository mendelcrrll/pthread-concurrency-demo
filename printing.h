// printing.h
#pragma once
#include <iostream>
#include <thread>
#include <chrono>
#include <cstdlib>

// Prints the donor's contribution and current total.
// Includes a short sleep to simulate real-world delays and interleaving.
inline void printing(int donor_id, int donation, int total_donations) {
    std::cout << "[Donor " << donor_id << "] donated $" << donation
              << " | Total: $" << total_donations << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 50 + 10));
}
