#pragma once

#include <iostream>
#include <string>
#include <utility>


class PostBL
{
public:
    PostBL(std::string name, int author_id, std::string information, std::string city, std::string organizer,
           std::string date, bool visible):
           _name(std::move(name)), _author_id(author_id), _information(std::move(information)),
           _city(std::move(city)), _organizer(std::move(organizer)), _date(std::move(date)), _visible(visible) {};
    PostBL(): _author_id(-1) {};

    std::string get_name();
    int get_author_id() const;
    std::string get_information();
    std::string get_city();
    std::string get_organizer();
    std::string get_date();
    bool get_visible() const;

    explicit operator bool() const { return _author_id != -1; }
    bool operator == (PostBL post) const
    {
        return post.get_name() == _name &&
        post.get_author_id() == _author_id &&
        post.get_information() == _information &&
        post.get_city() == _city &&
        post.get_organizer() == _organizer &&
        post.get_date() == _date;
    }

private:
    std::string _name;
    int _author_id;
    std::string _information;
    std::string _city;
    std::string _organizer;
    std::string _date;
    bool _visible;
};
