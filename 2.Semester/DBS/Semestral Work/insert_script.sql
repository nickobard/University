-- DEMON --
INSERT INTO demon (id_vlastnika, hell_id, jmeno, vrstva_pekla, adresa, hellphone, hellmail) VALUES (1, '369312666169', 'Asmodeyka', 'Limbo', 'Hadash-Dur, Ogha-nur 69', '666318216636', 'x_Asmodeyka@chaos.hell');
select setval(pg_get_serial_sequence('demon','id_vlastnika'),1);

-- DOBRODRUH --
INSERT INTO public.dobrodruh (id_dobrodruha, jmeno, class, lvl, rasa, hodnota_duse, stav) VALUES (10, 'Gully Mucky', 'Priest', 3, 'gnome', 266, 'Yet alive');
INSERT INTO public.dobrodruh (id_dobrodruha, jmeno, class, lvl, rasa, hodnota_duse, stav) VALUES (12, 'Ushu', 'Fighter', 2, 'dragonborn', 166, 'Yet alive');
INSERT INTO public.dobrodruh (id_dobrodruha, jmeno, class, lvl, rasa, hodnota_duse, stav) VALUES (14, 'Chuck Norris', 'error', 9999999, 'error', 9999999, 'We are yet alive');
INSERT INTO public.dobrodruh (id_dobrodruha, jmeno, class, lvl, rasa, hodnota_duse, stav) VALUES (9, 'Garagh Gur', 'Monk', 1, 'dwarf', 66, 'Dead');
INSERT INTO public.dobrodruh (id_dobrodruha, jmeno, class, lvl, rasa, hodnota_duse, stav) VALUES (7, 'Garagh Mur', 'Sourcerer', 1, 'dwarf', 66, 'Dead');
INSERT INTO public.dobrodruh (id_dobrodruha, jmeno, class, lvl, rasa, hodnota_duse, stav) VALUES (8, 'Garagh Pur', 'Fighter', 1, 'dwarf', 66, 'Dead');
INSERT INTO public.dobrodruh (id_dobrodruha, jmeno, class, lvl, rasa, hodnota_duse, stav) VALUES (1, 'Borris You-Miss', 'Rogue', 4, 'halfling', 466, 'Yet alive');
INSERT INTO public.dobrodruh (id_dobrodruha, jmeno, class, lvl, rasa, hodnota_duse, stav) VALUES (3, 'Azor', 'Barbarian', 4, 'elf', 466, 'Dead');
INSERT INTO public.dobrodruh (id_dobrodruha, jmeno, class, lvl, rasa, hodnota_duse, stav) VALUES (11, 'Fa Que', 'Monk', 2, 'human', 166, 'Dead');
INSERT INTO public.dobrodruh (id_dobrodruha, jmeno, class, lvl, rasa, hodnota_duse, stav) VALUES (4, 'Myspell Zgreat', 'Mage', 5, 'human', 866, 'Dead');
INSERT INTO public.dobrodruh (id_dobrodruha, jmeno, class, lvl, rasa, hodnota_duse, stav) VALUES (13, 'Kerlie Deaf', 'Bard', 2, 'human', 166, 'Dead');
INSERT INTO public.dobrodruh (id_dobrodruha, jmeno, class, lvl, rasa, hodnota_duse, stav) VALUES (6, 'Tendrial', 'Priest', 2, 'halfelf', 166, 'Yet alive');
INSERT INTO public.dobrodruh (id_dobrodruha, jmeno, class, lvl, rasa, hodnota_duse, stav) VALUES (5, 'Rock', 'Barbarian', 3, 'halfork', 266, 'Yet alive');
INSERT INTO public.dobrodruh (id_dobrodruha, jmeno, class, lvl, rasa, hodnota_duse, stav) VALUES (15, 'Grognak Barbar', 'Fighter', 3, 'halfork', 266, 'Dead');
INSERT INTO public.dobrodruh (id_dobrodruha, jmeno, class, lvl, rasa, hodnota_duse, stav) VALUES (16, 'Bully', 'Fighter', 3, 'halfelf', 266, 'Dead');
INSERT INTO public.dobrodruh (id_dobrodruha, jmeno, class, lvl, rasa, hodnota_duse, stav) VALUES (18, 'Agron', 'Fighter', 3, 'halfork', 266, 'Dead');
INSERT INTO public.dobrodruh (id_dobrodruha, jmeno, class, lvl, rasa, hodnota_duse, stav) VALUES (17, 'Zorro Firefist', 'Fighter', 3, 'tiefling', 15, 'Dead');
select setval(pg_get_serial_sequence('dobrodruh','id_dobrodruha'),18);


-- DUNGEON --
INSERT INTO dungeon (id_dungeonu, nazev, lvl, sila, hodnota, pomer_sila_k_hodnote) VALUES (1, 'Echo''s Wave Cave', 5, null, null, null);
select setval(pg_get_serial_sequence('dungeon','id_dungeonu'),1);

-- DEMON - DUNGEON --
INSERT INTO dungeon_demon (id_dungeonu, id_vlastnika) VALUES (1, 1);

-- OBJEDNAVKY --
INSERT INTO objednavka (id_objednavky, datum, domenove_jmeno, typ, cena) VALUES (1, '0234-01-23', 'fireroom.hell', 'room', 66);
INSERT INTO objednavka (id_objednavky, datum, domenove_jmeno, typ, cena) VALUES (2, '0234-05-21', 'fireroom.hell', 'room', 69);
INSERT INTO objednavka (id_objednavky, datum, domenove_jmeno, typ, cena) VALUES (3, '0235-06-02', 'fireroom.hell', 'room', 96);
INSERT INTO objednavka (id_objednavky, datum, domenove_jmeno, typ, cena) VALUES (4, '0237-04-30', 'fireroom.hell', 'room', 166);
INSERT INTO objednavka (id_objednavky, datum, domenove_jmeno, typ, cena) VALUES (6, '0234-02-03', 'deadheroes.dead', 'monsters', 69);
INSERT INTO objednavka (id_objednavky, datum, domenove_jmeno, typ, cena) VALUES (7, '0234-02-03', 'trapped.dead', 'traps', 36);
INSERT INTO objednavka (id_objednavky, datum, domenove_jmeno, typ, cena) VALUES (8, '0234-03-03', 'goldenfever.chaos', 'treasures', 96);
INSERT INTO objednavka (id_objednavky, datum, domenove_jmeno, typ, cena) VALUES (9, '0235-02-13', 'pizzatime.lim', 'pizza', 1);
INSERT INTO objednavka (id_objednavky, datum, domenove_jmeno, typ, cena) VALUES (10, '0235-03-13', 'pizzatime.lim', 'pizza', 1);
INSERT INTO objednavka (id_objednavky, datum, domenove_jmeno, typ, cena) VALUES (11, '0235-04-13', 'pizzatime.lim', 'pizza', 1);
INSERT INTO objednavka (id_objednavky, datum, domenove_jmeno, typ, cena) VALUES (12, '0235-03-13', 'pizzatime.lim', 'Cola', 1);
INSERT INTO objednavka (id_objednavky, datum, domenove_jmeno, typ, cena) VALUES (13, '0235-04-13', 'pizzatime.lim', 'Cola', 1);
INSERT INTO objednavka (id_objednavky, datum, domenove_jmeno, typ, cena) VALUES (14, '0235-02-13', 'pizzatime.lim', 'Cola', 1);
INSERT INTO objednavka (id_objednavky, datum, domenove_jmeno, typ, cena) VALUES (18, '0235-04-13', 'yourdungeon.hell', 'Statues', 6);
INSERT INTO objednavka (id_objednavky, datum, domenove_jmeno, typ, cena) VALUES (19, '0235-02-13', 'yourdungeon.hell', 'Creepy furniture', 9);
INSERT INTO objednavka (id_objednavky, datum, domenove_jmeno, typ, cena) VALUES (17, '0235-03-13', 'pizzatime.lim', 'Deliverer''s meat', 0);
INSERT INTO objednavka (id_objednavky, datum, domenove_jmeno, typ, cena) VALUES (15, '0235-02-13', 'pizzatime.lim', 'Deliverer''s meat', 0);
INSERT INTO objednavka (id_objednavky, datum, domenove_jmeno, typ, cena) VALUES (16, '0235-04-13', 'pizzatime.lim', 'Deliverer''s meat', 0);
INSERT INTO objednavka (id_objednavky, datum, domenove_jmeno, typ, cena) VALUES (20, '0235-04-29', 'deadheroes.dead', 'monsters', 266);
INSERT INTO objednavka (id_objednavky, datum, domenove_jmeno, typ, cena) VALUES (21, '0235-01-08', 'goldenfever.chaos', 'treasures', 366);
INSERT INTO objednavka (id_objednavky, datum, domenove_jmeno, typ, cena) VALUES (22, '0235-03-06', 'goldenfever.chaos', 'treasures', 366);
INSERT INTO objednavka (id_objednavky, datum, domenove_jmeno, typ, cena) VALUES (23, '0235-05-31', 'goldenfever.chaos', 'treasures', 666);
INSERT INTO objednavka (id_objednavky, datum, domenove_jmeno, typ, cena) VALUES (24, '0235-04-13', 'deadheroes.dead', 'monsters', 166);
INSERT INTO objednavka (id_objednavky, datum, domenove_jmeno, typ, cena) VALUES (25, '0235-01-08', 'deadheroes.dead', 'monsters', 1666);
INSERT INTO objednavka (id_objednavky, datum, domenove_jmeno, typ, cena) VALUES (26, '0235-03-13', 'hellymoney.chaos', 'marketing', 66);
INSERT INTO objednavka (id_objednavky, datum, domenove_jmeno, typ, cena) VALUES (27, '0235-04-13', 'hellymoney.chaos', 'marketing', 66);
INSERT INTO objednavka (id_objednavky, datum, domenove_jmeno, typ, cena) VALUES (28, '0235-04-13', 'hellymoney.chaos', 'marketing', 66);

select setval(pg_get_serial_sequence('objednavka','id_objednavky'),28);

-- OBJEDNAVKY - DUNGEON --
INSERT INTO objednavka_dungeon (id_objednavky, id_dungeonu) VALUES (1, 1);
INSERT INTO objednavka_dungeon (id_objednavky, id_dungeonu) VALUES (2, 1);
INSERT INTO objednavka_dungeon (id_objednavky, id_dungeonu) VALUES (3, 1);
INSERT INTO objednavka_dungeon (id_objednavky, id_dungeonu) VALUES (4, 1);
INSERT INTO objednavka_dungeon (id_objednavky, id_dungeonu) VALUES (7, 1);
INSERT INTO objednavka_dungeon (id_objednavky, id_dungeonu) VALUES (8, 1);
INSERT INTO objednavka_dungeon (id_objednavky, id_dungeonu) VALUES (9, 1);
INSERT INTO objednavka_dungeon (id_objednavky, id_dungeonu) VALUES (10, 1);
INSERT INTO objednavka_dungeon (id_objednavky, id_dungeonu) VALUES (11, 1);
INSERT INTO objednavka_dungeon (id_objednavky, id_dungeonu) VALUES (12, 1);
INSERT INTO objednavka_dungeon (id_objednavky, id_dungeonu) VALUES (13, 1);
INSERT INTO objednavka_dungeon (id_objednavky, id_dungeonu) VALUES (14, 1);
INSERT INTO objednavka_dungeon (id_objednavky, id_dungeonu) VALUES (15, 1);
INSERT INTO objednavka_dungeon (id_objednavky, id_dungeonu) VALUES (16, 1);
INSERT INTO objednavka_dungeon (id_objednavky, id_dungeonu) VALUES (17, 1);
INSERT INTO objednavka_dungeon (id_objednavky, id_dungeonu) VALUES (18, 1);
INSERT INTO objednavka_dungeon (id_objednavky, id_dungeonu) VALUES (19, 1);
INSERT INTO objednavka_dungeon (id_objednavky, id_dungeonu) VALUES (20, 1);
INSERT INTO objednavka_dungeon (id_objednavky, id_dungeonu) VALUES (21, 1);
INSERT INTO objednavka_dungeon (id_objednavky, id_dungeonu) VALUES (22, 1);
INSERT INTO objednavka_dungeon (id_objednavky, id_dungeonu) VALUES (23, 1);
INSERT INTO objednavka_dungeon (id_objednavky, id_dungeonu) VALUES (25, 1);
INSERT INTO objednavka_dungeon (id_objednavky, id_dungeonu) VALUES (24, 1);
INSERT INTO objednavka_dungeon (id_objednavky, id_dungeonu) VALUES (26, 1);
INSERT INTO objednavka_dungeon (id_objednavky, id_dungeonu) VALUES (28, 1);




-- MISTNOST --
INSERT INTO mistnost (id_mistnosti, id_dungeonu, id_objednavky, nazev, hodnota_pokladu, sila_ochrany) VALUES (3, 1, null, 'Dwarf Mine Tunnels', null, null);
INSERT INTO mistnost (id_mistnosti, id_dungeonu, id_objednavky, nazev, hodnota_pokladu, sila_ochrany) VALUES (1, 1, null, 'Cave Entrance', null, null);
INSERT INTO mistnost (id_mistnosti, id_dungeonu, id_objednavky, nazev, hodnota_pokladu, sila_ochrany) VALUES (4, 1, null, 'Old Entrance', null, null);
INSERT INTO mistnost (id_mistnosti, id_dungeonu, id_objednavky, nazev, hodnota_pokladu, sila_ochrany) VALUES (6, 1, 1, 'Old Guardroom', null, null);
INSERT INTO mistnost (id_mistnosti, id_dungeonu, id_objednavky, nazev, hodnota_pokladu, sila_ochrany) VALUES (7, 1, 1, 'Assayers''s Office', null, null);
INSERT INTO mistnost (id_mistnosti, id_dungeonu, id_objednavky, nazev, hodnota_pokladu, sila_ochrany) VALUES (8, 1, 2, 'South Barracks', null, null);
INSERT INTO mistnost (id_mistnosti, id_dungeonu, id_objednavky, nazev, hodnota_pokladu, sila_ochrany) VALUES (9, 1, 2, 'Ruined Storeroom', null, null);
INSERT INTO mistnost (id_mistnosti, id_dungeonu, id_objednavky, nazev, hodnota_pokladu, sila_ochrany) VALUES (12, 1, 4, 'Dark Pool', null, null);
INSERT INTO mistnost (id_mistnosti, id_dungeonu, id_objednavky, nazev, hodnota_pokladu, sila_ochrany) VALUES (13, 1, 4, 'North Barracks', null, null);
INSERT INTO mistnost (id_mistnosti, id_dungeonu, id_objednavky, nazev, hodnota_pokladu, sila_ochrany) VALUES (14, 1, 4, 'Starry Cavern', null, null);
INSERT INTO mistnost (id_mistnosti, id_dungeonu, id_objednavky, nazev, hodnota_pokladu, sila_ochrany) VALUES (10, 1, 3, 'Fungi Cavern', null, null);
INSERT INTO mistnost (id_mistnosti, id_dungeonu, id_objednavky, nazev, hodnota_pokladu, sila_ochrany) VALUES (11, 1, 4, 'Great Cavern', null, null);
select setval(pg_get_serial_sequence('mistnost','id_mistnosti'),11);

-- OCHRANA --
INSERT INTO ochrana (id_ochrany, stav, sila, prezdivka, ochrana_od, ochrana_do) VALUES (1, 'active', 2.5, 'skeletons', null, null);
INSERT INTO ochrana (id_ochrany, stav, sila, prezdivka, ochrana_od, ochrana_do) VALUES (10, 'active', 1, 'slimes', null, null);
INSERT INTO ochrana (id_ochrany, stav, sila, prezdivka, ochrana_od, ochrana_do) VALUES (11, 'active', 1, 'suckers', null, null);
INSERT INTO ochrana (id_ochrany, stav, sila, prezdivka, ochrana_od, ochrana_do) VALUES (12, 'active', 0.75, 'bear traps', null, null);
INSERT INTO ochrana (id_ochrany, stav, sila, prezdivka, ochrana_od, ochrana_do) VALUES (13, 'active', 8, 'ghoul squad', null, null);
INSERT INTO ochrana (id_ochrany, stav, sila, prezdivka, ochrana_od, ochrana_do) VALUES (14, 'active', 1.5, 'mushrooms threat', null, null);
INSERT INTO ochrana (id_ochrany, stav, sila, prezdivka, ochrana_od, ochrana_do) VALUES (15, 'pretending dead', 2.5, 'zombies', null, null);
INSERT INTO ochrana (id_ochrany, stav, sila, prezdivka, ochrana_od, ochrana_do) VALUES (16, 'active', 4, 'fire skull', null, null);
INSERT INTO ochrana (id_ochrany, stav, sila, prezdivka, ochrana_od, ochrana_do) VALUES (17, 'active', 6, 'sharks', null, null);
select setval(pg_get_serial_sequence('ochrana','id_ochrany'),17);

-- OCHRANA - MISTNOST --
INSERT INTO ochrana_mistnost (id_ochrany, id_mistnosti, id_dungeonu) VALUES (1, 4, 1);
INSERT INTO ochrana_mistnost (id_ochrany, id_mistnosti, id_dungeonu) VALUES (1, 7, 1);
INSERT INTO ochrana_mistnost (id_ochrany, id_mistnosti, id_dungeonu) VALUES (10, 3, 1);
INSERT INTO ochrana_mistnost (id_ochrany, id_mistnosti, id_dungeonu) VALUES (11, 1, 1);
INSERT INTO ochrana_mistnost (id_ochrany, id_mistnosti, id_dungeonu) VALUES (11, 3, 1);
INSERT INTO ochrana_mistnost (id_ochrany, id_mistnosti, id_dungeonu) VALUES (12, 1, 1);
INSERT INTO ochrana_mistnost (id_ochrany, id_mistnosti, id_dungeonu) VALUES (13, 8, 1);
INSERT INTO ochrana_mistnost (id_ochrany, id_mistnosti, id_dungeonu) VALUES (14, 10, 1);
INSERT INTO ochrana_mistnost (id_ochrany, id_mistnosti, id_dungeonu) VALUES (15, 13, 1);
INSERT INTO ochrana_mistnost (id_ochrany, id_mistnosti, id_dungeonu) VALUES (16, 13, 1);
INSERT INTO ochrana_mistnost (id_ochrany, id_mistnosti, id_dungeonu) VALUES (15, 11, 1);
INSERT INTO ochrana_mistnost (id_ochrany, id_mistnosti, id_dungeonu) VALUES (17, 12, 1);


-- PAST --
INSERT INTO past (id_pasti, id_objednavky, id_ochrany, nazev, typ, sila, stav) VALUES (2, null, 12, 'Bear trap', 'steel trap', 0.25, 'active');
INSERT INTO past (id_pasti, id_objednavky, id_ochrany, nazev, typ, sila, stav) VALUES (5, 7, 14, 'Poison Mushroom', 'poison trap', 0.5, 'active');
INSERT INTO past (id_pasti, id_objednavky, id_ochrany, nazev, typ, sila, stav) VALUES (4, 7, 14, 'Poison Mushroom', 'poison trap', 0.5, 'active');
INSERT INTO past (id_pasti, id_objednavky, id_ochrany, nazev, typ, sila, stav) VALUES (6, 7, 14, 'Poison Mushroom', 'poison trap', 0.5, 'active');
INSERT INTO past (id_pasti, id_objednavky, id_ochrany, nazev, typ, sila, stav) VALUES (1, null, 12, 'Bear trap', 'steel trap', 0.25, 'active');
INSERT INTO past (id_pasti, id_objednavky, id_ochrany, nazev, typ, sila, stav) VALUES (3, null, 12, 'Bear trap', 'steel trap', 0.25, 'active');
INSERT INTO past (id_pasti, id_objednavky, id_ochrany, nazev, typ, sila, stav) VALUES (9, null, null, 'Bear trap', 'steel trap', 0.25, 'repairs');
INSERT INTO past (id_pasti, id_objednavky, id_ochrany, nazev, typ, sila, stav) VALUES (8, null, null, 'Bear trap', 'steel trap', 0.25, 'repairs');
INSERT INTO past (id_pasti, id_objednavky, id_ochrany, nazev, typ, sila, stav) VALUES (7, null, null, 'Bear trap', 'steel trap', 0.25, 'repairs');
select setval(pg_get_serial_sequence('past','id_pasti'),9);

-- POKLAD --
INSERT INTO poklad (id_pokladu, id_mistnosti, id_dungeonu, id_dobrodruha, id_objednavky, nazev, hodnota, stav) VALUES (1, 4, 1, null, null, 'Golden ring', 6, 'In dungeon');
INSERT INTO poklad (id_pokladu, id_mistnosti, id_dungeonu, id_dobrodruha, id_objednavky, nazev, hodnota, stav) VALUES (3, 3, 1, null, null, 'Golden ore', 2, 'In dungeon');
INSERT INTO poklad (id_pokladu, id_mistnosti, id_dungeonu, id_dobrodruha, id_objednavky, nazev, hodnota, stav) VALUES (7, 1, 1, null, null, 'Buried chest', 24, 'In dungeon');
INSERT INTO poklad (id_pokladu, id_mistnosti, id_dungeonu, id_dobrodruha, id_objednavky, nazev, hodnota, stav) VALUES (8, 4, 1, null, null, 'Locked chest', 24, 'In dungeon');
INSERT INTO poklad (id_pokladu, id_mistnosti, id_dungeonu, id_dobrodruha, id_objednavky, nazev, hodnota, stav) VALUES (11, 10, 1, null, 8, 'Chest', 24, 'In dungeon');
INSERT INTO poklad (id_pokladu, id_mistnosti, id_dungeonu, id_dobrodruha, id_objednavky, nazev, hodnota, stav) VALUES (12, 8, 1, null, 8, 'Golden ring', 6, 'In dungeon');
INSERT INTO poklad (id_pokladu, id_mistnosti, id_dungeonu, id_dobrodruha, id_objednavky, nazev, hodnota, stav) VALUES (17, 14, 1, null, 21, 'Chest of gold', 86, 'In dungeon');
INSERT INTO poklad (id_pokladu, id_mistnosti, id_dungeonu, id_dobrodruha, id_objednavky, nazev, hodnota, stav) VALUES (18, 14, 1, null, 21, 'Chest of gold', 86, 'In dungeon');
INSERT INTO poklad (id_pokladu, id_mistnosti, id_dungeonu, id_dobrodruha, id_objednavky, nazev, hodnota, stav) VALUES (20, 14, 1, null, 21, 'Chest of gold', 86, 'In dungeon');
INSERT INTO poklad (id_pokladu, id_mistnosti, id_dungeonu, id_dobrodruha, id_objednavky, nazev, hodnota, stav) VALUES (21, 11, 1, null, 21, 'Precious stone', 12, 'In dungeon');
INSERT INTO poklad (id_pokladu, id_mistnosti, id_dungeonu, id_dobrodruha, id_objednavky, nazev, hodnota, stav) VALUES (23, 11, 1, null, 21, 'Precious stone', 12, 'In dungeon');
INSERT INTO poklad (id_pokladu, id_mistnosti, id_dungeonu, id_dobrodruha, id_objednavky, nazev, hodnota, stav) VALUES (27, 12, 1, null, 21, 'Adamantium Eggs', 166, 'Deliberately hidden');
INSERT INTO poklad (id_pokladu, id_mistnosti, id_dungeonu, id_dobrodruha, id_objednavky, nazev, hodnota, stav) VALUES (6, null, null, 1, null, 'Golden ore', 2, 'Stolen');
INSERT INTO poklad (id_pokladu, id_mistnosti, id_dungeonu, id_dobrodruha, id_objednavky, nazev, hodnota, stav) VALUES (4, null, null, 1, null, 'Golden ore', 2, 'Stolen');
INSERT INTO poklad (id_pokladu, id_mistnosti, id_dungeonu, id_dobrodruha, id_objednavky, nazev, hodnota, stav) VALUES (5, null, null, 1, null, 'Golden ore', 2, 'Stolen');
INSERT INTO poklad (id_pokladu, id_mistnosti, id_dungeonu, id_dobrodruha, id_objednavky, nazev, hodnota, stav) VALUES (22, null, null, 10, 21, 'Precious stone', 12, 'Stolen');
INSERT INTO poklad (id_pokladu, id_mistnosti, id_dungeonu, id_dobrodruha, id_objednavky, nazev, hodnota, stav) VALUES (16, 14, 1, null, 23, 'Scroll of Progtest Source Code', 666, 'In dungeon');
INSERT INTO poklad (id_pokladu, id_mistnosti, id_dungeonu, id_dobrodruha, id_objednavky, nazev, hodnota, stav) VALUES (19, null, null, 12, 21, 'Chest of gold', 86, 'Stolen');
INSERT INTO poklad (id_pokladu, id_mistnosti, id_dungeonu, id_dobrodruha, id_objednavky, nazev, hodnota, stav) VALUES (24, null, null, 1, 21, 'Precious stone', 12, 'Stolen');
INSERT INTO poklad (id_pokladu, id_mistnosti, id_dungeonu, id_dobrodruha, id_objednavky, nazev, hodnota, stav) VALUES (15, null, null, 1, 8, 'Precious stone', 12, 'Stolen');
INSERT INTO poklad (id_pokladu, id_mistnosti, id_dungeonu, id_dobrodruha, id_objednavky, nazev, hodnota, stav) VALUES (14, null, null, 1, 8, 'Precious stone', 12, 'Stolen');
INSERT INTO poklad (id_pokladu, id_mistnosti, id_dungeonu, id_dobrodruha, id_objednavky, nazev, hodnota, stav) VALUES (13, null, null, 1, 8, 'Precious stone', 12, 'Stolen');
INSERT INTO poklad (id_pokladu, id_mistnosti, id_dungeonu, id_dobrodruha, id_objednavky, nazev, hodnota, stav) VALUES (26, null, null, 1, 21, 'Precious stone', 12, 'Stolen');
INSERT INTO poklad (id_pokladu, id_mistnosti, id_dungeonu, id_dobrodruha, id_objednavky, nazev, hodnota, stav) VALUES (25, null, null, 1, 21, 'Precious stone', 12, 'Stolen');
INSERT INTO poklad (id_pokladu, id_mistnosti, id_dungeonu, id_dobrodruha, id_objednavky, nazev, hodnota, stav) VALUES (28, null, null, 12, 22, 'Ring of Strength', 86, 'Stolen');
INSERT INTO poklad (id_pokladu, id_mistnosti, id_dungeonu, id_dobrodruha, id_objednavky, nazev, hodnota, stav) VALUES (29, null, null, 12, 22, 'Chest of precious stones', 166, 'Stolen');
INSERT INTO poklad (id_pokladu, id_mistnosti, id_dungeonu, id_dobrodruha, id_objednavky, nazev, hodnota, stav) VALUES (30, null, null, 12, 22, 'Modern Rifle', 166, 'Stolen');
select setval(pg_get_serial_sequence('poklad','id_pokladu'),30);

-- PREKAZKA --
INSERT INTO prekazka (id_prekazky, id_dungeonu, popis, stav, datum, typ) VALUES (1, 1, 'Cleaning blood', 'Done', '3.2.234', null);
INSERT INTO prekazka (id_prekazky, id_dungeonu, popis, stav, datum, typ) VALUES (2, 1, 'Cleaning blood', 'Done', '2.13.235', null);
INSERT INTO prekazka (id_prekazky, id_dungeonu, popis, stav, datum, typ) VALUES (3, 1, 'Hungry Ghouls', 'Still hungry', '4.13.235', null);
INSERT INTO prekazka (id_prekazky, id_dungeonu, popis, stav, datum, typ) VALUES (4, 1, 'Crushed ceiling', 'Even better now', '3.6.235', null);
select setval(pg_get_serial_sequence('prekazka','id_prekazky'),4);

-- PREKAZKA - MISTNOST --
INSERT INTO prekazka_mistnost (id_prekazky, id_mistnosti, id_dungeonu) VALUES (1, 1, 1);
INSERT INTO prekazka_mistnost (id_prekazky, id_mistnosti, id_dungeonu) VALUES (1, 3, 1);
INSERT INTO prekazka_mistnost (id_prekazky, id_mistnosti, id_dungeonu) VALUES (1, 4, 1);
INSERT INTO prekazka_mistnost (id_prekazky, id_mistnosti, id_dungeonu) VALUES (1, 7, 1);
INSERT INTO prekazka_mistnost (id_prekazky, id_mistnosti, id_dungeonu) VALUES (1, 6, 1);
INSERT INTO prekazka_mistnost (id_prekazky, id_mistnosti, id_dungeonu) VALUES (2, 1, 1);
INSERT INTO prekazka_mistnost (id_prekazky, id_mistnosti, id_dungeonu) VALUES (2, 3, 1);
INSERT INTO prekazka_mistnost (id_prekazky, id_mistnosti, id_dungeonu) VALUES (2, 4, 1);
INSERT INTO prekazka_mistnost (id_prekazky, id_mistnosti, id_dungeonu) VALUES (2, 13, 1);
INSERT INTO prekazka_mistnost (id_prekazky, id_mistnosti, id_dungeonu) VALUES (2, 6, 1);
INSERT INTO prekazka_mistnost (id_prekazky, id_mistnosti, id_dungeonu) VALUES (2, 11, 1);
INSERT INTO prekazka_mistnost (id_prekazky, id_mistnosti, id_dungeonu) VALUES (3, 8, 1);
INSERT INTO prekazka_mistnost (id_prekazky, id_mistnosti, id_dungeonu) VALUES (4, 11, 1);



-- PRISERY --
INSERT INTO prisera (id_prisery, id_objednavky, id_ochrany, prisera_id_prisery, jmeno, typ, sila, stav) VALUES (43, 20, 16, null, 'Fire skull', 'demon', 4, 'flying and crazily laughing');
INSERT INTO prisera (id_prisery, id_objednavky, id_ochrany, prisera_id_prisery, jmeno, typ, sila, stav) VALUES (31, 6, null, null, 'Gholum', 'ghoul', 2, 'buisiness trip');
INSERT INTO prisera (id_prisery, id_objednavky, id_ochrany, prisera_id_prisery, jmeno, typ, sila, stav) VALUES (27, 6, 13, 43, 'Boss Ghoul', 'ghast', 2, 'hungry');
INSERT INTO prisera (id_prisery, id_objednavky, id_ochrany, prisera_id_prisery, jmeno, typ, sila, stav) VALUES (1, null, 1, null, 'Jacky Lee', 'skeleton', 0.25, 'active');
INSERT INTO prisera (id_prisery, id_objednavky, id_ochrany, prisera_id_prisery, jmeno, typ, sila, stav) VALUES (8, null, 1, 1, 'Dom-Degh', 'skeleton', 0.25, 'active');
INSERT INTO prisera (id_prisery, id_objednavky, id_ochrany, prisera_id_prisery, jmeno, typ, sila, stav) VALUES (6, null, 1, 1, 'Azor', 'skeleton', 0.25, 'active');
INSERT INTO prisera (id_prisery, id_objednavky, id_ochrany, prisera_id_prisery, jmeno, typ, sila, stav) VALUES (12, null, 10, null, 'John Sleeck', 'slime', 1, 'active');
INSERT INTO prisera (id_prisery, id_objednavky, id_ochrany, prisera_id_prisery, jmeno, typ, sila, stav) VALUES (16, null, 11, 12, 'Fay Woo', 'stirge', 0.125, 'Lost in battle');
INSERT INTO prisera (id_prisery, id_objednavky, id_ochrany, prisera_id_prisery, jmeno, typ, sila, stav) VALUES (2, null, 1, 1, 'Darry', 'skeleton', 0.25, 'Lost in battle');
INSERT INTO prisera (id_prisery, id_objednavky, id_ochrany, prisera_id_prisery, jmeno, typ, sila, stav) VALUES (36, 20, 15, 43, 'Bobby armless', 'zombie', 0.25, 'Lost in battle');
INSERT INTO prisera (id_prisery, id_objednavky, id_ochrany, prisera_id_prisery, jmeno, typ, sila, stav) VALUES (5, null, 1, 1, 'John', 'skeleton', 0.25, 'Lost in battle');
INSERT INTO prisera (id_prisery, id_objednavky, id_ochrany, prisera_id_prisery, jmeno, typ, sila, stav) VALUES (39, 20, 15, 43, 'Hue armless', 'zombie', 0.25, 'Lost in battle');
INSERT INTO prisera (id_prisery, id_objednavky, id_ochrany, prisera_id_prisery, jmeno, typ, sila, stav) VALUES (25, 6, 13, 27, 'Ghoul', 'ghoul', 1, 'Lost in battle');
INSERT INTO prisera (id_prisery, id_objednavky, id_ochrany, prisera_id_prisery, jmeno, typ, sila, stav) VALUES (24, 6, 13, 27, 'Ghoul', 'ghoul', 1, 'Lost in battle');
INSERT INTO prisera (id_prisery, id_objednavky, id_ochrany, prisera_id_prisery, jmeno, typ, sila, stav) VALUES (45, 24, 17, 1, 'Shark', 'pet', 2, 'Lost in battle');
INSERT INTO prisera (id_prisery, id_objednavky, id_ochrany, prisera_id_prisery, jmeno, typ, sila, stav) VALUES (34, 20, 15, 43, 'Joe legless', 'zombie', 0.25, 'pretending dead');
INSERT INTO prisera (id_prisery, id_objednavky, id_ochrany, prisera_id_prisery, jmeno, typ, sila, stav) VALUES (26, 6, 13, 27, 'Ghoul', 'ghoul', 1, 'Lost in battle');
INSERT INTO prisera (id_prisery, id_objednavky, id_ochrany, prisera_id_prisery, jmeno, typ, sila, stav) VALUES (46, 24, 17, 1, 'Shark', 'pet', 2, 'hungry');
INSERT INTO prisera (id_prisery, id_objednavky, id_ochrany, prisera_id_prisery, jmeno, typ, sila, stav) VALUES (44, 24, 17, 1, 'Shark', 'pet', 2, 'hungry');
INSERT INTO prisera (id_prisery, id_objednavky, id_ochrany, prisera_id_prisery, jmeno, typ, sila, stav) VALUES (21, 6, 13, 27, 'Ghoul', 'ghoul', 1, 'active');
INSERT INTO prisera (id_prisery, id_objednavky, id_ochrany, prisera_id_prisery, jmeno, typ, sila, stav) VALUES (23, 6, 13, 27, 'Ghoul', 'ghoul', 1, 'active');
INSERT INTO prisera (id_prisery, id_objednavky, id_ochrany, prisera_id_prisery, jmeno, typ, sila, stav) VALUES (9, null, 1, 1, 'Eliriel', 'skeleton', 0.25, 'hungry');
INSERT INTO prisera (id_prisery, id_objednavky, id_ochrany, prisera_id_prisery, jmeno, typ, sila, stav) VALUES (13, null, 11, 12, 'Day Woo', 'stirge', 0.125, 'hungry');
INSERT INTO prisera (id_prisery, id_objednavky, id_ochrany, prisera_id_prisery, jmeno, typ, sila, stav) VALUES (7, null, 1, 1, 'Gudh-Ahn', 'skeleton', 0.25, 'hungry');
INSERT INTO prisera (id_prisery, id_objednavky, id_ochrany, prisera_id_prisery, jmeno, typ, sila, stav) VALUES (22, 6, 13, 27, 'Ghoul', 'ghoul', 1, 'hungry');
INSERT INTO prisera (id_prisery, id_objednavky, id_ochrany, prisera_id_prisery, jmeno, typ, sila, stav) VALUES (4, null, 1, 1, 'Agarius', 'skeleton', 0.25, 'hungry');
INSERT INTO prisera (id_prisery, id_objednavky, id_ochrany, prisera_id_prisery, jmeno, typ, sila, stav) VALUES (3, null, null, 1, 'Macky', 'skeleton', 0.25, 'vacation');
INSERT INTO prisera (id_prisery, id_objednavky, id_ochrany, prisera_id_prisery, jmeno, typ, sila, stav) VALUES (30, 6, null, 31, 'Ghoul', 'ghoul', 1, 'buisiness trip');
INSERT INTO prisera (id_prisery, id_objednavky, id_ochrany, prisera_id_prisery, jmeno, typ, sila, stav) VALUES (28, 6, null, 31, 'Ghoul', 'ghoul', 1, 'buisiness trip');
INSERT INTO prisera (id_prisery, id_objednavky, id_ochrany, prisera_id_prisery, jmeno, typ, sila, stav) VALUES (29, 6, null, 31, 'Ghoul', 'ghoul', 1, 'buisiness trip');
INSERT INTO prisera (id_prisery, id_objednavky, id_ochrany, prisera_id_prisery, jmeno, typ, sila, stav) VALUES (41, 20, 15, 43, 'Joe dignity-less', 'zombie', 0.25, 'pretending dead');
INSERT INTO prisera (id_prisery, id_objednavky, id_ochrany, prisera_id_prisery, jmeno, typ, sila, stav) VALUES (40, 20, 15, 43, 'Jack armless', 'zombie', 0.25, 'pretending dead');
INSERT INTO prisera (id_prisery, id_objednavky, id_ochrany, prisera_id_prisery, jmeno, typ, sila, stav) VALUES (38, 20, 15, 43, 'Joe eyeless', 'zombie', 0.25, 'pretending dead');
INSERT INTO prisera (id_prisery, id_objednavky, id_ochrany, prisera_id_prisery, jmeno, typ, sila, stav) VALUES (33, 20, 15, 43, 'Joe armless', 'zombie', 0.25, 'pretending dead');
INSERT INTO prisera (id_prisery, id_objednavky, id_ochrany, prisera_id_prisery, jmeno, typ, sila, stav) VALUES (32, 20, 15, 43, 'Joe armless', 'zombie', 0.25, 'pretending dead');
INSERT INTO prisera (id_prisery, id_objednavky, id_ochrany, prisera_id_prisery, jmeno, typ, sila, stav) VALUES (47, 25, null, null, 'Yorn You-Burn', 'dragon', 6, 'in delivery');
INSERT INTO prisera (id_prisery, id_objednavky, id_ochrany, prisera_id_prisery, jmeno, typ, sila, stav) VALUES (17, null, 11, 12, 'Bay Woo', 'stirge', 0.125, 'active');
INSERT INTO prisera (id_prisery, id_objednavky, id_ochrany, prisera_id_prisery, jmeno, typ, sila, stav) VALUES (14, null, 11, 12, 'Gay Woo', 'stirge', 0.125, 'active');
INSERT INTO prisera (id_prisery, id_objednavky, id_ochrany, prisera_id_prisery, jmeno, typ, sila, stav) VALUES (18, null, 11, 12, 'Lay Woo', 'stirge', 0.125, 'active');
INSERT INTO prisera (id_prisery, id_objednavky, id_ochrany, prisera_id_prisery, jmeno, typ, sila, stav) VALUES (19, null, null, 12, 'Say Woo', 'stirge', 0.125, 'vacation');
INSERT INTO prisera (id_prisery, id_objednavky, id_ochrany, prisera_id_prisery, jmeno, typ, sila, stav) VALUES (20, null, 11, 12, 'Pay Woo', 'stirge', 0.125, 'active');
INSERT INTO prisera (id_prisery, id_objednavky, id_ochrany, prisera_id_prisery, jmeno, typ, sila, stav) VALUES (15, null, 11, 12, 'May Woo', 'stirge', 0.125, 'Lost in battle');
INSERT INTO prisera (id_prisery, id_objednavky, id_ochrany, prisera_id_prisery, jmeno, typ, sila, stav) VALUES (35, 20, 15, 43, 'Joe someless', 'zombie', 0.25, 'Lost in battle');
INSERT INTO prisera (id_prisery, id_objednavky, id_ochrany, prisera_id_prisery, jmeno, typ, sila, stav) VALUES (37, 20, 15, 43, 'Joe headless', 'zombie', 0.25, 'Lost in battle');

select setval(pg_get_serial_sequence('prisera','id_prisery'),47);

-- PRISERA - PREKAZKA --
INSERT INTO prisera_prekazka (id_prisery, id_prekazky) VALUES (4, 1);
INSERT INTO prisera_prekazka (id_prisery, id_prekazky) VALUES (5, 1);
INSERT INTO prisera_prekazka (id_prisery, id_prekazky) VALUES (6, 1);
INSERT INTO prisera_prekazka (id_prisery, id_prekazky) VALUES (4, 2);
INSERT INTO prisera_prekazka (id_prisery, id_prekazky) VALUES (5, 2);
INSERT INTO prisera_prekazka (id_prisery, id_prekazky) VALUES (6, 2);


-- SLUZBA --
INSERT INTO sluzba (id_sluzby, id_objednavky, popis, sluzba_od, sluzba_do) VALUES (1, null, 'Feeding Ghouls', null, null);
INSERT INTO sluzba (id_sluzby, id_objednavky, popis, sluzba_od, sluzba_do) VALUES (3, null, 'Feeding Ghouls', null, null);
INSERT INTO sluzba (id_sluzby, id_objednavky, popis, sluzba_od, sluzba_do) VALUES (4, null, 'Feeding Ghouls', null, null);
INSERT INTO sluzba (id_sluzby, id_objednavky, popis, sluzba_od, sluzba_do) VALUES (5, null, 'Feeding Ghouls', null, null);
INSERT INTO sluzba (id_sluzby, id_objednavky, popis, sluzba_od, sluzba_do) VALUES (6, null, 'Feeding Ghouls', null, null);
INSERT INTO sluzba (id_sluzby, id_objednavky, popis, sluzba_od, sluzba_do) VALUES (7, null, 'Feeding Ghouls', null, null);
INSERT INTO sluzba (id_sluzby, id_objednavky, popis, sluzba_od, sluzba_do) VALUES (8, null, 'Feeding Ghouls', null, null);
INSERT INTO sluzba (id_sluzby, id_objednavky, popis, sluzba_od, sluzba_do) VALUES (9, null, 'Feeding Ghouls', null, null);
INSERT INTO sluzba (id_sluzby, id_objednavky, popis, sluzba_od, sluzba_do) VALUES (10, null, 'Marketing', null, null);
INSERT INTO sluzba (id_sluzby, id_objednavky, popis, sluzba_od, sluzba_do) VALUES (12, null, 'Marketing', null, null);
INSERT INTO sluzba (id_sluzby, id_objednavky, popis, sluzba_od, sluzba_do) VALUES (11, 28, 'Marketing', null, null);
INSERT INTO sluzba (id_sluzby, id_objednavky, popis, sluzba_od, sluzba_do) VALUES (2, 27, 'Marketing', null, null);
INSERT INTO sluzba (id_sluzby, id_objednavky, popis, sluzba_od, sluzba_do) VALUES (13, 26, 'Marketing', null, null);
select setval(pg_get_serial_sequence('sluzba','id_sluzby'),13);

-- SLUZBA - PREKAZKA --
INSERT INTO sluzba_prekazka (id_sluzby, id_prekazky) VALUES (3, 3);
INSERT INTO sluzba_prekazka (id_sluzby, id_prekazky) VALUES (4, 3);
INSERT INTO sluzba_prekazka (id_sluzby, id_prekazky) VALUES (5, 3);
INSERT INTO sluzba_prekazka (id_sluzby, id_prekazky) VALUES (6, 3);
INSERT INTO sluzba_prekazka (id_sluzby, id_prekazky) VALUES (7, 3);
INSERT INTO sluzba_prekazka (id_sluzby, id_prekazky) VALUES (8, 3);
INSERT INTO sluzba_prekazka (id_sluzby, id_prekazky) VALUES (9, 3);


-- VYPRAVA --
INSERT INTO vyprava (id_vypravy, datum_registrace, stav, sila, prezdivka, ztraty_dusi, zisk_dusi, vyprava_od, vyprava_do) VALUES (5, '0666-04-12', 'Arriving', 9999999, 'Apocalypse', null, null, null, null);
INSERT INTO vyprava (id_vypravy, datum_registrace, stav, sila, prezdivka, ztraty_dusi, zisk_dusi, vyprava_od, vyprava_do) VALUES (2, '0234-02-02', 'Finished', 3, 'Dummy attack', null, null, null, null);
INSERT INTO vyprava (id_vypravy, datum_registrace, stav, sila, prezdivka, ztraty_dusi, zisk_dusi, vyprava_od, vyprava_do) VALUES (4, '0236-04-26', 'Finished', 16, '', null, null, null, null);
INSERT INTO vyprava (id_vypravy, datum_registrace, stav, sila, prezdivka, ztraty_dusi, zisk_dusi, vyprava_od, vyprava_do) VALUES (3, '0235-02-17', 'Finished', 12, 'ez', null, null, null, null);
INSERT INTO vyprava (id_vypravy, datum_registrace, stav, sila, prezdivka, ztraty_dusi, zisk_dusi, vyprava_od, vyprava_do) VALUES (6, '0235-08-17', 'Finished', 12, 'Fight club', null, null, null, null);
select setval(pg_get_serial_sequence('vyprava','id_vypravy'),6);

-- VYPRAVA - DOBRODRUH --
INSERT INTO vyprava_dobrodruh (id_vypravy, id_dobrodruha) VALUES (2, 7);
INSERT INTO vyprava_dobrodruh (id_vypravy, id_dobrodruha) VALUES (2, 8);
INSERT INTO vyprava_dobrodruh (id_vypravy, id_dobrodruha) VALUES (2, 9);
INSERT INTO vyprava_dobrodruh (id_vypravy, id_dobrodruha) VALUES (3, 5);
INSERT INTO vyprava_dobrodruh (id_vypravy, id_dobrodruha) VALUES (3, 6);
INSERT INTO vyprava_dobrodruh (id_vypravy, id_dobrodruha) VALUES (3, 10);
INSERT INTO vyprava_dobrodruh (id_vypravy, id_dobrodruha) VALUES (3, 11);
INSERT INTO vyprava_dobrodruh (id_vypravy, id_dobrodruha) VALUES (3, 13);
INSERT INTO vyprava_dobrodruh (id_vypravy, id_dobrodruha) VALUES (4, 1);
INSERT INTO vyprava_dobrodruh (id_vypravy, id_dobrodruha) VALUES (4, 3);
INSERT INTO vyprava_dobrodruh (id_vypravy, id_dobrodruha) VALUES (4, 4);
INSERT INTO vyprava_dobrodruh (id_vypravy, id_dobrodruha) VALUES (4, 5);
INSERT INTO vyprava_dobrodruh (id_vypravy, id_dobrodruha) VALUES (5, 14);
INSERT INTO vyprava_dobrodruh (id_vypravy, id_dobrodruha) VALUES (6, 15);
INSERT INTO vyprava_dobrodruh (id_vypravy, id_dobrodruha) VALUES (6, 16);
INSERT INTO vyprava_dobrodruh (id_vypravy, id_dobrodruha) VALUES (6, 17);
INSERT INTO vyprava_dobrodruh (id_vypravy, id_dobrodruha) VALUES (6, 18);



-- VYPRAVA - MISTNOST --
INSERT INTO vyprava_mistnost (id_vypravy, id_mistnosti, id_dungeonu) VALUES (2, 3, 1);
INSERT INTO vyprava_mistnost (id_vypravy, id_mistnosti, id_dungeonu) VALUES (2, 4, 1);
INSERT INTO vyprava_mistnost (id_vypravy, id_mistnosti, id_dungeonu) VALUES (2, 1, 1);
INSERT INTO vyprava_mistnost (id_vypravy, id_mistnosti, id_dungeonu) VALUES (3, 3, 1);
INSERT INTO vyprava_mistnost (id_vypravy, id_mistnosti, id_dungeonu) VALUES (3, 4, 1);
INSERT INTO vyprava_mistnost (id_vypravy, id_mistnosti, id_dungeonu) VALUES (3, 1, 1);
INSERT INTO vyprava_mistnost (id_vypravy, id_mistnosti, id_dungeonu) VALUES (3, 6, 1);
INSERT INTO vyprava_mistnost (id_vypravy, id_mistnosti, id_dungeonu) VALUES (3, 9, 1);
INSERT INTO vyprava_mistnost (id_vypravy, id_mistnosti, id_dungeonu) VALUES (3, 11, 1);
INSERT INTO vyprava_mistnost (id_vypravy, id_mistnosti, id_dungeonu) VALUES (3, 12, 1);
INSERT INTO vyprava_mistnost (id_vypravy, id_mistnosti, id_dungeonu) VALUES (4, 1, 1);
INSERT INTO vyprava_mistnost (id_vypravy, id_mistnosti, id_dungeonu) VALUES (4, 3, 1);
INSERT INTO vyprava_mistnost (id_vypravy, id_mistnosti, id_dungeonu) VALUES (4, 4, 1);
INSERT INTO vyprava_mistnost (id_vypravy, id_mistnosti, id_dungeonu) VALUES (4, 6, 1);
INSERT INTO vyprava_mistnost (id_vypravy, id_mistnosti, id_dungeonu) VALUES (4, 7, 1);
INSERT INTO vyprava_mistnost (id_vypravy, id_mistnosti, id_dungeonu) VALUES (4, 8, 1);
INSERT INTO vyprava_mistnost (id_vypravy, id_mistnosti, id_dungeonu) VALUES (4, 9, 1);
INSERT INTO vyprava_mistnost (id_vypravy, id_mistnosti, id_dungeonu) VALUES (4, 10, 1);
INSERT INTO vyprava_mistnost (id_vypravy, id_mistnosti, id_dungeonu) VALUES (4, 11, 1);
INSERT INTO vyprava_mistnost (id_vypravy, id_mistnosti, id_dungeonu) VALUES (4, 13, 1);
INSERT INTO vyprava_mistnost (id_vypravy, id_mistnosti, id_dungeonu) VALUES (6, 1, 1);
INSERT INTO vyprava_mistnost (id_vypravy, id_mistnosti, id_dungeonu) VALUES (6, 3, 1);
INSERT INTO vyprava_mistnost (id_vypravy, id_mistnosti, id_dungeonu) VALUES (6, 12, 1);
INSERT INTO vyprava_mistnost (id_vypravy, id_mistnosti, id_dungeonu) VALUES (6, 13, 1);
INSERT INTO vyprava_mistnost (id_vypravy, id_mistnosti, id_dungeonu) VALUES (6, 14, 1);

