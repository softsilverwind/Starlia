Compilers = {
	:cpp => ['g++', ['c', 'Wall', 'O3', 'std=c++0x'] ],
	:ar => ['ar', ['cvsr'] ],
	:ld => ['g++', ['lgl', 'lGLU', 'lSDL', 'lSDL_image', 'lSDL_mixer'] ]
}

Rm = 'rm -f'

Depend = 'depend.dep'
Src = FileList['*.cpp']
Obj = Src.ext('o')
Head = FileList['*.h']
Inl = FileList['*.inl']
