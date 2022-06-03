Správce souborů
===============

Zadání z Progtestu
------------------

Program na správu souborů/adresářů (inspirace Midnight Commander).

Implementujte následující funkcionalitu:

    1. vytváření a mazání souborů/adresářů/symbolických linků ...
    2. kopírování a přesun souborů/adresářů/symbolických linků ...
    3. možnost provádět předchozí operace nad množinou souborů definovaných regulárním výrazem
    4. navigace mezi jednotlivými adresáři
    5. uživatelské rozhraní: zobrazení adresářů nad kterými se pracuje a vizuální rozlišení souborů/adresářů/symbolických linků ...
    6. nepoužívejte funkci system, využijte místo toho systémové knihovny unistd.h, dirent.h, stat.h a další


Upřesnění zadání
----------------

Pracujeme se třemi druhy souborů. S klasickým souborem, adresářem a symbolickým linkem. Za další také pracujeme s celým úložištěm.
To znamená, že budeme vypisovat informace o aktuálním adresáři, ale i informace úložišti.
Soubory je možné libovolně kopírovat, přesouvat i mazat. Tyto operace je možné provádět i pomocí regulárních výrazů.
Pro práci se soubory je vyhotoveno vypisování jejich obsahu nebo zapisování textu do souboru.
Programem je možné měnit aktuální adresář a vypsat, kde se právě nacházíme. Existuje možnost program bezpečně ukončit.
Program nabízí nápovědu, jak program používat. Soubory jsou rozlišeny barevně.
Program se ovládá příkazy do terminálu.

Takové příkazy jsou:
    - CREATE - Vytvoření prázdného souboru.
    - DELETE - Smazání souboru.
    - MOVE - Přesunutí souboru do jiného adresáře. Adresář už musí existovat.
    - COPY - Překopírování obsahu souboru.
    - LIST - Vypsání obsahu aktuálního adresáře do terminálu.
    - WRITE - Zapsání textu do souboru.
    - CURRENT - Zobrazení aktuálního adresáře, kde se uživatel nachází.
    - MEDIA - Výpis informací o disku.
    - CHANGE - Změna aktuálního adresáře.
    - PRINT - Výpis obsahu souboru do terminálu v textové formě.
    - HELP - Výpis nápovědy, jak program používat a ovládat.
    - END - Bezpečné ukončení programu.

Zároveň bude program podporovat sadu přepínačů:
    - CREATE -f - Vytvoření prázdného souboru.
    - CREATE -d - Vytvoření prázdného adresáře.
    - CREATE -l - Vytvoření symbolického linku.
    - COPY -r Kopírování souborů podle regulárního výrazu.
    - MOVE -r Přesouvání souborů podle regulárního výrazu.
    - DELETE -r Mazání souborů podle regulárního výrazu.
    - PRINT -l - Dlouhý výpis informací o souborech

Polymorfismus je využitý mezi třídami souborů a jejich metodami, nebo také mezi jednotlivými příkazy.
Existuje hlavní třída CFileType pro soubory, ze které dědí třídy všech souborů. Třída CFileType je abstraktní.
Další hlavní třídou je CCommand. Ta zaštiťuje všechny příkazy programu.

Polymorfními metodami jsou:
    - createFile() - Vytvoření souboru.
    - copyFile() - Kopírování souboru.
    - moveFile() - Přesunutí souboru.
    - deleteFile() - Smazání souboru.
    - setName() - Úprava názvu souboru v případě, že už soubor v cílovém adresáři existuje.
    - doCom() - Provedení žádaného příkazu.

