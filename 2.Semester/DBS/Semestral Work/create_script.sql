-- odeberu pokud existuje funkce na oodebrání tabulek a sekvencí
DROP FUNCTION IF EXISTS remove_all();

-- vytvořím funkci která odebere tabulky a sekvence
-- chcete také umět psát PLSQL? Zapište si předmět BI-SQL ;-)
CREATE or replace FUNCTION remove_all() RETURNS void AS $$
DECLARE
    rec RECORD;
    cmd text;
BEGIN
    cmd := '';

    FOR rec IN SELECT
            'DROP SEQUENCE ' || quote_ident(n.nspname) || '.'
                || quote_ident(c.relname) || ' CASCADE;' AS name
        FROM
            pg_catalog.pg_class AS c
        LEFT JOIN
            pg_catalog.pg_namespace AS n
        ON
            n.oid = c.relnamespace
        WHERE
            relkind = 'S' AND
            n.nspname NOT IN ('pg_catalog', 'pg_toast') AND
            pg_catalog.pg_table_is_visible(c.oid)
    LOOP
        cmd := cmd || rec.name;
    END LOOP;

    FOR rec IN SELECT
            'DROP TABLE ' || quote_ident(n.nspname) || '.'
                || quote_ident(c.relname) || ' CASCADE;' AS name
        FROM
            pg_catalog.pg_class AS c
        LEFT JOIN
            pg_catalog.pg_namespace AS n
        ON
            n.oid = c.relnamespace WHERE relkind = 'r' AND
            n.nspname NOT IN ('pg_catalog', 'pg_toast') AND
            pg_catalog.pg_table_is_visible(c.oid)
    LOOP
        cmd := cmd || rec.name;
    END LOOP;

    EXECUTE cmd;
    RETURN;
END;
$$ LANGUAGE plpgsql;
-- zavolám funkci co odebere tabulky a sekvence - Mohl bych dropnout celé schéma a znovu jej vytvořit, použíjeme však PLSQL
select remove_all();

-- Remove conflicting tables
DROP TABLE IF EXISTS demon CASCADE;
DROP TABLE IF EXISTS dobrodruh CASCADE;
DROP TABLE IF EXISTS dungeon CASCADE;
DROP TABLE IF EXISTS mistnost CASCADE;
DROP TABLE IF EXISTS objednavka CASCADE;
DROP TABLE IF EXISTS ochrana CASCADE;
DROP TABLE IF EXISTS past CASCADE;
DROP TABLE IF EXISTS poklad CASCADE;
DROP TABLE IF EXISTS prekazka CASCADE;
DROP TABLE IF EXISTS prisera CASCADE;
DROP TABLE IF EXISTS sluzba CASCADE;
DROP TABLE IF EXISTS vyprava CASCADE;
DROP TABLE IF EXISTS dungeon_demon CASCADE;
DROP TABLE IF EXISTS objednavka_dungeon CASCADE;
DROP TABLE IF EXISTS ochrana_mistnost CASCADE;
DROP TABLE IF EXISTS prekazka_mistnost CASCADE;
DROP TABLE IF EXISTS prisera_prekazka CASCADE;
DROP TABLE IF EXISTS sluzba_prekazka CASCADE;
DROP TABLE IF EXISTS vyprava_mistnost CASCADE;
DROP TABLE IF EXISTS vyprava_dobrodruh CASCADE;
-- End of removing

CREATE TABLE demon (
    id_vlastnika SERIAL NOT NULL,
    hell_id VARCHAR(12) NOT NULL,
    jmeno VARCHAR(66) NOT NULL,
    vrstva_pekla VARCHAR(66) NOT NULL,
    adresa VARCHAR(66) NOT NULL,
    hellphone VARCHAR(12),
    hellmail VARCHAR(66)
);
ALTER TABLE demon ADD CONSTRAINT pk_demon PRIMARY KEY (id_vlastnika);

CREATE TABLE dobrodruh (
    id_dobrodruha SERIAL NOT NULL,
    jmeno VARCHAR(66) NOT NULL,
    class VARCHAR(66) NOT NULL,
    lvl INTEGER NOT NULL,
    rasa VARCHAR(66) NOT NULL,
    hodnota_duse DOUBLE PRECISION NOT NULL,
    stav VARCHAR(66) NOT NULL
);
ALTER TABLE dobrodruh ADD CONSTRAINT pk_dobrodruh PRIMARY KEY (id_dobrodruha);

CREATE TABLE dungeon (
    id_dungeonu SERIAL NOT NULL,
    nazev VARCHAR(66) NOT NULL,
    lvl INTEGER,
    sila DOUBLE PRECISION,
    hodnota DOUBLE PRECISION,
    pomer_sila_k_hodnote DOUBLE PRECISION
);
ALTER TABLE dungeon ADD CONSTRAINT pk_dungeon PRIMARY KEY (id_dungeonu);
ALTER TABLE dungeon ADD CONSTRAINT uc_dungeon_nazev UNIQUE (nazev);

CREATE TABLE mistnost (
    id_mistnosti SERIAL NOT NULL,
    id_dungeonu INTEGER NOT NULL,
    id_objednavky INTEGER,
    nazev VARCHAR(66) NOT NULL,
    hodnota_pokladu DOUBLE PRECISION,
    sila_ochrany DOUBLE PRECISION
);
ALTER TABLE mistnost ADD CONSTRAINT pk_mistnost PRIMARY KEY (id_mistnosti, id_dungeonu);

CREATE TABLE objednavka (
    id_objednavky SERIAL NOT NULL,
    datum DATE NOT NULL,
    domenove_jmeno VARCHAR(66) NOT NULL,
    typ VARCHAR(66) NOT NULL,
    cena DOUBLE PRECISION NOT NULL
);
ALTER TABLE objednavka ADD CONSTRAINT pk_objednavka PRIMARY KEY (id_objednavky);

CREATE TABLE ochrana (
    id_ochrany SERIAL NOT NULL,
    stav VARCHAR(66) NOT NULL,
    sila DOUBLE PRECISION NOT NULL,
    prezdivka VARCHAR(66),
    ochrana_od DATE,
    ochrana_do DATE
);
ALTER TABLE ochrana ADD CONSTRAINT pk_ochrana PRIMARY KEY (id_ochrany);

CREATE TABLE past (
    id_pasti SERIAL NOT NULL,
    id_objednavky INTEGER,
    id_ochrany INTEGER,
    nazev VARCHAR(66) NOT NULL,
    typ VARCHAR(66) NOT NULL,
    sila DOUBLE PRECISION NOT NULL,
    stav VARCHAR(66) NOT NULL
);
ALTER TABLE past ADD CONSTRAINT pk_past PRIMARY KEY (id_pasti);

CREATE TABLE poklad (
    id_pokladu SERIAL NOT NULL,
    id_mistnosti INTEGER,
    id_dungeonu INTEGER,
    id_dobrodruha INTEGER,
    id_objednavky INTEGER,
    nazev VARCHAR(66) NOT NULL,
    hodnota DOUBLE PRECISION NOT NULL,
    stav VARCHAR(66) NOT NULL
);
ALTER TABLE poklad ADD CONSTRAINT pk_poklad PRIMARY KEY (id_pokladu);
ALTER TABLE poklad ADD CONSTRAINT c_fk_poklad_mistnost CHECK ((id_mistnosti IS NOT NULL AND id_dungeonu IS NOT NULL) OR (id_mistnosti IS NULL AND id_dungeonu IS NULL));

CREATE TABLE prekazka (
    id_prekazky SERIAL NOT NULL,
    id_dungeonu INTEGER,
    popis VARCHAR(66) NOT NULL,
    stav VARCHAR(66) NOT NULL,
    datum DATE NOT NULL,
    typ VARCHAR(66)
);
ALTER TABLE prekazka ADD CONSTRAINT pk_prekazka PRIMARY KEY (id_prekazky);

CREATE TABLE prisera (
    id_prisery SERIAL NOT NULL,
    id_objednavky INTEGER,
    id_ochrany INTEGER,
    prisera_id_prisery INTEGER,
    jmeno VARCHAR(66) NOT NULL,
    typ VARCHAR(66) NOT NULL,
    sila DOUBLE PRECISION NOT NULL,
    stav VARCHAR(66) NOT NULL
);
ALTER TABLE prisera ADD CONSTRAINT pk_prisera PRIMARY KEY (id_prisery);

CREATE TABLE sluzba (
    id_sluzby SERIAL NOT NULL,
    id_objednavky INTEGER,
    popis VARCHAR(66) NOT NULL,
    sluzba_od DATE,
    sluzba_do DATE
);
ALTER TABLE sluzba ADD CONSTRAINT pk_sluzba PRIMARY KEY (id_sluzby);

CREATE TABLE vyprava (
    id_vypravy SERIAL NOT NULL,
    datum_registrace DATE NOT NULL,
    stav VARCHAR(66) NOT NULL,
    sila DOUBLE PRECISION NOT NULL,
    prezdivka VARCHAR(66),
    ztraty_dusi DOUBLE PRECISION,
    zisk_dusi DOUBLE PRECISION,
    vyprava_od DATE,
    vyprava_do DATE
);
ALTER TABLE vyprava ADD CONSTRAINT pk_vyprava PRIMARY KEY (id_vypravy);

CREATE TABLE dungeon_demon (
    id_dungeonu INTEGER NOT NULL,
    id_vlastnika INTEGER NOT NULL
);
ALTER TABLE dungeon_demon ADD CONSTRAINT pk_dungeon_demon PRIMARY KEY (id_dungeonu, id_vlastnika);

CREATE TABLE objednavka_dungeon (
    id_objednavky INTEGER NOT NULL,
    id_dungeonu INTEGER NOT NULL
);
ALTER TABLE objednavka_dungeon ADD CONSTRAINT pk_objednavka_dungeon PRIMARY KEY (id_objednavky, id_dungeonu);

CREATE TABLE ochrana_mistnost (
    id_ochrany INTEGER NOT NULL,
    id_mistnosti INTEGER NOT NULL,
    id_dungeonu INTEGER NOT NULL
);
ALTER TABLE ochrana_mistnost ADD CONSTRAINT pk_ochrana_mistnost PRIMARY KEY (id_ochrany, id_mistnosti, id_dungeonu);

CREATE TABLE prekazka_mistnost (
    id_prekazky INTEGER NOT NULL,
    id_mistnosti INTEGER NOT NULL,
    id_dungeonu INTEGER NOT NULL
);
ALTER TABLE prekazka_mistnost ADD CONSTRAINT pk_prekazka_mistnost PRIMARY KEY (id_prekazky, id_mistnosti, id_dungeonu);

CREATE TABLE prisera_prekazka (
    id_prisery INTEGER NOT NULL,
    id_prekazky INTEGER NOT NULL
);
ALTER TABLE prisera_prekazka ADD CONSTRAINT pk_prisera_prekazka PRIMARY KEY (id_prisery, id_prekazky);

CREATE TABLE sluzba_prekazka (
    id_sluzby INTEGER NOT NULL,
    id_prekazky INTEGER NOT NULL
);
ALTER TABLE sluzba_prekazka ADD CONSTRAINT pk_sluzba_prekazka PRIMARY KEY (id_sluzby, id_prekazky);

CREATE TABLE vyprava_mistnost (
    id_vypravy INTEGER NOT NULL,
    id_mistnosti INTEGER NOT NULL,
    id_dungeonu INTEGER NOT NULL
);
ALTER TABLE vyprava_mistnost ADD CONSTRAINT pk_vyprava_mistnost PRIMARY KEY (id_vypravy, id_mistnosti, id_dungeonu);

CREATE TABLE vyprava_dobrodruh (
    id_vypravy INTEGER NOT NULL,
    id_dobrodruha INTEGER NOT NULL
);
ALTER TABLE vyprava_dobrodruh ADD CONSTRAINT pk_vyprava_dobrodruh PRIMARY KEY (id_vypravy, id_dobrodruha);

ALTER TABLE mistnost ADD CONSTRAINT fk_mistnost_dungeon FOREIGN KEY (id_dungeonu) REFERENCES dungeon (id_dungeonu) ON DELETE CASCADE;
ALTER TABLE mistnost ADD CONSTRAINT fk_mistnost_objednavka FOREIGN KEY (id_objednavky) REFERENCES objednavka (id_objednavky) ON DELETE CASCADE;

ALTER TABLE past ADD CONSTRAINT fk_past_objednavka FOREIGN KEY (id_objednavky) REFERENCES objednavka (id_objednavky) ON DELETE CASCADE;
ALTER TABLE past ADD CONSTRAINT fk_past_ochrana FOREIGN KEY (id_ochrany) REFERENCES ochrana (id_ochrany) ON DELETE CASCADE;

ALTER TABLE poklad ADD CONSTRAINT fk_poklad_mistnost FOREIGN KEY (id_mistnosti, id_dungeonu) REFERENCES mistnost (id_mistnosti, id_dungeonu) ON DELETE CASCADE;
ALTER TABLE poklad ADD CONSTRAINT fk_poklad_dobrodruh FOREIGN KEY (id_dobrodruha) REFERENCES dobrodruh (id_dobrodruha) ON DELETE CASCADE;
ALTER TABLE poklad ADD CONSTRAINT fk_poklad_objednavka FOREIGN KEY (id_objednavky) REFERENCES objednavka (id_objednavky) ON DELETE CASCADE;

ALTER TABLE prekazka ADD CONSTRAINT fk_prekazka_dungeon FOREIGN KEY (id_dungeonu) REFERENCES dungeon (id_dungeonu) ON DELETE CASCADE;

ALTER TABLE prisera ADD CONSTRAINT fk_prisera_objednavka FOREIGN KEY (id_objednavky) REFERENCES objednavka (id_objednavky) ON DELETE CASCADE;
ALTER TABLE prisera ADD CONSTRAINT fk_prisera_ochrana FOREIGN KEY (id_ochrany) REFERENCES ochrana (id_ochrany) ON DELETE CASCADE;
ALTER TABLE prisera ADD CONSTRAINT fk_prisera_prisera FOREIGN KEY (prisera_id_prisery) REFERENCES prisera (id_prisery) ON DELETE CASCADE;

ALTER TABLE sluzba ADD CONSTRAINT fk_sluzba_objednavka FOREIGN KEY (id_objednavky) REFERENCES objednavka (id_objednavky) ON DELETE CASCADE;

ALTER TABLE dungeon_demon ADD CONSTRAINT fk_dungeon_demon_dungeon FOREIGN KEY (id_dungeonu) REFERENCES dungeon (id_dungeonu) ON DELETE CASCADE;
ALTER TABLE dungeon_demon ADD CONSTRAINT fk_dungeon_demon_demon FOREIGN KEY (id_vlastnika) REFERENCES demon (id_vlastnika) ON DELETE CASCADE;

ALTER TABLE objednavka_dungeon ADD CONSTRAINT fk_objednavka_dungeon_objednavk FOREIGN KEY (id_objednavky) REFERENCES objednavka (id_objednavky) ON DELETE CASCADE;
ALTER TABLE objednavka_dungeon ADD CONSTRAINT fk_objednavka_dungeon_dungeon FOREIGN KEY (id_dungeonu) REFERENCES dungeon (id_dungeonu) ON DELETE CASCADE;

ALTER TABLE ochrana_mistnost ADD CONSTRAINT fk_ochrana_mistnost_ochrana FOREIGN KEY (id_ochrany) REFERENCES ochrana (id_ochrany) ON DELETE CASCADE;
ALTER TABLE ochrana_mistnost ADD CONSTRAINT fk_ochrana_mistnost_mistnost FOREIGN KEY (id_mistnosti, id_dungeonu) REFERENCES mistnost (id_mistnosti, id_dungeonu) ON DELETE CASCADE;

ALTER TABLE prekazka_mistnost ADD CONSTRAINT fk_prekazka_mistnost_prekazka FOREIGN KEY (id_prekazky) REFERENCES prekazka (id_prekazky) ON DELETE CASCADE;
ALTER TABLE prekazka_mistnost ADD CONSTRAINT fk_prekazka_mistnost_mistnost FOREIGN KEY (id_mistnosti, id_dungeonu) REFERENCES mistnost (id_mistnosti, id_dungeonu) ON DELETE CASCADE;

ALTER TABLE prisera_prekazka ADD CONSTRAINT fk_prisera_prekazka_prisera FOREIGN KEY (id_prisery) REFERENCES prisera (id_prisery) ON DELETE CASCADE;
ALTER TABLE prisera_prekazka ADD CONSTRAINT fk_prisera_prekazka_prekazka FOREIGN KEY (id_prekazky) REFERENCES prekazka (id_prekazky) ON DELETE CASCADE;

ALTER TABLE sluzba_prekazka ADD CONSTRAINT fk_sluzba_prekazka_sluzba FOREIGN KEY (id_sluzby) REFERENCES sluzba (id_sluzby) ON DELETE CASCADE;
ALTER TABLE sluzba_prekazka ADD CONSTRAINT fk_sluzba_prekazka_prekazka FOREIGN KEY (id_prekazky) REFERENCES prekazka (id_prekazky) ON DELETE CASCADE;

ALTER TABLE vyprava_mistnost ADD CONSTRAINT fk_vyprava_mistnost_vyprava FOREIGN KEY (id_vypravy) REFERENCES vyprava (id_vypravy) ON DELETE CASCADE;
ALTER TABLE vyprava_mistnost ADD CONSTRAINT fk_vyprava_mistnost_mistnost FOREIGN KEY (id_mistnosti, id_dungeonu) REFERENCES mistnost (id_mistnosti, id_dungeonu) ON DELETE CASCADE;

ALTER TABLE vyprava_dobrodruh ADD CONSTRAINT fk_vyprava_dobrodruh_vyprava FOREIGN KEY (id_vypravy) REFERENCES vyprava (id_vypravy) ON DELETE CASCADE;
ALTER TABLE vyprava_dobrodruh ADD CONSTRAINT fk_vyprava_dobrodruh_dobrodruh FOREIGN KEY (id_dobrodruha) REFERENCES dobrodruh (id_dobrodruha) ON DELETE CASCADE;

ALTER TABLE poklad ADD CONSTRAINT xc_poklad_id_mistnosti_id_dobro CHECK ((id_mistnosti IS NOT NULL AND id_dobrodruha IS NULL) OR (id_mistnosti IS NULL AND id_dobrodruha IS NOT NULL));
