#!/bin/sh

#/etc/init.d/saslauthd start

echo Starting Cyrus
service cyrus-imapd start

# Compile updated postfix map files before starting
#postmap /etc/postfix/aliases && \
#postmap /etc/postfix/roleaccount_exceptions && \
#postmap /etc/postfix/virtual 
#&& /usr/sbin/postfix start-fg
#echo Starting Postfix
#service postfix start

#/etc/init.d/sendmail start

#/bin/sleep 10

echo 'cyrus:1234' | chpasswd
#echo "1234" | saslpasswd2 -p -c cyrus
adduser --gecos "" --disabled-password toc
echo 'toc:1234' | chpasswd
#echo "1234" | saslpasswd2 -p -c toc

# Check sasl users
#sasldblistusers2

 
# Create toc@localhost
#echo 'createmailbox user/toc@localhost' | cyradm -u toc -w 1234 localhost

tail -f /dev/null

