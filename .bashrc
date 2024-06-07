#
# ~/.bashrc
#

# If not running interactively, don't do anything
[[ $- != *i* ]] && return

alias v='nvim'
alias vim='nvim'

alias ls='ls --color=auto'
alias grep='grep --color=auto'

#PS1='[\u@\h \W]\$ '

PS1='\n  ┌─[ \[\033[36m\]\W\[\033[37m\] ]\n  └─> '

export PATH="/home/bk/My_Folders/My_Scripts:$PATH"
