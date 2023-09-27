# Blockchain2023
Apie algoritmą:

- Kiekviena įvestis turi to paties ilgio išvestį(64 bit hex'as).
- To paties ilgio įvesties hash'as yra skirtingas.
- Augant įvesties dydžiui, funkcijos efektyvumas nėra prastėjantis.
- Funckija nėra visai atspari kolizijai( Iš 100 000 eilučių apie 600 kolizijų).
- Taip pat, lavinos efekto tyrimo metu, bitų ir hex'ų lygmenyje procentinio skirtumo rodiklis buvo žemiau negu vidutinis.

Apibendrinant, funkcijos lavinos efekto savybė turi būti pagerinta. 




Pseudocode: 

function computations(div_padded_bin_str)
    hash = 154568778
    code_local = 46886
    secret = 7531
    a = 7

    for each character c in div_padded_bin_str do
        hash = ((hash << 5) * a + c + div_padded_bin_str[c] + div_padded_bin_str[0]) - ((hash >> 2) % 10)
        a = a + 1

    final = convertToString(hash)
    var = 64
    var2 = 128

    repeat
        secret_rand = (code_local / var) - (var % 10)
        final = final + ((secret_rand >> 1) % 10 + var % 3)
        var = var + 1
    until length of final is 32

    computed = asciiToBinary(final)
    n = shiftRight(computed, 7)

    return n