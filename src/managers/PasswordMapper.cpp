//
// Created by Volodymyr on 5/11/2023.
//

#include "PasswordMapper.h"
#include "ProgramManager.h"
#include <regex>

auto PasswordMapper::mapStringToPsw(const std::string &line) -> Password {
    auto dDotVec = strSplitTrim(line, ":");
    if (dDotVec.size() < 2 || dDotVec.size() > 4) return {};

    auto name = dDotVec[0];
    auto password = dDotVec[1];
    auto website = std::string();
    auto login = std::string();
    if (dDotVec.size() > 2) website = dDotVec[2];
    if (dDotVec.size() > 3) login = dDotVec[3];

    auto mappedPassword = Password(name, password);
    mappedPassword.setWebsite(website);
    mappedPassword.setLogin(login);

    return mappedPassword;
}

auto PasswordMapper::strSplit(const std::string &string, const std::string &delim) -> std::vector<std::string> {
    auto regex = std::regex(delim);
    auto dashIter = std::sregex_token_iterator(string.begin(), string.end(), regex, -1);
    auto dashIterEnd = std::sregex_token_iterator();
    return std::vector<std::string>{dashIter, dashIterEnd};
}

auto PasswordMapper::strSplitTrim(const std::string &str, const std::string &delim) -> std::vector<std::string> {
    auto valueVec = strSplit(str, delim);
    for (auto &el: valueVec) trim(el);
    return valueVec;
}

auto PasswordMapper::leftTrim(std::string &s) -> void {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
        return !std::isspace(ch);
    }));
}

auto PasswordMapper::rightTrim(std::string &s) -> void {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
    }).base(), s.end());
}

auto PasswordMapper::trim(std::string &s) -> void {
    rightTrim(s);
    leftTrim(s);
}