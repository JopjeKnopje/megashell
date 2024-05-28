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
Megashell depends on the [readline](https://tiswww.case.edu/php/chet/readline/rltop.html) library.
```
sudo apt install libreadline-dev
git clone git@github.com:JopjeKnopje/megashell.git
cd megashell
make
```

For the unit tests we're using [criterion](https://github.com/Snaipe/Criterion#downloads).
```
apt install libcriterion-dev
make test
```
