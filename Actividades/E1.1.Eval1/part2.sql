CREATE TABLE gomita (
  ID SMALLINT NOT NULL GENERATED ALWAYS AS IDENTITY (START WITH 1 INCREMENT BY 1),
  NOMBRE VARCHAR(45) NOT NULL,
  COSTO VARCHAR(45) NULL,
  INICIO DATE NOT NULL,
  FIN DATE NOT NULL,
  period business_time(INICIO,FIN),
  PRIMARY KEY (ID, business_time WITHOUT overlaps));

  INSERT INTO gomita ( NOMBRE, COSTO, INICIO, FIN) values
  ('dulce1',10 ,'2018-1-1', '2019-1-1'),
  ('dulce2',20 ,'2018-1-1', '2019-1-1'),
  ('dulce3',30 ,'2018-1-1', '2019-1-1'),
  ('dulce4',40 ,'2018-1-1', '2019-1-1'),
  ('dulce5',50 ,'2018-1-1', '2019-1-1'),
  ('dulce6',60 ,'2018-1-1', '2019-1-1'),
  ('dulce7',70 ,'2018-1-1', '2019-1-1'),
  ('dulce8',80 ,'2018-1-1', '2019-1-1'),
  ('dulce9',90 ,'2018-1-1', '2019-1-1'),
  ('dulce10',100 ,'2018-1-1', '2019-1-1'),
  ('dulce11',110 ,'2018-1-1', '2019-1-1'),
  ('dulce12',120 ,'2018-1-1', '2019-1-1');


  UPDATE gomita FOR portion of business_time FROM '2018-2-1' to '2018-2-15' SET costo = costo*1.45;

  UPDATE gomita FOR portion of business_time FROM '2018-2-15' to '2019-4-25' SET costo = (costo/1.45)*1.1;

  UPDATE gomita FOR portion of business_time FROM '2018-4-25' to '2019-5-5' SET costo = costo*1.45;

  UPDATE gomita FOR portion of business_time FROM '2018-5-5' to '2019-10-25' SET costo = (costo/1.45)*1.1;

  UPDATE gomita FOR portion of business_time FROM '2018-10-25' to '2019-11-5' SET costo = costo*1.45;

  UPDATE gomita FOR portion of business_time FROM '2018-11-5' to '2019-1-1' SET costo = (costo/1.45)*1.1;

  SELECT * from gomita WHERE NOMBRE='dulce1';

  SELECT SUM(COSTO)/COUNT(*) as promedio from gomita WHERE NOMBRE='dulce1';

  SELECT MAX(COSTO) as MAX from gomita WHERE NOMBRE='dulce1';

  SELECT MIN(COSTO) as MIN from gomita WHERE NOMBRE='dulce1';
