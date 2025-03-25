Domácí úkol č.1 z IJC

Termín odevzdání: 25. 3. 2025
Pokyny k vypracování

    Programy pište, pokud je to možné, do jednoho zdrojového souboru. Dodržujte předepsaná jména souborů.
    Na začátek každého souboru napište poznámku, která bude obsahovat jméno, fakultu, označení příkladu, datum a jméno překladače, kterým byl program testován.

    // primes.c
    // Řešení IJC-DU1, příklad a), 20.3.2111
    // Autor: John Wick, FIT
    // Přeloženo: gcc 12.2
    // ...popis příkladu - poznámky, omezení, atd

    Používejte standard ISO C11 (soubory *.c).
    Použití nepřenositelných konstrukcí není dovoleno.
    Příklady budou opravovány v prostředí Linux/GCC, LC_ALL=cs_CZ.utf8 a překládány příkazem gcc -g -std=c11 -pedantic -Wall -Wextra. Pro vlastní testování můžete místo GCC jiný překladač (napište to do poznámky).
    Programy musí fungovat na 32 (gcc -m32) i 64bitové platformě.
    Pro ověření správnosti paměťových operací zkuste extra parametry pro gcc (Makefile: CFLAGS += -fsanitize=address, LDFLAGS += -fsanitize=address).

Příklad A
Část 1: Knihovna bitset.h

V rozhraní „bitset.h“ definujte datovou strukturu typu pole bitů. Pro vaši implementaci použijte pole typu unsigned long[]. V tomto poli na indexu 0 bude velikost bitového pole v bitech. Implementace musí efektivně využívat paměť (využít každý bit pole až na posledních maximálně CHAR_BIT*sizeof(unsigned long)-1 bitů).

// Typ bitového pole (pro předávání parametru do funkce odkazem).
typedef <DOPLNIT> bitset_t;

// Typ indexu bitového pole.
typedef unsigned long bitset_index_t;

Definujte také makra, které s ní pracují:

    bitset_create(jméno_pole, velikost)

    Definuje a nuluje proměnnou jméno_pole. Použijte static_assert pro kontrolu velikosti pole.

    (Pozor: opravdu musí inicializovat pole bez ohledu na to, zda je pole statické nebo automatické/lokální! Vyzkoušejte obě varianty, v programu použijte lokální pole.)

    static bitset_create(p, 100); // p = pole 100 bitů, nulováno
    bitset_create(q, 100000L);    // q = pole 100000 bitů, nulováno
    bitset_create(q, -100);       // chyba při překladu

    bitset_alloc(jméno_pole, velikost)

    Definuje proměnnou jmeno_pole tak, aby byla kompatibilní s polem vytvořeným pomocí static_assert, ale pole bude alokováno dynamicky. Použijte assert pro kontrolu maximální možné velikosti pole. Pokud alokace selže, ukončete program s chybovým hlášením: "bitset_alloc: Chyba alokace paměti"

    bitset_alloc(q, 100000L);     // q = pole 100000 bitů, nulováno

    bitset_free(jméno_pole)

    Uvolní paměť dynamicky (bitset_alloc) alokovaného pole.
    bitset_size(jméno_pole)

    Vrátí deklarovanou velikost pole v bitech (uloženou v poli).
    bitset_fill(jméno_pole, bool_výraz)

    Vynuluje (false) nebo nastaví na 1 (true) celý obsah pole
    bitset_setbit(jméno_pole, index, bool_výraz)

    Nastaví zadaný bit v poli na hodnotu zadanou výrazem (nulový výraz == false == bit 0, jinak bit 1). Kontrolujte meze polí. V případě chyby volejte funkci z modulu error.c/error.h v příkladu B:

    error_exit("bitset_getbit: Index %lu mimo rozsah 0..%lu", (unsigned long)index, (unsigned long)mez)

    bitset_setbit(p, 20, 1);

    bitset_getbit(jméno_pole, index)

    Získá hodnotu zadaného bitu, vrací hodnotu 0 nebo 1. Stejně jako u bitset_setbit kontrolujte meze polí.

    if (bitset_getbit(p, i) == 1) printf("1");
    if (!bitset_getbit(p, i))     printf("0");

Podmíněným překladem zajistěte, aby se všude kde je to možné místo těchto maker definovaly inline funkce stejného jména, a to při definovaném symbolu USE_INLINE (bez změn v následujícím testovacím příkladu!).

Pozor: USE_INLINE nesmí být definováno ve zdrojovém textu — překládá se s argumentem -D (gcc -DUSE_INLINE ...).

Program musí fungovat s inline funkcemi i pro vypnuté optimalizace -O0 (ověřte si to - vyžaduje externí definice inline funkcí).

Část 2: Eratostenovo síto

Jako testovací příklad implementujte funkci, která použije algoritmus známý jako Eratostenovo síto (void Eratosthenes(bitset_t pole)), a použijte ji pro výpočet posledních 10 prvočísel ze všech prvočísel od 2 do N=333000000 (333 milionů). (Doporučuji program nejdříve odladit pro N=100.) Hodnotu N si funkce zjistí podle velikosti bitového pole.

Každé prvočíslo tiskněte na zvláštní řádek ve vzestupném pořadí. Netiskněte nic jiného než prvočísla. (Bude se automaticky kontrolovat!) Pro kontrolu správnosti prvočísel můžete použít program „factor“. (./primes | factor).

Naprogramujte (s využitím funkce clock()) měření doby běhu programu v sekundách a výsledek vypište na stderr následujícím příkazem:

fprintf(stderr, "Time=%.3g\n", (double)(clock()-start)/CLOCKS_PER_SEC);

(Porovnejte si vaše měření s výsledkem příkazu „time ./primes“.)

Pro lokální pole budete potřebovat zvětšit limit velikosti zásobníku. Na Unix-like systémech můžete použít příkaz „ulimit -a“ pro zjištění velikosti limitu a potom „ulimit -s zadana_velikost_v_KiB“ před spuštěním programu. (Toto názorně demonstruje nevhodnost používání velkých lokálních polí.)

Zdrojový kód této části napište do souboru „primes.c“ a funkci Eratosthenes napište do samostatného modulu „eratosthenes.c“.
Přibližná specifikace Eratostenova síta

    Nastavíme bitové pole p o rozměru N na samé 1.

    // Přeskočíme 0 a 1 - nejsou to prvočísla
    p[0]=0; p[1]=0;
    i = 2;

    Vybereme nejmenší index i, takový, že p[i]==1. Potom je i prvočíslo.
    Pro všechny násobky i nastavíme bit p[n*i]==1 na 0. Tím „vyškrtneme“ všechny násobky i - nejsou to prvočísla.

    Zvyšujeme i, dokud nejsme za sqrt(N), opakujeme bod 3 až 5.

    Pozor: sestavit s matematickou knihovnou parametrem -lm
    Výsledek: V poli p jsou na prvočíselných indexech hodnoty 1. (= Nebyly vyškrtnuty jako násobek nějakého menšího prvočísla.)

Efektivita výpočtu: cca 2.0s na AMD Ryzen 5 4600G @ 4.3GHz (gcc -O2). Porovnejte efektivitu obou variant (makra vs. inline funkce). Zamyslete se, jak by se ověřila efektivita pro (neinline) funkce.
Příklad B
Část 1: Knihovna error.h

Napište modul „error.c“ s rozhraním v „error.h“, který definuje funkce:

void warning(const char* fmt, ...);
void error_exit(const char* fmt, ...);

Tyto funkce mají stejné parametry jako printf() a:

    Tisknou text "Warning: " nebo "Error: " a potom chybové hlášení podle formátu fmt na stderr (standardní funkcí vfprintf).
    Potom pouze error_exit ukončí program voláním funkce exit(1). Použijte definice z knihovny <stdarg.h>.

Část 2: Knihovna ppm.h

Napište modul „ppm.c“ s rozhraním „ppm.h“, ve kterém definujete typ:

struct ppm {
	unsigned xsize;
	unsigned ysize;
	char data[];    // RGB bajty, celkem 3*xsize*ysize
};

A funkce:

    struct ppm* ppm_read(const char* filename);

    Načte obsah PPM souboru do touto funkcí dynamicky alokované struktury. Při chybě formátu použije funkci warning a vrátí NULL. Pozor na „memory leaks“.
    void ppm_free(struct ppm* p);

    Uvolní paměť dynamicky alokovanou v ppm_read.

Můžete doplnit další funkce, ale pro domácí úkol 1 to není nutné. (Zamyslete se nad (ne)vhodností použití warning() a promyslete alternativní způsoby hlášení různých chyb.)

Můžete omezit max. velikost XY souřadnic obrázku vhodným implementačním limitem (např. 16000). Alokujte vždy jen minimální potřebný prostor pro obrazová data.

Popis formátu PPM najdete na Internetu, implementujte pouze binární variantu P6 s barvami 0..255 a bez komentářů:

P6<ws+>
<width><ws+><height><ws+>
<colors><ws>
<data>
<EOF>

    P6: Tyto dva znaky jsou na začátku každého PPM souboru. Je to tzv. „magic number“.
    <ws+>: Sekvence jednoho či více bílých znaků, tj. mezer, tabulátorů, nových řádků a všeho jiného pro co funkce isspace z knihovny <ctype.h> vrací true.
    <width>: Šířka obrázku zapsaná v ASCII v desítkové soustavě.
    <height>: Obdobně výška obrázku.
    <colors>: Maximální hodnota barvy (zapsaná v ASCII v desítkové soustavě) v jednom barevném kanálu. Může mít hodnotu od 1 do 65535 (pro tento DÚ vždy 255).
    <ws>: Právě jeden bílý znak (typicky nový řádek).

    <data>: Binární rastr hodnot barevných kanálů v pořadí červený, zelený a modrý. Podle maximální hodnoty barvy je jeden barevný kanál reprezentován buď jedním (<colors> ≤ 255, tato varianta nastane v tomto DÚ) nebo dvěma (<colors> ≥ 256) byty. Každý barevný kanál je kódován jako big-endian binární číslo, tedy pokud je reprezentováno dvěma byty, tak první je ten významnější.

Část 3: Dekódování tajné zprávy

Testovací obrázek Testovací obrázek: du1-obrazek.ppm

Napište testovací program „steg-decode.c“, kde ve funkci main načtete ze souboru zadaného jako jediný argument programu obrázek ve formátu PPM a v něm najdete uloženou „tajnou“ zprávu. Zprávu vytisknete na stdout.

Zpráva je řetězec znaků (char, včetně '\0') uložený po jednotlivých bitech (počínaje LSb) na nejnižších bitech (LSb) vybraných bajtů barevných složek v datech obrázku. Dekódování ukončete po dosažení '\0'. Pro tento domácí úkol budou vybrané bajty určeny prvočísly (počínaje od START_PRIME) — použijte Eratostenovo síto podobně jako v příkladu „primes.c“ a začněte prvočíslem START_PRIME = 101. Velikost dynamicky alokovaného bitového pole musí odpovídat velikosti obrazových dat RGB.

Program použije error_exit v případě chyby čtení souboru (chybný formát), a v případě, že zpráva není korektně ukončena '\0'. Předpokládejte uložení textu zprávy ve formátu UTF-8 a zkontrolujte to. (Použijte např. https://www.cl.cam.ac.uk/~mgk25/ucs/utf8_check.c)

Zájemci si mohou vytvořit i program „steg-encode.c“ (nehodnotí se). Zamyslete se nad (ne)vhodností použití implementačních limitů.

Program můžete otestovat příkazem: ./steg-decode du1-obrazek.ppm
Makefile

Zařiďte, aby příkaz „make“ bez parametrů vytvořil všechny spustitelné soubory pro domácí úkol 1. Při změně kteréhokoli souboru musí přeložit jen změněný soubor a závislosti. Pokud bude Makefile vypadat jako skript, odečtou se 3 body.

Pro příklad A jsou dvě varianty:

    primes: Používá makra
    primes-i: používá inline funkce

Pro příklad B Makefile vytvoří program steg-decode.

Dále musí Makefile podporovat příkaz „make run“, který všechny varianty nejen vytvoří, ale i spustí (i s „ulimit -s“).

Pokyny k odevzdání

    Úkoly je nutné zabalit programem zip takto:

    zip xaaaaa99.zip *.c *.h Makefile

    Jméno xaaaaa99 nahradíte vlastním. Zip neobsahuje adresáře. Každý si zkontroluje obsah ZIP archivu jeho rozbalením v prázdném adresáři a napsáním „make run“.
    Posílejte pouze nezbytně nutné soubory — ne *.EXE!
    Řešení se odevzdává elektronicky v IS VUT (velikost souboru je omezena).
    Hodnocení celkem max. 15 bodů, až 7 bodů za příklad A a až 8 bodů za příklad B a Makefile.
    Pokud úkol nebude odevzdán v termínu, bude za 0 bodů.
    Opsané úkoly budou hodnoceny 0 bodů pro všechny zúčastněné, a to bez výjimky (+bonus v podobě návštěvy u disciplinární komise).
