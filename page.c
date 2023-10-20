#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fonction.h"


int main(){

        int first = 0, last = 0;
        char *env = getenv("QUERY_STRING");
        char **query = split(env, '&');
        char *username=malloc(strlen(split(query[0], '=')[1])+1);
        strcpy(username, split(query[0], '=')[1]);
        int page = atoi(split(query[1], '=')[1]);
        last = page * 10;
        first = last - 10;
        log_t *log = get_custom_logs(get_session(), username);
        if(!is_authenticated()) {
                redirect("http://localhost");
                return 0;
        }
        if(!log || !env || !query || !username){
                user_not_found();
                return 0;
        }
        log_t *tmp = log;
        int number_of_custom_logs = 0;
        while(tmp->next_log!=NULL){
                number_of_custom_logs++;
                tmp = tmp->next_log;
        }
        free(tmp);
        begin_html("Journal");
        header_html();
        search();
        printf(
        "<style>\
        table,tr, td{\
                        border-collapse: collapse;\
                        border: 1px solid;\
                        text-align:center\
                }\
        .line{\
                height:50px;\
                vertical-align: middle;\
        }\
        </style>\
        <table width=\"50%%\" style='margin-left:auto; margin-right:auto'>\
                <thead><tr>\
                <td>Date</td><td>Session</td><td>username</td>\
                </tr></thead>\
        ");
        log_t *actual_logs = go_to(log, first);
        for(int i = 0; i < 10 && actual_logs->next_log!=NULL; i++) {
                if(strcmp((actual_logs)->session_state, "opened") == 0){        
                        printf("<tr class=\"line\"><td>%s</t><td><p style='color: green'>%s</p></td><td><a href=\"./query.cgi?username=%s\">%s</a></td></tr>",
                        (actual_logs)->date, (actual_logs)->session_state, (actual_logs)->username, (actual_logs)->username);
                }else if(strcmp((actual_logs)->session_state, "failed") == 0){
                        printf("<tr class=\"line\"><td>%s</td><p style='color: yellow'>%s</p><td><a href=\"./query.cgi?username=%s\">%s</a></td></tr>", 
                        (actual_logs)->date, (actual_logs)->session_state, (actual_logs)->username, (actual_logs)->username);
                }else{
                        printf("<tr class=\"line\"><td>%s</t><td><p style='color: red'>%s</p></td><td><a href=\"./query.cgi?username=%s\">%s</a></td></tr>", 
                        (actual_logs)->date, (actual_logs)->session_state, (actual_logs)->username, (actual_logs)->username);
                }
                actual_logs = actual_logs->next_log;               
        }
        printf("</table>");
        other_page_html(number_of_custom_logs, actual_logs->username);
        end_html();
        free(log);
        free(query);
        free(username);
        return 0;
}