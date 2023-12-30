# Last Known Status

- Not working
- Uses Alpine + Dovecot (IMAP) and Exim (SMTP)
- Dovecot is configured to use linux user accounts, and static password `1234`
  as indicated in `dovecot.conf` and `passwd`. Mail clients should be able to
  authenticate using a valid local user account name and using static password 
  `1234` for IMAP login
- `docker-entrypoint.sh` is written to concurrently start both Dovecot and Exim
  service. Not sure if both manage to start successfully.
- Built-in exim configuration is edited in `Dockerfile` to use `mail` group as 
  user account, and `660` as permission to access `/var/mail`?
- Guess did not progress to actually testing with mail client

