// Copyright 2018 Your Name <your_email>

#include <iostream>

#include "helpFunctions.hpp"
#include "json.hpp"

Json::Json(const std::string &s) {
  int i = 0;
  i = missSpaces(s, i);

  if (s[i] == '{') {
    object = getObject(s, i + 1);
  } else if (s[i] == '[') {
    array = getArray(s, i + 1);
  } else {
    throw WrongJson("Illegal string!");
  }
}

bool Json::is_array() const { return !array.empty(); }

bool Json::is_object() const { return !object.empty(); }

bool Json::is_empty() const { return object.empty() && array.empty(); }

size_t Json::getArrSize() const {
  if (is_array()) {
    return array.size();
  } else {
    throw WrongJson("It is not an array!");
  }
}

std::pair<std::experimental::any, unsigned int> getValueAndLen(
    const std::string &s, unsigned int start) {
  std::experimental::any result;
  unsigned int i = start;
  unsigned int endObj = 0;

  if (s[i] == '{') {
    endObj = findEnd(s, i, '{', '}');
    std::string str = s.substr(i, endObj - i);
    result = Json(str);
    i = endObj;
  } else if (s[i] == '[') {
    endObj = findEnd(s, i, '[', ']');
    std::string str = s.substr(i, endObj - i);
    result = Json(str);
    i = endObj;
  } else if (s[i] == '\"') {
    std::string str = getString(s, i);
    i += str.length() + 2;
    result = str;
  } else if (isNum(s[i])) {
    std::pair<std::experimental::any, unsigned int> p = getNumAndLen(s, i);
    i += p.second;
    result = p.first;
  } else if (s.substr(i, 5) == "false") {
    i += 5;
    result = false;
  } else if (s.substr(i, 4) == "true") {
    i += 4;
    result = true;
  } else if (s.substr(i, 4) == "null") {
    i += 4;
    result = nullptr;
  } else {
    throw WrongJson("Illegal string!");
  }

  return std::pair<std::experimental::any, unsigned int>(result, i - start);
}

std::experimental::any &Json::operator[](const std::string &key) {
  if (is_object()) {
    return object[key];
  }
  throw WrongJson("It is not an object!");
}

std::experimental::any &Json::operator[](int index) {
  if (is_array()) {
    return array[index];
  }
  throw WrongJson("It is not an array!");
}

Json Json::parse(const std::string &s) { return Json(s); }

std::vector<std::experimental::any> Json::getArray(const std::string &s,
                                                   unsigned int start) const {
  std::vector<std::experimental::any> result;
  unsigned int i = start;

  while (i < s.length()) {
    i = missSpaces(s, i);
    std::pair<std::experimental::any, int> p = getValueAndLen(s, i);

    i += p.second;
    result.push_back(p.first);

    i = missSpaces(s, i);
    if (s[i] == ']') {
      break;
    }
    if (s[i++] == ',') {
      continue;
    }
    throw WrongJson("Illegal string!");
  }

  return result;
}

std::map<std::string, std::experimental::any> Json::getObject(
    const std::string &s, unsigned int start) const {
  std::map<std::string, std::experimental::any> result;
  unsigned int i = start;
  while (i < s.length()) {
    i = missSpaces(s, i);
    if (s[i] != '\"') {
      throw WrongJson("Illegal string!");
    }
    std::string key = getString(s, i);
    i += key.length() + 2;
    i = missSpaces(s, i);
    if (s[i++] != ':') {
      throw WrongJson("Illegal string!");
    }
    i = missSpaces(s, i);
    std::pair<std::experimental::any, unsigned int> p = getValueAndLen(s, i);
    result[key] = p.first;
    i += p.second;
    i = missSpaces(s, i);
    if (s[i] == '}') {
      break;
    }
    if (s[i++] == ',') {
      continue;
    }
    throw WrongJson("Illegal string!");
  }
  return result;
}
