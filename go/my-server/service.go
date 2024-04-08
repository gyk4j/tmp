package main

import (
	"encoding/json"
	"fmt"
	"strconv"
	"time"

	"github.com/gyk4j/tmp/go/my-server/archiver"
	"github.com/r3labs/sse/v2"
)

const (
	EVENT_NAME        = "ping"
	RETRY_INTERVAL_MS = 1000
)

func Events(server *sse.Server) {
	t := time.Now()
	pings := &ping{Time: t} //map[string]string{"time": t.String()} //
	timestamp, _ := json.Marshal(pings)
	fmt.Println("JSON: ", string(timestamp))
	// Publish a payload to the stream
	server.Publish(STREAM, &sse.Event{
		Event: []byte(EVENT_NAME),
		Data:  []byte(timestamp),
		Retry: []byte(strconv.FormatInt(RETRY_INTERVAL_MS, 10)),
	})
}

// Perform a backup on main
func Backup() {

}

// Perform a restoration on step-up
func Restore() {

}

// Sync backup/restoration progress from the other controller
func SyncProgress() {

}

// Get disk quotas from file server
func CheckQuotas() {

}

// Save/export logs as text files
func ExportLogs() {

}

// Save session data as ZIP archive
func SaveArchive() {
	archiver.ZipFile()
	archiver.ZipArray()
	archiver.RunGZip()
}
