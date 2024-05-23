#ifndef INC_2024_I2P2_TOWERDEFENSE_WITH_ANSWER_SCOREBOARDSCENE_H
#define INC_2024_I2P2_TOWERDEFENSE_WITH_ANSWER_SCOREBOARDSCENE_H

#include <allegro5/allegro_audio.h>
#include <memory>
#include "Engine/IScene.hpp"

class Date {
public:
    int year;
    int month;
    int day;

    // format: yyyy-mm-dd
    Date(const std::string& date) {
        if(date == "NaN") {
            year = month = day = 0;
            return;
        }

        char year_str[] = {date[0], date[1], date[2], date[3], '\0'};
        char month_str[] = {date[5], date[6], '\0'};
        char day_str[] = {date[8], date[9], '\0'};

        year = atoi(year_str);
        month = atoi(month_str);
        day = atoi(day_str);
    }

    bool operator==(Date b) {
        return year == b.year && month == b.month && day == b.day;
    }

    bool operator<(Date b) {
        if(year == b.year) {
            if(month == b.month) return day < b.day;
            else return month < b.month;
        }
        else return year < b.year;
    }

    bool operator>(Date b) {
        if(year == b.year) {
            if(month == b.month) return day > b.day;
            else return month > b.month;
        }
        else return year > b.year;
    }

};

class ScoreboardScene final : public Engine::IScene {
    public:
    struct ScoreData {
        std::string name;
        int score;
        int life;
        int time_spent;
        Date date;
    };

    explicit ScoreboardScene() = default;
    void Initialize() override;
    void Terminate() override;
    void BackOnClick(int stage);

    // return a vector array of ScoreData's (unsorted)
    std::vector<struct ScoreData> getScoresFromTxt(const std::string& file_path);
};
#endif //INC_2024_I2P2_TOWERDEFENSE_WITH_ANSWER_SCOREBOARDSCENE_H
