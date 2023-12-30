#!/bin/sh

echo "Adding users"
adduser -D tom
adduser -D jerry

echo 'tom:1234' | chpasswd
echo 'jerry:1234' | chpasswd

echo "Starting dovecot"
/usr/sbin/dovecot
#service dovecot start
#rc-update add dovecot

echo "Starting exim"
/usr/sbin/exim -bd -q30m
#service exim start
#rc-update add exim

echo "All done."

tail -f /dev/null
