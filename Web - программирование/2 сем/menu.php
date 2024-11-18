<nav>
    <ul>
        <li><a href="?page=main">Главная</a></li>
        <li><a href="?page=catalog">Список</a></li>
        <li><a href="?page=about">О нас</a></li>
        <?php 
        session_start();
        if(isset($_SESSION['name'])){
            echo '<li><a href="?page=exit">'.$_SESSION['name'].'</a></li>';
        }
        else{
            echo '<li><a href="?page=reg">Войти</a></li>';
        }
        ?>
        
    </ul>
</nav>
<hr>