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
    
    // Variables from shell variable interpolation
    fmt.Printf("SHELL: %s\n", os.Getenv("SHELL"))
    fmt.Printf("TERM: %s\n", os.Getenv("TERM"))
    fmt.Printf("USER: %s\n", os.Getenv("USER"))
    fmt.Printf("HOME: %s\n", os.Getenv("HOME"))
    
    // Variables from .env
    fmt.Printf("CUSTOM_VAR_1: %s\n", os.Getenv("CUSTOM_VAR_1"))
    fmt.Printf("CUSTOM_VAR_2: %s\n", os.Getenv("CUSTOM_VAR_2"))
    fmt.Printf("CUSTOM_VAR_3: %s\n", os.Getenv("CUSTOM_VAR_3"))
    
    // Variables from service.env
    fmt.Printf("SERVICE_A: %s\n", os.Getenv("SERVICE_A"))
    fmt.Printf("SERVICE_B: %s\n", os.Getenv("SERVICE_B"))
    fmt.Printf("SERVICE_C: %s\n", os.Getenv("SERVICE_C"))
    
    // Variables from Dockerfile
    fmt.Printf("DOCKERFILE_VAR_I: %s\n", os.Getenv("DOCKERFILE_VAR_I"))
    fmt.Printf("DOCKERFILE_VAR_II: %s\n", os.Getenv("DOCKERFILE_VAR_II"))
    fmt.Printf("DOCKERFILE_VAR_III: %s\n", os.Getenv("DOCKERFILE_VAR_III"))
}
