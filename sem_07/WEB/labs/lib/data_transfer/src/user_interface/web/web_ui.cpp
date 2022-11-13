#include "oatpp/network/Server.hpp"
#include "oatpp-swagger/Controller.hpp"

#include "user_interface/web/component.hpp"
#include "user_interface/web/web_ui.h"
#include "database/pg_database_async.h"
#include <repository/user.h>
#include <repository/post.h>
#include <repository/comment.h>

#include "controller/auth.hpp"
#include "controller/guest.hpp"
#include "controller/client.hpp"
#include "controller/author.hpp"
#include "controller/admin.hpp"


std::unordered_map<size_t, std::shared_ptr<void>> ServiceLocator::_instances;
void WebUI::instantiate()
{
    ServiceLocator::instantiate<PGDatabaseAsync, IDataBase>(_db);

    ServiceLocator::instantiate<UserRepository, IUserRepository>();
    ServiceLocator::instantiate<PostRepository, IPostRepository>();
    ServiceLocator::instantiate<CommentRepository, ICommentRepository>();

    ServiceLocator::instantiate<BearerAuthHandler>();
    ServiceLocator::instantiate<AuthService>();
    ServiceLocator::instantiate<AuthController>();

    ServiceLocator::instantiate<GuestService>();
    ServiceLocator::instantiate<GuestController>();

    ServiceLocator::instantiate<ClientService>();
    ServiceLocator::instantiate<ClientController>();

    ServiceLocator::instantiate<AuthorService>();
    ServiceLocator::instantiate<AuthorController>();

    ServiceLocator::instantiate<AdminService>();
    ServiceLocator::instantiate<AdminController>();
}


int WebUI::run()
{ 
    oatpp::base::Environment::init();
    OatppComponent components;
    
    OATPP_COMPONENT(std::shared_ptr<oatpp::web::server::HttpRouter>, router);
    instantiate();

    std::vector<std::shared_ptr<oatpp::web::server::api::ApiController>> controllers = {
        std::make_shared<OatppAuthController>(),
        std::make_shared<OatppGuestController>(),
        std::make_shared<OatppAdminController>(),
        std::make_shared<OatppClientController>(),
        std::make_shared<OatppAuthorController>()
    };
    for (auto& controller: controllers)
        router->addController(controller);

    OATPP_COMPONENT(std::shared_ptr<oatpp::network::ConnectionHandler>, connectionHandler);
    OATPP_COMPONENT(std::shared_ptr<oatpp::network::ServerConnectionProvider>, connectionProvider);
    oatpp::network::Server server(connectionProvider, connectionHandler);
    OATPP_LOGI("LeisureAfisha", "Server running on port %s", connectionProvider->getProperty("port").getData());
    
    oatpp::web::server::api::Endpoints docEndpoints;
    for (auto& controller: controllers)
        docEndpoints.append(controller->getEndpoints());
    router->addController(oatpp::swagger::Controller::createShared(docEndpoints)); 
    
    server.run();
    oatpp::base::Environment::destroy();
    return 0;
}
