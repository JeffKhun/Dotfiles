set nocompatible

""""""""""
" PATHOGEN
""""""""""
execute pathogen#infect()


""""""""""""
" FORMATTING
""""""""""""
set encoding=utf-8
set formatoptions=tcrn
set textwidth=80
set tabstop=4
set shiftwidth=4
set expandtab
set autowrite
"set autoindent
set smartindent

set nocompatible
filetype on
set history=1000
set clipboard=unnamed
set viminfo+=!
filetype plugin on
filetype indent on
syntax on
set modeline


""""""""""""""""
" USER INTERFACE
""""""""""""""""
set number
set mouse=a
set showmatch  " show matching brackets
set mat=5      " blink matching brackets for half a second
set so=10      " always see 10 lines up/down
set wildmenu
set backspace=2 " backspace over everything
"set foldminlines=60
"set foldlevel=3
"set foldmethod=marker

set hlsearch   "set nohlsearch " do not highlight searchstrings
set incsearch  " do incremental searching

set guifont=Lucida_Console:h10
colorscheme torte
set colorcolumn=+1




"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" YouCompleteMe
"let g:ycm_global_ycm_extra_conf = "~/.vim/.ycm_extra_conf.py"
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""


""""""""""
" NERDTREE
""""""""""
map <C-n> :NERDTreeToggle<CR>


""""""""
" TAGBAR
""""""""
nmap <F8> :TagbarToggle<CR>


"""""""""""""
" VIM-AIRLINE
"""""""""""""
let g:airline_theme='dark'
let g:airline#extensions#tabline#enabled = 1


"""""""""""
" SOLARIZED
"""""""""""
"syntax enable
"set background=dark
"colorscheme solarized


"""""""""
" DOXYGEN
"""""""""
let g:load_doxygen_syntax=1
let g:doxygen_enhanced_color=1

""""""""
