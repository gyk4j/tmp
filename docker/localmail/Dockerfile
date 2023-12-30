FROM python:3.6-slim

ENV SMTP=2025
ENV IMAP=2143
ENV HTTP=8880
ENV FILE=localmail.mbox

RUN pip install localmail

EXPOSE $SMTP
EXPOSE $IMAP
EXPOSE $HTTP

COPY docker-entrypoint.sh /usr/local/bin/docker-entrypoint.sh
ENTRYPOINT ["docker-entrypoint.sh"]
