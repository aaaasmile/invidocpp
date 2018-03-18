== InvidoCpp

In questa repository ho cercato di attualizzare il progetto invido. Non sono sicuro che i sorgenti su svn sf.net siano
attuali. In ogni modo ho usato una copia datata 07.01.2012.

Lo scopo è quello di avere la stessa applicazione compilata con visual studio 2015 e sdl 2.0

== SDL
Versioni:
SDL2_mixer-devel-2.0.2-VC
SDL2-devel-2.0.8-VC

Nota:
Ho messo tutti i files in include e lib senza distinguere le versioni.

Esempi di sdl 2 si trovano su https://www.libsdl.org/projects/

Un esempio di porting sdl 1.2 a 2.0 si trova su: https://github.com/yquake2/yquake2/blob/master/src/backends/sdl/refresh.c
La guida per la migrazione è su:
https://wiki.libsdl.org/MigrationGuide

Come riferimento guarda il progetto: D:\Projects\from_sf_net_to_github\Sdl_example\TextImput

Il problema del linker che non trova l'entry point:
Right click on project name -> Properties -> Expand Linker tab -> System -> SubSystem: make sure that it is Console (/SUBSYSTEM:CONSOLE)