FROM golang:alpine AS build

WORKDIR /app

COPY main.go .

RUN go build main.go

FROM scratch AS run

WORKDIR /app

COPY --from=build /app/main /app/main

ENTRYPOINT ["/app/main"]
