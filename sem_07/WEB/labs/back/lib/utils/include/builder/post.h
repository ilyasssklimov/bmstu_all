#pragma once

#include "model_bl/post.h"


class PostBuilder 
{
public:
    explicit PostBuilder();
    PostBL build(bool random=true);

    PostBuilder with_name(std::string name);
    PostBuilder with_author_id(int author_id);
    PostBuilder with_information(std::string information);
    PostBuilder with_city(std::string city);
    PostBuilder with_organizer(std::string organizer);
    PostBuilder with_date(std::string date);
    PostBuilder with_visible(bool visible);

private:
    std::string _name = "name_";
    int _author_id = 0;
    std::string _information = "information_";
    std::string _city = "city_";
    std::string _organizer = "organizer_";
    std::string _date = ".12.2022";
    bool _visible = false;

    std::string get_random(int range=10);
};