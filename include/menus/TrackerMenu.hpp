#ifndef TRACKER_MENU_HPP
#define TRACKER_MENU_HPP

#include "message/MessageManager.hpp"
#include "output/OutputManager.hpp"
#include "input/InputManager.hpp"
#include "menus/MenuNode.hpp"

class TrackerMenu : public MenuNode {
public:
    TrackerMenu(
        const std::string& title, 
        MessageManager& messageManager, 
        InputManager& inputManager, 
        OutputManager& outputManager);

    void execute() override;

private:
    void displayMenu() const;
    int handleUserSelection();

    MessageManager& messageManager_;
    InputManager& inputManager_;
    OutputManager& outputManager_;
    std::string title_;
};

#endif // TRACKER_MENU_HPP