<?php 
    $pages = [
        "main" => "pages/carBlog.php",
        "about" => "pages/aboutPage.php",
        "catalog" => "pages/catalog.php",
        "car" => "car.php",
        "edit" => "edit.php",
        "add" => "add.php",
        "exit" => "exit.php",
        "reg" => "reg.php",
        "chat" => "chat.html"
    ];
    $page = $pages["main"];
    $id="0";
    
    if(isset($_GET["page"])){
        if($_GET["page"] == "car"){
            $id = $_GET["id"];
        }
        $page = $pages[$_GET["page"]];
    }
?>