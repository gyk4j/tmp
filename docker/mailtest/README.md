# Last Known Status

- Not working. Abandoned halfway.
- Uses CentOS latest image, with postfix (for SMTP) and mailx (for IMAP)
- Tried to create test user accounts by using `client-info` and running 
  postfix's `makemap`
- Tried to create a `sendmail.mc` m4 template that references the generated 
  `client-info.db` file
- Perhaps postfix service did not even start up properly with the configuration
- Did not proceed to setting up IMAP server using mailx
