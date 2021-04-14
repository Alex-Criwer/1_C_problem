#ifndef INC_1_C_PROBLEM_PLAYING_CARD_H
#define INC_1_C_PROBLEM_PLAYING_CARD_H

#include <iostream>

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


#endif //INC_1_C_PROBLEM_PLAYING_CARD_H
