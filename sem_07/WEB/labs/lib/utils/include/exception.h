#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <iostream>
#include <string>
#include <exception>


class BaseException: public std::exception
{
public:
    BaseException(const std::string &filename, const int line, const char *time, const std::string &message);
    const char *what() const noexcept override;

protected:
    std::string error;
};


class PostGetException: public BaseException
{
public:
    PostGetException(const std::string &filename, const int line, const char *time):
    BaseException(filename, line, time, "Unable to get post.") {};
};


class PostIdGetException: public BaseException
{
public:
    PostIdGetException(const std::string &filename, const int line, const char *time):
    BaseException(filename, line, time, "Unable to get post id.") {};
};


class PostsGetException: public BaseException
{
public:
    PostsGetException(const std::string &filename, const int line, const char *time):
    BaseException(filename, line, time, "Unable to get all post.") {};
};


class PostDeleteException: public BaseException
{
public:
    PostDeleteException(const std::string &filename, const int line, const char *time):
    BaseException(filename, line, time, "Unable to delete post.") {};
};


class PostUpdateException: public BaseException
{
public:
    PostUpdateException(const std::string &filename, const int line, const char *time):
    BaseException(filename, line, time, "Unable to update post.") {};
};


class PostsFilterGetException: public BaseException
{
public:
    PostsFilterGetException(const std::string &filename, const int line, const char *time):
    BaseException(filename, line, time, "Unable to get posts with filters.") {};
};


class CommentAddException: public BaseException
{
public:
    CommentAddException(const std::string &filename, const int line, const char *time):
    BaseException(filename, line, time, "Unable to add comment.") {};
};


class CommentGetException: public BaseException
{
public:
    CommentGetException(const std::string &filename, const int line, const char *time):
    BaseException(filename, line, time, "Unable to get comment.") {};
};


class CommentsGetException: public BaseException
{
public:
    CommentsGetException(const std::string &filename, const int line, const char *time):
    BaseException(filename, line, time, "Unable to get comment.") {};
};


class CommentDeleteException: public BaseException
{
public:
    CommentDeleteException(const std::string &filename, const int line, const char *time):
    BaseException(filename, line, time, "Unable to delete comment.") {};
};


class CommentUpdateException: public BaseException
{
public:
    CommentUpdateException(const std::string &filename, const int line, const char *time):
    BaseException(filename, line, time, "Unable to update comment.") {};
};


class PostAddException: public BaseException
{
public:
    PostAddException(const std::string &filename, const int line, const char *time):
    BaseException(filename, line, time, "Unable to add post.") {};
};


class UserGetException: public BaseException
{
public:
    UserGetException(const std::string &filename, const int line, const char *time):
    BaseException(filename, line, time, "Unable to get user.") {};
};


class UsersGetException: public BaseException
{
public:
    UsersGetException(const std::string &filename, const int line, const char *time):
    BaseException(filename, line, time, "Unable to get all users.") {};
};


class UserAddException: public BaseException
{
public:
    UserAddException(const std::string &filename, const int line, const char *time):
    BaseException(filename, line, time, "Unable to add user.") {};
};


class UserUpdateException: public BaseException
{
public:
    UserUpdateException(const std::string &filename, const int line, const char *time):
    BaseException(filename, line, time, "Unable to update user.") {};
};


class UserDeleteException: public BaseException
{
public:
    UserDeleteException(const std::string &filename, const int line, const char *time):
    BaseException(filename, line, time, "Unable to delete user.") {};
};


class AdminFindException: public BaseException
{
public:
    AdminFindException(const std::string &filename, const int line, const char *time):
    BaseException(filename, line, time, "Unable to find admin.") {};
};


class MovieGetException: public BaseException
{
public:
    MovieGetException(const std::string &filename, const int line, const char *time):
            BaseException(filename, line, time, "Unable to get movie.") {};
};


class MovieIdGetException: public BaseException
{
public:
    MovieIdGetException(const std::string &filename, const int line, const char *time):
            BaseException(filename, line, time, "Unable to get movie id.") {};
};


class MoviesGetException: public BaseException
{
public:
    MoviesGetException(const std::string &filename, const int line, const char *time):
            BaseException(filename, line, time, "Unable to get all movie.") {};
};


class MovieDeleteException: public BaseException
{
public:
    MovieDeleteException(const std::string &filename, const int line, const char *time):
            BaseException(filename, line, time, "Unable to delete movie.") {};
};


class MovieUpdateException: public BaseException
{
public:
    MovieUpdateException(const std::string &filename, const int line, const char *time):
            BaseException(filename, line, time, "Unable to update movie.") {};
};


class MoviesFilterGetException: public BaseException
{
public:
    MoviesFilterGetException(const std::string &filename, const int line, const char *time):
            BaseException(filename, line, time, "Unable to get movies with filters.") {};
};


class MovieAddException: public BaseException
{
public:
    MovieAddException(const std::string &filename, const int line, const char *time):
            BaseException(filename, line, time, "Unable to add movie.") {};
};


class ConnectionException: public BaseException
{
public:
    ConnectionException(const std::string &filename, const int line, const char *time):
            BaseException(filename, line, time, "Unable to connect to DB.") {};
};


class ServiceLocatorException: public BaseException
{
public:
    ServiceLocatorException(const std::string &filename, const int line, const char *time):
            BaseException(filename, line, time, "Unable to get services from ServiceLocator.") {};
};


#endif  // EXCEPTION_H
