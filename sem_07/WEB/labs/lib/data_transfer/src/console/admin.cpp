#include "console/admin.h"


std::string AdminConsole::get_admin_menu()
{
    std::string menu = "\n( 1) Show current posts\n"
                       "( 2) Show posts with filters\n"
                       "( 3) Show information about selected post\n"
                       "( 4) Add comment\n"
                       "( 5) Get full post\n"
                       "( 6) Show organizer of selected post\n"
                       "( 7) Submit post\n"
                       "( 0) Exit\n"
                       "(-1) Log out\n";

    return menu;
}


void AdminConsole::submit_post()
{
    std::vector<PostBL> posts = _admin_service.get_waiting_posts();
    if (!posts.empty())
    {
        std::vector<int> posts_ids = _admin_service.get_posts_ids(posts);
        std::cout << "Waiting posts:" << std::endl;
        for (size_t i = 0; i < posts.size(); i++)
            std::cout << posts_ids[i] << " | " << posts[i].get_name() << " | " << posts[i].get_city()
            << " | " << posts[i].get_date() << std::endl;

        int post_id;
        std::cout << "Select an id to submit:";
        std::cin >> post_id;
        if (std::cin.fail())
        {
            std::cout << "Id should be integer" << std::endl;
            std::cin.clear();
            std::cin.ignore();
        }
        else
        {
            PostBL submitting_post = _admin_service.submit_post(_admin_service.get_post(post_id));
            if (submitting_post)
                std::cout << "Post successfully added" << std::endl;
            else
                std::cout << "There is not post with id = " << post_id << std::endl;
        }
    }
    else
        std::cout << "There are not waiting posts to submit" << std::endl;
}


void AdminConsole::switch_admin_menu(int command)
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
            submit_post();
            break;
        }
        default:
        {
            std::cout << "There is not such command..." << std::endl;
            break;
        }
    }
}