
<?php 
$id = $_GET["id"];
$pageText = $db->query("SELECT pageText FROM Cars WHERE id = ".$id)->fetch_assoc()["pageText"];
?>
<form action="<?php echo "?page=car&id=".$id?>" method="post">
    <textarea cols="150" rows="30" name="text"><?php echo $pageText?></textarea>
    <a href=<?php echo "?page=car&id=".$id; ?> ><button class="refactorButton" type="submit">Submit</button></a>
</form>


