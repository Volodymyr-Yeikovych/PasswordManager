//
// Created by Volodymyr on 4/30/2023.
//

#include <algorithm>
#include "ProgramManager.h"

auto ProgramManager::operator=(const ProgramManager &other) -> ProgramManager {
    this->fileManager = other.fileManager;
    this->consoleManager = other.consoleManager;
    this->cryptographyManager = other.cryptographyManager;
    return *this;
}

ProgramManager::ProgramManager(const FileManager &fileManager, const ConsoleManager &consoleManager,
                               const CryptographyManager &cryptographyManager)
        : fileManager(fileManager), consoleManager(consoleManager),
          cryptographyManager(cryptographyManager) {
    this->fileManager = fileManager;
    this->consoleManager = consoleManager;
    this->cryptographyManager = cryptographyManager;
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
    auto filePath = std::filesystem::path();
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
        auto decryptedFile = fileManager.getFileContents(filePath);
        consoleManager.println("Write help to list available commands.");
        auto command = std::string();
        while (!isCloseCommand(command)) {
            consoleManager.print("Enter your command: ");
            command = consoleManager.readString();
            if (isNotCommand(command)) {
                consoleManager.println("Invalid command, use help to list available commands.");
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

auto ProgramManager::isCloseCommand(const std::string &basicString) -> bool {
    return basicString == "exit";
}

auto ProgramManager::isNotCommand(const std::string &basicString) -> bool {
    return !isCloseCommand(basicString) && !isHelpCommand(basicString) && !isSearchCommand(basicString) &&
           !isSortCommand(basicString)
           && !isAddCommand(basicString) && !isEditPasswordCommand(basicString) && !isDeletePasswordCommand(basicString)
           && !isAddCategoryCommand(basicString) && !isDeleteCategoryCommand(basicString);
}

auto ProgramManager::isSearchCommand(const std::string &basicString) -> bool {
    return false;
}

auto ProgramManager::isSortCommand(const std::string &basicString) -> bool {
    return false;
}

auto ProgramManager::isAddCommand(const std::string &basicString) -> bool {
    return false;
}

auto ProgramManager::isEditPasswordCommand(const std::string &basicString) -> bool {
    return false;
}

auto ProgramManager::isDeletePasswordCommand(const std::string &basicString) -> bool {
    return false;
}

auto ProgramManager::isAddCategoryCommand(const std::string &basicString) -> bool {
    return false;
}

auto ProgramManager::isDeleteCategoryCommand(const std::string &basicString) -> bool {
    return false;
}

auto ProgramManager::isHelpCommand(const std::string &basicString) -> bool {
    return basicString == "help";
}

auto ProgramManager::executeCommand(const std::string &basicString) -> void {
    if (isCloseCommand(basicString)) return;
    if (isHelpCommand(basicString)) listCommands();
    if (isSearchCommand(basicString)) executeSearch(basicString);
    if (isSortCommand(basicString)) executeSort(basicString);
    if (isAddCommand(basicString)) executeAdd(basicString);
    if (isEditPasswordCommand(basicString)) executeEditPassword(basicString);
    if (isDeletePasswordCommand(basicString)) executeDeletePassword(basicString);
    if (isAddCategoryCommand(basicString)) executeAddCategory(basicString);
    if (isDeleteCategoryCommand(basicString)) executeDeleteCategory(basicString);
}

auto ProgramManager::executeSearch(const std::string &basicString) -> void {
}

auto ProgramManager::executeSort(const std::string &basicString) -> void {

}

auto ProgramManager::executeAdd(const std::string &basicString) -> void {

}

auto ProgramManager::executeEditPassword(const std::string &basicString) -> void {

}

auto ProgramManager::executeDeletePassword(const std::string &basicString) -> void {

}

auto ProgramManager::executeAddCategory(const std::string &basicString) -> void {

}

auto ProgramManager::executeDeleteCategory(const std::string &basicString) -> void {

}

auto ProgramManager::listCommands() -> void {
    consoleManager.println("================================================");
    consoleManager.println("------------------------------------------------");
    consoleManager.println("search -p \"PARAMS\"");
    consoleManager.println("instead of -p u need to choose the following parameters:");
    consoleManager.println("-a search among any params");
    consoleManager.println("-n search among names");
    consoleManager.println("-pw search among passwords");
    consoleManager.println("-c search among categories");
    consoleManager.println("-w search among website/service names");
    consoleManager.println("-l search among logins");
    consoleManager.println("Example: search -c \"Shopping\"");
    consoleManager.println("Will print all occurrences within this category");
    consoleManager.println("You can combine as many params as you like:");
    consoleManager.println(R"(search -n "Google" -s "Google.com")");
    consoleManager.println("------------------------------------------------");
    consoleManager.println(R"(sort -p "%1" "%2")");
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
    consoleManager.println(R"(Example: sort -n "len" "asc")");
    consoleManager.println("Sort by name in ascending order, the same as:");
    consoleManager.println(R"(sort -n "len")");
    consoleManager.println("Ascending order chosen by default");
    consoleManager.println("Sorting by length is also default parameter");
    consoleManager.println("Thus the following is equal to aforementioned:");
    consoleManager.println(R"(sort -n)");
    consoleManager.println("You can specify more params, provided that they are distinct:");
    consoleManager.println(R"(sort -n "abc" -c "desc")");
    consoleManager.println("------------------------------------------------");
    consoleManager.println("add -p \"%\"");
    consoleManager.println("instead of -p u need to choose the following parameters:");
    consoleManager.println("-c custom password, you need to specify: name, password, category");
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
    consoleManager.println(R"(add -c "Google psw:asj123kasd:Accounts::alex")");
    consoleManager.println("Generated:");
    consoleManager.println("(Google psw) - name, (asj123kasd) - password, (Accounts) - category");
    consoleManager.println("no website/service name, (alex) - login");
    consoleManager.println("Beware that even if you dont have website/service name additional ':' should be specified");
    consoleManager.println("------------------------------------------------");
    consoleManager.println("edit ");
    consoleManager.println("");
    consoleManager.println("");
    consoleManager.println("");
    consoleManager.println("");
    consoleManager.println("");
    consoleManager.println("");
    consoleManager.println("");
    consoleManager.println("");
    consoleManager.println("");
    consoleManager.println("");
    consoleManager.println("------------------------------------------------");
    consoleManager.println("delete");
    consoleManager.println("------------------------------------------------");
    consoleManager.println("add cat");
    consoleManager.println("------------------------------------------------");
    consoleManager.println("delete cat");
    consoleManager.println("------------------------------------------------");
    consoleManager.println("================================================");
}




