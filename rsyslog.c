
#include "fonction.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char **argv) {
        
        FILE *auth_log = NULL;
        auth_log = fopen("/var/log/auth.log", "r");
        if(!is_authenticated()) {
                redirect("http://mandrindra.org");
                return 0;
        }
        if(auth_log == NULL){
                fprintf(stderr, "OPENING FILE: ERROR ON LINE %d\n", __LINE__);
                exit(EXIT_FAILURE);
        }
        log_t *logs = get_session();
        begin_html("Log");
        header_html();search();
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
        printf("<tbody>");
        while(logs != NULL) {
                if(strcmp((logs)->session_state, "opened") == 0){
                        printf("<tr class='line'><td>%s</td><td><p style='color: green'>%s</p></td><td><a href=\"./page.cgi?username=%s&page=1\">%s</a></td></tr>",
                        (logs)->date, (logs)->session_state, (logs)->username, (logs)->username);
                }else if(strcmp((logs)->session_state, "closed") == 0){
                        printf("<tr class='line'><td>%s</td><td><p style='color: red'>%s</p></td><td><a href=\"./page.cgi?username=%s&page=1\">%s</a></td></tr>", 
                        (logs)->date, (logs)->session_state, (logs)->username, (logs)->username);
                }else{
                        printf("<tr class='line'><td>%s</td><td><p style='color: yellow'>%s</p></td><td><a href=\"./page.cgi?username=%s&page=1\">%s</a></td></tr>", 
                        (logs)->date, (logs)->session_state, (logs)->username, (logs)->username);
                }
                logs = logs->next_log;
        }
        printf("</tbody>\
        </table>");
        end_html();
        fclose(auth_log);
        return 0;
}

