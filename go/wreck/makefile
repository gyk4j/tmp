include .env
export

all: goexiftool go7z mediainfo

goexiftool: cmd\goexiftool\main.go
	go build -o bin\ .\cmd\goexiftool
	bin\goexiftool test\Chrysanthemum.jpg

go7z: cmd\go7z\main.go
	go build -o bin\ .\cmd\go7z
	bin\go7z.exe test\Core-15.0.iso

mediainfo: cmd\mediainfo\main.go
	go build -o bin\ .\cmd\mediainfo
	bin\mediainfo test\Wildlife.wmv

clean:
	rd /s /q out
	del bin\goexiftool.exe
	del bin\go7z.exe
	del bin\mediainfo.exe
	go mod tidy
