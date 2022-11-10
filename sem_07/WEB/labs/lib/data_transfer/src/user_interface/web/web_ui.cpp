#include "oatpp/network/Server.hpp"
#include "oatpp-swagger/Controller.hpp"

#include "logger.h"
#include "locator.hpp"

#include "user_interface/web/component.hpp"
#include "user_interface/web/web_ui.h"
#include "database/pg_database_async.h"
#include <repository/user.h>
#include <repository/post.h>
#include <repository/comment.h>
#include "controller/oatpp.hpp"


std::unordered_map<size_t, std::shared_ptr<void>> ServiceLocator::_instances;
void WebUI::instantiate()
{        
    ServiceLocator::instantiate<PGDatabaseAsync, IDataBase>(_db);

    ServiceLocator::instantiate<UserRepository, IUserRepository>();
    ServiceLocator::instantiate<PostRepository, IPostRepository>();
    ServiceLocator::instantiate<CommentRepository, ICommentRepository>();

    ServiceLocator::instantiate<AuthService>();
    ServiceLocator::instantiate<GuestService>();
    ServiceLocator::instantiate<ClientService>();
    ServiceLocator::instantiate<AuthorService>();
    ServiceLocator::instantiate<AdminService>();

    ServiceLocator::instantiate<AuthController>();
    ServiceLocator::instantiate<GuestController>();
    ServiceLocator::instantiate<ClientController>();
    ServiceLocator::instantiate<AuthorController>();
    ServiceLocator::instantiate<AdminController>();
}


int WebUI::run()
{ 
    oatpp::base::Environment::init();
    OatppComponent components;
    
    OATPP_COMPONENT(std::shared_ptr<oatpp::web::server::HttpRouter>, router);
    instantiate();

    auto controller = std::make_shared<OatppController>();
    router->addController(controller);

    OATPP_COMPONENT(std::shared_ptr<oatpp::network::ConnectionHandler>, connectionHandler);
    OATPP_COMPONENT(std::shared_ptr<oatpp::network::ServerConnectionProvider>, connectionProvider);
    oatpp::network::Server server(connectionProvider, connectionHandler);
    OATPP_LOGI("LeisureAfisha", "Server running on port %s", connectionProvider->getProperty("port").getData());

    auto swagger_controller = oatpp::swagger::Controller::createShared(controller->getEndpoints()); 
    router->addController(swagger_controller);
    
    server.run();
    oatpp::base::Environment::destroy();
    return 0;
}
