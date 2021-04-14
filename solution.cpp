#include <vector>
#include <algorithm>
#include <stack>

#include "Playing_card.h"
#include "Pack.h"
#include "constants.h"

bool BruteForce(std::vector<Pack> &cur_pose) {
    for (size_t j = 0; j < MAX_ITERATIONS; j++) {
        std::sort(cur_pose.begin(), cur_pose.end());
        size_t empty_heaps = 0;
        size_t no_actions = 0;
        for (size_t i = 0; i < number_of_packs - 1; i++) {
            if (cur_pose[i].Empty()) {
                ++empty_heaps;
                ++no_actions;
                continue;
            }

            if (cur_pose[i + 1].Empty() || cur_pose[i].FirstOpen() == cur_pose[i + 1].LastOpen() - 1) {
                cur_pose[i + 1].ShiftOpenCards(cur_pose[i]);
            } else {
                ++no_actions;
            }
        }

        if (no_actions == number_of_packs - 1) {
            return false;
        }

        if (cur_pose[Pack::NUMBER_OF_CARDS_IN_PACK - 1].Empty() && empty_heaps == number_of_packs) {
            return true;
        }
    }

    return false;
}
