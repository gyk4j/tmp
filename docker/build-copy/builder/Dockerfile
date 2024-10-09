FROM gcc
WORKDIR /app
COPY main.c .
RUN gcc -static -o main main.c
RUN /app/main

CMD [ "/app/main" ]