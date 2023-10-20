#include <stdio.h>
#include <stdlib.h>
#include "fonction.h"

int main(void) {
        printf("Content-type: text/html\n\n");
        printf("<html>");
        search();
        printf("<table border=\"1px\">");
        /* while(custom_logs->next_log != NULL){
                printf("<tr>");
                printf("<td>%s</td><td>%s</td><td>%s</td>", custom_logs->date, custom_logs->session_state, custom_logs->username);
                printf("</tr>");
                custom_logs = custom_logs->next_log;
        } */
        printf("</table>");
        printf("</html>");
        return 0;
}