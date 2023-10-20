#include "fonction.h"
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <stdbool.h>

void header_html() {
        printf("\
        <style>\
                input.submit{\
                        background-color: #1b3514;\
                        color: aliceblue;\
                        border-radius: 6px;\
                        border: 1px solid #1b3514;\
                        font-family: 'JetBrains Mono';\
                        font-size: 19px;\
                        padding: 4px;\
                }\
                a {text-decoration: none;}\
                a:hover {\
                        font-size:23px;\
                }\
                a.head{\
                        font-family: 'JetBrains Mono';\
                        font-size: 23px;\
                        text-decoration: none;\
                }</style>\
        <header style=\"display: flex;justify-content: space-between;align-items: center;\">\
                <div><a class='head' href=\"rsyslog.cgi\">Home</a></div>\
                <div><form action=\"logout.cgi\"><input type=\"submit\" value=\"Log out\" class='submit'></form></div>\
        </header>\
        ");

}

bool is_authenticated() {
        FILE *auth = NULL;
        auth = fopen("/tmp/auth", "r");
        if(auth != NULL) {
                fclose(auth);
                return true;
        }
        else return false;
        
}


void begin_html(char *title) {
        printf("Content-type: text/html\n\n");
        printf(
        "<html lang=\"en\">"
        "<head>"
        "<meta charset=\"UTF-8\">"
        "<title>%s</title>"
        "</head>"
        "<body>"
        , title);
}
void end_html() {
        printf("</body>"
        "</html>"
        );

}

int math_round(float intyaho) {
        int a=(int)intyaho;
        if(a-intyaho == 0) return a;
        else return (int)a+1;
}

void search() {
        printf(
        "<form action=\"page.cgi\" method=\"get\">"
        "<div style=\"display:flex;justify-content:center;\">"
        "<input type=\"text\" name=\"username\" style=\"border-radius:6px;border: 1px solid #1b3514;\" placeholder=\"Your username here...\">"
        "<input type=\"hidden\" name=\"page\" value=\"1\">"
        "<input type=\"submit\" value=\"Find\" style=\"border: 1px solid #1b3514;border-radius: 6px;margin-top: 5px;margin-bottom: 5px;color: white;background-color: #1b3514;width:50px;height:30px\">"
        "</div>"
        "</form>"
        );
}


log_t *go_to(log_t *head, int position) {
        for(int t = 0; t < position && (head->next_log != NULL); t++) {
                head = head->next_log;
        }
        if(head == NULL) return NULL;
        else return head;
}


log_t *create_new_log(char *date, char *session_state, char *username) {
        log_t *tmp = malloc(sizeof(log_t));
        if(tmp == NULL) { 
                fprintf(stderr, "Need more memory\n");
                exit(1);
        }
        strcpy(tmp->date, date);
        strcpy(tmp->session_state, session_state);
        strcpy(tmp->username, username);
        tmp->next_log = NULL;
        
        return tmp;
}

log_t *get_session() {
        FILE *auth_log = NULL;
        auth_log = fopen("/var/log/auth.log", "r");
        if(auth_log == NULL){
                fprintf(stderr, "ERROR ON LINE %d\n", __LINE__);
                exit(EXIT_FAILURE);
        }
        char month[] = "december";
        char day[] = "31";
        char hour[] = "10:56:25";
        char full_date[30];
        char line[255] = "", _username[255];char session_type[7];
        log_t *head = NULL; log_t *tmp = NULL;
        while(fgets(line, 255, auth_log)){
                if(strstr(line, "for user") != NULL) {
                        sscanf(line, "%[^ ] %[^ ] %[^ ] %*[^ ] %*[^ ] %*[^ ] %*[^ ] %[^ ] %*[^ ] %*[^ ] %[^\n]", month, day, hour, session_type, _username);
                        sprintf(full_date, "%s %s %s", month, day, hour);
                        tmp = create_new_log(full_date, session_type, make_readable(_username));
                        tmp->next_log = head;
                        head = tmp;
                }
        }

        fclose(auth_log);
        return head;
}
log_t *get_custom_logs(log_t *general_logs, char *username) {
        log_t *head = NULL, *element = NULL;
        while(general_logs->next_log != NULL) {
                if(strcmp(general_logs->username, username) == 0) {
                        element = create_new_log(general_logs->date, general_logs->session_state, general_logs->username);
                        element->next_log = head;
                        head = element;
                }
                general_logs = general_logs->next_log;
        }
        return head;
}

char* make_readable(char *some_string) {
        char *user = malloc(strlen(some_string));
        for(int i = 0, j = 0; i < strlen(some_string); i++) {
                if(isalpha(some_string[i])) {
                        user[j] = some_string[i];
                        j++;
                }
                if(i != 0 && (isspace(some_string[i]) || ispunct(some_string[i]))) return user;
        }
        return user;
}

void print(log_t *logs) {
        while(logs->next_log != NULL) {
                printf("%s\n", logs->username);
                logs = logs->next_log;
        }
}


/*
split implementation in c

*/

char **split(char *string_to_split, char separator) {
	char **splited=NULL;
	int j=0,k=0,count=0;

	/*
	Counting the number of field
	*/
	for(int i=0;i<strlen(string_to_split);i++){
		if(string_to_split[i]==separator) count++;
	}
	/*
	Allocate the appropriate memory size: no wasted memory
	*/
	splited=(char**)calloc(sizeof(char*),count+1);
	for(int i=0;i<count+1;i++){
		*(splited+i)=(char*)calloc(1,50);
	}


	for(int i=0;i<strlen(string_to_split);i++){
		if(string_to_split[i]==separator){
			k++;
			j=0;
		}else{
			*(*(splited+k)+j) = string_to_split[i];
			j++;
		}
	}
	return splited;
}

void user_not_found(){
                printf("Content-type: text/html\n\n");
                printf("<html>");
                printf("<h1 style=\"text-align:center;\"> User not found<br>"
                "<strong><a href=\"./rsyslog.cgi\">HOME</a><strong></h1>");
                printf("</html>");
}
void other_page_html(int line, char *username) {
        int total_page = math_round((float)line/10);
        for(int i = 0; i < total_page; i++) {
        // printf("<div'>");
        printf(
                
                "<form action=\"page.cgi\" method=\"get\" style=\"display: inline;\">" 
                "<input type=\"hidden\" name=\"username\" value=\"%s\">"
                "<input type=\"submit\" value=\"%d\" name=\"page\">"
                "</form>"
                
                , username, i+1
        );
        // printf("</div>");
        }

}
int redirect(const char *url) {
        printf("Content-type: text/html\n\n");
        printf("<html><head>");
        /* printf("<script>");
        printf("history.pushState(null, null, location.href);");
        printf("window.onpopstate = function(event) {");
        printf("history.go(1);");
        printf("};");
        printf("</script>"); */
        printf("<meta http-equiv=\"refresh\" content=\"0;url=%s\"></meta></head></html>",url);
        return 90;
}