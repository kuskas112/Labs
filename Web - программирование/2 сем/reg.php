<?php

function setFlash($msg)
{
    if(isset($_SESSION['flash'])){
        $_SESSION['flash'] = $_SESSION['flash'].'<br>'.$msg;
    }    
    else{
        $_SESSION['flash'] = $msg;
    }
}

function validateForm(&$login, &$password)
{
    if(isset($_POST['login'])){
        $login = $_POST['login'];
        if($login == ""){
            setFlash("Логин не может быть пустым");
        }
        $count = substr_count($login, ' ');
        if($count > 0){
            setFlash("Логин не должен содержать пробелов");
        }
        if(strlen($login) < 5 || strlen($login) > 30){
            setFlash("Логин должен быть длины 5-30 символов");
        }
    }
    else{
        return false;
    }
    if(isset($_POST['password'])){
        $password = $_POST['password'];
        if($password == ""){
            setFlash("Пароль не может быть пустым");
        }
        $count = substr_count($password, ' ');
        if($count > 0){
            setFlash("Пароль не должен содержать пробелов");
        }
        if(strlen($password) > 30|| !preg_match('/^[a-zA-Z0-9]{5,}$/', $password)) { // for english chars + numbers only
            setFlash("Пароль должен быть длины 5-30 символов и состоять только из латинских букв и цифр");
        }
        if(strlen($password) < 5 || strlen($password) > 30){
            setFlash("Пароль должен быть длины 5-30 символов");
        }

    }
    else{
        return false;
    }
    if(isset($_SESSION['flash'])){
        return false;
    }
    else{
        return true;
    }
}

$login;
$password;
$loggedIn = false;
if(validateForm($login, $password)){
    $query = $db->query('SELECT * from user where `name` = "'.$login.'"');
    if(mysqli_num_rows($query) > 0){
        while($row = $query->fetch_assoc()){
            if($row['password'] == md5($password)){
                $loggedIn = true;
                $_SESSION['privileges'] = $row['privileges'];
                $_SESSION['name'] = $row['name'];
                echo "Вы успешно вошли в систему, уважаемый ".$row['name'];
            }
        }
        if(!$loggedIn){
            setFlash("Такой пользователь уже зарегистрирован");
        }
    }
    else{
        $db->query('INSERT INTO user(name, password, privileges) values("'.$login.'", "'.md5($password).'", 1)');
        echo "SUCCESS ".$login;
    }
}

?>



<form method="post">
<label for="login">Введите логин</label>
<input name="login" type="text"  multiple/><br />
<label for="password">Введите пароль</label>
<input type="text" id="password" name="password">
<div>
<input type="submit" class="refactorButton" value="Подтвердить">
</div>
</form>

<?php 
if(isset($_SESSION['flash'])){
    echo $_SESSION['flash'];
    unset($_SESSION['flash']);
}
?>
