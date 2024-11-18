

<div class="catalogContentBlocks">
<?php 
$activeTile = 0;
if(isset($_GET['deleteId'])){
	$db->query('DELETE FROM Cars WHERE id = '.$_GET['deleteId']);
}

?>

<div class="catalogContent" id="catalogContent">
	
</div>
</div>

<div class="paginatorContainer">
	<div class="paginator" id="paginator">
		
	</div>
</div>
    
<script>
	const paginateBy = 2;
	var pageid = 1;

	// Функция для генерации пагинации
	function generatePagination(data, itemsPerPage, currentPage) {
		var pagination = [];
		var start = (currentPage - 1) * itemsPerPage;
		var end = start + itemsPerPage;
		var paginatedData = data.slice(start, end);
		return paginatedData;
	}

	function xhrRequest(){
		// Создание объекта XMLHttpRequest
		var xhr = new XMLHttpRequest();

		// Установка типа запроса (GET или POST)
		xhr.open('POST', '/paginator.php', true);

		// Установка данных запроса
		var sendData = 'paginateby=' + paginateBy + '&pageid=' + pageid;
		xhr.send(sendData);

		// Обработка ответа сервера
		xhr.onload = function() {
			if (xhr.status === 200) {
				var data = JSON.parse(xhr.responseText);
				const content = document.getElementById('catalogContent');
				const paginator = document.getElementById('paginator');

				let first = document.createElement('a');
				first.innerHTML = 'Первая';
				first.addEventListener('click', (event) => {
					pageid = 1;
					document.getElementById('a' + pageid).click();
				});
				paginator.appendChild(first);

				let leftArrow = document.createElement('a');
				leftArrow.innerHTML = '<';
				leftArrow.addEventListener('click', (event) => {
					pageid = pageid == 1 ? 1 : pageid - 1;
					document.getElementById('a' + pageid).click();
				});
				paginator.appendChild(leftArrow);

				
				

				var amountPages = Math.floor(data.length / paginateBy) + (data.length % paginateBy != 0); 
				for (let index = 0; index < amountPages; index++) {
					let a = document.createElement('a');
					a.innerText = index + 1;
					a.id = 'a' + a.innerText;
					a.addEventListener('click', (event) => {
						pageid = index + 1;
						var paginatedData = generatePagination(data, paginateBy, pageid);
						content.innerHTML = '';
						for(let i = 0; i < paginatedData.length; i++){
							var page = document.createElement('a');
							page.innerHTML = paginatedData[i]['name'];
							page.href = '/?page=car&id=' + paginatedData[i]['id'];
							page.style.height = '80px';
							content.appendChild(page);
						}
					})
					paginator.appendChild(a);
				}

				let rightArrow = document.createElement('a');
				rightArrow.innerHTML = '>';
				rightArrow.addEventListener('click', (event) => {
					pageRef = document.getElementById('a' + (pageid + 1));
					if(pageRef != null){
						pageid += 1;
						pageRef.click();
					}
				});
				paginator.appendChild(rightArrow);


				let last = document.createElement('a');
				last.innerHTML = 'Последняя';
				last.addEventListener('click', (event) => {
					pageRef = document.getElementById('a' + amountPages);
					if(pageRef != null){
						pageid = amountPages;
						pageRef.click();
					}
				});
				paginator.appendChild(last);
				

			} else {
				console.log('Ошибка: ' + xhr.status);
			}
			document.getElementById('a1').click();

		};

		// Обработка ошибок
		xhr.onerror = function() {
			console.log('Ошибка запроса');
		};
	}

	function ajaxXHR(){
		var xhr = new XMLHttpRequest();

		xhr.open('POST', '/ajaxpaginator.php', true);
		xhr.setRequestHeader('Content-Type', 'application/x-www-form-urlencoded');

		const url = new URL(window.location.href);

		const params = new URLSearchParams(url.search);

		pageid = params.get('pageid');
		if(!pageid) pageid = 1;
		
		var sendData = 'paginateby=' + paginateBy + '&pageid=' + pageid;
		xhr.send(sendData);
		// Обработка ответа сервера
		xhr.onload = function() {
			if (xhr.status === 200) {
				var paginatedData = JSON.parse(xhr.responseText);
				console.log(paginatedData);
				const content = document.getElementById('catalogContent');
				const paginator = document.getElementById('paginator');

				let first = document.createElement('a');
				first.innerHTML = 'Первая';
				first.href = '/?page=catalog&pageid=1';
				paginator.appendChild(first);

				let leftArrow = document.createElement('a');
				leftArrow.innerHTML = '<';
				leftArrow.addEventListener('click', (event) => {
					document.getElementById('a' + pageid).click();
				});
				leftArrow.href = '/?page=catalog&pageid=' + (pageid == 1 ? 1 : pageid - 1);
				paginator.appendChild(leftArrow);

				content.innerHTML = '';

				let amountPages = paginatedData[paginatedData.length - 1];
				for (let i = 1; i <= amountPages; i++) {
					let pageNum = document.createElement('a');
					pageNum.id = 'a' + i;
					pageNum.innerHTML = i;
					pageNum.href = '/?page=catalog&pageid=' + i;
					paginator.appendChild(pageNum);
				}

				for(let i = 0; i < paginatedData.length - 1; i++){
					var page = document.createElement('a');
					page.innerHTML = paginatedData[i]['name'];
					page.href = '/?page=car&id=' + paginatedData[i]['id'];
					page.style.height = '80px';
					content.appendChild(page);
				}

				let rightArrow = document.createElement('a');
				rightArrow.innerHTML = '>';
				pageid = parseInt(pageid) + 1;
				rightArrow.href = '/?page=catalog&pageid=' + pageid;
				paginator.appendChild(rightArrow);


				let last = document.createElement('a');
				last.innerHTML = 'Последняя';
				last.href = '/?page=catalog&pageid=' + amountPages;
				paginator.appendChild(last);
				

			} else {
				console.log('Ошибка: ' + xhr.status);
			}
		}
	}
	
	function ajaxFetch(){
		const url = new URL(window.location.href);

		const params = new URLSearchParams(url.search);

		pageid = params.get('pageid');
		if(!pageid) pageid = 1;

		const data = new URLSearchParams();
		data.append('paginateby', paginateBy);
		data.append('pageid', pageid);

		// Опции для запроса
		const options = {
			method: 'POST', // Метод POST
			headers: {
				'Content-Type': 'application/x-www-form-urlencoded', // Указываем, что тело запроса будет в формате URL-encoded
			},
			body: data, // Передаем данные в теле запроса
		};

		// Выполняем запрос
		fetch('/ajaxpaginator.php', options)
		.then(response => response.json())
		.then(paginatedData => {
			const content = document.getElementById('catalogContent');
			const paginator = document.getElementById('paginator');

			let first = document.createElement('a');
			first.innerHTML = 'Первая';
			first.href = '/?page=catalog&pageid=1';
			paginator.appendChild(first);

			let leftArrow = document.createElement('a');
			leftArrow.innerHTML = '<';
			leftArrow.addEventListener('click', (event) => {
				document.getElementById('a' + pageid).click();
			});
			leftArrow.href = '/?page=catalog&pageid=' + (pageid == 1 ? 1 : pageid - 1);
			paginator.appendChild(leftArrow);

			content.innerHTML = '';

			let amountPages = paginatedData[paginatedData.length - 1];
			for (let i = 1; i <= amountPages; i++) {
				let pageNum = document.createElement('a');
				pageNum.id = 'a' + i;
				pageNum.innerHTML = i;
				pageNum.href = '/?page=catalog&pageid=' + i;
				paginator.appendChild(pageNum);
			}

			for(let i = 0; i < paginatedData.length - 1; i++){
				var page = document.createElement('a');
				page.innerHTML = paginatedData[i]['name'];
				page.href = '/?page=car&id=' + paginatedData[i]['id'];
				page.style.height = '80px';
				content.appendChild(page);
			}

			let rightArrow = document.createElement('a');
			rightArrow.innerHTML = '>';
			pageid = parseInt(pageid) + 1;
			rightArrow.href = '/?page=catalog&pageid=' + pageid;
			paginator.appendChild(rightArrow);


			let last = document.createElement('a');
			last.innerHTML = 'Последняя';
			last.href = '/?page=catalog&pageid=' + amountPages;
			paginator.appendChild(last);
			
		})
		.catch(error => console.error('Ошибка:', error));
	}
	
	ajaxFetch();
	//ajaxXHR();
	//xhrRequest();

</script>

