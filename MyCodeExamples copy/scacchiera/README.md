Versione Finale del software per il controllo della scacchiera del Museo del Risorgimento di Ravenna.

Metodo: ARUCO

Librerie usate:
- OpenCV  v4.4.0
- Boost   v1.73.0
- pubixml v1.10 

## Funzionamento
La scacchiera ha le caselle sensibili in materiale semi-trasparente.
Alla base degli scacchi è presente un marker aruco di 5x5cm.
Sotto al tavolo è presente una telecamera USB con filtro IR e sul perimetro della scacchiera una barra led ad infrarossi sempre accesa.

Ogni scacco può essere posizionato su due delle 8 caselle sensibili, attivando quindi due video differenti ognuno.

Appena lo scacco viene posizionato su una delle due zone assegnate, parte un timer (la cui durata è determinata dal file di setting) al cui termine viene inviato un messaggio UDP verso il player (porta e IP determinati dal file di setting.

Nella cartella /data/ è presente un file "settings.xml" in cui si determinano i seguenti settaggi:
- dimensione, Id, posizione delle zone sensibili
- il match delle zone (per ogni marker ID, si assegnano due Id zone e i due messaggi da inviare al player)
- IP e porta del player 
- i valori di segmentazione iniziali (durante il runtime possono essere modificati e salvati da GUI)

## Installazione
Il programma si installa copiando la cartella Release che deve includere:
1. il file eseguibile "ravenna_scacchiera_aruco.exe"
2. il file "opencv_world440.dll"
3. la cartella data che deve contenere:
   - "settings.xml";
   - CameraCalibrationResult (eliminare se si vuole ri-creare automaticamente al riavvio del programma).

* la cartella data contiene anche il file "aruco_markers.pdf" con i 4 marker riconosciuti dal programma.

### Rilevazione Coordinate Zone

- cliccando sullo schermo in prossimità del punto di interesse, si possono leggere sulla console printerà le sue coordinate. Impostare di conseguenza la x e la y e calcolare width e height.
- inserire o modificare il xml di settaggio in /data

Murat    --> tag 0
Pio VII  --> tag 1
Mazzini  --> tag 2
Rivarola --> tag 3

| ---------- | ---------- | ---------- | ---------- | 
| Murat      | ---------- | Murat      | ---------- |
| 30-03-1815 | ---------- | 05-04-1815 | ---------- |
| ---------- | ---------- | ---------- | ---------- | 
| ---------- | Pio VII    | ---------- | Rivarola   |
| ---------- | 19-07-1815 | ---------- | 19-05-1824 |
| ---------- | ---------- | ---------- | ---------- | 
| Rivarola   | ---------- | Rivarola   | ---------- |
| 11-09-1826 | ---------- | 12-07-1824 | ---------- |
| ---------- | ---------- | ---------- | ---------- | 
| ---------- | Mazzini    | ---------- | Mazzini    |
| ---------- | 09-02-1831 | ---------- | xx-xx-1832 |
| ---------- | ---------- | ---------- | ---------- | 


N.B.
- Nello schermo le zone appariranno al contrario perché riprese dal  basso 
  ma non flippare l'immagine o la lettura dei tag risulterà errata.
