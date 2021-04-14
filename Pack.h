#ifndef INC_1_C_PROBLEM_PACK_H
#define INC_1_C_PROBLEM_PACK_H

#include <iostream>

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

    void PrintPack(std::ostream &os, std::deque<Playing_card> &stack) const {
        if (stack.empty()) {
            return;
        }

        auto tmp = stack.back();
        stack.pop_back();
        PrintPack(os, stack);
        if (tmp.IsOpen()) {
            os << tmp << "op ";
        } else {
            os << tmp << " ";
        }

    }
};

std::ostream &operator<<(std::ostream &os, const Pack &pack) {
    std::deque<Playing_card> saver_stack = pack.pack_;
    pack.PrintPack(os, saver_stack);
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

#endif //INC_1_C_PROBLEM_PACK_H
