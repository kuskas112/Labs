<?php 
$tiles = array_fill(0,5,"");
$tiles[$activeTile] = "active";
?>
<div class="verticalMenu">
        <a href="?page=catalog" class=<?php echo $tiles[0]?>>Каталог</a>
        <a href="?page=car1"class=<?php echo $tiles[1]?>>LADA Ellada</a>
        <a href="?page=car2"class=<?php echo $tiles[2]?>>Tesla Model S</a>
        <a href="?page=car3"class=<?php echo $tiles[3]?>>Tesla Cybertruck</a>
        <a href="?page=car4"class=<?php echo $tiles[4]?>>Cadillac Escalade IQ</a>
</div>