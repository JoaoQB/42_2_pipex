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

execve()  does  not return on success, and the text, initialized data, uninitialized data (bss), and stack of the calling process are overwritten according to the contents of the newly loaded program. That means that whatever is left to do after execve() will not be done.
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

# Execve and why using Fork

As stated above, using Execve() will replace the program being executed - the shell program in the case of the terminal, or our c written program in the case of ours - by the new program, the command being executed. That means that if we had something like:

```c
void	main(void)
{
	printf(something)
	execve(ls)
	printf(something else)
}
```

We would get:

```c
something
list of files given by ls
(second printf will not print.)
```

That means shell, or our program, needs to regain control of the program originally being executed. And that's why it uses fork.
By using fork, the parent process - shell/our program - is still active, and waits for it's child to use execve and therefore be replaced by the new command.
When it's done (dies), the parent can continue to run, and continue to execute whatever we wrote, or in the case of shell, wait for other instructions or follow the ones after that command.


# Opening Files

We need to open the input file if it exists. We only need to read from it so we use the "O_RDONLY" flag.
For the output file we need to create it "O_CREAT", or if it exists, overwrite it's content "O_WRONLY | O_TRUNC".

We need to make the input file, our stdin, and the output file, our stdout.
So that the program we will execute, reads from the input file and not from the stdin (the keyboard), and writes to our output file and not the stdout (terminal).
To do that we use dup2, to redirect the stdin and save it in another file descriptor. (same for stdout)
So instead of:
```c
FD[0] - stdin
FD[1] - stdout
FD[2] - stderr
```
We get:
```c
FD[0] - filein
FD[1] - fileout
FD[2] - stderr
FD[3] - stdin
FD[4] - stdout
```
So, `dup2(*input_file, STDIN_FILENO);` which means `dup2(oldfd we want to duplicate, fd number we want to replace);`

Let's observe how shell handles errors.

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

We'll use the perror function with an empty string "perror("")" to display the standard error message for the errors above.

# Pipes and Forks

Now we have the files opened, and replaced the stdinput and stdoutput, we can start actually using pipe() and fork().

```c
int	pipe_end[2];
pipe(pipe_end);
```

The pipe takes an array of two ints and links them together so that what one end listens to the other.
One end reads pipe_end[0], the other one writes pipe_end[1]. Also the pipe assigns a fd to each of the ends.

```c
pid_t	process_id;
process_id = fork();
```

Fork() makes a clone - child process - of the original process - parent process -, and each will be run simultaneously.
We can differentiate the processes by it's process id. The child process has `"process_id == 0"`, while the parent will have some random positive number like `"process_id == 1427387"`.

So we can then use this information to instruct what each process will do.
In this case we want the child process to execute a command and write it's output to the write end of the pipe, and the parent process to read from the read end of the pipe, whatever the child has sent.
It will then continue to create childs while there are commands to run, and always supervize and read whatever output they send, until the final command is reached.
Then main will regain control and execute the last command which output will be sent to output_file through `dup2(output_file, STDOUT_FILENO)`.

Because the program will continue to run while one or both ends of the pipe are open, we also need to make sure we properly close everything.
Because we're using both fork() and pipe(), our pipe actually has 4 ends. Two reading ends and two writing ends. So first thing is to close the reading end inside the child process and the writing end in the parent process as they will not be used. Something like:

```c
if (process_id == 0)	 // Child process
	close(pipe_end[0])   // Reading end
else if (process_id > 0) // Parent process
	close(pipe_end[1])   // Writing end
```

Here's an image to illustrate it better:

![Forked Pipe](https://miro.medium.com/v2/resize:fit:640/format:webp/1*kTkBU7h_iBJ1IIopUF-aHQ.png)

We can then continue to instruct each process to redirect the needed ends to stdin/out using dup2, and tell the child to execute the command in argv using execve().

# Execve() and the new char **envp

So we saw above that `execve(const char *pathname, char *const argv[], char *const envp[]);`
replaces the current process,
executes `pathname` with arguments `ARGV` and the environment `ENVP`.

So what is then `**envp`?

Envp stands for environment pointer, and is an array of strings that saves the `environment variables` information in our system, sometimes called shell variables.
It is a set of variables that our system has access to and contains information about the home directory, terminal type and more importantly in our case, the `$PATH` to the commands it can execute.
To find this `$PATH` we can type `"env | grep PATH"` in our terminal.
It will give us all the directory paths to the command binaries, which are separated by `:` as a delimiter. Like:
`"/snap/bin:/path/to/python/executable/"`
To see the $PATH to a specific command we can run for example `"which wc"`, with output `"/usr/bin/wc"`.

Let's create a function that executes the commands given in `argv[]`. To do that we need to make several steps before being able to use the `execve()` function.
First we retrieve the command in argv using `ft_split`. Then we get all the possible paths in envp, also using `split` but using `:`.
We should then check if the command retrieved exists in every possible path we got.
If so we can then use that path to execve(), if not we must display an error message.

pseudocode:

char	**path
char	**my path
char	*cmd

path = split(env, ":");
cmd = split(argv, " ");
while (path)
	my path = strjoin path + cmd;
	if (my path == path)
		execute
	else
		command not found
		clean


Now that the program is executing, it's time to clean!
