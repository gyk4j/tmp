package main

import (
	"archive/zip"
	"bufio"
	"fmt"
	"io"
	"io/fs"
	"log"
	"net/http"
	"os"
	"path/filepath"
	"time"

	"github.com/gyk4j/tmp/go/my-server/diff"
	"github.com/r3labs/sse/v2"
)

func main() {
	diff.Diff()
	diff.Patch()
	server := sse.New()

	// Create a new Mux and set the handler
	mux := http.NewServeMux()

	NewController(server, mux)

	// cleanup := make(chan os.Signal, 1)
	// signal.Notify(cleanup, os.Interrupt, syscall.SIGINT, syscall.SIGTERM)
	// GenerateData(server)
	http.ListenAndServe(":8080", mux)

	// <-cleanup
	// log.Print("Server Stopped")
	// ticker.Stop()
	// fmt.Println("Ticker stopped")

	// ctx, cancel := context.WithTimeout(context.Background(), 5*time.Second)
	// defer func() {
	// 	// extra handling here
	// 	cancel()
	// }()

	// if err := srv.Shutdown(ctx); err != nil {
	// 	log.Fatalf("Server Shutdown Failed:%+v", err)
	// }
	// log.Print("Server Exited Properly")
}

func Zip(w http.ResponseWriter, path string) {
	fmt.Println("Zip: ", path)

	// You need to write the headers and status code before any bytes
	w.Header().Set("Content-Type", "application/zip")
	// the filename which will be suggested in the save file dialog
	filename := time.Now().Format("20060102150405")
	w.Header().Set("Content-Disposition", fmt.Sprintf("attachment; filename=\"%s.zip\"", filename))
	w.WriteHeader(http.StatusOK)

	zipWriter := zip.NewWriter(w)

	startFileInfo, err := os.Stat(path)
	if err != nil {
		log.Fatal(err)
		return
	}

	// If it's a directory, walk recursvely.
	if startFileInfo.IsDir() {
		fsys := os.DirFS(path)
		fs.WalkDir(fsys, ".", func(relPath string, d fs.DirEntry, err error) error {
			if err != nil {
				return err
			}

			if relPath == "." {
				return nil
			}

			absPath := filepath.Join(path, relPath)

			fmt.Println("path: ", relPath, ", name: ", d.Name(), ", absPath: ", absPath)

			var zipEntryHeaderName string
			if d.IsDir() {
				zipEntryHeaderName = relPath + "/"
			} else {
				zipEntryHeaderName = relPath
			}

			fileInfo, err := d.Info()

			if err != nil {
				return err
			}

			header := &zip.FileHeader{
				Name:     zipEntryHeaderName,
				Method:   zip.Deflate, // deflate also works, but at a cost
				Modified: fileInfo.ModTime(),
			}

			entryWriter, err := zipWriter.CreateHeader(header)
			if err != nil {
				log.Fatal(err)
				return err
			}

			if !d.IsDir() {
				f, err := os.Open(absPath)

				if err != nil {
					log.Fatal(err)
					return err
				}

				defer f.Close()

				fileReader := bufio.NewReader(f)

				_, err = io.Copy(entryWriter, fileReader)
				if err != nil {
					log.Fatal(err)
					return err
				}
			}
			return nil
		})
		// Else if it's a file
	} else {
		header := &zip.FileHeader{
			Name:     path,
			Method:   zip.Deflate, // deflate also works, but at a cost
			Modified: startFileInfo.ModTime(),
		}

		entryWriter, err := zipWriter.CreateHeader(header)
		if err != nil {
			log.Fatal(err)
			return
		}

		f, err := os.Open(path)

		if err != nil {
			log.Fatal(err)
			return
		}

		defer f.Close()

		fileReader := bufio.NewReader(f)

		_, err = io.Copy(entryWriter, fileReader)
		if err != nil {
			log.Fatal(err)
			return
		}
	}

	zipWriter.Flush()
	flushingWriter, ok := w.(http.Flusher)
	if ok {
		flushingWriter.Flush()
	}

	zipWriter.Close()
}
