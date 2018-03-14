-- CREATE TABLE `sakila`.`log_film` (
--   `id` SMALLINT(5) NOT NULL,
--   `tipo` VARCHAR(25) NOT NULL DEFAULT 'update',
--   `film_id` SMALLINT(5) NOT NULL,
--   `new_value` VARCHAR(45) NULL,
--   `last_value` VARCHAR(45) NULL,
--   `timestamp` TIMESTAMP NOT NULL,
--   PRIMARY KEY (`id`),
--   UNIQUE INDEX `id_UNIQUE` (`id` ASC));
-- 
-- drop PROCEDURE IF EXISTS fill_log;
-- DELIMITER //
-- CREATE PROCEDURE fill_log
-- (IN film_id SMALLINT(5),
-- IN last_val CHAR(45),
-- IN new_val CHAR(45))
-- BEGIN
--   INSERT INTO LOG_FILM (tipo,fil_id,last_value,new_value) VALUES ('update',film_id,last_val,new_val);
-- END //
-- DELIMITER ;

-- CALL fill_log(4,'AFFAIR PREJUDICE','AFFAIR PREJJJUDICE');
-- 
-- DELIMITER //
-- CREATE TRIGGER filmp_update AFTER INSERT ON film
--        FOR EACH ROW 
--        BEGIN
--        CALL fill_log(NEW.film_id,NULL,NEW.original_language);
--        END;
-- 	DELIMITER ;


drop PROCEDURE IF EXISTS update_original_language;
DELIMITER //
CREATE PROCEDURE update_original_language()
BEGIN
	DECLARE done INT DEFAULT FALSE;
    DECLARE fid SMALLINT(5);
    DECLARE cat_name VARCHAR(25);
    DECLARE act_fname VARCHAR(45);
    DECLARE act_lname VARCHAR(45);
	DECLARE curs1 CURSOR FOR SELECT film.film_id, category.name as category_name, actor.first_name, actor.last_name FROM film join film_category on film.film_id=film_category.film_id join category on film_category.category_id=category.category_id join film_actor on film.film_id=film_actor.film_id join actor on film_actor.actor_id=actor.actor_id;
	DECLARE CONTINUE HANDLER FOR NOT FOUND SET done = TRUE;
-- 	UPDATE film SET original_language_id
	OPEN curs1;
    
    read_loop: LOOP
		FETCH curs1 INTO fid, cat_name,act_fname,act_lname;
		IF done THEN
			LEAVE read_loop;
		END IF;
		IF cat_name = "Documentary" THEN
			UPDATE film set original_language_id = 2 where film.film_id = fid;
		ELSEIF cat_name = "Foreign" THEN
			UPDATE film set original_language_id = 3 where film.film_id = fid;
		ELSEIF act_fname = "SISSI" AND act_lname = "SOBIESKI" THEN
			UPDATE film set original_language_id = 6 where film.film_id = fid;
		ELSEIF act_fname = "ED" AND act_lname = "CHASE" THEN
			UPDATE film set original_language_id = 4 where film.film_id = fid;
		ELSEIF act_fname = "AUDREY" AND act_lname = "OLIVIER" THEN
			UPDATE film set original_language_id = 5 where film.film_id = fid;
		ELSE
			UPDATE film set original_language_id = 1 where film.film_id = fid;
		END IF;
	END LOOP;

  CLOSE curs1;
    
END //
DELIMITER ;

call update_original_language();