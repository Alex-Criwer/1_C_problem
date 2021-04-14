#include <iostream>
#include <deque>

#include "solution.cpp"


int main() {

    std::vector<Pack> packs;
    for (size_t i = 0; i < number_of_packs; ++i) {
        Pack pack_at_the_moment;
        std::cin >> pack_at_the_moment;
        packs.push_back(pack_at_the_moment);
    }

    std::cout << (BruteForce(packs) ? "Win" : "Loose") << "\n";
    for (size_t i = 0; i < number_of_packs; ++i) {
        std::cout << packs[i];
    }
}




