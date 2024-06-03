#ifndef SG_DATA_H_
#define SG_DATA_H_

#include <string>
#include <list>
#include <vector>

#include "gamedef.h"

// game status that need to be saved
struct GameStatus {
    bool is_valid;
    struct {
        int hp, fuel, score, enemy_count;
        int player_x, player_y;
    } fixed_data;
    struct EnemyStatus {
        int x, y;
    };
    std::vector<EnemyStatus> enemy_status;
};

// game data manager class
class GameData {
public:
    static void SaveGame(GameStatus&& status);
    static GameStatus LoadGame();
    static void SaveData();
    static void LoadData();

    static GameStatus NewGame() {
        game_over_ = false;
        game_won_ = false;
        if (load_game_) {
            auto status = LoadGame();
            load_game_ = false;
            status.is_valid = true;
            return status;
        }
        else {
            score_ = kInitScore;
            return { false };
        }
    }

    static void LoadGameNextTime() {
        load_game_ = true;//再次载入之前的游戏
    }

    static void IncreaseScore() {
        score_=score_+5;
    }

   
    static int score() { return score_; }
    static int high_score() { return high_score_; }
    static bool game_over() { return game_over_; }
    static bool game_won() { return game_won_; }
    static const std::list<int>& rank() { return rank_; }

private:
    static void UpdateRank() {
        if (rank_.empty()) {
            rank_.push_back(score_);
        }
        else {
            for (auto it = rank_.begin(); it != rank_.end(); ++it) {
                if (score_ > * it) {
                    rank_.insert(it, score_);
                    if (rank_.size() > kRankMaxSize) {
                        rank_.pop_back();
                    }
                    return;
                }
            }
        }
        high_score_ = rank_.front();
    }

    static int score_, high_score_;
    static bool game_over_, game_won_, load_game_;
    static std::list<int> rank_;
};

#endif // SG_DATA_H_
