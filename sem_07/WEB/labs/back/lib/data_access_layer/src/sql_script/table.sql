-- create table public.user
CREATE TABLE IF NOT EXISTS public.user (
    id SERIAL,
    name VARCHAR(50),
    surname VARCHAR(50),
    login VARCHAR(30),
    password VARCHAR(30),
    city VARCHAR(30),
    access CHAR,
    post_ids TEXT
);


-- create table public.post
CREATE TABLE IF NOT EXISTS public.post (
    id SERIAL,
    name VARCHAR(50),
    author_id INTEGER,
    information TEXT,
    city VARCHAR(30),
    organizer VARCHAR(50),
    date VARCHAR(10),
    visible BOOLEAN DEFAULT false
);


-- create table public.comment
CREATE TABLE IF NOT EXISTS public.comment (
    id SERIAL,
    date VARCHAR(10),
    text TEXT,
    author_id INTEGER,
    post_id INTEGER
);
