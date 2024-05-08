CREATE SCHEMA IF NOT EXISTS `mydb`;
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


CREATE TABLE IF NOT EXISTS `mydb`.`Cancellation` (
  `id` SMALLINT UNSIGNED NOT NULL AUTO_INCREMENT,
  `summarised` DECIMAL(8,2) NULL,
  `date` DATE NOT NULL,
  PRIMARY KEY (`id`));


CREATE TABLE IF NOT EXISTS `mydb`.`Buy` (
  `id` MEDIUMINT UNSIGNED NOT NULL AUTO_INCREMENT,
  `summarised` DECIMAL(6,2) NULL,
  `datetime` DATETIME NOT NULL,
  PRIMARY KEY (`id`));


CREATE TABLE IF NOT EXISTS `mydb`.`Supply` (
  `id` SMALLINT UNSIGNED NOT NULL AUTO_INCREMENT,
  `date` DATE NOT NULL,
  `Company_id` SMALLINT UNSIGNED NOT NULL,
  PRIMARY KEY (`id`),
  CONSTRAINT `fk_Supply_Company`
    FOREIGN KEY (`Company_id`)
    REFERENCES `mydb`.`Company` (`id`));


CREATE TABLE IF NOT EXISTS `mydb`.`Product` (
  `id` MEDIUMINT UNSIGNED NOT NULL AUTO_INCREMENT,
  `name` VARCHAR(50) NOT NULL,
  `description` VARCHAR(70) NULL,
  `shortage_life` SMALLINT UNSIGNED NOT NULL,
  `Company_id` SMALLINT UNSIGNED NOT NULL,
  `Wrap_id` SMALLINT UNSIGNED NOT NULL,
  `extra` TINYINT UNSIGNED NOT NULL,
  `retail_price` DECIMAL(7,2) NULL,
  `mass` SMALLINT UNSIGNED NOT NULL,
  PRIMARY KEY (`id`),
  CONSTRAINT `fk_Product_Company1`
    FOREIGN KEY (`Company_id`)
    REFERENCES `mydb`.`Company` (`id`),
  CONSTRAINT `fk_Product_Wrap1`
    FOREIGN KEY (`Wrap_id`)
    REFERENCES `mydb`.`Wrap` (`id`));


CREATE TABLE IF NOT EXISTS `mydb`.`Supply_has_Product` (
  `Supply_id` SMALLINT UNSIGNED NOT NULL,
  `Product_id` MEDIUMINT UNSIGNED NOT NULL,
  `Measure_unit_id` SMALLINT UNSIGNED NOT NULL,
  `amount` SMALLINT UNSIGNED NOT NULL,
  `price` DECIMAL(7,2) NOT NULL,
  `tax` DECIMAL(2,2) NOT NULL,
  `summarised` DECIMAL(8,2) NULL,
  `taxed_summarised` DECIMAL(8,2) NULL,
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


CREATE TABLE IF NOT EXISTS `mydb`.`Cancellation_has_Supply_has_Product` (
  `Cancellation_id` SMALLINT UNSIGNED NOT NULL,
  `Supply_has_Product_Supply_id` SMALLINT UNSIGNED NOT NULL,
  `Supply_has_Product_Product_id` MEDIUMINT UNSIGNED NOT NULL,
  `amount` SMALLINT UNSIGNED NOT NULL,
  `summarised` DECIMAL(8,2) NULL,
  PRIMARY KEY (`Cancellation_id`, `Supply_has_Product_Supply_id`, `Supply_has_Product_Product_id`),
  CONSTRAINT `fk_Cancellation_has_Supply_has_Product_Cancellation1`
    FOREIGN KEY (`Cancellation_id`)
    REFERENCES `mydb`.`Cancellation` (`id`),
  CONSTRAINT `fk_Cancellation_has_Supply_has_Product_Supply_has_Product1`
    FOREIGN KEY (`Supply_has_Product_Supply_id` , `Supply_has_Product_Product_id`)
    REFERENCES `mydb`.`Supply_has_Product` (`Supply_id` , `Product_id`));


CREATE TABLE IF NOT EXISTS `mydb`.`Buy_has_Product` (
  `Buy_id` MEDIUMINT UNSIGNED NOT NULL,
  `Product_id` MEDIUMINT UNSIGNED NOT NULL,
  `amount` SMALLINT UNSIGNED NOT NULL,
  `summarised` DECIMAL(6,2) NULL,
  PRIMARY KEY (`Buy_id`, `Product_id`),
  CONSTRAINT `fk_Buy_has_Product_Buy1`
    FOREIGN KEY (`Buy_id`)
    REFERENCES `mydb`.`Buy` (`id`),
  CONSTRAINT `fk_Buy_has_Product_Product1`
    FOREIGN KEY (`Product_id`)
    REFERENCES `mydb`.`Product` (`id`));

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

insert into product(name, shortage_life, mass, Company_id, Wrap_id, extra, retail_price) values(
"Сметана Простоквашино 20%",                                         #name
35,                                                                  #shortage life
300,                                                                 #mass
(select id from company where name = "ООО Правильные продукты"),     #company
(select id from wrap where wrap_type = "Стаканчик"),                 #wrap
25,                                                                  #extra
117.00                                                               #price
);

insert into product(name, shortage_life, mass, Company_id, Wrap_id, extra, retail_price) values(
"Сметана Простоквашино 15%",                                         #name
35,                                                                  #shortage life
300,                                                                 #mass
(select id from company where name = "ООО Правильные продукты"),     #company
(select id from wrap where wrap_type = "Стаканчик"),                 #wrap
25,                                                                  #extra
87.00                                                                #price
);

insert into product(name, shortage_life, mass, Company_id, Wrap_id, extra, retail_price) values(
"Сметана Простоквашино БЗМЖ 15%",                                    #name
35,                                                                  #shortage life
180,                                                                 #mass
(select id from company where name = "ООО Правильные продукты"),     #company
(select id from wrap where wrap_type = "Стаканчик"),                 #wrap
25,                                                                  #extra
95.00                                                                #price
);

#drop schema mydb;
#drop schema mydb;
