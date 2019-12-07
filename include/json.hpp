// Copyright 2018 Your Name <your_email>

#pragma once

#include <string>
#include <experimental/any>
#include <vector>
#include <map>
#include <exception>

class WrongJson : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;
};

//using namespace std::experimental;

class Json {
    std::vector<std::experimental::any> getArray(const std::string &s, unsigned int start) const;

    std::map<std::string, std::experimental::any> getObject(const std::string &s, unsigned int start) const;

    std::vector<std::experimental::any> array;
    std::map<std::string, std::experimental::any> object;
public:
    // Пустой конструктор
    Json() = default;

    // Конструктор из строки, содержащей Json-данные.
    Json(const std::string &s);

    // Метод возвращает true, если данный экземпляр содержит в себе JSON-массив. Иначе false.
    bool is_array() const;

    // Метод возвращает true, если данный экземпляр содержит в себе JSON-объект. Иначе false.
    bool is_object() const;

    bool is_empty() const;

    size_t getArrSize() const;

    // Метод возвращает значение по ключу key, если экземпляр является JSON-объектом.
    // Значение может иметь один из следующих типов: Json, std::string, double, bool или быть пустым.
    // Если экземпляр является JSON-массивом, генерируется исключение.
    std::experimental::any &operator[](const std::string &key);

    // Метод возвращает значение по индексу index, если экземпляр является JSON-массивом.
    // Значение может иметь один из следующих типов: Json, std::string, double, bool или быть пустым.
    // Если экземпляр является JSON-объектом, генерируется исключение.
    std::experimental::any &operator[](int index);

    // Метод возвращает объект класса Json из строки, содержащей Json-данные.
    static Json parse(const std::string &s);

    // Метод возвращает объекта класса Json из файла, содержащего Json-данные в текстовом формате.
    static Json parseFile(const std::string &path_to_file);
};

