FROM golang:alpine AS build

WORKDIR /app

COPY main.go .

RUN go build main.go

FROM scratch AS run

WORKDIR /app

COPY --from=build /app/main /app/main

ENV DOCKERFILE_VAR_I="Docker Alpha"
ENV DOCKERFILE_VAR_II="Docker Bravo"
ENV DOCKERFILE_VAR_III="Docker Charlie"
ENTRYPOINT ["/app/main"]
