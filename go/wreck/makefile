include .env
export

all: go7z mediainfo

go7z: cmd\go7z\main.go
	go build -o bin\go7z.exe .\cmd\go7z
	bin\go7z.exe test\lzma1604.7z

mediainfo: cmd\mediainfo\main.go
	go build -o bin\mediainfo.exe .\cmd\mediainfo
	bin\mediainfo test\Wildlife.wmv

clean:
	rd /s /q out
	del bin\go7z.exe
	del bin\mediainfo.exe
	go mod tidy
