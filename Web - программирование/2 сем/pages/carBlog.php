

    	<div class="mainPageContent">
			
    	Добро пожаловать на сайт, посвященный электромобилям! Сайт выполнен в приятных зеленых оттенках, что отсылает к экологичности этих чудес техники. Уже давно существуют различные виды электрокаров, даже знаменитый в России АвтоВАЗ имел прототип электромобиля на базе LADA Kalina. Подробнее об этом и других электромобилях смотрите в разделе "Список".

    	</div>


    	<div class="imageRow">
    		<img src="images/ladaEllada.jpg" width="500">
    		<img src="images/electroCar.jpg" width="500">
    	</div>

		<script>
			function makeRequestXHR() {
				var xhr = new XMLHttpRequest();

				xhr.open("GET", "/request.php?par=kek", true);

				xhr.onreadystatechange = function() {
					if (xhr.readyState === 4) {
						if (xhr.status === 200) {
							console.log(xhr.responseText);
						} else {
							console.error('Произошла ошибка: ' + xhr.status);
						}
					}
				};

				xhr.send();
			}

			makeRequestXHR();

		</script>

