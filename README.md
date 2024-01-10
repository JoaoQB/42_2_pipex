# 42_2_pipex

This C project explores the UNIX pipe operator, aiming to replicate its functionality in a C program. The goal is to mimic the behavior of the shell pipe command ("< file1 cmd1 | cmd2 > file2").

### Usage Examples


```bash
./pipex infile "ls -l" "wc -l" outfile
```

Behaves like:

```bash
< infile ls -l | wc -l > outfile
```

Or:

```bash
./pipex infile "grep a1" "wc -w" outfile
```

Behaves like:

```bash
< infile grep a1 | wc -w > outfile
```

### Allowed Functions:
`open`, `close`, `read`, `write`, `malloc`, `free`, `perror`, `strerror`, `access`, `dup`, `dup2`, `execve`, `exit`, `fork`, `pipe`, `unlink`, `wait`, `waitpid`;
`ft_printf` (and any equivalent YOU coded).

### Explanation of Symbols

- `<` is an input redirection symbol, taking the content of a file as input for the desired command.
- `<<` takes input from the standard input until it encounters a specific limiter.
- `>` is an output redirection symbol, replacing the file content with the new output.
- `>>` appends the new output to the file.

**For example:**

```bash
cat << Stop >> file2.txt
Hi
My name is
Hi My name is Stop
Hi
Stop
```



# Functions Used


Quick look at the new functions:

<details>
  <summary><strong>perror()</strong></summary>

```c
void perror(const char *s);
```

The `perror()` function produces a message on standard error describing the last error encountered during a call to a system or library function.

First  (if s is not NULL and *s is not a null byte ('\0')), the argument string s is printed, followed by a colon and a blank.
Then an error message corresponding to the current value of errno and a new-line.

When a system call fails, it usually returns -1 and sets the variable errno to a value describing what went wrong.  (These values can be found in <errno.h>.)
Many library  functions  do  likewise.
The function perror() serves to translate this error code into human-readable form.
Note that errno is undefined after a successful system call or library function call:
this call may well change this variable, even though it succeeds, for example because it internally used some other library function that failed.
Thus, if a failing call is not immediately followed by a call to perror(), the value of errno should be saved.

The <errno.h> header file defines the integer variable errno, which is set by system calls and some library functions in the event of an error to indicate what went wrong.

The  value in errno is significant only when the return value of the call indicated an error (i.e., -1 from most system calls; -1 or NULL from most library functions);
a function that succeeds is allowed to change errno.  The value of errno is never set to zero by any system call or library function.

For some system calls and library functions (e.g., getpriority(2)), -1 is a valid return on success.
In such cases, a successful return can be distinguished from an error return by setting errno to zero before the call, and then, if the call returns a status that indicates that an error may have occurred, checking to see if errno has a nonzero value.

errno is defined by the ISO C standard to be a modifiable lvalue of type int, and must not be explicitly declared; errno may be a macro.  errno is thread-local; setting it in one thread does not affect its value in any other thread.
</details>
<details>
  <summary><strong>strerror()</strong></summary>

```c
char *strerror(int errnum);
```

The `strerror()` function returns a pointer to a string that describes the error code passed in the argument `errnum`, possibly using the LC_MESSAGES part of the current locale to select the appropriate language.

(For example, if errnum is EINVAL, the returned description will be "Invalid argument".)  This string must not be modified by  the  application, but may be modified by a subsequent call to `strerror()`.  No other library function, including `perror(3)`, will modify this string.
</details>
<details>
  <summary><strong>access()</strong></summary>

```c
int access(const char *pathname, int mode);
```

The `access()` function checks whether the calling process can access the file pathname. If pathname is a symbolic link, it is dereferenced.

The mode specifies the accessibility check(s) to be performed,  and  is
either the value `F_OK`, or a mask consisting of the bitwise OR of one or more of `R_OK`, `W_OK`, and `X_OK`.
`F_OK` tests  for  the  existence  of  the file.
`R_OK`, `W_OK`,  and `X_OK` test whether the file exists and grants read, write, and execute permissions, respectively.

On  success (all requested permissions granted, or mode is F_OK and the file exists), zero is returned.
On error (at least  one  bit  in  mode asked  for  a  permission  that is denied, or mode is F_OK and the file
does not exist, or some other error occurred), -1 is returned, and  errno is set appropriately.
</details>
<details>
<summary><strong>dup2()</strong></summary>

```c
int dup2(int oldfd, int newfd);
```

The `dup2()` system call creates a copy of the file descriptor `oldfd`, using the file descriptor number specified in `newfd`.

After  a  successful  return, the old and new file descriptors may be used interchangeably.  They refer to the same open file description (see open(2)) and thus share file offset and file status flags; for example, if the file offset is modified by using lseek(2) on one of the file descriptors, the offset is also changed for the other.

However, note the following points:

*  If oldfd is not a valid file descriptor, then the call fails, and newfd is not closed.
*  If oldfd is a valid file descriptor, and newfd has the same value as oldfd, then dup2() does nothing, and returns newfd.

On success, these system calls return the new file descriptor.  On error, -1 is returned, and errno is set appropriately.
</details>
<details>
  <summary><strong>execve()</strong></summary>

```c
int execve(const char *pathname, char *const argv[], char *const envp[]);
```

The `execve()` function executes the program referred to by `pathname` (or filename). This causes the program that is currently being run by the calling process to be replaced with a new program, with newly initialized stack, heap, and data segments.

execve()  does  not return on success, and the text, initialized data, uninitialized data (bss), and stack of the calling process are overwritten according to the contents of the newly loaded program.
</details>
<details>
  <summary><strong>fork()</strong></summary>

```c
pid_t fork(void);
```

The `fork()` function creates a new process by duplicating the calling process. The new process is referred to as the child process, and the calling process is referred to as the parent process.

The  child process and the parent process run in separate memory spaces.  At the time of fork() both memory spaces have the same content.
Memory writes, file mappings (mmap(2)), and unmappings (munmap(2)) performed by one of the processes do not affect the other.

The child process is an exact duplicate of the parent process except for the following points: see "man fork".
</details>
<details>
  <summary><strong>pipe()</strong></summary>

```c
int pipe(int pipefd[2]);
```

The `pipe()` function creates a unidirectional data channel that can be used for interprocess communication. The array pipefd is used to return two file descriptors referring to the ends of the pipe.  pipefd[0] refers to the read end of the pipe.
pipefd[1] refers to the write end of the pipe.  Data written to the write end of the pipe  is  buffered  by  the kernel until it is read from the read end of the pipe.

On success, zero is returned.  On error, -1 is returned, errno is set appropriately, and pipefd is left unchanged.
</details>
<details>
  <summary><strong>unlink()</strong></summary>

```c
int unlink(const char *pathname);
```

The `unlink()` function deletes a name from the filesystem. If that name was the last link to a file and no processes have the file open, the file is deleted and the space it was using is made available for reuse.

If the name was the last link to a file but any processes still have the file open, the file will remain in existence until the last file descriptor referring to it is closed.
</details>
<details>
  <summary><strong>wait() and waitpid()</strong></summary>

```c
pid_t wait(int *wstatus);
pid_t waitpid(pid_t pid, int *wstatus, int options);
```

All of these system calls are used to wait for state changes in a child of the calling process and obtain information about the child whose state has changed.
A state change is considered to be: the child terminated; the child was stopped by a signal; or the child was resumed by a signal.
In the case of a terminated child, performing a wait allows  the system to release the resources associated with the child;
if a wait is not performed, then the terminated child remains in a "zombie" state (see NOTES below).

The wait() system call suspends execution of the calling thread until one of its children terminates.

The  waitpid()  system  call  suspends execution of the calling thread until a child specified by pid argument has changed state.  By default, waitpid() waits only for terminated children.
</details>


# Opening Files

To begin, the first step is to open the input and output files. Let's observe how the shell handles errors.

- If the input file doesn't exist, it generates an error message such as:
  - "zsh: no such file or directory: file3.txt."

- If the input file exists but lacks the necessary permissions, the error message is:
  - "zsh: permission denied: file2.txt."

- In the case where the output file doesn't exist, it creates the file (with `chmod 664`). If the file already exists, it overwrites its content.
  However, if the output file exists but lacks the necessary permissions, the error message is similar to the one for the input file:
  - "zsh: permission denied: file2.txt."

- Notably, if the input file doesn't exist, but the output file exists and has the correct permissions, the error message is printed to stderr. However, the shell still attempts to execute the command on the output file. For instance:
  - "< file5.txt cat | wc -lc
  zsh: no such file or directory: file5.txt
        0       0"
