INSERT INTO poliza_usuario (NOMBRE,FECHA_NACIMIENTO,DIRECCION,INICIO_POLIZA,FIN_POLIZA,COSTO_POLIZA,COBERTURA,ANO_VEHICULO,MODELO_VEHICULO,MARCA_VEHICULO,PRECIO_VEHICULO,NUMERO_SERIE_VEIHCULO)
VALUES ('Enrique','1994-05-28','Colina de cahuas','2017-06-01','2018-06-01', 100.00, 2,2015,'SS2','Mazda', 234.00,'hkdbja87asdfb');

UPDATE poliza_usuario SET DIRECCION = 'Colina de arecibo' WHERE NO_POLIZA = 2;

UPDATE poliza_usuario SET COBERTURA = 1 WHERE NO_POLIZA = 2;
UPDATE poliza_usuario SET COBERTURA = 3 WHERE NO_POLIZA = 2;

select * from poliza_usuario
select * from poliza_usuario_sys
select * from poliza_usuario_sys_history
