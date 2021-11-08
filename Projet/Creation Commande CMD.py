import os

commande = ""                   # Variable contenant la commande de sortie

nomExe = "Source_7.exe"

cheminRun = ""                  # Chemin relatif des fichiers run
cheminIn = ""                   # Chemin relatif des fichiers in
cheminOut = ""                  # Chemin relatif des fichiers out

sprintMin = 1                   # Commence au Sprint n
sprintMax = 3                   # Termine par le Sprint n

utiliserFichiersProfs = True    # Utiliser les fichiers frauduleux (G07, G08, G09) ?
utiliserFichiersBase = True     # Utiliser les fichiers fournis par défaut ?

cheminBat = 'BUT Année 1\\Semestre 1\\Projets\\Projet-IAP\\Projet\\x64\\Debug\\'

for i in range(sprintMin, sprintMax+1):
    if utiliserFichiersProfs:
        for j in range(7, 10):
            commande += f'{nomExe} <"{cheminIn}inG0{j}Sp{i}.txt"> "{cheminRun}runG0{j}Sp{i}.txt" & fc.exe "{cheminOut}outG0{j}Sp{i}.txt" "{cheminRun}runG0{j}Sp{i}.txt" & '
    
    if utiliserFichiersBase:
        commande += f'{nomExe} <"{cheminIn}inSp{i}.txt"> "{cheminRun}runSp{i}.txt" & fc.exe "{cheminOut}outSp{i}.txt" "{cheminRun}runSp{i}.txt" & '

print(commande[:-3])

file = open(cheminBat+"listeCommande.bat", "w")
file.write(commande[:-3]+"\nPAUSE")
file.close()
