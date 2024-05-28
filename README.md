# Megashell
A unix shell written in C.

## Features
- [x] File redirections
- [x] Pipes
- [x] Heredoc
- [x] Environment variables
- [x] Shell history file
- [ ] Aliases

## Getting Started
Megashell depends on [readline](https://tiswww.case.edu/php/chet/readline/rltop.html).
###Installing
```
sudo apt install libreadline-dev
git clone git@github.com:JopjeKnopje/megashell.git
cd megashell
make
```

Optionally for the unit tests
```
apt install libcriterion-dev
make test
```
