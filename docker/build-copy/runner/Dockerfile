FROM builder
RUN /app/main

FROM scratch
COPY --from=0 /app/main /bin/start
ENTRYPOINT ["/bin/start"]