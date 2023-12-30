FROM alpine:latest

# install packages
RUN apk add --no-cache --update exim dovecot mailx bash

#COPY exim.conf /etc/exim/exim.conf
RUN sed -i~ \
  -e 's/# group = mail/  group = mail/' \
  -e 's/# mode = 0660/  mode = 0660/' \
  /etc/exim/exim.conf

COPY dovecot.conf /etc/dovecot/dovecot.conf
COPY passwd /etc/dovecot/passwd

RUN chown root:dovecot /etc/dovecot/passwd
RUN chgrp dovecot /etc/dovecot/passwd
RUN chmod 640 /etc/dovecot/passwd

RUN chgrp mail /var/mail
RUN chmod 2775 /var/mail

COPY docker-entrypoint.sh /usr/local/bin/docker-entrypoint.sh
ENTRYPOINT ["/usr/local/bin/docker-entrypoint.sh"]
