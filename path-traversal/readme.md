# Path Traversal

A path traversal vulnerability occurs when user input is used to construct file paths without proper validation, allowing attackers to access files outside the intended directory. 

## Exploitation

If the user enters `../../etc/passwd`, the resolved path becomes:
`/var/www/app/static/../../etc/passwd -> /var/www/etc/passwd`, which can lead to unauthorized access to sensitive files.

## Mitigation Strategies

Always validate user input against allowlists.
Use modern path resolution libraries instead of string concatenation.
Restrict file system permissions for the application.
