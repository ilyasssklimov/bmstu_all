#include "service/auth.h"
#include "logger.h"
#include "exception.h"


AuthService::AuthService()
{
    auto user_repo = ServiceLocator::resolve<IUserRepository>();

    if (!user_repo)
    {
        log_error("There are not repositories for AuthService");
        time_t time_now = time(nullptr);
        throw ServiceLocatorException(__FILE__, __LINE__, ctime(&time_now));
    }

    _user_repo = user_repo;
}


std::string AuthService::get_password(int user_id)
{
    try
    {
        UserBL user = _user_repo->get_user(user_id);
        log_info("Get password for user with id = " + std::to_string(user_id));
        return user.get_password();
    }
    catch (UserGetException &e)
    {
        log_error(e.what());
    }
    catch (...)
    {
        log_error("Some error while getting user");
    }

    return {};
}


std::string AuthService::get_access(int user_id)
{
    try
    {
        UserBL user = _user_repo->get_user(user_id);
        log_info("Get access for user with id = " + std::to_string(user_id));
        return user.get_access();
    }
    catch (UserGetException &e)
    {
        log_error(e.what());
    }
    catch (...)
    {
        log_error("Some error while getting user");
    }

    return {};
}


int AuthService::get_user_id(const std::string &login, const std::string &password)
{
    try
    {
        int user_id = _user_repo->get_user_id(login, password);
        log_info("Get user_id with login = " + login);
        return user_id;
    }
    catch (UserGetException &e)
    {
        log_error(e.what());
    }
    catch (...)
    {
        log_error("Some error while getting user_id");
    }

    return -1;

}
