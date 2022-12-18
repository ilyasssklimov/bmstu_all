#include "console/guest.h"


std::string GuestConsole::get_guest_menu()
{
    std::string menu = "\n(1) Show current posts\n"
                       "(2) Show information about selected post\n"
                       "(3) Register\n"
                       "(4) Log in\n"
                       "(0) Exit\n";

    return menu;
}


UserBL GuestConsole::show_posts()
{
    std::vector<PostBL> posts = _guest_service.get_posts();
    std::vector<int> posts_ids = _guest_service.get_posts_ids(posts);
    for (size_t i = 0; i < posts.size(); i++)
        std::cout << posts_ids[i] << " | " << posts[i].get_name() << " | " << posts[i].get_city() <<
        " | " << posts[i].get_date() << std::endl;

    return {};
}


UserBL GuestConsole::show_post_information()
{
    int post_id;
    std::cout << "Input post of id:";
    std::cin >> post_id;

    if (std::cin.fail())
    {
        std::cout << "Id should be integer" << std::endl;
        std::cin.clear();
        std::cin.ignore();
    }
    else
    {
        PostBL post = _guest_service.get_post(post_id);
        if (post)
            std::cout << "Information: " << post.get_information() << std::endl;
        else
            std::cout << "There is not post with id = " << post_id << std::endl;
    }

    return {};
}


UserBL GuestConsole::sign_in()
{
    std::string name, surname, login, password, city, access;
    std::cout << "Input data" << std::endl;

    std::cout << "Name:";
    std::cin >> name;
    std::cout << "Surname:";
    std::cin >> surname;
    std::cout << "Login:";
    std::cin >> login;
    std::cout << "Password:";
    std::cin >> password;
    std::cout << "City:";
    std::cin >> city;
    std::cout << "Access - client(C), author(A):";
    std::cin >> access;

    if (access == "C" || access == "A")
    {
        UserBL user = _guest_service.sign_up(name, surname, login, password, city, access);
        if (user)
            std::cout << "You registered successfully!" << std::endl;
        else
            std::cout << "There is error while registration" << std::endl;
    }
    else
        std::cout << "Access should be C or A" << std::endl;

    return {};
}


UserBL GuestConsole::log_in()
{
    std::string login, password;
    std::cout << "Input login:";
    std::cin >> login;
    std::cout << "Input password:";
    std::cin >> password;

    UserBL user = _guest_service.sign_in(login, password);
    if (user)
    {
        std::cout << "Success log in system" << std::endl;
        return user;
    }
    else
    {
        std::cout << "Failure while logging in system" << std::endl;
        return {};
    }
}


UserBL GuestConsole::switch_guest_menu(int command)
{
    switch (command)
    {
        case 1:
            return show_posts();
        case 2:
            return show_post_information();
        case 3:
            return sign_in();
        case 4:
            return log_in();
        default:
        {
            std::cout << "There is not such command..." << std::endl;
            return {};
        }
    }
}

