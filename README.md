# UNIX Shell Implementation in C

## Overview
Built a custom UNIX-style shell in C that parses user input, creates child processes, and executes commands using low-level POSIX system calls. The shell supports background execution, command history, input/output redirection, and inter-process communication via pipes.

## Features
- Command execution using `fork()` and `execvp()`
- Background process support using `&`
- Process synchronization with `wait()`
- Command history feature (`!!`)
- Input redirection (`<`)
- Output redirection (`>`)
- Single pipe support (`|`) for IPC between two processes
- Error handling for invalid commands and empty history

## System Calls Used
- `fork()`
- `execvp()`
- `wait()`
- `dup2()`
- `pipe()`

## Concepts Demonstrated
- Process creation and management
- Inter-process communication (IPC)
- File descriptor manipulation
- Shell command parsing
- UNIX process model

## Example Usage

```bash
osh> ls -l
osh> cat file.txt &
osh> sort < input.txt
osh> ls > output.txt
osh> ls -l | less
osh> !!