Skupinova prace
Skupina: Jan Bartoň, Nikola Haluzová, Lukáš Kalenský, Vladan Kořenek, Marek Ševčík

Dungeon Crawler - Textová hra

Dungeon Crawler je interaktivní textová hra napsaná v jazyce C++. Cílem hráče je prozkoumávat místnosti, bojovat s nepřáteli, sbírat předměty a přežít. Hra spojuje strategické prvky s jednoduchou grafikou a příběhem.


Popis funkcí

1. Hlavní průběh hry

• Hráč začíná hru se startovními hodnotami zdraví (HP) a zlatem.

• Hlavní herní obrazovka zahrnuje základní informace o stavu hráče, nepřátelích a obsahu místnosti.

• Hráč se pohybuje mezi místnostmi pomocí šipek na klávesnici.

• Souboje v místnostech jsou řízené náhodnými hodnotami a bonusy hráče.

2. Generování místností

Použití třídy Mistnost pro náhodné vytváření místností s různými vlastnostmi a obsahem.

3. Zdraví a inventář

Správa hráče probíhá přes třídu StatBar, kde:

• getHealth() sleduje aktuální stav zdraví hráče.

• getInventory() informuje o předmětech v inventáři.

• getGold() zobrazuje množství nasbíraného zlata.

4. Souboje

Pomocí funkce combat.fight() dochází k soubojům s náhodnými nepřáteli generovanými funkcí getRandomEnemy().

5. Vizuální styl

Vykreslování místností a rozhraní hry realizuje třída Kresleni, která spravuje:

• Zobrazení místností a obsahu.

• Psání statistik hráče a nepřátel.

• Vykreslení aktuální herní situace.


Klíčové výstupy ve hře

• Výsledky soubojů: Hráč může vyhrát nebo prohrát, což ovlivní jeho zdraví (damage od nepřátel).

• Náhodné události: V místnosti se mohou objevit předměty nebo nepřátelé.