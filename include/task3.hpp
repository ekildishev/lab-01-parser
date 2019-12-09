// Copyright 2018 Your Name <your_email>

#pragma once

#include <iostream>
#include <sstream>
#include "json.hpp"

Json Transform(const std::string &s) {
    Json data(s);

    if (!data.is_array()) {
        throw std::exception();
    }
    if (data.getArrSize() != 3) {
        throw std::exception();
    }
    std::stringstream ss;

    size_t size = std::experimental::any_cast<Json>(data[0]).getArrSize();
    if (size != std::experimental::any_cast<Json>(data[1]).getArrSize() ||
        size != std::experimental::any_cast<Json>(data[2]).getArrSize()) {
        throw std::exception();
    }
    ss << "[";
    for (size_t i = 0; i < size; ++i) {
        ss << "{";
        ss << "\"ticker\":\"" << std::experimental::any_cast<std::string>(std::experimental::any_cast<Json>(data[0])[i])
           << "\",";
        ss << "\"id\":" << std::experimental::any_cast<double>(std::experimental::any_cast<Json>(data[1])[i]) << ",";
        ss << "\"description\":\""
           << std::experimental::any_cast<std::string>(std::experimental::any_cast<Json>(data[2])[i]) << "\"";
        ss << "}";

        if (i != size - 1)
            ss << ",";
    }
    ss << "]";
    std::string str;
    getline(ss, str);
    return Json(str);
}
