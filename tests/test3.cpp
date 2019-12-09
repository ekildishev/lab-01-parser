// Copyright 2018 Your Name <your_email>

#include <gtest/gtest.h>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

TEST(Json, task3) {
    json empty_array = json::array();
    json my_json = json::array({
                                       {"Si-9.15", "RTS-9.15", "GAZP-9.15"},
                                       {100024, 100027, 100050},
                                       {"Futures contract for USD/RUB", "Futures contract for index RTS",
                                                               "Futures contract for Gazprom shares"}
                               });
    size_t count = 0;
    for (size_t j = 0; j < my_json.begin()->size(); ++j) {
        count = 0;
        json temp = json::object();
        for (size_t i = 0; i < my_json.size(); ++i, ++count) {
            switch (count) {
                case 0:
                    temp["ticker"] = my_json[i][j];
                    break;
                case 1:
                    temp["id"] = my_json[i][j];
                    break;
                case 2:
                    temp["description"] = my_json[i][j];
                    break;
                default:
                    break;
            }
        }
        empty_array.push_back(temp);
    }
    my_json = empty_array;
    EXPECT_EQ(my_json[0]["ticker"], "Si-9.15");
    EXPECT_EQ(my_json[1]["ticker"], "RTS-9.15");
    EXPECT_EQ(my_json[2]["ticker"], "GAZP-9.15");
    EXPECT_EQ(my_json[0]["id"], 100024);
    EXPECT_EQ(my_json[1]["id"], 100027);
    EXPECT_EQ(my_json[2]["id"], 100050);
    EXPECT_EQ(my_json[0]["description"], "Futures contract for USD/RUB");
    EXPECT_EQ(my_json[1]["description"], "Futures contract for index RTS");
    EXPECT_EQ(my_json[2]["description"], "Futures contract for Gazprom shares");
}
