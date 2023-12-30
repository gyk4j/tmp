#!/bin/sh

echo IMAP: $IMAP, SMTP: $SMTP, HTTP: $HTTP, FILE: $FILE 
twistd -n localmail --imap $IMAP --smtp $SMTP --http $HTTP --file $FILE
