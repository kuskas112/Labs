<div class="catalogContentBlocks">

<?php
if (isset($_POST["text"])) {
    $text = $_POST["text"];
    $db->query('UPDATE Cars SET pageText = "'.$text.'" WHERE id = '.$id);
} 

$activeTile = $id;

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
<div style="text-align: right;">
<?php
    if(isset($_SESSION['privileges'])){
        if($_SESSION['privileges'] >= 1){
            echo '<a href="?page=edit&id='.$_GET["id"].'" ><button class="refactorButton">Редактировать</button></a>';
        }
    }
?>
    
</div>


