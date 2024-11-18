<?php 
    $pages = [
        "main" => "pages/carBlog.php",
        "about" => "pages/aboutPage.php",
        "catalog" => "pages/catalog.php",
        "car1" => "cars/LadaEllada.php",
        "car2" => "cars/tesla.php",
        "car3" => "cars/cybertruck.php",
        "car4" => "cars/cadillac.php",
    ];

    $page = $pages["main"];
    if(isset($_GET["page"])){
        $page = $pages[$_GET["page"]];
    }
?>