package main

import (
  "log"
  "os"
  "syscall"
  "time"
  "golang.org/x/sys/windows"
  "github.com/lxn/win"
)

func main(){  
  var ct, at, wt windows.Filetime
  
  // syscall.S_IREAD
  from, err := windows.Open("test.txt", os.O_RDONLY, 0x100)
  defer windows.CloseHandle(from)
  if err != nil {
    log.Printf("Error at opening bootsqm.dat")
    return
  }
  windows.GetFileTime(from, &ct, &at, &wt)
  
  PrintFileTime("Create", ct)
  PrintFileTime("Access", at)
  PrintFileTime("Modify", wt)
  
  t, _ := time.Parse(time.RFC3339, "2006-01-02T15:04:05+08:00")
  
  var ll uint64
  ll = uint64(t.Unix() * 10000000) + uint64(116444736000000000)
  ft := windows.Filetime{
    LowDateTime: uint32(ll & (1 << 32 - 1)),
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

func PrintFileTime(header string, ft windows.Filetime) {
  var wft win.FILETIME
  var wst win.SYSTEMTIME
  
  wft.DwLowDateTime = ft.LowDateTime
  wft.DwHighDateTime = ft.HighDateTime
  
  if win.FileTimeToSystemTime(&wft, &wst) {
    log.Printf("%s: %04d-%02d-%02d %02d:%02d:%02d.%04d\n",
      header,
      wst.WYear, wst.WMonth, wst.WDay,
      wst.WHour, wst.WMinute, wst.WSecond, wst.WMilliseconds)
  } else {
    log.Printf("Error: FileTimeToSystemTime")
  }
}