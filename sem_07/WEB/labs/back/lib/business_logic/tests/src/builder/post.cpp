#include "builder/post.h"
#include <cstdlib>
#include <ctime>


PostBuilder::PostBuilder() 
{
    std::srand((unsigned) std::time(nullptr));
}


std::string PostBuilder::get_random(int range)
{
    return std::to_string(std::rand() % range + 1);
}


PostBL PostBuilder::build(bool random) 
{
    if (random)
    {
        _visible = (std::rand() % 2) == 0 ? true : false;

        return PostBL(
            _name + get_random(), 
            std::rand() % 10 + 1, 
            _information + get_random(),
            _city + get_random(),
            _organizer + get_random(),
            get_random(30) + _date,
            _visible
        );
    }

    return PostBL(_name, _author_id, _information, _city, _organizer, _date, _visible);
}


PostBuilder PostBuilder::with_name(std::string name)
{
    _name = name;
    return *this;
}


PostBuilder PostBuilder::with_author_id(int author_id)
{
    _author_id = author_id;
    return *this;
}


PostBuilder PostBuilder::with_information(std::string information)
{
    _information = information;
    return *this;
}


PostBuilder PostBuilder::with_city(std::string city)
{
    _city = city;
    return *this;
}


PostBuilder PostBuilder::with_organizer(std::string organizer)
{
    _organizer = organizer;
    return *this;
}


PostBuilder PostBuilder::with_date(std::string date)
{
    _date = date;
    return *this;
}


PostBuilder PostBuilder::with_visible(bool visible)
{
    _visible = visible;
    return *this;
}
