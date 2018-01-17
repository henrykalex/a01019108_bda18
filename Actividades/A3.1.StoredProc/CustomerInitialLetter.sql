use classicmodels;
delimiter $$
create procedure count_customers_a(
IN initial_char varchar(1)
)
BEGIN
	declare contador int default 0;
	select count(*)  into contador from customers where LEFT(customerName, 1) = initial_char;
    select contador;
END$$

delimiter ;
