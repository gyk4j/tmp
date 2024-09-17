package main

import (
  "log"
  "os"
  "syscall"
  "time"
  "golang.org/x/sys/windows"
)

func main(){  
  /* var ctime windows.Filetime
  var atime windows.Filetime
  var wtime windows.Filetime */
  
  /* from, err := windows.Open("go.sum", os.O_RDONLY, 0x100)
  defer windows.CloseHandle(from)
  if err != nil {
    log.Printf("Error at opening bootsqm.dat")
    return
  }
  windows.GetFileTime(from, &ctime, &atime, &wtime) */
  t, _ := time.Parse(time.RFC3339, "2006-01-02T15:04:05+08:00")
  
  var ll uint64
  ll = uint64(t.Unix() * 10000000) + uint64(116444736000000000)
  ft := windows.Filetime{
    LowDateTime: uint32(ll & 0b11111111111111111111111111111111),
    HighDateTime: uint32(ll >> 32),
  }
  
  
  to, err := windows.Open("test.txt", os.O_WRONLY, syscall.S_IWRITE)
  defer windows.CloseHandle(to)
  if err != nil {
    log.Printf("Error at opening test.txt")
    return
  }
  windows.SetFileTime(to, &ft, &ft, &ft)
}