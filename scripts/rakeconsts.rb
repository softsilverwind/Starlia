Compilers = {
	:cpp => ['g++', ['g', 'c', 'Wall', 'Wextra', 'O3', 'std=c++11'], [] ],
	:ar => ['ar', ['cvsr'], [] ],
	:ld => ['g++', [], ['lGLEW', 'lGL', 'lGLU', 'lSDL', 'lSDL_image', 'lSDL_mixer', 'lassimp'] ]
}

Rm = 'rm -f'

Depend = 'depend.dep'
Src = FileList['*.cpp']
Obj = Src.ext('o')
Head = FileList['*.h']
Inl = FileList['*.inl']
