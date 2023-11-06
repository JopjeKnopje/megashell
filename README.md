# Megashell
A unix shell written in C.

## Features
- [x] File redirections
- [x] Pipes
- [x] Heredoc
- [x] Environment variables
- [x] Shell history file
- [ ] Emoji based return status
- [ ] Aliases


## Building
Megashell depends on [readline](https://tiswww.case.edu/php/chet/readline/rltop.html) and on [criterion](https://github.com/Snaipe/Criterion#downloads) for its unit tests.  
You can install readline with `apt install libreadline-dev`.  
And criterion with `apt-get install libcriterion-dev`.

### Running
When you're done with all that just run `make` to build to project.
### Tests
To build to unit tests run `make tests`.
