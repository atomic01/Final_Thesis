# Zavrsni_rad
Rjesavanje problema labirinta A* algoritmom

Program je neoptimiziran. Za labirinte vece od 1000px x 1000px triba preko 8GB rama. Najveci koje sam rjesavao su bli 2000px x 2000px i potrebno je otprilike 10ak GB rama. Takoder je potrebno komplajlirat program kao 64 bitnu aplikaciju ne 32 bitnu jer ostane bez adresa u memoriji. Ako su manji labirinti onda to cak nije potrebno.

U code folderu se nalazi cili kod...
main.c              sadrzi glavni program
Declarations.h      sadrzi deklaracije funkcija
StackFunctions.h    sadrzi funkcije vezane za listu (tj priority queue)
GraphFunctions.h    sadrzi funkcije vezane za graf

U BMP_folder-u se nalaze sve BMP filovei tj labirinit. 
Kada budete pokrecali program bitno je da su sve slike u istom fajlu kao i main.c
