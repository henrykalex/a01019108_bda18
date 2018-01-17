use classicmodels;
delimiter $$
create procedure select_cheaper_epensive()
BEGIN
	declare cheaper varchar(70);
    declare cheaperPrice varchar(70);
    
    declare expensive varchar(70);
    declare expensivePrice varchar(70);
    
	select productName, buyPrice  into cheaper, cheaperPrice
	from products
	where buyPrice = 
    (select min(buyPrice) from products);
    
	select productName, buyPrice  into expensive, expensivePrice
	from products
	where buyPrice = 
    (select max(buyPrice) from products);
    
    select cheaper, cheaperPrice, expensive, expensivePrice;
END$$

delimiter ;
