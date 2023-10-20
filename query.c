#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "fonction.h"
int number_of_custom_logs = 0;


int main() {
        
        
        printf("Content-type: text/html\n\n");
        printf("<html>");
        //
        char *env = getenv("QUERY_STRING");
        char **query_string = split(env, '=');
        char username[20];
        strcpy(username, query_string[1]);
        log_t *general_logs = get_session();
        log_t *custom_logs = get_custom_logs(general_logs, username);
        if(custom_logs == NULL || general_logs == NULL){
                user_not_found();
                return 0;
        }
        //

        search();
        printf("<p>Cliquez<a href=\"./rsyslog.cgi\"> Ici </a> Pour tous les utilisateurs</p>");
        printf("<table border=\"1px\" width=\"100%%\">");
        while(custom_logs->next_log != NULL){
                if(strcmp((custom_logs)->session_state, "opened") == 0){        
                        printf("<tr bgcolor=\"green\" ><td>%s</t><td>%s</td><td><a href=\"./query.cgi?username=%s\">%s</a></td></tr>",
                        (custom_logs)->date, (custom_logs)->session_state, (custom_logs)->username, (custom_logs)->username);
                }else if(strcmp((custom_logs)->session_state, "failed") == 0){
                        printf("<tr bgcolor=\"yellow\" ><td>%s</t><td>%s</td><td><a href=\"./query.cgi?username=%s\">%s</a></td></tr>", 
                        (custom_logs)->date, (custom_logs)->session_state, (custom_logs)->username, (custom_logs)->username);
                }else{
                        printf("<tr bgcolor=\"red\" ><td>%s</t><td>%s</td><td><a href=\"./query.cgi?username=%s\">%s</a></td></tr>", 
                        (custom_logs)->date, (custom_logs)->session_state, (custom_logs)->username, (custom_logs)->username);
                }
                custom_logs = custom_logs->next_log;
                number_of_custom_logs++;
        }
        printf("</table>");
        other_page_html(number_of_custom_logs, custom_logs->username);     
        printf("</html>");    
        return 0;
}