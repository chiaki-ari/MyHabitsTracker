#ifndef MENU_NODE_HPP
#define MENU_NODE_HPP

#include "utils/CommonUtils.hpp"
#include <vector>
#include <memory>
#include <string>

class MenuNode {
public:
    virtual ~MenuNode() = default;
    virtual void execute() = 0;

    void addChild(std::unique_ptr<MenuNode> child) {
        children_.push_back(std::move(child));
    }

    void setTitle(const std::string& title) { title_ = title; }
    const std::string& getTitle() const { return title_; }

protected:
    std::vector<std::unique_ptr<MenuNode>> children_;
    std::string title_;
};

#endif // MENU_NODE_HPP