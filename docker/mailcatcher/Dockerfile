FROM ruby:alpine

RUN apk update && apk add --no-cache build-base

RUN gem install mailcatcher

EXPOSE 1025
EXPOSE 1080

ENTRYPOINT ["mailcatcher"]
