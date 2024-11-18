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

$query = "SELECT * FROM Cars";
$cars = $db->query($query)->fetch_all(MYSQLI_ASSOC);

echo json_encode($cars, JSON_UNESCAPED_UNICODE);