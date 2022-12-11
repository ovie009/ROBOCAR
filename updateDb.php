<?php

    include_once "./database_connect.php";

    if (isset($_POST['data'])) {
        # code...
        $data = $_POST['data'];
        $sql = "UPDATE `robocar_datastream` SET `data` = '".$data."', `datetime` = CURRENT_TIMESTAMP WHERE `robocar_datastream`.`id` = 1;";
        mysqli_query($connect, $sql);
        echo 'Car Direction: ';
        echo $data;
        echo '<br>';
        echo 'successful';
        
    } else{
        # code...
        header("location: index.php?successful");
    }
    
    header("location: index.php?successful");


?>