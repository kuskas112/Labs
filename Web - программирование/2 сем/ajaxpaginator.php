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

$paginateby = isset($_POST['paginateby']) ? $_POST['paginateby'] : 2;
$pageid = isset($_POST['pageid']) ? $_POST['pageid'] : 1;

$offset = ($pageid - 1) * $paginateby;
$query = "SELECT id, name FROM Cars LIMIT ".$paginateby." OFFSET ".$offset;
$cars = $db->query($query)->fetch_all(MYSQLI_ASSOC);
$amount = $db->query("SELECT COUNT(*) as cnt FROM Cars")->fetch_all(MYSQLI_ASSOC)[0]['cnt'];
if ($amount % $paginateby == 0){
    $amount = intdiv($amount, $paginateby);
}
else{
    $amount = intdiv($amount, $paginateby) + 1;
}
$cars[count($cars)] = $amount;
echo json_encode($cars, JSON_UNESCAPED_UNICODE);