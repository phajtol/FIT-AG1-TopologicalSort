# FIT-AG1-TopologicalSort

This is a project created as a homework for subject Algorithms and Graphs 1 (BI-AG1 - Algoritmy a grafy 1) at FIT CTU.

Full assignment in Czech language is below.

Summary of the assignment: For a given input graph, calculate its topological sort or if it's not possible, announce the fact.

---

Basically, the point of this assignment is to implement your own linked list.

My solution is in file `solution.cpp`, function main of this file contains test data for basic scenarios.

My solution includes custom version of vector and linked list data containers since using C++ STL was not allowed.

My solution has received maximum points (including big data test).

# Assignment

Prototyp nového modelu auta sice těší designéry a manažery místní automobilky, ale inženýrům zodpovědným za plánování průběhu výroby nepřináší nic než noční můry. Designéři se totiž na novém modelu náležitě vyřádili a ke kompletaci vozu je zapotřebí postupně smontovat velmi vysoké množství dílčích součástek. Navíc mnohdy nastává případ, kdy nelze některou součástku smontovat dříve, než jsou smontovány jiné součástky, na kterých montáž závisí (např. pro smontování dveří je zapotřebí mít připravený zámek a kliku, mechanismus stahování okének, okénko, těsnění, atp.).

Kvůli komplexnosti konstrukce nového modelu auta je tak zapotřebí průběh výroby auta precizně naplánovat. Jinak by totiž hrozilo, že doba potřebná pro kompletaci jednoho vozu bude dlouhodobě nerentabilní. Vzhledem k tomu, že se nejedná o úlohu, kterou by bylo možno vzhledem k objemu součástek vyřešit ručně, byli jste na řešení tohoto problému povoláni vy. Konkrétně je zapotřebí pro daný výrobní plán, určující závislosti součástek při montáži, a pro dané doby nutné pro montáž součástek určit, kdy přesně se ta která součástka má začít montovat tak, aby celková doba potřebná pro sestavení jednoho vozu byla minimální (k sestavení vozu je zapotřebí smontovat všechny součástky uvedené ve výrobním plánu).

K dispozici máte na vstupu počet součástek, časy nutné pro montáž jednotlivých součástek a výrobní plán, který pro každou součástku určuje součástky, které je zapotřebí smontovat před její montáží. Nelze začít montovat konkrétní součástku předtím, než jsou smontovány všechny součástky, na kterých její výroba závisí. Nezáleží-li montáž součástky na montáži žádné jiné součástky, lze ji začít montovat okamžitě. Pokud je součástka smontována v čase `x`, lze jí okamžitě použít pro montáž jiné součástky také v čase `x`. Předpokládejte, že pro montování součástek je vyčleněno neomezené množství dělníků, tj. v jeden okamžik lze montovat libovolné množství součástek. Může nastat situace, kdy designéři při honbě za perfektním návrhem vozu sestaví nevalidní výrobní plán, který z nějakého důvodu nelze realizovat. Takový případ musíte detekovat. Také je možné, že existuje více řešení, které minimalizují dobu pro kompletaci vozu, ale liší se časy pro montáž součástek. V takovém případě vypište libovolné z těchto řešení.

Vzhledem k aféře dieselgate je v automobilkách zakázán veškerý software, který byl použit pro podvody při měření emisí. Toto opatření se týká i knihovny STL a nelze ji tak při řešení této úlohy použít.

#### Formát vstupu:

- Na prvním řádku je číslo `N` udávající počet součástek nutných ke kompletaci jednoho vozu.
Součástky jsou číslovány od nuly, mají tedy čísla `0`, `1`, ..., `N - 1`.
- Na dalším řádku je `N` čísel `t0`, `t1`, ..., `tn-1`, `0 < ti < 10^9`. i-té číslo `ti` udává čas, který je potřeba pro montáž i-té součástky.
- Poté následuje `N` řádků, postupně pro součástky `0` až `N - 1`. Na začátku řádku je číslo udávající počet součástek potřebných k montáži dané součástky (toto číslo může být i 0), a následuje mezerami oddělený seznam čísel těchto součástek.
- Žádná součástka není uvedena ve svém vlastním seznamu závislostí a žádná součástka není uvedena v seznamu závislostí vícekrát.
- Výrobní plán se vždy skládá z alespoň jedné součástky, ale mezi součástkami nemusí existovat žádná závislost. Z toho vyplývá, že mohou existovat dvojice součástek, které na sobě vzájemně nezávisí (a to ani tranzitivně přes jiné součástky).
- Můžete předpokládat, že vstup je korektní.

#### Formát výstupu:

- Pokud nelze sestavit výrobní plán pro zadané závislosti součástek, program má vypsat na samostatný řádek řetězec "No solution." (bez uvozovek).
- Pokud řešení existuje, výstup sestává ze dvou řádků. Na prvním řádku program vypíše minimální dobu potřebnou pro smontování všech součástek auta. Na druhém řádku následuje `N` mezerami oddělených čísel, kde i-té z nich udává čas, kdy se má začít montovat i-tá součástka.

#### Bodové podmínky:

Pro splnění povinných testů (test základními a malými daty) je zapotřebí, aby program fungoval korektně pro výrobní plány o nejvýše 10 součástkách a 20 závislostech.
Pro splnění testu středními daty musí program splnit časový a paměťový limit pro plány o nejvýše 100 součástkách a 1 000 závislostech.
Pro splnění testu velkými daty musí program splnit časový a paměťový limit pro plány o nejvýše 100 000 součástkách a 1 000 000 závislostech.
