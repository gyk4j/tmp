package main

import (
	"fmt"
	"log"
	"net/http"

	"github.com/r3labs/sse/v2"
)

func NewController(server *sse.Server, mux *http.ServeMux) {
	mux.Handle("/", http.FileServer(http.Dir("./static")))

	mux.HandleFunc("/events", func(w http.ResponseWriter, r *http.Request) {
		go func() {
			// Received Browser Disconnection
			<-r.Context().Done()
			println("The client is disconnected here")
		}()

		server.ServeHTTP(w, r)
	})

	mux.HandleFunc("backup", func(w http.ResponseWriter, r *http.Request) {
		if r.Method == "GET" {
			// Get info about backup session
		} else if r.Method == "POST" {
			// Create a new backup session (full backup)
		} else if r.Method == "PUT" {
			// Create a delta backup? (incremental delta backup)
		} else {
			log.Println("Ignored unknown backup method: ", r.Method)
		}
	})

	mux.HandleFunc("restoration", func(w http.ResponseWriter, r *http.Request) {
		if r.Method == "GET" {
			// Get info about restoration request for a backup
		} else if r.Method == "POST" {
			// Restore a full backup
		} else if r.Method == "PUT" {
			// Restore a delta backup? (incremental delta backup)
		} else {
			log.Println("Ignored unknown restoration method: ", r.Method)
		}
	})

	mux.HandleFunc("/progress", func(w http.ResponseWriter, r *http.Request) {
		// vars := mux.Vars(r)
		w.WriteHeader(http.StatusOK)
		fmt.Fprintf(w, "progress\n")
	})

	mux.HandleFunc("/quotas", func(w http.ResponseWriter, r *http.Request) {
		// vars := mux.Vars(r)
		w.WriteHeader(http.StatusOK)
		fmt.Fprintf(w, "quotas\n")
	})

	mux.HandleFunc("/logs", func(w http.ResponseWriter, r *http.Request) {
		// vars := mux.Vars(r)
		w.WriteHeader(http.StatusOK)
		fmt.Fprintf(w, "logs\n")
	})

	mux.HandleFunc("/archive", func(w http.ResponseWriter, r *http.Request) {
		Zip(w, "static/index.html")
	})
}
