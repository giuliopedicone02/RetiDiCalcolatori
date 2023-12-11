# Secure Copy Protocol

Protocollo che permette di copiare un file tra due dispositivi connessi tramite SSH

**Sintassi:**    
 ```bash
scp [OPZIONI] [[user@]src_host:]file1 [[user@]dest_host:]file2
```

## Esempio di funzionamento (SSH -> Locale)

1) Aprire un terminale nella macchina locale e connettersi alla macchina virtuale tramite **SSH**
```bash 
ssh user@ip
 ```
2) Navigare verso il file/directory da voler copiare nella macchina locale ed utilizzare il comando **pwd** per visualizzare il percorso completo
3) Aprire un nuovo terminale nella macchina locale ed utilizzare il comando **scp** indicando come:
    - **src_host:** user@ip:percorso
    - **dest_host:** percorso locale dove copiare il file/directory

```bash 
# Esempio di funzionamento

scp user@192.168.56.107:/home/user/client.c ./

# Copia il file client.c nella home directory del computer locale
 ```

 ## Esempio di funzionamento (Locale -> SSH)

1) Aprire un terminale nella macchina locale ed utilizzare il comando **scp** indicando come:
    - **src_host:** percorso del file/directory da voler copiare
    - **dest_host:** user@ip:percorso

```bash 
# Esempio di funzionamento

scp C:\Users\user\Desktop\Folder\* user@192.168.56.107:/home/user

# Copia il contenuto della cartella 'Folder' presente sul desktop del dispositivo locale nella cartella 'home/user' del dispositivo connesso tramite SSH
 ```