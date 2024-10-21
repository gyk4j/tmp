include .env
export

all: clean main test	

main: main.go
	go build -o bin\wreck.exe

test: main
	bin\wreck.exe test\lzma1604.7z

clean:
	del bin\wreck.exe
	go mod tidy
