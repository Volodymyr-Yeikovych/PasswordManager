//
// Created by Volodymyr on 5/11/2023.
//

#include "PasswordMapper.h"
#include "fmt/core.h"
#include "fmt/ranges.h"
#include <regex>
#include <random>
#include <valarray>

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
            if (entry.empty()) continue;
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

auto PasswordMapper::mapCategoryVecToText(const std::vector<Category> &categoryVec) -> std::string {
    auto text = std::string();
    for (auto const &cat : categoryVec) {
        text.append(cat.getName() + " ").append("{\n");
        for (auto const& psw : cat.getPasswordVec()) {
            text.append("\t").append(mapPasswordToString(psw)).append("\n");
        }
        text.append("}\n");
    }
    return text;
}

auto PasswordMapper::getPasswordFromSearchCommand(const std::vector<std::string> &commandParams) -> Password {
    auto password = Password();
    for (int i = 1; i < commandParams.size(); i += 2) {
        const auto &type = commandParams[i];
        const auto &param = commandParams[i + 1];
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

auto PasswordMapper::getPasswordFromAddCommand(const std::vector<std::string> &commandParams) -> Password {
    auto isGeneratedPassword = commandParams[1] == "g";
    auto paramsVec = strSplitTrim(commandParams[2], ":");
    auto name = paramsVec[0];
    auto strPass = paramsVec[1];
    auto website = std::string();
    auto login = std::string();
    if (paramsVec.size() > 3) website = paramsVec[3];
    if (paramsVec.size() > 4) login = paramsVec[4];
    if (isGeneratedPassword) strPass = generatePassword(strPass);
    auto password = Password(name, strPass);
    password.setWebsite(website);
    password.setLogin(login);
    return password;
}

auto PasswordMapper::getEditCommandPipeIndex(const std::vector<std::string> &commandParams) -> int {
    auto delimIndex = int();
    auto delim = "|";
    for (int i = delimIndex; i < commandParams.size(); i++) {
        if (delim == commandParams[i]) {
            delimIndex = i;
            return delimIndex;
        }
    }
    return -1;
}

auto PasswordMapper::getSearchPasswordFromEditCommand(const std::vector<std::string> &commandParams) -> Password {
    auto delimIndex = getEditCommandPipeIndex(commandParams);
    if (delimIndex == -1) throw std::runtime_error("No pipe('|') was found in edit command. Invalid command.");

    auto searchSubRange = std::vector(commandParams.begin(), commandParams.begin() + delimIndex);
    return getPasswordFromSearchCommand(searchSubRange);
}

auto PasswordMapper::getEditPasswordFromEditCommand(const std::vector<std::string> &commandParams) -> Password {
    auto delimIndex = getEditCommandPipeIndex(commandParams);
    if (delimIndex == -1) throw std::runtime_error("No pipe('|') was found in edit command. Invalid command.");

    auto editSubRange = std::vector(commandParams.begin() + delimIndex, commandParams.end());
    return getPasswordFromSearchCommand(editSubRange);
}

auto PasswordMapper::getCategoryFromSearchCommand(const std::vector<std::string> &commandParams) -> Category {
    for (int i = 1; i < commandParams.size(); i += 2) {
        const auto &type = commandParams[i];
        const auto &param = commandParams[i + 1];
        if (type == "c") return Category(param);
    }
    return {};
}

auto PasswordMapper::getCategoryFromAddCommand(const std::vector<std::string> &commandParams) -> Category {
    return Category(strSplitTrim(commandParams[2], ":")[2]);
}

auto PasswordMapper::getSearchCategoryFromEditCommand(const std::vector<std::string> &commandParams) -> Category {
    auto delimIndex = getEditCommandPipeIndex(commandParams);
    if (delimIndex == -1) throw std::runtime_error("No pipe('|') was found in edit command. Invalid command.");

    auto searchSubRange = std::vector(commandParams.begin(), commandParams.begin() + delimIndex);
    return getCategoryFromSearchCommand(searchSubRange);
}

auto PasswordMapper::getEditCategoryFromEditCommand(const std::vector<std::string> &commandParams) -> Category {
    auto delimIndex = getEditCommandPipeIndex(commandParams);
    if (delimIndex == -1) throw std::runtime_error("No pipe('|') was found in edit command. Invalid command.");

    auto editSubRange = std::vector(commandParams.begin() + delimIndex, commandParams.end());
    return getCategoryFromSearchCommand(editSubRange);
}

auto PasswordMapper::mapPasswordToString(const Password &password) -> std::string {
    return std::string(password.getName() + ":" + password.getPassword() + ":" + password.getWebsite() + ":" +
                       password.getLogin() + ";");
}

auto PasswordMapper::generatePassword(const std::string &params) -> std::string {
    auto paramsVec = strSplitTrim(params, "-");
    auto size = int();
    auto isUpper = bool();
    auto isSpecial = bool();
    for (auto const &param: paramsVec) {
        if (param == "u") isUpper = false;
        if (param == "U") isUpper = true;
        if (param == "s") isSpecial = false;
        if (param == "S") isSpecial = true;
        try {
            size = std::stoi(param);
        } catch (std::invalid_argument &e) {
            continue;
        }
    }
    return createPassword(size, isUpper, isSpecial);
}

auto PasswordMapper::createPassword(int size, bool isUpper, bool isSpecial) -> std::string {
    std::random_device dev;
    std::mt19937 mt(dev());
    auto upperInc = isUpper ? 26 : 0;
    auto specialInc = isSpecial ? 24 : 0;
    std::uniform_int_distribution<int> distribution(0, 35 + upperInc + specialInc);
    auto password = std::string();
    for (int i = 0; i < size; i++) password.append(randomPool[distribution(mt)]);
}

auto PasswordMapper::mapCategoryToString(const Category &category) -> std::string {
    auto resultStr = std::string();
    resultStr.append(category.getName()).append(" ");
    resultStr.append("{\n");
    for (auto &psw : category.getPasswordVec()) {
        resultStr.append(PasswordMapper::mapPasswordToString(psw)).append("\n");
    }
    resultStr.append("}\n");
    return resultStr;
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