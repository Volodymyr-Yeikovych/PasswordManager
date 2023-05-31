//
// Created by Volodymyr on 4/30/2023.
//

#include <algorithm>
#include <regex>
#include <set>
#include "ProgramController.h"
#include "fmt/core.h"
#include "fmt/ranges.h"

auto ProgramController::operator=(const ProgramController &other) -> ProgramController & {
    this->fileManager = other.fileManager;
    this->consoleManager = other.consoleManager;
    this->cryptographyManager = other.cryptographyManager;
    this->passwordMapper = other.passwordMapper;
    return *this;
}

ProgramController::ProgramController(const FileManager &fileManager, const ConsoleView &consoleManager,
                                     const CryptographyManager &cryptographyManager, const PasswordMapper &mapper)
        : fileManager(fileManager), consoleManager(consoleManager),
          cryptographyManager(cryptographyManager), passwordMapper(mapper) {
    this->fileManager = fileManager;
    this->consoleManager = consoleManager;
    this->cryptographyManager = cryptographyManager;
    this->passwordMapper = mapper;
}

auto ProgramController::start() -> void {
    auto pathVector = fileManager.getFilesVector();
    consoleManager.println(
            "Choose files from list to decrypt/encrypt.");
    consoleManager.println("Type from 1 to n where n is the number of a last file.");
    consoleManager.println("If number out of bounds is printed, absolute path should be provided.");
    consoleManager.displayFiles(pathVector);

    consoleManager.print("Enter here: ");
    auto input = consoleManager.readNum();
    if (inputOutOfBounds(input, pathVector.size())) {
        consoleManager.print("Provide custom path: ");
        filePath = std::filesystem::path(consoleManager.readString());
    } else filePath = pathVector.at(input - 1);
    consoleManager.println(filePath.string());

    consoleManager.print("Provide your password: ");
    auto userPassword = consoleManager.readString();

    auto lastTimeModMsg = cryptographyManager.decrypt(filePath, userPassword);
    consoleManager.println(lastTimeModMsg);

    auto decryptedFile = fileManager.getFileLines(filePath);
    consoleManager.println("Write help to list available commands.");

    auto command = std::string();
    while (!isExitCommand(command)) {
        consoleManager.print("Enter your command: ");
        command = consoleManager.readString();
        if (isNotCommand(command)) {
            consoleManager.println("Invalid syntax or command doesnt exist.");
            consoleManager.println("Use help to list available commands.");
            continue;
        } else executeCommand(command);
    }

    cryptographyManager.encrypt(filePath, userPassword);
}

auto ProgramController::inputOutOfBounds(const int &input, const unsigned long long int &poolSize) -> bool {
    if (input <= 0 || input > poolSize) return true;
    return false;
}

auto ProgramController::isExitCommand(const std::string &command) -> bool {
    return command == "exit";
}

auto ProgramController::isNotCommand(const std::string &command) -> bool {
    return !isExitCommand(command) && !isHelpCommand(command) && !isSearchCommand(command) &&
           !isSortCommand(command) && !isAddCommand(command) && !isEditPasswordCommand(command)
           && !isDeletePasswordCommand(command) && !isAddCategoryCommand(command) && !isDeleteCategoryCommand(command);
}

auto ProgramController::isEmptyCommand(const std::vector<std::string> &params) -> bool {
    if (params.empty()) {
        return true;
    }
    return false;
}

auto ProgramController::isInvalidSADCommandSyntax(const std::vector<std::string> &params) -> bool {
    if (params.size() % 2 == 0) {
        consoleManager.println("Error: Invalid syntax for commands (search/add/delete).");
        consoleManager.println("Use 'help' for manual.");
        return true;
    }
    return false;
}

auto ProgramController::isInvalidAddCommandLength(const std::vector<std::string> &params) -> bool {
    if (params.size() > 3) {
        consoleManager.println("Error: Invalid syntax, refer to 'help' for manual.");
        return true;
    }
    return false;
}

auto ProgramController::isInvalidCommandKeyword(const std::vector<std::string> &params,
                                                const std::string &commandKeyword) -> bool {
    if (params[0] != commandKeyword) {
        return true;
    }
    return false;
}

auto ProgramController::isInvalidSEDParamType(const std::string &paramType) -> bool {
    auto wrongParam = bool(true);
    for (const auto &param: SEARCH_EDIT_DELETE_PARAMS_TYPES) {
        if (paramType == param) {
            wrongParam = false;
            break;
        }
    }
    if (wrongParam) {
        consoleManager.println(
                "Error: Illegal parameter type for commands (search/edit/add/delete) {" + paramType + "}");
        return true;
    }
    if (paramType.empty()) {
        consoleManager.println("Error: Empty parameters(\"  \").");
        return true;
    }
    return false;
}

auto ProgramController::isInvalidSDCommandTypes(const std::vector<std::string> &params) -> bool {
    for (int i = 1; i < params.size(); i += 2) {
        if (isInvalidSEDParamType(params[i])) return true;
    }
    return false;
}

auto ProgramController::isInvalidSortParam(const std::string &param) -> bool {
    for (const auto &el: SORT_PARAMS_TYPES) {
        if (param == el) {
            return false;
        }
    }
    return true;
}

auto ProgramController::isInvalidSortOrder(const std::string &param) -> bool {
    for (const auto &el: SORT_PARAMS_ORDER_TYPES) {
        if (param == el) {
            return false;
        }
    }
    return true;
}

auto ProgramController::isInvalidSortCommandTypes(const std::vector<std::string> &params) -> bool {
    auto paramSet = std::set<std::string>();
    auto timesInserted = 0;
    for (int i = 0; const auto &param: params) {
        if (i == 0) {
            i++;
            continue;
        }
        if (isInvalidSortParam(param)) {
            if (isInvalidSortOrder(param)) {
                consoleManager.println("Error: invalid command syntax. Use 'help' for reference.");
                return true;
            }
        } else {
            if (paramSet.insert(param).second) timesInserted++;
        }
        if (paramSet.size() != timesInserted) {
            consoleManager.println("Error: parameters should be distinct!");
            return true;
        }
    }
    return false;
}

auto ProgramController::isInvalidAddCommandTypes(const std::vector<std::string> &params) -> bool {
    if (params[1] != "c" && params[1] != "g") return true;
    auto valuesVec = PasswordMapper::strSplitTrim(params[2], ":");
    if (valuesVec.size() < 3 || valuesVec.size() > 5) return true;
    if (params[1] == "g") {
        auto paramsVec = PasswordMapper::strSplitTrim(valuesVec[1], "-");
        if (paramsVec.size() < 3 || paramsVec.size() > 4) return true;
        for (const auto &param: paramsVec) {
            if (!param.empty() && param != "u" && param != "U" && param != "s" && param != "S") {
                try {
                    auto intVal = std::stoi(param);
                    continue;
                } catch (std::invalid_argument &e) {
                    return true;
                }
            }
            if (param.empty() || param == "u" || param == "U" || param == "s" || param == "S") continue;
            return true;
        }
    }
    return false;
}

auto ProgramController::getStringVecFromAddCommands(const std::string &command) -> std::vector<std::string> {
    auto quoteVec = PasswordMapper::strSplitTrim(command, "\"");
    if (quoteVec.size() < 2) return {};
    auto leftSplit = PasswordMapper::strSplitTrim(quoteVec[0], "\\s");
    auto rightSplit = quoteVec[1];

    auto paramsVec = std::vector<std::string>();
    paramsVec.emplace_back(leftSplit[0]);
    paramsVec.emplace_back(leftSplit[1].substr(1));
    paramsVec.emplace_back(rightSplit);
    return paramsVec;
}

auto ProgramController::getStringVecFromSearchDeleteCommands(const std::string &command) -> std::vector<std::string> {
    auto dashVec = PasswordMapper::strSplitTrim(command, "-");
    auto paramsVec = std::vector<std::string>();
    paramsVec.emplace_back(dashVec[0]);
    for (int i = 1; i < dashVec.size(); i++) {
        if (!dashVec[i].ends_with('"')) {
            return {};
        }
        auto quoteVec = PasswordMapper::strSplitTrim(dashVec[i], "\"");
        if (quoteVec.size() != 2) {
            return {};
        }
        paramsVec.emplace_back(quoteVec[0]);
        paramsVec.emplace_back(quoteVec[1]);
    }
    return paramsVec;
}

auto ProgramController::getStringVecFromAddDelCatCommands(const std::string &command) -> std::vector<std::string> {
    auto paramsVec = PasswordMapper::strSplitTrim(command, "\\s");
    return paramsVec;
}

auto ProgramController::getStringVecFromSortCommand(const std::string &command) -> std::vector<std::string> {
    auto dashVec = PasswordMapper::strSplitTrim(command, "-");
    auto paramsVec = std::vector<std::string>();
    for (int i = 0; const auto &params: dashVec) {
        if (i == 0) paramsVec.emplace_back(params);
        else {
            auto spaceSplit = PasswordMapper::strSplitTrim(params, "\\s");
            for (const auto &param: spaceSplit) paramsVec.emplace_back(param);
        }
        i++;
    }
    return paramsVec;
}

auto ProgramController::getStringVecFromEditCommand(const std::string &command) -> std::vector<std::string> {
    auto paramsVec = std::vector<std::string>();
    auto pipeVec = PasswordMapper::strSplitTrim(command, "\\|");
    if (pipeVec.size() != 2) {
        return {};
    }
    auto firstHalf = getStringVecFromSearchDeleteCommands(pipeVec[0]);
    auto modInput = std::string("| ");
    modInput.append(pipeVec[1]);
    auto secondHalf = getStringVecFromSearchDeleteCommands(modInput);
    if (firstHalf.empty() || secondHalf.empty()) {
        return {};
    }
    for (auto const &el: firstHalf) paramsVec.emplace_back(el);
    for (int i = 0; auto const &el: secondHalf) {
        paramsVec.emplace_back(el);
        i++;
    }
    return paramsVec;
}

auto ProgramController::isInvalidAddDelCatCommandLength(const std::vector<std::string> &params) -> bool {
    if (params.size() != 1 && params.size() != 2) {
        consoleManager.println("Error: Invalid syntax, refer to 'help' for manual.");
        return true;
    }
    return false;
}

auto ProgramController::isInvalidEditCommandTypes(const std::vector<std::string> &params) -> bool {
    auto pipeCount = 0;
    auto keyWordCount = 0;
    for (int i = 0; auto const &el: params) {
        if (el == "edit") {
            if (keyWordCount == 0) {
                keyWordCount++;
                i++;
                continue;
            } else {
                consoleManager.println("Error: more than one edit keyword in command.");
                return true;
            }
        }
        if (el == "|") {
            if (pipeCount == 0) {
                pipeCount++;
                continue;
            } else {
                consoleManager.println("Error: more than one pipe char in command.");
                return true;
            }
        }
        if (i % 2 == 1 && isInvalidSEDParamType(el)) return true;
        i++;
    }
    return false;
}

/** SEARCH
 **
 **/
auto ProgramController::isSearchCommand(const std::string &command) -> bool {
    auto paramsVec = getStringVecFromSearchDeleteCommands(command);
    if (isEmptyCommand(paramsVec)) return false;
    if (isInvalidSADCommandSyntax(paramsVec)) return false;
    if (isInvalidCommandKeyword(paramsVec, "search")) return false;
    if (isInvalidSDCommandTypes(paramsVec)) return false;
    return true;
}

/** SORT
     **
     **/
auto ProgramController::isSortCommand(const std::string &command) -> bool {
    auto paramsVec = getStringVecFromSortCommand(command);
    if (isEmptyCommand(paramsVec)) return false;
    if (isInvalidCommandKeyword(paramsVec, "sort")) return false;
    if (isInvalidSortCommandTypes(paramsVec)) return false;
    return true;
}

/** ADD
     **
     **/
auto ProgramController::isAddCommand(const std::string &command) -> bool {
    auto paramsVec = getStringVecFromAddCommands(command);
    if (isEmptyCommand(paramsVec)) return false;
    if (isInvalidSADCommandSyntax(paramsVec)) return false;
    if (isInvalidCommandKeyword(paramsVec, "add")) return false;
    if (isInvalidAddCommandLength(paramsVec)) return false;
    if (isInvalidAddCommandTypes(paramsVec)) return false;
    return true;
}

/** EDIT
     **
     **/
auto ProgramController::isEditPasswordCommand(const std::string &command) -> bool {
    auto paramsVec = getStringVecFromEditCommand(command);
    if (isEmptyCommand(paramsVec)) return false;
    if (isInvalidCommandKeyword(paramsVec, "edit")) return false;
    if (isInvalidEditCommandTypes(paramsVec)) return false;
    return true;
}

/** DELETE
     **
     **/
auto ProgramController::isDeletePasswordCommand(const std::string &command) -> bool {
    auto paramsVec = getStringVecFromSearchDeleteCommands(command);
    if (isEmptyCommand(paramsVec)) return false;
    if (isInvalidSADCommandSyntax(paramsVec)) return false;
    if (isInvalidCommandKeyword(paramsVec, "delete")) return false;
    if (isInvalidSDCommandTypes(paramsVec)) return false;
    return true;
}

/** ADDCAT
     **
     **/
auto ProgramController::isAddCategoryCommand(const std::string &command) -> bool {
    auto paramsVec = getStringVecFromAddDelCatCommands(command);
    if (isEmptyCommand(paramsVec)) return false;
    if (isInvalidCommandKeyword(paramsVec, "addcat")) return false;
    if (isInvalidAddDelCatCommandLength(paramsVec)) return false;
    return true;
}

/** DELCAT
     **
     **/
auto ProgramController::isDeleteCategoryCommand(const std::string &command) -> bool {
    auto paramsVec = getStringVecFromAddDelCatCommands(command);
    if (isEmptyCommand(paramsVec)) return false;
    if (isInvalidCommandKeyword(paramsVec, "delcat")) return false;
    if (isInvalidAddDelCatCommandLength(paramsVec)) return false;
    return true;
}

auto ProgramController::isHelpCommand(const std::string &command) -> bool {
    return command == "help";
}

auto ProgramController::editData(const Category &catToMatch, const Category &catToEdit,
                                 const Password &pswToMatch, const Password &pswToEdit,
                                 std::vector<Category> &saveData) -> void {
    auto searchCatSelected = !catToMatch.getName().empty();
    auto editCatSelected = !catToEdit.getName().empty();

    auto containsEditCat = false;
    auto editCatInd = int();
    auto containsSearchCat = false;
    auto searchCatInd = int();

    auto diffCatMatching = std::map<int, std::vector<Password>>();
    auto saveTransferCats = std::vector<Password>();
    auto counter = 0;
    for (auto &cat: saveData) {
        if (!searchCatSelected) {
            auto matchingVec = cat.getMatchingVec(pswToMatch);
            if (!editCatSelected) {
                for (auto &psw: matchingVec) {
                    cat.removePassword(psw);
                    psw.editMatching(pswToEdit);
                    cat.addPassword(psw);
                }
            } else {
                diffCatMatching.insert({counter, matchingVec});
                if (cat.getName() == catToEdit.getName()) {
                    containsEditCat = true;
                    editCatInd = counter;
                }
            }
        } else {
            if (cat.getName() == catToMatch.getName()) {
                saveTransferCats = cat.getMatchingVec(pswToMatch);
                containsSearchCat = true;
                searchCatInd = counter;
            }
            if (editCatSelected) {
                if (cat.getName() == catToEdit.getName()) {
                    containsEditCat = true;
                    editCatInd = counter;
                }
            }
        }
        counter++;
    }

    if (searchCatSelected) {
        if (!containsSearchCat) {
            throw std::runtime_error(
                    "Unable to edit: given search category doesn't yet exist. Try addcat command to add category.");
        } else {
            auto &cat = saveData[searchCatInd];
            auto editIndex = editCatSelected ? editCatInd : searchCatInd;
            for (auto &psw: saveTransferCats) {
                \
                cat.removePassword(psw);
                psw.editMatching(pswToEdit);
                saveData[editIndex].addPassword(psw);
            }
        }
    }

    if (editCatSelected) {
        if (!containsEditCat) {
            throw std::runtime_error(
                    "Unable to edit: given edit category doesn't yet exist. Try addcat command to add category.");
        } else {
            counter = 0;
            if (diffCatMatching.empty()) return;
            for (auto &cat: saveData) {
                for (auto &psw: diffCatMatching[counter]) {
                    cat.removePassword(psw);
                    psw.editMatching(pswToEdit);
                    saveData[editCatInd].addPassword(psw);
                }
                counter++;
            }
        }
    }
}

auto ProgramController::catExists(const Category &catToAdd, const std::vector<Category> &fileData) -> bool {
    auto exists = bool(false);
    for (const auto &cat: fileData) {
        if (!catToAdd.getName().empty() && cat.getName() == catToAdd.getName()) {
            exists = true;
            break;
        }
    }
    return exists;
}

auto ProgramController::getNameMatchingCatIterator(const Category &catToAdd,
                                                   const std::vector<Category> &fileData) -> std::vector<Category>::const_iterator {
    auto it = fileData.begin();
    for (const auto &cat: fileData) {
        if (cat.getName() == catToAdd.getName()) break;
        it++;
    }
    return it;
}

auto ProgramController::deleteMatching(const Password &pswToMatch, const Category &catToMatch,
                                       std::vector<Category> &fileData) -> void {
    auto hasCatToMatch = !catToMatch.getName().empty();

    auto toDelete = std::map<int, std::vector<Password>>();
    for (int counter = 0; auto &cat: fileData) {
        if (!hasCatToMatch) {
            toDelete.insert({counter, cat.getMatchingVec(pswToMatch)});
        } else {
            if (cat.getName() == catToMatch.getName()) {
                toDelete.insert({counter, cat.getMatchingVec(pswToMatch)});
            }
        }
        counter++;
    }
    auto delSize = 0;
    for (const auto& pair : toDelete) {
        delSize += (int) pair.second.size();
    }

    auto confirmation = std::string("yes");
    if (delSize > 1) {
        consoleManager.print("You are trying to delete more than one password. Are you sure (yes/no): ");
        confirmation = consoleManager.readString();
    }

    if (confirmation == "yes") {
        for (const auto &pair: toDelete) {
            for (auto &toErase: pair.second) fileData[pair.first].removePassword(toErase);
        }
    }
}

auto ProgramController::isSortParam(const std::string &param) -> bool {
    for (const auto &constParam: SORT_PARAMS_TYPES) {
        if (constParam == param) return true;
    }
    return false;
}

auto ProgramController::isSortSubParam(const std::string &subParam) -> bool {
    for (const auto &constParam: SORT_PARAMS_ORDER_TYPES) {
        if (constParam == subParam) return true;
    }
    return false;
}

auto
ProgramController::getSortVecFromSortCommand(
        const std::vector<std::string> &commandParams) -> std::vector<std::string> {
    auto sortVec = std::vector<std::string>();
    for (int i = 1; i < commandParams.size(); i++) {
        auto nextIsEmpty = (i + 1) == commandParams.size();
        const auto &cur = commandParams[i];
        const auto &next = !nextIsEmpty ? commandParams[i + 1] : cur;
        if (isSortParam(cur)) {
            sortVec.emplace_back(cur);
            if (isSortParam(next)) {
                sortVec.emplace_back(DEFAULT_SORT_ORDER_FIRST_PARAM);
                sortVec.emplace_back(DEFAULT_SORT_ORDER_SECOND_PARAM);
            }
        }
        if (isSortSubParam(cur)) {
            sortVec.emplace_back(cur);
            const auto &prev = commandParams[i - 1];
            if (isSortParam(prev)) {
                if (isSortParam(next) || nextIsEmpty) {
                    sortVec.emplace_back(DEFAULT_SORT_ORDER_SECOND_PARAM);
                }
            }
        }
    }
    return sortVec;
}

auto ProgramController::isValidSortVec(const std::vector<std::string> &sortVec) -> bool {
    if (sortVec.size() % 3 != 0) return false;
    for (int i = 0; i < sortVec.size(); i += 3) {
        const auto &cur = sortVec[i];
        const auto &firstSub = sortVec[i + 1];
        const auto &secondSub = sortVec[i + 2];
        if (!isSortParam(cur)) return false;
        if (firstSub != "abc" && firstSub != "len") return false;
        if (secondSub != "desc" && secondSub != "asc") return false;
    }
    return true;
}

auto ProgramController::sortData(const std::vector<std::string> &sortVec, std::vector<Category> &fileData) -> void {
    for (int i = 0; i < sortVec.size(); i += 3) {
        const auto &sortParam = sortVec[i];
        const auto &firstSub = sortVec[i + 1];
        const auto &secondSub = sortVec[i + 2];
        for (auto &cat: fileData) {
            if (sortParam == "c") {
                if (firstSub == "len") {
                    if (secondSub == "asc") {
                        std::ranges::sort(fileData, [](Category &cat1, Category &cat2) -> int {
                            return cat1.getName().size() < cat2.getName().size();
                        });
                    }
                    if (secondSub == "desc") {
                        std::ranges::sort(fileData, [](Category &cat1, Category &cat2) -> int {
                            return cat1.getName().size() > cat2.getName().size();
                        });
                    }
                }
                if (firstSub == "abc") {
                    if (secondSub == "asc") {
                        std::ranges::sort(fileData, [](Category &cat1, Category &cat2) -> int {
                            return cat1.getName() < cat2.getName();
                        });
                    }
                    if (secondSub == "desc") {
                        std::ranges::sort(fileData, [](Category &cat1, Category &cat2) -> int {
                            return cat1.getName() > cat2.getName();
                        });
                    }
                }
                break;
            }
            if (firstSub == "len") cat.sortByLength(sortParam, secondSub);
            if (firstSub == "abc") cat.sortAlphabetically(sortParam, secondSub);
        }
    }

}

auto ProgramController::passwordSafetyInform(const std::string &psw, const std::vector<Category> &fileData) -> void {
    auto presentBefore = false;
    for (const auto &cat: fileData) {
        for (const auto &pass: cat.getPasswordVec()) {
            if (pass.getPassword() == psw) presentBefore = true;
        }
    }
    if (presentBefore)
        consoleManager.println("This password was already present in the file. Consider choosing a new one.");
    if (psw.size() <= 8 || presentBefore) consoleManager.println("Your password safety is mediocre.");
    else if (psw.size() >= 12 && psw.size() < 16 && !presentBefore)
        consoleManager.println("Your password safety is plausible.");
    else if (psw.size() >= 16 && !presentBefore) consoleManager.println("Your password safety is superb.");
}

auto ProgramController::executeCommand(const std::string &command) -> void {
    if (isExitCommand(command)) return;
    try {
        if (isHelpCommand(command)) executeHelp();
        if (isSearchCommand(command)) executeSearch(command);
        if (isSortCommand(command)) executeSort(command);
        if (isAddCommand(command)) executeAdd(command);
        if (isEditPasswordCommand(command)) executeEditPassword(command);
        if (isDeletePasswordCommand(command)) executeDeletePassword(command);
        if (isAddCategoryCommand(command)) executeAddCategory(command);
        if (isDeleteCategoryCommand(command)) executeDeleteCategory(command);
    } catch (std::invalid_argument &e) {
        consoleManager.println(e.what());
    }
}

auto ProgramController::executeSearch(const std::string &command) -> void {
    auto fileContent = fileManager.getFileContents(filePath);
    auto categoriesVec = PasswordMapper::mapTextToCategoryVec(fileContent);
    auto commandParams = getStringVecFromSearchDeleteCommands(command);

    auto searchPsw = PasswordMapper::getPasswordFromSearchCommand(commandParams);
    auto specificCat = PasswordMapper::getCategoryFromSearchCommand(commandParams);

    auto entryMap = std::map<Category, std::vector<Password>>();
    for (auto existingCats: categoriesVec) {
        auto matches = existingCats.getMatchingVec(searchPsw);
        if (!matches.empty()) {
            if (specificCat.getName().empty()) {
                entryMap[existingCats] = matches;
            } else {
                if (existingCats.getName() == specificCat.getName())
                    entryMap[existingCats] = matches;
            }
        }
    }

    consoleManager.printCategoryMap(entryMap);
}

auto ProgramController::executeSort(const std::string &command) -> void {
    auto fileContent = fileManager.getFileContents(filePath);
    auto categoriesVec = PasswordMapper::mapTextToCategoryVec(fileContent);
    auto commandParams = getStringVecFromSortCommand(command);

    auto sortVec = getSortVecFromSortCommand(commandParams);

    if (!isValidSortVec(sortVec)) {
        consoleManager.println("Error: Invalid sorting order. First param(%1) should be before second(%2) !!!");
        return;
    }
    sortData(sortVec, categoriesVec);

    consoleManager.displayCategoryVec(categoriesVec);

    auto newFileContent = PasswordMapper::mapCategoryVecToText(categoriesVec);
    fileManager.setFileContents(newFileContent, filePath);
}

auto ProgramController::executeAdd(const std::string &command) -> void {
    auto fileContent = fileManager.getFileContents(filePath);
    auto categoriesVec = PasswordMapper::mapTextToCategoryVec(fileContent);
    auto commandParams = getStringVecFromAddCommands(command);

    auto passwordToAdd = PasswordMapper::getPasswordFromAddCommand(commandParams);
    auto entryCat = PasswordMapper::getCategoryFromAddCommand(commandParams);

    auto contains = false;
    auto catInd = 0;
    for (const auto &cat: categoriesVec) {
        if (cat.getName() == entryCat.getName()) {
            contains = true;
            break;
        }
        catInd++;
    }
    if (!contains)
        throw std::invalid_argument(
                "Trying to add password in non-existent category. Try command -> addcat " + entryCat.getName());

    passwordSafetyInform(passwordToAdd.getPassword(), categoriesVec);
    categoriesVec[catInd].addPassword(passwordToAdd);
    auto newFileContent = PasswordMapper::mapCategoryVecToText(categoriesVec);
    fileManager.setFileContents(newFileContent, filePath);
}

auto ProgramController::executeEditPassword(const std::string &command) -> void {
    auto fileContent = fileManager.getFileContents(filePath);
    auto categoriesVec = PasswordMapper::mapTextToCategoryVec(fileContent);
    auto commandParams = getStringVecFromEditCommand(command);

    auto searchEditPassword = PasswordMapper::getSearchPasswordFromEditCommand(commandParams);
    auto editPassword = PasswordMapper::getEditPasswordFromEditCommand(commandParams);
    auto searchEditCategory = PasswordMapper::getSearchCategoryFromEditCommand(commandParams);
    auto editCategory = PasswordMapper::getEditCategoryFromEditCommand(commandParams);

    editData(searchEditCategory, editCategory, searchEditPassword, editPassword, categoriesVec);

    auto newFileContent = PasswordMapper::mapCategoryVecToText(categoriesVec);
    fileManager.setFileContents(newFileContent, filePath);
}

auto ProgramController::executeDeletePassword(const std::string &command) -> void {
    auto fileContent = fileManager.getFileContents(filePath);
    auto categoriesVec = PasswordMapper::mapTextToCategoryVec(fileContent);
    auto commandParams = getStringVecFromSearchDeleteCommands(command);

    auto deletePassword = PasswordMapper::getPasswordFromDeleteCommand(commandParams);
    auto deleteCat = PasswordMapper::getCategoryFromDeleteCommand(commandParams);

    deleteMatching(deletePassword, deleteCat, categoriesVec);

    auto newFileContent = PasswordMapper::mapCategoryVecToText(categoriesVec);
    fileManager.setFileContents(newFileContent, filePath);
}

auto ProgramController::executeAddCategory(const std::string &command) -> void {
    auto fileContent = fileManager.getFileContents(filePath);
    auto categoriesVec = PasswordMapper::mapTextToCategoryVec(fileContent);
    auto commandParams = getStringVecFromAddDelCatCommands(command);

    auto catToAdd = PasswordMapper::getCategoryFromAddDelCatCommand(commandParams);

    if (catToAdd.getName().empty()) {
        consoleManager.println("Error: You didn't specify category name, unable to add category.");
        return;
    }

    auto exists = catExists(catToAdd, categoriesVec);
    if (!exists) {
        categoriesVec.emplace_back(catToAdd);
        auto newFileContent = PasswordMapper::mapCategoryVecToText(categoriesVec);
        fileManager.setFileContents(newFileContent, filePath);
    } else {
        consoleManager.println
                ("Error: category you are trying to add already exists. Try using different cat name.");
    }

}

auto ProgramController::executeDeleteCategory(const std::string &command) -> void {
    auto fileContent = fileManager.getFileContents(filePath);
    auto categoriesVec = PasswordMapper::mapTextToCategoryVec(fileContent);
    auto commandParams = getStringVecFromAddDelCatCommands(command);

    auto catToDelete = PasswordMapper::getCategoryFromAddDelCatCommand(commandParams);

    auto exists = catExists(catToDelete, categoriesVec);

    if (exists) {
        auto elToErase = getNameMatchingCatIterator(catToDelete, categoriesVec);
        if (elToErase == categoriesVec.end()) {
            consoleManager.println("Error: can't find category to erase, even though before it existed.");
            return;
        } else categoriesVec.erase(elToErase);
    } else {
        categoriesVec.clear();
    }

    auto newFileContent = PasswordMapper::mapCategoryVecToText(categoriesVec);
    fileManager.setFileContents(newFileContent, filePath);
}

auto ProgramController::executeHelp() -> void {
    consoleManager.println("================================================");
    consoleManager.println("------------------------------------------------");
    consoleManager.println("exit");
    consoleManager.println("encrypts a file back with provided password and closes program");
    consoleManager.println("------------------------------------------------");
    consoleManager.println("search -p \"%\"");
    consoleManager.println("instead of -p u need to choose the following parameters:");
    consoleManager.println("-a search among any params");
    consoleManager.println("-n search among names");
    consoleManager.println("-pw search among passwords");
    consoleManager.println("-c search among categories");
    consoleManager.println("-w search among website/service names");
    consoleManager.println("-l search among logins");
    consoleManager.println("instead of % write any params");
    consoleManager.println("Example: search -c \"Shopping\"");
    consoleManager.println("Will print all occurrences within this category");
    consoleManager.println("You can combine as many params as you like:");
    consoleManager.println(R"(search -n "Google" -w "Google.com")");
    consoleManager.println("------------------------------------------------");
    consoleManager.println(R"(sort -p %1 %2)");
    consoleManager.println("instead of -p u need to choose the following parameters:");
    consoleManager.println("-n sort by name");
    consoleManager.println("-pw srd by password");
    consoleManager.println("-c sort by categories");
    consoleManager.println("-w sort by website/service names");
    consoleManager.println("-l sort by login");
    consoleManager.println("You need to choose 2 default sorting types instead of %1 and %2: ");
    consoleManager.println("%1 ->>");
    consoleManager.println("len - sort by length (default)");
    consoleManager.println("abc - sort in alphabetical order");
    consoleManager.println("%2 ->>");
    consoleManager.println("desc - sort in descending order");
    consoleManager.println("asc - sort in ascending order (default)");
    consoleManager.println("If no %1 or %2 will be provided, default sorting type will be chosen");
    consoleManager.println("You can omit both(%1 and %2) or only %2");
    consoleManager.println("Something like that: sort -pw asc  <-- won't work");
    consoleManager.println("sort -pw  <-- correct");
    consoleManager.println("sort -pw abc  <-- correct");
    consoleManager.println(R"(Example: sort -n len asc)");
    consoleManager.println("Sort by name in ascending order, the same as:");
    consoleManager.println(R"(sort -n len)");
    consoleManager.println("Ascending order chosen by default");
    consoleManager.println("Sorting by length is also default parameter");
    consoleManager.println("Thus the following is equal to aforementioned:");
    consoleManager.println(R"(sort -n)");
    consoleManager.println("You can specify more params, provided that they are distinct:");
    consoleManager.println(R"(sort -n abc -c len)");
    consoleManager.println("------------------------------------------------");
    consoleManager.println("add -p \"%\"");
    consoleManager.println("instead of -p u need to choose the following parameters:");
    consoleManager.println("-c custom password, you need to specify: name, password, category");
    consoleManager.println("custom password cant contain ':' characters");
    consoleManager.println("-g generated password, you need to specify: name, password parameters*, category");
    consoleManager.println("Example with custom password ->>");
    consoleManager.println(R"(add -c "Google psw:asj123kasd:Accounts")");
    consoleManager.println("(Google psw) - name, (asj123kasd) - password, (Accounts) - category");
    consoleManager.println("Beware you need to use ':' delimiter for your data to be parsed");
    consoleManager.println("Spaces between ':' does not matter");
    consoleManager.println("Example with generated password ->>");
    consoleManager.println(R"(add -g "Google psw: -% -u -s:Accounts")");
    consoleManager.println("-% character number if not specified default 16 will be used.");
    consoleManager.println("-u don't include upper case");
    consoleManager.println("-U include upper case");
    consoleManager.println("-s dont include special chars");
    consoleManager.println("-S include special chars");
    consoleManager.println(R"(add -g "Google psw: -12 -u -S:Accounts")");
    consoleManager.println("Generates random password of 12 chars, name (Google psw), category (Accounts)");
    consoleManager.println("no upper case but at least one special character");
    consoleManager.println("Optional parameters ->>");
    consoleManager.println("Additionally password can contain website/service name and login");
    consoleManager.println("Both of them or just one");
    consoleManager.println(R"(Syntax: add -c "name:password:category:website/service:login")");
    consoleManager.println("Example with custom password and additional params ->>");
    consoleManager.println(R"(add -c "Google psw:asj123kasd:Accounts:oracle.com")");
    consoleManager.println("Generated:");
    consoleManager.println("(Google psw) - name, (asj123kasd) - password, (Accounts) - category");
    consoleManager.println("(oracle.com) - website/service name, no login");
    consoleManager.println(R"(add -c "Google psw:asj123kasd:Accounts: :alex")");
    consoleManager.println("Generated:");
    consoleManager.println("(Google psw) - name, (asj123kasd) - password, (Accounts) - category");
    consoleManager.println("no website/service name, (alex) - login");
    consoleManager.println(
            "Beware that even if you dont have website/service name additional ':' and at least one space should be specified");
    consoleManager.println("------------------------------------------------");
    consoleManager.println(R"(edit -p "%" | -p "%")");
    consoleManager.println("instead of -p u need to choose the following parameters:");
    consoleManager.println("-a select among any params");
    consoleManager.println("-n select among names");
    consoleManager.println("-pw select among passwords");
    consoleManager.println("-c select among categories");
    consoleManager.println("-w select among website/service names");
    consoleManager.println("-l select among logins");
    consoleManager.println("Symbol pipe '|' separates edit command into two parts");
    consoleManager.println("First part selects passwords you want to change.");
    consoleManager.println("Second part changes all selected passwords towards provided values");
    consoleManager.println(R"(Example: edit -c "Shopping" | -c "Cooking")");
    consoleManager.println("Will transfer all passwords from Shopping category into Cooking");
    consoleManager.println("If cooking category doesn't exist the command will fail");
    consoleManager.println("You can combine as many params as you like:");
    consoleManager.println(R"(edit -n "Google" -w "Google.com" | -pw "GooglePsw")");
    consoleManager.println("------------------------------------------------");
    consoleManager.println("delete -p \"%\"");
    consoleManager.println("instead of -p u need to choose the following parameters:");
    consoleManager.println("-a select among any params");
    consoleManager.println("-n select among names");
    consoleManager.println("-pw select among passwords");
    consoleManager.println("-c select among categories");
    consoleManager.println("-w select among website/service names");
    consoleManager.println("-l select among logins");
    consoleManager.println("Example: delete -c \"Shopping\"");
    consoleManager.println("Will delete all passwords within this category");
    consoleManager.println("The category will remain, however, will be empty");
    consoleManager.println("You can combine as many params as you like:");
    consoleManager.println(R"(delete -n "Google" -w "Google.com")");
    consoleManager.println("Example: delete");
    consoleManager.println("This command will delete all passwords only leaving empty categories");
    consoleManager.println("------------------------------------------------");
    consoleManager.println("addcat %");
    consoleManager.println("instead of % u need to write category name");
    consoleManager.println("Example ->>");
    consoleManager.println("addcat Shopping");
    consoleManager.println("Will add new category Shopping");
    consoleManager.println("------------------------------------------------");
    consoleManager.println("delcat %");
    consoleManager.println("instead of % u need to write category name");
    consoleManager.println("Example ->>");
    consoleManager.println("delcat Shopping");
    consoleManager.println("Will delete category Shopping and all passwords in this category");
    consoleManager.println("Example: delcat");
    consoleManager.println("Will delete all categories and passwords within them.");
    consoleManager.println("Basically will clear a file");
    consoleManager.println("------------------------------------------------");
    consoleManager.println("================================================");
}




