FROM ubuntu:12.04.5
COPY ubuntu/sources.list /etc/apt/sources.list
RUN apt-get update \
  && apt-get install -y cyrus-imapd cyrus-clients-2.4 cyrus-doc-2.4 cyrus-admin-2.4 sasl2-bin \
  && apt-get install -y postfix postfix-doc postfix-pcre postfix-ldap

##COPY cyrus/cyrus.conf /etc/cyrus.conf
##COPY cyrus/imapd.conf /etc/imapd.conf

##COPY postfix/main.cf /etc/postfix/main.cf
##COPY postfix/aliases /etc/postfix/aliases
##COPY postfix/virtual /etc/postfix/virtual

RUN postconf -e "virtual_mailbox_domains=hash:/etc/postfix/virtual_recipient_domains"
RUN postconf -e "virtual_mailbox_maps=hash:/etc/postfix/virtual_recipients"
RUN postconf -e "virtual_destination_concurrency_limit=300"
RUN postconf -e "virtual_destination_recipient_limit=300"
RUN postconf -e 'home_mailbox= Maildir/'
RUN postconf -e 'virtual_alias_maps= hash:/etc/postfix/virtual'

# Same host
RUN postconf -e "virtual_transport=lmtp:unix:/run/cyrus/socket/lmtp"
# Different host
#RUN postconf -e "virtual_transport=lmtp:inet:lmtp.example.org:2003"

#RUN apt-get install -y sendmail
#COPY proto.m4.patch /root/proto.m4.patch
#COPY cyrusv2.m4.patch /root/cyrusv2.m4.patch
#RUN patch --dry-run /cf/m4/proto.m4 /root/proto.m4.patch
#RUN patch --dry-run /cf/mailer/cyrusv2.m4 /root/cyrusv2.m4.patch

#RUN mkdir -p /run/cyrus/socket
#RUN chown cyrus:mail /run/cyrus/socket
#RUN chmod 750 /run/cyrus/socket
#RUN mkdir -p /run/smmapd/socket
#RUN chown cyrus:mail /run/smmapd/socket
#RUN chmod 750 /run/smmapd/socket

RUN echo "BEGIN services" && cat /etc/services && echo "END services"

RUN mkdir -p /var/lib/cyrus /var/spool/cyrus
RUN chown -R cyrus:mail /var/lib/cyrus /var/spool/cyrus
RUN chmod 750 /var/lib/cyrus /var/spool/cyrus

#COPY cyrus/init.sh /root/init.sh
#RUN /bin/bash /root/init.sh
RUN dpkg-statoverride --add cyrus mail 755 /run/cyrus
RUN dpkg-statoverride --add cyrus mail 750 /run/cyrus/socket

COPY start.sh /root/start.sh

EXPOSE 143
EXPOSE 110
EXPOSE 25/tcp
EXPOSE 465/tcp
EXPOSE 587/tcp
EXPOSE 8008

ENTRYPOINT ["/bin/sh", "/root/start.sh"]
