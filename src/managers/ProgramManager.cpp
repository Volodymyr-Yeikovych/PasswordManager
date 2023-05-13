//
// Created by Volodymyr on 4/30/2023.
//

#include <algorithm>
#include <cstring>
#include <regex>
#include <set>
#include "ProgramManager.h"
#include "fmt/core.h"
#include "fmt/ranges.h"
#include "../model/Category.h"

auto ProgramManager::operator=(const ProgramManager &other) -> ProgramManager {
    this->fileManager = other.fileManager;
    this->consoleManager = other.consoleManager;
    this->cryptographyManager = other.cryptographyManager;
    this->passwordMapper = other.passwordMapper;
    return *this;
}

ProgramManager::ProgramManager(const FileManager &fileManager, const ConsoleManager &consoleManager,
                               const CryptographyManager &cryptographyManager, const PasswordMapper &mapper)
        : fileManager(fileManager), consoleManager(consoleManager),
          cryptographyManager(cryptographyManager), passwordMapper(mapper) {
    this->fileManager = fileManager;
    this->consoleManager = consoleManager;
    this->cryptographyManager = cryptographyManager;
    this->passwordMapper = mapper;
}

auto ProgramManager::start() -> void {
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
    consoleManager.print("Choose whether to decrypt/encrypt (type enc/dec): ");
    auto startMode = consoleManager.readString();
    while (!isValidStartMode(startMode)) {
        consoleManager.println(startMode);
        consoleManager.print("Invalid start mode (type enc/dec): ");
        startMode = consoleManager.readString();
    }
    consoleManager.print("Provide your password: ");
    auto userPassword = consoleManager.readString();
    if (isEncryption(startMode)) {
        cryptographyManager.encrypt(filePath, userPassword);
    } else {
        cryptographyManager.decrypt(filePath, userPassword);
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
}

auto ProgramManager::inputOutOfBounds(const int &input, const unsigned long long int &poolSize) -> bool {
    if (input <= 0 || input > poolSize) return true;
    return false;
}

auto ProgramManager::isValidStartMode(std::string basicString) -> bool {
    std::ranges::transform(basicString, basicString.begin(), [](char c) { return std::tolower(c); });
    return isEncryption(basicString) || isDecryption(basicString);
}

auto ProgramManager::isEncryption(const std::string &basicString) -> bool {
    return basicString == "enc";
}

auto ProgramManager::isDecryption(const std::string &basicString) -> bool {
    return basicString == "dec";
}

auto ProgramManager::isExitCommand(const std::string &command) -> bool {
    return command == "exit";
}

auto ProgramManager::isNotCommand(const std::string &command) -> bool {
    return !isExitCommand(command) && !isHelpCommand(command) && !isSearchCommand(command) &&
           !isSortCommand(command) && !isAddCommand(command) && !isEditPasswordCommand(command)
           && !isDeletePasswordCommand(command) && !isAddCategoryCommand(command) && !isDeleteCategoryCommand(command);
}

auto ProgramManager::exit(int errCode) -> void {
    std::exit(errCode);
}

auto ProgramManager::isEmptyCommand(const std::vector<std::string> &params) -> bool {
    if (params.empty()) {
//        consoleManager.println("Error: Invalid syntax. Use 'help' for manual.");
        return true;
    }
    return false;
}

auto ProgramManager::isInvalidSADCommandSyntax(const std::vector<std::string> &params) -> bool {
    if (params.size() % 2 == 0) {
        consoleManager.println("Error: Invalid syntax for commands (search/add/delete).");
        consoleManager.println("Use 'help' for manual.");
        return true;
    }
    return false;
}

auto ProgramManager::isInvalidAddCommandLength(const std::vector<std::string> &params) -> bool {
    if (params.size() > 3) {
        consoleManager.println("Error: Invalid syntax, refer to 'help' for manual.");
        return true;
    }
    return false;
}

auto ProgramManager::isInvalidCommandKeyword(const std::vector<std::string> &params,
                                             const std::string &commandKeyword) -> bool {
    if (params[0] != commandKeyword) {
//        consoleManager.println("Error: Command {" + params[0] + "} is not recognised as internal command.");
        return true;
    }
    return false;
}

auto ProgramManager::isInvalidSEDParamType(const std::string &paramType) -> bool {
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

auto ProgramManager::isInvalidSEDCommandTypes(const std::vector<std::string> &params) -> bool {
    for (int i = 1; i < params.size(); i += 2) {
        if(isInvalidSEDParamType(params[i])) return true;
    }
    return false;
}

auto ProgramManager::isInvalidSortParam(const std::string &param) -> bool {
    for (const auto &el: SORT_PARAMS_TYPES) {
        if (param == el) {
            return false;
        }
    }
    return true;
}

auto ProgramManager::isInvalidSortOrder(const std::string &param) -> bool {
    for (const auto &el: SORT_PARAMS_ORDER_TYPES) {
        if (param == el) {
            return false;
        }
    }
    return true;
}

auto ProgramManager::isInvalidSortCommandTypes(const std::vector<std::string> &params) -> bool {
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

auto ProgramManager::isInvalidAddCommandTypes(const std::vector<std::string> &params) -> bool {
    if (params[1] != "c" && params[1] != "g") return true;
    auto valuesVec = passwordMapper.strSplitTrim(params[2], ":");
    if (valuesVec.size() < 3 || valuesVec.size() > 5) return true;
    return false;
}

auto ProgramManager::getStringVecFromSADCommands(const std::string &command) -> std::vector<std::string> {
    auto dashVec = passwordMapper.strSplitTrim(command, "-");
    auto paramsVec = std::vector<std::string>();
    paramsVec.emplace_back(dashVec[0]);
    for (int i = 1; i < dashVec.size(); i++) {
        if (!dashVec[i].ends_with('"')) {
//            consoleManager.println("Error: missing closing quotes(\").");
            return {};
        }
        auto quoteVec = passwordMapper.strSplitTrim(dashVec[i], "\"");
        if (quoteVec.size() != 2) {
//            consoleManager.println("Error: Invalid number of quotes(\") expected {2}, found {"
//                                   + std::to_string(quoteVec.size()) + "}");
            return {};
        }
        paramsVec.emplace_back(quoteVec[0]);
        paramsVec.emplace_back(quoteVec[1]);
    }
    fmt::print("{} \n", paramsVec); /// debug line <------------------------
    return paramsVec;
}

auto ProgramManager::getStringVecFromAddDelCatCommands(const std::string &command) -> std::vector<std::string> {
    auto paramsVec = passwordMapper.strSplitTrim(command, "\\s");
//    fmt::print("{} \n", paramsVec); /// debug line <------------------------
    return paramsVec;
}

auto ProgramManager::getStringVecFromSortCommand(const std::string &command) -> std::vector<std::string> {
    auto dashVec = passwordMapper.strSplitTrim(command, "-");
    auto paramsVec = std::vector<std::string>();
    for (int i = 0; const auto &params: dashVec) {
        if (i == 0) paramsVec.emplace_back(params);
        else {
            auto spaceSplit = passwordMapper.strSplitTrim(params, "\\s");
            for (const auto &param: spaceSplit) paramsVec.emplace_back(param);
        }
        i++;
    }
//    fmt::print("{} \n", paramsVec); /// debug line <------------------------
    return paramsVec;
}

auto ProgramManager::getStringVecFromEditCommand(const std::string &command) -> std::vector<std::string> {
    auto paramsVec = std::vector<std::string>();
    auto pipeVec = passwordMapper.strSplitTrim(command, "\\|");
    if (pipeVec.size() != 2) {
        return {};
    }
    auto firstHalf = getStringVecFromSADCommands(pipeVec[0]);
    auto modInput = std::string("| ");
    modInput.append(pipeVec[1]);
    auto secondHalf = getStringVecFromSADCommands(modInput);
    if (firstHalf.empty() || secondHalf.empty()) {
        return {};
    }
    for (auto const &el: firstHalf) paramsVec.emplace_back(el);
    for (int i = 0; auto const &el: secondHalf) {
//        if (i != 0)
        paramsVec.emplace_back(el);
        i++;
    }
//    fmt::print("{} \n", paramsVec); /// debug line <------------------------
    return paramsVec;
}

auto ProgramManager::isInvalidAddDelCatCommandLength(const std::vector<std::string> &params) -> bool {
    if (params.size() != 1 && params.size() != 2) {
        consoleManager.println("Error: Invalid syntax, refer to 'help' for manual.");
        return true;
    }
    return false;
}

auto ProgramManager::isInvalidEditCommandTypes(const std::vector<std::string> &params) -> bool {
    auto pipeCount = 0;
    auto keyWordCount = 0;
    for (int i = 0; auto const &el : params) {
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
auto ProgramManager::isSearchCommand(const std::string &command) -> bool {
    auto paramsVec = getStringVecFromSADCommands(command);
    if (isEmptyCommand(paramsVec)) return false;
    if (isInvalidSADCommandSyntax(paramsVec)) return false;
    if (isInvalidCommandKeyword(paramsVec, "search")) return false;
    if (isInvalidSEDCommandTypes(paramsVec)) return false;
    return true;
}

/** SORT
     **
     **/
auto ProgramManager::isSortCommand(const std::string &command) -> bool {
    auto paramsVec = getStringVecFromSortCommand(command);
    if (isEmptyCommand(paramsVec)) return false;
    if (isInvalidCommandKeyword(paramsVec, "sort")) return false;
    if (isInvalidSortCommandTypes(paramsVec)) return false;
    return true;
}

/** ADD
     **
     **/
auto ProgramManager::isAddCommand(const std::string &command) -> bool {
    auto paramsVec = getStringVecFromSADCommands(command);
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
auto ProgramManager::isEditPasswordCommand(const std::string &command) -> bool {
    auto paramsVec = getStringVecFromEditCommand(command);
    if (isEmptyCommand(paramsVec)) return false;
    if (isInvalidCommandKeyword(paramsVec, "edit")) return false;
    if (isInvalidEditCommandTypes(paramsVec)) return false;
    return true;
}

/** DELETE
     **
     **/
auto ProgramManager::isDeletePasswordCommand(const std::string &command) -> bool {
    auto paramsVec = getStringVecFromSADCommands(command);
    if (isEmptyCommand(paramsVec)) return false;
    if (isInvalidSADCommandSyntax(paramsVec)) return false;
    if (isInvalidCommandKeyword(paramsVec, "delete")) return false;
    if (isInvalidSEDCommandTypes(paramsVec)) return false;
    return true;
}

/** ADDCAT
     **
     **/
auto ProgramManager::isAddCategoryCommand(const std::string &command) -> bool {
    auto paramsVec = getStringVecFromAddDelCatCommands(command);
    if (isEmptyCommand(paramsVec)) return false;
    if (isInvalidCommandKeyword(paramsVec, "addcat")) return false;
    if (isInvalidAddDelCatCommandLength(paramsVec)) return false;
    return true;
}

/** DELCAT
     **
     **/
auto ProgramManager::isDeleteCategoryCommand(const std::string &command) -> bool {
    auto paramsVec = getStringVecFromAddDelCatCommands(command);
    if (isEmptyCommand(paramsVec)) return false;
    if (isInvalidCommandKeyword(paramsVec, "delcat")) return false;
    if (isInvalidAddDelCatCommandLength(paramsVec)) return false;
    return true;
}

auto ProgramManager::isHelpCommand(const std::string &command) -> bool {
    return command == "help";
}

auto ProgramManager::eraseNotMatching(const Category &searchCat, std::map<Category, std::vector<Password>> &matchingPsw) -> void{
    for (const auto &entry : matchingPsw) {
        if (entry.first != searchCat) matchingPsw.erase(entry.first);
    }
}

auto ProgramManager::executeCommand(const std::string &command) -> void {
    if (isExitCommand(command)) return;
    if (isHelpCommand(command)) listCommands();
    if (isSearchCommand(command)) executeSearch(command);
    if (isSortCommand(command)) executeSort(command);
    if (isAddCommand(command)) executeAdd(command);
    if (isEditPasswordCommand(command)) executeEditPassword(command);
    if (isDeletePasswordCommand(command)) executeDeletePassword(command);
    if (isAddCategoryCommand(command)) executeAddCategory(command);
    if (isDeleteCategoryCommand(command)) executeDeleteCategory(command);
}

auto ProgramManager::executeSearch(const std::string &command) -> void {
    auto fileContent = fileManager.getFileContents(filePath);
    auto categoriesVec = PasswordMapper::mapTextToCategoryVec(fileContent);
    auto commandParams = getStringVecFromSADCommands(command);
    auto searchPsw = PasswordMapper::mapSearchCommandEntryToPassword(command);
    auto specificCat = PasswordMapper::getCategoryFromSearchCommand(command);
    auto entryMap = std::map<Category, std::vector<Password>>();
    for (auto existingCats : categoriesVec) {
        entryMap[existingCats] = existingCats.getMatchingVec(searchPsw);
    }
    if (!specificCat.getName().empty()) eraseNotMatching(specificCat, entryMap);
    consoleManager.printMap(entryMap);
}

auto ProgramManager::executeSort(const std::string &command) -> void {

}

auto ProgramManager::executeAdd(const std::string &command) -> void {

}

auto ProgramManager::executeEditPassword(const std::string &command) -> void {

}

auto ProgramManager::executeDeletePassword(const std::string &command) -> void {

}

auto ProgramManager::executeAddCategory(const std::string &command) -> void {

}

auto ProgramManager::executeDeleteCategory(const std::string &command) -> void {

}

auto ProgramManager::listCommands() -> void {
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
    consoleManager.println(R"(Example: sort -n len asc)");
    consoleManager.println("Sort by name in ascending order, the same as:");
    consoleManager.println(R"(sort -n len)");
    consoleManager.println("Ascending order chosen by default");
    consoleManager.println("Sorting by length is also default parameter");
    consoleManager.println("Thus the following is equal to aforementioned:");
    consoleManager.println(R"(sort -n)");
    consoleManager.println("You can specify more params, provided that they are distinct:");
    consoleManager.println(R"(sort -n abc -c desc)");
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




