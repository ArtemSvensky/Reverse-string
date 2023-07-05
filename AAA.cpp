#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cctype>

class String {
public:
    
    String() : data(nullptr), size(0) {}

    String(const char* str) {
        size = std::strlen(str);
        data = new char[size + 1];
        std::strcpy(data, str);
    }

    String(const String& other) {
        size = other.size;
        data = new char[size + 1];
        std::strcpy(data, other.data);
    }

    String(String&& other) noexcept {
        size = other.size;
        data = other.data;
        other.data = nullptr;
        other.size = 0;
    }

    ~String() {
        delete[] data;
    }

    String& operator=(const String& other) {
        if (this != &other) {
            delete[] data;
            size = other.size;
            data = new char[size + 1];
            std::strcpy(data, other.data);
        }
        return *this;
    }

    String& operator=(String&& other) noexcept {
        if (this != &other) {
            delete[] data;
            size = other.size;
            data = other.data;
            other.data = nullptr;
            other.size = 0;
        }
        return *this;
    }

    String& operator+=(const String& other) {
        char* temp = new char[size + other.size + 1];
        std::strcpy(temp, data);
        std::strcat(temp, other.data);
        delete[] data;
        data = temp;
        size += other.size;
        return *this;
    }

    String operator+(const String& other) const {
        String result;
        result.size = size + other.size;
        result.data = new char[result.size + 1];
        std::strcpy(result.data, data);
        std::strcat(result.data, other.data);
        return result;
    }

    String reverse() const {
        String result;
        result.size = size;
        result.data = new char[size + 1];
        for (int i = 0; i < size; ++i) {
            result.data[i] = data[size - i - 1];
        }
        result.data[size] = '\0';
        return result;
    }

    const char* c_str() const {
        return data;
    }

private:
    char* data;
    int size;
};

String operator+(const String& lhs, const char* rhs) {
    String temp(rhs);
    return lhs + temp;
}

String operator+(const char* lhs, const String& rhs) {
    String temp(lhs);
    return temp + rhs;
}

String operator+(const String& lhs, const String& rhs) {
    String result(lhs);
    result += rhs;
    return result;
}

int main(int argc, char** argv) {
    std::cout << "Please enter the strings (press Enter after each string). To stop, enter an empty line:\n";

    std::string input;
    std::vector<String> strings;
    while (std::getline(std::cin, input) && !input.empty()) {
        strings.push_back(input.c_str());
    }

    std::sort(strings.rbegin(), strings.rend(), [](const String& a, const String& b) {
        const char* str1 = a.c_str();
        const char* str2 = b.c_str();
        while (*str1 && *str2) {
            char c1 = std::tolower(*str1);
            char c2 = std::tolower(*str2);
            if (c1 != c2)
                return c1 < c2;
            ++str1;
            ++str2;
        }
        return *str1 == '\0' && *str2 != '\0';
    });

    for (const auto& str : strings) {
        std::cout << str.reverse().c_str() << '\n';
    }

    return 0;
}

