#include "repository/user.h"
#include "repository/post.h"
#include "repository/comment.h"
#include "console/guest.h"
#include "console/client.h"
#include "console/author.h"
#include "console/admin.h"
#include "user_interface/tech/technological_ui.h"



int TechnologicalUI::run()
{
    auto user_repo = std::make_shared<UserRepository>(_db);
    auto post_repo = std::make_shared<PostRepository>(_db);
    auto comment_repo = std::make_shared<CommentRepository>(_db);

    GuestService guest_service(post_repo, user_repo);
    ClientService client_service(post_repo, comment_repo, user_repo);
    AuthorService author_service(post_repo, comment_repo, user_repo);
    AdminService admin_service(post_repo, comment_repo, user_repo);

    GuestConsole guest_console(guest_service);
    ClientConsole client_console(client_service, 0);
    AuthorConsole author_console(author_service, 0);
    AdminConsole admin_console(admin_service, 0);

    char role = 'G';
    int command;
    UserBL guest_result;
    bool running = true;
    std::string menu = guest_console.get_guest_menu();

    while (running)
    {
        std::cout << menu << std::endl;
        std::cout << "Input command:";
        std::cin >> command;

        if (std::cin.fail())
        {
            std::cout << "Invalid command, try again" << std::endl;
            std::cin.clear();
            std::cin.ignore();
            continue;
        }

        if (command == 0)
        {
            std::cout << "You are out of the app :(" << std::endl;
            running = false;
            break;
        }
        else if (command == -1)
        {
            std::cout << "You log out from system" << std::endl;
            role = 'G';
            menu = guest_console.get_guest_menu();
            continue;
        }

        switch (role)
        {
            case 'G':
            {
                guest_result = guest_console.switch_guest_menu(command);
                if (guest_result)
                {
                    role = guest_result.get_access()[0];
                    int user_id = user_repo->get_user_id(guest_result);
                    if (role == 'C')
                    {
                        client_console = ClientConsole(client_service, user_id);
                        menu = client_console.get_client_menu();
                    }
                    else if (role == 'A')
                    {
                        author_console = AuthorConsole(author_service, user_id);
                        menu = author_console.get_author_menu();
                    }
                    else if (role == 'M')
                    {
                        admin_console = AdminConsole(admin_service, user_id);
                        menu = admin_console.get_admin_menu();
                    }
                }

                break;
            }
            case 'C':
            {
                client_console.switch_client_menu(command);
                break;
            }
            case 'A':
            {
                author_console.switch_author_menu(command);
                break;
            }
            case 'M':
            {
                admin_console.switch_admin_menu(command);
                break;
            }
            default:
            {
                std::cout << "Unknown role..." << std::endl;
                break;
            }
        }

    }

    return 0;
}
