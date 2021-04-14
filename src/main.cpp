#include <iostream>
#include <deque>
#include <vector>
#include <algorithm>
#include <stack>

const size_t number_of_packs = 8;
const size_t MAX_ITERATIONS = 100000;

class Playing_card {
public:
    enum Card {
        FIVE = 5,  //canary
        SIX = 6,
        SEVEN = 7,
        EIGHT = 8,
        NINE = 9,
        TEN = 10,
        JACK = 11,
        LADY = 12,
        KING = 13,
        ACE = 14,
        FREE = 15  //canary
    };

    bool operator<(const Playing_card &card) {
        return card_ < card.card_;
    }

    bool operator==(const Playing_card &card) {
        return card_ == card.card_;
    }

    Playing_card operator-(int i) {
        return card_ - 1;
    }

    friend std::ostream &operator<<(std::ostream &os, const Playing_card &playing_card);

    friend std::istream &operator>>(std::istream &is, Playing_card &playing_card);

    void SetOpen() {
        is_open_ = true;
    }

    bool IsOpen() {
        return is_open_;
    }

    Playing_card() = default;

private:
    Playing_card(size_t card) : card_(static_cast<Card>(card)) {}

    Card card_;
    bool is_open_ = false;
};


class Pack {
public:

    Playing_card FirstOpen() {
        return first_open_;
    }

    Playing_card LastOpen() {
        return pack_.back();
    }

    static const size_t NUMBER_OF_CARDS_IN_PACK = 9;

    friend std::ostream &operator<<(std::ostream &os, const Pack &pack);

    friend std::istream &operator>>(std::istream &is, Pack &pack);

    bool operator<(const Pack &pack) {
        return pack.Empty() || pack_.back() < pack.pack_.back();
    }

    void ShiftOpenCards(Pack &pack) {
        auto open_cards = pack.GetOpenCards();
        while (!open_cards.empty()) {
            pack_.push_back(open_cards.top());
            open_cards.pop();
            open_cards_++;
        }
    }

    std::stack<Playing_card> GetOpenCards() {
        std::stack<Playing_card> stack_of_open_values;
        size_t size = open_cards_;
        open_cards_ = 0;
        for (size_t i = 0; i < size; i++) {
            stack_of_open_values.push(pack_.back());
            pack_.pop_back();
        }

        if (!pack_.empty()) {
            pack_.back().SetOpen();
            first_open_ = pack_.back();
            open_cards_++;
        }

        return stack_of_open_values;
    }

    bool Empty() const {
        return !open_cards_;
    }

private:
    std::deque<Playing_card> pack_;
    size_t open_cards_ = 1;
    Playing_card first_open_;

    void PrintStack(std::ostream &os, std::deque<Playing_card> &stack) const {
        if (stack.empty()) {
            return;
        }

        auto tmp = stack.back();
        stack.pop_back();
        PrintStack(os, stack);
        if (tmp.IsOpen()) {
            os << tmp << "op ";
        } else {
            os << tmp << " ";
        }

    }
};

bool Perebor(std::vector<Pack> &cur_pose) {
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

int main() {

    std::vector<Pack> packs;
    for (size_t i = 0; i < number_of_packs; ++i) {
        Pack pack_at_the_moment;
        std::cin >> pack_at_the_moment;
        packs.push_back(pack_at_the_moment);
    }

    std::cout << (Perebor(packs) ? "Win" : "Loose") << "\n";
    for (size_t i = 0; i < number_of_packs; ++i) {
        std::cout << packs[i];
    }
}


std::ostream &operator<<(std::ostream &os, const Playing_card &playing_card) {
    os << playing_card.card_;
    return os;
}

std::istream &operator>>(std::istream &is, Playing_card &playing_card) {
    int in;
    is >> in;
    playing_card.card_ = static_cast<Playing_card::Card>(in);
    return is;
}

std::ostream &operator<<(std::ostream &os, const Pack &pack) {
    std::deque<Playing_card> saver_stack = pack.pack_;
    pack.PrintStack(os, saver_stack);
    os << "\n";
    return os;
}

std::istream &operator>>(std::istream &is, Pack &pack) {
    Playing_card card;

    for (size_t i = 0; i < Pack::NUMBER_OF_CARDS_IN_PACK; ++i) {
        is >> card;
        pack.pack_.push_back(card);

        if (i == Pack::NUMBER_OF_CARDS_IN_PACK - 1) {
            pack.pack_.back().SetOpen();
            pack.first_open_ = pack.pack_.back();
        }
    }
    return is;
}