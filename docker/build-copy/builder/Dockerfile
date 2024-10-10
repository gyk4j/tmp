FROM golang:alpine
WORKDIR /app
COPY main.go .
RUN go build main.go
RUN /app/main

CMD [ "/app/main" ]