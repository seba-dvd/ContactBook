# 📒 Agenda de Contacte

**Aplicatie de gestiune a contactelor scrisa in C++** — ruleaza in linia de comanda, cu salvare automata intr-un fisier text local si sortare cronologica.

---

## Functionalitati

- **Adaugare contact** cu validare completa pentru fiecare camp
- **Afisare agenda** sortata cronologic — cele mai recente contacte primele
- **Cautare contact** dupa Nume, Prenume sau Telefon
- **Modificare contact** — editare individuala a unui camp ales (Nume, Telefon, Email sau Adresa)
- **Stergere contact** cu confirmare inainte de executie
- **Export CSV** — genereaza `contacte_export.csv` compatibil cu Excel si Google Sheets
- **Salvare automata** la iesire in fisierul `contacte.txt`
- **Incarcare automata** la pornire — fara configurare manuala
- **Timestamp exact** — data si ora adaugarii fiecarui contact
- **Verificare duplicate** — telefonul si emailul trebuie sa fie unice in agenda

---

## Compilare si rulare

Nu sunt necesare biblioteci externe. Se folosesc exclusiv headere standard C++.

### g++ (Linux / macOS)

```bash
g++ -o agenda main.cpp
./agenda
```

### Windows (MinGW)

```bash
g++ -o agenda.exe main.cpp
agenda.exe
```

### Cerinte

- Compilator **C++11** sau mai nou
- Nu sunt necesare biblioteci externe

---

## Persistenta datelor

Datele sunt salvate in `contacte.txt`, in acelasi director cu executabilul. Exportul CSV este scris in `contacte_export.csv`.

Ordinea campurilor din `contacte.txt` este: `Nume` → `Prenume` → `Adresa` → `Judet` → `Oras` → `Tara` → `Telefon` → `Email` → `Timestamp (Unix)`.

---

## Structura proiect

```
ContactBook/
├── main.cpp
├── contacte.txt
├── contacte_export.csv
├── .vscode/
│   ├── settings.json
│   └── tasks.json
└── README.md
```
