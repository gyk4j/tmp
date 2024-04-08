package main

import (
	"encoding/json"
	"fmt"
	"strconv"
	"time"

	"github.com/r3labs/sse/v2"
)

// Need to match when creating stream, publishing message and in client stream
// subscription
const STREAM = "messages"

type ping struct {
	Time time.Time `json:"time"`
}

func GenerateData(server *sse.Server) {
	server.CreateStream(STREAM)

	// Periodically publish a SSE message for testing
	ticker := time.NewTicker(5 * time.Second)
	done := make(chan bool)

	go func() {
		for {
			select {
			case <-done:
				return
			case t := <-ticker.C:
				fmt.Println("Tick at", t)
				pings := &ping{Time: t} //map[string]string{"time": t.String()} //
				timestamp, _ := json.Marshal(pings)
				fmt.Println("JSON: ", string(timestamp))
				// Publish a payload to the stream
				server.Publish(STREAM, &sse.Event{
					Event: []byte("ping"),
					Data:  []byte(timestamp),
					Retry: []byte(strconv.FormatInt(1000, 10)),
				})
			}
		}
	}()
}
