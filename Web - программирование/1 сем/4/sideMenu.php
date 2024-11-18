<?php 
$cars = $db->query("SELECT * FROM Cars");
?>
<div class="verticalMenu">
        
        <?php 
        if($activeTile == 0){
                echo "<a class='active' href='?page=catalog'>Каталог</a>";
        }
        else{
                echo "<a href='?page=catalog'>Каталог</a>";
        }
        while ($row = $cars->fetch_assoc()) {
                if ($activeTile == $row["id"]) {
                        echo "<a class='active' href='?page=car&id=".$row["id"]."'>".$row["name"]."</a>";
                } 
                else {
                        echo "<a href='?page=car&id=".$row["id"]."'>".$row["name"]."</a>";
                }
        }
        ?>        
</div>