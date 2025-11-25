# 🗡️ Dungeon Crawler

> Interaktivní textová RPG hra napsaná v C++

[![C++](https://img.shields.io/badge/C++-11%20or%20higher-blue.svg)](https://isocpp.org/)
[![Platform](https://img.shields.io/badge/platform-Windows%20%7C%20macOS%20%7C%20Linux-lightgrey.svg)](https://github.com)
[![License](https://img.shields.io/badge/license-MIT-green.svg)](LICENSE)

**Autoři:** Jan Bartoň, Nikola Haluzová, Lukáš Kalenský, Vladan Kořenek, Marek Ševčík

---

## 📖 O Projektu

**Dungeon Crawler** je klasická textová dungeon RPG, kde hráč prozkoumává tajemné místnosti, bojuje s nebezpečnými nepřáteli, sbírá cenné předměty a snaží se přežít v nepřátelském světě. Hra kombinuje strategické rozhodování s náhodnými událostmi a postupnou progresí postavy.

### ✨ Hlavní Funkce

- 🎲 **Procedurálně generované místnosti** s náhodným obsahem
- ⚔️ **Dynamický bojový systém** založený na kostách
- 🎒 **Systém inventáře a loot** s různými předměty
- 💰 **Ekonomika** se zlatem a obchodováním
- 📊 **Statistiky postavy** (HP, síla, obrana)
- 🗺️ **Navigace** mezi místnostmi pomocí šipek
- 🎨 **ASCII vizualizace** herního světa

---

## 🔧 Technické Požadavky

| Požadavek | Specifikace |
|-----------|-------------|
| **C++ Standard** | C++11 nebo vyšší |
| **Kompilátor** | GCC, Clang, nebo MSVC |
| **Build System** | CMake 3.10+ |
| **OS** | Windows, macOS, Linux |
| **Knihovny** | Standardní C++ knihovna (STL) |

### Doporučené Vývojové Prostředí

- CLion (doporučeno)
- Visual Studio Code
- Visual Studio 2019+
- Jakýkoli C++ kompatibilní editor

---

## 🚀 Instalace a Spuštění

### Metoda 1: CLion (Doporučeno)

1. **Otevřete projekt v CLion**
   ```
   File → Open → vyberte složku projektu
   ```

2. **Build projekt**
   ```
   Build → Build Project (Ctrl+F9)
   ```

3. **Spusťte hru**
   ```
   Klikněte na zelené tlačítko Run (Shift+F10)
   ```

### Metoda 2: Příkazový Řádek (Windows)

```bash
cd C:\cesta\k\projektu\Textova_hra
mkdir build
cd build
cmake ..
cmake --build .
.\Debug\Textova_hra.exe
```

### Metoda 3: Příkazový Řádek (Linux/macOS)

```bash
cd /cesta/k/projektu/Textova_hra
mkdir build
cd build
cmake ..
make
./Textova_hra
```

---

## 🎮 Jak Hrát

### Ovládání

- **Šipky** - Pohyb mezi místnostmi
- **Číselné klávesy** - Výběr akcí v menu
- **Enter** - Potvrzení volby

### Herní Mechaniky

#### 🗺️ Průzkum
- Prozkoumávejte náhodně generované místnosti
- Každá místnost může obsahovat nepřátele, poklady nebo být prázdná
- Strategicky plánujte svou cestu

#### ⚔️ Souboje
- Bojový systém založený na házení kostkou
- Využívejte bonusy z předmětů a statistik
- Různé typy nepřátel s unikátními vlastnostmi

#### 🎒 Inventář
- Sbírejte předměty pro zlepšení statistik
- Spravujte zlaté mince pro nákupy
- Loot se generuje na základě obtížnosti

#### 📈 Progrese
- Získávejte zkušenosti z bojů
- Zlepšujte své statistiky
- Odemykejte nové oblasti

---

## 📁 Struktura Projektu

```
Textova_hra/
│
├── src/                          # Zdrojové soubory
│   ├── combat.cpp/.h            # Bojový systém
│   ├── dice_roll.cpp/.h         # Generátor náhodných čísel
│   ├── difficulty.cpp/.h        # Správa obtížnosti
│   ├── enemy_types.cpp/.h       # Definice nepřátel
│   ├── inventory.cpp/.h         # Systém inventáře
│   ├── Kresleni.cpp/.h          # Vykreslování UI
│   ├── loot.cpp/.h              # Generování loot
│   ├── Mistnost.cpp/.h          # Generování místností
│   ├── pravidla_hry.cpp/.h      # Herní pravidla
│   └── StatBar.cpp/.h           # Statistiky hráče
│
├── data/                         # Datové soubory
│   ├── 1J_Ctverec.txt           # Šablona místnosti
│   ├── enemies.txt              # Databáze nepřátel
│   ├── loot_table.txt           # Tabulka předmětů
│   ├── pravidla.txt             # Pravidla hry
│   ├── tvorba_mistnosti_pomocnik.txt
│   └── world.txt                # Mapa světa
│
├── CMakeLists.txt               # Konfigurační soubor CMake
└── README.md                    # Tento soubor
```

---

## 🏗️ Architektura

### Klíčové Třídy

| Třída | Popis |
|-------|-------|
| **StatBar** | Správa zdraví, inventáře a zlata hráče |
| **Mistnost** | Generování a správa herních místností |
| **Combat** | Řízení bojového systému |
| **Kresleni** | Vykreslování herního rozhraní |
| **Inventory** | Správa předmětů a vybavení |
| **EnemyTypes** | Definice a vlastnosti nepřátel |
| **Loot** | Generování a rozdělování loot |
| **DiceRoll** | Simulace házení kostkou |

---

## 🛠️ Možnosti Rozšíření

Projekt je navržen pro snadné rozšíření:

- ➕ **Nové typy nepřátel** - Upravte `enemies.txt`
- 🎁 **Nové předměty** - Rozšiřte `loot_table.txt`
- 🗺️ **Nové oblasti** - Vytvořte nové šablony místností
- ⚙️ **Herní mechaniky** - Přidejte nové soubory do `src/`

---

## 🐛 Řešení Problémů

### Hra se nespustí
- Zkontrolujte, zda máte správně nainstalovaný C++ kompilátor
- Ověřte, že CMake našel všechny potřebné soubory
- Ujistěte se, že složka `data/` je přístupná

### Chyby při kompilaci
- Použijte kompilátor podporující C++11 nebo vyšší
- Zkuste smazat složku `build/` a zkompilovat znovu
- Zkontrolujte konzistenci názvů souborů

### Problémy s daty
- Ujistěte se, že všechny `.txt` soubory jsou ve správné složce
- Zkontrolujte kódování souborů (UTF-8 doporučeno)

---

## 📝 Licence

Tento projekt je součástí školní skupinové práce. Pro informace o licenci kontaktujte autory.

---

## 👥 Kontakt

Pro otázky, návrhy nebo hlášení chyb kontaktujte některého z členů týmu:

- Jan Bartoň
- Nikola Haluzová
- Lukáš Kalenský
- Vladan Kořenek
- Marek Ševčík

---

<div align="center">

**Vydejte se na dobrodružství do temných kobek! 🗡️🛡️**

*Vytvořeno s ❤️ týmem Dungeon Crawler*

</div>