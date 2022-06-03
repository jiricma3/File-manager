Správce souborů
===============

Zadání z Progtestu
------------------

Program na správu souborů/adresářů (inspirace Midnight Commander).

<u>Implementujte následující funkcionalitu</u>:

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

<u>Takové příkazy jsou</u>:
    - <b>CREATE</b> - Vytvoření prázdného souboru.
    - <b>DELETE</b> - Smazání souboru.
    - <b>MOVE</b> - Přesunutí souboru do jiného adresáře. Adresář už musí existovat.
    - <b>COPY</b> - Překopírování obsahu souboru.
    - <b>LIST</b> - Vypsání obsahu aktuálního adresáře do terminálu.
    - <b>WRITE</b> - Zapsání textu do souboru.
    - <b>CURRENT</b> - Zobrazení aktuálního adresáře, kde se uživatel nachází.
    - <b>MEDIA</b> - Výpis informací o disku.
    - <b>CHANGE</b> - Změna aktuálního adresáře.
    - <b>PRINT</b> - Výpis obsahu souboru do terminálu v textové formě.
    - <b>HELP</b> - Výpis nápovědy, jak program používat a ovládat.
    - <b>END</b> - Bezpečné ukončení programu.

<u>Zároveň bude program podporovat sadu přepínačů</u>:
    - <b>CREATE</b> -<em>f</em> - Vytvoření prázdného souboru.
    - <b>CREATE</b> -<em>d</em> - Vytvoření prázdného adresáře.
    - <b>CREATE</b> -<em>l</em> - Vytvoření symbolického linku.
    - <b>COPY</b> -<em>r</em> - Kopírování souborů podle regulárního výrazu.
    - <b>MOVE</b> -<em>r</em> - Přesouvání souborů podle regulárního výrazu.
    - <b>DELETE</b> -<em>r</em> - Mazání souborů podle regulárního výrazu.
    - <b>PRINT</b> -<em>l</em> - Dlouhý výpis informací o souborech

<h2>Polymorfismus</h2>

Polymorfismus je využitý mezi třídami souborů a jejich metodami, nebo také mezi jednotlivými příkazy.
Existuje hlavní třída CFileType pro soubory, ze které dědí třídy všech souborů. Třída CFileType je abstraktní.
Další hlavní třídou je CCommand. Ta zaštiťuje všechny příkazy programu.

<u>Polymorfními metodami jsou</u>:
    - <b>createFile()</b> - Vytvoření souboru.
    - <b>copyFile()</b> - Kopírování souboru.
    - <b>moveFile()</b> - Přesunutí souboru.
    - <b>deleteFile()</b> - Smazání souboru.
    - <b>setName()</b> - Úprava názvu souboru v případě, že už soubor v cílovém adresáři existuje.
    - <b>doCom()</b> - Provedení žádaného příkazu.

