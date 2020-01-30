CREATE TABLE IF NOT EXISTS songs(
        id            INTEGER   PRIMARY KEY    AUTOINCREMENT,
        title         CHAR(10)          NOT NULL,
        type_id    INT                  NOT NULL,
        lyrics       CHAR(300);

CREATE TABLE IF NOT EXISTS songs(
    	id            INTEGER 	 PRIMARY KEY    AUTOINCREMENT,
    	title         CHAR(10)			 NOT NULL,
    	type_id    INT 				 NOT NULL,
    	lyrics       CHAR(300);

CREATE TABLE IF NOT EXISTS songs(
    	id            INTEGER 	 PRIMARY KEY,
    	name       CHAR(10)	 NOT NULL,
    	duration  INT 				 NOT NULL;

INSERT INTO songs (title, type_id, lyrics)
    VALUES ('Dona Maria do camboatà', 1, 'Dona Maria do camboatà ela chega na venda e comenca a gingar');
INSERT INTO songs (title, type_id, lyrics)
    VALUES ('Camungere', 1, 'Camungere come vai como ta camungere como vai voce camungere como vai de saude camungere para mi è un prazer');
INSERT INTO songs (title, type_id, lyrics)
    VALUES ('Dona Alice', 1, 'Dona Alice nao me pegue nao, nao me aggarra nao me pegue nao, Dona Alice nao me pegue nao, nao me pegue nao me pegue nao me pegue nao');
INSERT INTO songs (title, type_id, lyrics)
    VALUES ('Marinhero sò', 1, 'Eu nao sou da qui, Marinhero sò, eu nao tenho amor, Marinhero sò, eu so da bahia, Marinhero sò, de San Salvador ');