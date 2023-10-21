#ifndef LIST_H
#define LIST_H

#include <stdio.h>
#include <stdbool.h>

struct log{
        char date[60];
        char session_state[7];
        char username[20];
        struct log *next_log;
};
typedef struct log log_t;
char *make_readable(char *some_string);
log_t *get_session();
void user_not_found();
void print(log_t *logs);
log_t *get_custom_logs(log_t *general_logs, char *username);
void search();
void end_html();
void begin_html(char *title);
log_t *go_to(log_t *head, int position);
char **split(char *string_to_split, char separator);
void other_page_html(int line, char *username, int actual_page); 
// void home();
int redirect(const char *url);
bool is_authenticated();
void header_html();

#endif
