#include "console/client.h"


std::string ClientConsole::get_client_menu()
{
    std::string menu = "\n( 1) Show current posts\n"
                       "( 2) Show posts with filters\n"
                       "( 3) Show information about selected post\n"
                       "( 4) Add comment\n"
                       "( 5) Get full post\n"
                       "( 6) Show organizer of selected post\n"
                       "( 0) Exit\n"
                       "(-1) Log out\n";

    return menu;
}


void ClientConsole::show_posts_filters()
{
    std::string date, name, city, author;

    std::cout << "Input date:";
    std::cin >> date;
    std::cout << "Input name:";
    std::cin >> name;
    std::cout << "Input city:";
    std::cin >> city;
    std::cout << "Input author";
    std::cin >> author;

    std::vector<PostBL> posts = _client_service.get_posts(date, name, city, author);
    for (auto &post: posts)
        std::cout << post.get_name() << " | " << post.get_city() << " | " << post.get_date() << std::endl;
}


void ClientConsole::add_comment(int user_id)
{
    int post_id;
    std::string comment;

    std::cout << "Input post id:";
    std::cin >> post_id;
    if (std::cin.fail())
    {
        std::cout << "Id should be integer" << std::endl;
        std::cin.clear();
        std::cin.ignore();
    }
    else
    {
        std::cout << "Input comment:";
        std::cin >> comment;

        const time_t tm = time(nullptr);
        char date[64];
        strftime(date, std::size(date), "%d.%m.%Y", localtime(&tm));

        CommentBL adding_comment = _client_service.add_comment(date, comment, user_id, post_id);
        if (adding_comment)
            std::cout << "Comment successfully adding" << std::endl;
        else
            std::cout << "Unable to add comment" << std::endl;
    }
}


void ClientConsole::show_full_post()
{
    int post_id;

    std::cout << "Input post id:";
    std::cin >> post_id;
    if (std::cin.fail())
    {
        std::cout << "Id should be integer" << std::endl;
        std::cin.clear();
        std::cin.ignore();
    }
    else
    {
        PostBL post = _client_service.get_post(post_id);
        std::vector<CommentBL> comments = _client_service.get_comments(post_id);

        if (post)
        {
            std::cout << post.get_name() << " | " << post.get_city() << " | " << post.get_date() << std::endl;
            std::cout << "Comments:" << std::endl;
            for (auto &comment: comments)
                std::cout << comment.get_date() << " | " << comment.get_text() << " | " << comment.get_author_id() << std::endl;
        }
    }
}


void ClientConsole::show_organizer()
{
    int post_id;
    std::cout << "Input post of id:";
    std::cin >> post_id;

    if (std::cin.fail()) {
        std::cout << "Id should be integer" << std::endl;
        std::cin.clear();
        std::cin.ignore();
    } else {
        PostBL post = _client_service.get_post(post_id);
        if (post)
            std::cout << "Organizer: " << post.get_organizer() << std::endl;
        else
            std::cout << "There is not post with id = " << post_id << std::endl;
    }
}


void ClientConsole::switch_client_menu(int command)
{
    switch (command)
    {
        case 1:
        {
            show_posts();
            break;
        }
        case 2:
        {
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
        default:
        {
            std::cout << "There is not such command..." << std::endl;
            break;
        }
    }
}
