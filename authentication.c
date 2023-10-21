#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fonction.h"
bool has_account(char *username, char *passwd);

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
        if(has_account(username, passwd))
                redirect("rsyslog.cgi");
        else redirect("http://mandrindra.org");
        return 0;
}
bool has_account(char *username, char *passwd) {
        char *db_username, *db_passwd;
        FILE *database = fopen("/tmp/database", "r");
        while(!feof(database) && !ferror(database)){
                fscanf(database, "%m[^\t]\t%m[^\n]", &db_username, &db_passwd);
                if(strcmp(db_username, username) == 0 && strcmp(db_passwd, passwd) == 0) return true;
        }
        return false;
}