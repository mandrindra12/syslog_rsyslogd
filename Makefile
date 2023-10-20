CFLAGS=-Wall -O2


all: rsyslog.cgi cgi mv query.cgi mv-query page.cgi mv-page mv-rsyslog \
     authentication.cgi mv-authentication inscription.cgi logout.cgi mv-logout

authentication.cgi: authentication.c fonction.c
	cc -o $@ $^ $(CFLAGS)

logout.cgi: logout.c fonction.c
	cc -o $@ $^ $(CFLAGS)

mv-logout: 
	mv logout.cgi /srv/http/cgi-bin/

mv-authentication:
	mv authentication.cgi /srv/http/cgi-bin/

inscription.cgi: inscription.c fonction.c
	cc -o $@ $^ $(CFLAGS)

mv-inscription: 
	mv inscription.cgi /srv/http/cgi-bin/

main: main.c fonction.c
	cc -o $@ $^

rsyslog.cgi: rsyslog.c fonction.c
	cc -o $@ $^ $(CFLAGS)

mv-rsyslog:
	mv rsyslog.cgi /srv/http/cgi-bin/

cgi: main.c fonction.c
	cc -o list.cgi $^ $(CFLAGS)

mv:
	mv list.cgi /srv/http/cgi-bin/

query.cgi: query.c fonction.c
	cc -o $@ $^ $(CFLAGS)

page.cgi: page.c fonction.c 
	cc -o $@ $^ $(CFLAGS)

mv-page:
	mv page.cgi /srv/http/cgi-bin/
mv-query: 
	mv query.cgi /srv/http/cgi-bin/

clean:
	rm main