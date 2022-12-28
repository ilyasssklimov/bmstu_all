#pragma once

#include "web_ui.h"

#include "oatpp/web/server/HttpConnectionHandler.hpp"
#include "oatpp/network/tcp/server/ConnectionProvider.hpp"
#include "oatpp/parser/json/mapping/ObjectMapper.hpp"
#include "oatpp/core/macro/component.hpp"

#include "oatpp-swagger/Model.hpp"
#include "oatpp-swagger/Resources.hpp"
#include "oatpp-swagger/ControllerPaths.hpp"


class OatppComponent 
{
public:
    OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::network::ServerConnectionProvider>, serverConnectionProvider)([] {
        return oatpp::network::tcp::server::ConnectionProvider::createShared(
            {"localhost", (v_uint16) std::stoi(ServiceLocator::resolve<Server>()->get_port()), oatpp::network::Address::IP_4}
        );
    }());
  
    OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::web::server::HttpRouter>, httpRouter)([] {
        return oatpp::web::server::HttpRouter::createShared();
    }());
  
    OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::network::ConnectionHandler>, serverConnectionHandler)([] {
        OATPP_COMPONENT(std::shared_ptr<oatpp::web::server::HttpRouter>, router);
        return oatpp::web::server::HttpConnectionHandler::createShared(router);
    }());
  
    OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::data::mapping::ObjectMapper>, apiObjectMapper)([] {
        return oatpp::parser::json::mapping::ObjectMapper::createShared();
    }());

    OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::swagger::DocumentInfo>, swaggerDocumentInfo)([] {
        oatpp::swagger::DocumentInfo::Builder builder;  
        builder
         .setTitle("LeisureAfisha Swagger-UI")
         .setDescription("LeisureAfisha API with Swagger-UI")
         .setVersion("1.0")
         .setContactName("Klimov Ilya")
         .setContactUrl("https://github.com/ilyasssklimov")
         .addServer("http://localhost:" + ServiceLocator::resolve<Server>()->get_port(), "server on localhost")
         .addSecurityScheme("JWT-auth", oatpp::swagger::DocumentInfo::SecuritySchemeBuilder::DefaultBearerAuthorizationSecurityScheme());
         return builder.build();
    }());

    OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::swagger::Resources>, swaggerResources)([] {  
        //return oatpp::swagger::Resources::loadResources(OATPP_SWAGGER_RES_PATH);
        return oatpp::swagger::Resources::loadResources("/mnt/d/it/bmstu_all/sem_07/web/labs/back/static/api/");
    }());

    OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::swagger::ControllerPaths>, controllerPaths)([] {
        auto paths = std::make_shared<oatpp::swagger::ControllerPaths>();
        paths->apiJson = "api/v1/swagger.json";
        paths->ui = "api/v1";
        paths->uiResources = "api/{filename}";
        return paths;
    }());
};
