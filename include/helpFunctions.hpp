// Copyright 2018 Your Name <your_email>

#pragma once

#include <sstream>
#include <iostream>


bool isSpace(char ch) {
    return ch == ' ' || ch == '\n' || ch == '\r' || ch == '\t';
}

int findEnd(const std::string &s, int start, char openSym, char closeSym) {

    int i = 0;
    int openC = 1;
    int closeC = 0;
    for (unsigned int j = start + 1; j < s.length(); j++) {
        char symbol = s[j];
        if (symbol == openSym) {
            openC++;
        } else if (symbol == closeSym) {
            closeC++;
        }
        if (openC == closeC) {
            i = j;
            break;
        }
    }
    return i + 1;
}

int missSpaces(const std::string &s, unsigned int current) {
    while (current < s.length() && isSpace(s[current])) {
        ++current;
    }
    return current;
}

std::string getString(const std::string &s, unsigned int start) {
    unsigned int end = start + 1;
    while (end < s.length() && s[end] != '\"') {
        ++end;
    }
    if (end >= s.length()) {
        throw std::exception();
    }
    return s.substr(start + 1, end - start - 1);
}

bool isNum(char c) {
    return ((c > '0') && (c < '9')) || (c == '.');
}

std::pair<double, unsigned int> getNumAndLen(const std::string &s, unsigned int start) {
    double result;
    unsigned int cur = start;
    while (cur < s.length() && isNum(s[cur])) {
        ++cur;
    }
    if (cur == s.length()) {
        throw std::exception();
    }
    std::stringstream ss;
    std::string str = s.substr(start, cur - start);
    ss << str;
    ss >> result;

    return std::pair<double, unsigned int>(result, cur - start);
}
