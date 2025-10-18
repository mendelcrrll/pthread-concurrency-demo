// File: pthread_donations_demo_raw.cc
#include <iostream>
#include <pthread.h>
#include <thread>
#include <chrono>
#include <cstdlib>
#include "printing.h"

int total_donations = 0;
pthread_mutex_t balance_lock;
const int n_donors = 3;

void* donor(void* arg) {
    int donor_id = *reinterpret_cast<int*>(arg);
    for(int i = 0; i < 5; ++i) {
        int donation = rand() % 100 + 1;
        total_donations += donation;
        printing(donor_id, donation, total_donations);
    }
    return nullptr;
}

int main() {
    srand(42);
    pthread_mutex_init(&balance_lock, nullptr);
    pthread_t donors[n_donors];
    int donor_ids[n_donors] = {1, 2, 3};
    for(int i = 0; i < n_donors; ++i)
        pthread_create(&donors[i], nullptr, donor, (void*)&donor_ids[i]);
    for(int i = 0; i < n_donors; ++i)
        pthread_join(donors[i], nullptr);
    std::cout << "Final total donations: $" << total_donations << std::endl;
    pthread_mutex_destroy(&balance_lock);
    return 0;
}
