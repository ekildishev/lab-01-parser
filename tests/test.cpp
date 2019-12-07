// Copyright 2018 Your Name <your_email>

#include <gtest/gtest.h>
#include "json.hpp"


TEST(Json, Example1) {
    Json object = Json::parse(R"(
        {
            "lastname" : "Ivanov",
            "firstname" : "Ivan",
            "age" : 25,
            "islegal" : false,
            "marks" : [
                4,5,5,5,2,3
            ],
            "address" : {
                "city" : "Moscow",
                "street" : "Vozdvijenka"
            }
        }
    )");
    EXPECT_EQ(std::experimental::any_cast
                      <std::string>(object["lastname"]), "Ivanov");
    EXPECT_EQ(std::experimental::any_cast<bool>(object["islegal"]), false);
    EXPECT_EQ(std::experimental::any_cast<double>(object["age"]), 25);

    Json marks = std::experimental::any_cast<Json>(object["marks"]);
    EXPECT_EQ(std::experimental::any_cast<double>(marks[0]), 4);
    EXPECT_EQ(std::experimental::any_cast<double>(marks[1]), 5);

    Json address = std::experimental::any_cast<Json>(object["address"]);
    EXPECT_EQ(std::experimental::any_cast
                      <std::string>(address["city"]), "Moscow");
    EXPECT_EQ(std::experimental::any_cast
                      <std::string>(address["street"]), "Vozdvijenka");
}

TEST(Json, EmptyJson) {

    Json some{};
    EXPECT_EQ(some.is_object(), false);
    EXPECT_EQ(some.is_array(), false);
    EXPECT_EQ(some.is_empty(), true);
}


TEST(JsonArray, SimpleArray) {
    Json json{"[ 73 ]"};
    EXPECT_EQ(json.is_object(), false);
    EXPECT_EQ(json.is_array(), true);
    EXPECT_EQ(json.is_empty(), false);

    EXPECT_EQ(std::experimental::any_cast<double>(json[0]), 73.);
}

TEST(JsonArray, Array) {
    Json json{"[73, \"abc\", true]"};
    EXPECT_EQ(json.is_object(), false);
    EXPECT_EQ(json.is_array(), true);
    EXPECT_EQ(json.is_empty(), false);

    EXPECT_EQ(std::experimental::any_cast<double>(json[0]), 73);
    EXPECT_EQ(std::experimental::any_cast<std::string>(json[1]), "abc");
    EXPECT_EQ(std::experimental::any_cast<bool>(json[2]), true);
}

TEST(Json, Exception) {
    Json some{};
    EXPECT_THROW(some[1], WrongJson);
}

