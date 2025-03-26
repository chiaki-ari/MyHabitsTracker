#ifndef USER_MANAGER_HPP
#define USER_MANAGER_HPP

#include <string>
#include <vector>
#include <memory>
#include <filesystem>

class UserManager {
public:
    static UserManager& getInstance() {
        static UserManager instance;
        return instance;
    }

    void loadUserList() {
        userList_.clear();
        for (const auto& entry : std::filesystem::directory_iterator("data/")) {
            if (entry.is_directory()) {
                userList_.push_back(entry.path().filename().string());
            }
        }
    }

    const std::vector<std::string>& getUserList() const {
        return userList_;
    }

    void switchUser(const std::string& userId) {
        currentUser_ = userId;
    }

    std::string getUserPath() const {
        return "data/" + currentUser_ + "/";
    }

    std::string getCurrentUser() const {
        return currentUser_;
    }

private:
    UserManager() = default;
    std::vector<std::string> userList_;
    std::string currentUser_;
};
#endif