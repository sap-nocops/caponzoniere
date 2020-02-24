CREATE TABLE IF NOT EXISTS songs(
        id            INTEGER   PRIMARY KEY    AUTOINCREMENT,
        title         CHAR(10)          NOT NULL,
        type_id    INT                  NOT NULL,
        lyrics       CHAR(300));

CREATE TABLE IF NOT EXISTS topics(
        id            INTEGER   PRIMARY KEY    AUTOINCREMENT,
        name         CHAR(20)          NOT NULL);

CREATE TABLE IF NOT EXISTS song_types(
    	id            INTEGER 	 PRIMARY KEY,
    	name       CHAR(10)	 NOT NULL,
    	duration  INT 			 NOT NULL);
------

INSERT INTO song_types (id, name, duration)
    VALUES (1, 'Corrido', 25);

INSERT INTO song_types (id, name, duration)
    VALUES (2, 'Quadra', 60);

INSERT INTO song_types (id, name, duration)
    VALUES (3, 'Laidainha', 150);
------
INSERT INTO topics (name)
    VALUES ('Dona e Mulher');

INSERT INTO topics (name)
    VALUES ('Mar');

INSERT INTO topics (name)
    VALUES ('Lua');

INSERT INTO topics (name)
    VALUES ('Capoeira');

INSERT INTO topics (name)
    VALUES ('Mestres');

INSERT INTO topics (name)
    VALUES ('Besouro Mangangà');

INSERT INTO topics (name)
    VALUES ('Angola');

INSERT INTO topics (name)
    VALUES ('Orixas');

INSERT INTO topics (name)
    VALUES ('Deus y Santos');

INSERT INTO topics (name)
    VALUES ('Marinheiro');

INSERT INTO topics (name)
    VALUES ('Coco');
------
INSERT INTO songs (title, type_id, lyrics)
    VALUES ('Dona Maria do camboatà', 1, 'Dona Maria do camboatà ela chega na venda e comenca a gingar');

INSERT INTO songs (title, type_id, lyrics)
    VALUES ('Camungere', 1, 'Camungere come vai como ta camungere como vai voce camungere como vai de saude camungere para mi è un prazer');

INSERT INTO songs (title, type_id, lyrics)
    VALUES ('Dona Alice', 1, 'Dona Alice nao me pegue nao, nao me aggarra nao me pegue nao, Dona Alice nao me pegue nao, nao me pegue nao me pegue nao me pegue nao');

INSERT INTO songs (title, type_id, lyrics)
    VALUES ('Marinhero sò', 1, 'Eu nao sou da qui, Marinhero sò, eu nao tenho amor, Marinhero sò, eu so da bahia, Marinhero sò, de San Salvador ');

INSERT INTO songs (title, type_id, lyrics)
    VALUES ('Santa Maria mae de Deus', 1, 'Santa Maria mae de Deus, chegei na igregia me confessei, Santa Maria mae de Deus, chegei na igregia me ajuelhei');

INSERT INTO songs (title, type_id, lyrics)
    VALUES ('A bananeira caiu', 1, '');

INSERT INTO songs (title, type_id, lyrics)
    VALUES ('Abalou Capoeira', 1, '');

INSERT INTO songs (title, type_id, lyrics)
    VALUES ('Sim Sim Sim Nao Nao Nao', 1, '');

INSERT INTO songs (title, type_id, lyrics)
    VALUES ('A canoa virou marinhero', 1, '');

INSERT INTO songs (title, type_id, lyrics)
    VALUES ('Pomba vuou', 1, '');

INSERT INTO songs (title, type_id, lyrics)
    VALUES ('Ai ai ai Dottor', 1, '');

INSERT INTO songs (title, type_id, lyrics)
    VALUES ('Bentivi vuou La Lauè', 1, '');

INSERT INTO songs (title, type_id, lyrics)
    VALUES ('Ai ai ai Sao Bento me chama', 1, '');

INSERT INTO songs (title, type_id, lyrics)
    VALUES ('A cobra me mordeu Senhor Sao Bento', 1, '');

INSERT INTO songs (title, type_id, lyrics)
    VALUES ('O a o a e', 1, '');

INSERT INTO songs (title, type_id, lyrics)
    VALUES ('Quebra gereba', 1, '');

INSERT INTO songs (title, type_id, lyrics)
    VALUES ('Paranauè', 1, '');

INSERT INTO songs (title, type_id, lyrics)
    VALUES ('O que è bonito è pra si ver', 1, '');

INSERT INTO songs (title, type_id, lyrics)
    VALUES ('Meu atabaque è de couro de boi', 1, '');

INSERT INTO songs (title, type_id, lyrics)
    VALUES ('O lae laela o Lelè', 1, '');

INSERT INTO songs (title, type_id, lyrics)
    VALUES ('Nem tudo que reluce è ouro', 1, '');

INSERT INTO songs (title, type_id, lyrics)
    VALUES ('A marè ta cheia ioio', 1, '');

INSERT INTO songs (title, type_id, lyrics)
    VALUES ('Sou homeme nao sou mulher', 1, '');
