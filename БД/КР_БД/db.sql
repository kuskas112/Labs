CREATE SCHEMA IF NOT EXISTS `mydb` DEFAULT CHARACTER SET utf8 ;
USE `mydb` ;

CREATE TABLE IF NOT EXISTS `mydb`.`Wrap` (
  `id` SMALLINT UNSIGNED NOT NULL AUTO_INCREMENT,
  `wrap_type` VARCHAR(45) NOT NULL,
  PRIMARY KEY (`id`));


CREATE TABLE IF NOT EXISTS `mydb`.`Company` (
  `id` SMALLINT UNSIGNED NOT NULL AUTO_INCREMENT,
  `name` VARCHAR(45) NOT NULL,
  `city` VARCHAR(45) NULL,
  `is_manufacturer` BIT NULL,
  `is_supplier` BIT NULL,
  PRIMARY KEY (`id`));

CREATE TABLE IF NOT EXISTS `mydb`.`Measure_unit` (
  `id` SMALLINT UNSIGNED NOT NULL AUTO_INCREMENT,
  `name` VARCHAR(20) NULL,
  PRIMARY KEY (`id`));


CREATE TABLE IF NOT EXISTS `mydb`.`Worker` (
  `id` SMALLINT NOT NULL AUTO_INCREMENT,
  `name` VARCHAR(50) NOT NULL,
  `profession` VARCHAR(45) NOT NULL,
  PRIMARY KEY (`id`));


CREATE TABLE IF NOT EXISTS `mydb`.`Cancellation` (
  `id` SMALLINT UNSIGNED NOT NULL AUTO_INCREMENT,
  `summarised` DECIMAL(8,2) NULL DEFAULT 0,
  `date` DATE NOT NULL,
  `Worker_id` SMALLINT NOT NULL,
  PRIMARY KEY (`id`),
  CONSTRAINT `fk_Cancellation_Worker1`
    FOREIGN KEY (`Worker_id`)
    REFERENCES `mydb`.`Worker` (`id`));

CREATE TABLE IF NOT EXISTS `mydb`.`Buy` (
  `id` MEDIUMINT UNSIGNED NOT NULL AUTO_INCREMENT,
  `summarised` DECIMAL(6,2) NULL DEFAULT 0,
  `datetime` DATETIME NOT NULL,
  `Worker_id` SMALLINT NOT NULL,
  PRIMARY KEY (`id`),
  CONSTRAINT `fk_Buy_Worker1`
    FOREIGN KEY (`Worker_id`)
    REFERENCES `mydb`.`Worker` (`id`));

CREATE TABLE IF NOT EXISTS `mydb`.`Supply` (
  `id` SMALLINT UNSIGNED NOT NULL AUTO_INCREMENT,
  `date` DATE NOT NULL,
  `Company_id` SMALLINT UNSIGNED NOT NULL,
  `Worker_id` SMALLINT NOT NULL,
  PRIMARY KEY (`id`),
  CONSTRAINT `fk_Supply_Company`
    FOREIGN KEY (`Company_id`)
    REFERENCES `mydb`.`Company` (`id`),
  CONSTRAINT `fk_Supply_Worker1`
    FOREIGN KEY (`Worker_id`)
    REFERENCES `mydb`.`Worker` (`id`));

CREATE TABLE IF NOT EXISTS `mydb`.`Product` (
  `id` MEDIUMINT UNSIGNED NOT NULL AUTO_INCREMENT,
  `name` VARCHAR(50) NOT NULL,
  `shortage_life` SMALLINT UNSIGNED NOT NULL,
  `Company_id` SMALLINT UNSIGNED NOT NULL,
  `Wrap_id` SMALLINT UNSIGNED NOT NULL,
  `extra` TINYINT UNSIGNED NOT NULL,
  `retail_price` DECIMAL(7,2) NULL,
  PRIMARY KEY (`id`),
  CONSTRAINT `fk_Product_Company1`
    FOREIGN KEY (`Company_id`)
    REFERENCES `mydb`.`Company` (`id`),
  CONSTRAINT `fk_Product_Wrap1`
    FOREIGN KEY (`Wrap_id`)
    REFERENCES `mydb`.`Wrap` (`id`));


CREATE TABLE IF NOT EXISTS `mydb`.`Invoice` (
  `Supply_id` SMALLINT UNSIGNED NOT NULL,
  `Product_id` MEDIUMINT UNSIGNED NOT NULL,
  `Measure_unit_id` SMALLINT UNSIGNED NOT NULL,
  `amount` SMALLINT UNSIGNED NOT NULL,
  `price` DECIMAL(7,2) NOT NULL,
  `tax` DECIMAL(4,2) NOT NULL,
  `summarised` DECIMAL(8,2) NULL DEFAULT 0,
  `taxed_summarised` DECIMAL(8,2) NULL DEFAULT 0,
  PRIMARY KEY (`Supply_id`, `Product_id`),
  CONSTRAINT `fk_Supply_has_Product_Supply1`
    FOREIGN KEY (`Supply_id`)
    REFERENCES `mydb`.`Supply` (`id`),
  CONSTRAINT `fk_Supply_has_Product_Product1`
    FOREIGN KEY (`Product_id`)
    REFERENCES `mydb`.`Product` (`id`),
  CONSTRAINT `fk_Supply_has_Product_Measure_unit1`
    FOREIGN KEY (`Measure_unit_id`)
    REFERENCES `mydb`.`Measure_unit` (`id`));


CREATE TABLE IF NOT EXISTS `mydb`.`Cancellation_has_Invoice` (
  `Cancellation_id` SMALLINT UNSIGNED NOT NULL,
  `Invoice_Supply_id` SMALLINT UNSIGNED NOT NULL,
  `Invoice_Product_id` MEDIUMINT UNSIGNED NOT NULL,
  `amount` SMALLINT UNSIGNED NOT NULL,
  `summarised` DECIMAL(8,2) NULL DEFAULT 0,
  PRIMARY KEY (`Cancellation_id`, `Invoice_Supply_id`, `Invoice_Product_id`),
  CONSTRAINT `fk_Cancellation_has_Supply_has_Product_Cancellation1`
    FOREIGN KEY (`Cancellation_id`)
    REFERENCES `mydb`.`Cancellation` (`id`),
  CONSTRAINT `fk_Cancellation_has_Supply_has_Product_Supply_has_Product1`
    FOREIGN KEY (`Invoice_Supply_id` , `Invoice_Product_id`)
    REFERENCES `mydb`.`Invoice` (`Supply_id` , `Product_id`));


CREATE TABLE IF NOT EXISTS `mydb`.`Buy_has_Invoice` (
  `Buy_id` MEDIUMINT UNSIGNED NOT NULL,
  `Invoice_Supply_id` SMALLINT UNSIGNED NOT NULL,
  `Invoice_Product_id` MEDIUMINT UNSIGNED NOT NULL,
  `amount` SMALLINT UNSIGNED NOT NULL,
  `summarised` DECIMAL(6,2) NULL DEFAULT 0,
  PRIMARY KEY (`Buy_id`, `Invoice_Supply_id`, `Invoice_Product_id`),
  CONSTRAINT `fk_Buy_has_Product_Buy1`
    FOREIGN KEY (`Buy_id`)
    REFERENCES `mydb`.`Buy` (`id`),
  CONSTRAINT `fk_Buy_has_Product_Invoice1`
    FOREIGN KEY (`Invoice_Supply_id` , `Invoice_Product_id`)
    REFERENCES `mydb`.`Invoice` (`Supply_id` , `Product_id`));


CREATE TABLE IF NOT EXISTS `mydb`.`Characteristic` (
  `id` SMALLINT UNSIGNED NOT NULL AUTO_INCREMENT,
  `name` VARCHAR(60) NOT NULL,
  PRIMARY KEY (`id`));


CREATE TABLE IF NOT EXISTS `mydb`.`Product_has_Characteristic` (
  `Product_id` MEDIUMINT UNSIGNED NOT NULL,
  `Characteristic_id` SMALLINT UNSIGNED NOT NULL,
  `numeric_value` DECIMAL(6,2) NULL,
  `symbol_value` VARCHAR(45) NULL,
  PRIMARY KEY (`Product_id`, `Characteristic_id`),
  CONSTRAINT `fk_Product_has_Characteristic_Product1`
    FOREIGN KEY (`Product_id`)
    REFERENCES `mydb`.`Product` (`id`),
  CONSTRAINT `fk_Product_has_Characteristic_Characteristic1`
    FOREIGN KEY (`Characteristic_id`)
    REFERENCES `mydb`.`Characteristic` (`id`));

insert into worker(name, profession) values("Василения И. В.", "Директор");
insert into worker(name, profession) values("Мельниченко А. О.", "Кассир");
insert into worker(name, profession) values("Тимаков А. О.", "Кладовщик");

insert into wrap(wrap_type) values ("Коробка");
insert into wrap(wrap_type) values ("Пакет");
insert into wrap(wrap_type) values ("Контейнер");
insert into wrap(wrap_type) values ("Стаканчик");
insert into wrap(wrap_type) values ("Бутылка");
insert into wrap(wrap_type) values ("Банка");

insert into measure_unit(name) values("Киллограм");
insert into measure_unit(name) values("Грамм");
insert into measure_unit(name) values("Штука");
insert into measure_unit(name) values("Литр");
insert into measure_unit(name) values("Миллилитр");

insert into company(name, city, is_manufacturer, is_supplier) values("ИП Харламов М.В.", "Орел", false, true);
insert into company(name, city, is_manufacturer, is_supplier) values("Логистический партнёр", "Орел", false, true);
insert into company(name, city, is_manufacturer, is_supplier) values("Опт-Торг", "Орел", false, true);

insert into company(name, city, is_manufacturer, is_supplier) values("Сельскохозяйственная Марёвская Корпорация", "Марево", true, false);
insert into company(name, city, is_manufacturer, is_supplier) values("ООО МЯСОПРОДУКТ", "Москва", true, false);
insert into company(name, city, is_manufacturer, is_supplier) values("ООО Правильные продукты", "Абакан", true, false);

insert into company(name, city, is_manufacturer, is_supplier) values("ООО Хэппи-Фиш", "Астрахань", true, true);

insert into characteristic(name) values("Вес");
insert into characteristic(name) values("Процент жирности");
insert into characteristic(name) values("Наличие заменителя молочного жира");
insert into characteristic(name) values("Вид приготовления");


insert into product(name, shortage_life, Company_id, Wrap_id, extra, retail_price) values(
"Сметана Простоквашино",                                             #name
35,                                                                  #shortage life
(select id from company where name = "ООО Правильные продукты"),     #company
(select id from wrap where wrap_type = "Стаканчик"),                 #wrap
25,                                                                  #extra
117.00                                                               #price
);

insert into Product_has_Characteristic(product_id, characteristic_id, numeric_value, symbol_value) values(
1,
1,
300,
NULL
);

insert into Product_has_Characteristic(product_id, characteristic_id, numeric_value, symbol_value) values(
1,
2,
20,
NULL
);

insert into Product_has_Characteristic(product_id, characteristic_id, numeric_value, symbol_value) values(
1,
3,
NULL,
"да"
);


insert into product(name, shortage_life, Company_id, Wrap_id, extra, retail_price) values(
"Сметана Простоквашино",                                         #name
35,                                                                  #shortage life
(select id from company where name = "ООО Правильные продукты"),     #company
(select id from wrap where wrap_type = "Стаканчик"),                 #wrap
25,                                                                  #extra
87.00                                                                #price
);

insert into Product_has_Characteristic(product_id, characteristic_id, numeric_value, symbol_value) values(
2,
1,
180,
NULL
);

insert into Product_has_Characteristic(product_id, characteristic_id, numeric_value, symbol_value) values(
2,
2,
15,
NULL
);

insert into Product_has_Characteristic(product_id, characteristic_id, numeric_value, symbol_value) values(
2,
3,
NULL,
"да"
);

insert into product(name, shortage_life, Company_id, Wrap_id, extra, retail_price) values(
"Сметана Простоквашино",                                             #name
35,                                                                  #shortage life
(select id from company where name = "ООО Правильные продукты"),     #company
(select id from wrap where wrap_type = "Стаканчик"),                 #wrap
25,                                                                  #extra
95.00                                                                #price
);

insert into Product_has_Characteristic(product_id, characteristic_id, numeric_value, symbol_value) values(
3,
1,
180,
NULL
);

insert into Product_has_Characteristic(product_id, characteristic_id, numeric_value, symbol_value) values(
3,
2,
15,
NULL
);

insert into Product_has_Characteristic(product_id, characteristic_id, numeric_value, symbol_value) values(
3,
3,
NULL,
"нет"
);

delimiter //
CREATE TRIGGER check_price BEFORE insert ON Invoice
       FOR EACH ROW
       BEGIN
		set @extra = (select extra from product where product.id = new.product_id);
           IF (NEW.price / 100 * (100 + @extra)) > (select retail_price from product where id = new.product_id) then
               update product set product.retail_price = (NEW.price / 100 * (100 + @extra)) where product.id = new.product_id ;
           END IF;
       END;//
delimiter ;

delimiter //
CREATE TRIGGER summarise_invoice before insert ON Invoice
       FOR EACH ROW
       BEGIN
			set new.summarised = new.amount * new.price;
            set new.taxed_summarised = new.summarised * (100 + new.tax) / 100;
       END;//
delimiter ;

insert into supply(date, company_id, worker_id) values(
DATE_SUB(date(now()), INTERVAL 1 WEEK),
2,
3
);

insert into Invoice(supply_id, product_id, measure_unit_id, amount, price, tax) values(
1,
1,
(select id from measure_unit where `name` = "Штука"),
40,
93.6,
18
);

insert into supply(date, company_id, worker_id) values(
DATE_SUB(date(now()), INTERVAL 6 WEEK),
2,
3
);

insert into Invoice(supply_id, product_id, measure_unit_id, amount, price, tax) values(
2,
1,
(select id from measure_unit where `name` = "Штука"),
30,
100,
18
);

#просроченный товар
select product_id, supply_id, name, date, date(now()), shortage_life from Invoice 
join supply on(supply.id = Invoice.supply_id)
join product on (product.id = Invoice.product_id)
where datediff(date(now()), `date`) > shortage_life;

#узнать цену товара и не истек ли срок годности
select retail_price, datediff(date(now()), `date`) as days_count, shortage_life as eatable from invoice 
join product on (product.id = invoice.product_id)
join supply on (supply.id = invoice.Supply_id)
where supply_id = 2 and product_id = 1;

insert into buy(worker_id, `datetime`) values(
2,
now()
);

delimiter //
CREATE TRIGGER summarise_buy_has_invoice before insert ON buy_has_invoice
       FOR EACH ROW
       BEGIN
			set new.summarised = new.amount * (select retail_price from product where id = new.invoice_product_id);
            update buy set summarised = summarised + new.summarised where id = new.buy_id;
       END;//
delimiter ;

insert into buy_has_invoice(buy_id, invoice_product_id, invoice_supply_id, amount) values(
1,
1,
2,
4
);

insert into cancellation(date, worker_id) values(now(), 3);

delimiter //
CREATE TRIGGER summarise_cancellation_has_invoice before insert ON cancellation_has_invoice
       FOR EACH ROW
       BEGIN
			set new.summarised = new.amount * (select price from invoice where product_id = new.invoice_product_id and supply_id = new.invoice_supply_id);
            update cancellation set summarised = summarised + new.summarised where id = new.cancellation_id;
       END;//
delimiter ;

insert into cancellation_has_invoice(cancellation_id, invoice_supply_id, invoice_product_id, amount) values(
1,
2,
1,
30
);
#drop schema mydb;

