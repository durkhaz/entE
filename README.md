# entE
A source engine mapping tool 

================
) entE v1.1 by durkhaz (
================

WHAT IT DOES:

It shortens all targetnames to their minimum sizes to save entdata, 
while also making sure that wildcards and output connections stay intact.


HOW TO USE: 

Run inside hammer: (recommended)

0. If Hammer is running, close it now
1. Drop "ente.exe" into the bin folder of your SDK (should also contain "hammer.exe", "vbsp.exe" ... etc)
2. Run "ente.exe" once in the folder
3. Hammer now has a new entry in the expert compile configuration menu called "HDR Full Compile -final -entE"
4. Compile your map with that configuration

Run as standalone:

0. Directory of "ente.exe" doesn't matter
1. Drag and drop a vmf onto "ente.exe"
2. Wait for it to finish
3. Check log for errors
4. Manually compile newly generated vmf


NOTES:

The program doesn't alter the original vmf. It instead creates a new one.
In case of an ambigious match, the program didn't know about the
corresponding input/keyvalue and thus declares it too risky to process. 
Make sure the match is actually a targetname and either put a FGD file 
with the input/keyvalue in question inside the program's folder or manually 
create a new one using this systax:

KEYVALUENAME(target_destination) ::: 
or
input INPUTNAME(target_destination) :

(replace KEYVALUENAME or INPUTNAME with the input/keyvalue)
