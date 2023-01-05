-- function that adds constraint if it doesn't exist
CREATE OR REPLACE FUNCTION public.create_constraint (t_name text, c_name text, c_sql text)
RETURNS VOID AS
$$
BEGIN
    IF NOT EXISTS (SELECT constraint_name
                   FROM information_schema.constraint_column_usage
                   WHERE table_name = t_name AND constraint_name = c_name) THEN
        EXECUTE c_sql;
    END IF;
END;
$$
LANGUAGE 'plpgsql';


-- create constraints to public.user
SELECT public.create_constraint (
    'user',
    'user_pkey',
    'ALTER TABLE public.user ADD CONSTRAINT user_pkey PRIMARY KEY (id);'
);

SELECT public.create_constraint(
    'user',
    'user_name_check',
    'ALTER TABLE public.user ADD CONSTRAINT user_name_check CHECK (name IS NOT NULL);'
);

SELECT public.create_constraint(
    'user',
    'user_login_check',
    'ALTER TABLE public.user ADD CONSTRAINT user_login_check CHECK (login IS NOT NULL);'
);

SELECT public.create_constraint(
    'user',
    'user_password_check',
    'ALTER TABLE public.user ADD CONSTRAINT user_password_check CHECK (password IS NOT NULL);'
);

SELECT public.create_constraint(
    'user',
    'user_access_check',
    'ALTER TABLE public.user ADD CONSTRAINT user_access_check CHECK (access IS NOT NULL);'
);


-- create constraints to public.post
SELECT public.create_constraint (
    'post',
    'post_pkey',
    'ALTER TABLE public.post ADD CONSTRAINT post_pkey PRIMARY KEY (id);'
);

SELECT public.create_constraint(
    'post',
    'post_name_check',
    'ALTER TABLE public.post ADD CONSTRAINT post_name_check CHECK (name IS NOT NULL);'
);

SELECT public.create_constraint (
    'user',
    'post_author_id_fkey',
    'ALTER TABLE public.post ADD CONSTRAINT post_author_id_fkey FOREIGN KEY (author_id) REFERENCES public.user (id);'
);

SELECT public.create_constraint(
    'post',
    'post_city_check',
    'ALTER TABLE public.post ADD CONSTRAINT post_city_check CHECK (city IS NOT NULL);'
);

SELECT public.create_constraint(
    'post',
    'post_organizer_check',
    'ALTER TABLE public.post ADD CONSTRAINT post_organizer_check CHECK (organizer IS NOT NULL);'
);

SELECT public.create_constraint(
    'post',
    'post_date_check',
    'ALTER TABLE public.post ADD CONSTRAINT post_date_check CHECK (date IS NOT NULL);'
);

SELECT public.create_constraint(
    'post',
    'post_visible_check',
    'ALTER TABLE public.post ADD CONSTRAINT post_visible_check CHECK (visible IS NOT NULL);'
);


-- create constraints to public.comment
SELECT public.create_constraint (
    'comment',
    'comment_pkey',
    'ALTER TABLE public.comment ADD CONSTRAINT comment_pkey PRIMARY KEY (id);'
);

SELECT public.create_constraint(
    'comment',
    'comment_date_check',
    'ALTER TABLE public.comment ADD CONSTRAINT comment_date_check CHECK (date IS NOT NULL);'
);

SELECT public.create_constraint(
    'comment',
    'comment_text_check',
    'ALTER TABLE public.comment ADD CONSTRAINT comment_text_check CHECK (text IS NOT NULL);'
);

SELECT public.create_constraint (
    'user',
    'comment_author_id_fkey',
    'ALTER TABLE public.comment ADD CONSTRAINT comment_author_id_fkey FOREIGN KEY (author_id) REFERENCES public.user (id);'
);

SELECT public.create_constraint (
    'post',
    'comment_post_id_fkey',
    'ALTER TABLE public.comment ADD CONSTRAINT comment_post_id_fkey FOREIGN KEY (post_id) REFERENCES public.post (id);'
);
