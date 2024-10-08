create database carblog;
use carblog;
create table Cars(
id int not null auto_increment,
`name` varchar(20),
pageText text,
primary key (id)
);

create table Images(
id int not null auto_increment,
`path` varchar(50),
primary key(id)
);

create table Cars_has_Images(
id int not null auto_increment,
car int not null,
image int not null,
primary key(id),
foreign key(car) references Cars(id) ON DELETE CASCADE,
foreign key(image) references Images(id) ON DELETE CASCADE
);

create table `Privileges`(
id int not null auto_increment,
`description` varchar(15),
primary key(id)
);

create table `User`(
id int not null auto_increment,
`name` varchar(30),
`password` varchar(255),
`privileges` int not null, 
primary key(id),
foreign key(`privileges`) references `Privileges`(id)
);


insert into Images(`path`) values ('images/LadaEllada.jpg');
insert into Images(`path`) values ('images/tesla.jpg');
insert into Images(`path`) values ('images/cybertruck.jpg');
insert into Images(`path`) values ('images/cadillac.jpg');

insert into Cars(pageText, `name`) values(
"<div class='catalogContent'>
					<img class='contentImage' src=%image 1% height='500'>

					<p>LADA Ellada (или просто EL Lada) — первый серийный российский электромобиль производства «АвтоВАЗа», всего было собрано около 100 машин пилотной партии. Построен на шасси LADA Kalina. В 2011 году впервые показан публике.</p>

					<p>Разработкой и продвижением проекта занимались Евгений Шмелёв, Сергей Курдюк, Сергей Аманов, Александр Свиридов (руководитель проекта производства экспериментальной партии), Сергей Ивлев («АвтоВАЗ»); Георгий Ефремов и Дмитрий Толмачёв (Ставропольский край).</p>

					<p>Разработка обошлась в 10 млн €, а стоимость серийного образца составляет 1,25 млн рублей (30 тыс. евро на начало 2013 года).</p>

					<p>В декабре 2012 года объявили, что около ста машин поставятся в Ставропольский край, где будут использоваться как такси, при этом администрация Ставрополья должна была субсидировать предприятию половину стоимости автомобиля. 22 января 2013 года АвтоВАЗ отгрузил первые пять электромобилей LADA Ellada из партии автотранспортному предприятию «Автоколонна 1721» в городе-курорте Кисловодске. Однако из-за разногласий администрации Ставрополья и АвтоВАЗа дальнейшие поставки не осуществлялись. Кроме того, администрацией не была построена инфраструктура зарядных станций — на весь Кисловодск только три станции. Партнёром по строительству зарядных станций выступила фирма Ensto. К 2015 году пять используемых как такси автомобиля проехали по 50—70 тыс. км.</p>

					<p>Пилотная партия из ста машин была всё же выпущена.</p>

					<p>40 машин переданы дилерам Центрального и Южного федеральных округов в качестве тестовых — для изучения спроса, а ещё около 40 остались на «АвтоВАЗе». В начале января 2014 года решено продать электромобили дилерам практически по себестоимости — 960 тысяч рублей, но продажа осуществлялась только юридическим лицам, (чтобы завод мог наблюдать эксплуатацию автомобилей).</p>

					<p>Известно, что первый частный автомобиль приобрёл глава «Ростехнологий» С. В. Чемезов, кроме того владельцем автомобиля в 2012 году стал король Иордании, а в 2014 году автомобиль приобрёл глава «Минпромторга» Денис Мантуров.</p>
			</div>",
            "Lada Ellada"
);

insert into Cars_has_Images(car, image) values (1,1);

insert into Cars(pageText, `name`) values(
"<div class='catalogContent'>
			<img class='contentImage' src='images/tesla.jpg' height='500'>

			<p>Производство началось с ограниченного выпуска 1000 седанов Signature и Signature Performance стоимостью 95 400 и 105 400 долларов соответственно и оснащённых аккумуляторами ёмкостью 85 кВт•ч.</p>

			<p>Изначально Tesla планировала начать в 2013 году производство электромобилей с аккумуляторами ёмкостью 60 кВт·ч (335 км) и 40 кВт·ч (260 км), однако из-за низкого спроса на маломощную модель 40 кВт·ч решено было отказаться от них.</p>

			<p>В июне 2013 года компания показала перезарядку Model S путём автоматической замены батареи аккумуляторов. Процедура занимает примерно 90 секунд, что более чем вдвое быстрее заправки топливного бака автомобиля подобного класса. По заявлению президента компании Илона Маска, «медленная» (20 минут для 50 % заряда аккумулятора) зарядка батареи Model S на заправочных станциях компании останется бесплатной, в то время как быстрая замена обойдётся владельцу машины в сумму около 60—80 долларов, что примерно соответствует стоимости полного бака бензина.</p>

			<p>Однако, в дальнейшем, от планов по автоматической смене батарей было решено отказаться в пользу развития сети заправок Tesla Superchargers. Только автомобили, проданные до 22 января 2017 года, будут пользоваться пожизненной бесплатной неограниченной быстрой зарядкой на станциях Tesla Superchargers; автомобили, проданные после января 2017 года, получат 400 кВт·ч бесплатной быстрой зарядки в год, при превышении этого количества, владельцу придётся оплатить стоимость потреблённого во время быстрой зарядки электричества.</p>

			<p>В 2016 году Tesla Model S получил обновлённый дизайн, частично более схожий с Model 3. В 2017 году также произошло некоторое обновление модельного ряда и теперь в продаже доступны только версии 75, 75D, 100D, P100D (цифры обозначают ёмкость аккумулятора в кВт·ч, D — полный привод, P — производительная версия).
			</p>
	</div>",
            "Tesla Model S"
);

insert into Cars_has_Images(car, image) values (2,2);

insert into Cars(pageText, `name`) values(
"<div class='catalogContent'>
					<img class='contentImage' src='images/cybertruck.jpg' height='500'>

					<p>Tesla Cybertruck — электромобиль-пикап в стиле киберпанк (индустриальная эстетика), который выпускает компания Tesla. Заявленная грузоподъёмность — порядка 1,6 тонны. В зависимости от модели на одном заряде пикап должен проезжать до 500 миль (около 804 км).</p>

					<p>Производство полноприводных двухмоторных и трёхмоторных версий Cybertruck планировалось начать в конце 2021 года, а заднеприводной одномоторной модели — в конце 2022 года, но производство было перенесено на 2022 год, а затем на начало 2023 года. В январе 2022 года все упоминания о начале производств автомобиля в 2022 году на сайте Tesla были удалены.</p>

					<p>Производство автомобиля началось в июле 2023 года.</p>

					<p>В 2012 и 2013 годах Илон Маск обсуждал создание пикапа, схожего с Ford F-250. В начале 2014 года Маск предсказывал срок в 4-5 лет до начала работы над машиной.</p>

					<p>В 2016 году Илон Маск заявил о создании пикапа с совершенно новыми свойствами. Он также упомянул возможность создания рамы и подвески для создания пикапа или небольшого фургона. В конце 2017 года размер был определён как, по меньшей мере, схожий с Ford F-150. В процессе выкаток Tesla Semi и Tesla Roadster в ноябре 2017-го показывали картинку пикапа, способного перевозить другой пикап. Идеи этого пикапа прорабатывались по меньшей мере 5 лет.</p>

					<p>В позднем 2018 году Tesla работала над двумя типами своего пикапа. Первый тип — это использование основы Mercedes-Benz Sprinter с добавленными Tesla электрической трансмиссией, батареей и электроникой. Второй тип — производство собственного пикапа Tesla, что требует больше времени. Прототип этого пикапа был отвергнут в течение подготовки к шоу в 2019 году.</p>

					<p>В марте 2019 года, сразу после запуска Tesla Model Y, Илон Маск показывал изображение пикапа и говорил, что он будет в стиле киберпанк и не всем понравится из-за его футуристичных форм и стиля персонального защищённого транспорта.</p>

					<p>В течение презентации, которая состоялась с 22 на 23 ноября 2019 года по московскому времени, Илон Маск демонстрировал материалы, из которых сделан Tesla Cybertruck. Это — нержавеющая сталь и особо прочное стекло. Особо прочное стекло не разбилось в тесте прямо на презентации, но когда Франц фон Хольцхаузен металлическим шаром попытался разбить стекла в машине, они разбились. Илон Маск пошутил, сказав что «ему есть над чем поработать», а также, что это будет стёрто на видео.</p>

					<p>Перед концом презентации Илон Маск показал Tesla Cyberquad — полностью электрический квадроцикл. Его закатили в Tesla Cybertruck по рампе, и при том он мог заряжаться от него (от розетки 120 вольт).</p>
			</div>",
            "Tesla Cybertruck"
);
insert into Cars_has_Images(car, image) values (3,3);

insert into Cars(pageText, `name`) values(
"<div class='catalogContent'>
		<img class='contentImage' src='images/cadillac.jpg' height='500'>

		<p>Escalade IQ стал третьим в семействе электрических моделей Cadillac после 5-местного кроссовера Lyriq и роскошного лифтбека Celestiq, все эти модели построены на модульной платформе Ultium с 800-вольтовой электрической архитектурой. Cadillac Escalade IQ — не замена, а альтернатива «углеводородному» рамному внедорожнику Escalade. По размерам электрический SUV сопоставим с бензиновым в длиннобазном исполнении ESV, но выглядит менее монументально и более аристократично за счёт динамичного силуэта с заваленными задними стойками кузова. Габаритная длина Escalade IQ — 5697 мм, ширина — 2167 мм, высота — 1934 мм, колёсная база — 3460 мм.</p>

		<p>Для Escalade IQ на данный момент заявлена только одна двухмоторная силовая установка (по одному мотору на ось), её максимальная отдача — 560 кВт (761 л.с.) и 1064 Нм, постоянная — 505 кВт (687 л.с.) и 834 Нм. Ёмкость вмонтированной в пол батареи — 200 кВт·ч, расчётный запас хода на одной зарядке — свыше 450 миль (724 км) по циклу EPA. До 60 миль/ч (96,56 км/ч) Escalade IQ сможет разогнаться менее чем за 5 с. Допустимая масса буксируемого прицепа — 3628 кг.</p>

		<p>Адаптивная регулируемая пневмоподвеска в дефолтном положении обеспечивает дорожный просвет на уровне 175 мм, но в зависимости от выбранного режима он может быть увеличен на 25 мм или уменьшен на 50 мм. Полноуправляемое шасси (это одна из главных «фишек» платформы Ultium) позволяет кроссоверу двигаться по диагонали, что очень удобно при парковке, максимальный угол отклонения задних колёс — 10 градусов. В стандартном оснащении будет большое количество новейших электронных ассистентов водителя, вплоть до автопилота второго уровня Super Cruise. Штатные колёса — 24-дюймовые, размерность шин — 275/50 R 24.</p>

		<p>Салон у Escalade IQ трёхрядный, процесс складывания сидений третьего ряда полностью электрифицирован, во втором ряду может быть установлен трёхместных диван либо два раздельных кресла повышенной комфортности с массой регулировок, встроенными массажёрами, раскладными столиками, индивидуальными мультимедийными экранами и прочими удобствами. Все двери могут быть оснащены электроприводом. Панорамная стеклянная крыша входит в базовое оснащение. Объём основного багажника варьируется в диапазоне от 670 до 3374 л в зависимости от количества задействованных кресел, объём переднего багажника — 345 л.</p>

		<p>С места водителя Escalade IQ во многом похож на лифтбек Escalade, но у кроссовера более широкий салон, а потому по краям 55-дюймового двухэкранного табло появились громкоговорители аудиосистемы AKG (всего их в салоне 19, 36 либо 40 в зависимости от оснащения). Микроклиматом заведует отдельный экран на широком центральном тоннеле с двумя этажами, нижний этаж — это обитая бархатом вещевая ниша с вышивкой и подсветкой. Голого пластика в отделке почти нет, зато много кожи и деревянных панелей с лазерной гравировкой.</p>

		<p>Производство Cadillac Escalade IQ начнётся летом следующего года на заводе GM Factory Zero в Детройте. Минимальная цена составит около 130 000 долларов, что довольно скромно по сравнению с лифтбеком Celestiq, который ориентирован на конкуренцию с моделями Rolls-Royce и будет стоить, как на днях выяснилось, от 340 000 долларов.</p>
</div>",
            "Cadillac Escalade IQ"
);
insert into Cars_has_Images(car, image) values (4,4);

#drop database carblog;