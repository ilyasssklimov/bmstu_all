#pragma once

#include <iostream>
#include <string>
#include <utility>


class Comment
{
public:
    Comment(std::string date, std::string text, int author_id, int post_id):
            _date(std::move(date)), _text(std::move(text)), _author_id(author_id), _post_id(post_id) {};
    Comment(): _author_id(-1), _post_id(-1) {};

    std::string get_date();
    std::string get_text();
    int get_author_id() const;
    int get_post_id() const;

    void set_date(const std::string &value);
    void set_text(const std::string &value);

    explicit operator bool() const { return _author_id != -1; }
    bool operator == (Comment comment) const
    {
        return comment.get_date() == _date &&
               comment.get_text() == _text &&
               comment.get_author_id() == _author_id &&
               comment.get_post_id() == _post_id;
    }

private:
    std::string _date;
    std::string _text;
    int _author_id;
    int _post_id;
};
