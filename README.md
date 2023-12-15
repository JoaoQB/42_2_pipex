markdown

# 42_2_pipex

This C project explores the UNIX pipe operator, aiming to replicate its functionality in a C program. The goal is to mimic the behavior of the shell pipe command ("< file1 cmd1 | cmd2 > file2").

### Usage Examples

```bash
./pipex infile "ls -l" "wc -l" outfile

Behaves like:

bash

< infile ls -l | wc -l > outfile

bash

./pipex infile "grep a1" "wc -w" outfile

Behaves like:

bash

< infile grep a1 | wc -w > outfile

Allowed Functions: open, close, read, write, malloc, free, perror, strerror, access, dup, dup2, execve, exit, fork, pipe, unlink, wait, waitpid, ft_printf (and any equivalent YOU coded)
Explanation of Symbols

    < is an input redirection symbol, taking the content of a file as input for the desired command.
    << takes input from the standard input until it encounters a specific limiter.
    > is an output redirection symbol, replacing the file content with the new output.
    >> appends the new output to the file.

For example:

bash

cat << Stop >> file2.txt
heredoc> Hi
heredoc> My name is
heredoc> Hi My name is Stop
heredoc> Hi
heredoc> Stop
