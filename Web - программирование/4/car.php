<div class="catalogContentBlocks">

<?php
$activeTile = $id;
include("sideMenu.php");

$images = $db->query("SELECT * FROM Cars_has_Images JOIN Images ON(Cars_has_Images.image = Images.id) WHERE car = ".$id);
$pageText = $db->query("SELECT pageText FROM Cars WHERE id = ".$id)->fetch_assoc()["pageText"];

$count = 1;
while($image = $images->fetch_assoc()){
    $pageText = str_replace("%image ".$count."%", $image["path"], $pageText);
    $count++;
}
echo($pageText);
?>

</div>

