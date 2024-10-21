include .env
export

all: clean main test	

main: main.go
	go build

test: main
	wreck.exe test\Wildlife.wmv

clean:
	del wreck.exe
	go mod tidy
