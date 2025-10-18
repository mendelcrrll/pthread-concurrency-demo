// File: pthread_donations_demo_target.cc
#include <iostream>
#include <pthread.h>
#include <thread>
#include <chrono>
#include <cstdlib>
#include "printing.h"

// Global shared variable representing total donations
int total_donations = 0;

// Mutex to protect concurrent updates to total_donations
pthread_mutex_t balance_lock;

// Number of donor threads
const int n_donors = 3;

// Donor thread function
void* donor(void* arg) {
    int donor_id = *reinterpret_cast<int*>(arg);

    for(int i = 0; i < 5; ++i) {
        // Lock the mutex to update shared total
        pthread_mutex_lock(&balance_lock);

        // Random donation between 1 and 100
        int donation = rand() % 100 + 1;
        total_donations += donation;

        printing(donor_id, donation, total_donations);

        pthread_mutex_unlock(&balance_lock);

    }
    return nullptr;
}

int main() {
    // Fixed seed for deterministic output
    srand(42);

    // Initialize mutex
    pthread_mutex_init(&balance_lock, nullptr);

    pthread_t donors[n_donors];
    int donor_ids[n_donors] = {1, 2, 3};

    // Create donor threads
    for(int i = 0; i < n_donors; ++i)
        pthread_create(&donors[i], nullptr, donor, (void*)&donor_ids[i]);

    // Join donor threads
    for(int i = 0; i < n_donors; ++i)
        pthread_join(donors[i], nullptr);

    // Final total donations
    std::cout << "Final total donations: $" << total_donations << std::endl;

    pthread_mutex_destroy(&balance_lock);
    return 0;
}
