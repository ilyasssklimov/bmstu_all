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


oatpp::Object<PreviewOatpp> PostDTO::get_oatpp_object()
{
    auto preview = PreviewOatpp::createShared();
    
    preview->id = get_id();
    preview->name = get_name(); 
    preview->author = get_author().get_oatpp_object();
    preview->information = get_information();
    preview->city = get_city();
    preview->date = get_date();

    return preview;
}


oatpp::Object<PreviewsOatpp> PostDTO::get_oatpp_previews(std::vector<PostDTO> posts_dto)
{  
    auto previews = PreviewsOatpp::createShared();
    previews->previews = {};

    for (auto& post_dto: posts_dto)
    {
        auto preview = post_dto.get_oatpp_object();
        previews->previews->push_back(preview);
    }

    return previews;
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


oatpp::Object<PostOatpp> FullPostDTO::get_oatpp_object()
{
    auto post = PostOatpp::createShared();
    
    post->id = get_id();
    post->name = get_name(); 
    post->author = get_author().get_oatpp_object();
    post->information = get_information();
    post->organizer = get_organizer();
    post->city = get_city();
    post->date = get_date();
    post->comments = CommentDTO::get_oatpp_comments(get_comments());

    return post;
}


oatpp::Object<PostsOatpp> FullPostDTO::get_oatpp_posts(std::vector<FullPostDTO> posts_dto)
{  
    auto posts = PostsOatpp::createShared();
    posts->posts = {};

    for (auto& post_dto: posts_dto)
    {
        auto post = post_dto.get_oatpp_object();
        posts->posts->push_back(post);
    }

    return posts;
}