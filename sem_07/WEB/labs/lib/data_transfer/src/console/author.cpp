#include "console/author.h"


std::string AuthorConsole::get_author_menu()
{
    std::string menu = "\n( 1) Show current posts\n"
                       "( 2) Show posts with filters\n"
                       "( 3) Show information about selected post\n"
                       "( 4) Add comment\n"
                       "( 5) Get full post\n"
                       "( 6) Show organizer of selected post\n"
                       "( 7) Add post\n"
                       "( 0) Exit\n"
                       "(-1) Log out\n";

    return menu;
}


void AuthorConsole::add_post(int user_id)
{
    std::string name, info, city, organizer;

    std::cout << "Input name:";
    std::cin >> name;
    std::cout << "Input information:";
    std::cin >> info;
    std::cout << "Input city:";
    std::cin >> city;
    std::cout << "Input organizer:";
    std::cin >> organizer;

    const time_t tm = time(nullptr);
    char date[64];
    strftime(date, std::size(date), "%d.%m.%Y", localtime(&tm));

    PostBL post = _author_service.create_post(user_id, name, info, city, organizer, date);
    if (post)
        std::cout << "Post successfully added" << std::endl;
    else
        std::cout << "Unable to add post" << std::endl;
}


void AuthorConsole::switch_author_menu(int command)
{
    switch (command)
    {
        case 1:
        {
            show_posts();
            break;
        }
        case 2: {
            show_posts_filters();
            break;
        }
        case 3:
        {
            show_post_information();
            break;
        }
        case 4:
        {
            add_comment(_id);
            break;
        }
        case 5:
        {
            show_full_post();
            break;
        }
        case 6:
        {
            show_organizer();
            break;
        }
        case 7:
        {
            add_post(_id);
            break;
        }
        default:
        {
            std::cout << "There is not such command..." << std::endl;
            break;
        }
    }
}