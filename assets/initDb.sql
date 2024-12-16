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

INSERT INTO song_types (id, name, duration) VALUES
    (1, 'Corrido', 25),
    (2, 'Quadra', 60),
    (3, 'Laidainha', 150);
------
INSERT INTO topics (name) VALUES
    ('Dona e Mulher'),
    ('Mar'),
    ('Lua'),
    ('Capoeira'),
    ('Mestres'),
    ('Besouro Mangangà'),
    ('Angola'),
    ('Orixas'),
    ('Deus y Santos'),
    ('Marinheiro'),
    ('Coco');
------
INSERT INTO songs (title, type_id, lyrics) VALUES
    ('Dona Maria do camboatà', 1, 'Dona Maria do camboatà ela chega na venda e comenca a gingar'),
    ('Camungere', 1, 'Camungere come vai como ta camungere como vai voce camungere como vai de saude camungere para mi è un prazer'),
    ('Dona Alice', 1, 'Dona Alice nao me pegue nao, nao me aggarra nao me pegue nao, Dona Alice nao me pegue nao, nao me pegue nao me pegue nao me pegue nao'),
    ('Marinhero sò', 1, 'Eu nao sou da qui, Marinhero sò, eu nao tenho amor, Marinhero sò, eu so da bahia, Marinhero sò, de San Salvador '),
    ('Santa Maria mae de Deus', 1, 'Santa Maria mae de Deus, chegei na igregia me confessei, Santa Maria mae de Deus, chegei na igregia me ajuelhei'),
    ('A bananeira caiu', 1, ''),
    ('Abalou Capoeira', 1, ''),
    ('Sim Sim Sim Nao Nao Nao', 1, ''),
    ('A canoa virou marinhero', 1, ''),
    ('Pomba vuou', 1, ''),
    ('Ai ai ai Dottor', 1, ''),
    ('Bentivi vuou La Lauè', 1, ''),
    ('Ai ai ai Sao Bento me chama', 1, ''),
    ('A cobra me mordeu Senhor Sao Bento', 1, ''),
    ('O a o a e', 1, ''),
    ('Quebra gereba', 1, ''),
    ('Paranauè', 1, ''),
    ('O que è bonito è pra si ver', 1, ''),
    ('Meu atabaque è de couro de boi', 1, ''),
    ('O lae laela o Lelè', 1, ''),
    ('Nem tudo que reluce è ouro', 1, ''),
    ('A marè ta cheia ioio', 1, ''),
    ('Sou homeme nao sou mulher', 1, '');
