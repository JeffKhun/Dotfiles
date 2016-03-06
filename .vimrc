
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
set shiftwidth=2
set expandtab
set autowrite

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

set guifont=Lucida_Console:h10
colorscheme torte
set colorcolumn=+1


"""""""""""
" SOLARIZED
"""""""""""
"syntax enable
"set background=dark
"colorscheme solarized


""""""""""
" NERDTREE
""""""""""
map <C-n> :NERDTreeToggle<CR>
autocmd bufenter * if (winnr("$") == 1 && exists("b:NERDTree") && b:NERDTree.isTabTree()) | q | endif


""""""""
" TAGBAR
""""""""
nmap <F8> :TagbarToggle<CR>


"""""""""""""
" VIM-AIRLINE
"""""""""""""
let g:airline#extensions#tabline#enabled = 1


"""""""""
" DOXYGEN
"""""""""
let g:load_doxygen_syntax=1
let g:doxygen_enhanced_color=1