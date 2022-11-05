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

#include "controller/guest.hpp"


std::unordered_map<size_t, std::shared_ptr<void>> ServiceLocator::_instances;
void WebUI::instantiate()
{        
    ServiceLocator::instantiate<PGDatabaseAsync, IDataBase>(_db);

    ServiceLocator::instantiate<UserRepository, IUserRepository>();
    ServiceLocator::instantiate<PostRepository, IPostRepository>();
    ServiceLocator::instantiate<CommentRepository, ICommentRepository>();

    ServiceLocator::instantiate<GuestService>();
    ServiceLocator::instantiate<GuestController>();
}


int WebUI::run()
{ 
    oatpp::base::Environment::init();
    OatppComponent components;
    
    OATPP_COMPONENT(std::shared_ptr<oatpp::web::server::HttpRouter>, router);
    auto guest_controller = std::make_shared<OatppGuestController>();
    router->addController(guest_controller);

    instantiate();

    OATPP_COMPONENT(std::shared_ptr<oatpp::network::ConnectionHandler>, connectionHandler);
    OATPP_COMPONENT(std::shared_ptr<oatpp::network::ServerConnectionProvider>, connectionProvider);
    oatpp::network::Server server(connectionProvider, connectionHandler);
    OATPP_LOGI("LeisureAfisha", "Server running on port %s", connectionProvider->getProperty("port").getData());

    auto swagger_guest_controller = oatpp::swagger::Controller::createShared(guest_controller->getEndpoints()); 
    router->addController(swagger_guest_controller);
    
    server.run();
    oatpp::base::Environment::destroy();
    return 0;
}
