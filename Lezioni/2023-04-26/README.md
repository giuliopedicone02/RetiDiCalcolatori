# Comandi utili per Debian e gestione tramite SSH

**Installazione compilatore C**
```
sudo apt-get install gcc
```

**Verifica installazione compilatore C**
```
gcc --version
```

**Compilare un file in C**
```
gcc nomeFile.c -o nomeEseguibile
```

**Eseguire un file in C**
```
./nomeEseguibile
```

**Installazione SSH**
```
sudo apt-get install openssh-server
```

**Verifica installazione SSH**
```
ps ax | grep sshd
```

**Visualizzazione IP schede di rete**
```
ip a
```

**Connessione alla macchina virtuale tramite SSH**
```
ssh user@ip 
(Sostituire "ip" con quello IPv4 trovato eseguendo il comando sopra)
```

