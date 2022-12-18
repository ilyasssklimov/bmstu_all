#include "model_dal/post.h"


std::string Post::get_name()
{
    return _name;
}


int Post::get_author_id() const
{
    return _author_id;
}


std::string Post::get_information()
{
    return _information;
}


std::string Post::get_city()
{
    return _city;
}


std::string Post::get_organizer()
{
    return _organizer;
}


std::string Post::get_date()
{
    return _date;
}


bool Post::get_visible() const
{
    return _visible;
}


void Post::set_name(const std::string &value)
{
    _name = value;
}


void Post::set_information(const std::string &value)
{
    _information = value;
}


void Post::set_city(const std::string &value)
{
    _city = value;
}


void Post::set_date(const std::string &value)
{
    _date = value;
}


void Post::set_visible(bool value)
{
    _visible = value;
}
