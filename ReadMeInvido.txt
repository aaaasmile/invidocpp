== InvidoCpp

In questa repository ho cercato di attualizzare il progetto invido. Non sono sicuro che i sorgenti su svn sf.net siano
attuali. In ogni modo ho usato una copia datata 07.01.2012.

Lo scopo è quello di avere la stessa applicazione compilata con visual studio 2015 e sdl 2.0

== SDL
Versioni:
SDL2-devel-2.0.8-VC
SDL2_mixer-devel-2.0.2-VC
SDL2_image-devel-2.0.3-VC
SDL2_ttf-devel-2.0.14-VC

Ho sempre usato tutte dll in versione x64.

Nota:
Ho messo tutti i files in include e lib senza distinguere le versioni.

Esempi di sdl 2 si trovano su https://www.libsdl.org/projects/

Un esempio di porting sdl 1.2 a 2.0 si trova su: https://github.com/yquake2/yquake2/blob/master/src/backends/sdl/refresh.c
La guida per la migrazione è su:
https://wiki.libsdl.org/MigrationGuide

Come riferimento guarda il progetto: D:\Projects\from_sf_net_to_github\Sdl_example\TextImput

Il problema del linker che non trova l'entry point:
Right click on project name -> Properties -> Expand Linker tab -> System -> SubSystem: make sure that it is Console (/SUBSYSTEM:CONSOLE)

Nel porting tutte le chiamate a 
SDL_SetAlpha (m_pSymbols, SDL_SRCALPHA, 120);
vanno sostituite con SDL_SetSurfaceAlphaMod

== Codice cambiato durante il porting
Ho tolto la console in quanto il porting su 2.0 era troppo oneroso e non era bella da vedere.
Ho tolto tutti i riferimenti al gioco di rete così come allo scripting di python.

= Short Key 
Autoformat Code: CTRL + K + D
Delete line: CTRL + L
Compile: CTRL + F7

== Runtime error in pnglib
Der Prozedureinsprungpunkt "inflateValidate" wurde in der DLL "D:\Projects\from_sf_net_to_github\invidocpp\src\VisualStudio\x64\Debug\libpng16-16.dll" nicht gefunden. 
L'errore sopra riportato è dovuto al fatto che zlib1.dll non è della versione corretta. Va usata quella della SDL_Image a x64

== TODO
- background [DONE]
- opzioni non scompare
- durante il gioco non si vedono le carte
- alpha in menu e dialogbox [DONE]
- tasti nella toolbox del nome
- message box non funziona il background e l'alpha