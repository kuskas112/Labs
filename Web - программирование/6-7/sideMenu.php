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
        while ($row = $cars->fetch_assoc()) 
		{
			echo "<div class='catalogContentBlocks'>";
			if ($activeTile == $row["id"]) {
				echo "<a class='active' href='?page=car&id=".$row["id"]."'>".$row["name"]."</a>";
			} 
			else {
				echo "<a href='?page=car&id=".$row["id"]."'>".$row["name"]."</a>";
			}
			if(isset($_SESSION['privileges'])){
				if($_SESSION['privileges'] > 2){
					echo "<a href='?page=catalog&deleteId=".$row['id']."'>X</a>";
				}
			}
			echo "</div>";

        }
		if(isset($_SESSION['privileges'])){
			if($_SESSION['privileges'] > 1){
				echo "<a href='?page=add'><button class='refactorButton'>Добавить</button></a>";
			}
		}
        ?>        


</div>