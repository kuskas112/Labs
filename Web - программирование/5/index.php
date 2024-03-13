<!DOCTYPE html>
<html>
	<?php include("header.php"); ?>
	<body>
		
		<header>
			Electric Car Blog
		</header>

		
		<?php 
		$db_host = "localhost"; // сервер
		$db_user = "root"; // имя пользователя
		$db_pass = "123000"; // пароль
		$db_name = "CarBlog"; // название базы данных

		$db = new mysqli($db_host, $db_user, $db_pass, $db_name);

		if ($db->connect_error) {
			echo "Нет подключения к БД. Ошибка:".mysqli_connect_error();
			exit;
		}

		include("menu.php");
		include("content.php");
		include($page);
		?>


		<?php include("footer.php"); ?>
	</body>
</html>
