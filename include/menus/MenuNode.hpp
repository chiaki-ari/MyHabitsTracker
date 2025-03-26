#ifndef MENU_NODE_HPP
#define MENU_NODE_HPP

#include <vector>
#include <memory>
#include <string>

enum class MenuResult {
    OK,
    BACK,
    EXIT,
    SWITCH_USER
};

class MenuNode
{
public:
    MenuNode(const std::string &title)
        : title_(title)
    {
    }
    virtual ~MenuNode() = default;

    // メニュー動作: 抽象 or 具体でもOK
    virtual MenuResult execute() = 0;

    // 子要素を追加できるなら
    void addChild(std::unique_ptr<MenuNode> child)
    {
        children_.push_back(std::move(child));
    }

    void setTitle(const std::string &title) { title_ = title; }
    const std::string &getTitle() const { return title_; }

protected:
    std::vector<std::unique_ptr<MenuNode>> children_;
    std::string title_;
};

#endif // MENU_NODE_HPP