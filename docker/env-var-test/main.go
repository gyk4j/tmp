package main

import (
    "fmt"
    "os"
)

func main() {
    hostname, err := os.Hostname()
    if err != nil {
        fmt.Println(err)
        os.Exit(1)
    }
    fmt.Printf("Hostname: %s\n", hostname)
    
    fmt.Printf("SHELL: %s\n", os.Getenv("SHELL"))
    fmt.Printf("TERM: %s\n", os.Getenv("TERM"))
    fmt.Printf("USER: %s\n", os.Getenv("USER"))
    fmt.Printf("HOME: %s\n", os.Getenv("HOME"))
}
