# Last Known Status

- Not working
- Uses Alpine + Postfix + MSMTPRC
- Uses linux local user accounts and not virtual mbox users in Postfix 
  configuration
- MSMTPRC might be a simple forwarding SMTP that requires a real working SMTP
  server to work; may not work as a standalone SMTP server on a local host
- Did not progress to actually testing out with mail client
- `Dockerfile` indicates it tries to start *Postfix* service, but maybe stuck at
  not knowing how to start *MSMTPRC* concurrently in the `ENTRYPOINT`
