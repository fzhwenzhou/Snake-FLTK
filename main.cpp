#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Input.H>
#include <FL/fl_message.H>
#include "snake.hpp"

class main_window : public Fl_Window {
    public:
    main_window() : Fl_Window{500, 200, 340, 450} {
        this->copy_label("Snake Game");
        caption.labelsize(36);
        caption.labelfont(FL_BOLD);
        name_label.labelsize(28);
        start_button.labelsize(30);
        start_button.callback([](Fl_Widget*, void* window) {
            auto real_window = reinterpret_cast<main_window*>(window);
            auto name = real_window->name_textbox.value();
            fl_message_title("Welcome");
            fl_message("Hello, %s.", name);
            auto snake = new snake_window{name};
            snake->show();
            delete real_window;
        }, this);
        Fl::scheme("plastic");
    }

    private:
    Fl_Box caption{20, 40, 300, 100, "Snake Game"};
    Fl_Box name_label{20, 110, 300, 100, "Type in your name:"};
    Fl_Input name_textbox{40, 200, 260, 30};
    Fl_Button start_button{60, 280, 220, 60, "Start Game"};
};

int main(int argc, char** argv) {
    auto window = new main_window{};
    window->show(argc, argv);
    return Fl::run();
}