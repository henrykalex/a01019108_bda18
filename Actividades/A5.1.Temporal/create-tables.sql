-- Tablas:
--   PolizaUsuario
CREATE TABLE poliza_usuario (
  NO_POLIZA INT NOT NULL GENERATED ALWAYS AS IDENTITY (START WITH 1 INCREMENT BY 1),
  NOMBRE VARCHAR(25) NOT NULL,
  FECHA_NACIMIENTO DATE NOT NULL,
  DIRECCION VARCHAR(25) NOT NULL,
  INICIO_POLIZA DATE NOT NULL,
  FIN_POLIZA DATE NOT NULL,
  period business_time(INICIO_POLIZA,FIN_POLIZA),
  COSTO_POLIZA DECIMAL(9,2),
  COBERTURA INT NOT NULL,
  ANO_VEHICULO INT NOT NULL,
  MODELO_VEHICULO VARCHAR(20) NOT NULL,
  MARCA_VEHICULO VARCHAR(20) NOT NULL,
  PRECIO_VEHICULO DECIMAL(6,2) NOT NULL,
  NUMERO_SERIE_VEIHCULO VARCHAR(20) NOT NULL,
  PRIMARY KEY(NO_POLIZA)
);
CREATE TABLE  poliza_usuario_sys (
  NO_POLIZA INT NOT NULL,
  DIRECCION VARCHAR(25) NOT NULL,
  INICIO_POLIZA DATE NOT NULL,
  FIN_POLIZA DATE NOT NULL,
  period business_time(INICIO_POLIZA,FIN_POLIZA),
  COSTO_POLIZA DECIMAL(9,2),
  COBERTURA INT NOT NULL,
  INICIO_SYS TIMESTAMP(12) GENERATED ALWAYS AS ROW BEGIN NOT NULL,
  FIN_SYS TIMESTAMP(12) GENERATED ALWAYS AS ROW END NOT NULL,
  trans_start TIMESTAMP(12) GENERATED ALWAYS AS TRANSACTION START ID IMPLICITLY HIDDEN,
  period SYSTEM_time(INICIO_SYS,FIN_SYS),
  PRIMARY KEY(NO_POLIZA)
);
CREATE TABLE  poliza_usuario_sys_history LIKE poliza_usuario_sys;
-- keep history
ALTER TABLE poliza_usuario_sys ADD VERSIONING USE HISTORY TABLE poliza_usuario_sys_history;
