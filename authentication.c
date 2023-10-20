#include <stdio.h>
#include <stdlib.h>
#include "fonction.h"

int main() {
        char *env = getenv("CONTENT_LENGTH");
        int len_data = atoi(env);
        FILE *auth = NULL;
        auth = fopen("/tmp/auth", "w");
        char *data = (char*)malloc(len_data+1);
        fread(data, 1, len_data, stdin);
        data[len_data+1] = '\0';
        char *username, *passwd;
        sscanf(data, "%*[^=]=%m[^&]%*[^=]=%m[^\n]",&username,&passwd);
        fprintf(auth, "%s\t%s", username, passwd);
        fclose(auth); 
        redirect("http://localhost/cgi-bin/rsyslog.cgi");
        return 0;
}
DO NOT COMPILE;
bool is_in_db(char *username) {
        FILE *database = fopen("/home/mandrindra/.database")
        return 0;
}