#include "data.h"

#include <fstream>

int GameData::score_;
int GameData::high_score_;
bool GameData::game_over_;
bool GameData::game_won_;
bool GameData::load_game_;
std::list<int> GameData::rank_;

namespace {

template <typename T>
inline void WriteStream(std::ostream &os, const T &data) {
    os.write(reinterpret_cast<const char *>(&data), sizeof(T));
}

template <typename T>
inline void ReadStream(std::istream &is, T &data) {
    is.read(reinterpret_cast<char *>(&data), sizeof(T));
}

} // namespace

void GameData::SaveGame(GameStatus &&status) {
    // fill 'fixed_data'
    status.fixed_data.score = score_;
    // save status to file
    using namespace std;
    ofstream ofs(kDataPath, ios::binary | ios::ate | ios::in);
    ofs.seekp(kRankMaxSize * sizeof(int));
    WriteStream(ofs, status.fixed_data);
    WriteStream(ofs, status.enemy_status.size());
    for (const auto &i : status.enemy_status) {
        WriteStream(ofs, i);
    }
}

GameStatus GameData::LoadGame() {
    GameStatus status;
    std::ifstream ifs(kDataPath, std::ios::binary);
    ifs.seekg(kRankMaxSize * sizeof(int));
    ReadStream(ifs, status.fixed_data);
    // read 'fixed_data'
    score_ = status.fixed_data.score;
    // read enemy status
    decltype(status.enemy_status.size()) count;
    ReadStream(ifs, count);
    for (int i = 0; i < count; ++i) {
        GameStatus::EnemyStatus enemy_status;
        ReadStream(ifs, enemy_status);
        status.enemy_status.push_back(enemy_status);
    }
    return status;
}

void GameData::SaveData() {
    using namespace std;
    ofstream ofs(kDataPath, ios::binary | ios::ate | ios::in);
    ofs.seekp(0);
    int count = kRankMaxSize;
    for (const auto &i : rank_) {
        WriteStream(ofs, i);
        --count;
    }
    while (count--) {
        int i = 0;
        WriteStream(ofs, i);
    }
}

void GameData::LoadData() {
    std::ifstream ifs(kDataPath, std::ios::binary);
    for (int i = 0; i < kRankMaxSize; ++i) {
        int temp = 0;
        ReadStream(ifs, temp);
        rank_.push_back(temp);
    }
    high_score_ = rank_.front();
}
