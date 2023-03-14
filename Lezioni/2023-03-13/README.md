# Introduzione a C

Hello World in C:
```C
#include <stdio.h>

int main(int argc, char **argv)
{
    printf("Hello World!");
    return 0;
}
```

# printf()

```C
int a = 5, b = 10, c = 15;
printf("a: %d, b: %d, c: %d", a, b, c);
```

Serve per stampare in output testo e variabili.

**ATTENZIONE:** Ogni tipo di dato richiede il suo specificatore di formato.

# Specificatori di formato

| Formato 	|                 Tipo                 	|
|:-------:	|:------------------------------------:	|
|    %c   	|               Caratteri              	|
|    %d   	|                Interi                	|
|    %f   	|                 Float                	|
|    %e   	|         Notazione Scientifica        	|
|    %u   	|             Unsigned Int             	|
|   %li   	|               Long Int               	|
|   %lu   	|           Long Unsigned Int          	|
|   %le   	| Long Double in Notazione Scientifica 	|
|    %s   	|               Stringhe               	|

# scanf()

```C
int a = 0;

printf("Scrivi valore di a: ");
scanf("%d", &a);

printf("Valore inserito: %d", a);
```

La funzione scanf() permette di gestire l'input da tastiera.

Il suo prototipo prevede due parametri:

* Specificatore di formato
* Indirizzi delle variabili (puntatori a tali variabili)

**ATTENZIONE:** Prima del nome della variabile va **SEMPRE** posto il carattere &, tranne per gli array di caratteri in quanto l'array è già un puntatore.

# Stringhe in C

Le stringhe a differenza di C++, in C vengono viste come array di char che terminano con il carattere '\0'.

Alcuni metodi utili che ci fornisce la libreria <string.h> sono:

* **strcpy:** Copia stringa 2 su stringa 1 
* **strncpy:** Copia i primi n caratteri di stringa 2 su stringa 1 
* **strcat:** Concatena stringa 1 e stringa 2
* **strcmp:** Confronta stringa 1 e stringa 2 restituisce:
    * 0: stringa 1 e stringa 2 sono uguali
    * \>0: stringa 1 maggiore di stringa 2 
    * \<0: stringa 1 minore di stringa 2 

# Struct in C

```C
struct automobile
{
    char *marca;
    char *modello;
    int venduto;
};
```

Gli elementi della struttura sono detti membri.
Essi sono identificati da un nome, nomeMembro, e da un tipo, tipoMembro. 

Una volta definita una struttura, nomeStruttura diviene un nuovo tipo a tutti gli effetti.

# File in C

Per gestire file in C si utilizza il tipo di dato FILE, struttura dati definita nella libreria <stdio.h>

## Apertura di un file in C

```C
FILE *file = fopen("input.txt", "r");
```

Si utilizza il metodo fopen() che prende due parametri:

* Pathname del file
* Modalità di apertura del file

| Modalità 	|                      Descrizione                     	|
|:--------:	|:----------------------------------------------------:	|
|    "r"   	|                        Lettura                       	|
|    "w"   	|                       Scrittura                      	|
|    "a"   	|             Append (Apertura in aggiunta)            	|
|   "rb"   	|                  Lettura file binari                 	|
|   "wb"   	|                 Scrittura file binari                	|
|   "r+"   	| Apertura di un file esistente in lettura e scrittura 	|
|   "w+"   	|   Apertura di un file vuoto in lettura e scrittura   	|
|   "a+"   	|            Apertura in lettura ed aggiunta           	|

Il metodo fopen() restituisce NULL in caso di fallita apertura

```C
 if (file == NULL)
    {
        printf("Impossibile aprire il file");
        return 1;
    }
```
## Chiusura di un file in C

```C
fclose(file);
```

Il metodo fclose() restituisce:
* 0: Chiusura avvenuta con successo
* EOF: Errore in fase di chiusura

## End Of File
```C
feof(file);
```
Il metodo feof() restituisce:
* 0: NON è stata raggiunta la fine di un file
* !0: Fine del file

# fscanf()

```C
fscanf(file, "%s", &buffer);
```
Il metodo fscanf() serve a **leggere** un file e prevede tre parametri:
* Puntatore allo stream (il file nel nostro esempio)
* Specificatori di formato
* Variabili

**Nota Bene:**

* Elimina automaticamente gli spazi
* Considera finita una stringa al primo spazio che trova

# fprintf()

```C
fprintf(file, "%s", var);
```
Il metodo fscanf() serve a **scrivere** su un file e prevede tre parametri:
* Puntatore allo stream (il file nel nostro esempio)
* Specificatori di formato
* Variabili

# ferror()

```C
ferror(file);
```
Controlla se è stato commesso un errore nell'operazione di lettura/scrittura precedente.

Il metodo ferror() restituisce:
* 0: NON ci sono stati errori
* !0: Altrimenti

# clearerr()

```C
clearerr(file);
```
Riporta al valore di default lo stato delle informazioni di fine file ed errori ati ai file.

Il metodo ferror() restituisce:
* 0: NON ci sono stati errori
* !0: Altrimenti

# Lettura di stringhe
```C
fgets(s, n, file);
```

Trasferisce nella stringa s gli n-1 caratteri del file puntato.

Restituisce:
* La stringa
* NULL in caso di errore o fine del file

# Scrittura di stringhe
```C
fputs(s, file);
```

Trasferisce la stringa s nel file puntato.

Restituisce:
* \>0: Terminazione corretta
* EOF: altrimenti

# File Binari

Rappresentano una pura sequenza di byte

## Output binario

```C
fwrite(address, dim, n, file);
```

Scrive sul file n elementi grandi dim byte a partire dall'indirizzo address.

## Input binario

```C
fread(address, dim, n, file);
```

Legge dal file n elementi grandi dim byte a partire dall'indirizzo address.

# Operatori Bitwise

| Operatore 	|    Descrizione   	|
|:---------:	|:----------------:	|
|     &     	|   AND bit a bit  	|
|     \|    	|   OR bit a bit   	|
|     ^     	|   XOR bit a bit  	|
|     ~     	|   NOT bit a bit  	|
|     <<    	| SHIFT a sinistra 	|
|     >>    	|  SHIFT a destra  	|

| a 	| b 	| a&b 	| a\|b 	| a^b 	|
|:-:	|:-:	|:---:	|:----:	|:---:	|
| 0 	| 0 	|  0  	|   0  	|  0  	|
| 0 	| 1 	|  0  	|   1  	|  1  	|
| 1 	| 0 	|  0  	|   1  	|  1  	|
| 1 	| 1 	|  1  	|   1  	|  0  	|