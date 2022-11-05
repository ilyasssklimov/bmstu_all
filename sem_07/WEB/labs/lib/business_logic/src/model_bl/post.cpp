#include "model_bl/post.h"


std::string PostBL::get_name()
{
    return _name;
}


int PostBL::get_author_id() const
{
    return _author_id;
}


std::string PostBL::get_information()
{
    return _information;
}


std::string PostBL::get_city()
{
    return _city;
}


std::string PostBL::get_organizer()
{
    return _organizer;
}


std::string PostBL::get_date()
{
    return _date;
}


bool PostBL::get_visible() const
{
    return _visible;
}
