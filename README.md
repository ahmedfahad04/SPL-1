# slsh:~# Simple Linux Shell
I will recreate a simple Linux Shell (Bash) that includes the basic shell operations namely:
 
* Executing Shell Commands
* Command Name Customization (aliasing)
* Pipelined Command Execution
* Input-Output Redirection
* Terminal Color Customization
* Shell History Management
* Command Correction


## Executing Shell Commands
Initially, I will take the command prompt from
the user. Later I will parse and tokenize the command line and sort out the commands and
respective arguments. Then I will check whether the parsed command is built-in or an external
command for further execution. If the command is built-in I will simply execute the command
and show the result in stdout/stderr. Otherwise, for external commands, I will have to search for
the executable file in the system and then I will execute the command and demonstrate the result
as stdout/stderr. Then they will again enter another command prompt and this process will be
continued till the user exits the program. And this process of Read-Evaluate-Print-Loop is known
as REPL in terms of shell process execution.


## Command Name Customization
Users can assign short names or refactor shell commands through aliasing. By using aliases,
users can save a lot of time while doing tasks frequently. In that feature, we split the
command arguments into two parts. The first part, followed by the keyword ‘alias’, is the
actual command. And the second part is the aliased command. We map these two commands
so that the actual command can be replaced with aliased command before execution is
performed.


## Pipelined Command Execution
A pipeline is a collection of one or more instructions partitioned by the '|' control operator.
The output of each command in the pipeline is linked to the following command's input
through a pipe. It is a very common scenario when we need to execute multiple commands
at the same time. And pipelined command meets this requirement to execute multiple
commands simultaneously. We have used the pipe function to link the input-output of multiple
commands. And to represent the standard input-output stream we have used the file
descriptors. These descriptors act as the placeholder for stdin, stdout, and stderr.


## Input-Output Redirection
Redirection allows us to change the standard input (stdin) and standard output (stdout) while
executing shell commands in the terminal. It works with commands' file handles. This file
handle can be replicated, opened, or closed and even can change the file the command read
from and writes to. Before implementing this feature, we have to extract the input-output file
names as well as their relevant redirection sequence. This is the most challenging part of that
feature. Later on, after extracting the file names, we use the file descriptors. By replicating
the descriptors, we redirect the stdin and stdout to the files mentioned in the shell command.


## Terminal Color Customization
Terminal color customization denotes changing the color of the system prompt and terminal
background. Sometimes working in the same environment seems monotonous. And this
monotonous can be relinquished by using different variants of the terminal. However, we have
integrated the ANSI codes in the eventloop of the shell to manipulate the prompt and
background color.

 <hr> 

## Shell History Management
Our shell keeps track of user command history. Users can invoke specific commands using
the history expansion character (!). Sometimes some important commands might need in an
emergency and in that case, history plays a vital role. Initially, for a new user, our shell
creates a new history file to store user-given commands. Later on, whenever the program
starts, our shell search for the latest history serial number, so that the new history can be
appended from that point. Also, these serial numbers are useful for invoking any particular
command without typing it repeatedly.
 

## Command Correction
It is quite common that we type the wrong shell commands with or without the actual
command. In that case, this feature will help the user to understand the relevant shell
command if he/she puts any wrong commands. This feature is quite useful for those who are
new to Linux and learning commands by trial and error. Initially, it will suggest to the user
what can be the closest command to the given wrong command. In autocompletion mode,
our shell will suggest the most accurate command by inspecting user command history.

## Resources

* Shell builtins (https://www.gnu.org/software/bash/manual/html_node/Shell-Builtin-Commands.html)
* Simple commands (https://www.gnu.org/software/bash/manual/html_node/Simple-Commands.html)
* Basic Shell Features (https://www.gnu.org/software/bash/manual/html_node/Basic-Shell-Features.html)
* Interactive and non interactive shell (https://www.gnu.org/software/bash/manual/html_node/What-is-an-Interactive-Shell_003f.html)
* Shell operation (https://www.gnu.org/software/bash/manual/html_node/Shell-Operation.html)

