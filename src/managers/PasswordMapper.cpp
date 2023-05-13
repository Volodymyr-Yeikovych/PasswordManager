//
// Created by Volodymyr on 5/11/2023.
//

#include "PasswordMapper.h"
#include "ProgramManager.h"
#include "fmt/core.h"
#include "fmt/ranges.h"
#include <regex>

auto PasswordMapper::mapFileEntryToPassword(const std::string &line) -> Password {
    auto dDotVec = strSplitTrim(line, ":");
    if (dDotVec.size() < 3 || dDotVec.size() > 5) return {};

    auto name = dDotVec[0];
    auto password = dDotVec[1];
    auto website = std::string();
    auto login = std::string();
    if (dDotVec.size() > 3) website = dDotVec[3];
    if (dDotVec.size() > 4) login = dDotVec[4];

    auto mappedPassword = Password(name, password);
    mappedPassword.setWebsite(website);
    mappedPassword.setLogin(login);

    return mappedPassword;
}

auto PasswordMapper::mapTextToCategoryVec(const std::string &text) -> std::vector<Category> {
    auto categoryVec = std::vector<Category>();
    auto lCurSplit = PasswordMapper::strSplitTrim(text, "\\{");
    auto saveCatName = lCurSplit[0];
    for (int i = 1; i < lCurSplit.size(); i++) {
        auto lastIter = i + 1 == lCurSplit.size();
        auto rCurSplit = PasswordMapper::strSplitTrim(lCurSplit[i], "\\}");
        if (rCurSplit.size() != 2 && !(rCurSplit.size() == 1 && lastIter))
            throw std::runtime_error("Error: invalid file format. Impossible to parse {1}.");
        auto stringPasswords = PasswordMapper::strSplitTrim(rCurSplit[0], ";");
        auto passVec = std::vector<Password>();
        for (const auto &entry: stringPasswords) {
            auto entrySplit = PasswordMapper::strSplitTrim(entry, ":");
            if (entrySplit.size() < 2 || entrySplit.size() > 4)
                throw std::runtime_error("Error: invalid file format. Impossible to parse {2}.");
            auto name = entrySplit[0];
            auto password = entrySplit[1];
            auto pass = Password(name, password);
            if (entrySplit.size() > 2) pass.setWebsite(entrySplit[2]);
            if (entrySplit.size() > 3) pass.setLogin(entrySplit[3]);
            passVec.emplace_back(pass);
        }
        categoryVec.emplace_back(saveCatName, passVec);
        if (!lastIter) saveCatName = rCurSplit[1];
    }
    return categoryVec;
}

auto PasswordMapper::mapSearchCommandEntryToPassword(const std::vector<std::string> &commandParams) -> Password {
    auto password = Password();
    for (int i = 1; i < commandParams.size(); i += 2) {
        const auto& type = commandParams[i];
        const auto& param = commandParams[i + 1];
        if (type == "c") continue;
        if (type == "a") {
            if (password.getName().empty()) password.setName(param);
            if (password.getPassword().empty()) password.setPassword(param);
            if (password.getWebsite().empty()) password.setWebsite(param);
            if (password.getLogin().empty()) password.setLogin(param);
        }
        if (type == "n") {
            password.setName(param);
        }
        if (type == "pw") {
            password.setPassword(param);
        }
        if (type == "w") {
            password.setWebsite(param);
        }
        if (type == "l") {
            password.setLogin(param);
        }
    }
    return password;
}

auto PasswordMapper::getCategoryFromSearchCommand(const std::vector<std::string> &commandParams) -> Category {
    for (int i = 1; i < commandParams.size(); i += 2) {
        const auto &type = commandParams[i];
        const auto &param = commandParams[i + 1];
        if (type == "c") return Category(param);
    }
    return {};
}

auto PasswordMapper::mapPasswordToString(const Password &password) -> std::string {
    return std::string(password.getName() + ":" + password.getPassword() + ":" + password.getWebsite() + ":" + password.getLogin() + ";");
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