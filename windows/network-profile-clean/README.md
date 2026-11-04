# Network Profile Cleaning Tool

A script to delete Windows network profiles saved in the registry.

> [!TIP]
> Network profiles to be retained can be added to a whitelist.

> [!WARNING]
> Non-whitelisted profiles are *DELETED* without warning or prompting.

This can be useful when:

1. Windows has accumulated many old network profiles that are no longer in use,
   which were created when connecting to networks in the past.
2. When using USB tethering or WiFi hotspot with a device that generates a new
   random MAC physical address every time a new connection is made. This 
   confuses Windows into thinking that it has connected to a new network, 
   causing the list of one time use network profiles to grow over time.
   
This quick-and-dirty script can be modernised and rewritten as a PowerShell
script if needed. But for now, it works as intended, and no effort is expended
to rewrite it.
