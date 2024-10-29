package main

import (
	"fmt"
	"log"
	"os"
	
    "github.com/barasher/go-exiftool"
)

func main() {
	args := os.Args[1:]

	if len(args) < 1 {
		log.Printf("Usage: goexiftool FILE")
		os.Exit(1)
	}
	
	inPath := args[0]

    et, err := exiftool.NewExiftool()
    if err != nil {
        fmt.Printf("Error when intializing: %v\n", err)
        return
    }
    defer et.Close()

    fileInfos := et.ExtractMetadata(inPath)

    for _, fileInfo := range fileInfos {
        if fileInfo.Err != nil {
            fmt.Printf("Error concerning %v: %v\n", fileInfo.File, fileInfo.Err)
            continue
        }

        for k, v := range fileInfo.Fields {
            fmt.Printf("[%v] %v\n", k, v)
        }
    }
}