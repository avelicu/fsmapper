//
// config_option.cpp
//  Author: Hiroshi Murayama <opiopan@gmail.com>
//

#include "config_option.h"
#include <algorithm>

ConfigOption::ConfigOption(const std::string& key, const std::string& description, const std::vector<std::string>& choices) :
    key(key), description(description), choices(choices) {
    if (!choices.empty()) {
        value = choices[0];
    }
}

bool ConfigOption::setValue(const std::string& newValue) {
    if (value != newValue) {
        // Ensure the new value is one of the choices
        auto it = std::find(choices.begin(), choices.end(), newValue);
        if (it != choices.end()) {
            value = newValue;
            notifyListeners();
            return true;
        }
    }
    return false;
}

void ConfigOption::addListener(ChangeListener listener) {
    listeners.push_back(listener);
}

void ConfigOption::notifyListeners() {
    for (const auto& listener : listeners) {
        listener(value);
    }
}
