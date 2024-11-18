<?php


if (isset($_POST["name"])) {
    $name = $_POST['name'];
    $db->query('INSERT INTO Cars(`name`) VALUES("'.$name.'")');
    $text = $_POST["text"];
    $text = str_replace('"', "'", $text);
    $car = $db->query('SELECT id FROM Cars WHERE `name`="'.$name.'"');
    $car_id = $car->fetch_assoc()['id'];

    if(isset($_FILES['inputfile'])){ // Проверяем, загрузил ли пользователь файл
        for ($i=0; $i<count($_FILES['inputfile']['name']); $i++){
            $destiation_dir = 'images/'.$_FILES['inputfile']['name'][$i]; // Директория для размещения файла
            $db->query('INSERT INTO images(`path`) VALUES("'.$destiation_dir.'")');
            $img = $db->query('SELECT id FROM images WHERE `path`="'.$destiation_dir.'"');
            $img_id = $img->fetch_assoc()['id'];

            $db->query('INSERT INTO cars_has_images(`car`, `image`) VALUES('.$car_id.','.$img_id.')');
            move_uploaded_file($_FILES['inputfile']['tmp_name'][$i], $destiation_dir ); // Перемещаем файл в желаемую директорию
        }
        echo 'File Uploaded'; // Оповещаем пользователя об успешной загрузке файла
    }
    else{
        echo 'No File Uploaded'; // Оповещаем пользователя о том, что файл не был загружен
    }

    
    $db->query('UPDATE Cars SET pageText = "'.$text.'" WHERE id = '.$car_id);
} 

    
?>


<form method="post" action="" enctype="multipart/form-data">
<label for="inputfile">Загрузить изображения</label>
<input accept=".jpg, .jpeg, .png" name="inputfile[]" type="file"  multiple/><br />
<label for="name">Название машины</label>

<input type="text" id="name" name="name">
<textarea cols="60" rows="20" name="text"></textarea>
<input type="submit" value="Click To Upload">
</form>
