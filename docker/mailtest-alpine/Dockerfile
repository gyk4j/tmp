FROM alpine:latest

# install packages
RUN apk add --no-cache --update postfix mailx bash && \
    apk add --no-cache --upgrade musl musl-utils && \
    (rm "/tmp/"* 2>/dev/null || true) && (rm -rf /var/cache/apk/* 2>/dev/null || true)

RUN adduser -D tom && echo 'tom:1234' | chpasswd
RUN adduser -D jerry && echo 'jerry:1234' | chpasswd

COPY main.cf /etc/postfix/main.cf
COPY msmtprc /etc/msmtprc

# postfix is listening on port 25
EXPOSE 25
STOPSIGNAL SIGKILL

CMD ["postfix", "start-fg"]
