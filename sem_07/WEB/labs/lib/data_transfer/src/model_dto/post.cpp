#include "model_dto/post.h"


PostDTO::PostDTO(int post_id, UserDTO author, PostBL post_bl)
{
    _id = post_id;
    _name = post_bl.get_name();
    _author = author;
    _information = post_bl.get_information();
    _city = post_bl.get_city();
    _date = post_bl.get_date();
}


int PostDTO::get_id()
{
    return _id;
}


std::string PostDTO::get_name()
{
    return _name;
}


UserDTO PostDTO::get_author()
{
    return _author;
}


std::string PostDTO::get_information()
{
    return _information;
}


std::string PostDTO::get_city()
{
    return _city;
}


std::string PostDTO::get_date()
{
    return _date;
}


FullPostDTO::FullPostDTO(int post_id, UserDTO author, PostBL post_bl, std::vector<CommentDTO> comments): 
    PostDTO(post_id, author, post_bl)
{
    _organizer = post_bl.get_organizer();
    _comments = comments;
}


std::string FullPostDTO::get_organizer()
{
    return _organizer;
}


std::vector<CommentDTO> FullPostDTO::get_comments()
{
    return _comments;
}
