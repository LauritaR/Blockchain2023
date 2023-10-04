# Hash generatoriaus kūrimas 

## _Eksperimentinių tyrimų ir rezultatų analizė_

### _Apie funkciją_:

- Kiekviena įvestis turi **to paties ilgio išvestį**(64 simbolių hex'as).
- Funkcija gali priimti bet kokio dydžio įvestį.
- Tam pačiam įvedimui **išvedimas yra visuomet tas pats**. 
- To paties ilgio įvesčių hash'as yra skirtingas.
- Augant įvesties dydžiui, funkcijos efektyvumas keičiasi sekundės dalimis.
- Funkcija yra **atspari kolizijai**.
- Minimaliai pakeitus įvedimą, maišos kodas **keičiasi iš esmės**. 


![image](https://github.com/LauritaR/Blockchain2023/assets/116920291/75e583b9-6c15-4010-9e3f-c9d28cbc7ac9)


_**1.txt** ir **a.txt** yra vieno simbolio failai, 
**empty.txt** tuščias, 
failai **daug.txt** ir **maziau.txt** yra sudaryti iš daug(>1000) atsitiktinių simbolių, 
o **new.txt** ir **new2.txt** skiriasi tik vienu simboliu._

### Pseudokodas: 


function computations(input):

    length = length(input) * 8
    
    for i from 7 to 0:
        append input with (length >> (i * 8)) & 0xFF
    
    code_local = 46886
    var = 7
    secret_rand = 0
    hash_size = 8
    hash[hash_size] = {0}
    

    for each c in input:
   
        secret_rand = (code_local / var) - (var % 10)
        
        for i from 0 to hash_size - 1:
            hash[i] = (hash[i] XOR c) + secret_rand * (i + 1)
            hash[i] = (hash[i] XOR (hash[i] << 15) OR (hash[i] >> 21)) XOR 0x85ebca6b XOR 0xc2b2ae35
            var = var + 1
    
    result = ""
    for i from 0 to hash_size - 1:
        result = result + hexadecimal representation of hash[i] with 8 digits padded with zeros
    
    return result


## Hash funkcijos efektyvumas 

Failo **konstitucija.txt** hash'avimo laikos buvo matuojamas 5 kartus. Nuo 1 iki 16 eilučių hash'avimo vienu metu, procesas užtrukdavo po 0 s, kai hash'uojamų eilučių kiekis padidėjo ir nuo 32 eilučių iki 512 eilučių didėjo sekundės dalimis.

![image](https://github.com/LauritaR/Blockchain2023/assets/116920291/70ba1a1a-78a9-4f48-be1b-a543709406c9)


![image](https://github.com/LauritaR/Blockchain2023/assets/116920291/6a7bde9b-6645-499c-a979-b155b3de4e5b)


## Atsparumas kolizijai

| 25 tūkst. porų ilgis|Kolizijų skaičius|
|---------------------|-----------------|
|10                   |0                |
|100                  |0                |
|500                  |0                |
|1000                 |0                |

![image](https://github.com/LauritaR/Blockchain2023/assets/116920291/e30fabc6-8908-4727-a8a0-4d3aa6058c9f)


## Lavinos efektas(Avalanche effect)

Atlikus hash funkcijos lavinos efekto tyrimus, gauti tokie rezultatai:
 
![image](https://github.com/LauritaR/Blockchain2023/assets/116920291/5d86367a-9ca8-41dd-9c0b-e0a091773f3d)





