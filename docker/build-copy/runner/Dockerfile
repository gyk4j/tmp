FROM build-copy-builder AS build
FROM scratch
WORKDIR /app
COPY --from=build /app/main /app/main
ENTRYPOINT ["/app/main"]
