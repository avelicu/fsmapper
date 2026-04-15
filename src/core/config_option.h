//
// config_option.h
//  Author: Hiroshi Murayama <opiopan@gmail.com>
//

#pragma once

#include <string>
#include <vector>
#include <memory>
#include <functional>

class ConfigOption {
public:
    using ChangeListener = std::function<void(const std::string& newValue)>;

    ConfigOption(const std::string& key, const std::string& description, const std::vector<std::string>& choices);
    ~ConfigOption() = default;

    const std::string& getKey() const { return key; }
    const std::string& getDescription() const { return description; }
    const std::vector<std::string>& getChoices() const { return choices; }
    const std::string& getValue() const { return value; }
    
    bool setValue(const std::string& newValue); // Returns true if changed
    
    void addListener(ChangeListener listener);
    void notifyListeners();

private:
    std::string key;
    std::string description;
    std::vector<std::string> choices;
    std::string value;
    std::vector<ChangeListener> listeners;
};

using ConfigOptionPtr = std::shared_ptr<ConfigOption>;
