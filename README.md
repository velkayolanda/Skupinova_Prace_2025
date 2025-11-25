# Skupinová Práce - Dungeon Crawler

**Skupina:** Jan Bartoň, Nikola Haluzová, Lukáš Kalenský, Vladan Kořenek, Marek Ševčík

## 📖 O Hře

**Dungeon Crawler** je interaktivní textová hra napsaná v jazyce C++. Cílem hráče je prozkoumávat místnosti, bojovat s nepřáteli, sbírat předměty a přežít. Hra spojuje strategické prvky s jednoduchou grafikou a příběhem.

---

## ✨ Klíčové Funkce

### 1. Hlavní Průběh Hry
- Hráč začíná se startovními hodnotami zdraví (HP) a zlatem
- Hlavní herní obrazovka zobrazuje stav hráče, nepřátel a obsah místnosti
- Pohyb mezi místnostmi pomocí šipek na klávesnici
- Souboje řízené náhodnými hodnotami a bonusy hráče

### 2. Generování Místností
Třída `Mistnost` zajišťuje náhodné vytváření místností s různými vlastnostmi a obsahem.

### 3. Zdraví a Inventář
Třída `StatBar` spravuje:
- `getHealth()` — aktuální stav zdraví hráče
- `getInventory()` — předměty v inventáři
- `getGold()` — nasbírané zlato

### 4. Souboje
Funkce `combat.fight()` řídí souboje s náhodně generovanými nepřáteli pomocí `getRandomEnemy()`.

### 5. Vizuální Styl
Třída `Kresleni` spravuje:
- Zobrazení místností a jejich obsahu
- Vykreslení statistik hráče a nepřátel
- Vykreslení aktuální herní situace

---

## 🎮 Klíčové Výstupy ve Hře

- **Výsledky soubojů:** Hráč může vyhrát nebo prohrát, což ovlivní jeho zdraví
- **Náhodné události:** V místnostech se objevují předměty a nepřátelé
